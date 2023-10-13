from math import ceil
def colorRectangle(n,m):
  if n<m:
    return colorRectangle(m,n)
  if m==0:
    return 0
  if m==1:
    return ceil(n/3)
  if n==2:
    return colorRectangle(m, 1)*2
  optimal_rectangles = n // 3
  return optimal_rectangles*m+colorRectangle(m, n-optimal_rectangles*3)

t=int(input())
for _ in range(t):
  a,b=map(int, input().split())
  print(colorRectangle(a,b))
