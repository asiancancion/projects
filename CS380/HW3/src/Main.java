public class Main {
    public static void main(String[] args) {
        //array with 9
        int[] coins = new int[]{ 0,0,0,0,0,0,0,1,0 };
        //array with 12
        int[] coins1 = new int[]{ 0,0,0,0,1,0,0,0,0,0,0,0 };
        //test 43a
        System.out.println("The fake coin is the one numbered: " + sort1(coins));

        //test43b
        System.out.println("The fake coin is the one numbered: " + sort2(coins1,0,11));
        //DOESNT WORK WITH 15 for some reason
        //test 44
        int[][] testArray = new int[10][10];
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                testArray[i][j] = (i*10) + j;
            }
        }
        for (int i = 0; i < 10; i++){
            for (int j = 0; j < 10; j++){
                System.out.print(testArray[i][j] + " ");
            }
            System.out.println();
        }
        if (searchValue(testArray,870,0,0,9,9)){
            System.out.println("Found");
        }
        else{
            System.out.println("Not Found");
        }


    }
    /* 43A
    Suppose we have nine identical-looking coins numbered 1 through
    9 and only one of the coins is heavier than the others. Suppose
    further that you have one balance scale and are allowed only two
    weighings. Develop a method for finding the heavier counterfeit
    coin given these constraints.
     */
    public static int sort1(int[] arrayCoins){
        //Split the coins into 3 groups and add their weights
        int sum1 = arrayCoins[0] + arrayCoins[1] + arrayCoins[2];
        int sum2 = arrayCoins[3] + arrayCoins[4] + arrayCoins[5];
        int sum3 = arrayCoins[6] + arrayCoins[7] + arrayCoins[8];
        //compare group 1 and group 2, if its greater then the heavier is in group 1
        if (sum1 > sum2){
            //compare 1st coin and 2nd coin in group, if its heavier return 1 as the fake one is the first coin
            if (arrayCoins[0] > arrayCoins[1]){
                return 1;
            }
            //if the first coin is lighter than the second coin then return 2 as the fake one is the second coin
            else if (arrayCoins[0] < arrayCoins[1]){
                return 2;
            }
            //else they are equal which means the last coin is the heavier one so return 3
            else{
                return 3;
            }
        }
        //compare group 1 and group 2, if its less then the heavier is in group 2
        else if (sum1 < sum2){
            //compare 1st coin and 2nd coin in group, if its heavier return 4 as the fake one is the first coin
            if (arrayCoins[3] > arrayCoins[4]){
                return 4;
            }
            //if the first coin is lighter than the second coin then return 5 as the fake one is the second coin
            else if (arrayCoins[3] < arrayCoins[4]){
                return 5;
            }
            //else they are equal which means the last coin is the heavier one so return 6
            else{
                return 6;
            }
        }
        //else last group has the heavier coin
        else{
            //compare 1st coin and 2nd coin in group, if its heavier return 7 as the fake one is the first coin
            if (arrayCoins[6] > arrayCoins[7]){
                return 7;
            }
            //if the first coin is lighter than the second coin then return 8 as the fake one is the second coin
            else if (arrayCoins[6] < arrayCoins[7]){
                return 8;
            }
            //else they are equal which means the last coin is the heavier one so return 9
            else{
                return 9;
            }
        }

    }
    /*
    Suppose we now have an integer n (that represents n coins) and
    only one of the coins is heavier than the others. Suppose further
    that n is a power of 3 and you are allowed log3 n weighings to
    determine the heavier coin. Write an algorithm that solves this
    problem. Determine the time complexity of your algorithm.
     */
    public static int sort2(int[] arrayCoins, int start, int end){
        //get the number of coins
        //split coins into 3 groups
        int groupSize = (end+1-start)/3;
        //base case if groupSize is 1 compare 3 coins in group
        if (groupSize == 1){
            if (arrayCoins[start] > arrayCoins[start+1]){
                //return first coin in group plus 1 for 1-base indexing
                return start+1;
            }
            else if (arrayCoins[start] < arrayCoins[start+1]){
                //return second coin in group plus 1 for 1-base indexing
                return start+2;
            }
            else{
                //return third coin in group plus 1 for 1-base indexing
                return start+3;
            }

        }
        //recursive case, first get weights of all three groups
        else{
            int groupOne = getWeight(arrayCoins, start, start+groupSize-1);
            int groupTwo = getWeight(arrayCoins, start+groupSize, start+(2*groupSize)-1);
            //if groupOne has a higher weight then call sort again with that smaller group
            if (groupOne > groupTwo){
                return sort2(arrayCoins, start, start+groupSize-1);
            }
            else if (groupOne < groupTwo){
                return sort2(arrayCoins, start+groupSize, start+(2*groupSize)-1);
            }
            else{
                return sort2(arrayCoins, start+(2*groupSize), end);
            }


        }

    }
    public static int getWeight(int[] coinArray, int start, int end){
        int weight = 0;
        //loop through to find weights
        for (int i = start; i<=end;i++){
            weight += coinArray[i];

        }
        return weight;
    }

    public static boolean searchValue(int[][] array, int value, int startRow, int startCol, int endRow, int endCol) {
        //base case - nothing to search therefore value is not in array
        if (startRow > endRow || startCol > endCol) {
            return false;
        }
        //find middle row and column
        int middleRow = (startRow + endRow) / 2;
        int middleCol = (startCol + endCol) / 2;
        //set value we are checking at the middle of the array
        int target = array[middleRow][middleCol];
        //base case - found value
        if (target == value) {
            return true;
        }
        else {
            if (value > target) {
                //search bottom left, bottom right, top right
                return searchValue(array, value, middleRow+1, startCol, endRow, middleCol) ||
                        searchValue(array, value, middleRow, middleCol+1, endRow, endCol) ||
                        searchValue(array, value, startRow, middleCol+1, middleRow-1, endCol);
            } else  {
                //search top left, bottom left, top right
                return searchValue(array, value, startRow, startCol, middleRow-1, middleCol-1) ||
                        searchValue(array, value, middleRow, startCol, endRow, middleCol-1) ||
                        searchValue(array, value, startRow, middleCol, middleRow-1, endCol);
            }
        }
    }

}