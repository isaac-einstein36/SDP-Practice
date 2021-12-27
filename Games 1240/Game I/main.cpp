//Include headers
#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHSD.h"
#include "FEHUtility.h"
#include "LCDColors.h"
#include <windows.h>
#include <iostream>
#include <math.h>

//Using namespace
using namespace std;

//Define constants
#define YMAX 239.0
#define BUTTON1TEXT "Play Game"
#define BUTTON2TEXT "Display Statistics"
#define BUTTON3TEXT "Display Instructions"
#define BUTTON4TEXT "Display Credits"
#define BRUTUSY 104

//Function protoypes
void dispHome();
void dispInstruct();
void dispCredits();
void dispBrutus(int x,int y);
void fightsong();

//Game class to store member functions and variables for gameplay - Lily
//Public members are any functions related to actual gameplay
//Private members are all variables associated with gameplay
class gameplay{
    public:
        //Constructor
        gameplay();
        //Play the game from beginning
        int Play();
        //Display level screen
        void dispLevel(int a);
        //Display gameplay screen
        void dispGame(int a);
        //Display ending screen
        void dispEnd(int a);
        //Create functions for each shape
        void scooters(int x, int y, int z);
        void cars(int x, int y, int z);
        void fans(int x, int y, int z);
        void leaf(int x, int y);
        //Obtain time within gameplay
        int getTime();
        //Obtain which run/player is playing
        int getPlayer();
    private:
        int time;
        int brutusx;
        int obstaclesy[4][4];
        int obstaclesx[4];
};

//Constructor that initalizes gameplay values - Connor
gameplay::gameplay(){
    brutusx=1;
    time=0;
    for(int i=0; i<4; i++){
        //Each obstacle will be in 1 of 4 columns
        obstaclesx[i]=i*64+33;
        for(int j=0; j<4; j++){
            //Each obstacles will be in 1 of 4 rows
            obstaclesy[i][j]=j*60;
        }
    }
}

//Function to play the game from the beginning stage and go through appropriate functions - Daniel
//Returns the total time it takes to complete the game
int gameplay::Play()
{
    //Declare variables
    int levelindex=1, totaltime;
    int starttimes[3], endtimes[3];
    //Clear the screen
    LCD.Clear();
    for (int i=0; i<3; i++) {
        //Display level screen
        dispLevel(levelindex);
        //Keeping track of start time for each level
        starttimes[i]=(int) TimeNow();
        //Display gameplay screen
        dispGame(levelindex);
        //Keeping track of end time for each level
        endtimes[i]=(int) TimeNow();
        //Display end screen for each stage
        dispEnd(levelindex);
        //Increment the level index
        levelindex++;
    }
    //Clear screen
    LCD.Clear();
    totaltime=endtimes[0]-starttimes[0]+endtimes[1]-starttimes[1]+endtimes[2]-starttimes[2];
    return totaltime;
}

//Function to display level screen before start of each stage - Connor
void gameplay::dispLevel(int levelindex){
    //Clear screen
    LCD.Clear();
    int x=0, y=0;
    //While the screen hasn't been clicked
    while(!LCD.Touch(&x,&y)){
        LCD.SetDrawColor(LCD.White);
        //Writing the starting screen for each level "Level 1"
        LCD.WriteAt("Level ", 50, 65);
        LCD.WriteAt(levelindex, 100, 65);
        switch(levelindex){
            //Display description of setting based on what level you're on
            case 1:
                LCD.WriteAt("Crossing High Street", 50,130);
                LCD.WriteAt("Look out for cars", 50, 160);
                break;
            case 2:
                LCD.WriteAt("Crossing the Oval",50, 130);
                LCD.WriteAt("Look out for scooters", 50, 160);
                break;
            default:
                LCD.WriteAt("Crossing the Parking Lot", 50, 130);
                LCD.WriteAt("Look out for Xichigan fans",50,160);
        }
    }
}

//Function to display end screen after each stage - Daniel
void gameplay::dispEnd(int levelindex) {
    //Clear the screen
    LCD.Clear();
    int x=0,y=0;
    //While the screen hasn't been clicked
    while(!LCD.Touch(&x,&y)){
        LCD.SetDrawColor(LCD.White);
        switch(levelindex){
            //Display end based on stage completed
            case 1:
                LCD.WriteAt("Great job, you crossed High Street", 50,90);
                LCD.WriteAt("and avoided the cars", 50, 120);
                break;
            case 2:
                LCD.WriteAt("Fantastic job, you crossed the Oval",50, 90);
                LCD.WriteAt("and avoided the scooters", 50, 120);
                break;
            default:
                LCD.WriteAt("Outstanding work, you got Brutus", 50, 90);
                LCD.WriteAt("to the stadium on time",50,120);
        }
    }
    //Play fight song
    if (levelindex==3)
        fightsong();
}

//Function to actually play the game for each stage - Everyone
//Involves testing for movement and collisions on objects
void gameplay::dispGame(int levelindex) {
    //Define variables
    int x, y, i, j, k=0,f,g,sound;
    brutusx=1,sound=1;
    //Make screen white and add ending buckeye leaves
    LCD.SetDrawColor(LCD.White);
    LCD.FillRectangle(0,0,320,240);
    for(j=0; j<240; j=j+30) {
        i=289;
        leaf(i,j);
    }
    //Define variable
    i=0;
    while(brutusx<289) {
        //Display Brutus
        dispBrutus(brutusx,BRUTUSY);
        //Check if obstacles need to reset
        switch (levelindex) {
            case 1:
                f=15;
                g=26;
                break;
            case 2:
                f=3;
                g=25;
                break;
            default:
                f=6;
                g=19;
        }
        //Define variable
        j=3;
        //Check for reset
        if (obstaclesy[i][j]+f+k<238) {
            //Spawn all obstacles on column
            for(j=0; j<4; j++) {
                switch (levelindex) {
                    case 1:
                        //Moving cars
                        cars(i,j,k);
                        break;
                    case 2:
                        //Moving scooters
                        scooters(i,j,k);
                        break;
                    default:
                        //Moving Xichigan fans
                        fans(i,j,k);
                }
            }
        }
        //Reset k if needed
        else {
            k=0;
        }

        //Difficulty adjuster
        switch (levelindex) { 
            case 1:
                Sleep(0.5);
                break;
            case 2:
                Sleep(0.25);
        }

        //Move Brutus forwards, or backwards
        if(LCD.Touch(&x,&y)) {
            //Backwards
            if ((obstaclesy[i][1]+f+k>104&&obstaclesy[i][1]+f+k<134)||(obstaclesy[i][1]+g+k>104&&obstaclesy[i][1]+g+k<134)) {
                i=0;
                brutusx=1;
                //Play sound
                Sleep(.01);
                Beep(293.66,500);
                Sleep(.01);
                Beep(277.18,500);
                Sleep(.01);
                Beep(261.63,500);
                Sleep(.01);
                Beep(246.94,250);
                Sleep(.01);
                Beep(233.08,250);
                Sleep(.01);
                Beep(246.94,250);
                Sleep(.01);
                Beep(233.08,250);
                Sleep(.01);
                Beep(246.94,500);
                Sleep(.01);
                //Reset sound counter
                sound=1;
            }
            //Forwards
            else {
                LCD.SetDrawColor(LCD.White);
                LCD.FillRectangle(brutusx,104,32,30);
                brutusx+=32;
                dispBrutus(brutusx,BRUTUSY);
                //Play sound
                switch (sound) {
                    case 1:
                        Sleep(.01);
                        Beep(261.63,250);
                        Sleep(.01);
                        break;
                    case 2:
                        Sleep(.01);
                        Beep(329.63,250);
                        Sleep(.01);
                        break;
                    case 3:
                        Sleep(.01);
                        Beep(392,250);
                        Sleep(.01);
                        break;
                    default:
                        Sleep(.01);
                        Beep(523.25,250);
                        Sleep(.01);
                }
                //Check for movement to next obstacle column
                while(!LCD.Touch(&x,&y)) {
                }
                LCD.SetDrawColor(LCD.White);
                LCD.FillRectangle(brutusx,104,32,30);
                brutusx+=32;
                i++;
                sound++;
            }
        }
        //Clear partial screen
        if (brutusx<257) {
            LCD.SetDrawColor(LCD.White);
            LCD.FillRectangle(obstaclesx[i],0,289-obstaclesx[i],240);
            k+=7;
        }
        //Right before Brutus hits leaves
        if (brutusx==257) {
            dispBrutus(brutusx,BRUTUSY);
            while (!LCD.Touch(&x,&y)) {
            }
            LCD.SetDrawColor(LCD.White);
            LCD.FillRectangle(brutusx,104,32,30);
            brutusx+=32;
            dispBrutus(brutusx,BRUTUSY);
            //Play sound
            Sleep(.01);
            Beep(261.63,250);
            Sleep(.01);
            Beep(261.63,250);
            Sleep(.01);
            Beep(392,250);
            Sleep(.01);
            Beep(523.25,500);
            Sleep(.01);
            Beep(392,250);
            Sleep(.01);
            Beep(523.25,750);
            Sleep(.01);
        }
    }
}

//Function to create moving scooters on gameplay screen - Lily
void gameplay::scooters(int i, int j, int k) {
        LCD.SetDrawColor(LCD.Black);
        LCD.FillCircle(obstaclesx[i]+8,obstaclesy[i][j]+25+k,2);
        LCD.FillCircle(obstaclesx[i]+24,obstaclesy[i][j]+25+k,2);
        LCD.FillRectangle(obstaclesx[i]+5,obstaclesy[i][j]+4+k,2,17);
        LCD.FillRectangle(obstaclesx[i]+3,obstaclesy[i][j]+3+k,6,1);

        LCD.SetDrawColor(LCD.Green);
        LCD.FillRectangle(obstaclesx[i]+5,obstaclesy[i][j]+21+k,22,2);
        LCD.FillRectangle(obstaclesx[i]+1,obstaclesy[i][j]+3+k,2,1);
        LCD.FillRectangle(obstaclesx[i]+9,obstaclesy[i][j]+3+k,2,1);
}

//Function to create moving cars on gameplay screen - Lily
void gameplay::cars(int i, int j, int k) {
        LCD.SetDrawColor(LCD.Red);
        LCD.FillCircle(obstaclesx[i]+17,obstaclesy[i][j]+15+k,8);
        LCD.FillRectangle(obstaclesx[i]+4,obstaclesy[i][j]+15+k,24,7);

        LCD.SetDrawColor(LCD.Gray);
        LCD.FillRectangle(obstaclesx[i]+3,obstaclesy[i][j]+22+k,26,2);

        LCD.SetDrawColor(LCD.Black);
        LCD.FillCircle(obstaclesx[i]+8,obstaclesy[i][j]+26+k,3);
        LCD.FillCircle(obstaclesx[i]+24,obstaclesy[i][j]+26+k,3);

        LCD.SetDrawColor(LCD.Gray);
        LCD.FillCircle(obstaclesx[i]+5,obstaclesy[i][j]+16+k,1);
}

//Function to create moving Xichigan fans on gameplay screen - Lily
void gameplay::fans(int i, int j, int k) {
        LCD.SetDrawColor(LCD.Blue);
        LCD.FillRectangle(obstaclesx[i]+2,obstaclesy[i][j]+6+k,8,5);
        LCD.FillRectangle(obstaclesx[i]+4,obstaclesy[i][j]+11+k,6,8);
        LCD.FillRectangle(obstaclesx[i]+2,obstaclesy[i][j]+19+k,10,5);
        LCD.FillRectangle(obstaclesx[i]+20,obstaclesy[i][j]+6+k,8,5);
        LCD.FillRectangle(obstaclesx[i]+20,obstaclesy[i][j]+11+k,6,8);
        LCD.FillRectangle(obstaclesx[i]+18,obstaclesy[i][j]+19+k,10,5);

        LCD.FillRectangle(obstaclesx[i]+10,obstaclesy[i][j]+6+k,1,9);
        LCD.FillRectangle(obstaclesx[i]+11,obstaclesy[i][j]+8+k,1,9);
        LCD.FillRectangle(obstaclesx[i]+12,obstaclesy[i][j]+10+k,1,8);
        LCD.FillRectangle(obstaclesx[i]+13,obstaclesy[i][j]+11+k,1,8);
        LCD.FillRectangle(obstaclesx[i]+14,obstaclesy[i][j]+12+k,2,8);

        LCD.FillRectangle(obstaclesx[i]+16,obstaclesy[i][j]+11+k,1,8);
        LCD.FillRectangle(obstaclesx[i]+17,obstaclesy[i][j]+10+k,1,8);
        LCD.FillRectangle(obstaclesx[i]+18,obstaclesy[i][j]+8+k,1,9);
        LCD.FillRectangle(obstaclesx[i]+19,obstaclesy[i][j]+6+k,1,9);
}

//Function to create leaf column at end of each level - Lily 
void gameplay::leaf(int i, int j) {
    LCD.SetDrawColor(FORESTGREEN);
    LCD.FillCircle(i+14,j+16,2);
    LCD.DrawRectangle(i+13,j+18,1,8);

    LCD.DrawRectangle(i+15,j+17,7,1);
    LCD.DrawRectangle(i+16,j+18,7,1);
    LCD.DrawRectangle(i+17,j+19,7,1);
    LCD.DrawRectangle(i+18,j+20,7,1);

    LCD.DrawRectangle(i+16,j+15,6,1);
    LCD.DrawRectangle(i+17,j+14,6,1);
    LCD.DrawRectangle(i+18,j+13,6,1);
    LCD.DrawRectangle(i+20,j+12,5,1);
    LCD.DrawRectangle(i+21,j+11,6,1);
    LCD.DrawRectangle(i+22,j+10,4,1);

    LCD.DrawRectangle(i+14,j+8,1,6);
    LCD.DrawRectangle(i+15,j+7,1,7);
    LCD.DrawRectangle(i+16,j+6,1,7);
    LCD.DrawRectangle(i+17,j+5,1,7);
    LCD.DrawRectangle(i+18,j+4,1,8);
    LCD.DrawRectangle(i+19,j+3,1,8);
    LCD.DrawRectangle(i+20,j+2,1,8);

    LCD.DrawRectangle(i+7,j+5,1,4);
    LCD.DrawRectangle(i+8,j+3,1,7);
    LCD.DrawRectangle(i+9,j+3,1,8);
    LCD.DrawRectangle(i+10,j+4,1,8);
    LCD.DrawRectangle(i+11,j+5,1,8);
    LCD.DrawRectangle(i+12,j+7,1,7);

    LCD.DrawRectangle(i+3,j+12,6,1);
    LCD.DrawRectangle(i+4,j+13,6,1);
    LCD.DrawRectangle(i+5,j+14,6,1);
    LCD.DrawRectangle(i+6,j+15,7,2);

    LCD.SetDrawColor(BROWN);
    LCD.FillCircle(i+11,j+24,2);
}

//Function to create Brutus character to move across screen - Lily 
void dispBrutus(int x, int y){
    LCD.SetDrawColor(BROWN);
    LCD.FillCircle(x+15,y+15,12);

    LCD.SetDrawColor(YELLOW);
    LCD.FillCircle(x+15,y+15,9);

    LCD.SetDrawColor(BROWN);
    LCD.FillCircle(x+15,x+15,1);

    LCD.SetDrawColor(LCD.White);
    LCD.FillCircle(x+12,y+11,2);
    LCD.FillCircle(x+18,y+11,2);

    LCD.SetDrawColor(LCD.Black);
    LCD.FillCircle(x+12,y+11,1);
    LCD.FillCircle(x+18,y+11,1);

    LCD.SetDrawColor(LCD.Red);
    LCD.DrawLine(x+12,y+18,x+18,y+18);
    LCD.DrawLine(x+12,y+18,x+15,y+20);
    LCD.DrawLine(x+18,y+18,x+15,y+20);
    LCD.DrawPixel(x+14,y+19);
    LCD.DrawPixel(x+15,y+19);
    LCD.DrawPixel(x+16,y+19);

}

//Statistics class allowing for easy manuervability in leaderboard - Connor
//Public members are any functions related to the leaderboard
//Private members are arrays to display on the leaderboard
class statistics{
    public:
        statistics(int t[], int p[]);
        //Display the leaderboard
        void dispBoard();
        //Add a time to the fastest times
        void addTime(int p, int t);
    private:
        //Array for top 5 fastest times
        int toptimes[5];
        //Array for index of player for each fastest time
        int playernums[5];
};

//Constructor that initializes values for the statistics - Connor
statistics::statistics(int t[], int p[]){
    for(int i=0;i<5;i++){
        toptimes[i]=t[i];
        playernums[i]=p[i];
    }
}

//Function that displays the leaderboard and statistics - Connor
void statistics::dispBoard(){
    int x,y,k=0, countplayers=0;
    //Clear the screen
    LCD.Clear();
    //Display Credits
    LCD.SetDrawColor(LCD.White);
    //Finding how many player runs have occured and storing in countplayers
    if(toptimes[0]==3600)
        countplayers=0;
    else if(toptimes[1]==3600)
        countplayers=1;
    else if(toptimes[2]==3600)
        countplayers=2;
    else if(toptimes[3]==3600)
        countplayers=3;
    else if(toptimes[4]==3600)
        countplayers=4;
    else
        countplayers=5;
    //Loop to remain in the function until back button is clicked
    while(k==0){
        //Prints if nobody has played the game yet
        if(countplayers==0){
            LCD.WriteAt("No Statistics to show yet :(", 50, 50);
            LCD.WriteAt("Play the game to add some", 50, 80);
        }
        //If the game has been played at least once
        else{
            LCD.WriteAt("Leaderboard", 120, 5);
            //Horizontal lines
            LCD.DrawLine(0,50,319,50);
            LCD.DrawLine(40, 82,319,82);
            LCD.DrawLine(40,113,319,113);
            LCD.DrawLine(40,145,319,145);
            LCD.DrawLine(40,177,319,177);
            LCD.DrawLine(40,208,319,208);
            //Vertical lines
            LCD.DrawLine(40,50,40,239);
            LCD.DrawLine(133,50,133,239);
            LCD.DrawLine(226,50,226,239);
            //Labels
            LCD.WriteAt("Place", 45, 55);
            LCD.WriteAt("Time (s)", 138, 55);
            LCD.WriteAt("Player", 231, 55);
            LCD.WriteAt("1st", 45, 87 );
            LCD.WriteAt("2nd", 45, 118 );
            LCD.WriteAt("3rd", 45, 148 );
            LCD.WriteAt("4th", 45,  182);
            LCD.WriteAt("5th", 45, 213);
            //Prints times and player number for top 5 times
            //Prints fewer than 5 times if game has been played less than 5 times
            for(int i=0; i< countplayers; i++){
                LCD.WriteAt(toptimes[i],138,i*31+87);
                LCD.WriteAt(playernums[i],231,i*31+87);
            }
        }
        //Back button
        LCD.DrawRectangle(0,200,40,39);
        LCD.WriteAt("Back", 1, 215);
        if(LCD.Touch(&x,&y)){
           if(x<=40 && y>=200){
                k=1;
            }
        }
    }
    LCD.Clear();
}

//Function to add a time to (possibly) be displayed on the leaderboard - Connor
//Involves swapping times if needed
void statistics::addTime(int p, int t){
    int temptime=0;
    int tempplayer=0;
    //Putting t and p into 5th spot on leaderboard if necessary
    if(t<toptimes[4]){
        toptimes[4]=t;
        playernums[4]=p;
    }
    //Sorting list of top times
    for(int i=4;i>0;i--){
        //Checking if times need to be swapped
        if(toptimes[i]<toptimes[i-1]){
            //Swapping times
            temptime=toptimes[i-1];
            toptimes[i-1]=toptimes[i];
            toptimes[i]=temptime;
            //Swapping player numbers
            tempplayer=playernums[i-1];
            playernums[i-1]=playernums[i];
            playernums[i]=tempplayer;
        }
    }
}

//Int main function to actually run through code - Everyone
//Returns 0 at the end
int main() {
    //Create arrays for leaderboard and setting times to 3600 seconds 
    int times[5]={3600,3600,3600,3600,3600}, players[5]={0,0,0,0,0};
    //Declare variables
    int x=0, y=0;
    int player=0;
    int time=0;
    //Declare objects
    statistics Stats(times,players);
    gameplay Game;
    //Run until simulator is closed
    while (1) {
        //Display menu screen
        dispHome();
        //when the simulator is clicked
        if(LCD.Touch(&x,&y)){
            //If click is in top 1/4 of screen play the game
            if(y<YMAX/4){
                player++;
                time=Game.Play();
                Stats.addTime(player,time);
            }
            //If click is second highest 1/4 of screen show leaderboard
            else if( y<YMAX/2 && y>=YMAX/4 )  
                Stats.dispBoard();

            //If click is in third highest 1/4 of screen show instructions
            else if( y<YMAX*3.0/4.0 && y>=YMAX/2 )
                dispInstruct();
            //If click is in bottom 1/4 of screen show credits
            else
                dispCredits();
        }
    }
    return 0;
}

//Function to display the menu with all the possible options - Daniel
void dispHome()
{
    LCD.SetDrawColor(LCD.White);
    LCD.DrawHorizontalLine(YMAX/4,0,319);
    LCD.DrawHorizontalLine(2*YMAX/4,0,319);
    LCD.DrawHorizontalLine(3*YMAX/4,0,319);
    LCD.WriteAt(BUTTON1TEXT,130,30);
    LCD.WriteAt(BUTTON2TEXT,130,90);
    LCD.WriteAt(BUTTON3TEXT,130,150);
    LCD.WriteAt(BUTTON4TEXT,130,210);
}

//Function to display the instructions for the game - Daniel
void dispInstruct()
{
    //Clear the screen
    LCD.Clear();
    //Declare variables
    int x,y,k=0;
    //Loop to remain in function until back button is clicked
    while (k==0) {
        //Display instructions
        LCD.SetDrawColor(LCD.White);
        LCD.WriteAt("You must get to the Horseshoe",1,25);
        LCD.WriteAt("There are three stages to the game",1,50);
        LCD.WriteAt("Click to the right and avoid the objects",1,75);
        LCD.WriteAt("Hit an object, back to start of stage",1,100);
        LCD.WriteAt("New stages appear with harder obstacles",1,125);
        LCD.WriteAt("At the end your time will be recorded",1,150);
        LCD.WriteAt("Times are stored in the leaderboard",1,175);
        LCD.WriteAt("Don't get mad, and Go Bucks",1,200);
        LCD.DrawRectangle(279,200,40,39);
        LCD.WriteAt("Back",280,213);
        if(LCD.Touch(&x,&y)){
            //Check if the rectangle is touched
            if (x>=279 && y>=200){
                k=1;
            }
        }
    }
    //Clear the screeen
    LCD.Clear();
}

//Function to display the credits for the game - Lily
void dispCredits()
{
    int x,y,k=0;
    //Clear the screen
    LCD.Clear();
    //Display Credits
    LCD.SetDrawColor(LCD.White);
    //Loop to remain in the function until back button is clicked
    while(k==0){
        LCD.WriteAt("Brought to you by the developers: ",10,10);
        LCD.WriteAt("Lily Aaberg",10,40);
        LCD.WriteAt("Connor Halford",10,70);
        LCD.WriteAt("and Daniel Rose",10,100);
        LCD.WriteAt("From FEH at The Ohio State University",10,130);
        LCD.WriteAt("With inspiration from Komani and Sony",10,160);
        //Display back button
        LCD.DrawRectangle(0,200,40,39);
        LCD.WriteAt("Back", 1, 213);
        if(LCD.Touch(&x,&y)){
            if(x<=40 && y>=200) {
                k=1;
            }
        }
    }
    //Clear screen
    LCD.Clear();
}

//Function to play the fight song - Daniel
void fightsong()
{
    Sleep(.01);
    Beep(466.16,500);
    Sleep(.01);
    Beep(440,250);
    Sleep(.01);
    Beep(466.16,500);
    Sleep(.01);
    Beep(440,250);
    Sleep(.01);
    Beep(466.16,500);
    Sleep(.01);
    Beep(440,250);
    Sleep(.01);
    Beep(392,250);
    Sleep(.01);
    Beep(466.16,250);
    Sleep(.01);
    Beep(440,500);
    Sleep(.01);
    Beep(415.3,250);
    Sleep(.01);
    Beep(440,500);
    Sleep(.01);
    Beep(415.3,250);
    Sleep(.01);
    Beep(440,750);
    Sleep(.01);
}

//References: Frogger created by Komani and Sony
//FEH Proteus Simulator Docs
//APP B38-Overview
//APPs B38-1 through B38-4