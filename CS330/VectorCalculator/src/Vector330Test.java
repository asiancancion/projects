import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.util.Scanner;
import static org.junit.jupiter.api.Assertions.*;
/******************************************************************
 * Vector330 Tests - Unit Tests for Vector330 class
 *
 * @author  Caleb Song
 *
 */
public class Vector330Test {
    /**
     * Tolerance to test equality of floating point numbers
     */
    private static final double TOLERANCE = 1.0E-09;
    /**
     * First vector reference for testing
     */
    Vector330 a;
    /**
     * Second vector reference for testing
     */
    Vector330 b;
    /**
     * Third vector reference for testing
     */
    Vector330 c;
    /**
     * Fourth vector reference for testing
     */
    Vector330 d;
    /**
     * Fifth vector reference for testing
     */
    Vector330 e;
    /******************************************************************
     * setUp() - Set up values for test vectors for start of every unit test
     *
     */
    @BeforeEach
    void setUp(){
        a = new Vector330(4,4);
        b = new Vector330(2,2);
        c = new Vector330(2,2);
        d = new Vector330(4,3);
        e = new Vector330();
    }
    /******************************************************************
     * tearDown() - Disposal of test vectors at end of every unit test
     *
     */
    @AfterEach
    void tearDown(){
        a = null;
        b = null;
        c = null;
        d = null;
        e = null;
    }
    /******************************************************************
     * setVectorX() - test the setVectorX() setter method
     *
     */
    @Test
    void setVectorX() {
        //Set <4.0,4.0> vector to a <3.0,4.0> vector and test to see if it properly is set
        assertEquals(a.getVectorX(),4.0);
        a.setVectorX(3.0);
        assertEquals(a.getVectorX(),3.0);
    }
    /******************************************************************
     * setVectorY() - test the setVectorY() setter method
     *
     */
    @Test
    void setVectorY() {
        //Set <4.0,4.0> vector to a <4.0,3.0> vector and test to see if it properly is set
        assertEquals(a.getVectorY(),4.0);
        a.setVectorY(3.0);
        assertEquals(a.getVectorY(),3.0);
    }
    /******************************************************************
     * getVectorX() - test the setVectorX() getter method
     *
     */
    @Test
    void getVectorX() {
        //<4.0,4.0> vector get x coordinate
        assertEquals(a.getVectorX(),4.0);
    }
    /******************************************************************
     * getVectorY() - test the setVectorY() getter method
     *
     */
    @Test
    void getVectorY() {
        //<4.0,4.0> vector get Y coordinate
        assertEquals(a.getVectorY(),4.0);
    }
    /******************************************************************
     * equals() - test the equals() method
     *
     */
    @Test
    void equals(){
        //Test to compare <2.0,2.0> vector and <2.0,2.0> vector return true
        assertTrue(b.equals(c));
        //Test to compare <4.0,4.0> vector and <2.0,2.0> vector return false
        assertFalse(a.equals(c));
    }
    /******************************************************************
     * add() - test the add() method
     *
     */
    @Test
    void add(){
        //Adding <4.0,4.0> and <2.0,2.0> vectors and storing it in vector d which should hold <6.0,6.0>
        d = a.add(b);
        assertEquals(d.getVectorX(),6.0);
        assertEquals(d.getVectorY(),6.0);
    }
    /******************************************************************
     * addTo() - test the addTo() method
     *
     */
    @Test
    void addTo(){
        //Adding <4.0,4.0> and <2.0,2.0> vectors and storing it in the <4.0,4.0> vector which should hold <6.0,6.0>
        a.addTo(b);
        assertEquals(a.getVectorX(), 6.0);
        assertEquals(a.getVectorY(), 6.0);
    }
    /******************************************************************
     * subtract() - test the subtract() method
     *
     */
    @Test
    void subtract(){
        //Subtracting <2.0,2.0> and <2.0,2.0> vectors and storing result in new vector which should hold <0.0>
        d = b.subtract(c);
        assertEquals(d.getVectorX(),0.0);
        assertEquals(d.getVectorY(),0.0);
    }
    /******************************************************************
     * dotProduct() - test the dotProduct() method
     *
     */
    @Test
    void dotProduct(){
        //Dot product of <2.0,2.0> and <2.0,2.0> should return a double of 8
        double product = b.dotProduct(c);
        assertEquals(product, 8.0);
    }
    /******************************************************************
     * scale() - test the scale() method
     *
     */
    @Test
    void scale(){
        //Create a new vector of <2.0,2.0> scaled up by a magnitude of 4.0
        d = b.scale(4.0);
        assertEquals(d.getVectorX(),8.0);
        assertEquals(d.getVectorY(),8.0);
    }
    /******************************************************************
     * magnitude() - test the magnitude() method
     *
     */
    @Test
    void magnitude(){
        //Find magnitude of whole number
        double mag = d.magnitude();
        assertEquals(mag,5.0);
        //Find magnitude of floating point number
        mag = a.magnitude();
        assertEquals(mag, 5.656854249492381);
    }
    /******************************************************************
     * direction() - test the direction() method
     *
     */
    @Test
    void direction(){
        double angle = a.direction();
        assertEquals(angle,0.7853981633974483);

    }
    /******************************************************************
     * normalize() - test the normalize() method
     *
     */
    @Test
    void normalize(){
        //Set d to <4.0,4.0> with a magnitude of 1 in the same direction
        d = a.normalize();
        //Compare original angle with new angle
        double angleOriginal = a.direction();
        double angleNew = d.direction();
        //Show they equal the same thing
        assertEquals(angleOriginal,0.7853981633974483);
        assertEquals(angleNew,0.7853981633974483);
        //If magnitude of vector is 0 then it will return a zero vector
        d = e.normalize();
        assertEquals(d.getVectorX(),0);
        assertEquals(d.getVectorY(),0);
    }
    /******************************************************************
     * testToString() - test the toString() method
     *
     */
    @Test
    void testToString(){
        //Convert a vector of <4.0,4.0> to a string in a specific format of < 4.0, 4.0 >
        String testString = a.toString();
        assertEquals(testString,"< 4.0, 4.0 >");
    }
    /******************************************************************
     * forceParseException() - Helper method to test the parseVector() method with the error conditions
     * @param argument Vector expression to be passed in
     * @param errorMessage error message based on the Vector Expression
     */
    private void forceParseException(String argument, String errorMessage){
        try{
            Scanner s = new Scanner(argument);
            Vector330.parseVector(s);
            fail("Exception needed to be thrown for: " + argument);
        }catch(Exception e){
            assertEquals(errorMessage, e.getMessage());
        }
    }
    /******************************************************************
     * testParseVector() - Test parseVector() with good and bad inputs
     *
     */
    @Test
    void testParseVector(){
        Scanner s;
        //Test no space after the <
        forceParseException("<2.0, 2.0 >","Did not start with a < with a proper space after the <");
        //Test not starting with a <
        forceParseException("| 2.0, 2.0 >","Did not start with a < with a proper space after the <");
        //Test improper x coordinate
        forceParseException("< abc, 2.0 >","Not a valid number in the x coordinate of the vector");
        //Test no comma after the x coordinate
        forceParseException("< 2.0 2.0 >","No comma after the x coordinate with proper spacing before and after");
        //Test improper spacing after the comma
        forceParseException("< 2.0,2.0 >","No comma after the x coordinate with proper spacing before and after");
        //Test improper y coordinate
        forceParseException("< 2.0, abc >","Not a valid number in the y coordinate of the vector with a space after the coordinate");
        //Test improper spacing after y coordinate
        forceParseException("< 2.0, 2.0>","Not a valid number in the y coordinate of the vector with a space after the coordinate");
        //Test improper spacing after y coordinate
        forceParseException("< 2.0, 2.0 ","Did not end with a >");

        //Test valid input should return
        s = new Scanner("< 2.0, 2.0 >");
        d = Vector330.parseVector(s);
        assertEquals(d.getVectorX(),2.0);
        assertEquals(d.getVectorY(),2.0);

        s.close();
    }

}