import java.util.regex.Pattern;
/******************************************************************
 * Vector330 - 2D vector and various operations
 *
 * @author  Caleb Song
 *
 */
public class Vector330 {
     /**
     * Tolerance to test equality of floating point numbers
     */
    private static final double TOLERANCE = 1.0E-09;
     /**
     * x component/coordinate of vector
     */
    private double x;
     /**
     * y component/coordinate of vector
     */
    private double y;

    //Constructors

     /******************************************************************
     * Vector330() - 0 argument constructor
     *
     */
    public Vector330(){
        this.x = 0;
        this.y = 0;
    }
     /******************************************************************
     * Vector330() - 2 argument constructor for x and y component
     * @param num1 x component/coordinate of vector
     * @param num2 y component/coordinate of vector
     */
    public Vector330(double num1, double num2){
        this.x = num1;
        this.y = num2;
    }
     /******************************************************************
     * setVectorX() - Sets x component of vector using double
     * @param newX  new value for x component/coordinate of vector
     */
    public void setVectorX(double newX){
        this.x = newX;
    }
     /******************************************************************
     * setVectorY() - Sets Y component of vector using double
     * @param newY  new value for y component/coordinate of vector
     */
    public void setVectorY(double newY){
        this.y = newY;
    }
     /******************************************************************
     * getVectorX() - gets x component of vector
      * @return double of x component
     */
    public double getVectorX(){
        return this.x;
    }
     /******************************************************************
     * getVectorY() - gets y component of vector
      * @return double of y component
     */
    public double getVectorY(){
        return this.y;
    }
     /******************************************************************
     * equals() - Equality return true if equal, return false if not equal
     * @param otherV - other vector passed in
      * @return boolean true if equal false if not equal
     */
    public boolean equals(Vector330 otherV){
        //subtract current from other for both x and y components
        double compareX = this.getVectorX() - otherV.getVectorX();
        double compareY = this.getVectorY() - otherV.getVectorY();
        //compare based on the tolerance because they are floating point numbers
        if (compareX < TOLERANCE && compareX > -TOLERANCE && compareY < TOLERANCE && compareY > -TOLERANCE){
            return true;
        }
            return false;
    }
     /******************************************************************
     * add() - Adds passed in vector to current vector to create a new vector
     * @param otherV - other vector passed in
      * @return Vector330 vector
     */
    public Vector330 add(Vector330 otherV){
        //Add x and y components together and return a new vector
        return new Vector330(this.getVectorX() + otherV.getVectorX(), this.getVectorY() + otherV.getVectorY());
    }

     /******************************************************************
     * addTo() - Adds passed in vector to current vector and stores in current vector
     * @param otherV - other vector passed in
     */
   public void addTo(Vector330 otherV){
       //Set the current vector to the sum of the other vector and current vector
        this.setVectorX(this.getVectorX() + otherV.getVectorX());
        this.setVectorY(this.getVectorY() + otherV.getVectorY());
   }
     /******************************************************************
     * subtract() - Subtracts passed in vector to current vector to create a new vector
     * @param otherV - other vector passed in
      * @return Vector330 vector
     */
   public Vector330 subtract(Vector330 otherV){
       //create new vector by subtracting current from other for both components
       return new Vector330(this.getVectorX() - otherV.getVectorX(), this.getVectorY() - otherV.getVectorY());

   }
     /******************************************************************
     * dotProduct() - Computes dot product of current and passed in vector
     * @param otherV - other vector passed in
      * @return double dot product result
     */
    public double dotProduct(Vector330 otherV){
        //Multiply x components and y components and add the results and return the double
        return ((this.getVectorX() * otherV.getVectorX()) + (this.getVectorY() * otherV.getVectorY()));
    }
     /******************************************************************
     * scale() - scales up current vector by a double amount
     * @param scaleFactor - scale factor to scale vector by
      * @return Vector330 scaled up vector
     */
    public Vector330 scale(double scaleFactor){
        //create a new vector by multiplying the x and y component by the scale factor
        return new Vector330(this.getVectorX()*scaleFactor, this.getVectorY()*scaleFactor);

    }
     /******************************************************************
     * magnitude() - Computes magnitude of vector
      * @return double with magnitude
     */
    public double magnitude(){
        //Return the sqrt after adding the squares of the x and y component
        return Math.pow((Math.pow(this.x,2) + Math.pow(this.y,2)),.5);
    }
     /******************************************************************
     * direction() - Computes direction/orientation of vector in radians
      * @return double with direction of vector
     */
    public double direction(){
        //Return inverse tangent of y divided by x
       return Math.atan2(this.getVectorY(),this.getVectorX());
    }
     /******************************************************************
     * normalize() - Computes normalized vector of current vector (length one)
      * @return Vector330 of normalized vector
     */
    public Vector330 normalize(){
        //Get the magnitude of the vector
        double magnitude = this.magnitude();
        //If magnitude is 0 then return 0 vector
        if (magnitude <= TOLERANCE && magnitude >= -TOLERANCE){
            return new Vector330();
        }
        //Return a vector of magnitude 1 in same direction
        else{
            return new Vector330(this.getVectorX() * (1/magnitude), this.getVectorY() * (1/magnitude));
        }
    }
     /******************************************************************
     * toString() - Converts vector to String
      * @return String of vector expression
     */
    public String toString(){
        //Create a String of the vector with "<" "," and ">" and return it
        return ("< "+this.getVectorX()+", "+this.getVectorY()+" >");
    }
     /******************************************************************
     * parseVector() - Inputs a Scanner object with expected form {@literal <} 1.0, 2.0 {@literal >} spaces needed after {@literal <}, {@literal >}, and {@literal ,}
      * @param s - Scanner object to read input
      * @return Vector330 of parsed vector
     */
    public static Vector330 parseVector(java.util.Scanner s){
        Pattern originalPattern = s.delimiter();
        double x;
        double y;
        s.useDelimiter("[" + originalPattern + ",]");
        //Must start with < and have a proper space after
        if (s.hasNext("<")){
            s.next("<");
            //Must have a double
            if (s.hasNextDouble()){
                x = s.nextDouble();
                s.useDelimiter(originalPattern);
                //Must have a "," and a space after the x component
                if (s.hasNext(",")){
                    s.next(",");
                    //Must have a double for the y component
                    if (s.hasNextDouble()){
                        y = s.nextDouble();
                        //Must close with a >
                        if (s.hasNext(">")){
                            s.next(">");
                        }
                        else{
                            //If Vector does not end with a >
                            throw new IllegalArgumentException("Did not end with a >");
                        }

                    }
                    else{
                        //Not a valid number in the y or improper spacing
                        throw new IllegalArgumentException("Not a valid number in the y coordinate of the vector with a space after the coordinate");
                    }
                }
                else{
                    //No comma after the x or improper spacing
                    throw new IllegalArgumentException("No comma after the x coordinate with proper spacing before and after");
                }
            }
            else{
                //Not a valid x coordinate number
                throw new IllegalArgumentException("Not a valid number in the x coordinate of the vector");
            }
        }
        else{
            //Does not start with < or spacing is incorrect
            throw new IllegalArgumentException("Did not start with a < with a proper space after the <");
        }
        return new Vector330(x,y);
    }
}