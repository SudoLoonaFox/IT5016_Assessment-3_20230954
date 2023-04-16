using Luxor
function dragon(turtle::Turtle, level=4, size=200, direction=45)
    if level != 0
        Turn(turtle, -direction)
        dragon(turtle, level-1, size/sqrt(2), 45) # Recursively call dragon with level being decreased until it reaches 0
        Turn(turtle, direction*2)
        dragon(turtle, level-1, size/sqrt(2), -45)
        Turn(turtle, -direction)
    else
        Forward(turtle, size)
    end
end

Drawing(900, 500, "./Dragon.png")
t = Turtle(300, 300, true, 0, (0., 0.0, 0.0)); 
dragon(t, 10,400)
finish()
preview()

# Idk what to really comment. This code is very elegant and neat
