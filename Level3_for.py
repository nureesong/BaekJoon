# Step 1: No.2739
N = int(input())
for i in range(1,10):
    print(N,'*',i,'=',N*i)
 
    
# Step 2: No.10950
N = int(input())
for i in range(N):
    A,B = map(int,input().split())
    print(A+B)
    

# Step 9: No.2438
N = int(input())
for i in range(N):
    print('*'*(i+1))
    
# Step 10: No.2439
N = int(input())
for i in range(N):
    print(' '*(N-1-i)+'*'*(i+1))


# Step 11: No.10871
N,X = map(int,input().split())
A = input().split()
sel = []
for i in range(N):
    if int(A[i]) < X:
        sel = sel + [A[i]]
print(' '.join(sel))
    