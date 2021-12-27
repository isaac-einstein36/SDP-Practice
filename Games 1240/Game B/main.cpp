#include <string.h>
#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHSD.h"
#include "FEHUtility.h"
#include "Square.h"
#include "Mine.h"
#include "Flag.h"
#include "Stat.h"

using namespace std;

//Constants
#define GRID_ROWS 9
#define GRID_COLUMNS 16
#define SQUARE_SIDE 20
#define MAX_ADJACENT_SQUARES 8
#define TEXT_HEIGHT 20 
#define PLAY_REPLAY_YCOORD 94
#define PLAY_REPLAY_XCOORD 113
#define PLAY_REPLAY_WIDTH 94
#define INSTRUCTIONS_YCOORD 133
#define INSTRUCTIONS_XCOORD 113
#define INSTRUCTIONS_WIDTH 94
#define STATS_XCOORD 125
#define STATS_YCOORD 172
#define STATS_WIDTH 70
#define CREDITS_XCOORD 132
#define CREDITS_YCOORD 211
#define CREDITS_WIDTH 56
#define EASY_XCOORD 30
#define EASY_YCOORD 65
#define EASY_WIDTH 260
#define MEDIUM_XCOORD 15
#define MEDIUM_YCOORD 95
#define MEDIUM_WIDTH 290
#define HARD_XCOORD 30
#define HARD_YCOORD 125
#define HARD_WIDTH 260
#define SUPER_HARD_XCOORD 25
#define SUPER_HARD_YCOORD 155
#define SUPER_HARD_WIDTH 270
#define SUPER_HARD_HEIGHT 40
#define BACK_XCOORD 0
#define BACK_YCOORD 0
#define BACK_WIDTH 40
#define IN_GAME_YCOORD 0
#define IN_GAME_MAIN_MENU_XCOORD 0
#define IN_GAME_MAIN_MENU_WIDTH 90
#define IN_GAME_REPLAY_XCOORD 95
#define IN_GAME_REPLAY_WIDTH 55
#define IN_GAME_CLICK_XCOORD 162
#define IN_GAME_CLICK_WIDTH 40
#define IN_GAME_FLAG_XCOORD 210
#define IN_GAME_FLAG_WIDTH 35
#define MINES_LEFT_XCOORD 230
#define MINES_LEFT_YCOORD 27
#define MINES_LEFT_WIDTH 20
#define TIME_LEFT_XCOORD 82
#define TIME_LEFT_YCOORD 27
#define TIME_LEFT_WIDTH 30
#define EASY_TIME 300
#define EASY_MINES 25
#define MEDIUM_TIME 240
#define MEDIUM_MINES 30
#define HARD_TIME 180
#define HARD_MINES 35
#define SUPER_HARD_TIME 120
#define SUPER_HARD_MINES 40

//Function prototypes
void drawMenu();
void drawNewBoard(Square squares[GRID_ROWS][GRID_COLUMNS], int time, int numMines);
void displayInstructions();
void displayStats();
void displayCredits();
Mine createRandomMine();
int findAdjacentMines(Square sa[MAX_ADJACENT_SQUARES]);
bool redrawBoard(bool flag, bool click, Square *s, Square sm[GRID_ROWS][GRID_COLUMNS], int numMines);
void drawInGameMenu(int time, int mines);
void drawGridLines();
void revealAroundZeros(Square sa[MAX_ADJACENT_SQUARES], Square sm[GRID_ROWS][GRID_COLUMNS]);
void revealAdjacentZeros(Square s, Square sa[MAX_ADJACENT_SQUARES]);
void getAdjacentSquares(Square s, Square sm[GRID_ROWS][GRID_COLUMNS], Square *sa);
void endGame(Square sm[GRID_ROWS][GRID_COLUMNS], Square s);
void updateMinesLeft(int flags, int numMines);
bool updateTimeLeft(double time, Square sm[GRID_ROWS][GRID_COLUMNS], int totalTime, Square s);
int flagCount(Square sm[GRID_ROWS][GRID_COLUMNS]);
void drawInGameOptions();

/**
 * Entry point to the application.
 * 
 * @returns status code of program exit
 * 
 * @author Dylan Sussman and Zach Palmer
 */
int main() {
    //Declare variables
    int x = 0, y = 0, xCoord = 0, yCoord = 0, row = 0, col = 0, difficulty = 0, time = 0, numMines = 0;
    double startTime = 0, endTime = 0, timeDiff = 0;
    bool inMenu = true, inGame = false, inInstructions = false, inStats = false, inCredits = false, clicking = true, flagging = false, gameOver = false, gameStarted = false;
    bool won = false, lost = false, inGameOptions = false;
    Square squares[GRID_ROWS][GRID_COLUMNS];
    Stat statistics[6], currentGameStats;
    FEHFile* stats = SD.FOpen("GameStatistics.txt", "a");
    SD.FClose(stats);

    //Call drawMenu to begin and display the menu
    drawMenu();
    
    while (1) {
        /**
         * Waits for a touch
         * Reads in that touch as x and y
         */
        while(!LCD.Touch(&x, &y)) {
            /**
             * If the current screen is the menu display
             * Will always be tru at the start of the program
             */
            if (inMenu) {
                /**
                 * Determines which text was selected
                 * Uses constants and string length to 
                 * determine what was selected
                 */
                //Play/Replay was selected
                if(x >= PLAY_REPLAY_XCOORD && x <= PLAY_REPLAY_XCOORD + PLAY_REPLAY_WIDTH && y >= PLAY_REPLAY_YCOORD && y <= PLAY_REPLAY_YCOORD + TEXT_HEIGHT) {
                    drawInGameOptions();

                    inMenu = false;
                    inGameOptions = true;

                    //Reset x and y coordinates of click
                    x = 320;
                    y = 0;
                } 
                //Instructions was selected
                else if(x >= INSTRUCTIONS_XCOORD && x <= INSTRUCTIONS_XCOORD + INSTRUCTIONS_WIDTH && y >= INSTRUCTIONS_YCOORD && y <= INSTRUCTIONS_YCOORD + TEXT_HEIGHT) {
                    displayInstructions();
                    inMenu = false;
                    inInstructions = true;
                } 
                //Statistics was selected
                else if(x >= STATS_XCOORD && x <= STATS_XCOORD + STATS_WIDTH && y >= STATS_YCOORD && y <= STATS_YCOORD + TEXT_HEIGHT) { 
                    displayStats();
                    inMenu = false;
                    inStats = true;
                } 
                //Credits was selected
                else if(x >= CREDITS_XCOORD && x <= CREDITS_XCOORD + CREDITS_WIDTH && y >= CREDITS_YCOORD && y <= CREDITS_YCOORD + TEXT_HEIGHT) { 
                    displayCredits();
                    inMenu = false;
                    inCredits = true;
                }
            }

            //If the current screen is in the game display
            if(inGame) {
                //Main Menu was selected
                if(x >= IN_GAME_MAIN_MENU_XCOORD && x <= IN_GAME_MAIN_MENU_XCOORD + IN_GAME_MAIN_MENU_WIDTH && y >= IN_GAME_YCOORD && y <= IN_GAME_YCOORD + TEXT_HEIGHT){
                    drawMenu();
                    gameOver = false;
                    gameStarted = false;
                    won = false;
                    lost = false;

                    clicking = true;
                    flagging = false;

                    inGame = false;
                    inMenu = true;
                }

                //Replay was selected
                else if(x >= IN_GAME_REPLAY_XCOORD && x <= IN_GAME_REPLAY_XCOORD + IN_GAME_REPLAY_WIDTH && y >= IN_GAME_YCOORD && y <= IN_GAME_YCOORD + TEXT_HEIGHT){
                    // drawNewBoard(squares);
                    inGameOptions = true;
                    inGame = false;
                    won = false;
                    lost = false;
                    drawInGameOptions();

                    gameOver = false;
                    gameStarted = false;

                    clicking = true;
                    flagging = false;

                    //Reset coordinates of click to keep out of this else if after changes have been made
                    x = 320;
                    y = 0;
                }

                //Click was selected
                else if(x >= IN_GAME_CLICK_XCOORD && x <= IN_GAME_CLICK_XCOORD + IN_GAME_CLICK_WIDTH && y >= IN_GAME_YCOORD && y <= IN_GAME_YCOORD + TEXT_HEIGHT){
                    clicking = true;
                    flagging = false;
                }

                //Flag was selected
                else if(x >= IN_GAME_FLAG_XCOORD && x <= IN_GAME_FLAG_XCOORD + IN_GAME_FLAG_WIDTH && y >= IN_GAME_YCOORD && y <= IN_GAME_YCOORD + TEXT_HEIGHT){
                    clicking = false;
                    flagging = true;
                }

                //The board was selected
                else if(y >= 60 && !gameOver){
                    //Find the coordinates of the clicked square
                    xCoord = x - (x % 20);
                    yCoord = y - (y % 20);

                    //Find row and column of the square to correspond with matrix
                    row = yCoord/20 - 3;
                    col = xCoord/20;

                    gameOver = redrawBoard(flagging, clicking, &squares[row][col], squares, numMines);

                    if(gameOver) {
                        lost = true;
                    }

                    /**
                     * Determine if this was the first click
                     * No squares have been revealed or flagged until the first click
                     */
                    if (!gameStarted) {
                        for (int r = 0; r < GRID_ROWS; r++) {
                            for (int c = 0; c < GRID_COLUMNS; c++) {
                                if(squares[r][c].getRevealed() || squares[r][c].getFlagged()) {
                                    gameStarted = true;
                                }
                            }
                        }
                        startTime = TimeNow();
                    }

                    //Reset coordinates of click to keep out of this else if after changes have been made
                    x = 320;
                    y = 0;

                    /**
                     * Check if every square with a mine is flagged
                     * b/c if so then the game is over and the user
                     * has won
                     * 
                     * Gameover will be set to false if a square
                     * with a mine is found not to be flagged 
                     * and so will won
                     * 
                     * Only check this if the game isn't already over
                     */
                    if(!gameOver) {
                        gameOver = true;
                        won = true;
                        for (int r = 0; r < GRID_ROWS; r++) {
                            for (int c = 0; c < GRID_COLUMNS; c++) {
                                if(squares[r][c].getMine()) {
                                    if(!squares[r][c].getFlagged()) {
                                        gameOver = false;
                                        won = false;
                                    }
                                }
                            }
                        }
                    }
                }

                /**
                 * Update the time and check to make
                 * sure that the user hasn't run out of time
                 */
                if (gameStarted && !gameOver) {
                    endTime = TimeNow();
                    timeDiff = endTime - startTime;

                    gameOver = updateTimeLeft(timeDiff, squares, time, squares[row][col]); 

                    if(gameOver) {
                        lost = true;
                    }
                }

                /**
                 * When game is over determine whether the 
                 * user won or lost and print a short message
                 * to the screen indicating so
                 */
                if(gameOver) {
                    LCD.SetFontColor(LCD.Green);
                    if(won) {
                        won = false;
                        
                        LCD.WriteAt("You Won :) You Won :) You Won :)", 0, 40);

                        /**
                         * Set all Stat objects in statistics array
                         * to a time of zero so that everything
                         * from the file is read in and organized
                         * correctly and the new stat gets added correctly
                          */
                        for(int i = 0; i < 6; i++) {
                            statistics[i].setTime(500);
                            statistics[i].setSquaresClicked(0);
                            statistics[i].setDifficulty(0);
                        }
                        
                        /**
                         * Write statistics from the game that was just played
                         * out to the file that keeps track of statistics
                         * 
                         * Stats can only be written out if the user won the game
                         */
                        FEHFile* stats  = SD.FOpen("GameStatistics.txt", "r");
                        
                        /**
                         * Read in data from file first in order to determine 
                         * whether the game that was just completed should be added to the leaderboard
                         */
                        for (int i = 0; i < 5; i++) {
                            if (!SD.FEof(stats)) {
                                int t = 500, sq = 0, diff = 0;
                                SD.FScanf(stats, "%d%d%d", &t, &sq, &diff);

                                if(!SD.FEof(stats)) {
                                    Stat temp(t, sq, diff);
                                    statistics[i] = temp;
                                }
                            }
                        }
                        SD.FClose(stats);

                        /**
                         * Update currentGameStats and then add
                         * it to the 6th element of the 
                         * statistics array so that it can be compared
                         * to the other statistics
                         */ 
                        currentGameStats.setTime(timeDiff);
                        
                        //Determine the number of squares clicked
                        int counter = 0;
                        for (int r = 0; r < GRID_ROWS; r++) {
                            for (int c = 0; c < GRID_COLUMNS; c++) {
                                if(squares[r][c].getRevealed() && !squares[r][c].getMine()) {
                                    counter++;
                                }
                            }
                        }
                        currentGameStats.setSquaresClicked(counter);

                        //Add currentGameStats to the statistics array
                        statistics[5] = currentGameStats;

                        /**
                         * Use a bubble sort to determine the new order of the
                         * stats now that the stats from the current game
                         * has been added to the array
                         * Array is sorted based on the time with the quickest time
                         * (smallest number) 1st
                         */                        
                        bool swap = true;
                        Stat temp;
                        while (swap) {
                            swap = false;

                            for (int i = 0; i < 5; i++) {
                                if(statistics[i].getTime() > statistics[i+1].getTime()) {
                                    temp = statistics[i];
                                    statistics[i] = statistics[i+1];
                                    statistics[i+1] = temp;
                                    swap = true;
                                }
                            }
                        }
                        
                        /**
                         * Now that the array is sorted, the first 5 values
                         * are the top 5 stats (based on their time) and those
                         * will be printed out to the file
                         */
                        FEHFile* statsW  = SD.FOpen("GameStatistics.txt", "w");

                        for(int i = 0; i < 5; i++) {
                            SD.FPrintf(statsW, "%d\t%d\t%d\n", statistics[i].getTime(), statistics[i].getSquaresClicked(), statistics[i].getDifficulty());
                        }
                        SD.FClose(statsW);

                    } 
                    if (lost) {
                        LCD.WriteAt("You Lost :( You Lost :( You Lost :(", 0, 40);
                    }
                }
                
            }

            if(inGameOptions) {
                //Main Menu button was selected
                if (x >= BACK_XCOORD && x <= BACK_XCOORD + IN_GAME_MAIN_MENU_WIDTH && y >= BACK_YCOORD && y <= BACK_YCOORD + TEXT_HEIGHT) {
                    inMenu = true;
                    inGameOptions = false;
                    drawMenu();
                }
                //Easy difficulty level was selected
                else if (x >= EASY_XCOORD && x <= EASY_XCOORD + EASY_WIDTH && y >= EASY_YCOORD && y <= EASY_YCOORD + TEXT_HEIGHT) {
                    inGame = true;
                    inGameOptions = false;

                    time = EASY_TIME;
                    numMines = EASY_MINES;

                    difficulty = 1;

                    drawNewBoard(squares, time, numMines);

                    currentGameStats.setDifficulty(difficulty);
                }
                //Medium difficulty level was selected
                else if (x >= MEDIUM_XCOORD && x <= MEDIUM_XCOORD + MEDIUM_WIDTH && y >= MEDIUM_YCOORD && y <= MEDIUM_YCOORD + TEXT_HEIGHT) {
                    inGame = true;
                    inGameOptions = false;

                    time  = MEDIUM_TIME;
                    numMines = MEDIUM_MINES;

                    difficulty = 2;

                    drawNewBoard(squares, time, numMines);

                    currentGameStats.setDifficulty(difficulty);
                }
                //Hard difficulty level was selected
                else if (x >= HARD_XCOORD && x <= HARD_XCOORD + HARD_WIDTH && y >= HARD_YCOORD && y <= HARD_YCOORD + TEXT_HEIGHT) {
                    inGame = true;
                    inGameOptions = false;

                    time = HARD_TIME;
                    numMines = HARD_MINES;

                    difficulty = 3;

                    drawNewBoard(squares, time, numMines);

                    currentGameStats.setDifficulty(difficulty);
                }
                //Super hard difficulty level was selected
                else if (x >= SUPER_HARD_XCOORD && x <= SUPER_HARD_XCOORD + SUPER_HARD_WIDTH && y >= SUPER_HARD_YCOORD && y <= SUPER_HARD_YCOORD + SUPER_HARD_HEIGHT) {
                    inGame = true;
                    inGameOptions = false;

                    time = SUPER_HARD_TIME;
                    numMines = SUPER_HARD_MINES;

                    difficulty = 4;

                    drawNewBoard(squares, time, numMines);

                    currentGameStats.setDifficulty(difficulty);
                }

                //Reset x and y coordinates so nothing on the new board is clicked
                x = 320;
                y = 0;
            }

            //If the currrent screen is displaying the instructions
            if(inInstructions) {
                //Check if the back button was pressed to know when to go back to main menu
                if (x >= BACK_XCOORD && x <= BACK_XCOORD + BACK_WIDTH && y >= BACK_YCOORD && y <= BACK_YCOORD + TEXT_HEIGHT) {
                    inMenu = true;
                    inInstructions = false;
                    drawMenu();
                }
            }

            //If the current screen is displaying the stats
            if(inStats) {
                //Check if the back button was pressed to know when to go back to main menu
                if (x >= BACK_XCOORD && x <= BACK_XCOORD + BACK_WIDTH && y >= BACK_YCOORD && y <= BACK_YCOORD + TEXT_HEIGHT) {
                    inMenu = true;
                    inStats = false;
                    drawMenu();
                }
            }

            //If the current screen is displaying the credits
            if(inCredits) {
                //Check if the back button was pressed to know when to go back to main menu
                if (x >= BACK_XCOORD && x <= BACK_XCOORD + BACK_WIDTH && y >= BACK_YCOORD && y <= BACK_YCOORD + TEXT_HEIGHT) {
                    inMenu = true;
                    inCredits = false;
                    drawMenu();
                }
            }
        }
    }
    return 0;
}

/**
 * Function to draw the main menu
 * Will be called at the beginning of the program
 * and any time the user selects to go back to the
 * main menu
 * 
 * @author Dylan Sussman
 */
void drawMenu() {
    LCD.Clear();

    //Set draw color to black and font color to white
    LCD.SetDrawColor(LCD.Black);
    LCD.SetFontColor(LCD.White);

    //Draw rectangle the size of the screen to act as the menu background
    LCD.FillRectangle(0, 0, 320, 240);

    //Write out options to menu screen
    LCD.WriteAt("Welcome to Minesweeper", 55, 26);
    LCD.WriteAt("Play/Replay", PLAY_REPLAY_XCOORD, PLAY_REPLAY_YCOORD);
    LCD.WriteAt("Instructions", INSTRUCTIONS_XCOORD, INSTRUCTIONS_YCOORD);
    LCD.WriteAt("Statistics", STATS_XCOORD, STATS_YCOORD);
    LCD.WriteAt("Credits", CREDITS_XCOORD, CREDITS_YCOORD);
}

/**
 * Function to draw a new board
 * Will be called whenever the user starts a new game
 * Once the program is running properly it will take
 * an SD card as a parameter to keep track of stats
 * 
 * @author Dylan Sussman and Zach Palmer
 */
void drawNewBoard(Square squares[GRID_ROWS][GRID_COLUMNS], int time, int numMines) {
    LCD.Clear();
    
    drawInGameMenu(time, numMines);

    /**
     * Generate mines at random locations
     * Will start with creating 25 mines
     * Once program is running properly there
     * will be a different number of mines for different
     * difficulty levels
     */
    Mine mines[numMines];
    bool inMines;
    int k = 0;
    while (k < numMines) {
        inMines = false;
        
        Mine m = createRandomMine();
        /**
         * Runs thru array and checks against mines that have
         * already been added to make sure non are repeated
         */
        for (int i = 0; i < k; i++) {
            if(m.getXCoord() == mines[i].getXCoord() && m.getYCoord() == mines[i].getYCoord()) {
                inMines = true;
            }
        }

        /**
         * Only adds m to mines if it's there is no mine at that location
         * And k only gets incremented when m is added
         */
        if(!inMines) {
            mines[k] = m;
            k++;
        }
    }

    /**
     * Before drawing the gridlines, create a 9 x 16
     * matrix to store all of the squares and then 
     * draw them on the board
     */
    int x = 0, y = 60;
    bool hasMine;
    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLUMNS; c++) {
            hasMine = false;
            /**
             * Go thru mines array to determine if there are 
             * any mines at the current location
             */
            for (int i = 0; i < numMines; i++) {
                if(mines[i].getXCoord() == x && mines[i].getYCoord() == y) {
                    hasMine = true;
                }
            }

            squares[r][c] = Square(x, y, hasMine);

            //Increment x by 20 to move across the column to next square
            x += 20;
        }

        //Reset x because starting new row and increment y by 20 for new column
        x = 0;
        y += 20;
    }

    /**
     * Assign a value to each square based on the number 
     * of mines adjacent to it
     */
    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLUMNS; c++) {
            Square adjacentSquares[MAX_ADJACENT_SQUARES];
            Square *s = &squares[r][c];
            getAdjacentSquares(*s, squares, adjacentSquares);

            /**
             * If the square contains a mine
             * then its value is -1
             */
            if(s->getMine()) {
                s->setValue(-1);
            } else {
                s->setValue(findAdjacentMines(adjacentSquares));
            }
        }
    }
    
    //Draw all of the squares on the game board
    LCD.SetDrawColor(LCD.Blue);
    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLUMNS; c++) {
            LCD.FillRectangle(squares[r][c].getXCoord(), squares[r][c].getYCoord(), SQUARE_SIDE, SQUARE_SIDE);
        }
    }
    
    drawGridLines();

    /**
     * All code below is checking that everything works properly
     * Will be commented out when code is working
     */

    // //Print location of each mine to a file to check that they are generate correctly
    // FEHFile* mineLoc = SD.FOpen("MineLoc.txt", "w");
    // for (int i = 0; i < numMines; i++) {
    //     SD.FPrintf(mineLoc, "Mine #%d: (%d, %d)\n", i+1, mines[i].getXCoord(), mines[i].getYCoord());
    // }
    // SD.FClose(mineLoc);

    // //Check to make sure that mines are generated correctly
    // for (int i = 0; i < numMines; i++) {
    //     mines[i].drawMine();
    // }  

    // /**
    //  * Print the value of the mine variable from each square to a file 
    //  * to make sure that the variable is initialized correctly when 
    //  * the squares are created
    //  */
    // FEHFile* squareHasMine = SD.FOpen("SquareHasMine.txt", "w");
    // for (int r = 0; r < GRID_ROWS; r++) {
    //     for (int c = 0; c < GRID_COLUMNS; c++) {
    //         Square s = squares[r][c];
    //         if(s.getMine()) {
    //             SD.FPrintf(squareHasMine, "Square(%d, %d) hasMine: true\n", s.getXCoord(), s.getYCoord());
    //         } else {
    //             SD.FPrintf(squareHasMine, "Square(%d, %d) hasMine: false\n", s.getXCoord(), s.getYCoord());
    //         }
            
    //     }
    // }
    // SD.FClose(squareHasMine);

    // //Print the value of each value variable from each Square to a file
    // FEHFile* squareValue = SD.FOpen("SquareValue.txt", "w");
    // for (int r = 0; r < GRID_ROWS; r++) {
    //     for (int c = 0; c < GRID_COLUMNS; c++) {
    //         Square s = squares[r][c];

    //         SD.FPrintf(squareValue, "Square(%d, %d) Value: %d\n", s.getXCoord(), s.getYCoord(), s.getValue());
    //     }
    // }
    // SD.FClose(squareValue);

    // //Draw the value variable on each square
    // LCD.SetFontColor(LCD.Red);
    // for (int r = 0; r < GRID_ROWS; r++) {
    //     for (int c = 0; c < GRID_COLUMNS; c++) {
    //         Square s = squares[r][c];
    //         if (s.getValue() != -1) {
    //             LCD.WriteAt(s.getValue(), s.getXCoord() + 5, s.getYCoord() + 5);
    //         }
    //     }
    // }  
}

/**
 * Function to display the instructions to the screen
 * Called when instructions is selected from the main screen
 * 
 * @author Zach Palmer
 */
 void displayInstructions() {
    LCD.Clear();

    //Set draw color to black and font color to white
    LCD.SetDrawColor(LCD.Black);
    LCD.SetFontColor(LCD.White);

    //Draw a rectangle to the whole screen and act as a background
    LCD.FillRectangle(0, 0, 320, 240);

    //Display the instructions
    LCD.WriteAt("Back", BACK_XCOORD, BACK_YCOORD);
    LCD.WriteAt("Minesweeper Instructions", 57, 26);
    LCD.WriteAt("1) Start: press any square in minefield", 0, 52);
    LCD.WriteAt("2) Flag squares that have mines beneath", 0, 72);
    LCD.WriteAt("3) Select flag icon to flag squares", 0, 92);
    LCD.WriteAt("4) Select cursor icon to clear squares", 0, 112);
    LCD.WriteAt("5) Click square to reveal mine or number", 0, 132);
    LCD.WriteAt("6) Number indicates adjacent mines", 0, 152);
    LCD.WriteAt("7) Revealing a mine will end game", 0, 172);
    LCD.WriteAt("Goal: clear all squares without", 0, 192);
    LCD.WriteAt("revealing a mine before time ends", 0, 212);
 }

 /**
  * Function to display the statistics of the game 
  * from the SD card
  * Once the program is running properly the function 
  * will take the SD card with the stored info
  * as a parameter
  * 
  * @author Dylan Sussman
  */
 void displayStats() {
     LCD.Clear();

     //Set draw color to black and font color to white
     LCD.SetDrawColor(LCD.Black);
     LCD.SetFontColor(LCD.White);

     //Draw a rectangle to whole screen to act as a background
     LCD.FillRectangle(0, 0, 320, 240);

     Stat statistics[5];
     char difficulty[30];

     FEHFile* stat = SD.FOpen("GameStatistics.txt", "r");

     for (int i = 0; i < 5; i++) {
         int t = 0, sq = 0, diff = 0;
         SD.FScanf(stat, "%d%d%d", &t, &sq, &diff);
         Stat temp(t, sq, diff);
         statistics[i] = temp;
     }

     SD.FClose(stat);

     //Display stats
     LCD.WriteAt("Back", BACK_XCOORD, BACK_YCOORD);
     LCD.WriteAt("Leaderboard", 110, 26);
     LCD.WriteAt("(Top 5 Fastest Completion Times)", 30, 46);
     LCD.WriteAt("   Time    # Squares Clicked   Difficulty", 0, 76);
     LCD.WriteLine("");
     LCD.WriteLine("");
     LCD.WriteLine("");
     LCD.WriteLine("");

     for (int i = 0; i < 5; i++) {
         //Determine the string for the difficulty level
         if(statistics[i].getDifficulty() == 1) {
             strcpy(difficulty, "Easy");
         } else if(statistics[i].getDifficulty() == 2) {
             strcpy(difficulty, "Medium");
         } else if(statistics[i].getDifficulty() == 3) {
             strcpy(difficulty, "Hard");
         } else if(statistics[i].getDifficulty() == 4) {
             strcpy(difficulty, "Super Hard");
         }

         //Determine the number ranking based on i
         if (i == 0) {
             LCD.Write("1) ");
         } else if (i == 1) {
             LCD.Write("2) ");
         } else if (i == 2) {
             LCD.Write("3) ");
         } else if (i == 3) {
             LCD.Write("4) ");
         } else if (i == 4) {
             LCD.Write("5) ");
         }

         //No stats yet
         if (statistics[i].getTime() > 300 || statistics[i].getTime() == 0) {
             LCD.WriteLine("No statistics avialable yet");
         } else {
            LCD.Write(statistics[i].getTime());
            if(statistics[i].getTime() < 100) {
                LCD.Write(" ");
            }
            if (statistics[i].getTime() < 10) {
                LCD.Write(" ");
            }
            LCD.Write("                     ");

            LCD.Write(statistics[i].getSquaresClicked());
            if(statistics[i].getSquaresClicked() < 100) {
                LCD.Write(" ");
            }
            if (statistics[i].getSquaresClicked()) {
                LCD.Write(" ");
            } 
            LCD.Write("                    ");

            LCD.WriteLine(difficulty);
         }
     }
 }

/**
 * Function to display the credits to the screen
 * Called when credits is selected from the main screen
 * 
 * @author Dylan Sussman
 */
void displayCredits() {
    LCD.Clear();

    //Set draw color to black and font color to white
    LCD.SetDrawColor(LCD.Black);
    LCD.SetFontColor(LCD.White);

    //Draw a rectangle to whole screen and act as a background
    LCD.FillRectangle(0, 0, 320, 240);

    //Display the credits
    LCD.WriteAt("Back", BACK_XCOORD, BACK_YCOORD);
    LCD.WriteAt("Credits", 132, 26);
    LCD.WriteAt("Developers:", 114, 65);
    LCD.WriteAt("Zach Palmer", 110, 91);
    LCD.WriteAt("Luke Parsons", 107, 111);
    LCD.WriteAt("Jake Silvert", 115, 131);
    LCD.WriteAt("Dylan Sussman", 100, 151);
}

/**
 * Function that creates one mine
 * and puts it in a random square
 * 
 * @author Dylan Sussman
 */
Mine createRandomMine() {
    /**
     * Generates two random number to signify
     * which square the bomb will be in
     */
    int x = RandInt() % 16;
    int y = RandInt() % 9;

    //Create corresponding coordinates with square chosen
    int xCoord = x * 20;
    int yCoord = y * 20 + 60; //Grid doesn't start at top of page, but at 60

    //Now a mine object can be created and returned
    Mine m(xCoord, yCoord);

    return m;
}

/**
 * Function that finds the number of adjacent bombs 
 * to the Square passed in
 * The Square is in the matrix of Squares passed in
 * 
 * @author Dylan Sussman
 */
int findAdjacentMines(Square sa[MAX_ADJACENT_SQUARES]) {
    int numMines = 0;

    for (int i = 0; i < MAX_ADJACENT_SQUARES; i++) {
        if(sa[i].getMine()) {
            numMines++;
        }
    }

    return numMines;
}

/**
 * Redraws the game board corresponding to new changes made by the user
 * Flag or click will be true which will determine whether the clicked 
 * square - s - will be flagged or revealed
 * Square s is the square that was clicked and sm is the matrix of all
 * the squares on the board
 * Returns true if the game has ended; false otherwise
 * 
 * @author Dylan Sussman and Zach Palmer
 */
bool redrawBoard(bool flag, bool click, Square *s, Square sm[GRID_ROWS][GRID_COLUMNS], int numMines) {
    bool result = false;
    
    /**
     * If the clicked square has already been revealed
     * then nothing on the board should change
     */
    if (!s->getRevealed()) {
        /**
         * The user has clicked the flag button
         * meaning they want to flag squares
         */
        if (flag) {
            /**
             * Clicked square was previously flagged
             * Now the board will get redrawn with that
             * square without a flag
             */
            if (s->getFlagged()) {
                s->setFlagged(false);

                //Draw over current square with plain blue square
                LCD.SetDrawColor(LCD.Blue);
                LCD.FillRectangle(s->getXCoord(), s->getYCoord(), SQUARE_SIDE, SQUARE_SIDE);

                drawGridLines();
            } 
            /**
             * Clicked square wasn't previously
             * A flag will be drawn over the 
             * clicked square
             */
            else if (flagCount(sm) < numMines) {
                s->setFlagged(true);

                //Create a new flag at s's coordinates to be drawn
                Flag f(s->getXCoord(), s->getYCoord());
                f.drawFlag();
            } 
        }

        /**
         * The user has clicked the click button
         * meaning they want to reveal a square
         */
        if(click) {
            /**
             * If the user has selected to click
             * and they click a flagged square then 
             * nothing happens
             */
            if(!s->getFlagged()) {
                Square adjacentSquares[MAX_ADJACENT_SQUARES];
                getAdjacentSquares(*s, sm, adjacentSquares);
                
                s->setRevealed(true);

                LCD.SetDrawColor(LCD.Gray);
                LCD.SetFontColor(LCD.Red);

                LCD.FillRectangle(s->getXCoord(), s->getYCoord(), SQUARE_SIDE, SQUARE_SIDE);
                
                //Revealing mine when the selected square is a mine
                if(s->getMine()) {
                    endGame(sm, *s);
                    result = true;
                } 
                //Revealing adjacent squares when the selected square has no mines adjacent to it
                /**
                 * In both of these if statements all of the extra squares that
                 * are revealed as a result of function calls must have their
                 * revealed value changed to true
                 */
                else if (s->getValue() == 0) { 
                    revealAroundZeros(adjacentSquares, sm);

                    /**
                     * Call revealAdjacentZeros here so that all of the squares that get
                     * revealed have their revealed variable changed to true
                     */
                    for (int i = 0; i < MAX_ADJACENT_SQUARES; i++) {
                        if(adjacentSquares[i].getValue() == 0) {
                            for (int r = 0; r < GRID_ROWS; r++) {
                                for (int c = 0; c < GRID_COLUMNS; c++) {
                                    if (adjacentSquares[i].getXCoord() == sm[r][c].getXCoord() && adjacentSquares[i].getYCoord() == sm[r][c].getYCoord()) {
                                        Square as[MAX_ADJACENT_SQUARES];
                                        getAdjacentSquares(adjacentSquares[i], sm, as);
                                        revealAroundZeros(as, sm);

                                        /**
                                         * Change set reaveled to true for the squares that were
                                         * drawn in the revealAroundZeros function
                                         */
                                        for (int i = 0; i < MAX_ADJACENT_SQUARES; i++) {
                                            for (int r = 0; r < GRID_ROWS; r++) {
                                                for (int c = 0; c < GRID_COLUMNS; c++) {
                                                    if (as[i].getXCoord() == sm[r][c].getXCoord() && as[i].getYCoord() == sm[r][c].getYCoord()) {
                                                        if(!sm[r][c].getFlagged()) {
                                                            sm[r][c].setRevealed(true);
                                                        }
                                                    }
                                                }
                                            }
                                        }


                                    }
                                }
                            }
                        }
                    }

                    /**
                     * Change set reaveled to true for the squares that were
                     * drawn in the revealAroundZeros function
                     */
                    for (int i = 0; i < MAX_ADJACENT_SQUARES; i++) {
                        for (int r = 0; r < GRID_ROWS; r++) {
                            for (int c = 0; c < GRID_COLUMNS; c++) {
                                if (adjacentSquares[i].getXCoord() == sm[r][c].getXCoord() && adjacentSquares[i].getYCoord() == sm[r][c].getYCoord()) {
                                    if (!sm[r][c].getFlagged()) {
                                        sm[r][c].setRevealed(true);
                                    }   
                                }
                            }
                        }
                    }

                    
                } 
                else {
                    LCD.WriteAt(s->getValue(), s->getXCoord() + 5, s->getYCoord() + 5);
                    revealAdjacentZeros(*s, adjacentSquares);

                    /**
                     * Change set reaveled to true for the squares that were
                     * drawn in the revealAdjacentZeros function
                     */
                    for (int i = 0; i < MAX_ADJACENT_SQUARES; i++) {
                        for (int r = 0; r < GRID_ROWS; r++) {
                            for (int c = 0; c < GRID_COLUMNS; c++) {
                                if(adjacentSquares[i].getValue() == 0) {
                                    if (adjacentSquares[i].getXCoord() == sm[r][c].getXCoord() && adjacentSquares[i].getYCoord() == sm[r][c].getYCoord()) {
                                        if (!sm[r][c].getFlagged()) {
                                            sm[r][c].setRevealed(true);
                                        } 
                                    }
                                }
                                
                            }
                        }
                    }
                }

                drawGridLines();
            }
        }

        /**
         * Determine the number of the flags on the board
         * and update the display accordingly
         */
        updateMinesLeft(flagCount(sm), numMines);
    }

    return result;
}

/**
 * Top two lines of display will have options to
 * go back to the main menu, replay, flag button, click
 * button, a clock/timer, and the number if mines 
 * left in the grid
 * 
 * @author Dylan Sussman
 */
void drawInGameMenu(int time, int mines) {
    //Set draw color to gray
    LCD.SetDrawColor(LCD.Gray);

    //Draw background
    LCD.FillRectangle(0, 0, 320, 240);

    //Draw menu
    LCD.SetFontColor(LCD.Black);
    LCD.Write("Main Menu");
    LCD.Write("   Replay");
    LCD.Write("   Click");
    LCD.WriteLine("   Flag");
    LCD.WriteAt("Time Left: ", 0, TIME_LEFT_YCOORD - 1);
    LCD.WriteAt(time, TIME_LEFT_XCOORD, TIME_LEFT_YCOORD);
    LCD.WriteAt("Mines Left: ", 140, MINES_LEFT_YCOORD - 1);
    LCD.WriteAt(mines, MINES_LEFT_XCOORD, MINES_LEFT_YCOORD);
}

/**
 * Draws the gridlines on the game board
 * 9 x 16 grid
 * 
 * @author Dylan Sussman
 */
void drawGridLines() {
    LCD.SetDrawColor(LCD.Black);
    
    //Horizontal lines
    for (int i = 60; i <= 240; i += 20) {
        LCD.DrawHorizontalLine(i, 0, 320);
    }

    //Vertical lines
    for (int i = 0; i <= 320; i += 20) {
        LCD.DrawVerticalLine(i, 60, 240);
    }
}

/**
 * Reveals all adjacent squares to a square
 * with a value of zero except those who 
 * also have a value of zero
 * Adjacent Squares with a value of zero
 * are left unrevealed
 * Sa (an array of Squares) containes all
 * of the adjacent squares to the square 
 * that was clicked which has a value of zero
 *
 * @author Dylan Sussman and Zach Palmer
 */
void revealAroundZeros(Square sa[MAX_ADJACENT_SQUARES], Square sm[GRID_ROWS][GRID_COLUMNS]) {
    LCD.SetDrawColor(LCD.Gray);
    LCD.SetFontColor(LCD.Red);

    for (int i = 0; i < MAX_ADJACENT_SQUARES; i++) {
        if(sa[i].getYCoord() != 0 && sa[i].getValue() >= 0) {
            if(!sa[i].getFlagged() && !sa[i].getRevealed()) {
                LCD.FillRectangle(sa[i].getXCoord(), sa[i].getYCoord(), SQUARE_SIDE, SQUARE_SIDE);
                if(sa[i].getValue() != 0) {
                    LCD.WriteAt(sa[i].getValue(), sa[i].getXCoord() + 5, sa[i].getYCoord() + 5);
                }
            }
        }
    }
    return;
}

/**
 * Finds all squares adjacent to s and puts them in 
 * array sa
 * 
 * @author Dylan Sussman and Zach Palmer
 */
void getAdjacentSquares(Square s, Square sm[GRID_ROWS][GRID_COLUMNS], Square *sa) {
 int index = 0;

    /**
     * Special case: determine if s is on a 
     * boundary of the grid
     * If it is then also determine whether it's
     * a corner or not
     * For each case, using sm, determine how many mines
     * are around the square
     */
    if (s.getXCoord() == 0 ) { //Left boundary
        if(s.getYCoord() == 60) { //Top left corner
            for (int r = 0; r < 2; r++) {
                for (int c = 0; c < 2; c++) {
                    //Skip over corner square
                    if(!(r == 0 && c == 0)) {
                        sa[index] = sm[r][c];
                        index++;
                    }
                }
            }
        } else if (s.getYCoord() == 220) { //Bottom left corner
            for (int r = 7; r < 9; r++) {
                for (int c = 0; c < 2; c++) {
                    //Skip over corner square
                    if(!(r == 8 && c == 0)) {
                        sa[index] = sm[r][c];
                        index++;
                    }
                }
            }
        } else { //Anything else on the left boundary
            /**
             * Start one row above s (-1)
             * -3 b/c first row starts at 60 not 0
             */
            int row = s.getYCoord()/20 - 4; 
            int col = s.getXCoord()/20; //Start in same column as s

            int rEnd = row + 2;
            int cEnd = col + 1;

            for (int r = row; r <= rEnd; r++) {
                for (int c = col; c <= cEnd; c++) {
                    //Skip over s
                    if (!((r + 3) * 20 == s.getYCoord() && c * 20 == s.getXCoord())) {
                        sa[index] = sm[r][c];
                        index++;
                    }
                }
            }

            
        }
    } else if (s.getXCoord() == 300) { //Right boundary
        if(s.getYCoord() == 60) { //Top right corner
            for (int r = 0; r < 2; r++) {
                for (int c = 14; c < 16; c++) {
                    //Skip over corner square
                    if(!(r == 0 && c == 15)) {
                        sa[index] = sm[r][c];
                        index++;
                    }
                }
            }
        } else if (s.getYCoord() == 220) { //Bottom right corner
            for (int r = 7; r < 9; r++) {
                for (int c = 14; c < 16; c++) {
                    //Skip over corner square
                    if (!(r == 8 && c == 15)) {
                        sa[index] = sm[r][c];
                        index++;
                    }
                }
            }
        } else { //Anything else on the right boundary
            /**
             * Start one row above s (-1)
             * -3 b/c first row starts at 60 not 0
             */
            int row = s.getYCoord()/20 - 4; 
            int col = s.getXCoord()/20 - 1; //Start one Column to the left of s

            int rEnd = row + 2;
            int cEnd = col + 1;

            for (int r = row; r <= rEnd; r++) {
                for (int c = col; c <= cEnd; c++) {
                    //Skip over s
                    if (!((r + 3) * 20 == s.getYCoord() && c * 20 == s.getXCoord())) {
                        sa[index] = sm[r][c];
                        index++;
                    }
                }
            }
            
        }
    } else if (s.getYCoord() == 60) { //Top boundary
        /**
         * Start in same row as s
         * -3 to offset grid starting at 60
         */
        int row = s.getYCoord()/20 - 3;
        int col = s.getXCoord()/20 - 1; //Start one column to the left of s

        int rEnd = row + 1;
        int cEnd = col + 2;

        for (int r = row; r <= rEnd; r++) {
            for(int c = col; c <= cEnd; c++) {
                //Skip over s
                if (!((r + 3) * 20 == s.getYCoord() && c * 20 == s.getXCoord())) {
                        sa[index] = sm[r][c];
                        index++;
                    }
            }
        }
    } else if (s.getYCoord() == 220) { //Bottom boundary
        /**
         * Start one row above s (-1)
         * -3 to offest grid starting at 60
         */
        int row = s.getYCoord()/20 - 4;
        int col = s.getXCoord()/20 - 1;

        int rEnd = row + 1;
        int cEnd = col + 2;

        for (int r = row; r <= rEnd; r++) {
            for (int c = col; c <= cEnd; c++) {
                //Skip over s
                if (!((r + 3) * 20 == s.getYCoord() && c * 20 == s.getXCoord())) {
                        sa[index] = sm[r][c];
                        index++;
                    }
            }
        }
    } else { //Anywhere else in the grid that is not a boundary
        /**
         * Start one row above s (-1)
         * -3 to offset grid starting at 60
         */
        int row = s.getYCoord()/20 - 4;
        int col = s.getXCoord()/20 - 1;

        int rEnd = row + 2;
        int cEnd = col + 2;

        for (int r = row; r <= rEnd; r++) {
            for (int c = col; c <= cEnd; c++) {
                //Skip over s
                if (!((r + 3) * 20 == s.getYCoord() && c * 20 == s.getXCoord())) {
                        sa[index] = sm[r][c];
                        index++;
                    }
            }
        }
    }
}

/**
 * Checks if the square that was clicked – 
 * the square passed in - has a mine
 * If it does then return true and draw
 * all the mines on the board
 * If not then return false
 *
 * @author Dylan Sussman and Zach Palmer
 */
void endGame(Square sm[GRID_ROWS][GRID_COLUMNS], Square s) {
    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLUMNS; c++) {
            if(sm[r][c].getMine() && !sm[r][c].getFlagged()) {
                //Clicked square turns red
                if(sm[r][c].getXCoord() == s.getXCoord() && sm[r][c].getYCoord() == s.getYCoord()) {
                    LCD.SetDrawColor(LCD.Red);
                    LCD.FillRectangle(sm[r][c].getXCoord(), sm[r][c].getYCoord(), SQUARE_SIDE, SQUARE_SIDE);
                } else {
                    LCD.SetDrawColor(LCD.Gray);
                    LCD.FillRectangle(sm[r][c].getXCoord(), sm[r][c].getYCoord(), SQUARE_SIDE, SQUARE_SIDE);
                }
                
                Mine m(sm[r][c].getXCoord(), sm[r][c].getYCoord());
                m.drawMine();
            } 
            //Square was flagged but didn't contain a mine
            if (sm[r][c].getFlagged() && !sm[r][c].getMine()) {
                LCD.SetDrawColor(LCD.Gray);
                LCD.FillRectangle(sm[r][c].getXCoord(), sm[r][c].getYCoord(), SQUARE_SIDE, SQUARE_SIDE);

                Mine m(sm[r][c].getXCoord(), sm[r][c].getYCoord());
                m.drawMine();

                //Draw an X indicating that there was no mine there
                LCD.SetDrawColor(LCD.Red);
                LCD.DrawLine(sm[r][c].getXCoord(), sm[r][c].getYCoord(), sm[r][c].getXCoord() + 20, sm[r][c].getYCoord() + 20);
                LCD.DrawLine(sm[r][c].getXCoord() + 20, sm[r][c].getYCoord(), sm[r][c].getXCoord(), sm[r][c].getYCoord() + 20);
            }
        }
    }
    
}

/**
 * Sa (an array of squares) contains all the Squares
 * adjacent to the square that was clicked
 * 
 * This function will reveal any zeros that in sa
 * which represents any adjacent Squares with a value
 * of zero
 * 
 * @author Dylan Sussman
 */
void revealAdjacentZeros(Square s, Square sa[MAX_ADJACENT_SQUARES]) {
    for (int i = 0; i < MAX_ADJACENT_SQUARES; i++) {
        if(sa[i].getYCoord() != 0 && !sa[i].getFlagged()) {
            if(sa[i].getValue() == 0 && !sa[i].getRevealed()) {
                LCD.SetDrawColor(LCD.Gray);
                LCD.FillRectangle(sa[i].getXCoord(), sa[i].getYCoord(), SQUARE_SIDE, SQUARE_SIDE);
            }
        }
    }
}

/**
 * Displayes the updated value of 
 * the number of mines left
 * 
 * @author Dylan Sussman
 */
void updateMinesLeft(int flags, int numMines) {
    LCD.SetDrawColor(LCD.Gray);
    LCD.SetFontColor(LCD.Black);

    LCD.FillRectangle(MINES_LEFT_XCOORD - 2, MINES_LEFT_YCOORD - 4, MINES_LEFT_WIDTH + 5, TEXT_HEIGHT + 5);
    LCD.WriteAt(numMines - flags, MINES_LEFT_XCOORD, MINES_LEFT_YCOORD);
}

/**
 * Displays the updated value
 * of the time the user has left
 * to complete the game
 * 
 * @author Dylan Sussman
 */
bool updateTimeLeft(double time, Square sm[GRID_ROWS][GRID_COLUMNS], int totalTime, Square s) {
    bool result = false;
    
    LCD.SetDrawColor(LCD.Gray);
    LCD.SetFontColor(LCD.Black);

    LCD.FillRectangle(TIME_LEFT_XCOORD - 2, TIME_LEFT_YCOORD - 4, TIME_LEFT_WIDTH + 5, TEXT_HEIGHT + 5);
    LCD.WriteAt(int(totalTime - time), TIME_LEFT_XCOORD, TIME_LEFT_YCOORD);

    if(int(totalTime - time) == 0) {
        endGame(sm, s);
        drawGridLines();
        result = true;
    }

    return result;
}

/**
 * Counts and returns the current number of flags
 * in the grid
 * 
 * @author Dylan Sussman
 */
int flagCount(Square sm[GRID_ROWS][GRID_COLUMNS]) {
    int numFlags = 0;

    for (int r = 0; r < GRID_ROWS; r++) {
        for (int c = 0; c < GRID_COLUMNS; c++) {
            if (sm[r][c].getFlagged()) {
                numFlags++;
            }
        }
    }

    return numFlags;
}

/**
 * Displays the difficulty/level options
 * for the game
 * 
 * @author Dylan Sussman
 */
void drawInGameOptions() {
    LCD.Clear();

    LCD.SetFontColor(LCD.White);

    LCD.WriteAt("Main Menu", BACK_XCOORD, BACK_YCOORD);
    LCD.WriteAt("Level/Difficulty Options", 70, 26);
    LCD.WriteAt("Easy – Find 25 mines in 5 minutes", EASY_XCOORD, EASY_YCOORD);
    LCD.WriteAt("Medium – Find 30 mines in 4 minutes", MEDIUM_XCOORD, MEDIUM_YCOORD);
    LCD.WriteAt("Hard – Find 35 mines in 3 minutes", HARD_XCOORD, HARD_YCOORD);
    LCD.WriteAt("Drew (Super Hard) – Find 40 mines", SUPER_HARD_XCOORD, SUPER_HARD_YCOORD);
    LCD.WriteAt("in 2 minutes", 112, SUPER_HARD_YCOORD + 20);
}