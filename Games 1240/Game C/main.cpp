/*Includes necessary libraries for program to function.*/

//Assignment APP_B38_4
//Anoushka Dasi, Omer Sarig, Mike Grassi, Tori Ostrow
//12/6/20
//RJF 12:40 pm

#include "FEHLCD.h"
#include <time.h>
#include <math.h>
#include "FEHSD.h"
#include <FEHUtility.h>

/*Intializes important variables in the program. "scoreindex" is to be the user's 
score while playing and "lifeindex" is the number of lives user has. "highscore" is 
the highest score attained by any user in the game, "num_balls" is a counter variable 
used to determine the number of balls generated, so that the speed gets faster every 10 balls.*/


int lifeindex=3;
int scoreindex=0;
int highscore=0;
int num_balls = 0;

/*Defining class "start_game", which holds all of the functions and necessary variables for game to run. 
In the public section, all of the functions used in the program are defined.*/


class start_game
{
public:
void preliminary();
void mainmenu();
void timer_countdown();
void game_start_setup();
void game (int b=20, int c=20);
void life_count();
void lifescreen();
void football_gen();
void check_user_touch();
void dissapear();

/*In the private section of the class definition, variables 
"x_pos" and "y_pos" are defined which are the x and y coordinates 
respectively of each football as it is moving. "velocity" is a variable 
that controls the speed of the balls. "highscorefile" is defined for 
reading and writing the highest score.*/

private:
float x_pos=20, y_pos=20;
float velocity = 0.25;
FEHFile *highscorefile;
};

/*int main() is used to define the object for accessing functions and the "preliminary" function is called.*/

//Anoushka, Omer, Mike, Tori

int main() 
{
    /*"footballs" is the object belonging to the class start_game, 
    which allows the functions to be accessed within int main()*/


    start_game footballs;
    footballs.preliminary();
}


    /*"preliminary" function clears screen and allows user to navigate through the menu options.*/

    //Anoushka, Omer, Mike, Tori

    void start_game::preliminary()
    {
    
        /* creates infinite while loop to ensure that user can continue navigating through the menu options until they quit the game.*/


        while (0<1)
        {

        /*Screen is initally cleared*/


        LCD.Clear();
        
    
        /*Calls function mainmenu, which displays four button options at beginning of program, as well as title for game.*/

        mainmenu();

  /*Intializes variables "x" and "y" to be the coordinates of the user's touch.*/ 

        int x;
        int y;

        /*Reads in user's touch, as well as sets the writing font color to white.*/

        while (!LCD.Touch(&x,&y))
        {}
        LCD.SetFontColor(LCD.White);

        /*If user clicks on "play game" button, "timer_countdown" function is called. 
        This creates countdown for 3 seconds before game starts. "DrawColor" is set to red for the buttons.*/

            if (x>=10 && x<=159.5 && y>=20 && y<=119.5)
            {
                LCD.Clear();   
                LCD.SetDrawColor(LCD.Red);
        
                timer_countdown();


            /*Calls function "game_start_setup" that sets up the football stadium in background, 
            displays the amount of lives in the top left corner, and displays the score in the top right corner.*/
                
                game_start_setup();


                /*creates while loop that runs until user has lost their lives, 
                which calls function "football_gen", which generates random x,y coordinates of the footballs.*/


                while (lifeindex!=0)
                {
                football_gen();
                }
            
            } 

        /*If user clicks "instruction" button, current screen is cleared and new screen 
        appears displaying instructions. "Back" option button is presented to return to main menu if pressed.*/

            else if(x>=170 && x<=319.5 && y>=20 && y<=119.5)
            {
            LCD.Clear();
            LCD.WriteLine("Footballs will be shot from both sides.");
            LCD.WriteLine("Touch each football to");
            LCD.WriteLine("catch it before it hits"); 
            LCD.WriteLine("the ground in order to"); 
            LCD.WriteLine("score a touchdown."); 
            LCD.WriteLine("The footballs will be thrown faster"); 
            LCD.WriteLine("and faster as the game goes on.");
            LCD.WriteLine("If you drop 3 footballs, the game");
            LCD.WriteLine(" will end!");
            LCD.SetDrawColor(LCD.Red);
            LCD.FillRectangle(180,20,139.5,99.5);
            LCD.WriteAt("Back",180,59.75);
            
            /*If user clicks "back" button, screen is cleared, and mainmenu function is called.*/

                while (!LCD.Touch(&x,&y))
                {}
                if (x>=180 && x<=319.5 && y>=20 && y<=119.5)
                {
                LCD.Clear();
                mainmenu();
                }
            }

        /*If user clicks "see statistics" button, current screen is cleared and new screen with the high score is displayed using information written to a file.
         
        Back button is presented to return to main menu*/

            else if(x>=10 && x<=159.5 && y>=129.5 && y<=229)
            {
            LCD.Clear();
            LCD.WriteAt("High Score=",20,0);

            /*"score_record.txt" file is opened for reading*/

            highscorefile = SD.FOpen("score_record.txt", "r");
            
            /*ensures file opened correctly, otherwise message is written indicating it didn't open.*/

            if (highscorefile == NULL)
            {
                LCD.WriteAt("File could not be opened.", 120, 0);
            }

            /*if file opened correctly, the value existing in the file is scanned into variable "highscore".*/

            else
            {   
                SD.FScanf(highscorefile, "%d", &highscore);
                
            }

            /*file is closed.*/

            SD.FClose(highscorefile);

            /*highscore is written to the screen if user clicks "statistics" button, and the "back" button is presented to the user.*/

            LCD.WriteAt(highscore,120,0);
            LCD.SetDrawColor(LCD.Red);
            LCD.FillRectangle(170,20,149.5,99.5);
            LCD.WriteAt("Back",172,59.75);

            /*If user presses "back" button, screen is cleared, and mainmenu function is called.*/

            while (!LCD.Touch(&x,&y))
            {}
                if (x>=170 && x<=319.5 && y>=20 && y<=119.5)
                {
                LCD.Clear();
                mainmenu();
                }
            }

        /*If user presses see credits button, current screen is cleared and new screen is created with the creators of game displayed as well as back button option presented.*/ 

            else if(x>=170 && x<=319.5 && y>=129.5 && y<=229)
            { 
            LCD.Clear();
            LCD.Write("This game was created by"); 
            LCD.WriteLine(" Omer Sarig");
            LCD.WriteLine("Anoushka Dasi"); 
            LCD.WriteLine("Michael Grassi");
            LCD.WriteLine("Tori Ostrow");
            LCD.SetDrawColor(LCD.Red);
            LCD.FillRectangle(170,20,149.5,99.5);
            LCD.WriteAt("Back",172,59.75);
        
           
            /*If user presses "back" button, mainmenu function is called.*/

            while (!LCD.Touch(&x,&y))
            {}
                if (x>=170 && x<=319.5 && y>=20 && y<=119.5)
                {
                LCD.Clear();
                mainmenu();
                }
            } 
    
        }
    }
    


/*Function that creates the four buttons initially in the main menu 
for user to choose from. These are play game, see statistics, see 
instructions, and see credits. Title for game is written to the screen.*/

//Anoushka, Omer, Mike, Tori

void start_game::mainmenu()
{
  int x, y;
  LCD.WriteAt("Catch TD's Like Chris Olave!",80,0);
    LCD.SetDrawColor(LCD.Red);
    LCD.SetFontColor(LCD.White);
    LCD.FillRectangle(10,20,149.5,99.5);
    LCD.WriteAt("Begin Game",12,59.75);
    LCD.FillRectangle(170,20,149.5,99.5);
    LCD.WriteAt("See Instructions",172,59.75);
    LCD.FillRectangle(10,129.5,149.5,99.5);
    LCD.WriteAt("See Statistics",12,164.25);
    LCD.FillRectangle(170,129.5,149.5,99.5);
    LCD.WriteAt("Show Credits",172,164.25); 
}

/*Function that clears the screen and displays to the user that the game will start in
 3 seconds, and counts down from 3 seconds until game starts. 
 This occurs each time user initially presses "play game" or if a user loses a life while playing.*/

//Omer

void start_game::timer_countdown()
{
    LCD.Clear();
    LCD.WriteAt("Game Will Start in 3",110,20);
    Sleep(1.0);
    LCD.Clear();
    LCD.WriteAt("2",165,20);
    Sleep(1.0);
    LCD.Clear();
    LCD.WriteAt("1",165,20);
    Sleep(1.0);
    LCD.Clear();  
}

/*Function that sets up the functionality of the game 
when user presses "start game". The user's score is initially set 
to 0. The screen is then cleared and a new screen with an OSU 
football stadium background is drawn. Balls are drawn in the top 
left corner corresponding to the number of lives the user has left.*/

//Omer

void start_game::game_start_setup()
{
    
    LCD.Clear();
    LCD.SetDrawColor(FORESTGREEN);
    LCD.FillRectangle(0,0,319,239);

    check_user_touch();
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Score=",180,0);
    LCD.WriteAt(scoreindex,240,0);
    LCD.SetDrawColor(WHITE);
    LCD.DrawHorizontalLine(25,10,307);
    LCD.DrawHorizontalLine(214,10,307);
    LCD.DrawVerticalLine(10,25,214);
    LCD.DrawVerticalLine(37,25,214);
    LCD.DrawVerticalLine(64,25,214);
    LCD.DrawVerticalLine(91,25,214);
    LCD.DrawVerticalLine(118,25,214);
    LCD.DrawVerticalLine(145,25,214);
    LCD.DrawVerticalLine(172,25,214);
    LCD.DrawVerticalLine(199,25,214);
    LCD.DrawVerticalLine(226,25,214);
    LCD.DrawVerticalLine(253,25,214);
    LCD.DrawVerticalLine(280,25,214);
    LCD.DrawVerticalLine(307,25,214);

    LCD.SetDrawColor(SCARLET);
    LCD.FillRectangle(10,25,28,190);
    LCD.FillRectangle(280,25,28,190);
    
    LCD.DrawCircle(159.5,119.5,10);
    LCD.DrawCircle(159.5,119.5,20);
    LCD.SetDrawColor(SCARLET);
    LCD.FillCircle(159.5,119.5,20);
    LCD.SetDrawColor(WHITE);
    LCD.FillCircle(159.5,119.5,10);


    if (lifeindex ==3)
    {

        LCD.SetDrawColor(BROWN);
        LCD.FillCircle(0,0,8);
        LCD.FillCircle(30,0,8);
        LCD.FillCircle(52,0,8);
    }

    else if (lifeindex ==2)
    {
        LCD.SetDrawColor(BROWN);
        LCD.FillCircle(0,0,8);
        LCD.FillCircle(30,0,8);
    }

    else if (lifeindex ==1)
    {
        LCD.SetDrawColor(BROWN);
        LCD.FillCircle(0,0,8);
    }

}

/*function "life_count" is used to decrement the number of 
lives the user has each time they fail to click the ball before it falls off the screen.*/

//Tori

 void start_game::life_count()
   {
            /*Sets up beginning of game with user having 3 lives. 
            If a football falls off of the screen, one life is 
            lost, and the game resets and timer_countdown function 
            is called, as well as lifescreen function.*/

            while (lifeindex==3)
            {    
                
                if (y_pos+20>239)
                {
                lifeindex-=1;
                lifescreen();
                timer_countdown();
                }
            }

            /*If user has two lives left and football falls off screen, user loses a life and 
            timer_countdown function is called as well as 
            lifescreen function.*/

            while (lifeindex==2)
            {
                    
                    if ((y_pos+20)>239)
                    {
                    lifeindex-=1;
                    lifescreen();
                    timer_countdown();
                    }
            }
            
            /*If user has one life left and football falls off screen, user loses a life and 
            timer_countdown function is called as well as lifescreen function.*/

            while (lifeindex==1)
            {
                
                if ((y_pos+20)>239)
                {
                lifeindex-=1;
                lifescreen();
                timer_countdown();
                }
            }
 
                /*If user loses all lives, function "lifescreen" is called, 
                and the game ends.*/

                if (lifeindex==0)
                {
                lifescreen();
                }
    }
/*function "football_gen" randomly generates the initial starting positions of the footballs.*/

//Anoushka

void start_game::football_gen()
{
    /*Calls function "check_user_touch" to see if user 
    touched football*/
    
    check_user_touch();


    /*srand allows random generator to function. 
    Random footballs are generated from distinct locations 
    of the screen. This occurs by dividing by random generated 
    numbers by 3 and adding 1 to the answer, which will always 
    yield a number 1-3.*/
    
    
    srand(time(NULL));
    int rand_x_y=(rand()%3)+1;

        /*If 1 is yielded from the random number generator, 
        footballs appear from the top middle portion of the screen. Random x positions are generated,
        counter variable "num_balls" is incremented, and "game" function is called.*/

        if (rand_x_y ==1)
        {
        num_balls++;
        int football_gen_x=(rand()%279)+20;
        game(football_gen_x,20);
                    
        }

        /*If 2 is yielded from the random number generator, 
        footballs appear from the top right portion of the 
        screen. Random y positions are generated,
        counter variable "num_balls" is incremented, and "game" function is called.*/

        else if (rand_x_y ==2)
        {
            num_balls++;
            int football_gen_z=(rand() %119)+20;
        game(289, football_gen_z);
        
        }

        /*If 3 is yielded from the random number generator, 
        footballs appear from the top left portion of the screen. 
        Random y positions are generated, counter variable "num_balls"
        is incremented, and "game" function is called.*/

        else if (rand_x_y ==3)
        {
            num_balls++;
        int football_gen_y= (rand()% 119)+20;
        game(20,football_gen_y);
            
        }
    
}


/*Declares "game", which is in class "start_game. This function moves each ball using kinematic equations.*/

//Anoushka

void start_game::game (int x_loc, int y_loc)
{

    /*for every tenth ball generated, the speed in which they fall gets incremented 
    by 0.25 using the variable "velocity". A statement is written to the screen.*/

    if((num_balls % 10) == 0)
    {
        velocity = velocity + 0.25;
        LCD.SetDrawColor(FORESTGREEN);
        LCD.FillRectangle(80, 219, 150, 15);
        LCD.WriteAt("Balls are faster!", 80, 219);
        Sleep(0.5);
        LCD.FillRectangle(80, 219, 150, 15);
    }

    /*Footballs are drawn as circles of radius 20 in 
    the random x and y  locations that were generated 
    in the int main function.*/

    LCD.SetDrawColor(BROWN);
    LCD.FillCircle(x_loc,y_loc,20);

    /*"srand" fucntion allows random generator to work.*/

    srand(time(NULL));
    
    /*Variables "t" is defined to be used as a parameter for 
    football trajectory calculation.*/

    float t = 0.0;

    /*Intializes variables "x_pos" and "y_pos" which are to be the 
    changing x and y coordinates of each football. These are set 
    equal to "x_loc and "y_loc", which are the initial x and y 
    coordinates of each football when generated.*/

    x_pos=x_loc;
    y_pos=y_loc;
    
    
    /*Ensures football is not off of the screen, accounting for the radius of 
    size 20. "DrawColor" is set to brown. Generates footballs with kinematic equation used to move each 
    football to new location.*/
    
        while((y_pos+20)<= 239)
        {
            LCD.SetDrawColor(BROWN);

                /*If football is originally generated from the left 
                portion of the screen, trajectory equation is performed 
                so that it is thrown towards the right side of the screen.*/

                if(x_loc<159)
                {
                x_pos = x_pos + (velocity * t);
                y_pos = y_pos + (velocity * t) + (0.000025 * pow(t, 2));
                LCD.FillCircle(x_pos,y_pos,20);
                check_user_touch();
                 }

            /*Ensures football on right or middle side of the screen is shot 
            towards the left, and uses kinematic equation to move each 
            football accordingly.*/

                else 
                {
                x_pos = x_pos - (velocity * t);
                y_pos = y_pos + (velocity * t) + (0.000025 * pow(t, 2));
                LCD.FillCircle(x_pos, y_pos,20);
                check_user_touch();
                }
            
        /*Clears the screen after each change in football position. 
        Then, 1 is added to t in order to change kinematic equation and move the football.
        "DrawColor" is set to forestgreen to give the illusion that the ball is moving.*/

        LCD.SetDrawColor(FORESTGREEN);
        LCD.FillCircle(x_pos,y_pos,20);
        t+=1;
        }  

        /*"life_count" function is called to check if the ball left the screen, and user loses a life.*/

        life_count();  
    
}    

/*Declares function "lifescreen" within class "start_game". This 
is called when user loses a life. It clears the screen, and creates 
new screen that shows high score, current score, and how many lives are left.*/

//Mike, Tori

void start_game::lifescreen()
{
/*Intializes variables "a" and "b" for the user's touch.
Also clears the screen.*/

   
   int a, b;
   LCD.Clear();
   

   /*Create an if statement to see if the current value is higher than the 
   current high score. Opens "score_record.txt" for writing the high score.
   Actual high score is written to the file, and file is closed.*/
   
   if (scoreindex>highscore)
   {
       highscore = scoreindex;
       LCD.Write("High score: ");
       LCD.WriteLine(highscore);
       highscorefile = SD.FOpen("score_record.txt", "w");
       SD.FPrintf(highscorefile, "%d", highscore);
       SD.FClose(highscorefile);
   }
   /* if the current score is not greater than the high score, show the current high score*/
   else
   {
       LCD.Write("High score: ");
       LCD.WriteLine(highscore);
   }

   
   /*Informs the user how many lives they have left, as well as their score.*/

   LCD.Write("Lives left: ");
   LCD.WriteLine(lifeindex);
   LCD.Write("Your current score is: ");
   LCD.WriteLine(scoreindex);

   /*Create an if statement if the user has lost all of their lives, and have 0 left*/

   if (lifeindex == 0)
       {
           /*Writes that the game is over.*/

           LCD.WriteLine("Game Over");
           LCD.WriteLine("You don't have the moves like Olave");
           LCD.WriteLine("just yet, keep practicing!");
           LCD.WriteLine("");

           /*Create two buttons, giving user option to either quit 
           and return to main menu, or play again using red color 
           for the buttons and white color for writing.*/

           LCD.SetDrawColor(LCD.Red);
           LCD.SetFontColor(WHITE);
           LCD.FillRectangle(29.5, 170, 110, 30);
           LCD.WriteAt("Play Again", 31.5, 172);
           LCD.FillRectangle(179.5,170,110,30);
           LCD.WriteAt("Main Menu",181.5,172);

           /*Register the touch of the player to see if they 
           pressed the main menu button or play again button.
           Variable "j" is used to ensure that the user only 
           touches the play again or main menu button.*/

           int j=0;
           while (j ==0)
           {
            while(!LCD.Touch(&a, &b))
            {}
           
                if (a>=179.75 && a<=289.75 && b>=170 && b<=200)
                {

               /*If user chooses to go back to main menu, lives are reset to 3, 
               y position of the football is set to 0, score is set to 0, 
               number of footballs is set to 0, velocity is set to original value,
               "preliminary" function is called, "j" is now set to 1 so that the loop is exited, 
               and the user can go back to main menu.*/

               lifeindex=3;
               y_pos=0;
               scoreindex=0;
               num_balls = 0;
               velocity = 0.25;
               preliminary();
               j=1;
                }

                else if (a>=29.5 && a<=139.5 && b>=170 && b<=200)
                {
                /*Clear screen and call necessary functions to restart game.
                If user chooses to play again, lives are reset to 3, 
                y position of the football is set to 0, score is set to 0, 
                number of footballs is set to 0, velocity is set to original value,
                "preliminary" function is called, "j" is now set to 1 so that the loop is exited, 
                and the user can play again. Functions "timer_countdown", "game_start_setup", and 
                "football_gen" are called.*/

                LCD.Clear();
                lifeindex=3;
                y_pos=0;
                scoreindex=0;
                num_balls = 0;
                velocity = 0.25;
                timer_countdown();
                game_start_setup();
                football_gen();
                j=1;
                }
       
                /*If the user presses another location or no buttons are pressed, "j" remains 0, and loop continues.*/

                else 
                {
                j=0;
                }
            }
       }    
/*If user has lost a life but still has either 1 or 2 lives 
remaining, a message is printed to the screen that a life was lost 
and then necessary functions are called for game to 
countdown starting and then function.*/
    
   else if(lifeindex == 1 | lifeindex == 2)
   {
       LCD.WriteAt("Oh no! One life was lost!",120,119.5);
       Sleep(4.0);
       timer_countdown();
       game_start_setup();
       football_gen();
   }
}

/*Function that checks whether user has touched moving football. 
If user touches football, "dissapear" function is called, and 7 is added to the score. 
The updated score is also written in the top right corner.*/

//Anoushka, Omer, Mike, Tori

void start_game::check_user_touch()
{
    int x;
    int y;
    if(LCD.Touch(&x,&y))
    {
        
        if (x>=x_pos-20 && x<=x_pos+20 && y>=y_pos-20 && y<=y_pos+20)
        {
            scoreindex=scoreindex+7;
            LCD.SetDrawColor(FORESTGREEN);
            LCD.FillRectangle(180,0,100,20);
            LCD.WriteAt("Score=",180,0);
            LCD.WriteAt(scoreindex,240,0);
 
            dissapear();
        }   
    }

}

/*Function that fills in circles with color of background to make it look as if football dissapeared when user touches it.*/

//Anoushka, Omer, Mike, Tori

void start_game::dissapear()
{
LCD.SetDrawColor(FORESTGREEN);
LCD.FillCircle(x_pos,y_pos,20);
football_gen();
}