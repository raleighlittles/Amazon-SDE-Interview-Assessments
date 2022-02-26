# Complete the 'doesCircleExist' function below.

def doesCircleExist(commands):
    # Write your code here.
    results = []
    for cmd_sequence in commands:
        circle_found = False
        # handle the trivial case where there is only one command given to the robot.
        if len(cmd_sequence) == 1:
            if cmd_sequence == 'G':
                # Going 'forward' (whatever direction that may be) an infinite number of times
                # will always produce a line
                results.append("NO")

            elif cmd_sequence == "L" or cmd_sequence == "R":
                # Turning in only one direction an infinite number of times will produce a circle
                results.append("YES")

        else:
            # Describe robot's motion using current angle (changed by 'L' and 'R')
            # and position, changed by G only.
            # Direction values are 0 (North), 1 (East), 2 (South), 3 (West)
            # Direction starts off as up
            direction = 0
            # Cartesian coordinates representing the current position
            pos_x, pos_y = 0, 0
            for command in cmd_sequence:
                if (command == 'G'):
                    pos_x, pos_y = increment_coords(pos_x, pos_y, direction)

                # Directions were defined clockwise, so turning right goes 'up' by 1, and turning left does 'down' by 1
                # '4' is because there's 4 cardinal directions
                elif (command == 'R'):
                    direction = (direction + 1) % 4

                elif (command == 'L'):
                    direction = (direction - 1) % 4

                # While moving, check if you find yourself at where you started (the origin)
                if (pos_x == 0) and (pos_y) == 0:
                    circle_found = True

            if circle_found:
                results.append("YES")
                
            else:
                results.append("NO")

    return results



# Returns a pair of coordinates representing the new position of the robot
# after it moves in the given direction by one unit
def increment_coords(coord_x, coord_y, direction):
    pos_x, pos_y = coord_x, coord_y
    if direction == 0:
        pos_y += 1

    elif direction == 1:
        pos_x += 1

    elif direction == 2:
        pos_y -= 1

    elif direction == 3:
        pos_x -= 1

    return pos_x, pos_y

