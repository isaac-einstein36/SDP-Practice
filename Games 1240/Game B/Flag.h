/**
 * Flag class
 * Represents a flag
 * Only has two private variables – xCoord and yCoord
 * Only has three public functions – constructor, getXCoord, and getYCoord
 * Flagging certain squares allows the user to keep track of where tehy believe mines are located.
 * 
 * @author Zach Palmer
 */

class Flag {
private:
     /**
     * Indicates the xCoord of the top left corner
     * of the square that it's in
     */
    int xCoord;
    /**
     * Indicates the yCoord of the top left corner
     * of the sqaure that it's in
     */
    int yCoord;
public:
    /**
     * Contructor to initialize the position
     * of the flag
     */
    Flag(int x = 0, int y = 0);
    /**
     * Returns the xCoord
     */
    int getXCoord();
    /**
     * Returns the yCoord
     */
    int getYCoord();
    /**
    * Draws a flag
    */
    void drawFlag();

};
