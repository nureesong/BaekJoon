# Step 1: No.2748
N = int(input())

fibo = [0,1] + [0]*90
for i in range(2,N+1):
    fibo[i] = fibo[i-1] + fibo[i-2]
print(fibo[N])
    