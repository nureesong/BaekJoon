# N = 7
# table = [0,3,1,1,5,5,4,6]

# DFS를 안 쓰고 푼 거 같은데....??

import sys
N = int(sys.stdin.readline())
table = [0]
[table.append(int(sys.stdin.readline())) for _ in range(N)]
result = [0]*(N+1)

def dfs(start):
    num = [start]
    while (table[start] not in num) and (result[start]==0):
        num.append(table[start])
        start = table[start]
    # print(num)
    if num[0]==table[start]: 
        for k in num: result[k] = 1
    return


for i in range(1,N+1):
    if result[i]==0:
        dfs(i)

print('==================')
print(sum(result))
for k in range(1,N+1):
    if result[k]: print(k)
