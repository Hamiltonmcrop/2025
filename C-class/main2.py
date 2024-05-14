##Question 2

def dfs_classify_arcs(adj_list):
    n = len(adj_list)
    visited = [False] * n
    entry = [-1] * n
    exit = [-1] * n
    time = 0
    tree_arcs = 0
    cross_arcs = 0

    def dfs(node):
        nonlocal time, tree_arcs, cross_arcs
        visited[node] = True
        entry[node] = time
        time += 1
        
        for neighbor in adj_list[node]:
            if not visited[neighbor]:
                tree_arcs += 1
                dfs(neighbor)
            elif entry[neighbor] > entry[node]:  # This is a back edge
                cross_arcs += 1
        
        exit[node] = time
        time += 1

    dfs(0)
    
    return tree_arcs, cross_arcs

# Example usage
input_graphs = [
    [
        [1, 3],  # Adjacency list for node 0
        [2, 3],  # Adjacency list for node 1
        [0, 4],  # Adjacency list for node 2
        [1],     # Adjacency list for node 3
        [3]      # Adjacency list for node 4
    ],
    [
        [1, 2],  # Adjacency list for node 0
        [1],     # Adjacency list for node 1
        [1, 2]   # Adjacency list for node 2
    ]
]

for adj_list in input_graphs:
    tree, cross = dfs_classify_arcs(adj_list)
    print(f"{tree} {cross}")

