import java.awt.*;
import java.util.Random;

/***************************************************************************
 * DemoTrominos - simple program for tiling a 2^k x 2^k board with Trominos
 *
 * YOU JUST NEED TO FINISH THE CODE FOR THE containsForbidden() AND doTiling() METHODS
 *
 * Author:  Caleb Song
 *
 */
public class CS380_HW3_TrominosTemplate {

    /************************************************************************
     * main() - randomly places the forbidden tile, creates an TrominoTiling
     *    object of the specified size with the forbidden tile, and solves
     *    the tiling.
     */
    public static void main(String[] args) {

        int SIZE = 32;    // must be a power of 2

        // randomly place the forbidden tile

        Random rand = new Random();

        int forbiddenRow = rand.nextInt(SIZE);
        int forbiddenCol = rand.nextInt(SIZE);

        // create the TrominoTiling object

        TrominoTiling myTrominos = new TrominoTiling(SIZE,
                forbiddenRow, forbiddenCol);

        myTrominos.solve();  // solve the tiling

    }  // end main()

} // end DemoTrominos class

/***************************************************************************
 * TrominoTiling class - a tiling solution using Trominos with graphical
 *    presentation.
 */
class TrominoTiling {

    private final int BOARD_SIZE = 512;  // size of the graphic window

    private int cellSize;  // cell size based upon board size and # of cells

    private boolean trominoBoard[][];  // tracks open versus forbidden cells

    private int size;  // number of cell rows (and columns), must be power of 2

    private DrawingPanel panel;  // Drawing panel for graphical display
    private Graphics2D g;        // Graphics2D object for drawing

    private Random rand = new Random();  // Random object for random colors

    /***********************************************************************
     * TrominoTiling constructor - sets size and forbidden cell location
     */
    TrominoTiling( int size, int forbiddenRow, int forbiddenCol ) {

        this.setSize(size);  // set the size

        // set cell size based upon board size and number of cells

        this.cellSize = this.BOARD_SIZE / this.getSize();

        // allocate the underlying 2D array

        this.trominoBoard = new boolean[this.getSize()][this.getSize()];

        // place the forbidden cell

        this.setForbiddenCell(forbiddenRow,forbiddenCol);

    }

    /***********************************************************************
     * setSize() - sets the number of rows (and columns).  Must be a power
     *    of 2 between 2 and 512.
     *
     * @throws - Throws IllegalArgumentException if size is not a power of
     *           two between 2 and 512.
     */
    void setSize( int newSize ) {

        if ( (newSize == 2) || (newSize == 4) || (newSize == 8) ||
                (newSize == 16) || (newSize == 32) || (newSize == 64) ||
                (newSize == 128) || (newSize == 256) || (newSize == 512) ) {
            this.size = newSize;
        } else {
            throw new IllegalArgumentException(
                    "Board size must be a power of 2.");
        }
    }  // end setSize()

    /***********************************************************************
     * getSize() - getter method for size attribute
     */
    int getSize() { return this.size; }

    /***********************************************************************
     * setForbiddenCell() - sets the location of the forbidden cell
     *
     * @throws - IllegalArgumentException if location is not on the board
     */
    void setForbiddenCell( int row, int col ) {

        if ( (row < 0) || (row >= this.getSize()) ) {
            throw new IllegalArgumentException(
                    "Forbidden row value must be on the board.");
        }

        if ( (col < 0) || (col >= this.getSize()) ) {
            throw new IllegalArgumentException(
                    "Forbidden col value must be on the board.");
        }

        this.trominoBoard[row][col] = true;  // set true for forbidden

    } // end setForbiddenCell()

    /***********************************************************************
     * solve() - top-level method for solving the Tromino tiling.  Creates
     *    the graphical representation and shows the grid.  Then calls the
     *    recursive doTiling() method to create the tiling.
     */
    void solve() {

        // establish the graphical display

        this.panel = new DrawingPanel( this.BOARD_SIZE, this.BOARD_SIZE );
        this.panel.setBackground(Color.WHITE);
        this.g = panel.getGraphics();
        this.g.setColor(Color.BLACK);

        // draw the grid

        for(int x=this.cellSize; x<this.BOARD_SIZE; x += this.cellSize)
            for(int y=this.cellSize; y<this.BOARD_SIZE; y += this.cellSize)
            {
                g.drawLine(x,0,x,this.BOARD_SIZE-1);
                g.drawLine(0,y,this.BOARD_SIZE-1,y);
            }

        panel.copyGraphicsToScreen();  // display the grid

        // tile the entire board using this recursive routine

        doTiling( 0, this.getSize()-1, 0, this.getSize()-1 );

    } // end solve()

    /***********************************************************************
     * containsForbidden() - checks the sub-grid of [startRow..endRow] X
     *    [startCol..endCol] to see if it contains a forbidden cell
     */
    boolean containsForbidden( int startRow, int endRow,
                               int startCol, int endCol ) {

        boolean hasForbidden = false;  // assume no forbidden

        // YOUR CODE GOES HERE
        for (int i = startRow; i <= endRow; i++){
            for (int j = startCol; j <= endCol; j++){
                if (trominoBoard[i][j] == true) {
                    hasForbidden = true;
                    return hasForbidden;
                }
            }
        }

        return hasForbidden;  // return results

    } // end containsForbidden()

    /***********************************************************************
     * doTiling() - main recursive method that implements the divide-and-
     *    conquer algorithm for doing the tiling.
     */
    void doTiling( int startRow, int endRow, int startCol, int endCol ) {

        // set a random color for this tromino

        Color trominoColor = new Color(rand.nextInt(255),
                rand.nextInt(255),rand.nextInt(255));

        int size = (endRow+1)-startRow;  // determine sub-grid size

        // YOUR CODE CODES HERE

        int middleRow = (startRow+endRow)/2;
        int middleCol = (startCol+endCol)/2;

        if (size == 1){
            g.setColor(Color.BLACK);
            g.fillRect(startCol*cellSize, startRow*cellSize, cellSize, cellSize);
        }
        else{
            //top right
            if (containsForbidden(startRow,middleRow, middleCol+1,endCol)){
                doTiling(startRow,middleRow,middleCol+1,endCol);
            }
            else{
                setForbiddenCell(middleRow,middleCol+1);
                doTiling(startRow,middleRow,middleCol+1,endCol);
                g.setColor(trominoColor);
                g.fillRect((middleCol+1)*cellSize, middleRow*cellSize, cellSize, cellSize);
                panel.copyGraphicsToScreen();
            }
            //top left
            if (containsForbidden(startRow,middleRow, startCol,middleCol)){
                doTiling(startRow,middleRow, startCol,middleCol);
            }
            else{
                setForbiddenCell(middleRow,middleCol);
                doTiling(startRow,middleRow, startCol,middleCol);
                g.setColor(trominoColor);
                g.fillRect(middleCol*cellSize, middleRow*cellSize, cellSize, cellSize);
                panel.copyGraphicsToScreen();
            }
            //bottom left
            if (containsForbidden(middleRow+1,endRow, startCol,middleCol)){
                doTiling(middleRow+1,endRow, startCol,middleCol);
            }
            else{
                setForbiddenCell(middleRow+1,middleCol);
                doTiling(middleRow+1,endRow, startCol,middleCol);
                g.setColor(trominoColor);
                g.fillRect((middleCol)*cellSize, (middleRow+1)*cellSize, cellSize, cellSize);
                panel.copyGraphicsToScreen();
            }
            //bottom right
            if (containsForbidden(middleRow+1,endRow, middleCol+1,endCol)){
                doTiling(middleRow+1,endRow, middleCol+1,endCol);
            }
            else{
                setForbiddenCell(middleRow+1,middleCol+1);
                doTiling(middleRow+1,endRow, middleCol+1,endCol);
                g.setColor(trominoColor);
                g.fillRect((middleCol+1)*cellSize, (middleRow+1)*cellSize, cellSize, cellSize);
                panel.copyGraphicsToScreen();
            }
        }

    } // end doTiling()

} // end TrominoTiling class