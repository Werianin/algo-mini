def isBip(graph):
    visited = [0] * len(graph)
    def procedure(node, color) -> bool:
        visited[node] = color
        for ind in graph[node]:
            if visited[ind] == color:
                return 0
            if visited[ind] == 0:
                procedure(ind, -color)
        return 1
    return procedure(0, 1)

l = [[1,2,3],[0,2],[0,1,3],[0,2]]
l = [[1,3],[0,2],[1,3],[0,2]]
print(isBip(l))
