def cell_competition(states: list, days: int) -> list:
    new_states = []
    for day in range(0, days):
        for cell_index, cell_value in enumerate(states):
            # If you're at the beginning, treat it as though the cell that would be on your left was inactive
            if cell_index == 0:
                new_state_of_cell = determine_state_of_current_cell(0, cell_value, states[cell_index + 1])

            # Similarly, if you're at the last element, treat it as though the element that would be on your right is
            # inactive
            elif cell_index == (len(states) - 1):
                new_state_of_cell = determine_state_of_current_cell(states[cell_index - 1], cell_value, 0)

            else:
                new_state_of_cell = determine_state_of_current_cell(states[cell_index - 1], cell_value,
                                                                    states[cell_index + 1])

            new_states.append(int(new_state_of_cell))

        # update the array after each day's calculations are done
        states = new_states

        # "zero out" the new states variable
        new_states = []

    return states


def determine_state_of_current_cell(left_cell: int, current_cell: int, right_cell: int) -> int:
    return 0 if (left_cell == right_cell) else 1
