#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<wchar.h>
#include<locale.h>
#include<time.h>
#include<SDL2/SDL.h>

const int screenWidth = 1920;
const int screenHeight = 1080;

int mapHeight = 16;
int mapWidth = 16;
int fov = 3.14/2;
int rayMaxDepth = 16;
struct Player{
	float x;
	float y;
	float angle;
};

int map[] = {
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void delay(int milliseconds){
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int main(){

	uint32_t screenBuffer[screenWidth * screenHeight];
	SDL_Window * window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture * screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screenWidth, screenHeight);
	int i;
	int size = screenWidth*screenHeight;
	struct Player player;
	player.x = 8.0f;
	player.y = 8.0f;
	player.angle = 0.0f;
	clock_t lastUpdate = clock();
	// Game loop
	int running = 1; // adding kill functionality	
	while(running){
		SDL_Event event; // queues event
		clock_t startGameLoop = clock();

		// Physics
		// delta time calculations
		clock_t currentUpdate = clock();
		float deltaTime =(double)(currentUpdate - lastUpdate)/CLOCKS_PER_SEC;
		lastUpdate = currentUpdate;
		
		while(SDL_PollEvent(&event)){ // dequeues event and checks its value
			switch(event.type){
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.scancode){
				case SDL_SCANCODE_W:
					player.x += sinf(player.angle) * 5.0f * deltaTime;
					player.y += cosf(player.angle) * 5.0f * deltaTime;
					if(map[(int)(player.x) + (int)player.y * mapWidth] != 0){ // resets if inside of a block. this move forward and back isn't shown by the renderer but can be optimised
						player.x -= sinf(player.angle) * 5.0f * deltaTime;
						player.y -= cosf(player.angle) * 5.0f * deltaTime;
					}
					break;
				case SDL_SCANCODE_S:
					player.x -= sinf(player.angle) * 5.0f * deltaTime;
					player.y -= cosf(player.angle) * 5.0f * deltaTime;
					if(map[(int)(player.x) + (int)player.y * mapWidth] != 0){ // resets if inside of a block. this move forward and back isn't shown by the renderer but can be optimised
						player.x += sinf(player.angle) * 5.0f * deltaTime;
						player.y += cosf(player.angle) * 5.0f * deltaTime;
					}
					break;
				case SDL_SCANCODE_A:
					//strafe left
					break;
				case SDL_SCANCODE_D:
					//strafe right
					break;
				case SDL_SCANCODE_LEFT:
					player.angle -= 0.5f * deltaTime;
					break;
				case SDL_SCANCODE_RIGHT:
					player.angle += 0.5f * deltaTime;
					break;

				}
				break;
			}
		}

	

		// Render 
		for(int x=0; x < screenWidth; x++){
			// For each column calculate projected ray angle in world space
			float rayAngle = (player.angle - fov / 2.0f) + ((float)x / (float)screenWidth)*fov;
			float distToWall = 0;
			bool hitWall = false;
			float eyeX = sinf(rayAngle);
			float eyeY = cosf(rayAngle);

			while(!hitWall&&distToWall< rayMaxDepth){
				distToWall += 0.1f;
				int testX = (int)(player.x + eyeX*distToWall);
				int testY = (int)(player.y + eyeY*distToWall);
				if(testX < 0 || testX >= mapWidth || testY < 0 || testY >= mapHeight){
					hitWall = true;
					distToWall = rayMaxDepth;

				}
				else{
					if(map[testX + testY * mapWidth] != 0){
						hitWall = true;
					}

				}

			}
			distToWall = distToWall * cosf(player.angle - rayAngle );
			int ceiling = (float)(screenHeight / 2.0) - screenHeight / ((float)distToWall);
			int floor = screenHeight - ceiling;
			
			// RGB = (R*65536)+(G*256)+B , (when R is RED, G is GREEN and B is BLUE) must add alpha too
			for(int y = 0; y < screenHeight; y++){
				if(y < ceiling){
					screenBuffer[y * screenWidth + x] = (uint32_t)0xFF190033;
				}
				else if(y > ceiling && y <= floor){
					// screenBuffer[x+y*screenWidth] = wallColor[(int)(wallColorLen*(distToWall/(float)rayMaxDepth))];
					screenBuffer[y * screenWidth + x] = (uint32_t)(0xFF000000 + (1 / distToWall * 65536) + (1 / distToWall * 256) + (1 / distToWall)); // Make a color based on the distance you are to the wall so that you have a sense of distance despite not having textures.
				}
				else{
					/*
					float b = 1.0f - (((float)y - screenHeight / 2.0f) / ((float)screenHeight / 2.0f));
					screenBuffer[x+y*screenWidth] = (b<1)?floorShading[(int)(floorShadingLen * b)]:' ';
					*/
					screenBuffer[y * screenWidth + x] = (uint32_t)0xFF00FF00;
				}

			}

		}


	SDL_UpdateTexture(screen, NULL, screenBuffer, screenWidth * sizeof(uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screen, NULL, NULL);
	SDL_RenderPresent(renderer);

	// frame cap
	clock_t endGameLoop = clock();
	double elapsedLoopTime = (double)(endGameLoop - startGameLoop) / CLOCKS_PER_SEC;
	delay(16.6666f-elapsedLoopTime*1000);
	}

	SDL_DestroyTexture(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

