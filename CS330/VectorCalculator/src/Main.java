/*Documentation: Asked C2C Kayla Kim for in class concepts/hints that I missed. Looked up common commands on tutorialspoint
                 and referenced class slides and example code. */
import java.util.Scanner;
/******************************************************************
 * Main - Top level class to initiate scanner and run VectorCalculator
 *
 * @author  Caleb Song
 *
 */
public class Main {
    /******************************************************************
     * main() - Initiates Scanner linked to System.in and passes to VectorCalc
     *
     * @param args NOT USED
     */
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        VectorCalculator.VectorCalc(s);
    }
}
