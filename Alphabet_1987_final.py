from collections import deque
import sys

r,c = map(int, sys.stdin.readline().split())
board = [sys.stdin.readline() for _ in range(r)]

# right, up, left, down
dx = (0,-1,0,1)  
dy = (1,0,-1,0)

visit = deque()
alphabet = deque()
count, max_dist = 0,0

def dfs(i,j):
    global count, max_dist
    count += 1
    max_dist = max(max_dist,count)
    visit.append((i,j))
    alphabet.append(board[i][j])
    for k in range(4):
        x,y = i+dx[k],j+dy[k]
        if 0<=x<r and 0<=y<c and (board[x][y] not in alphabet):
            dfs(x,y)
    visit.pop()
    alphabet.pop()
    count -= 1
    if not(visit): return
    
dfs(0,0)
print(max_dist)