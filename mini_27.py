from collections import defaultdict

def sortItems(n: int, m: int, group: List[int], beforeItems: List[List[int]]) -> List[int]:
    for i in range(n):
        if group[i] == -1:
            group[i] = m
            m += 1

    item_graph = defaultdict(list)
    group_graph = defaultdict(list)
    glocal_indegroup_to_items = defaultdict(list)

    for i in range(n):
        group_to_items[group[i]].append(i)

    for cur in range(n):
        for prev in beforeItems[cur]:
            item_graph[prev].append(cur)
            if group[prev] != group[cur]:
                group_graph[group[prev]].append(group[cur])

    def top_sort(graph, nodes):
        visited = {}
        order = []

        def dfs(node):
            if node in visited:
                return visited[node]  # True = cycle
            visited[node] = True
            for nei in graph[node]:
                if dfs(nei):
                    return True
            visited[node] = False
            order.append(node)
            return False

        for node in nodes:
            if node not in visited:
                if dfs(node):
                    return None
        return order[::-1]

    group_order = top_sort(group_graph, list(range(m)))
    if group_order is None:
        return []

    result = []
    for g in group_order:
        items = group_to_items[g]
        if not items:
            continue
        item_subgraph = defaultdict(list)
        for item in items:
            for nei in item_graph[item]:
                if nei in items:
                    item_subgraph[item].append(nei)
        item_order = top_sort(item_subgraph, items)
        if item_order is None:
            return []
        result.extend(item_order)

    return result
