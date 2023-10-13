t=int(input())
for _ in range(t):
    n = int(input())
    letter_map = ({}, {})
    words_map = {}

    s = 0
    for _ in range(n):
        str = input()
        a = letter_map[0][str[0]] if str[0] in letter_map[0] else 0
        b = letter_map[1][str[1]] if str[1] in letter_map[1] else 0
        c = words_map[str] if str in words_map else 0
        s += a + b - 2*c
        letter_map[0][str[0]] = a + 1
        letter_map[1][str[1]] = b + 1
        words_map[str] = c + 1

    print(s)
