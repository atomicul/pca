_, k = map(int, input().split())
str1,str2 = input(), input()

ans = ''
for i, j in zip(str1, str2):
    ans += next(c for c in 'abc' if c not in [i, j])

k = len(str1) - k
if not k:
    print(ans)
    exit()
if k < 0:
    print(-1)
    exit()

ans = list(ans)

for i in range(len(str1)):
    if k == 0:
        break
    if str1[i] != str2[i]:
        continue
    ans[i] = str1[i]
    k-=1

if not k:
    print(''.join(ans))
    exit()

f = False
for i in range(len(str1)):
    if k == 0:
        break
    if ans[i] == str1[i]:
        continue
    if f:
        ans[i] = str1[i]
        k-=1
    else:
        ans[i] = str2[i]
    f = not f

if f or k:
    print(-1)
    exit()

print(''.join(ans))
