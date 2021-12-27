/************************************************************************************/
/* Name: Ryan Pochek, Michael Valcarcel, Jack Dennis, Charlie Farmer Date: 11/12/20 */
/* File: APP_B38_3.cpp                                                              */
/* Instructor: Freuler 12:40                                                        */
/************************************************************************************/
/*Libraries*/
#include "FEHLCD.h"
#include "FEHRandom.h"
#include <string.h>
#include "FEHUtility.h"
 
/*Definitions*/
#define YMAX 249
#define XMAX 319
#define BUTTON1 "One Player and AI"
#define BUTTON2 "Two Player"
#define BUTTON3 "Three Player"
#define BUTTON4 "Four Player"
#define BUTTON1TEXT "Play Game"
#define BUTTON2TEXT "See Statistics"
#define BUTTON3TEXT "See Instructions"
#define BUTTON4TEXT "Credits"
/**
* Entry point to the application.
*
* @returns status code of program exit
*/
/*Class Player is defined with all public variables and functions*/
/*Description: The player class object will be instantiated 5 times in the beginning of the 
int main. The player objects will be p1, p2, p3, p4, and ai to create player for single player
all the way up to 4 player multiplayer. There are no private data members in the class player. 
The public members of the class player include a default constructor player, a member function
spot that passes in the objects block location and moves the pawn to the updated block. The other 
data member variables include the information for key statistics of our game including # of ladders
used, # of slides used, num_blocks traveled, average blocks traveled, # of players eaten, and turns taken. 
Purpose: The purpose of this class is to be more efficient when tracking each player's location, statistics, 
and decisions by in the function and int main below just having to specify the player whos turn it is and modifying
the intended data for that player alone. For example: If player 1 were to roll a 3, the p1.block could be called and 
incremented by 3. This approach is very easy for multiplayer and only adjusting certain players at a time.
Author: Ryan Pochek*/
class Player
{
private:

public:
   /*Variables declared to allow for game to function and for keeping stats*/
   int block = 1;
   char name[20];
   int x = 0;
   int y = 0;
   int turns = 0;
   int ladder = 0;
   int slide = 0;
   int num_blocks = 0;
   int eaten = 0;
   float avg_blocks = 0;
   float total_time = 0;
   Player(char [] = "Dr. Rick");
   void Spot(int block);
};
 
/*All function prototypes are declared with names that describe what they do*/
/*Attribution section precedes the function definitions below int main*/
void set_game_board(int n, Player p1, Player p2, Player p3, Player p4, Player ai, int current, int roll, int test, int timer);
void DrawPlayer();
void RollDice(int &n, int &current, Player &p1, Player &p2, Player &p3, Player &p4, Player &ai);
void check_winner(int &n, Player p1, Player p2, Player p3, Player p4, Player ai);
void draw_winner(Player winner);
void DrawMenu();
void ShowInstructions();
void ShowCredits();
void Display_Results();
void ShowStats(Player p1, Player p2, Player p3, Player p4, Player ai);
 
/*Main function*/
int main() {
    /*Variables declared for main*/
    int total_turns = 0;
    int winner = 1;
    int current = -1;
    int r = 0;
    int test = 0;
    int timer = 0;
 
    /*Players are entered*/
 
    /*Initial locations are set for each player*/
    Player p1("Player 1");
    Player p2("Player 2");
    Player p3("Player 3");
    Player p4("Player 4");
    Player ai("Computer");
   
    int x, y, x1, y1, num;
    
    /*Menu is drawn*/
    DrawMenu();
    
    /*While loop to run the menu continuously*/
    while (1)
    {
    
    /*Initializes touch*/
        while (LCD.Touch(&x1,&y1))
        {
        }
        
        /*Touch for menu*/
        while (!LCD.Touch(&x,&y))
        {
        }
        
        /*Game Play touch*/
        if (y < 239/4 && y > 0)
        {
           
            /*Variables declared for winner and and whose turn it is*/ 
            winner = 1;
            total_turns = 0;
            current = -1;
            r = 0;
            test = 0;
            p1.block = 1;
            p2.block = 1;
            p3.block = 1;
            p4.block = 1;
            ai.block = 1;
            p1.x = XMAX/12 - 20;
            p1.y = YMAX/14*13.5;
            p2.x = XMAX/12 - 10;
            p2.y = YMAX/14*13.5;
            p3.x = XMAX/12;
            p3.y = YMAX/14*13.5;
            p4.x = XMAX/12 + 10;
            p4.y = YMAX/14*13.5;
            ai.x = XMAX/12 - 10;
            ai.y = YMAX/14*13.5;
            
            /*Menu is drawn*/
            DrawPlayer();
            
            /*Touch is initialized*/
            while (LCD.Touch(&x1,&y1))
            {
            }
            
            /*Touch for menu*/
            while (!LCD.Touch(&x,&y))
            {
            }
            
            /*Single Player object instantiation*/
            if (y < 239/4 && y > 0)
            {
                num = 1;
            }
            
            /*Two Player object instantiation*/
            if (y < 239/2 && y > 239/4)
            {
                num = 2;
            }
            
            /*Three Player object instantiation*/
            if (y < 239*.75 && y > 239/2)
            {
                num = 3;
            }
            
            /*Four Player object instantiation*/
            if (y > 239*.75 && y < 239)
            {
                num = 4;  
            }
            
            /*Touch is initialized*/
            while (LCD.Touch(&x1,&y1))
            {
            }
            
            /*Game board is set*/
            set_game_board(num, p1, p2, p3, p4, ai, current, r, test, timer);
            
            /*While loop until winner is found*/
            while (winner == 1)
            {
                
                /*Current turn is calculated here*/   
                current = total_turns % num;
                
                /*Initialize touch to wait to roll the dice*/
                while (!LCD.Touch(&x, &y))
                {
                }
                
                /*Dice roll*/
                if (x > 0 && x < XMAX/6 && y > 0 && y < YMAX/7)
                {
                    /*Dice roll function called*/
                    RollDice(num,current, p1, p2, p3, p4, ai);
                    
                    /*Check for winner function called*/
                    check_winner(winner, p1, p2, p3, p4, ai);
                }
                
                /*Total turns is incremented by 1 after each loop*/
                total_turns = total_turns + 1;
                
                /*Touch is initialized*/
                while (LCD.Touch(&x1,&y1))
                {
                }
            }
        }
        
        /*Statistics touch*/
        if (y < 239/2 && y > 239/4)
        {
            ShowStats(p1, p2, p3, p4, ai);
        }
        
        /*Instructions touch*/
        if (y < 239*.75 && y > 239/2)
        {
            ShowInstructions();
        }
        
        /*Credits touch*/
        if (y > 239*.75 && y < 239)
        {
            ShowCredits();
        }
        
        /*Back button is created*/
        LCD.SetDrawColor(LCD.Red);
        LCD.FillRectangle(319-50, 239-50, 50, 50);
        LCD.WriteAt("Back", 275, 210);
        
        /*Touch is initialized*/
        while (LCD.Touch(&x1,&y1))
        {
        }
        
        /*Back button touch*/
        while (!LCD.Touch(&x,&y))
        {
        }
        
        /*Resets to menu if back button is touched*/
        if (x > 319-50 && y > 239-50)
        {
            DrawMenu();
        }
    }   
    return 0;
}

/* Member function set_game_board
Description: The set_game_board function is a void function that does not pass a value
into another variable, but rather updates the game board with new locations of pawns after
each players turn along with a fresh game board at the start of the game. The input arguments 
needed for set_game_board are n which dictates if the game is over or not, all player objects p1
p2, p3, p4, and ai, current which holds the current player's turn, roll which holds the value of the dice,
and test which is another copy of roll that isn't modified and can be used to test for special features output. 
Purpose: The purpose of the function set_game_board is to update the game board at the beginning of the game, after each
player's turn, and when a special move is required for the user to select a choice. It's very universal and can be called
by any function when there is a need for the game board to be updated. 
Author: Michael Valcarcel*/

void set_game_board(int n, Player p1, Player p2, Player p3, Player p4, Player ai, int current, int roll, int test, int timer)
{
    /*Clears screen*/
    LCD.Clear();
    if (timer == 1){
        LCD.WriteAt("You Have 30 second to win", XMAX/5, YMAX/7);
    }
    /*Tests for special moves*/

    /*If a player rolls a 4*/
    if (test == 4){
        /*Prompts current user on their choices*/
        LCD.SetDrawColor(RED);
        LCD.FillRectangle(0, YMAX/14, XMAX/2, YMAX/14);
        LCD.SetDrawColor(GRAY);
        LCD.FillRectangle(XMAX/2, YMAX/14, XMAX/2, YMAX/14);
        LCD.WriteAt("Forward 4", XMAX/5, YMAX/14);
        LCD.WriteAt("Back 4", XMAX/5*3.5, YMAX/14);
   }
 
    /*If a player rolls a 2*/
    if (test == 2)
    {
        /*Prompts current user on their choices*/
        LCD.SetDrawColor(RED);
        LCD.FillRectangle(0, YMAX/14, XMAX/2, YMAX/14);
        LCD.SetDrawColor(GRAY);
        LCD.FillRectangle(XMAX/2, YMAX/14, XMAX/2, YMAX/14);
        LCD.WriteAt("Forward 2", XMAX/5, YMAX/14);
        LCD.WriteAt("Closest Object", XMAX/5*3, YMAX/14);
    }
    /*Game board is drawn*/

    /*Block O in center*/
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(XMAX/2-53, YMAX/2-63, 106, 139);
    LCD.SetDrawColor(RED);
    LCD.FillRectangle(XMAX/2-50, YMAX/2-60, 100, 133);
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(XMAX/2-26, YMAX/2-35, 50, 83);
    LCD.SetDrawColor(BLACK);
    LCD.FillRectangle(XMAX/2-23, YMAX/2-32, 44, 77);
    LCD.SetDrawColor(WHITE);
 
    /*6 by 6 board*/
    LCD.DrawHorizontalLine(YMAX/7, 0, XMAX);
    LCD.DrawHorizontalLine(YMAX/7 * 2, 0, XMAX);
    LCD.DrawHorizontalLine(YMAX/7 * 3, 0, XMAX);
    LCD.DrawHorizontalLine(YMAX/7 * 4, 0, XMAX);
    LCD.DrawHorizontalLine(YMAX/7 * 5, 0, XMAX);
    LCD.DrawHorizontalLine(YMAX/7 * 6, 0, XMAX);
    LCD.DrawVerticalLine(XMAX/6, YMAX/7, YMAX);
    LCD.DrawVerticalLine(XMAX/6 * 2, YMAX/7, YMAX);
    LCD.DrawVerticalLine(XMAX/6 * 3, YMAX/7, YMAX);
    LCD.DrawVerticalLine(XMAX/6 * 4, YMAX/7, YMAX);
    LCD.DrawVerticalLine(XMAX/6 * 5, YMAX/7, YMAX);
 
    /*Ladders are drawn*/
    LCD.SetDrawColor(BLUE);
    LCD.DrawLine(XMAX/18*4, YMAX/14*13, XMAX/18*10, YMAX/14*7);
    LCD.DrawLine(XMAX/18*5.5, YMAX/14*13, XMAX/18*11.5, YMAX/14*7);
    LCD.DrawHorizontalLine(YMAX/14*13, XMAX/18*4, XMAX/18*5.5);
    LCD.DrawHorizontalLine(YMAX/14*7, XMAX/18*10, XMAX/18*11.5);
    LCD.DrawLine(XMAX/18*13.25, YMAX/14*11, XMAX/18*16.25, YMAX/14*9);
    LCD.DrawLine(XMAX/18*14.75, YMAX/14*11, XMAX/18*17.75, YMAX/14*9);
    LCD.DrawHorizontalLine(YMAX/14*11, XMAX/18*13.25, XMAX/18*14.75);
    LCD.DrawHorizontalLine(YMAX/14*9, XMAX/18*16.25, XMAX/18*17.75);
 
    /*Slides are drawn*/
    LCD.SetDrawColor(GRAY);
    LCD.DrawLine(XMAX/18*.5, YMAX/14*5.25, XMAX/18*4, YMAX/14*9.25);
    LCD.DrawLine(XMAX/18*2.5, YMAX/14*5.25, XMAX/18*6, YMAX/14*9.25);
    LCD.DrawHorizontalLine(YMAX/14*5.25, XMAX/18*.5, XMAX/18*2.5);
    LCD.DrawHorizontalLine(YMAX/14*9.25, XMAX/18*4, XMAX/18*6);
    LCD.DrawLine(XMAX/18*10, YMAX/14*3, XMAX/18*13, YMAX/14*7);
    LCD.DrawLine(XMAX/18*11, YMAX/14*3, XMAX/18*14, YMAX/14*7);
    LCD.DrawHorizontalLine(YMAX/14*3, XMAX/18*10, XMAX/18*11);
    LCD.DrawHorizontalLine(YMAX/14*7, XMAX/18*13, XMAX/18*14);
 
    /*Finish block*/
    LCD.WriteAt("Finish", 0, YMAX/7 + 10);
 
    /*Arrows to navigate players*/
    LCD.SetDrawColor(WHITE);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 13, XMAX/2 + 10, YMAX/14 * 13);
    LCD.DrawLine(XMAX/2 + 10, YMAX/14 * 13, XMAX/2 + 5, YMAX/14 * 13 + 7);
    LCD.DrawLine(XMAX/2 + 10, YMAX/14 * 13, XMAX/2 + 5, YMAX/14 * 13 - 7);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 11, XMAX/2 + 10, YMAX/14 * 11);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 11, XMAX/2 - 5, YMAX/14 * 11 + 7);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 11, XMAX/2 - 5, YMAX/14 * 11 - 7);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 9, XMAX/2 + 10, YMAX/14 * 9);
    LCD.DrawLine(XMAX/2 + 10, YMAX/14 * 9, XMAX/2 + 5, YMAX/14 * 9 + 7);
    LCD.DrawLine(XMAX/2 + 10, YMAX/14 * 9, XMAX/2 + 5, YMAX/14 * 9 - 7);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 7, XMAX/2 + 10, YMAX/14 * 7);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 7, XMAX/2 - 5, YMAX/14 * 7 + 7);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 7, XMAX/2 - 5, YMAX/14 * 7 - 7);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 5, XMAX/2 + 10, YMAX/14 * 5);
    LCD.DrawLine(XMAX/2 + 10, YMAX/14 * 5, XMAX/2 + 5, YMAX/14 * 5 + 7);
    LCD.DrawLine(XMAX/2 + 10, YMAX/14 * 5, XMAX/2 + 5, YMAX/14 * 5 - 7);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 3, XMAX/2 + 10, YMAX/14 * 3);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 3, XMAX/2 - 5, YMAX/14 * 3 + 7);
    LCD.DrawLine(XMAX/2 - 10, YMAX/14 * 3, XMAX/2 - 5, YMAX/14 * 3 - 7);
    LCD.DrawLine(XMAX/14 * 13 + 5, YMAX/14 * 13, XMAX/14 * 13 + 5, YMAX/14 * 13 - 25);
    LCD.DrawLine(XMAX/14 * 13 + 5, YMAX/14 * 13 - 25, XMAX/14 * 13, YMAX/14 * 13 - 18);
    LCD.DrawLine(XMAX/14 * 13 + 5, YMAX/14 * 13 - 25, XMAX/14 * 13 + 10, YMAX/14 * 13 - 18);
    LCD.DrawLine(XMAX/14 + 5, YMAX/14 * 11, XMAX/14 + 5, YMAX/14 * 11 - 25);
    LCD.DrawLine(XMAX/14 + 5, YMAX/14 * 11 - 25, XMAX/14, YMAX/14 * 11 - 18);
    LCD.DrawLine(XMAX/14 + 5, YMAX/14 * 11 - 25, XMAX/14 + 10, YMAX/14 * 11 - 18);
    LCD.DrawLine(XMAX/14 * 13 + 5, YMAX/14 * 9, XMAX/14 * 13 + 5, YMAX/14 * 9 - 25);
    LCD.DrawLine(XMAX/14 * 13 + 5, YMAX/14 * 9 - 25, XMAX/14 * 13, YMAX/14 * 9 - 18);
    LCD.DrawLine(XMAX/14 * 13 + 5, YMAX/14 * 9 - 25, XMAX/14 * 13 + 10, YMAX/14 * 9 - 18);
    LCD.DrawLine(XMAX/14 + 5, YMAX/14 * 7, XMAX/14 + 5, YMAX/14 * 7 - 25);
    LCD.DrawLine(XMAX/14 + 5, YMAX/14 * 7 - 25, XMAX/14, YMAX/14 * 7 - 18);
    LCD.DrawLine(XMAX/14 + 5, YMAX/14 * 7 - 25, XMAX/14 + 10, YMAX/14 * 7 - 18);
    LCD.DrawLine(XMAX/14 * 13 + 5, YMAX/14 * 5, XMAX/14 * 13 + 5, YMAX/14 * 5 - 25);
    LCD.DrawLine(XMAX/14 * 13 + 5, YMAX/14 * 5 - 25, XMAX/14 * 13, YMAX/14 * 5 - 18);
    LCD.DrawLine(XMAX/14 * 13 + 5, YMAX/14 * 5 - 25, XMAX/14 * 13 + 10, YMAX/14 * 5 - 18);
 
    /*Roll button is drawn*/
    LCD.SetDrawColor(RED);
    LCD.FillRectangle(0, 0, XMAX/6, YMAX/7);
    LCD.WriteAt("Roll", .5, 1);
    LCD.SetDrawColor(BLUE);
 
    /*Shows what the previous player was and what they rolled*/
    LCD.WriteAt("Player: ", XMAX/6*4, 1);
    LCD.WriteAt(current + 1, XMAX/6*5.5, 1);
    LCD.WriteAt("# Rolled: ", XMAX/6*1.5, 1);
    LCD.WriteAt(roll, XMAX/6*3.5, 1);
  
    /*Single player game pieces are drawn*/
    if (n == 1){
        LCD.FillCircle(p1.x, p1.y, 5);
        LCD.SetDrawColor(GRAY);
        LCD.FillCircle(ai.x, ai.y, 5);
    }
 
    /*Two player game pieces are drawn*/
    if (n == 2){
        LCD.FillCircle(p1.x, p1.y, 5);
        LCD.SetDrawColor(GRAY);
        LCD.FillCircle(p2.x, p2.y, 5);
    }
 
    /*Three player game pieces are drawn*/
    if (n == 3){
        LCD.FillCircle(p1.x, p1.y, 5);
        LCD.SetDrawColor(GRAY);
        LCD.FillCircle(p2.x, p2.y, 5);
        LCD.SetDrawColor(WHITE);
        LCD.FillCircle(p3.x, p3.y, 5);
    }
 
    /*Four player game pieces are drawn*/
    if (n == 4){
        LCD.SetDrawColor(BLUE);
        LCD.FillCircle(p1.x, p1.y, 5);
        LCD.SetDrawColor(GRAY);
        LCD.FillCircle(p2.x, p2.y, 5);
        LCD.SetDrawColor(WHITE);
        LCD.FillCircle(p3.x, p3.y, 5);
        LCD.SetDrawColor(GREEN);
        LCD.FillCircle(p4.x, p4.y, 5);
    }
}
 
/*Player constructor function
Description: The player constructor has one input argument that is n which holds the name of
the player which will be strcopied into the name.
Purpose: The purpose of the constructor function is to make the player name copied into the 
specific objects name. 
Author: Ryan Pochek*/
Player::Player(char n[])
{
   strcpy(name, n);
}
 
/* RollDice member function
Description: The RollDice() function is one of the largest functions in our game. It is another
void function that does not return a specific value to a variable. The input arguments needed for
this function are all passed by reference so modications made within this function will keep saved
to those variables outside of the function. These input arguments include n which dictates if the 
game is won or not, current which dictates who's turn it is and updates after each turn, and all 5
player objects including p1, p2, p3, p4, and ai.
Purpose: The purpose of the RollDice() function is to identify which player's turn it is, then
randomly generate a number from the 4 options of the die. Once the roll number is produced, if there
is a special feature for that roll including a 2 or a 4, the function waits for the users choice on 
where they want to go. After the user selects where they want to go, the function tests for if the 
user landed on a slide, ladder, or on an opponent and at the end calls the spot function to move the
players to their respective spots and call the set_game_board function. 
Author: Michael Valcarcel*/

void RollDice(int &n, int &current, Player &p1, Player &p2, Player &p3, Player &p4, Player &ai)
{
   /*Variables declared*/
   int temp;
   int roll;
   int r;
   int x, y, x1, y1;
   double runtime = 500;
   int flag;
   int timer = 0;
 
   /*Multiplayer setting*/
   if (n == 2 || n == 3 || n == 4){
 
   /*Player 1*/   
   if (current == 0)
   {
 
       /*Die is rolled*/
       roll = (RandInt() % 4) + 1;
       r = roll;
 
       /*Turn counter incremented*/
       p1.turns = p1.turns + 1;
 
       /*Special move for rolling a 4*/
       if (r == 4)
       {
 
            /*Set game board function is called to be ready to update board*/
            set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
          
            /*Touch for what user wants to do*/
            while (!LCD.Touch(&x, &y))
            {
            }
      
            /*If statement for if the current player clicks to move forward 4 spaces*/
            if (x > 0 && x < XMAX/2 && y > 0 && y < YMAX/7){
                temp = p1.block;
                p1.block = p1.block + 4;
                if (p1.block > 36){
                p1.block = temp;
            }  
            }
 
            /*If statement for if the current player clicks to move backward 4 spaces*/
            else if(x > XMAX/2 && x < XMAX && y > 0 && y < YMAX/7)
            {
                p1.block = p1.block - 4;
            }
        }
 
       /*Special move for rolling a 2*/
       else if (r == 2)
       {
           /*Set game board function is called to be ready update the board*/
           set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
 
           /*Touch for what the user wants to do*/
           while (!LCD.Touch(&x, &y))
           {
           }
 
            /*If statement for if the current player clicks to move forward 2 spaces*/  
            if (x > 0 && x < XMAX/2 && y > YMAX/14 && y < YMAX/7){
                temp = p1.block;
                p1.block = p1.block + 2;
                if (p1.block > 36){
                p1.block = temp;
                }
            }
 
            /*If statement for if the current player wants to move to the closest object*/
            else if(x > XMAX/2 && x < XMAX && y > YMAX/14 && y < YMAX/7){
                if (p1.block >= 1 && p1.block <= 4){
                    p1.block = 2;
                }
                if(p1.block >= 5 && p1.block <= 20){
                    p1.block = 8;
                }
                if(p1.block >= 21 && p1.block <=28){
                    p1.block = 25;
                }
                if(p1.block >= 29 && p1.block <= 35){
                    p1.block = 33;
                }
            }
       
        }
       
       /*Normal move*/
       else{
       temp = p1.block;
       p1.block = p1.block + roll;
       if (p1.block > 36){
           p1.block = temp;
       }
    }
 
    /*Chutes and ladders are made.   If a user lands on a block that will send them up a ladder or down a chute, it will move them here*/
    /*Sent back to start if another player lands on them is sent here*/
    if (p1.block == 2){
        p1.block = 21;
        p1.ladder = p1.ladder + 1;
    }
    if (p1.block == 8){
        p1.block = 18;
        p1.ladder = p1.ladder + 1;
    }
    if (p1.block == 25){
        p1.block = 14;
        p1.slide = p1.slide + 1;
    }
    if (p1.block == 33){
        p1.block = 20;
        p1.slide = p1.slide + 1;
    }
    if (p1.block == p2.block){
        p2.block = 1;
        p1.eaten = p1.eaten + 1;
        p2.Spot(p2.block);
    }
    if (p1.block == p3.block){
        p3.block = 1;
        p1.eaten = p1.eaten + 1;
        p3.Spot(p3.block);
    }
    if (p1.block == p4.block){
        p4.block = 1;
        p1.eaten = p1.eaten + 1;
        p4.Spot(p4.block);
    }
 
    /*Touch is initialized*/
    while (LCD.Touch(&x1,&y1))
    {
    }
    /*Shows current player what they rolled*/
    LCD.WriteAt("# Rolled: ", XMAX/6*1.5, 1);
    LCD.WriteAt(roll, XMAX/6*3.5, 1);
 
    /*Updated spot for player 1*/
    p1.Spot(p1.block);
    r = 0;
 
    /*Board is updated*/
    set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
        
}
 
   /*Player 2*/
   if (current == 1){
 
       /*Die is rolled*/
       roll = (RandInt() % 4) + 1;
       r = roll;
 
       /*Turn counter incremented*/
       p2.turns = p2.turns + 1;
 
       /*Special move for rolling a 4*/
       if (r == 4){
 
           /*Set game board function is called to be ready to update game board*/
           set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
   /*Player clicks on what they want to do*/
   while (!LCD.Touch(&x, &y))
   {
   }
       /*If statement for if the current player clicks to move forward 4 spaces*/
       if (x > 0 && x < XMAX/2 && y > 0 && y < YMAX/7){
           temp = p2.block;
           p2.block = p2.block + 4;
           if (p2.block > 36){
               p2.block = temp;
           }
       }
 
       /*Else if statement for if the current player clicks to move back 4 spaces*/
       else if(x > XMAX/2 && x < XMAX && y > 0 && y < YMAX/7){
           p2.block = p2.block - 4;
       }
       }
 
       /*Special move for rolling a 2*/
       else if (r == 2){
      
           /*Set game board function is called to be ready to update the game board*/
           set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
 
 
   /*Player clicks on what they want to do*/
   while (!LCD.Touch(&x, &y))
   {
   }
 
       /*If statement for if the current player clicks to move forward 2 spaces*/
       if (x > 0 && x < XMAX/2 && y > YMAX/14 && y < YMAX/7){
           temp = p2.block;
           p2.block = p2.block + 2;
           if (p2.block > 36){
               p2.block = temp;
           }
       }
 
       /*If statement for if the current player clicks to move to the closest object*/
       else if(x > XMAX/2 && x < XMAX && y > YMAX/14 && y < YMAX/7){
            if (p2.block >= 1 && p2.block <= 4){
                p2.block = 2;
            }
            if(p2.block >= 5 && p2.block <= 20){
                p2.block = 8;
            }
            if(p2.block >= 21 && p2.block <=28){
                p2.block = 25;
            }
            if(p2.block >= 29 && p2.block <= 35){
                p2.block = 33;
            }
       }
       }
       /*Normal move*/
       else{ 
       temp = p2.block;    
       p2.block = p2.block + roll;
       if (p2.block > 36){
           p2.block = temp;
       }
       }
 
       /*Chutes and ladders are made.   If a user lands on a block that will send them up a ladder or down a chute, it will move them here*/
       /*Sent back to start if another player lands on them is sent here*/
       if (p2.block == 2){
           p2.block = 21;
           p2.ladder = p2.ladder + 1;
       }
       if (p2.block == 8){
           p2.block = 18;
           p2.ladder = p2.ladder + 1;
       }
       if (p2.block == 25){
           p2.block = 14;
           p2.slide = p2.slide + 1;
       }
       if (p2.block == 33){
           p2.block = 20;
           p2.slide = p2.slide + 1;
       }
       if (p2.block == p1.block){
           p1.block = 1;
           p2.eaten = p2.eaten + 1;
           p1.Spot(p1.block);
       }
       if (p2.block == p3.block){
           p3.block = 1;
           p2.eaten = p2.eaten + 1;
           p3.Spot(p3.block);
       }
       if (p2.block == p4.block){
           p4.block = 1;
           p2.eaten = p2.eaten + 1;
           p4.Spot(p4.block);
       }
 
       /*Touch is initialized*/
       while (LCD.Touch(&x1,&y1))
       {
       }
 
       /*Shows what current player rolled*/
       LCD.WriteAt("# Rolled: ", XMAX/6*1.5, 1);
       LCD.WriteAt(roll, XMAX/6*3.5, 1);
 
       /*Updates spot of player 2*/
       p2.Spot(p2.block);
       r = 0;
 
       /*Game board is updated*/
       set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
   }
 
   /*Player 3*/
   if (current == 2){
       /*Die is rolled*/
       roll = (RandInt() % 4) + 1;
       r = roll;
 
       /*Turn counter incremented*/
       p3.turns = p3.turns + 1;
 
       /*Special move for rolling a 4*/
       if (r == 4){
 
           /*Set game board function is called to be ready to update game board*/
           set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
   /*Player clicks on what they want to do*/
   while (!LCD.Touch(&x, &y))
   {
   }
       /*If statement for if the current player clicks to move forward 4 spaces*/
       if (x > 0 && x < XMAX/2 && y > 0 && y < YMAX/7){
           temp = p3.block;
           p3.block = p3.block + 4;
           if (p3.block > 36){
               p3.block = temp;
           }
       }
 
       /*Else if statement for if the current player clicks to move back 4 spaces*/
       else if(x > XMAX/2 && x < XMAX && y > 0 && y < YMAX/7){
           p3.block = p3.block - 4;
       }
       }
 
       /*Special move for rolling a 2*/
       else if (r == 2){
      
           /*Set game board function is called to be ready to update the game board*/
           set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
 
 
   /*Player clicks on what they want to do*/
   while (!LCD.Touch(&x, &y))
   {
   }
 
       /*If statement for if the current player clicks to move forward 2 spaces*/
       if (x > 0 && x < XMAX/2 && y > YMAX/14 && y < YMAX/7){
           temp = p3.block;
           p3.block = p3.block + 2;
           if (p3.block > 36){
               p3.block = temp;
           }
       }
 
       /*If statement for if the current player clicks to move to the closest object*/
       else if(x > XMAX/2 && x < XMAX && y > YMAX/14 && y < YMAX/7){
            if (p3.block >= 1 && p3.block <= 4){
                p3.block = 2;
            }
            if(p3.block >= 5 && p3.block <= 20){
                p3.block = 8;
            }
            if(p3.block >= 21 && p3.block <=28){
                p3.block = 25;
            }
            if(p3.block >= 29 && p3.block <= 35){
                p3.block = 33;
            }
       }
       }
 
       /*Normal move*/
       else{ 
       temp = p3.block;    
       p3.block = p3.block + roll;
       if (p3.block > 36){
           p3.block = temp;
       }
       }
 
       /*Chutes and ladders are made.   If a user lands on a block that will send them up a ladder or down a chute, it will move them here*/
       /*Sent back to start if another player lands on them is sent here*/
       if (p3.block == 2){
           p3.block = 21;
           p3.ladder = p3.ladder + 1;
       }
       if (p3.block == 8){
           p3.block = 18;
           p3.ladder = p3.ladder + 1;
       }
       if (p3.block == 25){
           p3.block = 14;
           p3.slide = p3.slide + 1;
       }
       if (p3.block == 33){
           p3.block = 20;
           p3.slide = p3.slide + 1;
       }
       if (p3.block == p1.block){
           p1.block = 1;
           p3.eaten = p3.eaten + 1;
           p1.Spot(p1.block);
       }
       if (p3.block == p2.block){
           p2.block = 1;
           p3.eaten = p3.eaten + 1;
           p2.Spot(p2.block);
       }
       if (p3.block == p4.block){
           p4.block = 1;
           p3.eaten = p3.eaten + 1;
           p4.Spot(p4.block);
       }
 
 
       /*Touch is initialized*/
       while (LCD.Touch(&x1,&y1))
       {
       }
 
       /*Shows what current player rolled*/
       LCD.WriteAt("# Rolled: ", XMAX/6*1.5, 1);
       LCD.WriteAt(roll, XMAX/6*3.5, 1);
 
       /*Updates spot of player 3*/
       p3.Spot(p3.block);
       r = 0;
 
       /*Game board is updated*/
       set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
   }
 
   /*Player 4*/
   if (current == 3){
       /*Die is rolled*/
       roll = (RandInt() % 4) + 1;
       r = roll;
 
       /*Turn counter incremented*/
       p4.turns = p4.turns + 1;
 
       /*Special move for rolling a 4*/
       if (r == 4){
 
           /*Set game board function is called to be ready to update game board*/
           set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
   /*Player clicks on what they want to do*/
   while (!LCD.Touch(&x, &y))
   {
   }
       /*If statement for if the current player clicks to move forward 4 spaces*/
       if (x > 0 && x < XMAX/2 && y > 0 && y < YMAX/7){
           temp = p4.block;
           p4.block = p4.block + 4;
           if (p4.block > 36){
               p4.block = temp;
           }
       }
 
       /*Else if statement for if the current player clicks to move back 4 spaces*/
       else if(x > XMAX/2 && x < XMAX && y > 0 && y < YMAX/7){
           p4.block = p4.block - 4;
       }
       }
 
       /*Special move for rolling a 2*/
       else if (r == 2){
      
           /*Set game board function is called to be ready to update the game board*/
           set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
 
 
   /*Player clicks on what they want to do*/
   while (!LCD.Touch(&x, &y))
   {
   }
 
       /*If statement for if the current player clicks to move forward 2 spaces*/
       if (x > 0 && x < XMAX/2 && y > YMAX/14 && y < YMAX/7){
           temp = p4.block;
           p4.block = p4.block + 2;
           if (p4.block > 36){
               p4.block = temp;
           }
       }
 
       /*If statement for if the current player clicks to move to the closest object*/
       else if(x > XMAX/2 && x < XMAX && y > YMAX/14 && y < YMAX/7){
            if (p4.block >= 1 && p4.block <= 4){
                p4.block = 2;
            }
            if(p4.block >= 5 && p4.block <= 20){
                p4.block = 8;
            }
            if(p4.block >= 21 && p4.block <=28){
                p4.block = 25;
            }
            if(p4.block >= 29 && p4.block <= 35){
                p4.block = 33;
            }
       }
       }
       /*Normal move*/
       else{ 
       temp = p4.block;    
       p4.block = p4.block + roll;
       if (p4.block > 36){
           p4.block = temp;
       }
       }
 
       /*Chutes and ladders are made.   If a user lands on a block that will send them up a ladder or down a chute, it will move them here*/
       /*Sent back to start if another player lands on them is sent here*/
       if (p4.block == 2){
           p4.ladder = p4.ladder + 1;
           p4.block = 21;
       }
       if (p4.block == 8){
           p4.ladder = p4.ladder + 1;
           p4.block = 18;
       }
       if (p4.block == 25){
           p4.slide = p4.slide + 1;
           p4.block = 14;
       }
       if (p4.block == 33){
           p4.slide = p4.slide + 1;
           p4.block = 20;
       }
       if (p4.block == p1.block){
           p1.block = 1;
           p4.eaten = p4.eaten + 1;
           p1.Spot(p1.block);
       }
       if (p4.block == p2.block){
           p2.block = 1;
           p4.eaten = p4.eaten + 1;
           p2.Spot(p2.block);
       }
       if (p4.block == p3.block){
           p3.block = 1;
           p4.eaten = p4.eaten + 1;
           p3.Spot(p3.block);
       }
       /*Touch is initialized*/
       while (LCD.Touch(&x1,&y1))
       {
       }
 
       /*Shows what current player rolled*/
       LCD.WriteAt("# Rolled: ", XMAX/6*1.5, 1);
       LCD.WriteAt(roll, XMAX/6*3.5, 1);
 
       /*Updates spot of player 4*/
       p4.Spot(p4.block);
       r = 0;
 
       /*Game board is updated*/
       set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
   }
   }
 
   /*Single Player*/
   if (n == 1){

       if (current == 0){
       /*Die is rolled*/
       roll = (RandInt() % 4) + 1;
       r = roll;
       
       /*Turn counter incremented*/
       p1.turns = p1.turns + 1;
 
       /*Special move for rolling a 4*/
       if (r == 4){
 
           /*Set game board function is called to be ready to update board*/
           set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
          
           /*Touch for what user wants to do*/
           while (!LCD.Touch(&x, &y))
           {
           }
      
            /*If statement for if the current player clicks to move forward 4 spaces*/
            if (x > 0 && x < XMAX/2 && y > 0 && y < YMAX/7){
                temp = p1.block;
                p1.block = p1.block + 4;
                if (p1.block > 36){
                    p1.block = temp;
                }
          
            }
 
            /*If statement for if the current player clicks to move backward 4 spaces*/
            else if(x > XMAX/2 && x < XMAX && y > 0 && y < YMAX/7){
                p1.block = p1.block - 4;
            }
        }
 
        /*Special move for rolling a 2*/
        else if (r == 2){
 
           /*Set game board function is called to be ready update the board*/
           set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
 
           /*Touch for what the user wants to do*/
           while (!LCD.Touch(&x, &y))
           {
           }
 
            /*If statement for if the current player clicks to move forward 2 spaces*/  
            if (x > 0 && x < XMAX/2 && y > YMAX/14 && y < YMAX/7){
                temp = p1.block;
                p1.block = p1.block + 2;
            if (p1.block > 36){
                p1.block = temp;
            }
            }
 
            /*If statement for if the current player wants to move to the closest object*/
            else if(x > XMAX/2 && x < XMAX && y > YMAX/14 && y < YMAX/7){
                
                if (p1.block >= 1 && p1.block <= 4){
                    p1.block = 2;
                }

                if(p1.block >= 5 && p1.block <= 20){
                    p1.block = 8;
                }

                if(p1.block >= 21 && p1.block <=28){
                    p1.block = 25;
                }

                if(p1.block >= 29 && p1.block <= 35){
                    p1.block = 33;
                }
            }
        }
 
       /*Normal move*/
       else{
       temp = p1.block;
       p1.block = p1.block + roll;
       
       if (p1.block > 36){
           p1.block = temp;
       }

       }
       if (p1.block < 24){
           flag = 0;
       }

       if (p1.block >= 24){
            flag = 1;
       }

       if (p1.block >= 24 && flag == 1){
           runtime = TimeNow() + 30;
           flag = 0;
           timer = 1;
       }

       if (p1.block != 36 && TimeNow() > runtime){
            p1.block = 1;
       }

       /*Chutes and ladders are made.   If a user lands on a block that will send them up a ladder or down a chute, it will move them here*/
       /*Sent back to start if another player lands on them is sent here*/
       if (p1.block == 2){
           p1.block = 21;
           p1.ladder = p1.ladder + 1;
       }

       if (p1.block == 8){
           p1.block = 18;
           p1.ladder = p1.ladder + 1;
       }

       if (p1.block == 25){
           p1.block = 14;
           p1.slide = p1.slide + 1;
       }

       if (p1.block == 33){
           p1.block = 20;
           p1.slide = p1.slide + 1;
       }

       if (p1.block == ai.block){
           ai.block = 1;
           p1.eaten = p1.eaten + 1;
           ai.Spot(ai.block);
       }
 
       /*Touch is initialized*/
       while (LCD.Touch(&x1,&y1))
        {
        }
       /*Shows current player what they rolled*/
       LCD.WriteAt("# Rolled: ", XMAX/6*1.5, 1);
       LCD.WriteAt(roll, XMAX/6*3.5, 1);
 
       /*Spot changes for Player 1*/
       p1.Spot(p1.block);
       r = 0;
 
       /*Board is updated*/
       set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
  
       /*Die is rolled for AI*/
       roll = (RandInt() % 4) + 1;
       r = roll;
      
       /*AI is moved*/
       temp = ai.block;
       ai.block = ai.block + roll;
       if (ai.block > 36){
           ai.block = temp;
       }
       }

       /*Chutes and ladders are made.   If a user lands on a block that will send them up a ladder or down a chute, it will move them here*/
       if (ai.block == 2){
           ai.block = 21;
       }
       if (ai.block == 8){
           ai.block = 18;
       }
       if (ai.block == 25){
           ai.block = 14;
       }
       if (ai.block == 33){
           ai.block = 20;
       }
       if (ai.block == p1.block){
           p1.block = 1;
           ai.eaten = ai.eaten + 1;
           p1.Spot(p1.block);
       }
       while (LCD.Touch(&x1,&y1))
        {
        }
       LCD.WriteAt("# Rolled: ", XMAX/6*1.5, 1);
       LCD.WriteAt(roll, XMAX/6*3.5, 1);
 
       /*AI spot is updated*/
       ai.Spot(ai.block);
       r = 0;
        
       /*Game board is updated*/
       set_game_board(n, p1, p2, p3, p4, ai, current, roll, r, timer);
    }
}
   /* Check winner member function
   Description: The check_winner function is a void function meaning it does not pass
   any values to a certain variable. The input arguments needed for check_winner are n
   which is a variable used in the int main to check in a while loop to continue playing 
   the game. If n == 1, the while loop continues to play the game. Since the n variable is
   called by reference using the &, we can manipulated it in this function by if there is a 
   winner we can set n = 2 to stop playing the game. 
   Purpose: The purpose of the check_winner function is to constantly check if any player on 
   the board game has reached the finish spot. If so, it calls another function called draw_winner
   which ends the game and draws a new screen for celebrating the winner. 
   Author: Ryan Pochek*/
   void check_winner(int &n, Player p1, Player p2, Player p3, Player p4, Player ai){
 
       /*If player 1 is on final block*/
       if (p1.block == 36){
           draw_winner(p1);
           n = 2;
       }
 
       /*If player 2 is on final block*/
       if (p2.block == 36){
           draw_winner(p2);
           n = 2;
       }
 
       /*If player 3 is on final block*/
       if (p3.block == 36){
           draw_winner(p3);
           n = 2;
       }
 
       /*If player 4 is on final block*/
       if (p4.block == 36){
           draw_winner(p4);
           n = 2;
       }
 
       /*If AI is on final block*/
       if (ai.block == 36){
           draw_winner(ai);
           n = 2;
       }
   }

/*Displays the winner
Description: The draw_winner function is a void function that is called when there is 
a specific winner identified. The input arguments required for this function are the object
winner whose name data member is going to be announced on the screen. 
Purpose: The purpose of this function is to clear the board game and have a screen for announcing 
the winner of the game.
Author: Jack Dennis*/

void draw_winner(Player winner){
    LCD.Clear();
    LCD.WriteAt("The Winner is ", XMAX/5, YMAX/8);
    LCD.WriteAt(winner.name, XMAX/5*2.9, YMAX/8);
}
   
/*Menu is drawn again
Description: The DrawMenu() function is a void function that resets the screen and 
redraws the menu of options including play game, see stats, see instructions, and see credits. 
Purpose: The purpose of this function is to be called up at the beginning of the game to prompt 
the user to make a selection and guide them from there. Also, it is called again after the game 
is finished or the user selects the back button. 
Author: Charlie Farmer
*/
void DrawMenu()
{
    /*Clears menu*/
    LCD.Clear();

    /*Line to split up Play game and Instructions*/
    LCD.SetDrawColor(LCD.Gray);
    LCD.DrawHorizontalLine(239/4, 0, 319);

    /*Line to split up Instructions and Statistics*/
    LCD.SetDrawColor(LCD.Red);
    LCD.DrawHorizontalLine(239/2, 0, 319);

    /*Line to split up Statistics and Credits*/
    LCD.SetDrawColor(LCD.Gray);
    LCD.DrawHorizontalLine(239 * .75, 0, 319);

    /*Button names are printed to their respective boxes*/
    LCD.WriteAt(BUTTON1TEXT, 319* .05, 239 * .125);
    LCD.WriteAt(BUTTON2TEXT, 319* .05, 239 * .375);
    LCD.WriteAt(BUTTON3TEXT, 319* .05, 239 * .625);
    LCD.WriteAt(BUTTON4TEXT, 319* .05, 239 * .875);
}

/*DrawPlayer member function
Description: The DrawPlayer() function is another void function that does not 
pass a value into a variable. The function has no input arguments needed to work.
Purpose: The purpose of this function is to provide a menu to the screen where the
users can select the game mode they desire including single player, two player, three
player, or four player. 
Author: Jack Dennis*/
void DrawPlayer()
{
    /*Clears menu*/
    LCD.Clear();

    /*Line to split up Single Player and Two Player*/
    LCD.SetDrawColor(LCD.Gray);
    LCD.DrawHorizontalLine(239/4, 0, 319);

    /*Line to split up Two Player and Three Player*/
    LCD.SetDrawColor(LCD.Red);
    LCD.DrawHorizontalLine(239/2, 0, 319);

    /*Line to split up Three Player and Four Player*/
    LCD.SetDrawColor(LCD.Gray);
    LCD.DrawHorizontalLine(239 * .75, 0, 319);

    /*Button names are printed to their respective boxes*/
    LCD.WriteAt(BUTTON1, 319* .05, 239 * .125);
    LCD.WriteAt(BUTTON2, 319* .05, 239 * .375);
    LCD.WriteAt(BUTTON3, 319* .05, 239 * .625);
    LCD.WriteAt(BUTTON4, 319* .05, 239 * .875);
}

/* Instructions member function
Description: The ShowInstructions function is a void function meaning it does not return any 
values back a certain variable. Along with that, the ShowInstructions() function does not require any
input arguments to operate or use during its function. The ShowInstructions() function is to occurr if the user
on the main menu selects the row pertaining to Show Instructions thus this function will be called.
Purpose: The purpose of ShowInstructions is to allow for an easy call from the menu code to output
a clean set of instructions for the user to use before playing the game. It will provide enough rules
for players to have the fundamentals to play the game. 
Author: Jack Dennis*/

void ShowInstructions()
{
    LCD.Clear();

    //Game instructions are printed
    LCD.Write("Game Instructions: ");
    LCD.Write("Select game mode: ");
    LCD.WriteLine("\n");
    LCD.Write("single-player or multiplayer");
    LCD.WriteLine("\n");
    LCD.Write("The objective of the game is to get");
    LCD.WriteLine("\n");
    LCD.Write("to the top of the board before your opponent.");
    LCD.WriteLine("\n");
    LCD.Write("You can use the ladders to your advantage");
    LCD.WriteLine("\n");
    LCD.Write("to advancing your character closer to victory.");
    LCD.WriteLine("\n");
    LCD.Write("However, watch out for the chutes -- ");
    LCD.WriteLine("\n");
    LCD.Write("they will send you backward.");
}

/* Credits member function
Description: The ShowCredits() function is a void function so it does not pass a certain 
value back to certain variables. There are no input arguments needed for this function but it
utilizes the LCD write tools to clearly mention names of authors and references used.
Purpose: The purpose of the ShowCredits() function is to provide the credits for the game including
name of creators and references after the user selects the row listed Show Credits on the main menu.
Author: Charlie Farmer
*/

void ShowCredits()
{
    LCD.Clear();

    /*Tells the user who created the game*/
    LCD.Write("Game created by Dr Rick's Rangers aka");
    LCD.WriteLine("\n");
    LCD.Write("Ryan Pochek");
    LCD.WriteLine("\n");
    LCD.Write("Michael Valcarcel");
    LCD.WriteLine("\n");
    LCD.Write("Jack Dennis");
    LCD.WriteLine("\n");
    LCD.Write("Charlie Farmer");
    LCD.WriteLine("\n");
    LCD.Write("Based off Chutes and Ladders");
}
 
/* Show stats member function
Description: The function ShowStats() is a void function meaning it doesn't pass a value back
into another variable. The function does require a few input arguments including each player object
p1, p2, p3, p4, and ai. This function will output the key statistics of each player playing the game.
To begin the function there is menu that asks the user for which player stats they'd like to view, once
selected, the function will output the player and its key statistics to the screen, along with a back 
button to the main menu.
Purpose: The purpose of this function is to quickly be called after the user selects Show Statistics in
the main menu. It brings in the player objects, and requests the user to select what player's stats they
want to view. It allows for an easy call for any player's stats whenever the user wants. 
Author: Michael Valcarcel*/

void ShowStats(Player p1, Player p2, Player p3, Player p4, Player ai){
    int x, y, x1, y1;
 
    /*Initializes touch*/
   while (LCD.Touch(&x1,&y1))
    {
    }

   /*Clears screen*/
   LCD.Clear();

    /*Line to split up Play game and Instructions*/
    LCD.SetDrawColor(LCD.Gray);
    LCD.DrawHorizontalLine(239/4, 0, 319);

    /*Line to split up Instructions and Statistics*/
    LCD.SetDrawColor(LCD.Red);
    LCD.DrawHorizontalLine(239/2, 0, 319);

    /*Line to split up Statistics and Credits*/
    LCD.SetDrawColor(LCD.Gray);
    LCD.DrawHorizontalLine(239 * .75, 0, 319);

    /*Button names are printed to their respective boxes*/
    LCD.WriteAt("Player 1 Stats", 319* .05, 239 * .125);
    LCD.WriteAt("Player 2 Stats", 319* .05, 239 * .375);
    LCD.WriteAt("Player 3 Stats", 319* .05, 239 * .625);
    LCD.WriteAt("Player 4 Stats", 319* .05, 239 * .875);

    /*Touch for stats*/
    while (!LCD.Touch(&x,&y))
    {
    }

    /*Clears screen*/
    LCD.Clear();

    /*Player 1 Stats*/
    if (y < 239/4 && y > 0){
        LCD.Write("Player 1 Stats");
        LCD.WriteLine("\n");
        LCD.Write("Total Blocks Moved: ");
        LCD.Write(p1.block);
        LCD.WriteLine("\n");
        LCD.Write("Number of Turns: ");
        LCD.Write(p1.turns);
        LCD.WriteLine("\n");
        LCD.Write("Average Blocks Moved: ");
        p1.avg_blocks = p1.block / p1.turns;
        LCD.Write(p1.avg_blocks);
        LCD.WriteLine("\n");
        LCD.Write("Number of Ladders Used: ");
        LCD.Write(p1.ladder);
        LCD.WriteLine("\n");
        LCD.Write("Number of Slides Used: ");
        LCD.Write(p1.slide);
        LCD.WriteLine("\n");
        LCD.Write("Players Eaten: ");
        LCD.Write(p1.eaten);
    }
 
    /*Player 2 Stats*/
    if (y < 239/4*2 && y > 239/4){
        LCD.Write("Player 2 Stats");
        LCD.WriteLine("\n");
        LCD.Write("Total Blocks Moved: ");
        LCD.Write(p2.block);
        LCD.WriteLine("\n");
        LCD.Write("Number of Turns: ");
        LCD.Write(p2.turns);
        LCD.WriteLine("\n");
        LCD.Write("Average Blocks Moved: ");
        p2.avg_blocks = p2.block / p2.turns;
        LCD.Write(p2.avg_blocks);
        LCD.WriteLine("\n");
        LCD.Write("Number of Ladders Used: ");
        LCD.Write(p2.ladder);
        LCD.WriteLine("\n");
        LCD.Write("Number of Slides Used: ");
        LCD.Write(p2.slide);
        LCD.WriteLine("\n");
        LCD.Write("Players Eaten: ");
        LCD.Write(p2.eaten);
    }
 
    /*Player 3 Stats*/
    if (y < 239/4*3 && y > 239/4*2){
        LCD.Write("Player 3 Stats");
        LCD.WriteLine("\n");
        LCD.Write("Total Blocks Moved: ");
        LCD.Write(p3.block);
        LCD.WriteLine("\n");
        LCD.Write("Number of Turns: ");
        LCD.Write(p3.turns);
        LCD.WriteLine("\n");
        LCD.Write("Average Blocks Moved: ");
        p3.avg_blocks = p3.block / p3.turns;
        LCD.Write(p3.avg_blocks);
        LCD.WriteLine("\n");
        LCD.Write("Number of Ladders Used: ");
        LCD.Write(p3.ladder);
        LCD.WriteLine("\n");
        LCD.Write("Number of Slides Used: ");
        LCD.Write(p3.slide);
        LCD.WriteLine("\n");
        LCD.Write("Players Eaten: ");
        LCD.Write(p3.eaten);
    }
 
    /*Player 4 Stats*/
    if (y > 239/4*3 && y < 239){
        LCD.Write("Player 4 Stats");
        LCD.WriteLine("\n");
        LCD.Write("Total Blocks Moved: ");
        LCD.Write(p4.block);
        LCD.WriteLine("\n");
        LCD.Write("Number of Turns: ");
        LCD.Write(p4.turns);
        LCD.WriteLine("\n");
        LCD.Write("Average Blocks Moved: ");
        p4.avg_blocks = p4.block / p4.turns;
        LCD.Write(p4.avg_blocks);
        LCD.WriteLine("\n");
        LCD.Write("Number of Ladders Used: ");
        LCD.Write(p4.ladder);
        LCD.WriteLine("\n");
        LCD.Write("Number of Slides Used: ");
        LCD.Write(p4.slide);
        LCD.WriteLine("\n");
        LCD.Write("Players Eaten: ");
        LCD.Write(p4.eaten);
    }
}

/* Spot class function
Description: The member function Player::spot is a void function that does
not pass a value to a variable. It has one input argument which is named block.
The block variable holds the square the user is currently at while playing the game.
This function allows the coordinates of the pawn on the screen to update before 
calling set_game_board again.
Purpose: The purpose of this member function is to allow for an easy update of the
x and y coordinates of the pawns on the game board. It knows where all 36 blocks are 
on the board and can easily updatae each player members x and y location accordingly.
Author: Charlie Farmer
*/

void Player::Spot(int block){
   if (block == 1){
       x = (XMAX/12);
       y = 13*YMAX/14;
   }
   if (block == 2){
       x = 3*(XMAX/12);
       y = 13*YMAX/14;
   }
   if (block == 3){
       x = 5*(XMAX/12);
       y = 13*YMAX/14;
   }
   if (block == 4){
       x = 7*(XMAX/12);
       y = 13*YMAX/14;
   }
   if (block == 5){
       x = 9*(XMAX/12);
       y = 13*YMAX/14;
   }
   if (block == 6){
       x = 11*(XMAX/12);
       y = 13*YMAX/14;
   }
   if (block == 7){
       x = 11*(XMAX/12);
       y = 11*YMAX/14;
   }
   if (block == 8){
       x = 9*(XMAX/12);
       y = 11*YMAX/14;
   }
   if (block == 9){
       x = 7*(XMAX/12);
       y = 11*YMAX/14;
   }
   if (block == 10){
       x = 5*(XMAX/12);
       y = 11*YMAX/14;
   }
   if (block == 11){
       x = 3*(XMAX/12);
       y = 11*YMAX/14;
   }
   if (block == 12){
       x = (XMAX/12);
       y = 11*YMAX/14;
   }
   if (block == 13){
       x = (XMAX/12);
       y = 9*YMAX/14; 
   }
   if (block == 14){
       x = 3*(XMAX/12);
       y = 9*YMAX/14; 
   }
   if (block == 15){
       x = 5*(XMAX/12);
       y = 9*YMAX/14; 
   }
   if (block == 16){
       x = 7*(XMAX/12);
       y = 9*YMAX/14;
   }
   if (block == 17){
       x = 9*(XMAX/12);
       y = 9*YMAX/14;
   }
   if (block == 18){
       x = 11*(XMAX/12);
       y = 9*YMAX/14;
   }
   if (block == 19){
       x = 11*(XMAX/12);
       y = 7*YMAX/14; 
   }
   if (block == 20){
       x = 9*(XMAX/12);
       y = 7*YMAX/14;
   }
   if (block == 21){
       x = 7*(XMAX/12);
       y = 7*YMAX/14;
   }
   if (block == 22){
       x = 5*(XMAX/12);
       y = 7*YMAX/14;
   }
   if (block == 23){
       x = 3*(XMAX/12);
       y = 7*YMAX/14;
   }
   if (block == 24){
       x = (XMAX/12);
       y = 7*YMAX/14;
   }
   if (block == 25){
        x = (XMAX/12);
       y = 5*YMAX/14;
   }
   if (block == 26){
       x = 3*(XMAX/12);
       y = 5*YMAX/14;
   }
   if (block == 27){
       x = 5*(XMAX/12);
       y = 5*YMAX/14;
   }
   if (block == 28){
       x = 7*(XMAX/12);
       y = 5*YMAX/14;
   }
   if (block == 29){
       x = 9*(XMAX/12);
       y = 5*YMAX/14;
   }
   if (block == 30){
       x = 11*(XMAX/12);
       y = 5*YMAX/14;
   }
   if (block == 31){
       x = 11*(XMAX/12);
       y = 3*YMAX/14;
   }
   if (block == 32){
       x = 9*(XMAX/12);
       y = 3*YMAX/14;
   }
   if (block == 33){
       x = 7*(XMAX/12);
       y = 3*YMAX/14;
   }
   if (block == 34){
       x = 5*(XMAX/12);
       y = 3*YMAX/14;
   }
   if (block == 35){
       x = 3*(XMAX/12);
       y = 3*YMAX/14;
   }
   if (block == 36){
       x = (XMAX/12);
       y = 3*YMAX/14;
   }
}


    




