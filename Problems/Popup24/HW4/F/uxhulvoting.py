def solve_test_case(test_case):
    num_priests = len(test_case)
    outcomes = [
        [False, False, False],  # 0: 1, 2, 4
        [False, False, True],  # 1: 0, 3, 5
        [False, True, False],  # 2: 0, 3, 6
        [False, True, True],  # 3: 1, 2, 7
        [True, False, False],  # 4: 0, 5, 6
        [True, False, True],  # 5: 1, 4, 7
        [True, True, False],  # 6: 2, 4, 7
        [True, True, True],  # 7: 3, 5, 6
    ]

    matrix = [[j for j in range(8)] for i in range(num_priests)]
    for j in range(8):
        best_priority = 9
        index_state = -1
        for k in range(3):
            current_state = [elem for elem in outcomes[j]]
            current_state[k] = not current_state[k]
            priority = test_case[num_priests - 1][outcomes.index(current_state)]
            if priority < best_priority:
                best_priority = priority
                index_state = outcomes.index(current_state)

        matrix[num_priests - 1][j] = index_state

    for i in range(num_priests - 2, -1, -1):
        for j in range(8):
            best_priority = 9
            index_state = -1
            for k in range(3):
                current_state = [elem for elem in outcomes[j]]
                current_state[k] = not current_state[k]
                priority = test_case[i][matrix[i + 1][outcomes.index(current_state)]]
                if priority < best_priority:
                    best_priority = priority
                    index_state = outcomes.index(current_state)

            matrix[i][j] = matrix[i + 1][index_state]

    return outcomes[matrix[0][0]]


if __name__ == "__main__":
    num_test_cases = int(input())
    test_cases = [[] for i in range(num_test_cases)]

    for i in range(num_test_cases):
        num_priests = int(input())
        test_cases[i] = [[] for j in range(num_priests)]
        for j in range(num_priests):
            test_cases[i][j] = [int(elem) for elem in input().split()]

    for i in range(num_test_cases):
        solution = solve_test_case(test_cases[i])
        for elem in solution:
            print("Y" if elem else "N", end="")
        print()
