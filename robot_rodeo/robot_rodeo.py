# Complete the 'doesCircleExist' function below.


def doesCircleExist(commands):
    # Write your code here.
    results = []
    for cmd in commands:
        # handle the trivial case where there is only one command given to the robot.
        if len(cmd) == 1:
            if cmd == 'G':
                results.append("NO")
            else:
                results.append("YES")

        else:
            # Build a Cartesian coordinate model. The L instruction shifts the robot left along the x-axis,
            # the R instruction shifts the robot right along the x-axis, and the G instruction moves the robot
            # up the y-axis.
            current_loc = [0, 0]
            for instruction in cmd:
                if instruction == 'G':
                    current_loc[1] += 1
                elif instruction == 'L':
                    current_loc[0] -= 1
                else:  # instruction == 'R'
                    current_loc[0] += 1

            if current_loc == [0, 0]:
                results.append("YES")
            else:
                results.append("NO")

    return results
