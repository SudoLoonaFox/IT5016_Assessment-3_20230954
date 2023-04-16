# Research Repository
## IT5016
---
### Introduction
The vast majority of my codes are in c so I am including those here. I have written codes in fortran and c++ and python but I don't have access to most of those codes at the moment as they are stored on a hard drive that isn't at my place. So I'm making do with the codes I do have saved here. I rarely write python code so don't have many examples of that and many of my projects aren't large enough to have proper design patterns like making code that minimises dependencies between sections and making code modular.
[github repo](https://github.com/SudoLoonaFox/IT5016_Assessment-3_20230954)

### Thoughts
The fast inverse square root is my favourite piece of code that i have found. It is slightly complex with the math used. Writing an explanation in markdown wouldn't be pleasant (No typesetting for math in native markdown). While the line labeled evil bit hack is not considered good c code i personally like it. You could use a union to do this however this way is more interesting to me and likely works the same way as a union when translated to assembly.
This math does actually come from a scientific paper a few years prior. It is a very good optimization and shows that keeping up to date on math and algorithms can lead to some heavy optimisation opportunities if you can spot use cases

A mind is born is one of the most fascinating codes i have come across. It is a demo for the commodore 64 that is only 256 bytes long. This code inspired me to learn commodore 64 basic and eventually how to program for the gameboy advance (i have real hardware i can demonstrate this with).
Its use of a linear feedback shift register to create audio is really interesting and is something i could try applying on systems with very small amounts of memory. It is also a good system for generating seemingly random numbers. I might attempt implementing this on other hardware however working with audio on a microcontroller isn't pleasant in c.
You can view it as hexadecimal in vim by typing `:%!xxd` which is a simple way to turn vim into a sort of hex editor. This command just overwrites the buffer with the output from the xxd command. `:%!xxd -r` reverses this. However it is still not readable. Also I am unsure if the endianness between the two is the same so it might display incorrectly

gba\_mandelbrot is a code i created myself as my first code for the gameboy advance. It does not use any libraries and can generate a mandelbrot set on the gameboy advance (although not very fast due to the amount of iterations needed for each pixel)

Conways game of life is a code i made very late at night (3am to around 6am according to the git commit). It isn't the best written and some choices are probably not good practice eg swapping buffers through double pointers instead of changing which buffer is active (I'm not sure this is actually that bad though just not a normal way to do it). Furthermore the neighbour testing section is a bit more compact than it needs to be
n Systems Hungarian notation, the prefix encodes the actual data type of the variable. For example: 
wolfenstein\_style\_engine was an attempt at creating a wolfenstein engine in c. The math requires some tweaking. The version included doesn't have any walls added but they can be easily added in the code. If I was to expand on this code I would use a modular system like I saw in the doom engine to make the code easy to improve.

Ticket\_system.py is a program I made for an assignment which is a basic ticketing system. I also created a c++ version of this code.

Ticket\_system.cpp is a version written in c++ which employs a modular design pattern and object orientated code which is a scalable method of writing code.

rand.c is from libc and is really interesting. The random numbers are generated with a seed and then a simple equation is done on that to make random numbers. Unfortunately there are the limitations of pseudorandom numbers and the fact that the library isn't cryptographically secure. It uses a static(c static is different to other languages) variable so that you don't have to pass in a value every time that the equation is run. The simple equation of `*seed = *seed * 1103515245 + 12345;` being used (also using a bitwise and to keep it from always increasing) is such a simple and elegant way. It does use the static variable of next as the seed input to the rand\_r function which is an elegant way to do this. I did find it strange that srand doesn't actually use the value supplied in the version of this code I am seeing which makes little sense as this is the value that controls the initial seed in normal use

Doom src. I'm not including this one as a file due to size but I have read through a large portion of this and I have noticed some very important design choices. One was to keep the code modular there are many parts for each main function that needs to be performed in the game. The drawing, rendering, video, audio and many others are all separate and inside of these they are made modular by splitting each section into functions that work together without many dependencies on other sections (although there are definitely dependencies). This allows the code to be easy to maintain and expand as well as modify as reducing interconnectivity can lead to more maintainable code.
The use of the naming system employed also makes knowing which parts of code a certain function belongs to which is very beneficial as some functions might have similar names. In the absence of namespaces this is a good idea in certain types of projects

Median of two sorted arrays. This was a problem I saw on leetcode and the solution while easy to understand is more complicated to implement. This isn't my solution but it is a solution that I like

Dragon (julia) This is just a really nice simple example of recursion which is quite pretty. I personally almost always avoid recursion when possible with only a few exceptions as there are issues with it however this is a nice example of when recursion makes a problem significantly easier and neater. Another nice example is the quick sort i included

The codes that I wrote are:

conway-s-game-of-life
gba\_mandelbrot
reverse\_int.asm
ticket\_system.cpp
ticket\_system.py
wolfenstein-style-engine


## Conclusion
---
The codes I have studied have shown a few design patterns that I will be implementing in other codes I write. When I eventually start a big project I will use the modularity I have learned from studying the doom source as well as object orientated programming which I learned when writing the ticketing system in c++. I have never been a fan of object orientated code as it can lead to more interconnected code which can make changing features more complex. I especially dislike inheritance and polymorphism in most cases as this can make code more difficult to read. Recursion can be useful in programming however I largely avoid it due to memory usage however in certain circumstances it would be far preferable to using an iterative function. This is shown in the dragon curve and the quick sort. I have written a max heap before without recursion however it would be easier to use recursion. I do have a partially done version of this in assembly but gave up because debugging assembly is very tedious and unpleasant.
