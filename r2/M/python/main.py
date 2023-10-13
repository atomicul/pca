import bisect
t = int(input())
for i in range(t):
    _, unlucky = map(int, input().split())
    scnd = lambda x: x[1]
    arr = sorted(enumerate(map(int, input().split())), key=scnd)
    workaround = [x[1] for x in arr]

    def eq_range(a, x, lo=0, hi=None):
        if hi is None:
            hi = len(a)
        return (bisect.bisect_left(a, x, lo, hi), bisect.bisect_right(a, x, lo, hi))

    out = [0 for _ in range(len(arr))]
    for idx, (original_idx, el) in enumerate(arr):
        x = unlucky - el
        if x < el:
            break
        if x==el:
            lo, hi = eq_range(workaround, x, idx)
            mid = (lo+hi)//2
            for j in range(mid, hi):
                out[arr[j][0]] = 1
            break
        lo, hi = eq_range(workaround, x, idx)
        for j in range(lo, hi):
            out[arr[j][0]] = 1

    print(' '.join(map(str, out)))
