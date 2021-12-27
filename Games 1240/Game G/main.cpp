
//Developed by Isaac Einstein, Will Rinehart, Kevin Kotobelli, and Deeya Rodrigues
//Include necessary libraries
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHSD.h"
#include "FEHUtility.h"

//-----------------------------------Define constants -------------------------------//
#define ROW_STATE_ROAD 0
#define ROW_STATE_FOREST 1
#define NUM_OF_ROADS 3
#define NUM_OF_FORESTS 6 - NUM_OF_ROADS
#define CHANGE_IN_CAR_POS 30
#define MAX_NUMBER_OF_TREES 6

/**
*
* This class draws all figures used in the game.
* It is also responsible for handling player movement, score, collisions,
* and high scores. The class is largely used to pass the same variables across multiple functinos
*
* */
class drawObjects
{
private:
    //Amount of buffer time (changes with each level)
    double BUFFER_TIME = 0.1;

    //Y coordinates of each row to be able to reference throughout program
    int rowCoordinates[10] = {30, 60, 90, 120, 150, 180};

    //Middle of tree x coordinates
    int midTreeX[MAX_NUMBER_OF_TREES];

    //Middle of tree y coordinates
    int midTreeY[MAX_NUMBER_OF_TREES];

    //Array to indicate if the row is a road or forest (will consist of 0's or 1's)
    int rowStateArray[6];

    // X position of each car (will be updated each time the car moves)
    int xPositionCar[NUM_OF_ROADS];

    //Array that will contain the y coordinates where roads begin
    int yPositionCar[NUM_OF_ROADS];

    // Creates blank array with the amount of columns that aren't roads.
    // This array will contain the row coordinates of all rows with trees
    int yPositionTrees[NUM_OF_FORESTS];

    //Creates an array to store the x position of each tree; array filled in the drawForest function
    int xPositionTree[MAX_NUMBER_OF_TREES];

    //Variables for player position
    // playerPositionX is the length and playerPositionY is the width of the rectangle that is being moved.
    int playerPositionX = 155, playerPositionY = 211;

    //Boolean to see if game keeps playing
    bool rerun = true;
    bool bigLoop = true;

    //Declare variable for time left. Decreases by 15 seconds with each level
    int timeLeft;

    //Player score
    int playerScore = 0;

    //highscore array. Used to store high scores for all 3 levels
    int hs_array[3] = {0, 0, 0};

    //Have a variable for all 3 levels to indicate which level the user selected
    bool levelOne = false, levelTwo = false, levelThree = false;

public:
    //Functions in the class (Declared as public)
    drawObjects();
    void drawBoard();
    void drawSingleRoad(int);
    void drawForest(int);
    int drawMovingCar(int, int);
    int drawCarsWithBackground();
    void collisionWithCar();
    void collisionWithTree();
    void drawMovementKeys();
    void mainmenu();
    void userChoosesMenu();
    void playerMovement();
    void selectLevel();
    void moveBackToBottom();
    int endgame();
    void quit();
    int *SDLoad();
    void SDWrite();
    void stats();
};

//Function prototypes for main menu, play game, display stats, instructions, and credits
void instructions();
void credits();
void goodbye();

/**
* Main function (Try and keep as empty as possible, just call functions)
*/
int main()
{

    //Clear the screen
    LCD.Clear();

    // Instance of class
    drawObjects p1;

    //Display main menu options
    p1.mainmenu();

    //Have user select where they want to go (play game, show credits, etc.)
    p1.userChoosesMenu();
}

/**
* Quit function.
* Checks if the screen has been clicked. If it has, it will store the coordinates into x and y and then checks if the position is anywehre inside the quit rectangle drawn on screen.
* If it is, then the whole game will end.
*
* @author Kevin Kotobelli
*/
void drawObjects::quit()
{
    int x, y;
    if (LCD.Touch(&x, &y))
    {
        if (x > 5 && x < 5 + 36 && y > 5 && y < 5 + 22)
        {
            rerun = false;
            bigLoop = false;

            //WRITES TO THE SCREEN THAT THE USER QUIT
            LCD.WriteAt("QUIT!", 150, 10);
        }
    }
}

/**
* Draw objects constructor
* Initializes most variables and arrays used within the class
*
* @author Isaac Einstein
*/
drawObjects::drawObjects()
{

    int i;
    // Initialize all elements of rowStateArray to one; Will be overwritten with 0's later to signify there's a road
    for (i = 0; i < 6; i++)
    {
        rowStateArray[i] = 1;
    }
    //tree x and y coordinates
    for (i = 0; i < MAX_NUMBER_OF_TREES; i++)
    {
        midTreeX[i] = 0;
        midTreeY[i] = 0;
    }

    // X and Y position of each car (will be updated each time the car moves)
    for (i = 0; i < NUM_OF_ROADS; i++)
    {
        xPositionCar[i] = 0;
        yPositionCar[i] = 0;
    }

    // Creates blank array with the amount of columns that aren't roads.
    // This array will contain the row coordinates of all rows with trees
    for (i = 0; i < NUM_OF_FORESTS; i++)
    {
        yPositionTrees[i] = 0;
    }

    //Creates an array to store the x position of each tree; array filled in the drawForest function
    for (i = 0; i < MAX_NUMBER_OF_TREES; i++)
    {
        xPositionTree[i] = 0;
    }
}

/**
*
* User written function for home screen of main menu. Displays the main menu
 
* @author Deeya Rodrigues
*/
void drawObjects::mainmenu()
{

    //clear screen
    LCD.Clear();
    //Set the font color to black
    LCD.SetFontColor(LCD.Red);
    //Write main menu
    LCD.WriteAt("Main Menu", 110, 20);
    //Set menu option font color to white
    LCD.SetFontColor(LCD.White);
    //write play game here
    LCD.WriteAt("Play Game", 110, 60);
    //write display statistics
    LCD.WriteAt("Display Statistics", 110, 100);
    //write instructions
    LCD.WriteAt("Instructions", 110, 140);
    //write credits
    LCD.WriteAt("Credits", 110, 180);
}

/**
*
* User selects where to go based on menu options.
*
* @author Deeya Rodrigues; Isaac Einstein
*/
void drawObjects::userChoosesMenu()
{
    //load in high scores to be diplayed in statistics slide
    SDLoad();

    //intialize and declare variables
    int x, y, k = 0;

    //wait for touch to register
    while (k == 0)
    {
        k = 1;
        while (k == 1)
        {
            while (!LCD.Touch(&x, &y))
            {
            }

            {
                //start if statement for play game here
                if (x >= 110 && x <= 240 && y >= 60 && y <= 100)
                {
                    selectLevel();
                    Sleep(.5);

                    //Plays the game until there's a collission or time runs out and the game ends
                    //Returns a k vale of 4 to end the game
                    // k = 0;

                    k = drawCarsWithBackground();

                    //Pauses for timeLeft seconds before showing the game over screen
                    double wait = TimeNow(), timeLeft = 2;
                    while ((TimeNow() - wait) <= timeLeft)
                    {
                    }
                }
                //if statement for if display stats button is clicked
                else if (x >= 110 && x <= 240 && y >= 100 && y <= 140)
                {
                    stats();
                    k = 2;
                }
                //if statement for instructions button
                else if (x >= 110 && x <= 240 && y >= 140 && y <= 180)
                {
                    instructions();
                    k = 2;
                }
                //else statement for credits
                else if (x >= 110 && x <= 240 && y >= 180)
                {
                    credits();
                    k = 2;
                }
                else
                    (k = 5);
            }
            while (k == 2)
            {
                while (!LCD.Touch(&x, &y))
                {
                }
                {
                    if (x >= 90 && x <= 190 && y >= 220)
                    {
                        mainmenu();
                    }
                    k = 0;
                }
            }
            while (k == 4)
            {
                k = endgame();
                k = 0;
            }

            while (k == 5)
            {
                goodbye();

                Sleep(3);

                //Exits every loop
                k = 6;
            }
        }
    }
}

/**
* Runs if k = 5, displays a goodbye message. Runs after the endgame function runs (if the user clicks anywhere besides return to main menu)
*
* @author Isaac Einstein
*/
void goodbye()
{
    LCD.Clear(GREEN);
    LCD.SetFontColor(RED);
    LCD.WriteAt("Thanks for Hoppin' Around With Us!", 2, 100);
    LCD.WriteAt("Catch you on the flippity flip:)", 2, 200);
}

/**
* user written fucntion for end game. Displays when the user loses the game.
* Shows the user's score and gives the option to return to the main menu.
* If the user clicks anywhere else, the game ends
*
* @author Isaac Einstein; Deeya Rodrigues
*/
int drawObjects::endgame()
{
    int returnVal = 5;

    //clear screen
    LCD.Clear(GREEN);

    //Set the font color to red
    LCD.SetFontColor(LCD.Red);
    //Write Game Over
    LCD.WriteAt("Game Over", 110, 20);
    //Write return to main menu
    LCD.WriteAt("Return to Main Menu", 90, 220);

    //Display the player's score
    LCD.WriteAt(playerScore, 145, 100);
    LCD.WriteAt("Your Score: ", 117, 80);

    //Update highscores in the SD card
    SDWrite();

    //Have user touch to return to main menu
    int a, b;
    while (!LCD.Touch(&a, &b))
    {
    }

    //If the user clicks the region that contains "return to main menu"
    if (b >= 210)
    {
        returnVal = 0;
        mainmenu();

        playerPositionX = 115;
        playerPositionY = 211;

        levelOne = false;
        levelTwo = false;
        levelThree = false;
    }

    //Return the value to loop through; either 2 for return to main menu or 5 for goodbye screen
    return returnVal;
}

/**
* user written function for display state
* SHows the current high score for each level
 
* @author Will Rinehart; Deeya Rodrigues
*/
void drawObjects::stats()
{
    //clear screen
    LCD.Clear();
    //write in Red
    LCD.SetFontColor(LCD.Red);
    //Write and display statistics
    LCD.WriteAt("Statistics", 110, 20);

    //Display Level 1 high score
    LCD.WriteAt("Level One High Score ", 100, 60);
    LCD.WriteAt(hs_array[0], 90, 80);

    //Display level 2 high score
    LCD.WriteAt("Level Two High Score: ", 100, 100);
    LCD.WriteAt(hs_array[1], 90, 120);

    //Display level 3 high score
    LCD.WriteAt("Level 3 High Score: ", 100, 140);
    LCD.WriteAt(hs_array[2], 90, 160);

    //Return to main menu
    LCD.WriteAt("Return to Main Menu", 90, 220);
}

/**
* Gives the instructions of the game
 
* @author Deeya Rodrigues
*/
void instructions()
{
    //clear screen
    LCD.Clear();
    //write in Red
    LCD.SetFontColor(LCD.Red);
    //Write and display instructions header
    LCD.WriteAt("Instructions", 110, 10);
    //write in white
    LCD.SetFontColor(LCD.White);
    //write instructions
    LCD.WriteAt("Select a level ", 3, 30);
    LCD.WriteAt("Touch arrow keys to move", 3, 50);
    LCD.WriteAt("Avoid Obstacles", 3, 70);
    LCD.WriteAt("One road crossed = + 1 point", 3, 90);
    LCD.WriteAt("Level increases = less time", 3, 110);
    LCD.WriteAt("Game ends when player hits obstacle", 3, 130);
    LCD.WriteAt("or runs out of time", 3, 150);
    LCD.WriteAt("High Score displayed at end of game", 3, 170);
    LCD.WriteAt("Return to Main Menu", 90, 220);
}

/**
* Gives the credits of the game
 
* @author Deeya Rodrigues
*/
void credits()
{
    //clear screen
    LCD.Clear();
    //write in Red
    LCD.SetFontColor(LCD.Red);
    //Write and display credits
    LCD.WriteAt("Credits", 120, 20);
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("Developers", 110, 40);
    LCD.SetFontColor(LCD.Gray);
    LCD.WriteAt(" Deeya Rodrigues, Kevin Kotobelli", 3, 60);
    LCD.WriteAt(" Will Rinehart, Isaac Einstein", 3, 80);
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("References", 110, 100);
    LCD.SetFontColor(LCD.Gray);
    LCD.WriteAt("Frogger(1997 Video Game)", 3, 120);
    LCD.WriteAt("FEH Proteus Simulator Website", 3, 140);
    LCD.WriteAt("https://feh.osu.edu/simulator_docs/api", 3, 160);
    LCD.WriteAt("Return to Main Menu", 90, 220);
}

/**
*
* All code needed to draw the background with the
* cars moving on roads. Calls all other functions besides those
* related to the main menu. Big shoutout to the amazing TA Samara Einstein 
* for all her help on this!!
*
* @author Isaac Einstein; Kevin Kotobelli
*/
int drawObjects::drawCarsWithBackground()
{
    //reset all necessary variables to play the game with a fresh start
    int quit = 1;
    bigLoop = true;
    playerScore = 0;
    int startTime = TimeNow();

    while (bigLoop)
    {

        rerun = true;

        //Call function to draw the board
        drawBoard();

        //Creates an array to store the x position of each tree
        int j = 0, k = 0;

        //Runs through all elements of the array containing Ones and Zeros
        for (int i = 0; i < 6; i++)
        {

            //If the row was assigned to be road
            if (rowStateArray[i] == ROW_STATE_ROAD)
            {
                //Assigns Y-coordinate for where a road should be to the array "rowsWithRoads"; This array ONLY contains the numbers of coordinates where roads begin
                yPositionCar[j] = rowCoordinates[i];
                j++;
            }
            //If the row was assigned to be forest; (rowStateArray[i] == ROW_STATE_FOREST)
            else
            {
                //Assigns Y-coordinate for where a tree should be to the array "columnsWithTrees"; This array ONLY contains the numbers of coordinates where roads begin
                yPositionTrees[k] = rowCoordinates[i];
                k++;
            }
        }

        //Run through the number of rows with trees, and draw trees at that y position
        for (int i = 0; i < NUM_OF_FORESTS; i++)
        {
            drawForest(yPositionTrees[i]);
        }

        //Assign random car start points. Fills an array of he size NUM_OF_ROADS with random numbers between 0 and 320 (all possible x values)
        // int xPositionCar[NUM_OF_ROADS];
        for (int i = 0; i < NUM_OF_ROADS; i++)
        {
            xPositionCar[i] = RandInt() % 320;
        }

        //Draws cars and then redraws roads where the car was and draws a new moved car indefinitely
        while (rerun == true)
        {

            //Time remaining keeps decreasing
            int currentStartTime = (int)(TimeNow() - startTime);
            LCD.WriteAt(timeLeft - currentStartTime, 50, 225);

            LCD.WriteAt(playerScore, 290, 10);

            //Runs through to draw cars on all roads
            for (int i = 0; i < NUM_OF_ROADS; i++)

            {

                // Draw a car starting at the coordinate that a road begins (each element of rowsWithRoads)
                for (int j = 0; j < NUM_OF_ROADS; j++)
                {
                    //For x position, picks the element of the xPosition array (which is random)
                    xPositionCar[j] = drawMovingCar(xPositionCar[j], yPositionCar[j]);
                }

                //Program pauses (WAITING WHILE LOOP); waits however long buffer time is
                double start = TimeNow();
                while ((TimeNow() - start) <= BUFFER_TIME)
                {
                }

                //Call function that determines where the player should go based on user touch
                playerMovement();

                //Test to see if there's a collision with tree. Makes boolean rerun false if there's a collision a
                collisionWithTree();

                //Test to see if there's a colission with a car. Makes boolean rerun false if there's a collision and the game stops
                collisionWithCar();

                //If the user runs out of time, they lose
                if (timeLeft - currentStartTime <= 0)
                {
                    LCD.WriteAt("Time's Up!", 145, 10);
                    rerun = false;
                    bigLoop = false;
                }

                LCD.SetDrawColor(LCD.Blue);

                /* Instead of clearing a screen the program redraws a blank road before looping back and drawing
          a car again; gives the appearance of the car moving even though it's just being drawn over. Only runs if there is no collision before */

                for (int j = 0; j < NUM_OF_ROADS; j++)
                {
                    drawSingleRoad(yPositionCar[j]);
                }

                LCD.DrawRectangle(playerPositionX, playerPositionY + 4, 24, 24);
                LCD.DrawVerticalLine(playerPositionX + 4, playerPositionY + 4 + 6, playerPositionY + 4 + 24 - 14);
                LCD.DrawVerticalLine(playerPositionX + 20, playerPositionY + 4 + 6, playerPositionY + 4 + 24 - 14);
                LCD.DrawHorizontalLine(playerPositionY + 4 + 18, playerPositionX + 5, playerPositionX + 24 - 5);
            }

            //Redraw board once the user reaches the top of the screen
            moveBackToBottom();

            //Fill rectangle to cover score and current time
            LCD.SetDrawColor(GREEN);
            LCD.FillRectangle(290, 10, 25, 20);
            LCD.FillRectangle(45, 215, 50, 25);
        }

        // ----------------------------------------------------
        // DEBUG REINITIALIZE ALL ARRAYS TO TRY AND FIX ISSUE OF HIDDEN TREES AND EXTRA ROADS
        //Probs don't need this but it can't hurt:)
        for (int i = 0; i < 6; i++)
        {
            // if (rowStateArray[i] == ROW_STATE_FOREST)
            // {
            yPositionTrees[i] = 0;
            xPositionTree[i] = 0;
            // }
            // if (rowStateArray[i] == ROW_STATE_ROAD)
            // {
            xPositionCar[i] = 0;
            yPositionCar[i] = 0;
            // }
            rowStateArray[i] = 1;
        }

        for (int i = 0; i < MAX_NUMBER_OF_TREES; i++)
        {
            midTreeX[i] = 0;
            midTreeY[i] = 0;
        }

        //----------------------------------------------------
    }

    //Return value of 4 to quit the game. Only returns 4 when the while loop is quit
    quit = 4;
    return quit;
}

/**
* Test to see if there's a collision with a tree
* The x and y coordinates of the tree were stored in arrays midtreex and midtreey. A hitbox of 50 by 30 is drawn around and if the player intersects with that hitbox it is game over
*
* @author Kevin Kotobelli; Isaac Einstein
*/
void drawObjects::collisionWithTree()
{
    for (int i = 0; i < MAX_NUMBER_OF_TREES; i++)
    {

        if (playerPositionX + 14 > midTreeX[i] - 25 && playerPositionX + 14 < midTreeX[i] + 25 && playerPositionY + 14 > midTreeY[i] - 8 && playerPositionY + 14 < midTreeY[i] + 8)
        {
            //Makes sure the user isn't at the starting row
            if (playerPositionY != 211)
            {
                rerun = false;
                bigLoop = false;

                //WRITES TO THE SCREEN THAT THERE WAS A COLLISION
                LCD.WriteAt("TREE!", 150, 10);
            }
        }
    }
}

/**
* Test to see if there's a collision with a car
* The x and y coordinates of the car were stored in arrays carPositionX and carPositionY. A hitbox of 50 by 30 is drawn around and if the player intersects with that hitbox it is game over
*
* @author Kevin Kotobelli; Isaac Einstein
*/
void drawObjects::collisionWithCar()
{
    //Boolean to determine if the program should keep running or not
    //true = keep running, false == there was a collision
    // bool continueRunning = rerun;
    for (int p = 0; p < NUM_OF_ROADS; p++)
    {
        //if the X coordinates of the player are within the coordinates of the car
        if (playerPositionX + 20 > xPositionCar[p] && playerPositionX + 20 < xPositionCar[p] + 25)
        {

            //if the Y coordinates of the player are within those of the car
            if ((playerPositionY + 4) > yPositionCar[p] && playerPositionY + 4 < yPositionCar[p] + 30)
            {
                //Change the boolean to signify a collision so the program stops
                rerun = false;
                bigLoop = false;

                //WRITES TO THE SCREEN THAT THERE WAS A COLLISION
                LCD.WriteAt("CAR!", 150, 10);
            }
        }
    }
}

/**
*
* Draws a moving car that, given a certain
* dificulty level will move a car across the screen
* indefinitely, which will wrap around the screen
*
* @return state integer array that is now filled with either 0's or 1's.
* Used later to determine where a moving car should be placed
*
* @author Isaac Einstein, Will Rinehart
*/
void drawObjects::drawBoard()
{
    //Sets background color to green
    LCD.Clear(GREEN);

    //Seed random number based on time program's been running
    srand(TimeNow());

    int currNumRoads = 0, i = 0;

    //Set state of each column, randomly deterine if each column is road or forest (0 or 1). To ensure there are NUM_OF_ROADS roads,
    while (currNumRoads < NUM_OF_ROADS && i < 6)
    {
        //Sets array to 0 (road) or 1 (forest)
        rowStateArray[i] = RandInt() % 2;

        //If a road was assigned...
        if (rowStateArray[i] == ROW_STATE_ROAD)
        {
            //Increment the current number of roads
            currNumRoads++;
        }

        i++;

        /* FAILSAFE: If all elements are assigned (0/1) but there aren't NUM_OF_ROADS roads,
    restart the process. Set all variables back to 0 and loop through again make
    until there are NUM_OF_ROADS roads */

        //if all 6 elements are assigned before the necessary number of roads are assignmed...
        if (i == 6 && currNumRoads < NUM_OF_ROADS)
        {
            //Reset all counting variables so that the loop restarts
            i = 0;
            currNumRoads = 0;
            LCD.Clear(GREEN);
            for (int k = 0; k < 6; k++)

            {
                rowStateArray[k] = 1;
            }
        }
    }

    //Now that the state of each row is assigned, draw roads
    for (int i = 0; i < 6; i++)
    {
        if (rowStateArray[i] == ROW_STATE_ROAD)
        {
            drawSingleRoad(rowCoordinates[i]);
        }
    }

    // Display the score on the board and the time
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Score: ", 235, 10);
    LCD.WriteAt("Time:", 0, 225);

    // Draw movement keys
    drawMovementKeys();
}

/**
*
* Converts one row to  a single road starting at the y coordinate given. Road is a grey rectangle with yellow dividing liens
*
* @param yPos integer of the top left y position of the row
*
* @author Isaac Einstein, Will Rinehart
*/
void drawObjects::drawSingleRoad(int y)
{

    // Draw grey road
    LCD.SetDrawColor(LCD.Gray);
    LCD.FillRectangle(0, y, 320, 30);

    //Draw yellow dashed lines
    for (int k = 0; k < 6; k++)
    {
        LCD.SetDrawColor(YELLOW);
        LCD.FillRectangle(k * 60, y + 15, 10, 2);
    }

    //Add Black lines to show each row
    LCD.SetDrawColor(LCD.Black);
    LCD.DrawHorizontalLine(y, 0, 320);
    LCD.DrawHorizontalLine(y + 30, 0, 320);
}

/**
*
* Converts one row to a forest starting at the y coordinate given. Forest is a grey rectangle with trees.
*
* @param yPos integer of the top left y position of the row
*
* @return xCoordinates integer array containing all the x values of trees
*
* @author Isaac Einstein, Will Rinehart
*/

void drawObjects::drawForest(int y)
{

    //draw trees
    for (int j = 1; j < MAX_NUMBER_OF_TREES; j++)
    {
        //There is a 1 in 4 chance that each forest row having a tree
        int tree = RandInt() % 4;
        if (tree == 1)
        {
            //Draw in tree at correct cordinate

            //Draw the trunk
            LCD.SetDrawColor(BROWN);
            LCD.FillRectangle((j * 40) + 1, y + 12, 5, 14);

            //Store the x coordinate of the rectangle in an array to be returned
            midTreeX[j] = (j * 40) + 1 + 3;
            midTreeY[j] = (y + 12) + 7;

            LCD.SetFontColor(BLACK);

            //Leaves of the tree
            LCD.SetDrawColor(FORESTGREEN);
            LCD.FillCircle((j * 40) + 3, (y + 9), 7);
            LCD.FillCircle((j * 40), (y + 11), 7);
            LCD.FillCircle((j * 40) + 6, (y + 11), 7);

            //Circle on the trunk
            LCD.SetDrawColor(BLACK);
            LCD.FillCircle((j * 40) + 3.75, y + 21.5, 2);
        }
    }

    //Add Black lines to show each row
    LCD.SetDrawColor(LCD.Black);
    LCD.DrawHorizontalLine(y, 0, 320);
    LCD.DrawHorizontalLine(y + 30, 0, 320);
}

/**
*
* Draws a moving car that will move a car across the screen
* indefinitely. The car will also wrap around the screen.
*
* @param xPos integer of the top left x position of the rectangular portion of the car
* @param yPos integer of the top left y position of the rectanular portion of the car
*
* @return xPos integer of the x coordinate of the car. Will be used to determine where to redraw the next car and if a collision occurs.
*
* @author Isaac Einstein
*/

int drawObjects::drawMovingCar(int xPos, int yPos)
{

    //DRAW THE CAR
    //Sets the draw color to red
    LCD.SetDrawColor(LCD.Scarlet);

    //Draw Rectangle body of car
    LCD.FillRectangle(xPos, yPos, 20, 10);

    //Draw the wheels of the car
    LCD.SetDrawColor(LCD.Black);
    LCD.FillCircle(xPos + 5, yPos + 15, 5);
    LCD.FillCircle(xPos + 15, yPos + 15, 5);

    xPos += CHANGE_IN_CAR_POS;

    //If the car reaches the right side of the screen (300 pixles) have it be redrawn on the left side
    if (xPos > 300)
    {
        xPos = 10;
    }

    return xPos;
}

/**
*  Function Player Movement 
* It initializes variables x and y and checks for touch. If touch is detected, the coordinates of that touch are stored into x and y.
* If touch is detected, it will draw over the original rectangle in green to erase it and then calculate what needs to be changed in the coordinates of the old position to get to the new position
* It checks if the user clicked either of the movement keys on the bottom right of the screen and changes the values of the players position accordingly
* Once the movement has been registered, the rectangle will be moved a specific amount of pixels in the direction where the user wanted it to
*  @author Kevin Kotobelli
*/
void drawObjects::playerMovement()
{
    //PLAYER MOVEMENT
    int x, y;
    if (LCD.Touch(&x, &y))
    {
        LCD.SetDrawColor(LCD.Green);
        LCD.DrawRectangle(playerPositionX, playerPositionY + 4, 24, 24);
        LCD.DrawVerticalLine(playerPositionX + 4, playerPositionY + 4 + 6, playerPositionY + 4 + 24 - 14);
        LCD.DrawVerticalLine(playerPositionX + 20, playerPositionY + 4 + 6, playerPositionY + 4 + 24 - 14);
        LCD.DrawHorizontalLine(playerPositionY + 4 + 18, playerPositionX + 5, playerPositionX + 24 - 5);

        /*-------------------------------------------------------*/

        //Move Left is pushed
        if (x > 219 && x < 244)
        {
            if (y > 209 && y < 234)
            {
                // this is for collision. The rectangle cannot leave the left side of the screen. If the x value is less than 0 then it will not move further.
                if (playerPositionX >= 0)
                {
                    playerPositionX = playerPositionX - 30;
                }
            }
        }

        /*-------------------------------------------------------*/

        // Move Up is pushed
        if (x > 254 && x < 279)
        {
            //Add one to the player's score
            playerScore++;

            if (y > 209 && y < 234)
            {
                // this will only allow the rectangle to move if the position of the rectangle is less than or equal to 196. That is the starter position.
                if (playerPositionY <= 219)
                {
                    playerPositionY = playerPositionY - 30;
                    if (playerPositionY > 219 - 3)
                    {
                        playerPositionY = 219 - 3;
                    }
                }
            }
        }

        /*-------------------------------------------------------*/

        // Move right button is pushed
        if (x > 289 && x < 314)
        {
            if (y > 209 && y < 234)
            {
                if (playerPositionX <= 291)
                {
                    playerPositionX = playerPositionX + 30;
                    // This keeps the player from moving off screen to the right. If h is greater than 291, it defaults to 291.
                    if (playerPositionX > 291)
                    {
                        playerPositionX = 291;
                    }
                }
            }
        }
    }
    //Checks if user clicks quit button
    quit();
}

/**
* Draw the movement keys and quit button onto the screen
* This function draws three squares with lines indicating direction at the bottom right corner of the screen. This is so the user knows where to press to move the player
* This function also draws the quit button on the screen so the user knows where to click to prematurely end the game
*  @author Kevin Kotobelli
*/
void drawObjects::drawMovementKeys()
{
    // these draw the movement keys
    LCD.SetDrawColor(LCD.Red);
    LCD.DrawRectangle(219, 209 + 2, 25, 25);
    LCD.DrawRectangle(254, 209 + 2, 25, 25);
    //LCD.DrawRectangle(254,209+2-30,25,25);
    LCD.DrawRectangle(289, 209 + 2, 25, 25);
    LCD.DrawVerticalLine(266, 214, 229);
    //LCD.DrawVerticalLine(266,214-30,229-30);

    LCD.DrawHorizontalLine(221, 224, 239);
    LCD.DrawHorizontalLine(221, 294, 309);

    LCD.DrawRectangle(5, 5, 36, 22);
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt("Quit", 6, 8);
}

/**
* This function allows the user to select which difficulty they would like to play on. Level 1 is beginner. Level 2 is intermediate. Level 3 is Expert.
* Each level comes with a different buffer time for the cars. The higher the difficulty the faster the cars move and the harder it is to cross the road.
*
* @author Isaac Einstein
*/
void drawObjects::selectLevel()
{

    LCD.Clear(GREEN);
    LCD.SetFontColor(RED);
    LCD.SetDrawColor(RED);
    LCD.Write("Pick a level!");

    //Beginner level
    LCD.WriteAt("Level 1", 102, 55);
    LCD.DrawRectangle(100, 50, 100, 20);

    //Intermediate level
    LCD.WriteAt("Level 2", 102, 130);
    LCD.DrawRectangle(100, 125, 100, 20);

    //Expert level
    LCD.WriteAt("Level 3", 102, 205);
    LCD.DrawRectangle(100, 200, 100, 20);

    int x, y;

    while (!LCD.Touch(&x, &y))
    {
    }

    // If beginner box is chosen
    if (y >= 40 && y <= 80)
    {
        //Set buffer time to easy level
        BUFFER_TIME = 1.0;

        //Make total time to 120 seconds
        timeLeft = 120;

        levelOne = true;
    }

    // If intermediate box is chosen
    if (y >= 115 && y <= 160)
    {

        //Set buffer time to intermediate level
        BUFFER_TIME = .5;

        //Make total time to 90 seconds
        timeLeft = 90;

        levelTwo = true;
    }

    // If expert box is chosen
    if (y >= 190 && y <= 230)
    {
        //Set buffer time to expert level
        BUFFER_TIME = .1;

        //Make total time to 60 seconds
        timeLeft = 60;

        levelThree = true;
    }

    //Write to the screen you have ___ seconds in total
    LCD.WriteAt("You have _____ seconds", 30, 15);
    LCD.WriteAt(" to get as far as you can!", 30, 30);

    //Display how many seconds
    LCD.WriteAt(timeLeft, 110, 13);

    Sleep(1.5);
}

/**
* This function moves the player back to the bottom of the screen once they reach the end.
* This way, the game can keep running with different levels, instead of just ending once the player reaches the top.
*
* @author Isaac Einstein
*
*/
void drawObjects::moveBackToBottom()
{

    //When the player reaches the top, move them back to the bottom
    if (playerPositionY <= 29)
    {
        playerPositionX = 155;
        playerPositionY = 211;

        rerun = false;
    }
}

/**
* This function allows the game to save data like high scores into a text document and display them in the beginning and end of the game.
* It opens up file Group_G_log.txt and scans the data into the document for later use.
*
* @author Will Rinehart
*/
int *drawObjects::SDLoad()
{
    //open log file
    FEHFile *log = SD.FOpen("Group_G_log.txt", "r");

    //read in high score
    int hs1, hs2, hs3, test;
    SD.FScanf(log, "%i%i%i", &hs1, &hs2, &hs3);

    //close file
    test = SD.FCloseAll();

    //put all high scores into array which can be exported from function
    int hs_array[3] = {hs1, hs2, hs3};
}

/**
* This function writes the highscores saved in the Group_G data file to screen for the user to see.
* It calculates whether or not the user beat the current highscore by using if statements.
*
* @author Will Rinehart
*
*/
void drawObjects::SDWrite()
{
    //if level one is selected, check to see if highscore is broken
    if (levelOne == true)
    {
        //if highscore is broken update hs_array
        if (playerScore > hs_array[0])
        {
            hs_array[0] = playerScore;
        }
    }
    //if level two is selected, check to see if highscore is broken
    if (levelTwo == true)
    {
        //if highscore is broken update hs_array
        if (playerScore > hs_array[1])
        {
            hs_array[1] = playerScore;
        }
    }

    //if level three is selected, check to see if highscore is broken
    if (levelThree == true)
    {
        //if highscore is broken update hs_array
        if (playerScore > hs_array[2])
        {
            hs_array[2] = playerScore;
        }
    }

    //open log file
    FEHFile *log = SD.FOpen("Group_G_log.txt", "w");

    //print new high scores
    SD.FPrintf(log, "%i%i%i", hs_array[0], hs_array[1], hs_array[2]);

    //close the file
    SD.FCloseAll();
}

//----------------------------------------------END OF CODE!-------------------------------------//