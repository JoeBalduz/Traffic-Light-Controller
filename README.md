# Traffic-Light-Controller

This is a traffic light controller that was created using the Tiva C Series TM4C123G. A breadboard, some LEDs, switches, and resistors
were also used to create this traffic light controller. An image of the setup of the road this traffic light is designed to work
on is below.

![street intersection](https://i.imgur.com/Y38acAG.jpg)

# Design

I would be using 6 LEDs for the traffic light outputs. Three of them would be for the west light and three of them would be for the 
south light. I would then also use an LED that is on the TM4C123G that would be for the pedestrian light. Three switches would be used 
as sensors for cars and pedestrians. The sensors will be used to change the lights. Below is what the traffic light controller looked 
like when it was completed. The pedestrian light is underneath the board.

![final design](https://i.imgur.com/HZYJh8x.png)

I first started off by thinking of every possible state the traffic lights and the pedestrian walk light could be in. The west and south
light should never be green and green or yellow and green at the same time. Another thing that could never happen at the same time is
having the pedestrian walk light be on at the same time as one of the lights is green. The states I came up with are shown in the image
below.

![state table](https://i.imgur.com/leOgN5j.png)

The bits represent the lights. The first 3 bits are the green, yellow, and red light for the west light. The second set of 3 bits are
the green, yellow, and red light for the south light. The final bit is the pedestrian walk light. When any of the traffic lights have a 
1,  that means the light is on. When any of the traffic lights have a 0, it is off. If the pedestrian light has a 1, that means it is 
green and pedestrians should cross the street. If the pedestrian light has a 0, that means it is red and pedestrians should not cross. 
In the last state, Walk Fast, my state shows the light as being off. What I actually want it to do is flash so that the pedestrians know 
that the light will go red soon. Now that I had all my possible states I could then draw a finite state machine to help me figure out 
how I will transisiton to different states. The finite state machine I came up with is shown below.

![finite state machine](https://i.imgur.com/lVnGqPD.png)

The inputs bits represent the sensors. The most significant bit means the pedestrian sensor, the middle bit means the west sensor, and 
the least significant bit means the south sensor.

All that was left in the design was figuring out which ports I would use. I decided to use PB5-PB3 for the west lights, PB2-PB0 for the
south lights, PA4 for the pedestrian sensor, PA3 for the west sensor, and PA2 for the south sensor. PF1 was used for the don't walk
light and PF3 was used for the walk light.

# How it Works
From the state machine, you can tell what will happen when certain inputs are pressed at different states. When a switch is pressed,
that means that there is a car, or a pedestrian, waiting to get their turn to go. The traffic lights work just how they do in real life.
They go from green to yellow to red and then back to green again. The pedestrian light will be green when they can cross, flash red when
they need to hurry up, and be red when they can no longer cross. I made the times of the lights much shorter than they are in real life
so that I'm able to go through all of the states faster. Below is a link to a video of the working traffic light controller.

https://www.youtube.com/watch?v=Lz2lez73DQE&feature=youtu.be
