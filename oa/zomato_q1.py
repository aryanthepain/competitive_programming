from collections import deque


def check_query(query, n, parent, child_count):
    # first should always be 1
    if query[0] != 1:
        return '0'
    
    seen = [False]*(n+1)
    remaining = child_count.copy()
    
    q = deque()
    q.append(1)
    seen[1] = True
    
    for x in query[1:]:
        if seen[x]:
            return '0'
        
        p = parent[x]
        
        while((q) and (q[0] != p) and remaining[q[0]] == 0):
            q.popleft()
            
        if not q:
            return '0'
        
        if q[0] != p:
            return '0'
        
        remaining[p]-=1
        
        seen[x] = True
        q.append(x)
    
    return '1'
        


def check_log_tables(process_nodes, process_from, process_to, q, queries):
    # Build undirected tree
    adj = [[] for _ in range(process_nodes + 1)]

    for u, v in zip(process_from, process_to):
        adj[u].append(v)
        adj[v].append(u)

    # Root the tree at node 1
    parent = [0] * (process_nodes + 1)
    child_count = [0] * (process_nodes + 1)

    # Write your code here
    # Find parent[] and child_count[]
    traverse = deque()
    traverse.append(1)
    
    while(traverse):
        curr = traverse.popleft()
        
        for neighbour in adj[curr]:
            if neighbour != parent[curr]:
                parent[neighbour] = curr
                child_count[curr]+=1
                traverse.append(neighbour)

    ans = []

    for query in queries:
        ans.append(check_query(
            query,
            process_nodes,
            parent,
            child_count
        ))

    return "".join(ans)


# --------------------------------------------------
# MAIN
# --------------------------------------------------

process_nodes, edges = map(int, input().split())

process_from = []
process_to = []

for _ in range(edges):
    u, v = map(int, input().split())
    process_from.append(u)
    process_to.append(v)

q = int(input())

# These two values are part of the OA custom-input format.
rows = int(input())
cols = int(input())

queries = []

for _ in range(rows):
    queries.append(list(map(int, input().split())))

print(
    check_log_tables(
        process_nodes,
        process_from,
        process_to,
        q,
        queries
    )
)