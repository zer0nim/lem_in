# 42 _ lem_in

An ant farm manager

## Info
Some students of the School of Wizardry have created Hex, a thinking machine.

It is composed of ants for calculus, bee-hives and bees for memory and a mouse for (.. Huh,
right, what for already?) cheese (to feed the mouse) and a feather for writing.

> For more information, please refer to Terry Pratchett’s books, so
that you can switch your mind off 42. (**) Ook !

We are going to look in depth at its calculus bit.

How does it work? **Simple**! We make an **ant farm**, with tunnels and rooms; we place the ants on one side; and we look at how they find the exit.

How do we build an ant farm ?

We need tubes and rooms, we join the rooms to one another with as many tubes as we need.
A tube joins two rooms to each other.

No more than that.

A room can be linked to an infinite number of rooms and by as many tubes as deemed necessary. Then we must bury the ant farm (wherever you want).

This is extremely important to ensure that ants don’t cheat and look at your design before the game starts.

Because arts and crafts with boxes, tape and ropes are not our greatest strength, we will
create a digital version instead.
The goal of this project is to create an “Hex” simulator.


## how does it work ?
Your program will receive the data describing the ant farm from the standard output
in the following format
```
number_of_ants
the_rooms
the_links
```

The ant farm is defined by the following links:
```
$> cat test_map/subject.map
10
##start
room1 23 3
room2 16 7
#commentaire
room3 16 3
room4 16 5
room5 9 3
room6 1 5
room7 4 8
##end
room0 9 5
room0-room4
room0-room6
room1-room3
room4-room3
room5-room2
room3-room5
#autre commentaire
room4-room2
room2-room1
room7-room6
room7-room2
room7-room4
room6-room5
```

Which corresponds to the following representation

```
           _______________
          /               \
  ______[5]----[3]----[1]  |
 /              |    /     |
[6]-----[0]----[4]  /      |
 \    _________/|  /       |
  \  /         [2]/_______/
   [7]_________/

```
There are two parts

* The rooms, which are defined by: `name` `coord_x` `coord_y`
* The links, which are defined by: `name1`-`name2`
* All of it is broken by comments, which start with `#`

The results is printed on the standard output in the following format
```
// The map

Lx-y Lz-w Lr-o ...
```
`x`, `z`, `r` represents the ants’ numbers (going from 1 to number_of_ants)

and `y`, `w`, `o` represents the rooms’ names.

## Compiling
> Made for OS X only

Run `Make`

## Try it !

./lem-in < `map`

#### Exemple

```
$> ./lem-in < test_map/subject.map
10
##start
room1 23 3
room2 16 7
#commentaire
room3 16 3
room4 16 5
room5 9 3
room6 1 5
room7 4 8
##end
room0 9 5
room0-room4
room0-room6
room1-room3
room4-room3
room5-room2
room3-room5
#autre commentaire
room4-room2
room2-room1
room7-room6
room7-room2
room7-room4
room6-room5

L1-room3 L2-room2
L1-room4 L2-room7 L3-room3 L4-room2
L1-room0 L2-room6 L3-room4 L4-room7 L5-room3 L6-room2
L2-room0 L3-room0 L4-room6 L5-room4 L6-room7 L7-room3 L8-room2
L4-room0 L5-room0 L6-room6 L7-room4 L8-room7 L9-room3 L10-room2
L6-room0 L7-room0 L8-room6 L9-room4 L10-room7
L8-room0 L9-room0 L10-room6
L10-room0
```

#### Options

`--nbstep` print number of move instead of result

`-start` `name` change the start room

`-end` `name` change the end room

`-nbant` `nb` change the number of ant

#### Exemple

```
$> ./lem-in < test_map/subject.map --nbstep -start "room3" -end "room7" -nbant 42
16
```

## Visualizer

For a better understanding of the path(s) choosed i made a visualizer

## Commands

| Key           | Action        |
| ------------- |:-------------:|
| arrow or wasd | move          |
| shift         | zoom-in       |
| ctrl          | zoom-out      |
| space         | play / pause  |
| right-alt     | next-move     |
| enter         | full-screen   |


You can run it like this

./lem-in < `map` | ./lem_in_visu/lem-in-visu

```
$> ./lem-in < test_map/subject.map | ./lem_in_visu/lem-in-visu
```

![subject.map](../assets/subject.map.png)
![my3.map](../assets/my3.map.png)
![zoom_in](../assets/zoom_in.png)
