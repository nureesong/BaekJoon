
r,c = map(int, '5 7'.split())
treasure_map = ['W'*(c+2)]
treasure_map.append('W'+'WLLWWWL'+'W')
treasure_map.append('W'+'LLLWLLL'+'W')
treasure_map.append('W'+'LWLWLWW'+'W')
treasure_map.append('W'+'LWLWLLL'+'W')
treasure_map.append('W'+'WLLWLWW'+'W')
treasure_map.append('W'*(c+2))
print('\n'.join(treasure_map), sep='\n')

# r,c = map(int, input().split())
# treasure_map = ['W'*(c+2)] + ['W'+input()+'W' for _ in range(r)] + ['W'*(c+2)]


def bfs(start):
    i,j = start
    visited = [[0]*(c+2) for _ in range(r+2)]
    visited[i][j] = 1
    queue = [start]
    while queue:
        i,j = queue[0]
        for x,y in [(i-1,j),(i+1,j),(i,j-1),(i,j+1)]: # up, down, left, right
            if treasure_map[x][y] == 'L' and visited[x][y] == 0:
                visited[x][y] = visited[i][j] + abs(i-x) + abs(j-y) # L1-norm
                queue.append((x,y))
        queue.pop(0)
    return max(map(max,visited))-1, visited

max_path = []
max_dist = 0
for i in range(1,r+1):
    for j in range(1,c+1):
        if treasure_map[i][j]=='L':
            # dist = bfs((i,j)) 
            dist, path = bfs((i,j))
            if dist > max_dist: 
                max_dist = dist
                max_path = path
print('-'*40)
print(f'Travel time between the two islands: {max_dist}')
print('-'*40)
for k in range(1,r+1): print(''.join(map(str,max_path[k][1:-1])))
                    