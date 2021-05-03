# Question description

During the next Amazon summit, the Amazon robotics team wants to demonstrate how easy it is to use their latest robot.

For the event, they have built a simple language to control it:

* <i>G</i> instructs the robot to move forward one step.
* <i>L</i> instructs the robot to turn left in place.
* <i>R</i> instructs the robot to turn right in place.

To keep the event more interactive, once the robot has completed the list of instructions, it will repeat them in an
infinite loop.

Given the time and effort in building this robot, the robotics team don't want to lose it because of a bad sequence of
instructions. They've asked you to build a simulator based on a list of commands that will determine if it exists a
circle such that the robot always moves within the circle.

Consider the commands R and G executed infinitely. A diagram of the robot's movement looks like:

```
RG --> RG
^      |
|      v
RG <-- RG
```

The robot will never leave the circle.

## Function description

Complete the function `doesCircleExist` in the editor below. The function must return an array of `n` strings either
'YES' or 'NO' based on whether the robot is bound within a circle or not, in order of test results.

`doesCircleExist` has the following parameter(s):

* commands[commands[0], ..., commands[n-1]]: An array of `n` `commands[i]` where each represents a list of commands to
  test.

## Constraints

* 1 <= | commands[i] | <= 2500
* 1 <= n <= 10
* Each command consists of G, L, and R only.

# Sample Case 0

## Sample Input 0

```
2
G
L
```

## Sample Output 0

```
NO
YES
```

## Explanation 0

There are `n=2` commands.

1. For `commands[0] = "G"`, the robot will move forward forever (G --> G --> G --> ...) without ever turning or being
   restricted to a circle. Set index 0 of the return array to 'NO'.
2. For `commands[1] == "L"`, the robot will just turn 90 degrees left forever without moving forward (because there is
   no 'G' instruction). The robot is effectively trapped at one spot, thus bound within a circle. Set index 1 of the
   return array to 'YES'.

# Sample Case 1

## Sample Input 1

```
1
GRGL
```

## Sample Output 1

```
NO
```

## Explanation 1

Consider the robot's initial orientation to be facing northward toward the positive `y` direction. The robot performs
the following four steps in a loop:

1. Go forward one step. The robot moves from (0, 0) to (0, 1).
2. Turn right. The robot turns eastward, facing the positive `x` direction.
3. Go forward one step. The robot moves from (0, 1) to (1, 1).
4. Turn left. The robot turns northward, facing the positive `y` direction again.

```
                  ^
                  |
         RG  ->  LG
         ^
         |
RG  ->  LG
^
|
G
```

The robot then repeats these steps indefinitely, following an endless zig-zag path in the northeasterly direction.
Because the robot will never turn in such a way that it would be restricted to a circle, set index 0 of the return array
to NO.