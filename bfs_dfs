import sys
from collections import deque


def dfs(v, data, visited):
    print(v, end=" ")
    visited[v] = True

    for i in data[v]:
        if visited[i] is False:
            dfs(i, data, visited)


def bfs(v, data):
    visited = [False for _ in range(n + 1)]
    queue = deque([v])
    visited[v] = True

    while queue:
        v = queue.popleft()
        print(v, end=" ")

        for i in data[v]:
            if visited[i] is False:
                queue.append(i)
                visited[i] = True


if __name__ == "__main__":
    n, m, v = map(int, sys.stdin.readline().rstrip().split())
    data = [[] for _ in range(n+1)]
    visited = [False for _ in range(n+1)]

    for i in range(m):
        start, end = map(int, sys.stdin.readline().rstrip().split())
        data[start].append(end)
        data[end].append(start)

    for j in range(n+1):
        data[j].sort()

    dfs(v, data, visited)
    print()
    bfs(v, data)
