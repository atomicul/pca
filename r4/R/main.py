input()
brackets = filter(lambda x: x[1] in '({[]})', enumerate(input()))

map_parentheses = {')': '(', '}': '{', ']': '['}
stk = []
for i, br in brackets:
    if br in '({[':
        stk.append(br)
    else:
        corresponding_br = map_parentheses[br]
        if not stk or stk[-1] != corresponding_br:
            print(br, i)
            exit()
        stk.pop()

print('ok so far')


