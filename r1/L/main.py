k = int(input().split()[1])-1
ids = list(map(int, input().split()))

if k in [0, 1]:
    print(ids[0])
    exit()

def gauss(n: int):
    return n*(n+1)//2

def getRobotNo(max: int, k: int):
    min = 0
    while min<max:
        mid = (min+max)//2
        if gauss(mid+1) <= k:
            min=mid+1
        else:
            max=mid
    return min;

print(ids[k-gauss(getRobotNo(len(ids)-1, k))])
