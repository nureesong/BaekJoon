# Step 1: No.1260
N,M,V = map(int,input().split())

A = [[0 for _ in range(N+1)] for _ in range(N+1)]
for i in range(M):
    a,b = map(int,input().split())
    A[a][b],A[b][a] = 1,1
    # A[b][a] = 1


def dfs(start,visited):
    visited.append(start)
    for i in range(1,len(A[start])):
        if A[start][i] == 1 and (i not in visited):
            dfs(i,visited)
    return visited
print(' '.join(map(str,dfs(V,[]))))


def bfs(start):
    visited = [start]
    queue = [start]
    while queue:
        n = queue.pop(0)
        for i in range(1,len(A[start])):
            if A[n][i] == 1 and (i not in visited):
                visited.append(i)
                queue.append(i)        
    return visited
print(' '.join(map(str,bfs(V))))