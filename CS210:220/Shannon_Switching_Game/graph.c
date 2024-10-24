/** Graph.c
 * ===========================================================
 * Name: CS220
 * Modified by: Caleb Song
 * Section: M3 De Freitas
 * Project: PEX5
 * Purpose: The definition of a graph.
 * Documentation: Lots of EI from Lt Col De Freitas. Asked C3C Michel for help on how to fix my graph when the cut function was not working - she told me to reorder the functions.
 * ===========================================================
 */

#include "graph.h"
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include "gameLogic.h"
/** -------------------------------------------------------------------
 * Create the memory needed to hold a graph data structure.
 * @param numberVertices the number of vertices in the graph
 * @param bytesPerNode the number of bytes used to represent a
 *                     single vertex of the graph
 * @return a pointer to a graph struct
 */
Graph * graphCreate(int numberVertices, int bytesPerNode) {
    // TODO
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numberVertices = numberVertices;

    graph->vertices = malloc(numberVertices*bytesPerNode);
    graph->edges = (int**)malloc(numberVertices * sizeof(int));
    for (int i = 0; i < numberVertices; i++){
        graph->edges[i] = (int*)malloc(numberVertices * sizeof(int));      
    }
    for(int k = 0; k < numberVertices; k ++){
        for(int j = 0; j < numberVertices; j++){
            graph->edges[k][j] = 0;
        }
    }
    return graph;
}
/** -------------------------------------------------------------------
 * Delete a graph data structure
 * @param graph the graph to delete
 */
void graphDelete(Graph* graph) {
    free(graph->vertices);
    free(graph);
}
/** -------------------------------------------------------------------
 * Set the state of an edge in a graph
 * @param graph the graph to modify
 * @param fromVertex the beginning vertex of the edge
 * @param toVertex the ending vertex of the edge
 * @param state the state of the edge
 */
void graphSetEdge(Graph* graph, int fromVertex, int toVertex, int state) {
    graph->edges[fromVertex][toVertex] = state;
    graph->edges[toVertex][fromVertex] = state;
}
/** -------------------------------------------------------------------
 * Get the state of an edge in a graph
 * @param graph the graph
 * @param fromVertex the starting vertex of the edge
 * @param toVertex the ending vertex of the edge
 * @return the state of the edge
 */
int graphGetEdge(Graph* graph, int fromVertex, int toVertex) {
    int value = graph->edges[fromVertex][toVertex];
    return value;
}
