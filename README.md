# Traffic-Light-Controller

This is a traffic light controller that was created using the Tiva C Series TM4C123G. A breadboard, some LEDs, switches, and resistors
were also used to create this traffic light controller. An image of the setup of the road this traffic light is designed to work
on is linked below.

![street intersection](https://i.imgur.com/Y38acAG.jpg)

# Design
I first started off by thinking of every possible state the traffic lights and the pedestrian walk light could be in. The west and south
light should never be green and green or yellow and green at the same time. Another thing that could never happen at the same time is
having the pedestrian walk light be on at the same time as one of the lights is green. The states I came up with are shown in the image
below.

![state table](https://i.imgur.com/leOgN5j.png)

The bits represent the lights. The first 3 bits are the green, yellow, and red light for the west light. The second set of 3 bits are
the green, yellow, and red light for the south light. The final bit is the pedestrian walk light. When any of the traffic lights have a 1, 
that means the light is on. When any of the traffic lights have a 0, it is off. If the pedestrian light has a 1, that means it is green
and pedestrians should cross the street. If the pedestrian light has a 0, that means it is red and pedestrians should not cross. In the 
last state, Walk Fast, my state shows the light as being off. What I actually want it to do is flash so that pedestrians know that the
light will go red soon.
