import java.util.Scanner;
/******************************************************************
 * VectorCalculator - Command Line Vector Calculator
 *
 * @author  Caleb Song
 *
 */
public class VectorCalculator {
    /******************************************************************
     * VectorCalc() - Initiates and runs Vector Calculator on infinite loop until user inputs exit
     * @param s - Scanner to read user input from
     */
    public static void VectorCalc(Scanner s){
        //while user does not input keep going
        boolean keepGoing = true;
        while (keepGoing) {
            try {
                //Have user input expression
                System.out.print("Enter vector expression: ");
                String cmdLine = s.nextLine();
                //if user inputs exit, exit the program
                if (cmdLine.equalsIgnoreCase("exit")) {
                    keepGoing = false;
                } else {
                    Scanner cs = new Scanner(cmdLine);
                    //parse the expression to determine what to do
                    parseExpression(cs);
                    cs.close();
                }
                //if there are error messages later based on the parse it will catch at top level here
            } catch (Exception e) {
                System.out.println("ERROR:" + e.getMessage());
            }
        }
        System.out.println("Thank you for using the Vector Calculator. Goodbye.");
    }
    /******************************************************************
     * parseExpression() - Looks at first token and splits off into different methods
     * @param s - Scanner to read user input from
     */
    private static void parseExpression(Scanner s){
        //Magnitude token
        if (s.hasNext("\\|")){
            s.next("\\|");
            parseNormExpression(s);

        }
        //Token for addition, subtraction, and dot product
        else if (s.hasNext("<")) {
            parseVectorExpression(s);
        }
        //Token for scale
        else if (s.hasNextDouble()){
            parseScaleExpression(s);
        }
        //Token for direction
        else if (s.hasNext("dir")){
            s.next("dir");
            parseDirectionExpression(s);
        }
        //Token for normalize
        else if (s.hasNext("unit")){
            s.next("unit");
            parseNormalizeExpression(s);
        }
        else{
            throw new IllegalArgumentException("Did not enter valid input of |, unit, dir, <, or a number");
        }

    }
    /******************************************************************
     * parseDirectionExpression() - Parses vector and gets direction
     * @param s - Scanner to read user input from
     */
    private static void parseDirectionExpression(Scanner s){
        //parse the vector
        Vector330 expression = Vector330.parseVector(s);
        //Angle in radians
        double angleRad = expression.direction();
        //Angle in degrees
        double angleDeg = angleRad * (180/Math.PI);
        System.out.printf("Result is %.5f radians (%.5f degrees)\n",angleRad,angleDeg);
    }
    /******************************************************************
     * parseNormalizeExpression() - Parse Vector and normalize
     * @param s - Scanner to read user input from
     */
    private static void parseNormalizeExpression(Scanner s){
        //parse vector
        Vector330 expression = Vector330.parseVector(s);
        //Normalize the vector
        expression = expression.normalize();
        System.out.println("Result is < "+expression.getVectorX()+", "+expression.getVectorY()+" >");
    }
    /******************************************************************
     * parseNormExpression() - Parse Vector and get magnitude
     * @param s - Scanner to read user input from
     */
    private static void parseNormExpression(Scanner s){
        //parse vector
        Vector330 expression = Vector330.parseVector(s);
        //get magnitude
        double mag = expression.magnitude();
        if (s.hasNext("\\|")){
            System.out.printf("Result is %.5f\n",mag);
        }
        else{
            throw new IllegalArgumentException("Does not have | at end of expression");
        }
    }
    /******************************************************************
     * parseScaleExpression() - Parse vector and scale it up based on the double
     * @param s - Scanner to read user input from
     */
    private static void parseScaleExpression(Scanner s){
        //get the double to scale up by
        double scale = s.nextDouble();
        if (s.hasNext("[*]")){
            s.next("[*]");
        }
        else{
            throw new IllegalArgumentException("Invalid expression");
        }
        //parse the vector
        Vector330 expression = Vector330.parseVector(s);
        //scale the vector
        expression = expression.scale(scale);
        System.out.println("Result is < "+expression.getVectorX()+", "+expression.getVectorY()+" >");
    }
    /******************************************************************
     * parseVectorExpression() - Parses vector and adds, subtracts, or dot products based on operator
     * @param s - Scanner to read user input from
     */
    private static void parseVectorExpression(Scanner s){
        double result;
        //parse 1st vector
        Vector330 expression = Vector330.parseVector(s);
        //find what operator
        String operator;
        if (s.hasNext("[+-.]")){
            operator = s.next("[+-.]");
        }
        else{
            throw new IllegalArgumentException("Invalid operator");
        }

        //parse 2nd vector
        Vector330 expression2 = Vector330.parseVector(s);
        //if + its add
        if (operator.equals("+")){
            expression.addTo(expression2);
            System.out.println("Result is < "+expression.getVectorX()+", "+expression.getVectorY()+" >");
        }
        //if - subtract
        else if (operator.equals("-")){
            expression = expression.subtract(expression2);
            System.out.println("Result is < "+expression.getVectorX()+", "+expression.getVectorY()+" >");
        }
        //if . dot product
        else if (operator.equals(".")){
            result = expression.dotProduct(expression2);
            System.out.println("Result is "+result);
        }
    }

}

