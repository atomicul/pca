#!/bin/env python3

def main():
    problems_map: dict[str, Problem] = {}
    solved_problems = 0 
    time_to_solve = 0

    while True:
        line = input()
        if line == "-1":
            break

        time, problem, result = line.split()
        time = int(time)

        if problem not in problems_map:
            problems_map[problem] = Problem()

        problems_map[problem].attempt(time, result == "right")
    
    solved_problems = sum(p.solved for p in problems_map.values())
    time_to_solve = sum(p.penalty for p in problems_map.values())

    print(solved_problems, time_to_solve)


class Problem():
    _FAILED_PENALTY = 20
    _solve_time: int
    _attemts: int

    def __init__(self):
        self._solve_time = -1
        self._attemts = 0

    def attempt(self, time:int, success: bool) -> None:
        if self.solved:
            return
        if success:
            self._solve_time = time
        else:
            self._attemts += 1

    @property
    def solved(self) -> bool:
        return self._solve_time != -1

    @property
    def penalty(self) -> int:
        if not self.solved:
            return 0
        return self._solve_time + self._attemts * self._FAILED_PENALTY


if __name__ == "__main__":
    main()
