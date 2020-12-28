# Step 1: No.11654
s = input()
print(ord(s))


# Step 2: No.11720
N = int(input())
numbers = list(input())
sum = 0
for i in numbers:
    sum = sum + int(i)
print(sum)


# Step 3: No.10809
S = input()
pos = []
for i in range(ord('a'),ord('z')+1):
    pos.append(S.find(chr(i)))

for i in range(len(pos)):
    print(pos[i],end=' ')
    

# Step 4: No.2675
T = int(input())
for t in range(T):
    R,S = input().split()
    R = int(R)
    P = ''
    for s in S:
        P = P + s*R
    print(P)
    
    
# Step 5: No.1157
S = input().lower()
S_uniq = list(set(S))
c = []
for s in S_uniq:
    c.append(S.count(s))

num = 0
for i in c:
    if i == max(c):
        num += 1
if num > 1:
    print('?')
else:
    print( S_uniq[c.index(max(c))].upper())
    

# Step 6: No.1152
S = input().split()
print(len(S))


# Step 7: No.2908
A,B = input().split()
A = int(A[::-1])
B = int(B[::-1])
if A > B:
    print(A)
else:
    print(B)

