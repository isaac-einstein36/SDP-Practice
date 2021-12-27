#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHUtility.h"

//function prototypes
void DrawBackground();
void mainmenu();
int statistics(int, int, int, int);
void credits();
void instructions();
int backbutton();
float difficultymenu(float);
int drawLight(int[]);
int fillLight(int[]);
void randLight(int * );
int ornament(float, int);

int main() 
{
//declare integer variables 
int x, y, i, TotalPoints = 0, TotalGames = 0, HighScore = 0;
int q=0;
int goagain = 1;
int alltimepoints = 0;
//declare float variables 
float difficulty = 0.0, t_round;

//Title Screen
LCD.Clear(FORESTGREEN);
LCD.SetDrawColor(RED);
LCD.DrawRectangle(40, 40, 240, 150);
LCD.FillRectangle(40, 40, 240, 150);
LCD.SetDrawColor(WHITE);
LCD.DrawRectangle(77, 80, 166, 70);
LCD.FillRectangle(77, 80, 166, 70);
LCD.SetDrawColor(FORESTGREEN);
LCD.DrawRectangle(77, 80, 166, 70);
LCD.SetFontColor(FORESTGREEN);
LCD.WriteAt("Click'n Round ", 110, 90);
LCD.WriteAt("The Christmas Tree!", 80, 120);
Sleep(2.01);
LCD.Clear();
//use a while loop to take make the screen the main menu 
while(goagain == 1){
mainmenu();
 while (!LCD.Touch(&x, &y))
    {
    }
    //play game when the user clickes the button
    if(y<=59){
        //set the difficulty
        difficulty = difficultymenu(difficulty);
        //call the darw backfround function
        DrawBackground();
        //increments total games played by one
        TotalGames++;
        //displays total points earned throughout game
        LCD.WriteAt("Total Points:", 0, 0);
        LCD.WriteAt(TotalPoints, 0, 20);
        //loop for round mechanism in game 
        for(i = 1; i <= 14; i++)
            {
            int loc[6], oof;
            int g=0;
            //set functions to generate lights
            randLight(loc);
            g=drawLight(loc);
            //Draw two rectangles in the sky so that total points and "oof" can be written without text overlapping itself
            LCD.SetDrawColor(SKYBLUE);
            LCD.FillRectangle(0, 0, 45, 38);
            LCD.FillRectangle(45, 0, 70, 20);
            LCD.DrawRectangle(250, 25, 60, 30);
            LCD.FillRectangle(250, 25, 60, 30);
            LCD.SetFontColor(RED);
            LCD.WriteAt("Total Points:", 0, 0);
            LCD.WriteAt(TotalPoints, 0, 20);
            //set time for the loops to reference
            t_round = TimeNow();
            while (TimeNow() - t_round <= difficulty) {
                //award points if the generated lights are clicked for light 1
                if (LCD.Touch(&x, &y)) {
                    if (x<loc[0]+5 && x>loc[0]-5 && y<loc[1]+5 && y>loc[1]-5) {
                                TotalPoints += 100;
                                LCD.SetDrawColor(SKYBLUE);
                                LCD.FillRectangle(0, 0, 45, 38);
                                LCD.FillRectangle(45, 0, 70, 20);
                                LCD.WriteAt("Total Points:", 0, 0);
                                LCD.WriteAt(TotalPoints, 0, 20);
                                LCD.SetDrawColor(FORESTGREEN);
                                LCD.DrawCircle(loc[0], loc[1], 5);
                                LCD.FillCircle(loc[0], loc[1], 5);
                                //remove the point click area from its original location
                                loc[0]=190;
                                loc[1]=10;
                    }
                    //repeat for light 2
                    if (x<loc[2]+5 && x>loc[2]-5 && y<loc[3]+5 && y>loc[3]-5) {
                            TotalPoints += 100;
                            LCD.SetDrawColor(SKYBLUE);
                            LCD.FillRectangle(0, 0, 45, 38);
                            LCD.FillRectangle(45, 0, 70, 20);
                            LCD.WriteAt("Total Points:", 0, 0);
                            LCD.WriteAt(TotalPoints, 0, 20);
                            LCD.SetDrawColor(FORESTGREEN);
                            LCD.DrawCircle(loc[2], loc[3], 5);
                            LCD.FillCircle(loc[2], loc[3], 5);
                            loc[2]=190;
                            loc[3]=10;
                    }
                    //repeat for light 3
                    if (x<loc[4]+5 && x>loc[4]-5 && y<loc[5]+5 && y>loc[5]-5) {
                        //check if the light is red. If so, subtract 50 points from the score
                        if (oof=g) {
                            TotalPoints -= 50;
                            //Draw "O o f!" in the sky if a red light is clicked
                            LCD.SetDrawColor(BLACK);
                            LCD.DrawRectangle(250, 25, 60, 30);
                            LCD.FillRectangle(250, 25, 60, 30);
                            LCD.SetFontColor(WHITE);
                            LCD.WriteAt("O o f !", 260, 30);
                            LCD.SetDrawColor(SKYBLUE);
                            LCD.FillRectangle(0, 0, 45, 38);
                            LCD.FillRectangle(45, 0, 70, 20);
                            LCD.SetFontColor(RED);
                            LCD.WriteAt("Total Points:", 0, 0);
                            LCD.WriteAt(TotalPoints, 0, 20);
                            LCD.SetDrawColor(FORESTGREEN);
                            LCD.DrawCircle(loc[4], loc[5], 5);
                            LCD.FillCircle(loc[4], loc[5], 5);
                            loc[4]=190;
                            loc[5]=10;
                        }
                        else {
                            //if light is not red, award 100 points if clicked
                            TotalPoints += 100;
                            LCD.SetDrawColor(SKYBLUE);
                            LCD.FillRectangle(0, 0, 45, 38);
                            LCD.FillRectangle(45, 0, 70, 20);
                            LCD.WriteAt("Total Points:", 0, 0);
                            LCD.WriteAt(TotalPoints, 0, 20);
                            LCD.SetDrawColor(FORESTGREEN);
                            LCD.DrawCircle(loc[4], loc[5], 5);
                            LCD.FillCircle(loc[4], loc[5], 5);
                            loc[4]=190;
                            loc[5]=10;
                        }
                    }
                }
            }
            LCD.SetDrawColor(SKYBLUE);
            LCD.DrawRectangle(250, 25, 60, 30);
            //fill the colored light spaces with green to make it seem like the lights disappear
            fillLight(loc);
            }
            //if on the final round, play the bonus round with falling ornaments
            if (i==15) {
                TotalPoints = ornament(difficulty, TotalPoints);
                //update high score if the total score of the last game was larger than the high score
                if (TotalPoints > HighScore && difficulty < 2.5) {
                    HighScore = TotalPoints;
                }
            }
            //write game over screen
            LCD.Clear(WHITE);
            LCD.SetDrawColor(RED);
            LCD.WriteAt("Game Over!", 106, 74);
            Sleep(2.0);
        //shows statistics
        y=61;
        alltimepoints += TotalPoints;
    }
    if(y<=119 && y>59){
        //shows statistics
        statistics(TotalPoints, TotalGames, alltimepoints, HighScore);
        //if backbutton is touched, take to main menu
        while(q==0)
        {
             while (!LCD.Touch(&x, &y))
            {
            }
            if(x<=60&&y<=40)
            {
                goagain=backbutton();
                q=1;
            }
        }
        
    }
        
    //show instruction when button is clicked
    if(y<=179 && y>119){
        //shows instructions
        instructions();
        //if backbutton is touched, brings to main 
         while(q==0)
        {
             while (!LCD.Touch(&x, &y))
            {
            }
            if(x<=60&&y<=40)
            {
                goagain=backbutton();
                q=1;
            }
        }
            
    }
    //show credits when button is clicked
    if(y>179){
        //show credits
        credits();
        // if backbutton is touched, brings to main
         while(q==0)
        {
             while (!LCD.Touch(&x, &y))
            {
            }
            if(x<=60&&y<=40)
            {
                goagain=backbutton();
                q=1;
            }
        }
        
    }
    q=0;
    TotalPoints=0;

}
}

void mainmenu(){
LCD.Clear(WHITE);
//divide main screen into 4 sections with lines
LCD.SetDrawColor(RED);
LCD.DrawHorizontalLine(59,0,319);
LCD.DrawHorizontalLine(119,0,319);
LCD.DrawHorizontalLine(179,0,319);
//write text to make the 4 sections into buttons
LCD.SetFontColor(RED);
LCD.WriteAt("Play Game Here!", 96, 29);
LCD.WriteAt("Show Statistics", 103 , 88);
LCD.WriteAt("Show Instructions", 92 , 148);
LCD.WriteAt("Credits", 132, 208);
}

int backbutton(){

    //store touch as x and y cordinates
   int goagain = 1;
    
return(goagain);
}

int statistics(int TotalPoints, int TotalGames, int alltimepoints, int HighScore){
    //Clear the screen
    LCD.Clear(WHITE);
    //set font color
    LCD.SetFontColor(RED);
    //draw back button
    LCD.DrawRectangle(0, 0, 60, 30);
    LCD.WriteAt("BACK", 10, 10);
    //show stats
    LCD.DrawRectangle(113, 7, 100, 20);
    LCD.WriteAt("MyCareer", 127, 10);
    LCD.WriteAt("Final Score: ", 80, 100);
    LCD.WriteAt(TotalPoints, 170, 100);
    LCD.WriteAt("High Score: ", 80, 120);
    LCD.WriteAt(HighScore, 170, 120);
    LCD.WriteAt("Total Points Earned: ", 80, 140);
    LCD.WriteAt(alltimepoints, 235, 140);
    LCD.WriteAt("Total games: ", 80, 160);
    LCD.WriteAt(TotalGames, 180, 160);
    
}

void instructions()
{
    //Clear the screen
    LCD.Clear(WHITE);
    //set font color
    LCD.SetFontColor(RED);
    //draw back button
    LCD.DrawRectangle(0, 0, 60, 34);
    LCD.WriteAt("BACK", 10, 10);
    // show instructions 
    LCD.DrawRectangle(105, 7, 105, 20);
    LCD.WriteAt("Instructions:", 113, 10);
    LCD.WriteAt("The goal is to earn points by clicking", 20, 50);
    LCD.WriteAt("on the lights that appear on the tree.", 35, 70);
    LCD.WriteAt("You will receive 100 points for clicking ", 20, 90);
    LCD.WriteAt("on a light.", 40, 110);
    LCD.WriteAt("DO NOT CLICK ON A RED LIGHT! ", 20, 130);
    LCD.WriteAt("You will lose 50 points for clicking ", 20, 150);
    LCD.WriteAt("on red lights.", 40, 170);
    LCD.WriteAt("Be sure to watch for falling ornaments", 20,190);
    LCD.WriteAt("which will give you 200 points!", 40, 210);

}

void credits()
{
LCD.Clear();
    //set font color
    LCD.SetFontColor(WHITE);
    //draw back button
    LCD.DrawRectangle(0, 0, 60, 30);
    LCD.WriteAt("BACK", 10, 10);
    //show credits 
    LCD.WriteAt("Created by:", 70, 80);
    LCD.WriteAt("Matt Richard", 100, 100);
    LCD.WriteAt("Isabella Marino", 100, 120);
    LCD.WriteAt("Kavya Subramanian", 100, 140); 
    LCD.WriteAt("Peter Salem", 100, 160);

}

float difficultymenu(float difficulty){
    int x, y;
    float chosendifficulty = 0;
    //clear screen to blue
    LCD.Clear(WHITE);
    //draw menu
    LCD.SetDrawColor(RED);
    LCD.DrawHorizontalLine(79,0,319);
    LCD.DrawHorizontalLine(159,0,319);
    LCD.SetFontColor(RED);
    LCD.DrawRectangle(80, 5, 160, 23);
    LCD.WriteAt("Select Difficulty:", 100, 10);
    LCD.WriteAt("Easy", 145, 50);
    LCD.WriteAt("Intermediate", 110, 115);
    LCD.WriteAt("Difficult (High Score)", 85, 190);
    //touch for selection
    while (!LCD.Touch(&x, &y))
    {
    }
    //easy button
    if(y <= 79 ){
        chosendifficulty = 3.45;
    }
    //intermediate button
    else if(y > 79 && y < 159){
        chosendifficulty = 2.90;
    }
    //hard button
    else{
        chosendifficulty = 2.35;
    }

    //return difficulty value 
    return(chosendifficulty);
}

void DrawBackground() 
{
// draw background
LCD.Clear(SKYBLUE);

// draw snowman
// 3 body circles
LCD.SetDrawColor(LCD.White);
LCD.FillCircle(300, 235, 15);
LCD.SetDrawColor(LCD.White);
LCD.FillCircle(300, 205, 11);
LCD.FillCircle(300, 190, 7);
// snowman eyes
LCD.SetDrawColor(LCD.Black);
LCD.FillCircle(302, 190, 2);
LCD.SetDrawColor(LCD.Black);
LCD.FillCircle(298, 190, 2);
//snowman buttons
LCD.SetDrawColor(LCD.Black);
LCD.FillCircle(300, 210, 3);
LCD.SetDrawColor(LCD.Black);
LCD.FillCircle(300, 220, 3);
//snowman arms
LCD.SetDrawColor(BROWN);
LCD.DrawLine(280, 220, 290 ,205);
LCD.DrawLine(317, 220, 307 ,205);

//draw tree
LCD.SetDrawColor(BROWN);
//stump
LCD.FillRectangle(150, 179, 20, 60);
LCD.SetDrawColor(FORESTGREEN);
//tree
LCD.FillRectangle(10, 149, 300, 30);
LCD.FillRectangle(30,119, 260, 30);
LCD.FillRectangle(50,89, 220, 30);
LCD.FillRectangle(70, 59, 180, 30);
LCD.FillRectangle(90,29, 140, 30);
LCD.FillRectangle(120,1, 80, 30);

//draw presents
//draw box
LCD.SetDrawColor(RED);
LCD.FillRectangle(41, 211, 30, 28);
//vertical stripe
LCD.SetDrawColor(FORESTGREEN);
LCD.FillRectangle(53, 211, 6, 28);
//horizontal stripe
LCD.FillRectangle(41, 222, 30, 6);

//draw box
LCD.SetDrawColor(PURPLE);
LCD.FillRectangle(72, 219, 48, 20);
//horizontal stripe
LCD.SetDrawColor(GRAY);
LCD.FillRectangle(72, 226, 48, 6);
//vertical stripe
LCD.FillRectangle(93, 219, 6, 20);

//draw box
LCD.SetDrawColor(YELLOW);
LCD.FillRectangle(21, 191, 18, 48);
//vertical stripe
LCD.SetDrawColor(WHITE);
LCD.FillRectangle(28, 191, 4, 48);
//horizontal stripe
LCD.FillRectangle(21, 213, 18, 4);

//draw box
LCD.SetDrawColor(BLUE);
LCD.FillRectangle(1, 219, 18, 20);
//vertical stripe
LCD.SetDrawColor(GREEN);
LCD.FillRectangle(8, 219, 4, 20);
//horizontal stripe
LCD.FillRectangle(1, 227, 18, 4);

//draw box
LCD.SetDrawColor(FORESTGREEN);
LCD.FillRectangle(122, 207, 40, 32);
//vertical stripe
LCD.SetDrawColor(YELLOW);
LCD.FillRectangle(139, 207, 6, 32);
//horizontal stripe
LCD.FillRectangle(122, 220, 40, 6);

//draw box
LCD.SetDrawColor(RED);
LCD.FillRectangle(164, 197, 30, 42);
//vertical stripe
LCD.SetDrawColor(WHITE);
LCD.FillRectangle(176, 197, 6, 42);
//horizontal stripe
LCD.FillRectangle(164, 215, 30, 6);

//draw box
LCD.SetDrawColor(WHITE);
LCD.FillRectangle(196, 215, 44, 24);
//vertical stripe
LCD.SetDrawColor(GREEN);
LCD.FillRectangle(215, 215, 6, 24);
//horizontal stripe
LCD.FillRectangle(196, 224, 44, 6);

//draw box
LCD.SetDrawColor(GRAY);
LCD.FillRectangle(242, 219, 16, 20);
//vertical stripe
LCD.SetDrawColor(PURPLE);
LCD.FillRectangle(248, 219, 4, 20);
//horizontal stripe
LCD.FillRectangle(242, 227, 16, 4);

//draw box
LCD.SetDrawColor(FORESTGREEN);
LCD.FillRectangle(260, 199, 18, 40);
//vertical stripe
LCD.SetDrawColor(RED);
LCD.FillRectangle(268, 199, 4, 40);
//horizontal stripe
LCD.FillRectangle(260, 217, 18, 4);

//draw star on top of tree
int a, b, c, d, e, f, g, h, i, j, k, l, m, n;
for (a=9; a<=25; a++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(160,a);

}
for (b=149; b<=172; b++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(b,16);   
}

for (c=154; c<=166; c++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(c,15);   
}

for (d=155; d<=165; d++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(d,14);   
}

for (e=156; e<=164; e++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(e,13);   
}

for (f=157; f<=163; f++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(f,12);   
}

for (g=158; g<=162; g++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(g,11);   
}

for (h=159; h<=161; h++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(h,10);   
}

for (i=150; i<=171; i++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(i,17);   
}

for (j=151; j<=170; j++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(j,18);   
}

for (k=152; k<=169; k++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(k,19);   
}

for (l=153; l<=168; l++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(l,20);   
}

for (m=154; m<=167; m++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(m,21);   
}

for (n=155; n<=166; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,22);   
}

n=0;
for (n=154; n<=167; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,23);   
}

n=0;
for (n=154; n<=167; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,24);   
}

n=0;
for (n=153; n<=168; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,25);   
}

n=0;
for (n=153; n<=158; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,26);   
}

n=0;
for (n=152; n<=157; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,27);   
}

n=0;
for (n=152; n<=156; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,28);   
}

n=0;
for (n=150; n<=155; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,29);   
}

n=0;
for (n=150; n<=154; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,30);   
}

n=0;
for (n=149; n<=153; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,31);   
}

n=0;
for (n=150; n<=152; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,32);   
}

n=0;
for (n=161; n<=168; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,26);   
}

n=0;
for (n=162; n<=169; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,27);   
}

n=0;
for (n=163; n<=169; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,28);   
}

n=0;
for (n=164; n<=170; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,29);   
}

n=0;
for (n=165; n<=170; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,30);   
}

n=0;
for (n=166; n<=170; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,31);   
}

n=0;
for (n=167; n<=169; n++)
{
LCD.SetDrawColor(YELLOW);
LCD.DrawPixel(n,32);   
}
}

void randLight(int * loc)
{
    //random number generated for the first light from 1-20
    int L1=0;
    L1=RandInt()%20;
    //this switch case is to decide the location of the first light
    switch (L1){
        case 0:
            loc[0]=134;
            loc[1]=15;
            break;
        case 1:
            loc[0]=66;
            loc[1]=102;
            break;
        case 2:
            loc[0]=116;
            loc[1]=69;
            break;
        case 3: 
            loc[0]=209;
            loc[1]=87;
            break;
        case 4:
            loc[0]=127;
            loc[1]=126;
            break;
        case 5:
            loc[0]=186;
            loc[1]=135;
            break;
        case 6:
            loc[0]=74;
            loc[1]=139;
            break;
        case 7: 
            loc[0]=30;
            loc[1]=165;
            break;
        case 8:
            loc[0]=115;
            loc[1]=162;
            break;
        case 9:
            loc[0]=173;
            loc[1]=161;
            break;
        case 10:
            loc[0]=158;
            loc[1]=95;
            break;
        case 11:
            loc[0]=178;
            loc[1]=13;
            break;
        case 12:
            loc[0]=151;
            loc[1]=44;
            break;
        case 13: 
            loc[0]=187;
            loc[1]=46;
            break;
        case 14:
            loc[0]=237;
            loc[1]=74;
            break;
        case 15:
            loc[0]=230;
            loc[1]=122;
            break;
        case 16:
            loc[0]=272;
            loc[1]=127;
            break;
        case 17: 
            loc[0]=228;
            loc[1]=151;
            break;
        case 18:
            loc[0]=273;
            loc[1]=163;
            break;
        case 19:
            loc[0]=72;
            loc[1]=168;
            break;
    }
    //initialize the second light
    int L2=L1;
    //while loop until a number for 2 is picked that is not the same as 1
    while(L2==L1)
    {
        L2=RandInt()%20;
    }
    //switch case to decide the location of the second light
    switch (L2){
        case 0:
            loc[2]=134;
            loc[3]=15;
            break;
        case 1:
            loc[2]=66;
            loc[3]=102;
            break;
        case 2:
            loc[2]=116;
            loc[3]=69;
            break;
        case 3: 
            loc[2]=209;
            loc[3]=87;
            break;
        case 4:
            loc[2]=127;
            loc[3]=126;
            break;
        case 5:
            loc[2]=186;
            loc[3]=135;
            break;
        case 6:
            loc[2]=74;
            loc[3]=139;
            break;
        case 7: 
            loc[2]=30;
            loc[3]=165;
            break;
        case 8:
            loc[2]=115;
            loc[3]=162;
            break;
        case 9:
            loc[2]=173;
            loc[3]=161;
            break;
        case 10:
            loc[2]=158;
            loc[3]=95;
            break;
        case 11:
            loc[2]=178;
            loc[3]=13;
            break;
        case 12:
            loc[2]=151;
            loc[3]=44;
            break;
        case 13: 
            loc[2]=187;
            loc[3]=46;
            break;
        case 14:
            loc[2]=237;
            loc[3]=74;
            break;
        case 15:
            loc[2]=230;
            loc[3]=122;
            break;
        case 16:
            loc[2]=272;
            loc[3]=127;
            break;
        case 17: 
            loc[2]=228;
            loc[3]=151;
            break;
        case 18:
            loc[2]=273;
            loc[3]=163;
            break;
        case 19:
            loc[2]=72;
            loc[3]=168;
            break;
    }
    //intialize third light
    int L3=L2;
    //while loop to make sure that the third light in the same loc as the other 2 lights
    while(L3==L1||L3==L2)
    {
        L3=RandInt()%20;
    }
    //record location of the third light into the array
    switch (L3){
        case 0:
            loc[4]=134;
            loc[5]=15;
            break;
        case 1:
            loc[4]=66;
            loc[5]=102;
            break;
        case 2:
            loc[4]=116;
            loc[5]=69;
            break;
        case 3: 
            loc[4]=209;
            loc[5]=87;
            break;
        case 4:
            loc[4]=127;
            loc[5]=126;
            break;
        case 5:
            loc[4]=186;
            loc[5]=135;
            break;
        case 6:
            loc[4]=74;
            loc[5]=139;
            break;
        case 7: 
            loc[4]=30;
            loc[5]=165;
            break;
        case 8:
            loc[4]=115;
            loc[5]=162;
            break;
        case 9:
            loc[4]=173;
            loc[5]=161;
            break;
        case 10:
            loc[4]=158;
            loc[5]=95;
            break;
        case 11:
            loc[4]=178;
            loc[5]=13;
            break;
        case 12:
            loc[4]=151;
            loc[5]=44;
            break;
        case 13: 
            loc[4]=187;
            loc[5]=46;
            break;
        case 14:
            loc[4]=237;
            loc[5]=74;
            break;
        case 15:
            loc[4]=230;
            loc[5]=122;
            break;
        case 16:
            loc[4]=272;
            loc[5]=127;
            break;
        case 17: 
            loc[4]=228;
            loc[5]=151;
            break;
        case 18:
            loc[4]=273;
            loc[5]=163;
            break;
        case 19:
            loc[4]=72;
            loc[5]=168;
            break;
    }
    //at the end of this function through the use of pointers the array loc now has the x and y values of the location
    //for each of the three lights
}

int drawLight(int loc[])
{
    //create a random variable to choose color
    int c;
    c=RandInt()%3;
    //switch case for 3 random colors
    switch (c)
    {
        case 0:
            LCD.SetDrawColor(BLUE);
            break;
        case 1:
            LCD.SetDrawColor(YELLOW);
            break;
        case 2:
            LCD.SetDrawColor(WHITE);
            break;
    }
    //Draw the circle in the randomly generated spot
    LCD.FillCircle(loc[0],loc[1],5);
    //get a new random number
    c=RandInt()%3;
    //use number to calculate random color
    switch (c)
    {
        case 0:
            LCD.SetDrawColor(BLUE);
            break;
        case 1:
            LCD.SetDrawColor(YELLOW);
            break;
        case 2:
            LCD.SetDrawColor(WHITE);
            break;
    }
    //draw the new light in given location
    LCD.FillCircle(loc[2],loc[3],5);
    // random number 
    c=RandInt()%4;
    //get color for light
    // This switch case ensures that there is a max of one red light per round
    switch (c)
    {
        case 0:
            LCD.SetDrawColor(BLUE);
            break;
        case 1:
            LCD.SetDrawColor(YELLOW);
            break;
        case 2:
            LCD.SetDrawColor(WHITE);
            break;
        case 3:
            LCD.SetDrawColor(RED);
            break;
    }
    //draw the light
    LCD.FillCircle(loc[4],loc[5],5);
    if(c==3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int fillLight(int loc[])
{
    //set color to green
    LCD.SetDrawColor(FORESTGREEN);
    //Draw the green circle to fill the spot of the previous lights
    LCD.FillCircle(loc[0],loc[1],5);
    //set color to green
    LCD.SetDrawColor(FORESTGREEN);
    //draw the new light in given location
    LCD.FillCircle(loc[2],loc[3],5);
    //set color to green
    LCD.SetDrawColor(FORESTGREEN);
    //draw the light
    LCD.FillCircle(loc[4],loc[5],5);
}

int ornament (float difficulty, int TotalPoints)
{
    int X[5], Y[5], N, M, O, P, Q, R, x, y, j, k, l, j1, k1, l1, L=0;
    float t_now;
    //Set the potential starting points for each ornament
    X[0] = 230;
    X[1] = 150;
    X[2] = 75;
    X[3] = 100;
    X[4] = 195;
    Y[0] = 70;
    Y[1] = 90;
    Y[2] = 120;
    Y[3] = 105;
    Y[4] = 85;

    //Design the bonus round start-up screen
    LCD.Clear(WHITE);
    LCD.SetFontColor(RED);
    LCD.WriteAt("Bonus Round!", 106, 30);
    LCD.WriteAt("Click the falling ornaments ", 60, 120);
    LCD.WriteAt("before they disappear for 200 points!", 20, 140);
    Sleep(2.01);
    LCD.Clear();
    DrawBackground();

    //Set up a loop to run three times and make ornaments fall three different times
    while (L<=2) {
        j=0;
        k=0;
        l=0;
        j1=0;
        k1=0;
        l1=0;
        //Randomly generate integers to generate random ornament starting positions
        N = RandInt()%5;
        M = RandInt()%5;
        O = RandInt()%5;
        P = RandInt()%5;
        Q = RandInt()%5;
        R = RandInt()%5;

        //Make sure no two ornaments start in the same place
        while (N == O || O == Q || N == Q) {
            O = RandInt()%5;
            Q = RandInt()%5;
        }
        //Display current score
        LCD.WriteAt("Total Points:", 0, 0);
        LCD.WriteAt(TotalPoints, 0, 20);
        //Have the ornaments drop for each third of the difficulty time 
        //That the ornaments are displaying
        t_now = TimeNow();
        while (TimeNow() - t_now <= difficulty) {
            while (TimeNow() - t_now <= difficulty/3) {
                    LCD.SetDrawColor(YELLOW);
                    if (j==0) {
                        LCD.DrawCircle(X[N], Y[M], 5);
                        LCD.FillCircle(X[N], Y[M], 5);
                    }
                    if (k==0) {
                        LCD.DrawCircle(X[O], Y[P], 5);
                        LCD.FillCircle(X[O], Y[P], 5);
                    }
                    if (l==0) {
                        LCD.DrawCircle(X[Q], Y[R], 5);
                        LCD.FillCircle(X[Q], Y[R], 5);
                    }
                    //Award points if an ornament is touched
                    if (LCD.Touch(&x, &y)) {
                        if (x<X[N]+5 && x>X[N]-5 && y<Y[M]+5 && y>Y[M]-5 && j==0) {
                            LCD.SetDrawColor(SKYBLUE);
                            LCD.FillRectangle(0, 0, 80, 50);
                            TotalPoints += 200;
                            LCD.WriteAt("Total Points:", 0, 0);
                            LCD.WriteAt(TotalPoints, 0, 20);
                            LCD.SetDrawColor(FORESTGREEN);
                            LCD.DrawCircle(X[N], Y[M], 5);
                            LCD.FillCircle(X[N], Y[M], 5);
                            j=1;
                        }
                        if (x<X[O]+5 && x>X[O]-5 && y<Y[P]+5 && y>Y[P]-5 && k==0) {
                            LCD.SetDrawColor(SKYBLUE);
                            LCD.FillRectangle(0, 0, 80, 50);
                            TotalPoints += 200;
                            LCD.WriteAt("Total Points:", 0, 0);
                            LCD.WriteAt(TotalPoints, 0, 20);
                            LCD.SetDrawColor(FORESTGREEN);
                            LCD.DrawCircle(X[O], Y[P], 5);
                            LCD.FillCircle(X[O], Y[P], 5);
                            k=1;
                        }
                        if (x<X[Q]+5 && x>X[Q]-5 && y<Y[R]+5 && y>Y[R]-5 && l==0) {
                            LCD.SetDrawColor(SKYBLUE);
                            LCD.FillRectangle(0, 0, 80, 50);
                            TotalPoints += 200;
                            LCD.WriteAt("Total Points:", 0, 0);
                            LCD.WriteAt(TotalPoints, 0, 20);
                            LCD.SetDrawColor(FORESTGREEN);
                            LCD.DrawCircle(X[Q], Y[R], 5);
                            LCD.FillCircle(X[Q], Y[R], 5);
                            l=1;
                        }
                    }
            }
            //Fill in the last ornament spot to make it seem like it disappeared
            LCD.SetDrawColor(FORESTGREEN);
            LCD.DrawCircle(X[N], Y[M], 5);
            LCD.FillCircle(X[N], Y[M], 5);
            LCD.DrawCircle(X[O], Y[P], 5);
            LCD.FillCircle(X[O], Y[P], 5);
            LCD.DrawCircle(X[Q], Y[R], 5);
            LCD.FillCircle(X[Q], Y[R], 5);
            //If an ornament isn't clicked yet, shift it one position
            //down the tree 
            if (TimeNow() - t_now >= difficulty/3 && TimeNow() - t_now <= (2 * difficulty/3)) {
                if (j==0) {
                    Y[M] += 10;
                    j1++;
                }
                if (k==0) {
                    Y[P] += 10;
                    k1++;
                }
                if (l==0) {
                    Y[R] += 10;
                    l1++;
                }
            }
            //Repeat
            while (TimeNow() - t_now >= difficulty/3 && TimeNow() - t_now <= (2 * difficulty/3)) {
                LCD.SetDrawColor(YELLOW);
                if (j==0) {
                    LCD.DrawCircle(X[N], Y[M], 5);
                    LCD.FillCircle(X[N], Y[M], 5);
                }
                if (k==0) {
                    LCD.DrawCircle(X[O], Y[P], 5);
                    LCD.FillCircle(X[O], Y[P], 5);
                }
                if (l==0) {
                    LCD.DrawCircle(X[Q], Y[R], 5);
                    LCD.FillCircle(X[Q], Y[R], 5);
                }
                if (LCD.Touch(&x, &y)) {
                    if (x<X[N]+5 && x>X[N]-5 && y<Y[M]+5 && y>Y[M]-5 && j==0) {
                        LCD.SetDrawColor(SKYBLUE);
                        LCD.FillRectangle(0, 0, 80, 50);
                        TotalPoints += 200;
                        LCD.WriteAt("Total Points:", 0, 0);
                        LCD.WriteAt(TotalPoints, 0, 20);
                        LCD.SetDrawColor(FORESTGREEN);
                        LCD.DrawCircle(X[N], Y[M], 5);
                        LCD.FillCircle(X[N], Y[M], 5);
                        j=1;
                    }
                    if (x<X[O]+5 && x>X[O]-5 && y<Y[P]+5 && y>Y[P]-5 && k==0) {
                        LCD.SetDrawColor(SKYBLUE);
                        LCD.FillRectangle(0, 0, 80, 50);
                        TotalPoints += 200;
                        LCD.WriteAt("Total Points:", 0, 0);
                        LCD.WriteAt(TotalPoints, 0, 20);
                        LCD.SetDrawColor(FORESTGREEN);
                        LCD.DrawCircle(X[O], Y[P], 5);
                        LCD.FillCircle(X[O], Y[P], 5);
                        k=1;
                    }
                    if (x<X[Q]+5 && x>X[Q]-5 && y<Y[R]+5 && y>Y[R]-5 && l==0) {
                        LCD.SetDrawColor(SKYBLUE);
                        LCD.FillRectangle(0, 0, 80, 50);
                        TotalPoints += 200;
                        LCD.WriteAt("Total Points:", 0, 0);
                        LCD.WriteAt(TotalPoints, 0, 20);
                        LCD.SetDrawColor(FORESTGREEN);
                        LCD.DrawCircle(X[Q], Y[R], 5);
                        LCD.FillCircle(X[Q], Y[R], 5);
                        l=1;
                    }
                }
            }
            LCD.SetDrawColor(FORESTGREEN);
            LCD.DrawCircle(X[N], Y[M], 5);
            LCD.FillCircle(X[N], Y[M], 5);
            LCD.DrawCircle(X[O], Y[P], 5);
            LCD.FillCircle(X[O], Y[P], 5);
            LCD.DrawCircle(X[Q], Y[R], 5);
            LCD.FillCircle(X[Q], Y[R], 5);
            if (TimeNow() - t_now >= 2 * difficulty/3 && TimeNow() - t_now <= difficulty) {
                if (j==0) {
                    Y[M] += 10;
                    j1++;
                }
                if (k==0) {
                    Y[P] += 10;
                    k1++;
                }
                if (l==0) {
                    Y[R] += 10;
                    l1++;
                }
            }
            while (TimeNow() - t_now >= 2 * difficulty/3 && TimeNow() - t_now <= difficulty) {
                LCD.SetDrawColor(YELLOW);
                if (j==0) {
                    LCD.DrawCircle(X[N], Y[M], 5);
                    LCD.FillCircle(X[N], Y[M], 5);
                }
                if (k==0) {
                    LCD.DrawCircle(X[O], Y[P], 5);
                    LCD.FillCircle(X[O], Y[P], 5);
                }
                if (l==0) {
                    LCD.DrawCircle(X[Q], Y[R], 5);
                    LCD.FillCircle(X[Q], Y[R], 5);
                }
                if (LCD.Touch(&x, &y)) {
                    if (x<X[N]+5 && x>X[N]-5 && y<Y[M]+5 && y>Y[M]-5 && j==0) {
                        LCD.SetDrawColor(SKYBLUE);
                        LCD.FillRectangle(0, 0, 80, 50);
                        TotalPoints += 200;
                        LCD.WriteAt("Total Points:", 0, 0);
                        LCD.WriteAt(TotalPoints, 0, 20);
                        LCD.SetDrawColor(FORESTGREEN);
                        LCD.DrawCircle(X[N], Y[M], 5);
                        LCD.FillCircle(X[N], Y[M], 5);
                        j=1;
                    }
                    if (x<X[O]+5 && x>X[O]-5 && y<Y[P]+5 && y>Y[P]-5 && k==0) {
                        LCD.SetDrawColor(SKYBLUE);
                        LCD.FillRectangle(0, 0, 80, 50);
                        TotalPoints += 200;
                        LCD.WriteAt("Total Points:", 0, 0);
                        LCD.WriteAt(TotalPoints, 0, 20);
                        LCD.SetDrawColor(FORESTGREEN);
                        LCD.DrawCircle(X[O], Y[P], 5);
                        LCD.FillCircle(X[O], Y[P], 5);
                        k=1;
                    }
                    if (x<X[Q]+5 && x>X[Q]-5 && y<Y[R]+5 && y>Y[R]-5 && l==0) {
                        LCD.SetDrawColor(SKYBLUE);
                        LCD.FillRectangle(0, 0, 80, 50);
                        TotalPoints += 200;
                        LCD.WriteAt("Total Points:", 0, 0);
                        LCD.WriteAt(TotalPoints, 0, 20);
                        LCD.SetDrawColor(FORESTGREEN);
                        LCD.DrawCircle(X[Q], Y[R], 5);
                        LCD.FillCircle(X[Q], Y[R], 5);
                        l=1;
                    }
                }
            }
            //Draw a green circle on the final spot to make it seem that each
            //ornament spot disappeared
            LCD.SetDrawColor(FORESTGREEN);
            LCD.DrawCircle(X[N], Y[M], 5);
            LCD.FillCircle(X[N], Y[M], 5);
            LCD.DrawCircle(X[O], Y[P], 5);
            LCD.FillCircle(X[O], Y[P], 5);
            LCD.DrawCircle(X[Q], Y[R], 5);
            LCD.FillCircle(X[Q], Y[R], 5);
        }
        //Reset the values of the Y array based on how many times it changed 
        //position
        Y[M] -= 10*j1;
        Y[P] -= 10*k1;
        Y[R] -= 10*l1;
        L++;
    }
    //return the total amount of points acquired during the regular and 
    //bonus rounds
    return TotalPoints;
}