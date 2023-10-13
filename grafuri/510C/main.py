def lowercase_letters():
    for i in range(ord('a'), ord('z')+1):
        yield chr(i)

lower_chars = {};
for ch in lowercase_letters():
    lower_chars[ch] = set()

n = int(input())
words = []
for _ in range(n):
    words.append(input())

def combinations(arr):
    for i in range(len(arr)-1):
        for j in range(i, len(arr)):
            yield (arr[i], arr[j])

for word1, word2 in combinations(words):
    a, b = next((x for x in zip(word1, word2) if x[0] != x[1]), (None, None))
    if a is None:
        if len(word1) > len(word2):
            print("Impossible")
            exit()
        else:
            continue
    lower_chars[b].add(a)

nodes_ingrade = {}
for ch in lowercase_letters():
    nodes_ingrade[ch] = 0;

for ch in lowercase_letters():
    for i in lower_chars[ch]:
        nodes_ingrade[i] += 1

sorting = []
while lower_chars:
    ch = next((x for x in lower_chars if nodes_ingrade[x] == 0), None)
    if ch is None:
        print("Impossible")
        exit()
    sorting.append(ch)
    for lch in lower_chars[ch]:
        nodes_ingrade[lch] -= 1
    del lower_chars[ch]

print(''.join(sorting[::-1]))
