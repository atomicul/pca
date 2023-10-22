commands = int(input())
dir = []
for _ in range(commands):
    command = input()
    if(command == 'pwd'):
        print('/' + '/'.join(dir) + ('/' if len(dir) else ''))
    else:
        command, arg = command.split()
        if arg[0] == '/':
            dir = []
            arg = arg[1:]
        for d in arg.split('/'):
            if(d == '..'):
                if dir:
                    dir.pop()
            elif d != '.':
                dir.append(d)

