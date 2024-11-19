import static java.lang.Math.min;

public class Main {
    public static void main(String[] args) {
        System.out.println("Hello world!");
        long startTime;
        double actualTime;
        System.out.println("1st binary algorithm");
        for (int i = 10; i < 31; i++){
            startTime = System.nanoTime();
            bin(i,i/2);
            actualTime = (System.nanoTime() - startTime) / 1.0E09;
            System.out.println(actualTime);

        }
        System.out.println("2nd binary algorithm");
        for (int i = 10; i < 31; i++){
            startTime = System.nanoTime();
            bin2(i,i/2);
            actualTime = (System.nanoTime() - startTime) / 1.0E09;
            System.out.println(actualTime);
        }

        int[] testArray = { 14, 3, -18, 12, 6, -2, 8, 13, 21, -52, 4, 9, 21, 5 };
        int[] testArray2 = {-2, -3, 4, -1, -2, 1, 5, -3};
        max(testArray2);


    }
    public static int bin (int n, int k){
        //if k is 0 or n is equal to k on the choose function return 1
        if (k == 0 || n == k){
            return 1;
        }
        //else recursively run the next choose values decreasing by 1
        else{
            return bin(n-1,k-1)+bin(n-1,k);
        }
    }
    public static int bin2 (int n, int k){
        //create an array for the intermedaite values
        int[][] B = new int [n+1][k+1];
        //loop through all values in array
        for (int i = 0; i<=n;i++){
            for (int j = 0; j <= min(i,k); j++){
                //set equal to 1 if j is 0 or if j and i are equal
                if (j == 0 || j == i){
                    B[i][j] = 1;
                }
                //else set B[i][j] equal to previous value + value to left in array
                else{
                    B[i][j] = B[i-1][j-1] + B[i-1][j];
                }
            }
        }
        //return index in array for choose function
        return B[n][k];
    }
    public static void max(int[] array){
        //create sum array to track sums of previous values
        int[] sum = new int [array.length];
        //create index array to keep track of indices
        int[] indexArray = new int [array.length];
        //index to track previous index
        int index = 1;
        //keep track of max sum
        int max = array[0];
        //keep track of max index
        int indexMax = 0;
        //set first sum value in array to first value of array
        sum[0] = array[0];
        //set first index to first index of array
        indexArray[0] = 0;
        for (int i = 1; i < array.length; i++){
            //if array value is less than the array value + previous sum then set sum at that index to array value
            //+ previous sum
            if (array[i] < array[i] + sum[i-1]){
                sum[i] = array[i] + sum[i-1];

            }
            //else set sum equal to array value and set the index to the one in the array
            else {
                sum[i] = array[i];
                index = i;

            }
            //set index to the index saved
            indexArray[i] = index;
            //check to see if sum is max and then set values
            if (sum[i] > max){
                max = sum[i];
                indexMax = i;
            }
        }
        //print out results
        System.out.println("Sum: " + max);
        System.out.println("Start index: " + index);
        System.out.println("End index: " + indexMax);

    }
}