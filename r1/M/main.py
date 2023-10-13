_ = input()
array = sorted(list(map(int, input().split())))

def quit():
    print("Impossible")
    exit()

for i in range(1, len(array)):
    if i%2:
        el, pos = max(map(lambda x: x[::-1], enumerate(array[i:], i)))
        if el < array[i-1]:
            quit()
    else:
        el, pos = min(map(lambda x: x[::-1], enumerate(array[i:], i)))
        if el > array[i-1]:
            quit()

    array[i], array[pos] = array[pos], array[i]


print(' '.join(map(str, array)))
