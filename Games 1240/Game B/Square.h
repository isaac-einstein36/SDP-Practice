/**
 * Square Class
 * Represents a square object which is what each space on the board is covered with
 * Each square can be clicked on and beneath is it has either a mine or it doesn't
 * If it doesn't have a mine then beneath the square is a number representing
 * the number of mines adjacent to that square
 * 
 * @author Dylan Sussman
 */
class Square {
private:
    /**
     * Indicates whether the square conatains a mine
     * True if contains a mine, false if it doesn't
     */
    bool mine;
    /**
     * Indicates whether the square has been revealed
     * True if revealed, false if not
     */
    bool revealed;
    /**
     * Indicates whether the square has been flagged
     * True if flagged, false if not
     */
    bool flagged;
    /**
     * Indicates the number of adjacent mines
     * -1 if the square contains a mine
     */
    int value;
    /**
     * Indicates the x coordinate of the top left corner
     */
    int xCoord;
    /**
     * Indicates the y coordinate of the top left corner
     */
    int yCoord; 
public:
    /**
     * Constructor for square object
     * Revealed and flagged don't need to be parameters because
     * when a new square is created they must both be false
     * Value can't be a parameter because when a square 
     * is created it doesn't necessarily know who all 
     * of its neighbors are
     */
    Square(int x = 0, int y = 0, bool mine = false);
    /**
     * Returns the x coordinate of the top left corner
     * of the square
     */
    int getXCoord();
    /**
     * Returns the y coordinate of the top left corner
     * of the square
     */
    int getYCoord();
    /**
     * Returns the mine variable
     */
    bool getMine();
    /**
     * Returns the value variable 
     */
    int getValue();
    /**
     * Sets the value variable to the int
     * dictated by the parameter
     */
    void setValue(int v);
    /**
     * Returns the revealed variable
     */
    bool getRevealed();
    /**
     * Sets the revealed variable to the state
     * dictated by the parameter
     */
    void setRevealed(bool r);
    /**
     * Returns the flagged variable
     */
    bool getFlagged();
    /**
     * Sets the flagged variabled to the state
     * dictated by the parameter
     */
    void setFlagged(bool f);
};