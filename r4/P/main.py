from typing import Iterable
def chars_iterator() -> Iterable[str]:
    for i in range(26):
        yield chr(ord('a') + i)

def removes_required(s: str, c: str) -> int:
    le=0
    r=len(s)-1
    ans = 0
    while le<r:
        if s[le] == s[r]:
            le+=1
            r-=1
            continue
        if s[le] == c:
            le+=1
            ans+=1
            continue
        if s[r] == c:
            r-=1
            ans+=1
            continue
        return 2**30
    return ans


t = int(input())
for _ in range(t):
    input()
    s = input()
    ans = min(removes_required(s, ch) for ch in chars_iterator())
    print(ans if ans != 2**30 else -1)
