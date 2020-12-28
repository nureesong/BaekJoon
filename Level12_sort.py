# Step 1: No.2750
N = int(input())
num = []
for i in range(N):
    num.append(int(input()))
num.sort()
for i in num:
    print(i)


# Step 6: No.11650
N = int(input())
pts = []
for i in range(N):
    xi,yi = map(int,input().split())
    pts.append([xi,yi])
for i in sorted(pts):
    print(i[0],i[1])
