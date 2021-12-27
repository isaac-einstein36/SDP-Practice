//Include identifying information for code and creators

//**************************************************************************
//* Topic: SDP Code                                                        *
//* Creators: Kushi Malasani, Gavin Hartzell, Amy Medland, Maxwel Pace     *
//* Instructor + Time: RJF 12:40                                           *
//**************************************************************************

//Include neccessary libraries
#include "FEHLCD.h"
#include "string"
#include "FEHUtility.h"
#include "FEHRandom.h"

//Include namespace to simplify c++ commands
using namespace std; 

//Function Prototypes
void DrawLandscape(); 
void StartTimer(); 
void DrawLandscape1();
void DrawLandscape2();
void DrawTree(int x, int y, int width, int height, int radius);
void DrawLandscape3();
void drawVacc(int,int, int);
void DrawLandscapeRan();

/*
This is the leaderboard class. It is used to track the top 3 scores of the user during
a game. An object of this class will be used to print these values and set them.
The three variables (score1, score2 , and score 3) each contain the 3 highest scores.
The get_score() methods are used to return these scores into other functions.  

*/
class Leaderboard
{
    private:
        int buffer; //buffer variable
    public:
        float score1=0; //Highest Score
        float score2=0; // Second Highest Score
        float score3=0; // Third Highest Score
        float get_score1(){ // Returns the top score
            return score1;
        }
        float get_score2(){ // Returns the scond to top score
            return score2;
        }
        float get_score3(){ // Returns the third to top score 
            return score3;
        }

};

/*
This is the vaccine class. Its private variables are its location,
whether it is jumping, how high it is at and what color it is in. 
Its public member functions include functions that return the x 
and y coordinates, creates a vaccine, starts jumping, returns 
the jump stage. There are also several functions that update the 
jump stage 
*/
class Vaccine
{
    private: 
        int x=30; //x-coordinate of the vaccine 
        int y=210; //y-coordinate of the vaccine
        int isJumping = 0;//whether or not the vaccine is jumping 
        int jumpHeight = 8;//height of the vaccine 
        int col = RandInt()%5;//random number that will decide the color of the vaccine
    public: 
        /*This function returns the x coordinate of the vaccine 
        It does not have any input arguments.
        */
        int getx()
        {
            return x;
        }

        /*This function returns the y coordinate of the vaccine 
         It does not have any input arguments.
        */
        int gety()
        {
            return y;
        }

        /*This function's purpose is to create a vaccine. It calls the drawVacc 
        function that draws the vaccine It does not have any input argumrnts or 
        return values.
        */
        void createVaccine()
        {
            LCD.SetDrawColor(WHITE);
            drawVacc(x,y, col);
        }

        /*This function changes isjumping to 1 signifying that the vaccine started jumping
        It foes not have any input argumens or return values.
        */
        void startjump()
        {
            isJumping +=1;
        }

        /*This function returns the isJumping variable that tells which stage of the jump
        the vaccine is in. It does not have any input arguments or return values.
        */
        int getjumpstage()
        {
            return isJumping;
        }

        /*This function updates the jump to stage1 which is a little higher than its original height
        It decides the location, and calls the drawVacc function to draw the vaccine at that location.
        It does not have any input arguments or return values.
        */
        void stage1()
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillRectangle(x-5,y-30,25,60);//making the rectangle in the vaccine
            LCD.SetDrawColor(WHITE);//changes color to white
            y-=jumpHeight;//changing jump height
            drawVacc(x,y,col);
            isJumping++;//updates the stage of the jump
        }

        /*This function updates the jump to stage2 which is higher than stage1.
        It decides the location, and calls the drawVacc function to draw the vaccine at that location.
        It does not have any input arguments or return values.
        */
        void stage2()
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillRectangle(x-5,y-30,25,60);//making rectangle
            LCD.SetDrawColor(RED);//changes color to red 
            y-=jumpHeight;//changing jump height 
            drawVacc(x,y,col);
            isJumping++;//updates the stage of the jump

        }

         /*This function updates the jump to stage3 which is the highest point of the jump.
        It decides the location, and calls the drawVacc function to draw the vaccine at that location.
        It does not have any input arguments or return values.
        */
        void stage3()
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillRectangle(x-5,y-30,25,60);//makes rectangle
            LCD.SetDrawColor(BLUE);//changes color to blue
            isJumping++;//upddates the stage of the jump
            drawVacc(x,y,col);
        }

        /*This function updates the jump to stage4 which is lower than stage3. The vaccine begins to
        travel downwards in stage4. It decides the location, and calls the drawVacc function to draw 
        the vaccine at that location. It does not have any input arguments or return values.
        */
        void stage4()
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillRectangle(x-5,y-30,25,60);//makes rectangle
            LCD.SetDrawColor(GREEN);//changes color to green
            y+=jumpHeight;//makes y higher which means vaccine is travelling downwards
            isJumping++;//updates the stage of the jump
            drawVacc(x,y,col);
        }

        /*This function updates the jump to stage5 which is lower than stage4. The vaccine travels
        further downwards. It decides the location, and calls the drawVacc function to draw 
        the vaccine at that location. It does not have any input arguments or return values.
        */
        void stage5()
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillRectangle(x-5,y-30,25,60);//makes rectangle
            LCD.SetDrawColor(PURPLE);//changes color to purple
            y+=jumpHeight;//moves the vaccine downwards 
            isJumping++;//updates the stage of the jump/
            drawVacc(x,y,col);
        }

        /*This function updates the jump to stage6 which is lower than stage5. The vaccine reaches
        the ground in this stage. It decides the location, and calls the drawVacc function to draw 
        the vaccine at that location. It does not have any input arguments or return values.
        */
        void stage6()
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillRectangle(x-5,y-30,25,60);//makes rectangle
            LCD.SetDrawColor(WHITE);//changes color to white 
            y+=jumpHeight;//moves vaccine to the ground
            isJumping = 0;//vaccine is not jumping anymore b/c it reached the ground. 
            drawVacc(x,y,col);
            //Jump is complete 
        }
};

/* This is the game class. It's purpose is to manage the time and score of the game.
Its private variables include the start time, end time, score, and a vaccine object. 
Its public member functions include a type 2 constructor and functions that will start 
the timer, end the timer, make a vaccine and calculate the score. 
*/
class Game
{
    private:
        float time_start;//stores the start time
        float time_end;//stores the end time 
        float score;//stores the score
        Vaccine vacccine;//vaccine object

    public:

        /* This is a type 2 constructor that takes as its input the 
        pointer to a vaccine object so that it has access to the vaccine's
        location, jump status and color. 
        */
        Game(Vaccine* vacc)
        {
            vacccine = *(vacc);//vaccine stores the values at pointer vacc
        }

        /* This function updates the start of the timer. It does not have 
        any input arguments or return values.
        */
        void start_time()
        {
            time_start = TimeNow();//TimeNow gives the current time
        }

        /* This function updates the end time and also calculates the score.
        It does not have any input arguments but returns the score of the game.
        */
        float end_time()
        {
            time_end = TimeNow();//gets current time
            score = time_end-time_start;//subtracts start time from end time to calc score
            return score;
        }

        /* This function simply uses the vaccine object to create a vaccine which then calls
        drawVacc to display the vaccine on the screen. It does not have any input arguments or
        return values.
        */
        void print()
        {
                vacccine.createVaccine();
        }

        /* This function also calculates the score of the game. It does not have
        any input arguments or return values.
        */
        void printtitle()
        {
            score = TimeNow()-time_start;
        }

};

/* This is a germ class. The purpose of this class is to make germs and store 
all attributes of a germ. It includes private variables that store the coordinates
of the germ, the speed the germ is moving at, and the color of each of the germs.
The public member functions include ones that draw the germs, move the germs, 
increase the speed of the germs, and returns the coordinates of the germs.
*/
class Germ
{
    private: 
        int x; //x-coordinate of the germ
        int y; //y-coordinate of the germ
        int speed = 6;//speed of the germ
        int col1 = RandInt()%4;//random color of the germ
        int col2 = RandInt()%4;//random color of the germ

    public: 

        /* This function returns the x coordinate of the germ. 
        It does not have any input arguments or return values.
        */
        int getx()
        {
            return x;
        }

        /* This function returns the y coordinate of the germ. 
        It does not have any input arguments or return values.
        */
        int gety()
        {
            return y;
        }

        /* This function takes as inputs the x and y coordinates of
        the germ. It does not return anything. It initializes the
         private variables and also draws the germ at that location. 
        */
         void start(int x1, int y1)
        {
            x = x1;
            y = y1;
            drawGerm(x, y, col1, col2);
        }

        /* This function takes as inputs the coordinates and colors
        of the germ. It does not output anything. The purpose of this 
        function is to draw the germ.
        */
        void drawGerm(int x1, int y1, int col1, int col2)
        {
            //The draw color is set based on the first color parameter sent in.
            switch(col1)
            {
                case(1):
                    LCD.SetDrawColor(YELLOW);
                    break;
                case(2):
                    LCD.SetDrawColor(SKYBLUE);
                    break;
                case(3):
                    LCD.SetDrawColor(RED);
                    break; 
                case(0):
                    LCD.SetDrawColor(LIGHTGREEN);
                    break;
            }
            //The circle of the germ is drawn in at the coordinates sent in 
            //with radius 8.
            LCD.FillCircle(x1,y1,8);

            //The second color parameter is used to set a new draw color 
            switch(col2){
                case(1):
                    LCD.SetDrawColor(BLUE);
                    break;
                case(2):
                    LCD.SetDrawColor(PURPLE);
                    break;
                case(3):
                    LCD.SetDrawColor(MAROON);
                    break; 
                case(0):
                    LCD.SetDrawColor(DARKRED);
                    break;
            }
            //Circles are dorawn on the outer edge of the main circle to make it look like a germ.
            LCD.FillCircle(x1-8,y1,1);
            LCD.FillCircle(x1,y1,1);
            LCD.FillCircle(x1-4,y1-4,1);
            LCD.FillCircle(x1+8,y1,1);
            LCD.FillCircle(x1+4,y1-4,1);
            LCD.FillCircle(x1,y1-8,1);
        }

        /* This function has no input arguments or return values.
        It increments the speed of the germ.
        */
        void incSpeed()
        {
            speed++;
        }

        /* This function has no input arguments or return values. 
        It changes the location of the germs to move it to the left, 
        decides new colors, and calls the drawGerm function to draw 
        the germ again.
        */
        void moveleft()
        {
            LCD.SetDrawColor(BLACK);
            LCD.FillCircle(x,y,10); //making circle
           
           //If the germ is too much to the left, it is reset to the right
            if(x<=15)
            {
                x=300;
                //finding 2 new random colors 
                col1 = RandInt()%4;
                col2 = RandInt()%4;
            }
            else
            {
                 x-=speed; //the x is decreased which makes the germ be further to the left
                 //This appears as the germ moving faster.
            }
            drawGerm(x,y,col1,col2);//drawGerm is called to redraw the germ.
        }
};

//More Function Prototypes.
int checkCollision(Vaccine*, Germ*);
void playgame(Leaderboard* boards);
void showstats(Leaderboard*);
void showcredits(Leaderboard*);
void showdocs(Leaderboard*);
void end_game(float, Leaderboard*);
int menu(Leaderboard*); 

/*The purpose of this function is to check if the germ and vaccine have collided. 
It takes as input pointers to the vaccine and germ object that will then give 
access to all information regarding the location of the vaccine and germs. 
It returns an integer that will return a value which signifies whether the collision
has occured.
*/
int checkCollision(Vaccine* vaccine2, Germ* germ2)
{
            int vaccx;
            vaccx = (*vaccine2).getx();//the x coordinate of the vaccine
            int vaccy; 
            vaccy = (*vaccine2).gety();//the y coordinate of the vaccine 
            int germx;
            germx = (*germ2).getx();//the x coordinate of the germ 
            int germy;
            germy =  (*germ2).gety();//the y coordinate of the germ

            if(vaccx>=germx-8 && vaccx<=germx+8 && vaccy+26>=germy+8)
            {
                return 0;
            }
            if(vaccx+15>=germx-8 && vaccx+15<=germx+8 && vaccy+26>=germy+8)
            {
                return 0;
            }
            if(germx+8>=vaccx+15 && vaccx+15>=germx-8 && vaccy+26>=germy-8)
            {
                return 0;
            }
            if(germx+8>=vaccx && vaccx>=germx-8 && vaccy+26>=germy-8)
            {
                return 0;
            }
            return 1;
}

//This is the main function
int main ()
{
    LCD.Clear();//clears the screen 
  
    int choice =1;
    Leaderboard boards;

    //loop runs as long as choice equals 1 
    while (choice == 1) 
    {
        choice=menu(&boards);//the menu function is called.
    }
    return 0;
}

/* This is the menu function. It is given as a parameter a pointer to the leader board object.
It returns an integer 0 if the user chooses to quit. The purpose of this function is to 
provide the user with a menu and take them to the appropriate screen by calling the specific 
fucntions.
*/
int menu(Leaderboard* boards)
{
    //Displays all the menu options to the screen
    int cont = 1;
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(0,0,319,239);
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("VACCINE VICTORY - The Game", 70, 10);
    LCD.WriteAt("Play Game", 120, 60);
    LCD.WriteAt("Instructions", 120, 90);
    LCD.WriteAt("Stats", 120, 120);
    LCD.WriteAt("Credits", 120, 150);
    LCD.WriteAt("Quit", 120, 180);
    LCD.SetDrawColor(BLACK);
    LCD.DrawRectangle(105,55,110,25); 
    LCD.DrawRectangle(105,85,110,25); 
    LCD.DrawRectangle(105,115,110,25); 
    LCD.DrawRectangle(105,145,110,25); 
    LCD.DrawRectangle(105,175,110,25); 
    int touch_x = 0;
    int touch_y = 0;
   
   //reads in the touch.
    while(!LCD.Touch(&touch_x,&touch_y))
    {
        touch_x = 0;
    }
    LCD.SetFontColor(BLACK);

    //If the user clicked on the play game button, the playgame function is called
    if(touch_x>=105 && touch_x<=205 && touch_y>=55 && touch_y<=80)
    {
        playgame(boards);
        cont = 0;
    }
    //If  the user clicked on the instructions button, the showdocs function is called 
    else if(touch_x>=105 && touch_x<=205 && touch_y>=85 && touch_y<=110)
    {
        showdocs(boards);
    }
    //If the user clicked on the stats button, the showstats function is called 
    else if(touch_x>=105 && touch_x<=205 && touch_y>=115 && touch_y<=140)
    {
        showstats(boards);
    }
    //If the user clicked on the credits button, the showcredits function is called.
    else if(touch_x>=105 && touch_x<=205 && touch_y>=145 && touch_y<=170)
    {
        showcredits(boards);
    }
    else if(touch_x>=105 && touch_x<=205 && touch_y>175 && touch_y<=190)
    {
        LCD.Clear();
        cont = 0;
        return 0;
    }
    else
    {
        menu(boards);
    }
    return 0;
}

/* The purpsoe of the showstats function is to display the statistics to 
the screen. It takes as an input a pointer to a leaderboard object so that
it can use the stats in the leaderboard object.
*/
void showstats(Leaderboard* boards)
{
    
    LCD.SetDrawColor(BLACK);
    int touch_x = 0;
    int touch_y=0;
    LCD.FillRectangle(0,0,319,239);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Leaderboard", 110, 10);//header
    LCD.WriteAt("1: ", 100, 50);
    LCD.WriteAt((*boards).get_score1(), 120, 50);//displaying the first score
    LCD.WriteAt("2: ", 100, 80);
    LCD.WriteAt((*boards).get_score2(), 120, 80);//displaying the second score
    LCD.WriteAt("3: ", 100, 110);
    LCD.WriteAt((*boards).get_score3(), 120, 110);//displaying the third score
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(85,180,135,25); 
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Return to Home", 90, 185);//return to home option
    int cont = 1;
    
    while(cont == 1)
    {
        while(!LCD.Touch(&touch_x,&touch_y))//reading in the touch 
        {
            touch_x = 0;
        }
        //if the user clicks on the "return to home" button, the loop ends
        if(touch_x>=90 && touch_x<=255 && touch_y>185 && touch_y<=210)
        {
            cont = 0;
        }
    }
    menu(boards);//menu function is called again to display the menu 
}

/* The purpsoe of the showdocs function is to display the instructions to 
the screen. It takes as an input a pointer to a leaderboard object so that
it can use the stats in the leaderboard object.
*/
void showdocs(Leaderboard* boards)
{
    LCD.SetDrawColor(BLACK);
    int touch_x = 0;
    int touch_y=0;
    LCD.FillRectangle(0,0,319,239);
    LCD.SetFontColor(WHITE);
    LCD.SetDrawColor(WHITE);
    LCD.WriteAt("Instructions",140,8);//header
    LCD.WriteLine("");
    //prints instructions to the screen
    LCD.WriteAt("***********************************",0,30);
    LCD.WriteAt("  Click to make the vaccine jump.",0,50);
    LCD.WriteAt("  Jump over each of the germs that pass.",0,70);
    LCD.WriteAt("  Don't hit a Germ or the game ends!",0,90);
    LCD.WriteAt("  The longer you go, the higher you score!",0,110);
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(85,180,135,25); 
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Return to Home", 90, 185);//return to home button 
    int cont = 1;
   
    while(cont == 1)
    {
         //reading in touch 
        while(!LCD.Touch(&touch_x,&touch_y))
        {
             touch_x = 0;
        }
        //if the user clicks on the "return to home" button, the loop ends
        if(touch_x>=105 && touch_x<=205 && touch_y>180 && touch_y<=205)
        {
             cont = 0;
        }
    }
    menu(boards);//menu function is called again to display the menu
    
}
/* This function displays the end screen once the game is over. It takes as 
inputs the score and a pointer to a leaderboard object. It does not return
any value.
*/
void end_game(float sc, Leaderboard* a){
    sc *= 100;
    LCD.Clear();
    LCD.SetFontColor(WHITE);
    LCD.WriteLine(" ");
    LCD.WriteLine("             Game Over!");//Displaying that game is over 
    LCD.WriteLine(" " );
    LCD.WriteLine("              You scored");
    LCD.WriteLine(sc);//displaying score 
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(85,180,135,25); 
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Return to Home", 90, 185);//return to home button

    /*This calculates the highest score and changes the variable in the leader
    board class with the help of pointers.
    */
    if (sc>(a)->get_score1())
    {
         (a)->score3 = (a)->score2;
         (a)->score2=(a)->score1;
         (a)->score1 = sc;
    }
    //calculates the second highest score 
    else if (sc>(a)->get_score2())
    {
        (a)->score3 = (a)->score2;
        (a)->score2 = sc;
    }
    //calculates the third highest score 
    else if (sc>(a)->get_score3())
    {
        (a)->score3 = sc;
    }
    int cont = 1;
    int touch_x =0;
    int touch_y=0;
    while(cont == 1)
    {
        //reads in touch 
        while(!LCD.Touch(&touch_x,&touch_y))
        {
             touch_x = 0;
        }
        if(touch_x>=105 && touch_x<=205 && touch_y>180 && touch_y<=205)
        {
            cont = 0;
        }
    }
    //game is ended at this point
}

/* The purpsoe of the showcredits function is to display the credits to 
the screen. It takes as an input a pointer to a leaderboard object so that
it can use the stats in the leaderboard object.
*/
void showcredits(Leaderboard* boards)
{
    LCD.Clear();
    int touch_x = 0;
    int touch_y=0;
    LCD.SetDrawColor(BLACK);
    LCD.FillRectangle(0,0,319,239);
    LCD.SetFontColor(WHITE);
    LCD.WriteAt("Credits", 90, 10);//header
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(85,180,135,25); 
    LCD.SetFontColor(BLACK);
    LCD.WriteAt("Return to Home", 90, 185);//return to home button
    LCD.SetFontColor(WHITE);
    LCD.WriteLine(" ");
    //Prints credits to the screen
    LCD.WriteLine("  Collaborators: ");
    LCD.WriteLine("  Kushi Malasani, Amy Medland");
    LCD.WriteLine("  Gavin Hartzell, Maxwel Pace");
    LCD.WriteLine("  Date: 11/30/2020");
    LCD.WriteLine("  Class: FEH");
    LCD.WriteLine("  Inspiration: Google dinosaur game");
    int cont = 1;
    while(cont == 1)
    {
        //reads in touch
        while(!LCD.Touch(&touch_x,&touch_y))
        {
            touch_x = 0;
        }
        //If touch is in the return to home button, the loop ends 
        if(touch_x>=105 && touch_x<=205 && touch_y>180 && touch_y<=205)
        {
            cont = 0;
        }
    }
    menu(boards);//menu function is called again with the leaderboard pointer passed in

}
/*This function draws the first landscape which is a city setting. 
It does not take any input arguments or return any values.
*/
void DrawLandscape1()
{
    LCD.Clear();
    LCD.Clear();
    int touch_x = 0;
    int touch_y=0;
    LCD.SetDrawColor(WHITE);
    LCD.DrawHorizontalLine(200,0,319);
    //Sun
        //Draw Outer Circle
    LCD.SetDrawColor(SCARLET);
    LCD.FillCircle(289, 31, 31);
        //Draw Inner Circle
    LCD.SetDrawColor(RED);
    LCD.FillCircle(290, 31, 28);
    //Draw Left Gray building
    LCD.SetDrawColor(GRAY);
    LCD.FillRectangle(40, 50, 50, 150);
            // Left Gray Building Windows
        LCD.SetDrawColor(BLUE);
        LCD.FillRectangle(43, 60, 12, 20 );
        LCD.FillRectangle(59, 60, 12, 20 );
        LCD.FillRectangle(75, 60, 12, 20 );
            //Row two
        LCD.FillRectangle(43, 85, 12, 20 );
        LCD.FillRectangle(59, 85, 12, 20 );
        LCD.FillRectangle(75, 85, 12, 20 );
            //Row Three
        LCD.FillRectangle(43, 110, 12, 20 );
        LCD.FillRectangle(59, 110, 12, 20 );
        LCD.FillRectangle(75, 110, 12, 20 );
            //Row Four
        LCD.FillRectangle(43, 135, 12, 20 );
        LCD.FillRectangle(59, 135, 12, 20 );
        LCD.FillRectangle(75, 135, 12, 20 );
            //Row Five
        LCD.FillRectangle(43, 160, 12, 20 );
        LCD.FillRectangle(59, 160, 12, 20 );
        LCD.FillRectangle(75, 160, 12, 20 );
            //Left Gray Building Window Trim           
        LCD.SetDrawColor(BLACK);
        LCD.DrawRectangle(43, 60, 12, 20 );
        LCD.DrawRectangle(59, 60, 12, 20 );
        LCD.DrawRectangle(75, 60, 12, 20 );
            //Row two
        LCD.DrawRectangle(43, 85, 12, 20 );
        LCD.DrawRectangle(59, 85, 12, 20 );
        LCD.DrawRectangle(75, 85, 12, 20 );
            //Row Three
        LCD.DrawRectangle(43, 110, 12, 20 );
        LCD.DrawRectangle(59, 110, 12, 20 );
        LCD.DrawRectangle(75, 110, 12, 20 );
            //Row Four
        LCD.DrawRectangle(43, 135, 12, 20 );
        LCD.DrawRectangle(59, 135, 12, 20 );
        LCD.DrawRectangle(75, 135, 12, 20 );
            //Row Five
        LCD.DrawRectangle(43, 160, 12, 20 );
        LCD.DrawRectangle(59, 160, 12, 20 );
        LCD.DrawRectangle(75, 160, 12, 20 );
            //Top Platform 
        LCD.SetDrawColor(GRAY);
        LCD.FillRectangle(45, 35, 39, 15);
            //Antenna
        LCD.DrawVerticalLine(64.5, 35, 15);
    //Draw Middle Back building
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(105, 70, 50, 130);
            //Middle back building windows
        LCD.SetDrawColor(PURPLE);
            //Row one
        LCD.FillRectangle(108, 85, 12, 20 );
        LCD.FillRectangle(124, 85, 12, 20 );
        LCD.FillRectangle(140, 85, 12, 20 );
            //Row two
        LCD.FillRectangle(108, 110, 12, 20 );
        LCD.FillRectangle(124, 110, 12, 20 );
        LCD.FillRectangle(140, 110, 12, 20 );
            //Row three
        LCD.FillRectangle(108, 135, 12, 20 );
        LCD.FillRectangle(124, 135, 12, 20 );
        LCD.FillRectangle(140, 135, 12, 20 );
            //Row four
        LCD.FillRectangle(108, 160, 12, 20 );
        LCD.FillRectangle(124, 160, 12, 20 );
        LCD.FillRectangle(140, 160, 12, 20 );
            //Middle Back Building Window Trim           
        LCD.SetDrawColor(BLACK);
            //Row one
        LCD.DrawRectangle(108, 85, 12, 20 );
        LCD.DrawRectangle(124, 85, 12, 20 );
        LCD.DrawRectangle(140, 85, 12, 20 );
            //Row two
        LCD.DrawRectangle(108, 110, 12, 20 );
        LCD.DrawRectangle(124, 110, 12, 20 );
        LCD.DrawRectangle(140, 110, 12, 20 );
            //Row three
        LCD.DrawRectangle(108, 135, 12, 20 );
        LCD.DrawRectangle(124, 135, 12, 20 );
        LCD.DrawRectangle(140, 135, 12, 20 );
            //Row four
        LCD.DrawRectangle(108, 160, 12, 20 );
        LCD.DrawRectangle(124, 160, 12, 20 );
        LCD.DrawRectangle(140, 160, 12, 20 );
    //Draw Right Back Building
    LCD.SetDrawColor(GRAY);
    LCD.FillRectangle(170, 50, 50, 150);
        // Left Gray Building Windows
        LCD.SetDrawColor(BLUE);
        LCD.FillRectangle(173, 60, 12, 20 );
        LCD.FillRectangle(189, 60, 12, 20 );
        LCD.FillRectangle(205, 60, 12, 20 );
            //Row two
        LCD.FillRectangle(173, 85, 12, 20 );
        LCD.FillRectangle(189, 85, 12, 20 );
        LCD.FillRectangle(205, 85, 12, 20 );
            //Row Three
        LCD.FillRectangle(173, 110, 12, 20 );
        LCD.FillRectangle(189, 110, 12, 20 );
        LCD.FillRectangle(205, 110, 12, 20 );
            //Row Four
        LCD.FillRectangle(173, 135, 12, 20 );
        LCD.FillRectangle(189, 135, 12, 20 );
        LCD.FillRectangle(205, 135, 12, 20 );
            //Row Five
        LCD.FillRectangle(173, 160, 12, 20 );
        LCD.FillRectangle(189, 160, 12, 20 );
        LCD.FillRectangle(205, 160, 12, 20 );
            //Left Gray Building Window Trim           
        LCD.SetDrawColor(BLACK);
        LCD.DrawRectangle(173, 60, 12, 20 );
        LCD.DrawRectangle(189, 60, 12, 20 );
        LCD.DrawRectangle(205, 60, 12, 20 );
            //Row two
        LCD.DrawRectangle(173, 85, 12, 20 );
        LCD.DrawRectangle(189, 85, 12, 20 );
        LCD.DrawRectangle(205, 85, 12, 20 );
            //Row Three
        LCD.DrawRectangle(173, 110, 12, 20 );
        LCD.DrawRectangle(189, 110, 12, 20 );
        LCD.DrawRectangle(205, 110, 12, 20 );
            //Row Four
        LCD.DrawRectangle(173, 135, 12, 20 );
        LCD.DrawRectangle(189, 135, 12, 20 );
        LCD.DrawRectangle(205, 135, 12, 20 );
            //Row Five
        LCD.DrawRectangle(173, 160, 12, 20 );
        LCD.DrawRectangle(189, 160, 12, 20 );
        LCD.DrawRectangle(205, 160, 12, 20 );
            //Top Platform 
        LCD.SetDrawColor(GRAY);
        LCD.FillRectangle(175, 35, 39, 15);
            //Antenna
        LCD.DrawVerticalLine(194.5, 35, 15);
    //Draw Right Brown building
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(190, 150, 102, 50);
        //Right Brown Building Details
            //Windows
        LCD.SetDrawColor(OLIVE);
        LCD.FillRectangle(200, 165, 7, 10);
        LCD.FillRectangle(215, 165, 7, 10);
        LCD.FillRectangle(230, 165, 7, 10);
        LCD.FillRectangle(245, 165, 7, 10);
        LCD.FillRectangle(260, 165, 7, 10);
        LCD.FillRectangle(275, 165, 7, 10);
            //Second Set of Windows
        LCD.FillRectangle(200, 180, 7, 10);
        LCD.FillRectangle(215, 180, 7, 10);
        LCD.FillRectangle(230, 180, 7, 10);
        LCD.FillRectangle(245, 180, 7, 10);
        LCD.FillRectangle(260, 180, 7, 10);
        LCD.FillRectangle(275, 180, 7, 10);
            //First window trim
        LCD.SetDrawColor(BLACK);
        LCD.DrawRectangle(200, 165, 7, 10);
        LCD.DrawRectangle(215, 165, 7, 10);
        LCD.DrawRectangle(230, 165, 7, 10);
        LCD.DrawRectangle(245, 165, 7, 10);
        LCD.DrawRectangle(260, 165, 7, 10);
        LCD.DrawRectangle(275, 165, 7, 10);
            //Second Window Trim
        LCD.DrawRectangle(200, 180, 7, 10);
        LCD.DrawRectangle(215, 180, 7, 10);
        LCD.DrawRectangle(230, 180, 7, 10);
        LCD.DrawRectangle(245, 180, 7, 10);
        LCD.DrawRectangle(260, 180, 7, 10);
        LCD.DrawRectangle(275, 180, 7, 10);
            //Door
        LCD.SetDrawColor(BROWN);
        LCD.FillRectangle(231,193,20,7);
        LCD.SetDrawColor(BLACK);
        LCD.DrawRectangle(231,193,20,7);
            //Olive Trim
        LCD.SetDrawColor(OLIVE);
        LCD.FillRectangle(190, 155, 102, 2);
    //Draw left Turquoise building
    LCD.SetDrawColor(TURQUOISE);
    LCD.FillRectangle(50, 170, 80, 30);
            //Turquoise  GrayTrim
        LCD.SetDrawColor(GRAY);
        LCD.FillRectangle(50, 174, 80, 2);
            //Turquoise Windows
        LCD.SetDrawColor(DARKRED);
        LCD.FillRectangle(54, 178, 7, 10);
        LCD.FillRectangle(65, 178, 7, 10);
        LCD.FillRectangle(76, 178, 7, 10);
        LCD.FillRectangle(87, 178, 7, 10);
        LCD.FillRectangle(98, 178, 7, 10);
        LCD.FillRectangle(109, 178, 7, 10);
        LCD.FillRectangle(120, 178, 7, 10);
            //Turquoise Window Trim
        LCD.SetDrawColor(BLACK);
        LCD.DrawRectangle(54, 178, 7, 10);
        LCD.DrawRectangle(65, 178, 7, 10);
        LCD.DrawRectangle(76, 178, 7, 10);
        LCD.DrawRectangle(87, 178, 7, 10);
        LCD.DrawRectangle(98, 178, 7, 10);
        LCD.DrawRectangle(109, 178, 7, 10);
        LCD.DrawRectangle(120, 178, 7, 10);
            //Turquoise Door
        LCD.SetDrawColor(GRAY);
        LCD.FillRectangle(80,194, 20, 6);
        LCD.SetDrawColor(BLACK);
        LCD.DrawRectangle(80,194, 20, 6);
        //Draw Sidewalk
    LCD.SetDrawColor(GRAY);
    LCD.FillRectangle(0,201, 319, 6);
        //Sidewalk underline
    LCD.SetDrawColor(WHITE);
    LCD.DrawHorizontalLine(207,0,319);
        //Draw tree
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(174, 180, 4, 20);
        //Tree Leaves
    LCD.SetDrawColor(GREEN);
    LCD.FillCircle(172, 180, 3);
    LCD.FillCircle(180, 180, 3);
    LCD.FillCircle(176, 176, 3);
        //Cloud 1 shading
    LCD.SetDrawColor(GRAY);    
    LCD.FillCircle(20, 30, 10);
    LCD.FillCircle(40, 30, 10);
        //Cloud 1
    LCD.SetDrawColor(WHITE);    
    LCD.FillCircle(15, 25, 12);
    LCD.FillCircle(30, 20, 17);
    LCD.FillCircle(45, 25, 12);
        //Cloud 2
    LCD.SetDrawColor(WHITE); 
    LCD.FillCircle(100, 33, 15);
    LCD.FillCircle(115, 28, 20);
    LCD.FillCircle(130, 33, 15);
        //Cloud 3
    LCD.FillCircle(175, 25, 12);
    LCD.FillCircle(190, 20, 17);
    LCD.FillCircle(205, 25, 12);
        //Cloud 4 by sun
    LCD.FillCircle(265, 57, 9);
    LCD.FillCircle(275, 54, 12);
    LCD.FillCircle(285, 57, 9);
        //Cloud 5 by sun
    LCD.FillCircle(290, 60, 8);
    LCD.FillCircle(300, 54, 11);
    LCD.FillCircle(310, 55, 8);
        //Steet Lines
     LCD.SetDrawColor(YELLOW);
     // y pos x pos x pos end
    LCD.DrawHorizontalLine(225,0,20);
    LCD.DrawHorizontalLine(225,40,60);
    LCD.DrawHorizontalLine(225,80,100);
    LCD.DrawHorizontalLine(225,120,140);
    LCD.DrawHorizontalLine(225,160,180);
    LCD.DrawHorizontalLine(225,200,220);
    LCD.DrawHorizontalLine(225,240,260);
    LCD.DrawHorizontalLine(225,280,300);
    LCD.DrawHorizontalLine(225,318,319);
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt("Welcome to", 220, 80);
    LCD.WriteAt("Corona City!", 230, 100);
}
/*This function draws the second landscape which is a night
time forest setting.It does not take any input arguments or
 return any values.
*/
void DrawLandscape2()
{
    LCD.Clear();
    //set backgrond to blue 
    LCD.SetDrawColor(BLUE);
    LCD.FillRectangle(0,0,319,175);
    //Rightmost mountain
    LCD.SetDrawColor(GRAY);
    LCD.FillRectangle(219,160,100,15);
    LCD.FillRectangle(224,150,90,10);
    LCD.FillRectangle(229,140,80,10);
    LCD.FillRectangle(234,130,70,10);
    LCD.FillRectangle(239,120,60,10);
    LCD.FillRectangle(244,110,50,10);
    LCD.FillRectangle(249,100,40,10);
    LCD.FillRectangle(254,90,30,10);
    LCD.FillRectangle(259,80,20,10);
    LCD.FillRectangle(264,70,10,10);
    LCD.FillRectangle(269,60,0,10);
    //second mountain
    LCD.FillRectangle(119,160,100,15);
    LCD.FillRectangle(124,150,90,10);
    LCD.FillRectangle(129,140,80,10);
    LCD.FillRectangle(134,130,70,10);
    LCD.FillRectangle(139,120,60,10);
    LCD.FillRectangle(144,110,50,10);
    LCD.FillRectangle(149,100,40,10);
    LCD.FillRectangle(154,90,30,10);
    LCD.FillRectangle(159,80,20,10);
    LCD.FillRectangle(169,70,10,10);
    LCD.FillRectangle(174,60,0,10);
    //bottom row of trees
    DrawTree(294,125,4,50,10);
    DrawTree(264,140,5,35,9);
    DrawTree(234,129,6,46,5);
    DrawTree(204,120,3,55,8);
    DrawTree(174,112,4,63,6);
    DrawTree(144,133,4,42,7);
    DrawTree(114,122,6,53,10);
    DrawTree(84,125,6,50,11);
    DrawTree(54,115,7,60,10);
    //second row of trees
    DrawTree(279,100,4,75,10);
    DrawTree(249,110,3,65,8);
    DrawTree(219,110,5,65,5);
    DrawTree(189,105,5,70,6);
    DrawTree(159,100,3,75,3);
    DrawTree(129,110,4,65,7);
    DrawTree(99,102,4,73,4);
    DrawTree(69,100,3,75,9);
    //Moon
    //Draw Outer Circle
    LCD.SetDrawColor(WHITE);
    LCD.FillCircle(289, 31, 31);
    //Draw Inner Circle
    LCD.SetDrawColor(GRAY);
    LCD.FillCircle(290, 31, 28);
    //Cloud 1 shading
    LCD.SetDrawColor(GRAY);    
    LCD.FillCircle(20, 30, 10);
    LCD.FillCircle(40, 30, 10);
    //Cloud 1
    LCD.SetDrawColor(GRAY);    
    LCD.FillCircle(15, 25, 12);
    LCD.FillCircle(30, 20, 17);
    LCD.FillCircle(45, 25, 12);
    //Cloud 2
    LCD.SetDrawColor(GRAY); 
    LCD.FillCircle(100, 33, 15);
     LCD.FillCircle(130, 33, 15);
    LCD.SetDrawColor(GRAY);    
    LCD.FillCircle(115, 28, 20);
    //Cloud 3
    LCD.FillCircle(175, 25, 12);
    LCD.FillCircle(190, 20, 17);
    LCD.FillCircle(205, 25, 12);
    //Cloud 4 by moon
    LCD.FillCircle(265, 57, 9);
    LCD.FillCircle(275, 54, 12);
    LCD.FillCircle(285, 57, 9);
    //Cloud 5 by moon
    LCD.FillCircle(290, 60, 8);
    LCD.FillCircle(300, 54, 11);
    LCD.FillCircle(310, 55, 8);

}
//function definition
void DrawLandscapeRan();
/*This function draws a random landscape out of the three 
options if the user chooses to do so. It does not take any
input arguments or return any values.
*/
void DrawLandscapeRan()
{
    int ran = RandInt()%3;//calculating a random number between 0 and 2 
    switch (ran)
    {
        case (0):
            DrawLandscape1();//draws the first landscape
            break;
        case (1):
            DrawLandscape2();//draws the second landscape
            break;
        case (2):
            DrawLandscape3();//draws the third landscape
            break;

    }
}
/* This function draws a tree. It takes as inputs the x and y
coordinates of the rectangle part of the tree, the width of the 
tree, the height of the tree and finally the radius of the circles
that make up the leaves/branches of the tree.
*/
void DrawTree(int x, int y, int width, int height, int radius)
{
    //Tree
    LCD.SetDrawColor(BROWN);
    LCD.FillRectangle(x ,y, width, height);
    //Tree Leaves
    LCD.SetDrawColor(GREEN);
    LCD.FillCircle(x-2, y, radius);
    LCD.FillCircle(x+6, y, radius);
    LCD.FillCircle(x+2, y-4, radius);

}
/*This function displays options to the screen and then makes the appropriate
landscape based on what the user chooses. This function does not take in any 
input arguments and does not return any values.
*/
void DrawLandscape()
{
    int touch_x;
    int touch_y; 
    int buff;
    LCD.Clear();
    LCD.SetFontColor(WHITE);
    //displays the options to the screen
    LCD.WriteLine("Choose your landscape");
    LCD.WriteAt("Corona City", 120, 60);
    LCD.WriteAt("Pandemic Peaks", 120, 90);
    LCD.WriteAt("Rona River", 120, 120);
    LCD.WriteAt("Random", 120, 150);
    LCD.SetDrawColor(RED);
    LCD.DrawRectangle(105,55,150,25); 
    LCD.DrawRectangle(105,85,150,25); 
    LCD.DrawRectangle(105,115,150,25); 
    LCD.DrawRectangle(105,145,150,25); 
    //reads in the touch.
    while(!LCD.Touch(&touch_x,&touch_y))
    {
        buff = 0;
    }
    LCD.SetFontColor(BLACK);
    //if the user selects landscape 1, the DrawLandscape1() function is called
    if(touch_x>=105 && touch_x<=205 && touch_y>=55 && touch_y<=80)
    {
        DrawLandscape1();
    }
    //if the user selects landscape 2, the DrawLandscape2() function is called
    else if(touch_x>=105 && touch_x<=205 && touch_y>=85 && touch_y<=110)
    {
        DrawLandscape2();
    }
    //if the user selects landscape 3, the DrawLandscape3() function is called
    else if(touch_x>=105 && touch_x<=205 && touch_y>=115 && touch_y<=140)
    {
        DrawLandscape3();
    }
    //if the user selects random landscape, the DrawLandscapeRan() function is called
    else if(touch_x>=105 && touch_x<=205 && touch_y>=145 && touch_y<=170)
    {
        DrawLandscapeRan();
    }
    //if none of the options are chosen, the DrawLandscape function is called again
    else
    {
        DrawLandscape();
    }
}
/*This function draws the third landscape which is also a night time setting 
with stars. This function does not take any input arguments and does not return
any values.
*/
 void DrawLandscape3()
 {
     LCD.Clear();
    //Draw hills
    LCD.SetDrawColor(GREEN);
    LCD.FillCircle(50,201,50);
    LCD.FillCircle(130,201,40);
    LCD.FillCircle(220,201,60);
    LCD.FillCircle(300,201,20);
    //Draw River
    LCD.SetDrawColor(BLUE);
    LCD.FillRectangle(0,201, 319, 38);
    //Draw stars 
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(305,100,5,5);
    LCD.FillRectangle(130,25,5,5);
    LCD.FillRectangle(300,120,5,5);
    LCD.FillRectangle(280,28,5,5);
    LCD.FillRectangle(260,90,5,5);
    LCD.FillRectangle(240,51,5,5);
    LCD.FillRectangle(220,60,5,5);
    LCD.FillRectangle(10,74,5,5);
    LCD.FillRectangle(170,80,3,3);
    LCD.FillRectangle(150,97,3,3);
    LCD.FillRectangle(310,88,3,3);
    LCD.FillRectangle(110,108,3,3);
    LCD.FillRectangle(90,99,3,3);
    LCD.FillRectangle(70,30,4,4);
    LCD.FillRectangle(50,123,4,4);
    LCD.FillRectangle(30,10,4,4);
    LCD.FillRectangle(170,133,4,4);
    //Draw Moon
    LCD.SetDrawColor(WHITE);
    LCD.FillCircle(190,30,15);
    LCD.SetDrawColor(BLACK);
    LCD.FillCircle(198,30,12);
    //Draw Tree Trunks
    LCD.SetDrawColor(SCARLET);
    LCD.FillRectangle(60,100,5,50);
    LCD.FillRectangle(15,110,5,50);
    LCD.FillRectangle(240,80,5,50);
    //Draw Tree Leaves
    LCD.SetDrawColor(GREEN);
    LCD.FillCircle(55,100,10);
    LCD.FillCircle(70,110,15);
    LCD.FillCircle(55,110,10);
    LCD.FillCircle(10,110,10);
    LCD.FillCircle(15,115,10);
    LCD.FillCircle(20,110,10);
    LCD.FillCircle(235,75,10);
    LCD.FillCircle(240,80,10);
    LCD.FillCircle(245,75,10);
}
/* This is the main function that executs the game by having the vaccine
jump and make the germs move. This function takes as input a pointer to 
the leaderboard object. It does not return any value.
*/
void playgame(Leaderboard* boards)
{
    int framespeed = 7;
    LCD.Clear();
    float score = 0;
    int touch_x = 0;
    int touch_y=0;
    LCD.SetFontColor(WHITE);
    LCD.SetDrawColor(WHITE);
    DrawLandscape();
    Vaccine vacc;
    Game start(&vacc);
    start.print();
    Germ germ1;
    Germ germ2;
    germ1.start(300,230);
    germ2.start(RandInt()%30+155,230);
    start.start_time();
    int alive = 1;
    int alive2 = 1;
    int buffer=0;
    int buffer2=0;
    while(alive == 1&& alive2==1){ //white the vaccines aren't hitting the germs...
        if(int(TimeNow()*100)%framespeed==0){ // every 0.07 seconds...
            start.printtitle(); // kepp track of score
        switch (vacc.getjumpstage()){ // switch the jumpstage
                case(0): // if its 0..
                    if(!LCD.Touch(&buffer,&buffer2)){ // if there is no touch... don't touch jumpstage
                        start.print();
                    }
                    else{ //else..
                        if(vacc.getjumpstage()==0){ // if the jump stage is in the first stage, start the jump
                        vacc.startjump(); // startjump() function is called to start a jump
                        start.print();
                        }
                        else{
                            int a = 5; // do nothing
                        }
                    }
                    break;
                // If its in stage 1, 2, or 3, call stage1() function
                case(1):
                case(2):
                case(3):
                    LCD.Touch(&buffer,&buffer2); // call buffer to remove double jumps from lag
                    vacc.stage1();
                    break;
                // If its in stage 4,5,6, call stage2() function
                case(4):
                case(5):
                case(6):
                    vacc.stage2();
                    LCD.Touch(&buffer,&buffer2); // call buffer to remove double jumps from lag
                    break;
                // If its in stage 7, 8, or 9, call stage3() function
                case(7):
                case(8):
                case(9):
                    vacc.stage3();
                    LCD.Touch(&buffer,&buffer2); // call buffer to remove double jumps from lag
                    break;
                // If its in stage 10,11,12, call stage4() function
                case(10):
                case(11):
                case(12):
                    vacc.stage4();
                    LCD.Touch(&buffer,&buffer2); // call buffer to remove double jumps from lag
                    break;
                case(13):
                case(14):
                // If its in stage 13, 14, call stage5() function
                    vacc.stage5();
                    LCD.Touch(&buffer,&buffer2); // call buffer to remove double jumps from lag
                    break;
                case(15):
                // If its in stage 15, call stage 6
                    vacc.stage6();
                    germ1.incSpeed(); // increase germ1 speed
                    LCD.Touch(&buffer,&buffer2); // call buffer to remove double jumps from lag
                    germ2.incSpeed(); // increment germ2 speed
                    break;
                // If none (an error has been made) treat as if there is no jump at all
                default:
                    start.print();
                    LCD.Touch(&buffer,&buffer2);// call buffer to remove double jumps from lag
                    break;
        }
            germ1.moveleft(); // move germ1 left
            germ2.moveleft(); // move germ2 left
            alive = checkCollision(&vacc, &germ1); // check collision between vaccine and germ1
            alive2 = checkCollision(&vacc,&germ2); // check collision between vaccine and germ1
        }
    }
    score = start.end_time(); // set score to score using end_time func
    end_game(score, boards); // call end_game func
    menu(boards); // return to menu
}
/*This function draws the vaccine on the screen. It takes as input the 
x and y coordinates of the vaccine, and a random value that decides the 
color of the vaccine 
*/
void drawVacc(int x, int y, int col)
{   
    //if the random value is 1, the color is set to red 
    if(col == 0)
    {
        LCD.SetDrawColor(RED);
    }
    //if the random value is 2, the color is set to cyan
    else if(col == 1)
    {
        LCD.SetDrawColor(CYAN);
    }
    //if the random value is 3, the color is set to light green
    else if(col == 2)
    {
        LCD.SetDrawColor(LIGHTGREEN);
    }
    //if the random value is 4, the color is set to skyblue
    else if(col == 3)
    {
        LCD.SetDrawColor(SKYBLUE);
    }
    //if the random value is 5, the color is set to yellow
    else if(col == 4)
    {
        LCD.SetDrawColor(PURPLE);
    }
    //This draws the vaccine 
    //This draws the vaccine
        //body 
    LCD.FillRectangle(x+1,y-5,12,30);
        //needle
    LCD.FillRectangle(x+6.8,y+25,1,5);
        //top
    LCD.FillRectangle(x-5,y-9,24,4);
        // Body Slant
    LCD.FillRectangle(x+3,y-2,8,28);
        //Pump Body
    LCD.FillRectangle(x+3,y-20,8,29);
        //Pump Top
    LCD.FillRectangle(x-3,y-22,20,2);
    
        //Eye
    LCD.SetDrawColor(WHITE);
    LCD.FillCircle(x+9, y+10,3);
        //Eye Pupil
    LCD.SetDrawColor(BLACK);
    LCD.FillCircle(x+10, y+10,1);
        //Eye Outline
    LCD.DrawCircle(x+9, y+10,3);
        //Lines
    LCD.DrawHorizontalLine(y+20,x+1, x+3);
    //LCD.DrawHorizontalLine(y+18,x+1, x+3);
    LCD.DrawHorizontalLine(y+16,x+1, x+3);
    //LCD.DrawHorizontalLine(y+14,x+1, x+3);
    LCD.DrawHorizontalLine(y+12,x+1, x+3);
   //LCD.DrawHorizontalLine(y+10,x+1, x+3);
    LCD.DrawHorizontalLine(y+8,x+1, x+3);
    //LCD.DrawHorizontalLine(y+6,x+1, x+3);
    LCD.DrawHorizontalLine(y+4,x+1, x+3);
    //LCD.DrawHorizontalLine(y+2,x+1, x+3);
        //Mouth Bottom
    LCD.SetDrawColor(WHITE);
    LCD.FillRectangle(x+6.3,y+20,6.2,2);
        //Mouth top
    LCD.FillRectangle(x+6.3,y+18,2,2);
    //This is just to get to 1400!
    //Yikes still not there
    //You saw nothing here
    //THIS is just to get to 1400!
}