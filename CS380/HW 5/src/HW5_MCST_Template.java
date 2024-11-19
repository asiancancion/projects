import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
// import java.util.Arrays;  // for debugging purposes, if needed

/*************************************************************************
 * HW5_MCST - CS 380 Homework 5 Minimum Cost Spanning Tree
 * 		class for demonstrating an implementation of both
 * 		Prim's and Kruskal's algorithms.
 *
 * 	Note: there are helper classes for edge sets (EdgeSet)
 * 		and edges (Edge) at the bottom of this file.
 *
 * @author Steven.Hadfield
 * @version 1.0 - 3/1/2014
 *
 */
public class HW5_MCST_Template {

    private static final int INF = Integer.MAX_VALUE;  // infinity

    /**********************************************************************
     * main() - top level driver.  Sets the adjacency matrix for the graph.
     * 		Calls Prim's algorithm and prints the results.  Establishes
     * 		an edge set for all edges and calls Kruskal's algorithm and
     * 		then prints the results.
     *
     * @param args - unused
     */
    public static void main(String[] args) {

        // set the adjacency matrix for the graph

        int[][] weights = { {0, 1, 3, 2, 4, 4},
                {1, 0, 3, 4, 3, INF},
                {3, 3, 0, 1, 5, INF},
                {2, 4, 1, 0, 3, 4},
                {4, 3, 5, 3, 0, 2},
                {4, INF, INF, 4, 2, 0} };

        // establish other needed variables and objects

        int nodeCount = weights.length;
        int edgeCount = 0;  // we'll count these up

        EdgeSet allEdges = new EdgeSet();  // all edges in the graph
        EdgeSet primEdges;		// edges for MCST from Prim's algorithm
        EdgeSet kruskalEdges;	// edges for MCST from Kruskal's algorithm
        EdgeSet greedyEdges;    //edges for greedy algo

        primEdges = prim( nodeCount, weights );  // call Prim's algorith

        // print the results from Prim's algorithm

        System.out.println("\nMCST from Prim's Algorithm:");
        if (primEdges != null) primEdges.print();

        // Prep for Kruskal's algorithm:
        //		count and add edges to the allEdges edge set

        for(int i=0; i<weights.length-1; i++)
            for(int j=i+1; j<weights[i].length; j++)
                if (weights[i][j] > 0) {
                    allEdges.addEdge(i, j, weights[i][j]);
                    edgeCount++;
                }

        // call Kruskall's algorithm

        kruskalEdges = kruskal( nodeCount, edgeCount, allEdges );

        // print results from Kruskal's algorithm

        System.out.println("\nMCST from Kruskal's Algorithm:");
        if (kruskalEdges != null) kruskalEdges.print();


        int[][] weights2 = { {0, 1, 3, 2},
                {1, 0, 3, 4},
                {3, 3, 0, INF},
                {2, 4, INF, 0}};

        greedyEdges = greedy(weights2.length,weights2);

        System.out.println("\nMCST from Greedy Algorithm:");
        if (greedyEdges != null) greedyEdges.print();
    }  // end main()

    /************************************************************************
     * prim() - Implementation of Prim's algorithm for computing
     * 		the minimum cost spanning tree.
     *
     * Note:
     * 		- EdgeSet is a subclass of LinkedList<Edge> and thus has an
     * 		  add(Edge) method.  The Edge class has a three-parameter
     * 		  constructor:  Edge(node1,node2,weight)
     *
     * 		- Algorithm 4.1 in the N&N text uses 1-based indexing for arrays
     * 		  so you'll need to adapt the algorithm for the 0-based indexing
     * 		  of Java
     *
     * @param numNodes - number of nodes in the graph
     * @param weights  - adjacency matrix with weights for the graph
     * @return         - Edge set with edges for the MCST
     */
    private static EdgeSet prim( int numNodes, int[][] weights ) {

        EdgeSet mcstEdges = new EdgeSet();
        int min;
        int vnear = 0;
        int[] nearest = new int[numNodes];
        int[] distance = new int[numNodes];
        //initialize all values in array to have 0 as nearest node and have weight be distance of edge to v1
        for (int i =1; i< numNodes; i++){
            nearest[i] = 0;
            distance[i] = weights[0][i];
        }
        for (int i = 0; i < numNodes-1; i++){
            min = INF;
            //find minimum distance node
            for (int j = 1; j < numNodes; j++){
                if (distance[j] >= 0 && distance[j] < min){
                    min = distance[j];
                    vnear = j;
                }
            }
            //add edge of minimum distance that is connected to current nodes to mcst
            mcstEdges.addEdge(vnear,nearest[vnear], distance[vnear]);
            //set distance to -1 as it was already travelled to
            distance[vnear] = -1;
            //go through a reintialize nearest based on the new node added
            for (int k = 1; k < numNodes; k++){
                if (weights[k][vnear] < distance[k]){
                    distance[k] = weights[k][vnear];
                    nearest[k] = vnear;
                }
            }
        }

        return mcstEdges;  // return the MCST edges

    } // end prim() method

    /************************************************************************
     * kruskal() - Implementation of Kruskall's algorithm for computing
     * 		the minimum cost spanning tree.
     *
     * Notes:
     * 		- Helper methods:  initial(), find(), and merge() from N&N
     * 		  Algorithm 4.2 are provided below this. They work on an int
     * 		  array mapping a node (via the array index) to a subset number
     * 		  (as the array value - subset[i] = j means node i is in subset j).
     *
     * 		- EdgeSet has a sort() method which will come in handy.
     *
     * 		- You can setup and use an iterator to traverse through an edge
     * 		  set as EdgeSet is a subclass of LinkedList<Edge>.
     *
     * @param numNodes - number of nodes (vertices) in the graph
     * @param numEdges - number of edges in the graph
     * @param edges	   - edge set for all edges in the graph
     * @return		   - edge set with just edges for the MCST
     */
    private static EdgeSet kruskal( int numNodes, int numEdges,
                                    EdgeSet edges ) {
        //initalize mcst to return
        EdgeSet mcst = new EdgeSet();
        //sort edges in increasing order
        edges.sort();
        int node1;
        int node2;
        Edge edge;
        //create a subset for nodes
        int[] subsets = initial(numNodes);
        int subsetFor1;
        int subsetFor2;
        int i = 0;
        while (mcst.size() < numNodes-1){
            //get lowest weight edge
            edge = edges.get(i);
            //get nodes that connect them
            node1 = edge.getNode1();
            node2 = edge.getNode2();
            //find what subsets those nodes are in
            subsetFor1 = find(subsets,node1);
            subsetFor2 = find(subsets,node2);
            //if they are not in the same subset merge the subset and then add the edge to the mcst
            if (subsetFor1 != subsetFor2){
                merge(subsets, subsets[node1],subsets[node2]);
                mcst.addEdge(node1,node2,edge.getWeight());
            }
            //increase to go to next edge
            i++;
        }

        return mcst;  // return the resulting MCST

    } // end  kruskal() method

    //Question 7 - greedy algorithm
    private static EdgeSet greedy( int numNodes, int[][] weights ){
        EdgeSet mcst = new EdgeSet();
        boolean[] visited = new boolean[numNodes];
        //initialize all visited array to false
        for (int i = 0; i < numNodes; i++){
            visited[i]= false;
        }
        //start at 0 node
        int sourceNode = 0;
        int nextNode = 0;
        int minEdge;
        while (mcst.size() < numNodes-1){
            minEdge = INF;
            //go nodes edges and find min cost edge and node that connects to it
            for (int i = 0; i <numNodes-1; i++){
                if (weights[sourceNode][i] < minEdge && sourceNode != i && visited[i] == false){
                    minEdge = weights[sourceNode][i];
                    nextNode = i;
                }
            }
            //set the node you are going to true
            visited[nextNode] = true;
            //set weights of where you just came from false
            weights[sourceNode][nextNode] = INF;
            weights[nextNode][sourceNode] = INF;
            //add edge to MCST
            mcst.addEdge(sourceNode,nextNode,minEdge);
            //set next node to source node and run through loop
            sourceNode = nextNode;

        }
        return mcst;
    }

    /**********************************************************************
     * initial() - allocates and initializes an array mechanism to map
     * 		nodes to the subset that they are in.  Initially, each is in
     * 		a subset identified by its own node number.  Node i is in
     * 		subset[i].
     *
     * @param numNodes - number of nodes (vertices)
     * @return		   - int array mapping nodes to their subset
     */
    private static int[] initial(int numNodes) {
        int[] subset = new int[numNodes];
        for(int i=0; i<numNodes; i++) subset[i] = i;
        return subset;
    }  // end initial() method

    /**********************************************************************
     * find() - returns the subset that node is in.
     *
     * @param subset - int array mapping nodes to their subsets
     * @param node   - node to look up the subset for
     * @return		 - subset number
     */
    private static int find( int[] subset, int node) {
        return subset[node];
    }  // end find() method

    /**********************************************************************
     * merge() - merges subsets p and q into one subset (all nodes)
     *
     * @param subset - int array mapping nodes to their subsets
     * @param p	     - first subset to merge
     * @param q      - second subset to merge
     */
    private static void merge( int[] subset, int p, int q ) {
        for(int i=0; i<subset.length; i++) {
            if (subset[i] == q) subset[i] = p;  // all of q goes into p
        }
    } // end merge() method

}  // end HW5_MCST class

/**********************************************************************
 * EdgeSet class - subclass of LinkedList containing Edge objects.
 *
 * @author Steven.Hadfield
 * @version 1.0 - 3/1/2014
 */
@SuppressWarnings("serial")
class EdgeSet extends LinkedList<Edge> {

    /*****************************************************************
     * EdgeSet() constructor - just uses the super class constructor
     */
    EdgeSet() {
        super();
    }  // EdgeSet() constructor

    /*****************************************************************
     * AddEdge() - creates a new Edge object with adjoining nodes and
     * 		the associated weight and then adds the edge to the EdgeSet
     *
     * @param node1 - first adjoining node
     * @param node2 - second adjoining node
     * @param weight - weight of the edge
     */
    void addEdge(int node1, int node2, int weight) {
        Edge e = new Edge(node1,node2,weight);
        this.add(e);
    }  // end addEdge() method

    /****************************************************************
     * sort() - sorts the edge set using the underlying order for
     * 		the Edge class (based upon the edge weight).  Note, this
     * 		is handy for Kruskal's algorithm.
     */
    void sort() {
        Collections.sort(this);
    }  // end sort() method

    /****************************************************************
     * print() - traverses the edge set printing each edge followed
     * 		by a total of the edge weights
     */
    void print() {
        Iterator<Edge> iterator = this.iterator();
        int mcstWeight = 0;
        while(iterator.hasNext()) {
            Edge e = iterator.next();
            System.out.println(e);
            mcstWeight += e.getWeight();
        }
        System.out.println("MCST total weight is " + mcstWeight);
    }
}  // end EdgeSet inner class


/********************************************************************
 * Edge class - hold individual edges with adjoining nodes and the
 * 		weight for the edge
 *
 * @author Steven.Hadfield
 * @version 1.0 - 3/1/2014
 */
class Edge implements Comparable<Edge> {

    private int node1; // first node
    private int node2; // second node
    private int weight;  // weight of the edge

    /*****************************************************************
     * Edge() constructor setting all three attributes
     *
     * @param n1 - first adjoining node (vertex)
     * @param n2 - second adjoining node (vertex)
     * @param w  - weight of the edge
     */
    Edge(int n1, int n2, int w) {
        this.node1 = n1;
        this.node2 = n2;
        this.weight = w;
    } // end Edge constructor

    /*****************************************************************
     * getter methods for each attribute
     */
    int getNode1() { return this.node1; }
    int getNode2() { return this.node2; }
    int getWeight() { return this.weight; }

    /*****************************************************************
     * compareTo() method needed to implement the Comparable interface
     */
    public int compareTo(Edge e) {
        return this.weight - e.weight;
    } // end compareTo() method

    /*****************************************************************
     * toString() method for printing the edge
     */
    public String toString() {
        return String.format("(%d, %d) weighs %d",
                this.node1, this.node2, this.weight);
    } // end toString() method

}  // end Edge inner class

