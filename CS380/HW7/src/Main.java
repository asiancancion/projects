public class Main {
    public static void main(String[] args) {
        //Question 2
        int[][] adjacencyMatrix = new int[5][5];
        adjacencyMatrix[0][1] = 1;
        adjacencyMatrix[0][3] = 1;
        adjacencyMatrix[0][4] = 1;
        adjacencyMatrix[1][0] = 1;
        adjacencyMatrix[1][2] = 1;
        adjacencyMatrix[1][3] = 1;
        adjacencyMatrix[1][4] = 1;
        adjacencyMatrix[2][1] = 1;
        adjacencyMatrix[2][3] = 1;
        adjacencyMatrix[3][0] = 1;
        adjacencyMatrix[3][1] = 1;
        adjacencyMatrix[3][2] = 1;
        adjacencyMatrix[3][4] = 1;
        adjacencyMatrix[4][0] = 1;
        adjacencyMatrix[4][1] = 1;
        adjacencyMatrix[4][3] = 1;



        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                System.out.print(adjacencyMatrix[i][j]);
            }
            System.out.println();
        }
        int[] vertexSet = new int[]{0,1,4};
        boolean clique = findClique(adjacencyMatrix, vertexSet);
        if (clique){
            System.out.println("It's a clique");
        }
        else{
            System.out.println("Not a clique");
        }



        //Question 3
        boolean[][] hamiltonianCircuit = new boolean[5][5];
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                hamiltonianCircuit[i][j] = true;
            }
        }
        int[][] tsp = transform(hamiltonianCircuit);
        int bound = tsp.length;
        int[] solution = new int []{0,1,2,3,4,0};
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                System.out.print(tsp[i][j]);
            }
            System.out.println();
        }
        boolean tspVerify = verifyTSP(tsp,solution,bound);
        if (tspVerify){
            System.out.println("Valid solution");
        }
        else{
            System.out.println("Invalid solution");
        }

        //Question 4

        //first show HC is NP
        boolean[][] graph = new boolean[5][5];
        graph[0][1] = true;
        graph[1][2] = true;
        graph[2][3] = true;
        graph[3][4] = true;
        graph[4][0] = true;
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                System.out.print(graph[i][j] + " ");
            }
            System.out.println();
        }
        int[] path = new int []{0,1,2,3,4,0};
        boolean HCverify = verifyHamiltonianCircuit(graph,path);
        if (HCverify){
            System.out.println("Candidate solution for HC is a valid solution");
        }
        else{
            System.out.println("Candidate solution for HC is an invalid solution");
        }
        //Second show HC is NP-hard by verifying that HC is a reduction of HP (Question am I going from HP -> HC or HC -> HP?)
        //Ima assume HC -> HP
        boolean[][] HP = transformHCToHP(graph);
        for (int i = 0; i < 6; i++){
            for (int j = 0; j < 6; j++){
                System.out.print(HP[i][j] + " ");
            }
            System.out.println();
        }
        int[] newPath = new int[path.length];
        for (int i = 0; i < newPath.length-1; i++){
            newPath[i+1] = path[i];
        }
        newPath[0] = newPath.length-1;
        boolean HPverify = verifyHP(HP, newPath);
        if (HPverify){
            System.out.println("HP Decision is valid therefore HC is NP Hard");
        }
        else{
            System.out.println("HP Decision is invalid therefore HC is not NP Hard");
        }


    }

    //Do we need to change this so that it uses just a parameter k and if so do I need to do backtracking??
    public static boolean findClique(int[][] adjMatrix, int[] vertexSet){
        //go through the vertex set and make sure that they are all in the adj matrix
        for (int i = 0; i < vertexSet.length; i++){
            for (int j = i+1; j < vertexSet.length; j++){
                if(adjMatrix[vertexSet[i]][vertexSet[j]] != 1){
                    return false;
                }
            }
        }
        return true;
    }
    //transformation algorithm
    public static int[][] transform(boolean[][] hamiltonianCircuit){
        int size = hamiltonianCircuit.length;
        int[][] tsp = new int[size][size];
        for (int i = 0; i < size; i++){
            for (int j = 0; j < size; j++){
                if (hamiltonianCircuit[i][j]){
                    tsp[i][j] = 1;
                }
                else{
                    tsp[i][j] = 2;
                }
            }
        }
        return tsp;
    }
    public static boolean verifyTSP(int[][] graph, int[] solution, int threshhold){
        boolean[] visited = new boolean[graph.length];
        for (int i = 0; i < graph.length-1; i++){
            visited[i] = false;
        }
        int total = 0;
        int edgeCount = 0;
        boolean valid = true;
        for (int i = 0; i < solution.length-1; i++){
            if (graph[solution[i]][solution[i+1]] > 0 && visited[solution[i+1]] == false){
                total+= graph[solution[i]][solution[i+1]];
                edgeCount+=1;
                visited[solution[i+1]] = true;
            }
            else{
                valid = false;
                return valid;
            }
        }
//        System.out.println(solution[0]);
//        System.out.println(solution[solution.length-1]);
//        System.out.println(valid);
//        System.out.println(edgeCount);
//        System.out.println(graph.length);
//        System.out.println(total);
//        System.out.println(threshhold);
        for (int i = 0; i < graph.length; i++){
            if (visited[i] == false){
                valid = false;
            }
        }

        return (solution[0] == solution[solution.length-1]) && valid && (edgeCount== graph.length) && (total <= threshhold);
    }
    public static boolean verifyHamiltonianCircuit (boolean[][] graph, int[] path){
        int length = graph.length;
        boolean verify = true;
        for (int i = 0; i < length; i++){
            if(graph[path[i]][path[i+1]] == false){
                verify = false;
            }
        }
        return verify;
    }
    public static boolean[][] transformHCToHP(boolean[][] graph){
        boolean [][] HP = new boolean[graph.length+1][graph.length+1];
        for (int i = 0; i < graph.length; i++){
            for (int j = 0; j < graph.length; j++){
                HP[i][j] = graph[i][j];
            }
        }

        HP[graph.length][0] = true;

        return HP;
    }
    //what to do for this, check if start or end is new node, make sure HP exists, visit exactly once,
    public static boolean verifyHP (boolean[][] graph, int[] path){
        boolean valid = true;
        boolean[] visited = new boolean[graph.length];
        visited[graph.length-1] = true;
        for (int i = 0; i < graph.length-1; i++){
            if (graph[path[i]][path[i+1]] == true && visited[path[i+1]] == false){
                visited[path[i+1]] = true;
            }
            else{
                valid = false;
            }

        }
        for (int i = 0; i < graph.length; i++){
            if (visited[i] == false){
                valid = false;
            }
        }

        return valid && (path[0] == graph.length-1);
    }

}