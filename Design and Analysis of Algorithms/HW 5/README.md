# Minimum Cost Spanning Tree (MCST) Algorithms

## Project Overview
This program demonstrates the implementation of three algorithms for constructing a **Minimum Cost Spanning Tree** (MCST) for a weighted undirected graph:
1. **Prim's Algorithm**
2. **Kruskal's Algorithm**
3. **Greedy Algorithm**

---

## Problems and Solutions

### Problem 1: Prim's Algorithm
#### Problem Description
- **Prim's Algorithm** constructs the MCST by growing it one edge at a time, starting from an arbitrary vertex.
- At each step, the algorithm adds the smallest edge that connects a node in the current tree to a node outside it.

#### Approach
1. Start from an arbitrary node (node 0).
2. Use two arrays:
   - `nearest[]`: Tracks the nearest node in the current MCST for each node.
   - `distance[]`: Tracks the minimum distance from each node to the current MCST.
3. Add the edge with the smallest weight to the MCST and update the arrays.

#### Code:
```
private static EdgeSet prim(int numNodes, int[][] weights) {
    EdgeSet mcstEdges = new EdgeSet();
    int min, vnear = 0;
    int[] nearest = new int[numNodes];
    int[] distance = new int[numNodes];

    for (int i = 1; i < numNodes; i++) {
        nearest[i] = 0;
        distance[i] = weights[0][i];
    }

    for (int i = 0; i < numNodes - 1; i++) {
        min = INF;
        for (int j = 1; j < numNodes; j++) {
            if (distance[j] >= 0 && distance[j] < min) {
                min = distance[j];
                vnear = j;
            }
        }
        mcstEdges.addEdge(vnear, nearest[vnear], distance[vnear]);
        distance[vnear] = -1;
        for (int k = 1; k < numNodes; k++) {
            if (weights[k][vnear] < distance[k]) {
                distance[k] = weights[k][vnear];
                nearest[k] = vnear;
            }
        }
    }
    return mcstEdges;
}
```

---

### Problem 2: Kruskal's Algorithm
#### Problem Description
- **Kruskal's Algorithm** constructs the MCST by selecting the smallest edges one by one, ensuring no cycles are formed.

#### Approach
1. Sort all edges by weight.
2. Use a **union-find** data structure to keep track of connected components.
3. Add edges to the MCST if they do not form a cycle.

#### Code:
```
private static EdgeSet kruskal(int numNodes, int numEdges, EdgeSet edges) {
    EdgeSet mcst = new EdgeSet();
    edges.sort();
    int[] subsets = initial(numNodes);

    for (Edge edge : edges) {
        int subset1 = find(subsets, edge.getNode1());
        int subset2 = find(subsets, edge.getNode2());

        if (subset1 != subset2) {
            mcst.addEdge(edge.getNode1(), edge.getNode2(), edge.getWeight());
            merge(subsets, subset1, subset2);
        }
        if (mcst.size() == numNodes - 1) break;
    }
    return mcst;
}
```

---

### Problem 3: Greedy Algorithm
#### Problem Description
- The **Greedy Algorithm** builds the MCST by iteratively selecting the smallest edge connected to the current node.

#### Approach
1. Start at an arbitrary node.
2. Repeatedly select the smallest edge connected to the current tree, ensuring no cycles are formed.

#### Code:
```
private static EdgeSet greedy(int numNodes, int[][] weights) {
    EdgeSet mcst = new EdgeSet();
    boolean[] visited = new boolean[numNodes];
    int sourceNode = 0, nextNode = 0, minEdge;

    while (mcst.size() < numNodes - 1) {
        minEdge = INF;
        for (int i = 0; i < numNodes; i++) {
            if (!visited[i] && weights[sourceNode][i] < minEdge) {
                minEdge = weights[sourceNode][i];
                nextNode = i;
            }
        }
        visited[nextNode] = true;
        weights[sourceNode][nextNode] = INF;
        weights[nextNode][sourceNode] = INF;
        mcst.addEdge(sourceNode, nextNode, minEdge);
        sourceNode = nextNode;
    }
    return mcst;
}
```

