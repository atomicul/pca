_, orange_size, collector_size = map(int, input().split())
appropirate_sized_oranges = [x for x in map(int, input().split()) if x <= orange_size ]

waste_size = 0
cnt = 0
for orange in appropirate_sized_oranges:
    waste_size += orange
    if waste_size > collector_size:
        waste_size = 0
        cnt += 1

print(cnt)
