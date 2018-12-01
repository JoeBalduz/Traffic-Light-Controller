# Traffic-Light-Controller

This is a traffic light controller that was created using the Tiva C Series TM4C123G. A breadboard, some LEDs, switches, and resistors
were also used to create this traffic light controller. An image of the setup of the road this traffic light is designed to work
on is linked below.

https://i.imgur.com/Y38acAG.jpg

# Design
I first started off by thinking of every possible state the traffic lights and the pedestrian walk light could be in. The west and south
light should never be green and green or yellow and green at the same time. Another thing that could never happen at the same time is
having the pedestrian walk light be on at the same time as one of the lights is green. The states I came up with are as follows.

Go West\t\t\t                       Yellow West                     Go South

1000010                       0100010                         00110000


Yellow South                  Walk                            Walk Fast

0010100                       0010011                         0010010
