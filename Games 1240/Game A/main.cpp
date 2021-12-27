/*  
    SDP Project 
    By: Adam Farrell, Jacob Kasmarcak, David Kuntz, Max Starr
    RJF 12:40
    12/1/2020
*/
 

/*
    Include and define statements
*/

#include <iostream>
#include <FEHLCD.h>
#include <FEHRandom.h>
#include <FEHSD.h>
#include <FEHUtility.h>
#include <LCDColors.h>
#include <math.h>
#define SPACESHIP_Y 160
#define SPACESHIP_RADIUS 15
 
/*
    Global variables for the score, lives, and spaceship x posisition
*/

int SPACESHIP_X = 140;
int SCORE = 0;
int LIVES = 3;
 
/*
    Function prototypes for the back button, background, and stars
*/

void BackButton();
void DrawBackground();
void DrawStars();

// Jacob + Max
/* 
   Stats Class that involves the high scores of 
   the game and the longest time survived.
   There is a constructor function that sets
   both of these values to zero.
   There are getter and setter functions for
   both of the variables. At the end, there is a 
   DisplayStats() function that is called from the
   main menu when the user selects the option.
*/

//Class for Game Statistics
class Stats
{
 
    private:
 
        float LongestSurvived;
        int HighScore;
 
    public:
 
        Stats() //Stats Constructer with parameters
        {
            LongestSurvived = 0.0;
            HighScore = 0;
        }
 
        float GetLongestSurvived()
        {
            return LongestSurvived;
        }
 
        int GetHighScore()
        {
            return HighScore;
        }
 
        void SetLongestSurvived(float a)
        {
            LongestSurvived = a;
        }
        
        void SetHighScore(int b)
        {
            HighScore = b;
        }
 
        //Displaying Statistics to Screen
        void DisplayStats()
        {
            LCD.Clear();
            LCD.SetFontColor(LIME);
            LCD.WriteLine(" ");
            LCD.Write("     The high score is: ");
            LCD.WriteLine(HighScore );
            LCD.Write("     The longest time survived is: ");
            LCD.Write((int)LongestSurvived );
            LCD.Write(" (s)");
            
            BackButton();
        }
};
 


//Jacob + Max
/* 
    Asteroid Class keeps the radius, x, y, and speed
    values for each asteroid object. There is a constructor 
    which initializes these values to random numbers.
    A MoveAsteroid() function which will move the asteroid
    down the screen based on the speed. A ResetAsteroid()
    function that checks to see if the object's y value
    has surpassed a certain threshold. If so, it will redraw
    the object at the top of the screen. This function also
    applies the difficulty value to the speed variable.
    The AsteroidCollision() function checks if the object 
    is touching the spaceship. If so, it will reset the 
    asteroid, redraw the spaceship, and return true.
*/

class Asteroid
{
 
    private:
 
        int x, y, radius, speed;
 
    public:
 
    Asteroid()
    {
        radius = (RandInt() % 12) + 5;
        x = (RandInt() % 300) + 14;
        y = (RandInt() % 10) + 14;
        speed = ((RandInt() % 3) + 3);
    }
 

    void MoveAsteroid()
    {
        LCD.SetDrawColor(BLACK);
        LCD.FillCircle(x, y, radius);
        LCD.SetDrawColor(GRAY);
        LCD.FillCircle(x, y + speed, radius);
        y += speed;
    }
 

    void ResetAsteroid(int y_dist, int difficulty)
    {
        if (y >= y_dist)
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillCircle(x, y, radius);
            y = 14;
            x = (RandInt() % 300) + 14;
            speed = ((RandInt() % 3) + 3)*difficulty;
        }
        
    }
 

    bool AsteroidCollision(int level)
    {

        bool collide = false;
        double dx, dy, D;
        
        dx = ::SPACESHIP_X-x;
        dy = SPACESHIP_Y-y;
 
        D  = sqrt(double (dx * dx + dy * dy));
 
        if (D <= SPACESHIP_RADIUS + radius)
        {
            collide = true;
            ResetAsteroid(145-radius, level);
            LCD.SetDrawColor(WHITE);
            LCD.FillRectangle(::SPACESHIP_X - 3,146,7,19);
            LCD.FillRectangle(::SPACESHIP_X - 13,161,26,5);
            LCD.SetDrawColor(RED);
            LCD.FillRectangle(::SPACESHIP_X + 7,152,4,9);
            LCD.FillRectangle(::SPACESHIP_X - 11,152,4,9);
            LCD.SetDrawColor(BLUE);
            LCD.FillRectangle(::SPACESHIP_X - 1,147,3,5);
        }
        return collide;
    }
    
};
 


//Jacob + Max
/* 
    Coin Class keeps the radius, x, y, and speed
    values for each coin object. There is a constructor 
    which initializes the x value to a random number and
    the rest of the variables to constants.
    A MoveCoin() function which will move the coin
    down the screen based on the speed. A ResetCoin()
    function that checks to see if the object's y value
    has surpassed a certain threshold. If so, it will redraw
    the object at the top of the screen.
    The CoinCollision() function checks if the object 
    is touching the spaceship. If so, it will reset the 
    coin, redraw the spaceship, and return true.
*/

class Coin
{
 
    private:
 
        int x, y, radius, speed;
 
    public:
 
    Coin()
    {
        radius = 12;
        x = (RandInt() % 300) + 14;
        y = 14;
        speed = 7;
    }
 

    void MoveCoin()
    {
        LCD.SetDrawColor(BLACK);
        LCD.FillCircle(x, y, radius);
        LCD.SetDrawColor(YELLOW);
        LCD.FillCircle(x, y + speed, radius);
        LCD.SetFontColor(BLACK);
        LCD.WriteAt('$', x-4, y-1);
        y += speed;
    }
 

    void ResetCoin(int y_dist)
    {
        if (y >= y_dist)
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillCircle(x, y, radius);
            y = 14;
            x = (RandInt() % 300) + 14;
        }
        
    }
 

    bool CoinCollision()
    {

        bool collide = false;
        double dx, dy, D;
        
        dx = ::SPACESHIP_X-x; 
        dy = SPACESHIP_Y-y; 
 
        D  = sqrt(double (dx * dx + dy * dy));
 
        if (D <= SPACESHIP_RADIUS + radius)
        {
            collide = true;
            ResetCoin(145-radius);
            LCD.SetDrawColor(WHITE);
            LCD.FillRectangle(::SPACESHIP_X - 3,146,7,19);
            LCD.FillRectangle(::SPACESHIP_X - 13,161,26,5);
            LCD.SetDrawColor(RED);
            LCD.FillRectangle(::SPACESHIP_X + 7,152,4,9);
            LCD.FillRectangle(::SPACESHIP_X - 11,152,4,9);
            LCD.SetDrawColor(BLUE);
            LCD.FillRectangle(::SPACESHIP_X - 1,147,3,5);
        }
        return collide;
    }
    
};
 


//Jacob + Max
 /* 
    PowerUp Class keeps the radius, x, y, and speed
    values for each powerup object. There is a constructor 
    which initializes the x value to a random number and
    the rest of the variables to constants.
    A MovePowerUp() function which will move the powerup
    down the screen based on the speed. A ResetPowerUp()
    function that checks to see if the object's y value
    has surpassed a certain threshold. If so, it will redraw
    the object at the top of the screen.
    The PowerUpCollision() function checks if the object 
    is touching the spaceship. If so, it will reset the 
    powerup, redraw the spaceship, and return true.
*/

class PowerUp
{
 
    private:
 
        int x, y, radius, speed;
 
    public:
 
    PowerUp()
    {
        radius = 10;
        x = (RandInt() % 300) + 14;
        y = 14;
        speed = 2;
    }
 

    void MovePowerUp()
    {
        LCD.SetDrawColor(BLACK);
        LCD.FillCircle(x, y, radius);
        LCD.SetDrawColor(GREEN);
        LCD.FillCircle(x, y + speed, radius);
        LCD.SetFontColor(BLACK);
        LCD.WriteAt('P', x-3, y-3);
        y += speed;
    }
 

    void ResetPowerUp(int y_dist)
    {
        if (y >= y_dist)
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillCircle(x, y, radius);
            y = 14;
            x = (RandInt() % 300) + 14;
        }
        
    }
 

    bool PowerUpCollision()
    {

        bool collide = false;
        double dx, dy, D;
        
        dx = ::SPACESHIP_X-x; 
        dy = SPACESHIP_Y-y; 
 
        D  = sqrt(double (dx * dx + dy * dy)); 
 
        if (D <= SPACESHIP_RADIUS + radius) 
        {
            collide = true;
            ResetPowerUp(145-radius);
            LCD.SetDrawColor(WHITE);
            LCD.FillRectangle(::SPACESHIP_X - 3,146,7,19);
            LCD.FillRectangle(::SPACESHIP_X - 13,161,26,5);
            LCD.SetDrawColor(RED);
            LCD.FillRectangle(::SPACESHIP_X + 7,152,4,9);
            LCD.FillRectangle(::SPACESHIP_X - 11,152,4,9);
            LCD.SetDrawColor(BLUE);
            LCD.FillRectangle(::SPACESHIP_X - 1,147,3,5);
        }
        return collide;
    }
    
};
 


/*
    Function Prototypes.
*/

void DisplayMainMenu();
void DisplayCredits();
void DisplayInstruction();
void DisplayGameOver();
void GameStartSequence();
 
void PlayGame(Stats *a);
int ChooseLevel();
 
void InitialDraw();
void DrawSpaceship();

void WritePoints(int b);
void WriteLives(int b);


 
//Jacob + Adam + David + Max
//--------------------------------------------------------//
 //--------------------Main Function---------------------//
 
 
int main()
{
 
    // Initializes variables
    int x, y;
    bool game = true;
 
    // Creates object for the stats
    Stats GameStats;
    Stats *StatsPTR = &GameStats;
 
    // While loop for running proteus simulator
    while(game)
    {
        // First, Display main menu
        DisplayMainMenu(); 

        // While loop for reading user input
        while(!LCD.Touch(&x, &y))
        {
            
        }
 
        // If the top 1/4 of the screen is touched --> Play game
        if(y < 60)
        {
            PlayGame(StatsPTR);
        }
        // If the 2nd/4th of the screen is touched --> Instructions are displayed
        if(y > 60 && y < 120)
        {
            DisplayInstruction();
        }
        // If the 3rd/4th of the screen is touched --> Stats are displayed
        if(y > 120 && y < 180)
        {
            GameStats.DisplayStats();
        }
        // If the bottom quarter of the screen is touched --> credits are displayed
        if(y > 180 && y < 240)
        {
            DisplayCredits();
        }
 
    }
 
}
 
//Jacob + Adam + Max + David
/*
    This function will display the main menu at
    the start of the game.
*/

void DisplayMainMenu()
{
    // Const char*s for the choices on the menu
    const char* BUTTON1TEXT = "Play Game";
    const char* BUTTON2TEXT = "Game Instructions";
    const char* BUTTON3TEXT = "Game Stats";
    const char* BUTTON4TEXT = "Credits";
 
    // This will create 4 different color rectangles so that the  
    // 4 sections of the screen will be clear play Game Tab
    LCD.SetDrawColor(RED);
    LCD.FillRectangle(0, 0, 320, 60);
 
    // Game Instruction Tab
    LCD.SetDrawColor(BLUE);
    LCD.FillRectangle(0, 60, 320, 60);
 
    // Game Stats Tab
    LCD.SetDrawColor(RED);
    LCD.FillRectangle(0, 120, 320, 60);
 
    // Credit Tab
    LCD.SetDrawColor(BLUE);
    LCD.FillRectangle(0, 180, 320, 60);
 
    // Left Black Screen for Game Title/Cover
    LCD.SetDrawColor(BLACK);
    LCD.FillRectangle(0, 0, 130, 240);
 
    // Title Box
    LCD.SetDrawColor(RED);
    LCD.DrawRectangle(10,85,115,45);
    
    // Draws three horizontal black lines to divide 
    // buttons 3 pixels thick in between each rectangle
    LCD.SetDrawColor(LCD.Black);
    LCD.DrawHorizontalLine(59, 0, 319);
    LCD.DrawHorizontalLine(60, 0, 319);
    LCD.DrawHorizontalLine(61, 0, 319);
    LCD.DrawHorizontalLine(119, 0, 319);
    LCD.DrawHorizontalLine(120, 0, 319);
    LCD.DrawHorizontalLine(121, 0, 319);
    LCD.DrawHorizontalLine(179, 0, 319);
    LCD.DrawHorizontalLine(180, 0, 319);
    LCD.DrawHorizontalLine(181, 0, 319);
 
    // Game Title/Cover
    LCD.SetFontColor(RED);
    LCD.WriteAt("Avoid",40,90);
    LCD.WriteAt("The Asteroids",15,110);
    LCD.SetFontColor(WHITE);
 
    // Draw Saturn/Satellite
    LCD.SetDrawColor(OLIVE);
    LCD.FillCircle(90,60,10);
    LCD.SetDrawColor(GRAY);
    LCD.DrawLine(75,75,105,45);
    LCD.DrawLine(78,78,108,48);
 
    // Draw Earth
    LCD.SetDrawColor(BLUE);
    LCD.FillCircle(40,185,20);
    LCD.SetDrawColor(GREEN);
    LCD.FillCircle(30,185,5);
    LCD.FillCircle(35,190,5);
    LCD.FillCircle(40,182,8);
    LCD.FillCircle(50,195,4);
 
    // Write function text to quarters of screen
    LCD.WriteAt(BUTTON1TEXT, 150, 25);
    LCD.WriteAt(BUTTON2TEXT, 150, 85);
    LCD.WriteAt(BUTTON3TEXT, 150, 145);
    LCD.WriteAt(BUTTON4TEXT, 150, 205);
}


//Jacob + Adam + Max + David
/*
    This is the function for displaying instructions
    when the option is selected from the main menu.
*/

void DisplayInstruction()
{
    // Displaying instructions
    LCD.Clear();
    LCD.WriteLine(" ");
    LCD.WriteLine("  Game Instructions:");
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteLine("  Stay alive as long as possible.");
    LCD.WriteLine("  Use the arrow buttons to move the ");
    LCD.WriteLine("  spaceship left and right.");
    LCD.WriteLine("  Collect power-ups and coins along the ");
    LCD.WriteLine("  way and dodge the incoming asteroids.");
    LCD.WriteLine("  Asteroids: Gray, Coins: Gold, ");
    LCD.Write("  Powerup: Green.");
 
 
    // Includes the back button function
    BackButton();
}
 

//Jacob + Adam + Max + David
/*
    This is the function for displaying credits
    when the user chooses the option from the
    main menu.
*/

void DisplayCredits()
{
    // Writes out the names of all the developers
    LCD.Clear();
    LCD.WriteAt("Developers:", 107,20);
    LCD.SetFontColor(RED);
    LCD.WriteAt("Max Starr", 115,55);
    LCD.WriteAt("Adam Farrell", 104,80);
    LCD.WriteAt("Jacob Kasmarcak", 88,105);
    LCD.WriteAt("David Kuntz",112,130);
 
    // Writes the game referenced
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Game Reference: Dodger",60,160);
 
    // Writes The Ohio State University at the bottom
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("The Ohio State University",51,221);
    LCD.SetFontColor(RED);
    LCD.WriteAt("The Ohio State University",50,220);
 
    // Includes the back button function
    BackButton();
}


//Max Starr
/*
    Function that creates and provides
    the logic for the back button.
*/

void BackButton()
{
    // Initializes the variables necessary for the back button
    int x, y;
    bool back = true;
 
    // Sets the colors to white for the font and the outside of the rectangle
    LCD.SetFontColor(LCD.White);
    LCD.SetDrawColor(LCD.White);
    LCD.DrawRectangle(263,206,50,30);   
    LCD.WriteAt("Back",270,213);
 
    // Loop that if the back button is touched it will return to the main screen
    while(back)
    {
        while(!LCD.Touch(&x, &y))
        {
        }
        if(x > 263 && x < 313 && y > 206 && y < 236)
        {
            back = false;
            LCD.Clear();
        }
    }
}
 

//Jacob
/*
    This function will run the game. It creates 
    variables to track statistics. This function
    creates the asteroid, coin, and powerup objects.
    It will start and draw the game. It checks for 
    collision and moves each of the objects.
    Finally, it keeps your overall stats and 
    displays game over once the user has lost.
*/

void PlayGame(Stats *Statistics)
{
    // Initializes te variables for the levels, lives
    // score multiplier, old score, and old lives
    int level;
    bool alive = true;
    int multiplier = 1;
    int oldscore = 0;
    int oldlives = 3;

    // Resets the global variables
    ::LIVES = 3;
    ::SCORE = 0;
    ::SPACESHIP_X = 140;
 
    // Creates an array of 7 asteroid objects
    Asteroid arr[7];
 
    // Creates an array of 2 coin objects
    Coin coinArr[2];

    // Creates a powerup object
    PowerUp Pow;
 
    // Clear screen
    LCD.Clear();
    
    // Set difficulty level based on users choice
    level = ChooseLevel();
 
    // Display countdown timer
    GameStartSequence();
    
    // Draws the initial parts of the game
    InitialDraw();
 
    //Draws stars at the beginning of the game
    DrawStars();
 
    //Keeps track of when the user started the game
    double t_start = TimeNow();
 
    // Loop representing while the player is alive
    while(alive)
    {
        // Call to WritePoints and set old score equal to score
        WritePoints(oldscore);
        oldscore = ::SCORE;

        // Call to WriteLives and set old lives equal to lives
        WriteLives(oldlives);
        oldlives = ::LIVES;

        // Draws and moves the spaceship
        DrawSpaceship(); 

        // If statement that will redraw the stars and planets peroidically
        if(((int)TimeNow() % 6) == 0)
        {
            DrawStars();
        }

        // For loop that moves the asteroids, resets them if
        // necessary, checks for collision, and adjusts lives accordingly
        for(int i = 0; i < 7; i++)
        {
            arr[i].MoveAsteroid();
            arr[i].ResetAsteroid(157, level);
            if(arr[i].AsteroidCollision(level))
            {
                ::LIVES -= 1;
            }
        }

        // For loop that moves the coins, resets them if
        // necessary, checks for collision, and adjusts 
        // score accordingly based on the multiplier
        for (int i = 0; i < 2; i++)
        {
            coinArr[i].MoveCoin();
            coinArr[i].ResetCoin(160);
            if(coinArr[i].CoinCollision())
            {
                ::SCORE += 10 * multiplier;
            }
        }
        
        // Moves the powerups, resets them if necessary, checks
        // for collision, and adjusts lives and the multiplier accordingly

        Pow.MovePowerUp();
        Pow.ResetPowerUp(160);
        if(Pow.PowerUpCollision())
        {
            int type = RandInt()%2;
            if(type == 0)
            {
                ::LIVES ++;
            }
            else if(type == 1)
            {
                multiplier++;
            }
        }
 
        // If statement to evaluate whether or not the 
        // player is alive based on LIVES
        if(::LIVES <= 0)
        {
            alive = false;
        }
    }

    // Sets the end time and calculates the total time survived
    double t_end = TimeNow();
    double t_survived = t_end - t_start;
 
    // If player survived longer than previous record,
    // then set it to the longest survived
    if (Statistics->GetLongestSurvived() <= t_survived)
    {
        Statistics->SetLongestSurvived(t_survived);
    }
    
    // If player got more points than the previous record,
    // then set it to the highest score
    if(Statistics->GetHighScore() < ::SCORE)
    {
        Statistics->SetHighScore(::SCORE);
    }

    // Displays the game over sequence
    DisplayGameOver();

    // Keeps game over on the screen for 3 seconds
    Sleep(3.0);
    
}
 

//David
/*
    The ChooseLevel() function is called in the
    Play game function and allows the user to select 
    between easy and hard difficulties. It returns
    an integer, 1 or 2, which specifies difficulty.
*/

int ChooseLevel()
{
    // Initializes variables for the choose level function
    int level, x, y; 
 
    // Drawing the easy mode selection 
    LCD.SetDrawColor(LCD.Blue);
    LCD.FillRectangle(0, 0, 320, 120);
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("Easy", 140, 50);
 
    // Drawing the hard mode selection 
    LCD.SetDrawColor(LCD.Red);
    LCD.FillRectangle(0, 120, 320, 120);
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("Hard", 140, 170);
 
    // While loop for reading user input
        while(!LCD.Touch(&x, &y))
        {
            
        }
 
        // If the top 1/2 of the screen is touched --> Easy
        if(y < 120)
        {
            level = 1;
        }
        // If the bottom half of the screen is touched --> Hard
        if(y > 120 && y < 240)
        {
            level = 2;
        }
 
        return level;
}
 

//David
/*
    This function draws the spaceship and 
    checks to see if the user has touched the
    screen. If the left side is touched, the 
    spaceship will move left. If the right side
    is touched, the spaceship will move right.
*/

void DrawSpaceship()
{
    
    // Initializes the variables
    int x, y;
 
    // Determines where the screen was touched
    while(LCD.Touch(&x, &y))
    {
        // Determines which side was touched
        if (x > 0 && x < 170)
        {
 
            // Changes the position of the spaceship to the left
            ::SPACESHIP_X -= 10;
 
            // Keeps the spaceship on the screen
            if  (::SPACESHIP_X < 15)
            {
                ::SPACESHIP_X = 15;
            }
 
            // Draws Spaceship in new spot to the left
            LCD.SetDrawColor(BLACK);
            LCD.FillCircle(::SPACESHIP_X + 10, 160, SPACESHIP_RADIUS + 4);
            LCD.SetDrawColor(WHITE);
            LCD.FillRectangle(::SPACESHIP_X - 3, 146,7,19);
            LCD.FillRectangle(::SPACESHIP_X - 13, 161,26,5);
            LCD.SetDrawColor(RED);
            LCD.FillRectangle(::SPACESHIP_X + 7, 152,4,9);
            LCD.FillRectangle(::SPACESHIP_X - 11, 152,4,9);
            LCD.SetDrawColor(BLUE);
            LCD.FillRectangle(::SPACESHIP_X - 1,147,3,5);
        
        }
        else if (x > 170 && x < 340)
        {
 
            // Changes the position of the spaceship to the right
            ::SPACESHIP_X += 10;
 
            // Keeps the spaceship on the screen
            if (::SPACESHIP_X > 305)
            {
                ::SPACESHIP_X = 305;
            }
 
            // Draws Spaceship in new spot to the right
            LCD.SetDrawColor(BLACK);
            LCD.FillCircle(::SPACESHIP_X - 10, 160, SPACESHIP_RADIUS + 4);
            LCD.SetDrawColor(WHITE);
            LCD.FillRectangle(::SPACESHIP_X - 3, 146,7,19);
            LCD.FillRectangle(::SPACESHIP_X - 13, 161,26,5);
            LCD.SetDrawColor(RED);
            LCD.FillRectangle(::SPACESHIP_X + 7, 152,4,9);
            LCD.FillRectangle(::SPACESHIP_X - 11, 152,4,9);
            LCD.SetDrawColor(BLUE);
            LCD.FillRectangle(::SPACESHIP_X - 1,147,3,5);
 
 
        }
        
        
    }
}
 
 
//David
/*
    Writes the number of points the user 
    has to the scoreboard if the number
    of points has changed.
*/

void WritePoints(int OldScore)
{
    if(::SCORE != OldScore)
    {
        // Erases old points
        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(10, 185, 65, 50);
        
        // Writes the score the user has to the screen
        LCD.SetFontColor(LCD.White);
        LCD.WriteAt("Points: ", 12, 195);
        LCD.WriteAt(::SCORE, 14, 215);
    }
}
 

//David
/*
    Writes the number of lives the user 
    has to the scoreboard if the number
    of lives has changed.
*/

void WriteLives(int OldLives)
{
    if(::LIVES != OldLives)
    {
        // Erases old lives
        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(245, 200, 74, 39);

        // Writes the lives the user has to the screen
        LCD.SetFontColor(LCD.White);
        LCD.WriteAt("Lives: ", 250,205);
        LCD.WriteAt(::LIVES, 300, 206);
    }    
}
 

//David + Adam
/*
    This function draws the initial spaceship,
    lives, score, and background.
*/

void InitialDraw()
{
    // Draws background at the beginning 
    DrawBackground();
 
    // Draws the original spaceship
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(::SPACESHIP_X - 3,146,7,19);
    LCD.FillRectangle(::SPACESHIP_X - 13,161,26,5);
    LCD.SetDrawColor(RED);
    LCD.FillRectangle(::SPACESHIP_X + 7,152,4,9);
    LCD.FillRectangle(::SPACESHIP_X - 11,152,4,9);
    LCD.SetDrawColor(BLUE);
    LCD.FillRectangle(::SPACESHIP_X - 1,147,3,5);
    // LCD.DrawCircle(::SPACESHIP_X, 160, SPACESHIP_RADIUS); (Hit box testing)
    
    // Writes the original lives the user has to the screen (3)
    LCD.SetFontColor(LCD.White);
    LCD.WriteAt("Lives: ", 250,205);
    LCD.WriteAt(::LIVES, 300, 206);

    // Writes the original score the user has to the screen (0)
    LCD.WriteAt("Points: ", 12, 195);
    LCD.WriteAt(::SCORE, 14, 215);
 
}
 

//Jacob
/*
    This function displays the countdown timer 
    once the game has been started.
*/

void GameStartSequence()
{
    // Clears the screen, writes the number of seconds left,
    // and sleeps for 1 second. This is repeated till GO!
    LCD.Clear();
    Sleep(0.5); 

    LCD.WriteAt("3", 156, 118);
    Sleep(1.0);
    LCD.Clear();

    LCD.WriteAt("2", 156, 118);
    Sleep(1.0);
    LCD.Clear();

    LCD.WriteAt("1", 156, 118);
    Sleep(1.0);
    LCD.Clear();

    LCD.WriteAt("GO!", 153, 118);
    Sleep(1.0);
    LCD.Clear();
}


//Adam
/*
    Draws horizontal line separating gameplay
    from the control panel/where points are 
    displayed; creates arrow controls
*/
void DrawBackground()
{
   // Clear screen
   LCD.Clear();
 
   // Set draw color
   LCD.SetDrawColor(GRAY);
 
   // Draw horizontal line for separating UI
   LCD.DrawHorizontalLine(180,0,319);
 
   // Draw arrow buttons
   LCD.FillRectangle(90,185,50,50);
   LCD.FillRectangle(180,185,50,50);
 
   // Set draw color
   LCD.SetDrawColor(WHITE);
   
   // Outline rectangles
   LCD.DrawRectangle(180,185,50,50);
   LCD.DrawRectangle(90,185,50,50);
 
   // Arrow tail
   LCD.DrawLine(100,210,130,210);
   LCD.DrawLine(190,210,220,210);
 
   // Arrow head for left arrow
   LCD.DrawLine(100,210,108,202);
   LCD.DrawLine(100,210,108,218);
 
   // Arrow head for right arrow
   LCD.DrawLine(220,210,212,202);
   LCD.DrawLine(220,210,212,218);
}
 

//Adam
/*
    Draws stars in the background of gameplay;
    each star composed of 4 lines and drawn in 3
    separate rows as designated by for loops.  Also
    includes pixel art for Earth and another Space
    Object/Planet.
*/ 
 
void DrawStars()
{
    // Initialize xstar and ystar
    int xstar=100, ystar=10, i;
 
    // Change Draw Color
    LCD.SetDrawColor(GRAY);
 
    // For loop for drawing 1st row of stars
    for (i=1;i<3;i++)
    {

        // Initializes all the star variables
        int xstar1s=0,xstar1e=0,xstar2s=0,xstar2e=0,xstar3s=0,xstar3e=0,xstar4s=0,xstar4e=0;
        int ystar1s=0,ystar1e=0,ystar2s=0,ystar2e=0,ystar3s=0,ystar3e=0,ystar4s=0,ystar4e=0;
        xstar1s=xstar;
        ystar1s=ystar;
        xstar1e=xstar1s+6;
        ystar1e=ystar1s+6;
        xstar2s=xstar1s+3;
        xstar2e=xstar2s;
        ystar2s=ystar1s;
        ystar2e=ystar1s+1;
        xstar3s=xstar1s;
        xstar3e=xstar1s+6;
        ystar3s=ystar1s+6;
        ystar3e=ystar1s;
        xstar4s=xstar1s;
        xstar4e=xstar1s+6;
        ystar4s=ystar1s+3;
        ystar4e=ystar1s+3;
        LCD.DrawLine(xstar1s,ystar1s,xstar1e,ystar1e);
        LCD.DrawLine(xstar2s,ystar2s,xstar2e,ystar2e);
        LCD.DrawLine(xstar3s,ystar3s,xstar3e,ystar3e);
        LCD.DrawLine(xstar4s,ystar4s,xstar4e,ystar4e);
        xstar+=90;
    }
   
    // Initialize star variables
    xstar=40;
    ystar=60;

    // For loop for drawing 2nd row of stars
    for (i=1;i<4;i++)
    {

        // initializes all the star variables
        int xstar1s=0,xstar1e=0,xstar2s=0,xstar2e=0,xstar3s=0,xstar3e=0,xstar4s=0,xstar4e=0;
        int ystar1s=0,ystar1e=0,ystar2s=0,ystar2e=0,ystar3s=0,ystar3e=0,ystar4s=0,ystar4e=0;
        xstar1s=xstar;
        ystar1s=ystar;
        xstar1e=xstar1s+6;
        ystar1e=ystar1s+6;
        xstar2s=xstar1s+3;
        xstar2e=xstar2s;
        ystar2s=ystar1s;
        ystar2e=ystar1s+1;
        xstar3s=xstar1s;
        xstar3e=xstar1s+6;
        ystar3s=ystar1s+6;
        ystar3e=ystar1s;
        xstar4s=xstar1s;
        xstar4e=xstar1s+6;
        ystar4s=ystar1s+3;
        ystar4e=ystar1s+3;
        LCD.DrawLine(xstar1s,ystar1s,xstar1e,ystar1e);
        LCD.DrawLine(xstar2s,ystar2s,xstar2e,ystar2e);
        LCD.DrawLine(xstar3s,ystar3s,xstar3e,ystar3e);
        LCD.DrawLine(xstar4s,ystar4s,xstar4e,ystar4e);
        xstar+=100;
    }
 
    // Initialize star variables
    xstar=20;
    ystar=110;
 
    // For loop for drawing 3rd row of stars
    for (i=1;i<5;i++)
    {

        // initializes all the star variables
        int xstar1s=0,xstar1e=0,xstar2s=0,xstar2e=0,xstar3s=0,xstar3e=0,xstar4s=0,xstar4e=0;
        int ystar1s=0,ystar1e=0,ystar2s=0,ystar2e=0,ystar3s=0,ystar3e=0,ystar4s=0,ystar4e=0;
        xstar1s=xstar;
        ystar1s=ystar;
        xstar1e=xstar1s+6;
        ystar1e=ystar1s+6;
        xstar2s=xstar1s+3;
        xstar2e=xstar2s;
        ystar2s=ystar1s;
        ystar2e=ystar1s+1;
        xstar3s=xstar1s;
        xstar3e=xstar1s+6;
        ystar3s=ystar1s+6;
        ystar3e=ystar1s;
        xstar4s=xstar1s;
        xstar4e=xstar1s+6;
        ystar4s=ystar1s+3;
        ystar4e=ystar1s+3;
        LCD.DrawLine(xstar1s,ystar1s,xstar1e,ystar1e);
        LCD.DrawLine(xstar2s,ystar2s,xstar2e,ystar2e);
        LCD.DrawLine(xstar3s,ystar3s,xstar3e,ystar3e);
        LCD.DrawLine(xstar4s,ystar4s,xstar4e,ystar4e);
        xstar+=85;
    }
 
    //Draw Earth
    LCD.SetDrawColor(BLUE);
    LCD.FillCircle(280,35,20);
    LCD.SetDrawColor(GREEN);
    LCD.FillCircle(270,35,5);
    LCD.FillCircle(275,40,5);
    LCD.FillCircle(280,32,8);
    LCD.FillCircle(290,45,4);
 
    //Draw Saturn/Satellite whatever it is
    LCD.SetDrawColor(OLIVE);
    LCD.FillCircle(90,60,10);
    LCD.SetDrawColor(GRAY);
    LCD.DrawLine(75,75,105,45);
    LCD.DrawLine(78,78,108,48);
    LCD.SetDrawColor(GRAY);
}
 

//Adam 
/*
    Displays animated game over screen
    after the player loses all 3 lives.
*/ 

void DisplayGameOver()
{
    //Clear the screen
    LCD.Clear();

    //Change font color to red
    LCD.SetDrawColor(RED);

    //Draw out "Game Over" with animation
    //Draw "G"
    LCD.DrawLine(50,70,90,70);
    Sleep(130);
    LCD.DrawLine(50,70,50,120);
    Sleep(130);
    LCD.DrawLine(50,120,90,120);
    Sleep(130);
    LCD.DrawLine(90,120,90,95);
    Sleep(130);
    LCD.DrawLine(90,95,70,95);
    Sleep(130);

    //Draw "A"
    LCD.DrawLine(105,120,105,70);
    Sleep(130);
    LCD.DrawLine(105,70,145,70);
    Sleep(130);
    LCD.DrawLine(145,70,145,120);
    Sleep(130);
    LCD.DrawLine(105,95,145,95);
    Sleep(130);

    //Draw "M"
    LCD.DrawLine(160,120,160,70);
    Sleep(130);
    LCD.DrawLine(160,70,185,70);
    Sleep(130);
    LCD.DrawLine(185,70,185,120);
    Sleep(130);
    LCD.DrawLine(185,70,210,70);
    Sleep(130);
    LCD.DrawLine(210,70,210,120);
    Sleep(130);

    //Draw "E"
    LCD.DrawLine(225,120,225,70);
    Sleep(130);
    LCD.DrawLine(225,70,265,70);
    Sleep(130);
    LCD.DrawLine(225,95,265,95);
    Sleep(130);
    LCD.DrawLine(225,120,265,120);
    Sleep(130);

    //Draw "O"
    LCD.DrawLine(50,135,90,135);
    Sleep(130);
    LCD.DrawLine(90,135,90,185);
    Sleep(130);
    LCD.DrawLine(90,185,50,185);
    Sleep(130);
    LCD.DrawLine(50,185,50,135);
    Sleep(130);

    //Draw "V"
    LCD.DrawLine(105,135,105,185);
    Sleep(130);
    LCD.DrawLine(105,185,145,185);
    Sleep(130);
    LCD.DrawLine(145,185,145,135);
    Sleep(130);

    //Draw "E"
    LCD.DrawLine(155,135,155,185);
    Sleep(130);
    LCD.DrawLine(155,135,195,135);
    Sleep(130);
    LCD.DrawLine(155,160,195,160);
    Sleep(130);
    LCD.DrawLine(155,185,195,185);

    //Draw "R"
    LCD.DrawLine(210,135,250,135);
    Sleep(130);
    LCD.DrawLine(210,135,210,185);
 
}
 
 
 

