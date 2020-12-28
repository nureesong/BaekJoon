# Step 1: No.15596
def solve(a):
    ans = sum(a)
    return ans


# Step 2: No.4673
def d(n):    
    sum = 0
    for i in str(n):
        sum = sum + int(i)
    return n + sum
    
seq = []
for n in range(1,10000):
    seq.append(d(n))
# there are numbers larger than 100 in seq

for n in range(1,10001):
    if not(n in seq):
        print(n)


# Recursive algorithm -> it takes longer time..
seq = []
for n in range(1,10000):
    if not(n in seq):
        print(n)
        while n < 10000 and d(n) < 10000:
            seq.append(d(n))
            n = d(n)


# Step 3: No.1065
def han(n):
    s = list(map(int,list(str(n))))
    if len(s) == 1:
        ans = True
    else:
        d = s[0]-s[1]  # initial difference
        num = 0
        for i in range(1,len(s)-1):
            if s[i]-s[i+1] == d:
                num = num + 1
        if num == len(s)-2:
            ans = True
        else:
            ans = False
    return ans

N = int(input())
count = 0
for n in range(1,N+1):
    if han(n):
        count = count + 1
print(count)