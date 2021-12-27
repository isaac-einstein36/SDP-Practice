/**
 * Mine class
 * Represents a mine
 * Only has two private variables – xCoord and yCoord
 * Only has three public functions – constructor, getXCoord, and getYCoord
 * Might never be drawn but their "virtual" locations is vital
 * to the success of the game
 * 
 * @author Dylan Sussman
 */
class Mine {
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
     * of the mine
     */
    Mine(int x = 0, int y = 0);
    /**
     * Returns the xCoord
     */
    int getXCoord();
    /**
     * Returns the yCoord
     */
    int getYCoord();
    /**
     * Draws a mine
     */
    void drawMine();

};