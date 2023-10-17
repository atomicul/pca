time_until_party = 4*60
problems, time_to_drive = map(int, input().split())
time_until_party -= time_to_drive

for i in range(1, problems+1):
    if time_until_party >= i*5:
        time_until_party -= i*5
    else:
        print(i-1)
        exit()

print(problems)
