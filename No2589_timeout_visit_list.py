
r,c = map(int, '5 7'.split())
treasure_map = ['W'*(c+2)]
treasure_map.append('W'+'WLLWWWL'+'W')
treasure_map.append('W'+'LLLWLLL'+'W')
treasure_map.append('W'+'LWLWLWW'+'W')
treasure_map.append('W'+'LWLWLLL'+'W')
treasure_map.append('W'+'WLLWLWW'+'W')
treasure_map.append('W'*(c+2))



def bfs(start):
    visited = [start]
    queue = [start]
    count = [1]
    point = 0
    while queue:
        i,j = queue[0]
        for x,y in [(i-1,j),(i+1,j),(i,j-1),(i,j+1)]: # up, down, left, right
            if treasure_map[x][y] == 'L' and ((x,y) not in visited):
                count.append(count[point] + abs(i-x) + abs(j-y))  # L1-norm
                queue.append((x,y))
                visited.append((x,y))
        queue.pop(0)
        point += 1
    return max(count)-min(count)


max_dist = 0
for i in range(1,r+1):
    for j in range(1,c+1):
        if treasure_map[i][j]=='L':
            dist = bfs((i,j))
            if dist > max_dist: max_dist = dist
print(max_dist)
    