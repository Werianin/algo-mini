def kosaraju_find_scc(graph):
    visited = set()
    order = []
    
    def dfs(u):
        stack = [(u, False)]
        while stack:
            node, done = stack.pop()
            if done:
                order.append(node)
                continue
            if node in visited:
                continue
            visited.add(node)
            stack.append((node, True))
            for neighbor in graph.get(node, []):
                if neighbor not in visited:
                    stack.append((neighbor, False))
    
    for func in graph:
        if func not in visited:
            dfs(func)
    
    rev_graph = {}
    for u in graph:
        for v in graph[u]:
            if v not in rev_graph:
                rev_graph[v] = []
            rev_graph[v].append(u)
    
    visited = set()
    sccs = []
    
    for func in order[::-1]:
        if func not in visited:
            stack = [func]
            visited.add(func)
            component = []
            while stack:
                node = stack.pop()
                component.append(node)
                for neighbor in rev_graph.get(node, []):
                    if neighbor not in visited:
                        visited.add(neighbor)
                        stack.append(neighbor)
            sccs.append(component)
    
    return sccs

def find_recursion(graph, sccs):
    rec_funcs = set()
    for scc in sccs:
        if len(scc) > 1 or (len(scc) == 1 and scc[0] in graph and scc[0] in graph.get(scc[0], [])):
            rec_funcs.update(scc)
    return rec_funcs

def solution(input_graph):
    sccs = kosaraju_find_scc(input_graph)
    largest_scc = max(sccs, key=len) if sccs else []
    rec_funcs = find_recursion(input_graph, sccs)
    
    print("largest recursive component:", largest_scc)
    print()
    print("recursive functions:", rec_funcs)

graph = {
    'foo': ['bar', 'baz', 'qux'],
    'bar': ['baz', 'foo', 'bar'],
    'qux': ['qux'],
    'baz': [],
}

solution(graph)
'''
largest recursive component: ['foo', 'bar']

recursive functions: {'foo', 'bar', 'qux'}
'''
