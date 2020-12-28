# Step 1: No.10952
A,B = map(int,input().split())
while A!=0 and B!=0:
    print(A+B)
    A,B = map(int,input().split())
    

# Step 3: No.1110
N = int(input())
cycle = 0
New = N
while cycle == 0 or New != N:
    # N = 10a+b
    a = New // 10
    b = New % 10
    New = b*10 + (a+b)%10
    cycle = cycle +1
    
print(cycle)