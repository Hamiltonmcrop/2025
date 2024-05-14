def duplicate_node_0(digraphs):
    result = []
    
    for adj_list in digraphs:
        n = len(adj_list)  # Order of the original digraph
        new_adj_list = [neighbors[:] for neighbors in adj_list]
        
        # Duplicate node 0 to node n
        new_adj_list.append(new_adj_list[0][:])
        
        # Add node n to all the nodes that point to node 0
        added_arcs = 0
        for i in range(n):
            if 0 in new_adj_list[i]:
                new_adj_list[i].append(n)
                added_arcs += 1
        
        # Output the modified graph
        result.append(f"{n + 1}")
        for neighbors in new_adj_list:
            if neighbors:
                result.append(" ".join(map(str, neighbors)))
            else:
                result.append("")
        result.append(str(added_arcs))
    
    return result

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

output = duplicate_node_0(input_graphs)
for line in output:
    print(line)

