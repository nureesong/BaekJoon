# Example
def solution(v):
    x = []    
    y = []
    for i in range(len(v)):
        x.append(v[i][0])    
        y.append(v[i][1])
    if x.count(min(x))==2:
        a = max(x)
    else:
        a = min(x)

    if y.count(min(y))==2:
        b = max(y)
    else:
        b = min(y)
    answer = [a,b]
    return answer

v = [[1,4],[3,4],[3,10]]
print(solution(v))
v = [[1,1],[2,2],[1,2]]
print(solution(v))