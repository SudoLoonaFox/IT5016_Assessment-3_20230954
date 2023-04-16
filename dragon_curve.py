# from rosetta code
from turtle import * # imports all turtle elements. Turtle is a pen style graphics library in python

def dragon(step, length): # Unnecessary but calls dcr with the same arguments
    dcr(step, length)

def dcr(step, length):
    step -= 1
    length /= 1.41421
    if step > 0:
        right(45)
        dcr(step, length)
        left(90)
        dcl(step, length)
        right(45)
    else:
        right(45)
        forward(length)
        left(90)
        forward(length)
        right(45)

def dcl(step, length):
    step -= 1
    length /= 1.41421

    if step > 0:
        left(45)
        dcr(step, length)
        right(90)
        dcl(step, length)
        left(45)
    else:
        left(45)
        forward(length)
        right(90)
        forward(length)
        left(45)
