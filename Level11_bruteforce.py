# Step 1: No.2798
N,M = map(int,input().split())
card = list(map(int,input().split()))
card.sort()
s = []
for i in range(N-2):
    for j in range(i+1,N-1):
        for k in range(j+1,N):
            sum3 = card[i]+card[j]+card[k]
            if sum3 <= M:
                s.append(sum3)
s.sort()
if M in s:
    print(M)
else:
    print(s[-1])