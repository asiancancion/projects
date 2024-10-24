/** gameLogic.c
 * ===========================================================
 * Name: CS220
 * Modified by: Caleb Song
 * Section: M3 De Freitas
 * Project: PEX5
 * Purpose: The implementation of functions needed to
 *          create a Shannon Switching Game.
 * Documentation: Lots of EI from Lt Col De Freitas. Asked C3C Michel for help on how to fix my graph when the cut function was not working - she told me to reorder the functions.
 * ===========================================================
 */

#define _CRT_SECURE_NO_WARNINGS  // Hide "unsafe, deprecated" warnings, must be at the top


#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "gameLogic.h"

#define MAXIMUM_TRIES_TO_SET_LOCATION 1000
#define MAXIMUM_TRIES_TO_CREATE_EDGE 1000
#define MAXIMUM_TRIES_TO_FIND_RANDOM_EDGE 5000
#define VERTEX_DRAW_RADIUS 5
#define CLICK_TOLERANCE 5.0

// The type of the two game players.
static int playerType[2] = {HUMAN_PLAYER, HUMAN_PLAYER};
static char *playerTypeNames[2] = {" (Human)", " (AI)"};

static int activePlayer = CUT_PLAYER;
static char *activePlayerName[] = {"Cut's turn", "Short's turn"};

// Additional global variables
static int gameState = GAME_UNDERWAY;  // Possible values: SHORT_WINS, CUT_WINS, GAME_UNDERWAY

// Local functions - intentionally not included in the header file
static void setLocation(Vertex *vertex, int width, int height, int margin);
static int distance(Vertex *v1, Vertex *v2);
static int someVerticesTooClose(Vertex *vertices, int last, int minimumDistance);
static int compareVertices(const void *e1, const void *e2);
static int degree(Graph *graph, int index);
static void findEdge(Graph *graph, int mouseX, int mouseY, Edge *edge);
static int humanPlayer(Graph *graph, int mouseX, int mouseY);
static int aiPlayer(Graph *graph);

// Vertices are sorted according to their distance from the origin (0,0)
static Vertex origin = {0, 0, 0};

/** -------------------------------------------------------------------
 * Set the type of player.
 * @param player Either CUT_PLAYER or SHORT_PLAYER
 * @param type Either HUMAN_PLAYER or AI_PLAYER
 */
void setPlayerType(int player, int type) {
    if ((player == CUT_PLAYER || player == SHORT_PLAYER) &&
        (type == HUMAN_PLAYER || type == AI_PLAYER)) {
        playerType[player] = type;
    }
}

/** -------------------------------------------------------------------
 * Set the active player. This should be called only once at
 * the start of the game to determine who goes first.
 * @param player Either CUT_PLAYER or SHORT_PLAYER
 */
void setActivePlayer(int player) {
    if (player == CUT_PLAYER || player == SHORT_PLAYER) {
        activePlayer = player;
    }
}

/** -------------------------------------------------------------------
 * Create a set of random vertices for the game graph. The location
 * of each vertex must meet certain constraints:
 *    1) It must be inside the game window.
 *    2) It must be "margin" pixels aways from the window borders.
 *    3) It must be "minDistance" away from all other vertices.
 * @param graph the graph to modify
 * @param max_X the width of the window along the x axis
 * @param max_Y the height of the window along the y axis
 * @param margin the number of pixels to keep clear along all borders
 * @param minDistance the minimum distance between any two vertices
 * @param randomize if TRUE, the location of the vertices is random.
 *                  if FALSE, the same graph every time.
 */
void createVertices(Graph *graph, int max_X, int max_Y, int margin, int minDistance,
                    int randomize) {
    // Create a local variable to point to the vertex array to simplify the code.
    Vertex *vertices = (Vertex *)graph->vertices;

    if (randomize) {
        // Use the current time to randomize the random number generator.
        time_t t;
        srand((unsigned)time(&t));
    }

    // Set a random location for the first vertex.
    setLocation(vertices, max_X, max_Y, margin);

    // Set a random location for all the other vertices, but make sure they are
    // not too close to any of the other vertices that have already been created.
    int numberTries;
    int tooClose;
    for (int j = 1; j < graph->numberVertices; j++) {
        numberTries = 0;
        tooClose = TRUE;
        while (tooClose && numberTries < MAXIMUM_TRIES_TO_SET_LOCATION) {
            numberTries++;
            setLocation(vertices + j, max_X, max_Y, margin);

            tooClose = someVerticesTooClose(vertices, j, minDistance);
        }
        if (numberTries >= MAXIMUM_TRIES_TO_SET_LOCATION) {
            printf("ERROR in createVertices. Too many tries to create a new vertex.");
            exit(1);
        }
    }

    // Sort the vertices based on their distance from the origin (0,0)
    qsort(graph->vertices, (size_t)graph->numberVertices, sizeof(Vertex), compareVertices);

    // Make the first and last vertex the starting and ending vertices
    // of the Shannon switching game.
    vertices[0].type = STARTING_VERTEX;
    vertices[graph->numberVertices - 1].type = ENDING_VERTEX;
}

/** -------------------------------------------------------------------
 * Set the location of a vertex.
 * @param vertex the vertex to change
 * @param width the width of the window
 * @param height the height of the window
 * @param margin the margins around the borders
 */
void setLocation(Vertex *vertex, int width, int height, int margin) {
    vertex->x = (rand() % (width - (2 * margin))) + margin;
    vertex->y = (rand() % (height - (2 * margin))) + margin;
    vertex->type = NORMAL_VERTEX;
}

/** -------------------------------------------------------------------
 * Check to verify that a vertex is not too close to any of the other
 * vertices in the graph.
 * @param vertices the array of vertices
 * @param last the vertex to check
 * @param minimumDistance the minimum distance between two vertices
 * @return TRUE if the distance between vertices[last] and every
 *         other vertex is greater than minimumDistance.
 *         return FALSE otherwise.
 */
int someVerticesTooClose(Vertex *vertices, int last, int minimumDistance) {
    // Check to make sure vertices[last] is not too close to other vertices
    Vertex *lastVertex = vertices + last;
    int k = 0;
    while (k < last && distance(lastVertex, vertices + k) > minimumDistance) {
        k++;
    }
    return k < last;  // TRUE if one vertex is less than minimumDistance away.
}

/** -------------------------------------------------------------------
 * Calculate the distance between two vertices
 * @param v1 vertex 1
 * @param v2 vertex 2
 * @return the distance between the two vertices
 */
int distance(Vertex *v1, Vertex *v2) {
    double dx = (double)v1->x - (double)v2->x;
    double dy = (double)v1->y - (double)v2->y;
    return (int)(sqrt(dx * dx + dy * dy));
}

/** -------------------------------------------------------------------
 * Compare two vertices. This is used by qsort to sort the vertices array.
 * @param e1 a pointer to a vertex
 * @param e2 a pointer to a vertex
 * @return -1 if e1 < e1; 0 if e1 == e2, +1 if e1 > e2
 */
int compareVertices(const void *e1, const void *e2) {
    Vertex *v1 = (Vertex *)e1;
    Vertex *v2 = (Vertex *)e2;
    int dist1 = distance(v1, &origin);
    int dist2 = distance(v2, &origin);
    if (dist1 < dist2)
        return -1;
    else if (dist1 == dist2)
        return 0;
    else
        return 1;
}

void createEdges(Graph *graph, int minNumberEdges, int maxNumberEdges, int windowWidth,
                 int windowHeight, double edgeLengthPercent) {
    Vertex *vertices = (Vertex *)graph->vertices;

    // The number of edges for each vertex is random within a range
    int edgeRange = (maxNumberEdges - minNumberEdges) + 1;
    int existingEdges;
    int desiredEdges;
    int edgesNeeded;
    int toVertex;

    // Restrict the edges to the close vertices by restricting the length
    // of an edge.
    int maxEdgeLength;
    if (windowWidth > windowHeight) {
        maxEdgeLength = (int)(windowWidth * edgeLengthPercent);
    } else {
        maxEdgeLength = (int)(windowHeight * edgeLengthPercent);
    }

    for (int nodeIndex = 0; nodeIndex < graph->numberVertices; nodeIndex++) {
        existingEdges = degree(graph, nodeIndex);
        desiredEdges = (rand() % edgeRange) + minNumberEdges;
        edgesNeeded = desiredEdges - existingEdges;
        for (int j = 0; j < edgesNeeded; j++) {
            toVertex = nodeIndex;
            int tries = 0;
            while (tries < MAXIMUM_TRIES_TO_CREATE_EDGE && toVertex == nodeIndex) {
                toVertex = rand() % graph->numberVertices;
                if (toVertex != nodeIndex) {
                    int existingEdge = graphGetEdge(graph, nodeIndex, toVertex);
                    if (existingEdge == NO_EDGE &&
                        distance(vertices + nodeIndex, vertices + toVertex) <= maxEdgeLength) {
                        break;
                    }
                }
                tries++;
            }
            if (tries > MAXIMUM_TRIES_TO_CREATE_EDGE) {
                printf("Error in createEdges. The maximum number of tries was exceeded.\n");
                exit(1);
            }
            graphSetEdge(graph, nodeIndex, toVertex, NORMAL_EDGE);
        }
    }
}

/** -------------------------------------------------------------------
 * Calculate the number of edges that are connected to a specific vertex.
 * @param graph the graph
 * @param index which vertex, an array index [0, graph->numberNodes-1]
 * @return the number of edges leaving vertex[index]
 */
int degree(Graph *graph, int index) {
    int count = 0;
    for (int j = 0; j < graph->numberVertices; j++) {
        if (graph->edges[index][j] > NO_EDGE) {
            count++;
        }
    }
    return count;
}

/** -------------------------------------------------------------------
 * Print the value that define a graph. Great for debuggin!
 * @param graph the graph
 */
void printGraph(Graph *graph) {
    Vertex *vertices = (Vertex *)graph->vertices;
    for (int j = 0; j < graph->numberVertices; j++) {
        printf("VERTEX %3d:   X=%4d    Y=%4d  TYPE=%1d\n", j, vertices[j].x, vertices[j].y,
               vertices[j].type);
    }

    for (int j = 0; j < graph->numberVertices; j++) {
        printf("FROM %d   TO: ", j);
        for (int k = 0; k < graph->numberVertices; k++) {
            printf(" %3d", graph->edges[j][k]);
        }
        printf("\n");
    }
}

/** -------------------------------------------------------------------
 * Draw the graph on the window.
 * @param graph the graph
 * @param hwnd handle to the window where the graph is to be drawn
 * @param labelVertices if TRUE, the array index of each vertex is displayed
 */
void drawGraph(Graph *graph, HWND hwnd, int labelVertices) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    int brush;
    int pen;
    char textString[40];
    Vertex *vertices = (Vertex *)graph->vertices;

    clearBackground(hwnd, hdc, SOLID_THIN_WHITE, MY_WHITE_BRUSH);

    // Display the player's name and the player's type in the upper-left corner.
    strcpy(textString, activePlayerName[activePlayer]);
    strcat(textString, playerTypeNames[playerType[activePlayer]]);

    // TODO: Output winner, HINT -> look at the global var "gameState"
    if (gameState == CUT_WINS) {
        strcpy(textString, "CUT WINS - GAME OVER");
    } else if (gameState == SHORT_WINS) {
        strcpy(textString, "SHORT WINS - GAME OVER");
    }

    drawText(hdc, 3, 3, textString);

    // Draw the edges
    for (int from = 0; from < graph->numberVertices; from++) {
        for (int to = from + 1; to < graph->numberVertices; to++) {
            if (graph->edges[from][to] > NO_EDGE) {
                if (graph->edges[from][to] == LOCKED_EDGE) {
                    // Draw a locked edge
                    pen = SOLID_THICK_RED;
                } else {
                    // Draw a normal edge
                    pen = SOLID_THIN_BLACK;
                }
                drawLine(hdc, vertices[from].x, vertices[from].y, vertices[to].x, vertices[to].y,
                         pen);
            }
        }
    }

    // Draw the vertices
    for (int j = 0; j < graph->numberVertices; j++) {
        if (vertices[j].type == NORMAL_VERTEX) {
            pen = SOLID_THIN_BLACK;
            brush = MY_BLACK_BRUSH;
        } else {  // vertices[j].type == STARTING_VERTEX
            pen = SOLID_THIN_GREEN;
            brush = MY_GREEN_BRUSH;
        }

        drawCircle(hdc, vertices[j].x, vertices[j].y, VERTEX_DRAW_RADIUS, pen, brush);

        if (labelVertices) {
            if (j == 0) {
                sprintf(textString, "START");
            } else if (j == (graph->numberVertices - 1)) {
                sprintf(textString, "END");
            } else {
                sprintf(textString, "%d", j);
            }
            drawText(hdc, vertices[j].x - 20, vertices[j].y - 20, textString);
        }
    }
    EndPaint(hwnd, &ps);
}

/** -------------------------------------------------------------------
 * Determine if a mouse click has selected a specific graph edge
 * @param x1 the starting coordinate (x1,y1) of the edge
 * @param y1
 * @param x2 the ending coordinate (x2,y2) of the edge
 * @param y2
 * @param mouseX the location of the mouse (mouseX, mouseY)
 * @param mouseY
 * @return TRUE if the mouse location is within CLICK_TOLERANCE pixels
 *         of any part of the edge. Return FALSE otherwise.
 */
int edgeClicked(int x1, int y1, int x2, int y2, int mouseX, int mouseY) {
    // double d = 10000.0;
    double onX, onY;  // The projection of the mouse onto the line segment
    double t;         // parametric parameter for a line segment from (x1,y1) to (x2,y2)

    double dx = x2 - x1;
    double dy = y2 - y1;
    t = ((mouseX - x1) * (x2 - x1) + (mouseY - y1) * (y2 - y1)) / (dx * dx + dy * dy);
    if (t < 0 || t > 1.0) {
        // The projected point is not on the line segment
        return FALSE;
    } else {
        // Calculate the projected point.
        onX = x1 + dx * t;
        onY = y1 + dy * t;

        // Find the distance from the mouse to the projected point.
        double dx2 = mouseX - onX;
        double dy2 = mouseY - onY;
        double dist = sqrt(dx2 * dx2 + dy2 * dy2);

        return dist <= CLICK_TOLERANCE;
    }
}

/** -------------------------------------------------------------------
 * Find an edge that is within CLICK_TOLERANCE of the mouse location.
 * @param graph the graph
 * @param mouseX the location of the mouse (mouseX, mouseY)
 * @param mouseY
 * @param edge output of the function. If the edge is (-1,-1) then
 *             no edge was found. If the edge is (A,B) on return
 *             then the edge that goes from node A to node B was
 *             within CLICK_TOLERANCE of the mouse location.
 */
void findEdge(Graph *graph, int mouseX, int mouseY, Edge *edge) {
    // Assume that no edge can be found
    edge->fromVertex = -1;
    edge->toVertex = -1;

    Vertex *vertices = (Vertex *)graph->vertices;

    // Search all the edges and find the closest one
    for (int from = 0; from < graph->numberVertices; from++) {
        for (int to = 0; to < graph->numberVertices; to++) {
            if (graph->edges[from][to] == NORMAL_EDGE) {
                if (edgeClicked(vertices[from].x, vertices[from].y, vertices[to].x, vertices[to].y,
                                mouseX, mouseY)) {
                    // printf("Found %3d %3d\n", from, to);
                    edge->fromVertex = from;
                    edge->toVertex = to;
                    return;
                }
            }
        }
    }
}

/** -------------------------------------------------------------------
 * Take a turn of the game by a human player. The location of the
 * user's mouse click is used to detemine the edge that is changed.
 * @param graph the graph
 * @param mouseX the location of the mouse (mouseX, mouseY)
 * @param mouseY
 * @return TRUE if the turn was taken. Return FALSE if the turn
 *         was not taken (e.g., if the user did not select an edge.)
 */
int humanPlayer(Graph *graph, int mouseX, int mouseY) {
    Edge edge;
    findEdge(graph, mouseX, mouseY, &edge);

    if (edge.fromVertex == -1) {
        // No edge was found; therefore this turn still needs
        // to be made.
        return FALSE;
    } else {
        if (activePlayer == SHORT_PLAYER) {
            graphSetEdge(graph, edge.fromVertex, edge.toVertex, LOCKED_EDGE);
        } else {  // activePlayer == CUT_PLAYER
            graphSetEdge(graph, edge.fromVertex, edge.toVertex, NO_EDGE);
        }
        return TRUE;
    }
}

/** -------------------------------------------------------------------
 * Make a move for an AI player.
 * @param graph the graph
 * @return TRUE if the turn was taken. Return FALSE if the turn
 *         was not taken.
 */
int aiPlayer(Graph *graph){
    
    int parent;
    int toVertex;
    int numVert = graph->numberVertices - 1;
    //declare a 2d array of ints
    int **table = (int **)malloc(3 * sizeof(int));
    for (int i = 0; i < 3; i++) {
        table[i] = (int *)malloc((numVert+1) * sizeof(int));
    }
    table = runDjikstras(graph,0);
    parent = table[1][numVert];
    toVertex = numVert;
    int value;
    //Loops through djikstras table, looks at edges from endNode to parent until we find an edge that is unprotected that can be cut or protected
    while (toVertex != 0) {
        //see if edge is protected, unprotected, cut
        value = graphGetEdge(graph, parent, toVertex);
        //if edge is normal
        if (value == NORMAL_EDGE) {
            //if player is short will protect the edge
            if (activePlayer == SHORT_PLAYER) {
                graphSetEdge(graph, parent, toVertex, LOCKED_EDGE);
            } 
            //if player is cut will cut the edge
            else {  // activePlayer == CUT_PLAYER
                graphSetEdge(graph, parent, toVertex, NO_EDGE);
            }
            return TRUE;
        } 
        else {
            toVertex = parent;
            parent = table[1][toVertex];
        }
    }
    return FALSE;
}
/** -------------------------------------------------------------------
 * create Djikstras table
 * @param graph the graph
 * @param type determines what edges to use if it is 0 then do shortest path of unprotected and protected edges. if it is 1 then do shortest path of protected edges
 * @return returns 2d djikstras table
 */
int **runDjikstras(Graph *graph, int type) {
    int numberVerts = graph->numberVertices;
    int *distance = (int *)malloc(numberVerts * sizeof(int));
    int *visited = (int *)malloc(numberVerts * sizeof(int));
    int *parent = (int *)malloc(numberVerts * sizeof(int));

    //create 2d table
    int **table = (int **)malloc(3 * sizeof(int));
    for (int i = 0; i < 3; i++) {
        table[i] = (int *)malloc(numberVerts * sizeof(int));
    }

    //initalize values of arrays
    for (int i = 0; i < numberVerts; i++) {
        distance[i] = 1000;
        visited[i] = 0;
        parent[i] = -1;
    }

    distance[0] = 0;
    int mindist;
    int nextNode = 0;
    int currentV = 0;

    //if type is 0 then runs protected and unprotected shortest path
    if (type == 0) {
        for (int i =0; i<numberVerts;i++){
            mindist = 1000;
            nextNode = 0;
            //find the smallest value
            for (int j =0; j<numberVerts;j++){
                if (distance[j] < mindist && visited[j] != 1){
                    mindist = distance[j];
                    nextNode = j;
                }
            }
            currentV = nextNode;
            visited[currentV] = 1;
            //run through distance table and update if it is smaller
            for (int k =0; k<numberVerts;k++){
                //edge must not be cut and the distance is greater than the distance to current node + 1 to update
                if ((graph->edges[currentV][k] == 1 || graph->edges[currentV][k] == 2) && distance[k] > distance[currentV] + 1){
                    distance[k] = distance[currentV] +1;
                    parent[k] = currentV;
                }
            }
        }
    }
    //type 1 runs only protected shortest path
    else {
        for (int i =0; i<numberVerts;i++){
            mindist = 1000;
            nextNode = 0;
            for (int j =0; j<numberVerts;j++){
                if (distance[j] < mindist && visited[j] != 1){
                    mindist = distance[j];
                    nextNode = j;
                }
            }
            currentV = nextNode;
            visited[currentV] = 1;
            //run through distance table and update if it is smaller
            for (int k =0; k<numberVerts;k++){
                //edge must not be cut or normal edge and the distance is greater than the distance to current node + 1 to update
                if (graph->edges[currentV][k] == 2 && distance[k] > distance[currentV] + 1){
                    distance[k] = distance[currentV] +1;
                    parent[k] = currentV;
                }
            }
        }
        }
    // print table and assigns values to 2d table to return
    printf("\nTABLE\n");
    printf("NODES:  ");
    for (int i = 0; i < numberVerts; i++) {
        printf("%4d ", i);
    }
    printf("\nCOST:   ");
    for (int i = 0; i < numberVerts; i++) {
        table[0][i] = distance[i];
        printf("%4d ", table[0][i]);
    }
    printf("\nPARENT: ");
    for (int i = 0; i < numberVerts; i++) {
        table[1][i] = parent[i];
        printf("%4d ", table[1][i]);
    }
    printf("\nVISITED:");
    for (int i = 0; i < numberVerts; i++) {
        table[2][i] = visited[i];
        printf("%4d ", table[2][i]);
    }
    printf("\n\n");

    printf("\n\n");

    return table;
}

/** -------------------------------------------------------------------
 * checks to see who wins
 * @param graph the graph
 * @param table djikstras table
 * @param type determines what to check if it is 0 then it checks if cut wins, if it is 1 then it checks if short wins
 * @return returns 0 if cut wins, 1 if short wins, and -1 if game continues
 */
int checkWinner(Graph *graph, int **table, int type) {
    int numberVerts = graph->numberVertices;
    //Check if cut wins
    if (type == 0) {
        if (table[1][numberVerts - 1] == -1) {
            return 0;
        }
        //continue game
        return -1;
    }
    //Check if short wins 
    else {
        if (table[1][numberVerts - 1] != -1) {
            return 1;
        }
        //Continue game
        return -1;
    }
}

/** -------------------------------------------------------------------
 * Take one turn in the Shannon Switching game. If the turn was successful,
 * the active player changes to the other player and the window is redrawn.
 * If the turn was not taken, the active player is unchanged and the window
 * is not redrawn.
 * @param graph the graph
 * @param mouseX the location of the mouse (mouseX, mouseY)
 * @param mouseY
 */
void doTurn(Graph *graph, int mouseX, int mouseY) {
    int turnIsDone = FALSE;
    int numberVerts = graph->numberVertices;
    int checker =-1;
    int checker2 =-1;
    
    //if game is underway does player/ai turn
    if (gameState == GAME_UNDERWAY) {
        if (playerType[activePlayer] == HUMAN_PLAYER) {
            turnIsDone = humanPlayer(graph, mouseX, mouseY);
        } else {
            turnIsDone = aiPlayer(graph);
        }
    }
    //create 2d array for unprotected table
    int **unprotectedTable = (int **)malloc(3 * sizeof(int));
    for (int i = 0; i < 3; i++) {
        unprotectedTable[i] = (int *)malloc(numberVerts * sizeof(int));
    }
    //create 2d array for protected table
    int **protectedTable = (int **)malloc(3 * sizeof(int));
    for (int i = 0; i < 3; i++) {
        protectedTable[i] = (int *)malloc(numberVerts * sizeof(int));
    }

    // Checks for cut winner
    if (gameState == GAME_UNDERWAY){ 
        unprotectedTable = runDjikstras(graph, 0);
        //if checkWinner retunrns 0 cut wins
        checker = checkWinner(graph, unprotectedTable, 0);
        if (checker == 0) {
            gameState = CUT_WINS;
        }
    }
    //Checks for short winner
    if (gameState == GAME_UNDERWAY){
        protectedTable = runDjikstras(graph, 1);
        checker2 = checkWinner(graph, protectedTable, 1);
        //if checkWinner retunrns 1 cut wins
        if (checker2 == 1) {
            gameState = SHORT_WINS;  
        }
    }
    
    printGraph(graph);
    
    //Swaps player if turn is complete
    if (turnIsDone) {
        activePlayer = 1 - activePlayer;  // swap active player
        redraw();
    }
    
}
