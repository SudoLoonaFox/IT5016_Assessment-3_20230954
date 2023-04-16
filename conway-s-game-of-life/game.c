#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>
#include<time.h>
#include<SDL2/SDL.h>

const int screenWidth = 1920;
const int screenHeight = 1080;

float framerate = 2;

void delay(int milliseconds){
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
void randomBufferFill(int* buffer, int width, int height);
void swapBuffers(int** buffer_1, int** buffer_2);

int main(){
	int* screenBuffer = malloc(sizeof(uint32_t)*screenWidth*screenHeight);
	int* currentBuffer = malloc(sizeof(uint32_t)*screenWidth*screenHeight);
	int* previousBuffer = malloc(sizeof(uint32_t)*screenWidth*screenHeight);

	SDL_Window* window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Texture* screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, screenWidth, screenHeight);
	// clock_t lastUpdate = clock();

	srand(time(NULL));
	
	randomBufferFill(currentBuffer, screenWidth, screenHeight);

	// Game loop
	int running = 1; // adding kill functionality	
	while(running){
		SDL_Event event; // queues event
		clock_t startGameLoop = clock();
		/*
		// delta time calculations
		clock_t currentUpdate = clock();
		float deltaTime =(double)(currentUpdate - lastUpdate)/CLOCKS_PER_SEC;
		lastUpdate = currentUpdate;
		*/
		while(SDL_PollEvent(&event)){ // dequeues event and checks its value
			switch(event.type){
			case SDL_QUIT:
				running = 0;
				break;
			}
		}

	for(int y=0; y<screenHeight; y++){
		for(int x=0; x<screenWidth; x++){
			int neighbours = 0;
			neighbours += ((x-1)>0 &&(y+1)<screenHeight)?currentBuffer[(x-1) + (y+1)*screenWidth]:0;
			neighbours += ((y+1)<screenHeight)?currentBuffer[x + (y+1)*screenWidth]:0;
			neighbours += ((x+1)<screenWidth &&(y+1)<screenHeight)?currentBuffer[(x+1) + (y+1)*screenWidth]:0;
			neighbours += ((x-1)>0)?currentBuffer[(x-1) + y*screenWidth]:0;
			neighbours += ((x+1)<screenWidth)?currentBuffer[(x+1) + y*screenWidth]:0;
			neighbours += ((x-1)>0 &&(y-1)>0)?currentBuffer[(x-1) + (y-1)*screenWidth]:0;
			neighbours += ((y-1)>0)?currentBuffer[x + (y-1)*screenWidth]:0;
			neighbours += ((x+1)<screenWidth &&(y-1)>0)?currentBuffer[(x-1) + (y-1)*screenWidth]:0;
			if(neighbours<2){
				previousBuffer[x+y*screenWidth] = 0;
				continue;
			}
			if(neighbours==3){
				previousBuffer[x+y*screenWidth] = 1;
				continue;
			}
			if(neighbours>3){
				previousBuffer[x+y*screenWidth] = 0;
				continue;
			}
		}
	}




	swapBuffers(&currentBuffer, &previousBuffer);
	// Render Screen
	for(int i = 0; i<screenWidth*screenHeight; i++){
		screenBuffer[i] = (currentBuffer[i] == 1)?0xff1a2536:0xaa000000;
	}
	SDL_UpdateTexture(screen, NULL, screenBuffer, screenWidth * sizeof(uint32_t));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screen, NULL, NULL);
	SDL_RenderPresent(renderer);

	// frame cap
	clock_t endGameLoop = clock();
	double elapsedLoopTime = (double)(endGameLoop - startGameLoop) / CLOCKS_PER_SEC;
	delay((1/framerate*1000)-elapsedLoopTime*1000);
	}

	SDL_DestroyTexture(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	free(screenBuffer);

	return 0;
}

void randomBufferFill(int* buffer, int width, int height){
	for(int i=0; i<width*height; i++){
		buffer[i] = rand() % 2;
	}
}

void swapBuffers(int** buffer_1, int** buffer_2){
	int* temp = *buffer_1;
	*buffer_1 = *buffer_2;
	*buffer_2 = temp;
}

