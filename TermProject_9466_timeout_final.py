# n = 7
# table = [0,3,1,3,7,3,4,6]
# n = 8
# table = [0,1,2,3,4,5,6,7,8]

import sys
T = int(sys.stdin.readline())
answer = []
for _ in range(T):
    n = int(sys.stdin.readline())
    table = [0] + list(map(int,sys.stdin.readline().split()))
    result = [0]*(n+1)

    for i in range(1,n+1):
        if result[i]==0:
            team = [i]
            start,point = i,table[i]
            while (point not in team) and result[start]==0:
                team.append(point)
                start = point
                point = table[start]
            if i==point: 
                for k in team: result[k] = 1
    
    answer.append(n-sum(result))
for t in range(T): print(answer[t])
