children = int(input().split()[0])
throws = []
commands = iter(input().split())
while True:
    word = next(commands, None)
    if word is None:
        break
    if word == 'undo':
        amount = int(next(commands))
        throws = throws[:-amount]
    else:
        throws.append(int(word))

print((sum(throws) % children + children) % children)
