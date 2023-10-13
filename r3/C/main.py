from itertools import chain
t=int(input())
for _ in range(t):
    grid=[]
    for _ in range(3):
        grid.append([1 if x=='X' else 2 if x=='O' else 0 for x in input()])
    input()
    
    def linearIteratorMatrix(a):
        iterable = []
        for row in a:
            iterable = chain(iterable, row)
        return iterable

    xs = len([x for x in linearIteratorMatrix(grid) if x==1])
    os = len([x for x in linearIteratorMatrix(grid) if x==2])

    if os > xs:
        print('no')
    elif xs-os > 1:
        print('no')
    else:
        print('yes')
