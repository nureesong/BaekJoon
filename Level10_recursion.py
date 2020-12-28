# Step 1: No.10872
def factorial(n):
    if n > 0:
        num = factorial(n-1)*n
    else:
        num = 1
    return num
N = int(input())
print(factorial(N))


# Step 2: No.10870
def Fibonacci(n):
    if n >= 2:
        ans = Fibonacci(n-1) + Fibonacci(n-2)
    elif n == 1:
        ans = 1
    else:
        ans = 0
    return ans
N = int(input())
print(Fibonacci(N))


# Step 3: No.2447
def printstar(n):
    global P
    if n == 3:
        P[0][:3] = P[2][:3] = [1]*3
        P[1][:3] = [1,0,1]
        return
     
    printstar(n//3)
    for i in range(3):
        for j in range(3):
            if i==1 and j==1:
                continue
            for k in range(n//3):
                P[(n//3)*i+k][(n//3)*j:(n//3)*(j+1)] = P[k][:n//3]

N = int(input())  # N=3^k (k=1~8)
P = [[0 for i in range(N)] for i in range(N)]
printstar(N)
for i in P:
    for j in i:
        if j:
            print('*',end='')
        else:
            print(' ',end='')
    print()


# Step 4: No.11729
def hanoi(n,a,c,b):
    if n == 1:
        path.append([a,c])
    else:
        hanoi(n-1,a,b,c)
        hanoi(1,a,c,b)
        hanoi(n-1,b,c,a)

N = int(input())
path = []
hanoi(N,1,3,2)

print(len(path))
for i in path:
    print(i[0],i[1])
    
    