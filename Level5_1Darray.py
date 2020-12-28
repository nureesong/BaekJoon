# Step 1: No.10818
N = int(input())
a = list(map(int,input().split()))
print(min(a),max(a))


# Step 2: No.2562
a = []
for i in range(9): 
    a.append(int(input()))
print(max(a))
print(a.index(max(a))+1)


# Step 3: No.2577
A = int(input())
B = int(input())
C = int(input())
N = str(A*B*C)
k = len(N)  # digit of N

for i in range(10):
    count = 0
    for j in range(k):
        if i == int(N[j]):
            count = count + 1
    print(count)


# Step 4: No.3052
r = []
for i in range(10):
    N = int(input())
    if not(N%42 in r):
        r.append(N%42)        
print(len(r))


# Step 5: No.1546
N = int(input())
a = list(map(int,input().split()))
M = max(a)
for i in range(N):
    a[i] = a[i]/M*100
print(sum(a)/N)


# Step 6: No.8958
N = int(input())
for i in range(N):
    quiz = input()
    n = len(quiz)
    score = [0]*n  # score array
    curscore = 0   # current score
    for j in range(n):
        if quiz[0] == 'O':
            curscore = curscore + 1
        else: 
            curscore = 0
        score[j] = curscore
        quiz = quiz[1:]
    print(sum(score))
    
    
# Step 7L No.4344
C = int(input())
for i in range(C):
    test = list(map(int,input().split()))
    N = test[0]  # number of students
    avg = sum(test[1:])/N
    count = 0
    for j in range(1,N+1):
        if test[j] > avg:
            count = count + 1
    prop = count/N*100
    print('%.3f%%' % prop)
    



    