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

def topological_sort(a):
    def dfs(a, node, visited=None):
        if visited is None:
            visited = set()

        if node in visited:
            raise Exception("Cycle detected")
        visited.add(node)

        for n in a[node]:
            for i in dfs(a, n, visited):
                yield i;
        yield node
    
    out = []
    visited = set();
    for ch in lowercase_letters():
        if ch in visited:
            continue
        for i in dfs(a, ch, visited):
            out.append(i)

    out.reverse()
    return out

try:
    print("".join(topological_sort(lower_chars)))
except:
    print("Impossible")
