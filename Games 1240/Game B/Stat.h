/**
 * Stat class
 * Represents the statistics that will be kept 
 * track of in an SD card file
 * 
 * @author Dylan Sussman
 */

class Stat {
private:
    /**
     * Represents the time that it took the user
     * to complete the game
     */
    int time;
    /**
     * Represents that amount of squares that the user
     * clicked to win the game
     */
    int squaresClicked;
    /**
     * Represents the difficulty that the user
     * chose to play the game at
     */
    int difficulty;
public:
    /**
     * Constructor for a Stat object
     */
    Stat(int t = 0, int sqClicked = 0, int diff = 0);
    /**
     * Returns the time
     */
    int getTime();
    /**
     * Sets the time
     */
    void setTime(int t);
    /**
     * Returns the squaresClicked
     */
    int getSquaresClicked();
    /**
     * Sets squaresClicked
     */
    void setSquaresClicked(int sqClicked);
    /**
     * Returns difficulty
     */
    int getDifficulty();
    /**
     * Sets the difficulty
     */
    void setDifficulty(int diff);
};