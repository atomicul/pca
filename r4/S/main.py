t=int(input())
for _ in range(t):
    s = input()
    cnt=0
    b_count = 0
    for ch in s:
        if ch == 'A':
            cnt+=1
        if ch == 'B':
            if cnt:
                cnt -= 1
            else:
                b_count += 1
    print(cnt + b_count % 2)
