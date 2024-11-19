# Graph Algorithms and NP Problems

## Project Overview
This program solves several graph-related problems and demonstrates concepts in computational complexity, specifically for cliques, Hamiltonian Circuits (HC), and Traveling Salesperson Problem (TSP). The program verifies solutions, transforms problems between formats, and illustrates key reductions.

---

## Problems and Solutions

### Problem 1: Clique Verification
#### Problem Description
- Determine if a given subset of vertices forms a **clique** in an undirected graph.
- A clique is a subset of vertices such that every two distinct vertices are adjacent.

#### Approach
1. Use an adjacency matrix to represent the graph.
2. Check that every pair of vertices in the subset is connected.

#### Code:
```
public static boolean findClique(int[][] adjMatrix, int[] vertexSet) {
    for (int i = 0; i < vertexSet.length; i++) {
        for (int j = i + 1; j < vertexSet.length; j++) {
            if (adjMatrix[vertexSet[i]][vertexSet[j]] != 1) {
                return false;
            }
        }
    }
    return true;
}
```

---

### Problem 2: Traveling Salesperson Problem (TSP)
#### Problem Description
- Transform a graph for the TSP and verify if a given path is a valid solution:
  1. Visits each vertex exactly once.
  2. Returns to the starting vertex.
  3. The path weight does not exceed a given threshold.

#### Transformation
Convert a Hamiltonian Circuit graph into a TSP graph:
1. Assign a weight of 1 to edges in the Hamiltonian Circuit.
2. Assign a higher weight (e.g., 2) to non-existent edges.

#### Code:
```
public static int[][] transform(boolean[][] hamiltonianCircuit) {
    int size = hamiltonianCircuit.length;
    int[][] tsp = new int[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            tsp[i][j] = hamiltonianCircuit[i][j] ? 1 : 2;
        }
    }
    return tsp;
}
```

#### Verification
Validate the TSP solution by checking:
1. Every vertex is visited once.
2. The solution starts and ends at the same vertex.
3. Total weight does not exceed the threshold.

```
public static boolean verifyTSP(int[][] graph, int[] solution, int threshold) {
    boolean[] visited = new boolean[graph.length];
    int total = 0, edgeCount = 0;
    boolean valid = true;

    for (int i = 0; i < solution.length - 1; i++) {
        if (graph[solution[i]][solution[i + 1]] > 0 && !visited[solution[i + 1]]) {
            total += graph[solution[i]][solution[i + 1]];
            edgeCount++;
            visited[solution[i + 1]] = true;
        } else {
            valid = false;
            return false;
        }
    }

    for (boolean visit : visited) {
        if (!visit) valid = false;
    }

    return valid && solution[0] == solution[solution.length - 1] && edgeCount == graph.length && total <= threshold;
}
```

---

### Problem 3: Hamiltonian Circuit (HC)
#### Problem Description
- Verify whether a given path is a Hamiltonian Circuit:
  1. Visits every vertex exactly once.
  2. Starts and ends at the same vertex.

#### Approach
1. Validate that all consecutive vertices in the path are connected.
2. Check that the path forms a cycle.

#### Code:
```
public static boolean verifyHamiltonianCircuit(boolean[][] graph, int[] path) {
    for (int i = 0; i < graph.length; i++) {
        if (!graph[path[i]][path[i + 1]]) {
            return false;
        }
    }
    return true;
}
```

---

### Problem 4: Hamiltonian Path (HP)
#### Problem Description
- Transform an HC into an HP to demonstrate HC's NP-hardness:
  - Add a new node connected only to the start and end nodes of the HC.
  - Verify the HP solution.

#### Transformation Code:
```
public static boolean[][] transformHCToHP(boolean[][] graph) {
    boolean[][] HP = new boolean[graph.length + 1][graph.length + 1];
    for (int i = 0; i < graph.length; i++) {
        for (int j = 0; j < graph.length; j++) {
            HP[i][j] = graph[i][j];
        }
    }
    HP[graph.length][0] = true;
    return HP;
}
```

#### Verification Code:
```
public static boolean verifyHP(boolean[][] graph, int[] path) {
    boolean[] visited = new boolean[graph.length];
    visited[graph.length - 1] = true;
    boolean valid = true;

    for (int i = 0; i < path.length - 1; i++) {
        if (graph[path[i]][path[i + 1]] && !visited[path[i + 1]]) {
            visited[path[i + 1]] = true;
        } else {
            valid = false;
        }
    }

    for (boolean visit : visited) {
        if (!visit) valid = false;
    }

    return valid && path[0] == graph.length - 1;
}
```

---

## Key Highlights
- **Clique Verification**: Validates subsets of vertices using adjacency matrices.
- **TSP Transformation and Verification**: Demonstrates reductions from Hamiltonian Circuit to TSP.
- **NP Completeness**: Proves HC is NP-hard by reducing HC to HP.

---
