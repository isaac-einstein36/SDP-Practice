/***********************************************/
/* Name:  Team JeoPARTY!    Date: 12/1/20      */
/* Seat No. 19,22,23,34  File:  SDPFinal.cpp   */
/* Instructor: RJF         12:45               */
/***********************************************/
// WEBSITE URL: https://u.osu.edu/fehsdp2020rjf1240f/
#include "FEHLCD.h"
#include "FEHRandom.h"
#include "FEHUtility.h"
#include "LCDColors.h"
//define constants
#define YMAX 240
/*
#define BUTTON1TEXT
#define BUTTON2TEXT
#define BUTTON3TEXT
#define BUTTON4TEXT
*/
 
//forward declarations
void DrawBoard(int[][4]);
int generateAddition(int difficulty);
int generateMultiplication(int difficulty);
int generateSubtraction(int difficulty);
int generateDivision(int difficulty);
 
//Game class
class Game
{
    public:
    int Play();
};
 
//Stats class
class Stats
{
    public:
    void Show(int scores[]);
};
 
//Draw Menu function
void DrawMenu()
{
   LCD.Clear();
   LCD.SetDrawColor(LIGHTGREEN);
   LCD.FillRectangle(0,0,319,YMAX/4);
   LCD.SetDrawColor(AQUA);
   LCD.FillRectangle(0,YMAX/4,319,YMAX/4);
   LCD.SetDrawColor(BLUE);
   LCD.FillRectangle(0,YMAX/2,319,YMAX/4);
   LCD.SetDrawColor(PURPLE);
   LCD.FillRectangle(0,YMAX*.75,319,YMAX/4);
   LCD.WriteAt("Play JeoPARTY!", 110, 20);
   LCD.WriteAt("Statistics", 130, 80);
   LCD.WriteAt("Instructions", 120, 140);
   LCD.WriteAt("Credits", 130, 200);
}
 
 
//Actual game! Fun
int Game::Play()
{
    //initialize values and data types
    int x, y, score=0, difficulty, type, Qleft=16;
    //vector to make sure same spot cannot be clicked twice
    int again[4][4]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //loop 16 time to make sure every question is picked
    while(Qleft>0)
    {
        //Draw Board 
        DrawBoard(again);
        //wait for user selection
        while(!LCD.Touch(&x, &y)){}
        difficulty=0;
        //find selected difficulty
        //difficulty 1
        if(y>48&&y<96)
        {difficulty=1;}
        //difficulty 2
        else if(y>96&&y<144)
        {difficulty=2;}
        //difficulty 3
        else if(y>144&&y<192)
        {difficulty=3;}
        //difficulty 4
        else if(y>192&&y<240)
        {difficulty=4;}
        else
        {difficulty=0;}
        //find type of question
        //addition
        if(x>0&&x<80)
        {type=1;}
        //multiplication
        else if(x>80&&x<160)
        {type=2;}
        //subtraction
        else if(x>160&&x<240)
        {type=3;}
        //division
        else if(x>240&&x<320)
        {type=4;}
        //find exact question selected
        switch (type)
        {
            //bad x input catcher just in case
            case 0: break;
 
            //addition
            case 1:
            //if user selects a y value below 48, where there are no question buttons
            if(difficulty==0)
            {
                break;
            }
            //test to see if this question had been picked before
            //if has been picked, break
            if(again[difficulty-1][type-1]==1)
            {
                break;
            }
            //has not been picked before
            if(again[difficulty-1][type-1]==0)
            {
                //now has been picked, wont be picked again
                again[difficulty-1][type-1]=1;
                //generate question and modify score accordingly
                score+=generateAddition(difficulty);
                Qleft--;
                break;
            }
 
            //multiplication
            case 2:
            //if user selects a y value below 48, where there are no question buttons
            if(difficulty==0)
            {
                break;
            }
            //test to see if this question had been picked before
            //if has been picked, break
            if(again[difficulty-1][type-1]==1)
            {
                break;
            }
            //has not been picked before
            if(again[difficulty-1][type-1]==0)
            {
                //now has been picked, wont be picked again
                again[difficulty-1][type-1]=1;
                //generate question and modify score accordingly
                score+=generateMultiplication(difficulty);
                Qleft--;
                break;
            }
 
            //subtraction
            case 3:
            //if user selects a y value below 48, where there are no question buttons
            if(difficulty==0)
            {
                break;
            }
            //test to see if this question had been picked before
            //if has been picked, break
            if(again[difficulty-1][type-1]==1)
            {
                break;
            }
            //has not been picked before
            if(again[difficulty-1][type-1]==0)
            {
                //now has been picked, wont be picked again
                again[difficulty-1][type-1]=1;
                //generate question and modify score accordingly
                score+=generateSubtraction(difficulty);
                Qleft--;
                break;
            }
 
            //division
            case 4:
            //if user selects a y value below 48, where there are no question buttons
            if(difficulty==0)
            {
                break;
            }
            //test to see if this question had been picked before
            //if has been picked, break
            if(again[difficulty-1][type-1]==1)
            {
                break;
            }
            //has not been picked before
            if(again[difficulty-1][type-1]==0)
            {
                //now has been picked, wont be picked again
                again[difficulty-1][type-1]=1;
                //generate question and modify score accordingly
                score+=generateDivision(difficulty);
                Qleft--;
                break;
            }
        }
 
    }
    //After all questions have been answered
    LCD.Clear();
    LCD.Write("Your score was: ");
    LCD.Write(score);
    //exit button
    LCD.DrawLine(0,YMAX*3/4,319,YMAX*3/4);
    LCD.WriteAt("MENU", 130, 195);
    while(1){
    while(!LCD.Touch(&x, &y)){}
    if(y>YMAX*3/4)
    {
        LCD.Clear();
        return score;
    }
    }
}
 
//Show stats function
void Stats::Show(int scores[])
{
   int x, y;
   LCD.Clear();
   LCD.SetFontColor(AQUA);
 
   //write stats to screen
   LCD.WriteLine("Your five most recent scores are:");
   LCD.WriteLine(scores[0]);
   LCD.WriteLine(scores[1]);
   LCD.WriteLine(scores[2]);
   LCD.WriteLine(scores[3]);
   LCD.WriteLine(scores[4]);
 
   // creating exit button
   LCD.SetDrawColor(BLACK);
   LCD.DrawRectangle(0,YMAX*.75,319,YMAX*.25);
   LCD.SetDrawColor(AQUA);
   LCD.FillRectangle(0,YMAX*.75,319,YMAX*.25);
   LCD.SetFontColor(BLACK);
   LCD.WriteAt("MENU", 130, 195);
   int startX1=230,startY=50,endX1,endY1,tree=0, endX2,startX2,q=1, startY2,yCircle=319;
   while(yCircle>230)
   {
       LCD.SetDrawColor(YELLOW);
       LCD.FillCircle(yCircle,40,10);
 
       if (yCircle<=319)
       {
           LCD.SetDrawColor(BLACK);
           LCD.FillCircle(yCircle,40,10);
       }
     yCircle=yCircle-1;
   }
           LCD.SetDrawColor(BLACK);
           LCD.FillCircle(230,40,10);   
   if (yCircle=230)
   {
       while(tree<3)
       {
           //makes tree move up and down
           if (tree%2==0)
           {
               startY=50;
           }
           else
           {
               startY=65;
           }
           startX1=230;
           //makes the star on top
           LCD.SetDrawColor(YELLOW);
           LCD.FillCircle(startX1,startY-10,10);
         
          //drawing the top of the tree
           LCD.SetDrawColor(RED);
           endX1=startX1+30;
           endX2=startX1-30;
           endY1=startY+20;
           LCD.DrawLine(startX1,startY,endX1,endY1);
           LCD.DrawLine(startX1,startY,endX2,endY1);
           startX1=endX1;
           startX2=endX2;
           endX1=endX1-15;
           endX2=endX2+15;
        
          //ending top layer of the tree
           LCD.SetDrawColor(LIGHTGREEN);
           LCD.DrawLine(startX1,endY1,endX1,endY1);
           LCD.DrawLine(startX2,endY1,endX2,endY1);
 
           startY=endY1;
           startX1=endX1;
           startX2=endX2;
           endY1=endY1+20;
           endX1=endX1+30;
           endX2=endX2-30;
 
          //starting the second layer of the tree
           LCD.SetDrawColor(YELLOW);
           LCD.DrawLine(startX1,startY,endX1,endY1);
           LCD.DrawLine(startX2,startY,endX2,endY1);
 
           startX1=endX1;
           startX2=endX2;
           endX1=endX1-15;
           endX2=endX2+15;
 
           
           //ending second layer
           LCD.SetDrawColor(LIME);
           LCD.DrawLine(startX1,endY1,endX1,endY1);
           LCD.DrawLine(startX2,endY1,endX2,endY1);
 
           startX1=endX1;
           startX2=endX2;
           endX1=endX1+30;
           endX2=endX2-30;
           startY=endY1;
           endY1=endY1+20;
           
           //starting the third layer of the tree
           LCD.SetDrawColor(WHITE);
           LCD.DrawLine(startX1,startY,endX1,endY1);
           LCD.DrawLine(startX2,startY,endX2,endY1);
           
           //finishing the third layer of the tree
           LCD.SetDrawColor(AQUA);
           LCD.DrawLine(endX1,endY1,endX2,endY1);
           
           //Drawing the trunk of the tree
           LCD.SetDrawColor(BROWN);
           LCD.FillRectangle((((endX1+endX2)/2)-10),endY1,20,20);
 
       //makes it so the tree flashes
           //makes tree move up and down
           startX1=230;
           if (tree%2==0)
           {
               startY=50;
           }
           else
           {
               startY=65;
           }
          
           //makes the star on top
           LCD.SetDrawColor(BLACK);
           LCD.FillCircle(startX1,startY-10,10);
 
           LCD.SetDrawColor(BLACK);
           endX1=startX1+30;
           endX2=startX1-30;
           endY1=startY+20;
           LCD.DrawLine(startX1,startY,endX1,endY1);
           LCD.DrawLine(startX1,startY,endX2,endY1);
           startX1=endX1;
           startX2=endX2;
           endX1=endX1-15;
           endX2=endX2+15;
           LCD.SetDrawColor(BLACK);
           LCD.DrawLine(startX1,endY1,endX1,endY1);
           LCD.DrawLine(startX2,endY1,endX2,endY1);
 
           startY=endY1;
           startX1=endX1;
           startX2=endX2;
           endY1=endY1+20;
           endX1=endX1+30;
           endX2=endX2-30;
 
           LCD.SetDrawColor(BLACK);
           LCD.DrawLine(startX1,startY,endX1,endY1);
           LCD.DrawLine(startX2,startY,endX2,endY1);
 
           startX1=endX1;
           startX2=endX2;
           endX1=endX1-15;
           endX2=endX2+15;
 
           LCD.SetDrawColor(BLACK);
           LCD.DrawLine(startX1,endY1,endX1,endY1);
           LCD.DrawLine(startX2,endY1,endX2,endY1);
 
           startX1=endX1;
           startX2=endX2;
           endX1=endX1+30;
           endX2=endX2-30;
           startY=endY1;
           endY1=endY1+20;
           LCD.SetDrawColor(BLACK);
           LCD.DrawLine(startX1,startY,endX1,endY1);
           LCD.DrawLine(startX2,startY,endX2,endY1);
      
           LCD.SetDrawColor(BLACK);
           LCD.DrawLine(endX1,endY1,endX2,endY1);
      
           LCD.SetDrawColor(BLACK);
           LCD.FillRectangle((((endX1+endX2)/2)-10),endY1,20,20);
 
           tree++;
 
       }
   }
   while(1){
   while(!LCD.Touch(&x,&y)){}
   if(y>YMAX*3/4)
   {
       LCD.Clear();
       return;
   }
   }
 
 
}
 
//Show instructions function
void ShowInstructions()
{
   int x, y;
   LCD.Clear();
   //write Instructions to screen
   LCD.SetFontColor(SKYBLUE);
   LCD.WriteLine("How to play JeoPARTY!:");
   LCD.WriteLine("Click on a number to select a question!");
   LCD.WriteLine("The column  decides the type of problem");
   LCD.WriteLine("The row decides the difficulty,");
   LCD.WriteLine("and the point value!");
   LCD.WriteLine("Select the correct answer to win points,");
   LCD.WriteLine("but the wrong answer, you lose points");
   //exit button
   LCD.DrawLine(0,YMAX*3/4,319,YMAX*3/4);
   LCD.SetDrawColor(SKYBLUE);
   LCD.FillRectangle(0,YMAX*.75,319,YMAX*.25);
   LCD.SetFontColor(BLACK);
   LCD.WriteAt("MENU", 130, 195);
   while(!LCD.Touch(&x,&y)){}
   while(1){
   if(y>YMAX*3/4)
   {
       LCD.Clear();
       return;
   }
   }
 
}
 
//Show Credits function
void ShowCredits()
{
   int x, y;
   LCD.Clear();
   //write Credits to screen
   LCD.SetFontColor(PURPLE);
   LCD.WriteLine("Credits/Developers:");
   LCD.WriteLine("Kevin Penrose");
   LCD.WriteLine("Shreya Gundavarpu");
   LCD.WriteLine("Aiden Powers");
   LCD.WriteLine("Riya Sangtani");
 
 
  
   //exit button
   LCD.SetDrawColor(BLACK);
   LCD.DrawRectangle(0,YMAX*3/4,319,YMAX*1/4);
   LCD.SetDrawColor(PURPLE);
   LCD.FillRectangle(0,YMAX*.75,319,YMAX*.25);
   LCD.SetFontColor(BLACK);
   LCD.WriteAt("MENU", 130, 195);
 
   int xChange=0;
   int yChange=0;
 
       while (xChange<319)
       {
               LCD.SetDrawColor(YELLOW);
                  LCD.FillRectangle(xChange,yChange,11,1);
 
           if (xChange>0)
           {
               LCD.SetDrawColor(BLACK);
               LCD.FillRectangle(xChange-11,yChange,11,1);
           }
           xChange=xChange+11;
       }
 
       xChange=319;
       yChange=0;
       //gets rid of last rectangle
       LCD.SetDrawColor(BLACK);
       LCD.FillRectangle(308,0,11,1);
       LCD.SetDrawColor(SCARLET);
       LCD.FillRectangle(319,239,50,1);
      
       //makes right border
       if (xChange==319 && yChange==0)
       {
        while (yChange<239)
        {
            if (yChange==230)
            {
               LCD.SetDrawColor(YELLOW);
               LCD.FillRectangle(xChange,yChange,1,9);
              
              
            }
            else
            {
               LCD.SetDrawColor(YELLOW);
               LCD.FillRectangle(xChange,yChange,1,10);
            }
           //gets rid of last rectangle
           if (yChange>0)
           {
               LCD.SetDrawColor(BLACK);
               LCD.FillRectangle(xChange,yChange-10,1,10);
           }
           yChange=yChange+10;
        }
       }
 
       //gets rid of last rectangle
       xChange=319;
       yChange=239;
       LCD.SetDrawColor(BLACK);
       LCD.FillRectangle(319,220,1,19);
       LCD.SetDrawColor(SCARLET);
       LCD.FillRectangle(319,239,50,1);
 
       //makes bottom border
       if (xChange==319 && yChange==239)
       {
       xChange=308;
 
        while (xChange>0)
        {
              
               LCD.SetDrawColor(YELLOW);
               LCD.FillRectangle(xChange,yChange,11,1);
           if (xChange<=308)
           {
               LCD.SetDrawColor(BLACK);
               LCD.FillRectangle(xChange+11,yChange,11,1);
           }
           xChange=xChange-11;
        }
       }
       //gets rid of last rectangle
       xChange=0;
       yChange=239;
       LCD.SetDrawColor(BLACK);
       LCD.FillRectangle(0,239,30,1);
       LCD.SetDrawColor(SCARLET);
       LCD.FillRectangle(0,239,1,50);
       LCD.SetDrawColor(SCARLET);
       LCD.FillRectangle(319,239,50,1);
       //makes left border
       if (xChange==0 && yChange==239)
       {
       yChange=228;
        while (yChange>0)
        {
            if (yChange==9)
            {
               LCD.SetDrawColor(YELLOW);
               LCD.FillRectangle(xChange,yChange,1,9);
            }
            else
            {
               LCD.SetDrawColor(YELLOW);
                  LCD.FillRectangle(xChange,yChange,1,10);
            }
           if (yChange<=228)
           {
               LCD.SetDrawColor(BLACK);
               LCD.FillRectangle(xChange,yChange+10,1,10);
           }
           yChange=yChange-10;
        }
       //gets rid of rectangle
       xChange=0;
       yChange=0;
       LCD.SetDrawColor(BLACK);
       LCD.FillRectangle(0,0,1,20);
       LCD.SetDrawColor(SCARLET);
       LCD.FillRectangle(319,239,50,1);
           
   }
 
   while(1){
   while(!LCD.Touch(&x,&y)){}
   if(y>YMAX*3/4)
   {
       LCD.Clear();
       return;
   }
   }
}
 
//Draw Board
void DrawBoard(int clicked[][4])
{
 
   int x, y;
   LCD.Clear();
   //makes boxes for all of the categories in various colors
   LCD.SetFontColor(BLACK);
   LCD.SetDrawColor(BLUE);
   LCD.FillRectangle(0,0,80,48);
   LCD.WriteAt("+",40,24);
   LCD.SetDrawColor(GREEN);
   LCD.FillRectangle(80,0,80,48);
   LCD.WriteAt("X",120,24);
   LCD.SetDrawColor(DARKRED);
   LCD.FillRectangle(160,0,80,48);
   LCD.WriteAt("-",200,24);
   LCD.SetDrawColor(TEAL);
   LCD.FillRectangle(240,0,80,48);
   LCD.WriteAt("/",280,24);
 
   //draws first row of question boxes
 
  //drawing the first column
   LCD.SetDrawColor(SKYBLUE);
   LCD.FillRectangle(0,48,80,48);
   if (clicked[0][0]==0)
   {
       LCD.WriteAt("100",40,62);
   }
  //drawing the second column
   LCD.SetDrawColor(LIGHTGREEN);
   LCD.FillRectangle(80,48,80,48);
  if (clicked[0][1]==0)
   {
       LCD.WriteAt("100",120,62);
   }
 
  //drawing the third column
   LCD.SetDrawColor(RED);
   LCD.FillRectangle(160,48,80,48);
  if (clicked[0][2]==0)
   {
       LCD.WriteAt("100",200,62);
   }   
   //drawing the fourth column
   LCD.SetDrawColor(AQUA);
   LCD.FillRectangle(240,48,80,48);
   if (clicked[0][3]==0)
   {
       LCD.WriteAt("100",280,62);
   }
 
   //draws second row of question boxes
//drawing the first column
   LCD.SetDrawColor(SKYBLUE);
   LCD.FillRectangle(0,96,80,48);
   if (clicked[1][0]==0)
   {
       LCD.WriteAt("200",40,120);
   }
 
   //drawing the second column
LCD.SetDrawColor(LIGHTGREEN);
   LCD.FillRectangle(80,96,80,48);
   if (clicked[1][1]==0)
   {
       LCD.WriteAt("200",120,120);
   }
 
 //drawing the third column
   LCD.SetDrawColor(RED);
   LCD.FillRectangle(160,96,80,48);
   if (clicked[1][2]==0)
   {
       LCD.WriteAt("200",200,120);
   }
  //drawing the fourth column
   LCD.SetDrawColor(AQUA);
   LCD.FillRectangle(240,96,80,48);
   if (clicked[1][3]==0)
   {
       LCD.WriteAt("200",280,120);
   }
   //draws third row of question boxes
   //drawing the first column
   LCD.SetDrawColor(SKYBLUE);
   LCD.FillRectangle(0,144,80,48);
   if (clicked[2][0]==0)
   {
       LCD.WriteAt("300",40,168);
   }
  //drawing the second column
   LCD.SetDrawColor(LIGHTGREEN);
   LCD.FillRectangle(80,144,80,48);
   if (clicked[2][1]==0)
   {
       LCD.WriteAt("300",120,168);
   }
 
 //drawing the third column
   LCD.SetDrawColor(RED);
   LCD.FillRectangle(160,144,80,48);
   if (clicked[2][2]==0)
   {
       LCD.WriteAt("300",200,168);
   }
 
 //drawing the fourth column
   LCD.SetDrawColor(AQUA);
   LCD.FillRectangle(240,144,80,48);
   if (clicked[2][3]==0)
   {
       LCD.WriteAt("300",280,168);
   }
 
   //draws fourth row of question boxes
   //drawing the first column
   LCD.SetDrawColor(SKYBLUE);
   LCD.FillRectangle(0,192,80,48);
   if (clicked[3][0]==0)
   {
       LCD.WriteAt("400",40,216);
   }
 
  //drawing the second column
   LCD.SetDrawColor(LIGHTGREEN);
   LCD.FillRectangle(80,192,80,48);
   if (clicked[3][1]==0)
   {
       LCD.WriteAt("400",120,216);
   }
 
   //drawing the third column
   LCD.SetDrawColor(RED);
   LCD.FillRectangle(160,192,80,48);
   if (clicked[3][2]==0)
   {
       LCD.WriteAt("400",200,216);
   }
 
   //drawing the fourth column
   LCD.SetDrawColor(AQUA);
   LCD.FillRectangle(240,192,80,48);
   if (clicked[3][3]==0)
   {
       LCD.WriteAt("400",280,216);
   }
 
   //draws line dividers for boxes
    LCD.SetDrawColor(BLACK);
     LCD.DrawLine(0,48,319,48);
   LCD.DrawLine(0,96,319,96);
   LCD.DrawLine(0,144,319,144);
   LCD.DrawLine(0,192,319,192);
   LCD.DrawLine(80,0,80,240);
   LCD.DrawLine(160,0,160,240);
   LCD.DrawLine(240,0,240,240);
 
   while(!LCD.Touch(&x, &y)){}
}
 
 
//Generate Addition
int generateAddition(int difficulty){
    //declare variables
    int x = -10000 , y = - 10000;
//declare variables for the random question generation, while loop, and points to return
    int a,b,c,i,countdown,answer,ChangeInPoints;
    int wrong1, wrong2, wrong3, plusminus, ansplace;
 //declare time variables
    double timeadd;
 
    //create a switch case statement to check for the difficulty
    switch (difficulty){
        //if the difficulty is 1 (worth 100 points)
        case 1:
            //generate 3 random integers between 1 and 10
            a = (RandInt() % 10) + 1;
            b = (RandInt() % 10) + 1;
            c = (RandInt() % 10) + 1;
            //set the time given to 15 seconds
            timeadd = 15;
            break;
        //if the difficulty is 2 (worth 200 points)
        case 2:
            //generate 3 random integers between 1 and 100
            a = (RandInt() % 100) + 1;
            b = (RandInt() % 100) + 1;
            c = (RandInt() % 100) + 1;
            //set the time given to 12 seconds
            timeadd = 12;
            break;
        //if the difficulty is 3 (worth 300 points)
        case 3:
            //generate 3 random integers between 1 and 1000
            a = (RandInt() % 1000) + 1;
            b = (RandInt() % 1000) + 1;
            c = (RandInt() % 1000) + 1;
            //set the time given to 10 seconds
            timeadd = 10;
            break;
        //if the difficulty is 4 (worth 400 points)
        case 4:
            //generate 3 random integers between 1 and 10000
            a = (RandInt() % 10000) + 1;
            b = (RandInt() % 10000) + 1;
            c = (RandInt() % 10000) + 1;
            //set the time given to 7 seconds
            timeadd = 7;
            break;
    }
    //store the answer
    answer = a + b + c;
 
      //Calculating how far off the incorrect answers will be from the answer
      //Incorrect answers are no more than 10 numbers away from the correct answer
      wrong1 = RandInt() % 10 + 1;
      wrong2 = RandInt() % 10 + 1;
      wrong3 = RandInt() % 10 + 1;
 
      //Calculating the value of incorrect answer 1 (wrong1)
      
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong1 = answer + wrong1;    
      }
 
      if (plusminus == 1)
      {
        wrong1 = answer - wrong1;
      }
 
      //Calculating the value of incorrect answer 2 (wrong2)
 
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong2 = answer + wrong2;
        
        //making sure incorrect answers do not repeat
        while(wrong2 == wrong1){
 
          wrong2 = wrong2 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong2 == answer){
 
           wrong2 = wrong2 + 1;
 
          }
      }
 
      if (plusminus == 1)
      {
        wrong2 = answer - wrong2;
 
        //making sure incorrect answers do not repeat
        while(wrong2 == wrong1){
 
          wrong2 = wrong2 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong2 == answer){
 
           wrong2 = wrong2 + 1;
           }
 
      }
 
 
      //Calculating the value of incorrect answer 3 (wrong3)
 
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong3 = answer + wrong3;
 
        //making sure incorrect answers do not repeat
        while(wrong3 == wrong2){
 
          wrong3 = wrong3 + 1;
          }
           
           while(wrong3 == wrong1){
 
          wrong3 = wrong3 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong3 == answer){
 
           wrong3 = wrong3 + 1;
 
          }
      }
 
      if (plusminus == 1)
      {
        wrong3 = answer - wrong3;
 
        //making sure incorrect answers do not repeat
        while(wrong3 == wrong2){
 
          wrong3 = wrong3 + 1;
          }
           
           while(wrong3 == wrong1){
 
          wrong3 = wrong3 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong3 == answer){
 
           wrong3 = wrong3 + 1;
 
          }
      }
 
 
    //Displaying the problem and the 4 multiple choice possibilities
 
    //Clearing the board and displaying the problem
    LCD.Clear();
    LCD.SetFontColor(LCD.Gray);
    LCD.WriteAt(a,60,60);
    LCD.WriteAt("+", 120, 60);
    LCD.WriteAt(b, 140, 60);
    LCD.WriteAt("+", 200, 60);
    LCD.WriteAt(c, 220, 60);
 
    //Displaying '(A)' '(B)' '(C)' and '(D)' to the screen which will be followed by answer choices
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt("(A) ",60,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt("(B) ",60,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt("(C) ",60,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt("(D) ",60,220);
 
 
    //Randomly assigning the correct answer to either '(A)', '(B)', '(C)', or '(D)'
     ansplace = RandInt() % 4;
 
 switch (ansplace)
 {
 
     //Case 0: the correct answer goes in the '(A)' slot
    case 0:  
    
    //Setting the correct answer to '(A)' and the wrong answers to the other slots
    
    LCD.SetFontColor(LCD.Blue); 
    LCD.WriteAt(answer,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong1,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong2,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
     
    //Setting countdown equal to timeadd
     countdown = timeadd;
      
    //start a for loop to display the countdown
 
    for (i=0; i <= timeadd; i++){
       
        //make a rectangle to cover the past number                 LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
    
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
 
       LCD.Touch(&x,&y);
 
    
    //Setting a while loop to wait for user to select an answer
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>114 && y<146)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if (x>60 && x<120 && y>145 && y<236)
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative so it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
  
      //Returning change in points
      return ChangeInPoints;
 
     
  }
 
  //if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
           
}
      
 
  break;
 
 
  
  //Case 1: the correct answer goes in the '(B)' slot
    case 1:  
    
    //Setting the correct answer to '(A)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(answer,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong2,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
    countdown = timeadd;
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
        //make a rectangle to cover the past number        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
        //subtract one from the variable countdown
        countdown = countdown - 1;
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
    
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>145 && y<176)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
       
    }
    
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if ((x> 60 && x< 120 && y>175 && y<236) || (x> 60 && x< 120 && y<146 && y>115))
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the scren 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
      
  }
 
//if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
}
 
  break;
  
     
//Case 2: the correct answer goes in the '(C)' slot
    case 2:  
    
    //Setting the correct answer to '(C)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong2,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(answer,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
 
    //setting countdown equal to timeadd
      countdown = timeadd;
 
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
 
        //make a rectangle to cover the past number        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
 
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
   
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>175 && y<206)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if ((x> 60 && x< 120 && y>205 && y<236) || (x> 60 && x< 120 && y<176 && y>115))
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
     
  }
  
  //if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
}
 
  break;
 
 
     //Case 3: the correct answer goes in the '(D)' slot
    case 3:  
    
    //Setting the correct answer to '(D)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong2,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong3,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(answer,90,220);
 
     //Displaying how much time is left to answer the question
    countdown = timeadd;
 
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
        //make a rectangle to cover the past number           LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
 
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
   
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>205 && y<236)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
       
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if (x>60 && x<120 && y<206 && y>115)
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
     
  }
     
    //if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
} 
 
  break;
    }
}
 
 
//Generate Multiplication
int generateMultiplication(int difficulty){
    //declare variables
    int x = -10000 , y = - 10000;
    //declare variables for the random question generation, while loop, and points to return
    int a,b,i,countdown,answer,ChangeInPoints;
    int wrong1, wrong2, wrong3, plusminus, ansplace;
    //declare time variables
    double timeadd;
 
    //create a switch case statement to check for the difficulty
    switch (difficulty){
        //if the difficulty is 1 (worth 100 points)
        case 1:
            //generate 3 random integers between 1 and 10
            a = (RandInt() % 10) + 1;
            b = (RandInt() % 10) + 1;
            //set the time given to 10 seconds
            timeadd = 10;
            break;
        //if the difficulty is 2 (worth 200 points)
        case 2:
            //generate 3 random integers between 1 and 100
            a = (RandInt() % 100) + 1;
            b = (RandInt() % 100) + 1;
            //set the time given to 9 seconds
            timeadd = 9;
            break;
        //if the difficulty is 3 (worth 300 points)
        case 3:
            //generate 3 random integers between 1 and 1000
            a = (RandInt() % 1000) + 1;
            b = (RandInt() % 1000) + 1;
            //set the time given to 8 seconds
            timeadd = 8;
            break;
        //if the difficulty is 4 (worth 400 points)
        case 4:
            //generate 3 random integers between 1 and 10000
            a = (RandInt() % 10000) + 1;
            b = (RandInt() % 10000) + 1;
            //set the time given to 8 seconds
            timeadd = 8;
            break;
    }
    //store the answer
    answer = a * b;
 
      //Calculating how far off the incorrect answers will be from the answer
      //Incorrect answers are no more than 3 numbers away from the correct answer
      wrong1 = RandInt() % 2 + 1;
      wrong2 = RandInt() % 2 + 1;
      wrong3 = RandInt() % 2 + 1;
 
      //Calculating the value of incorrect answer 1 (wrong1)
      
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong1 = answer + wrong1;    
      }
 
      if (plusminus == 1)
      {
        wrong1 = answer - wrong1;
      }
 
      //Calculating the value of incorrect answer 2 (wrong2)
 
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong2 = answer + wrong2;
        
        //making sure incorrect answers do not repeat
        while(wrong2 == wrong1){
 
          wrong2 = wrong2 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong2 == answer){
 
           wrong2 = wrong2 + 1;
 
          }
      }
 
      if (plusminus == 1)
      {
        wrong2 = answer - wrong2;
 
        //making sure incorrect answers do not repeat
        while(wrong2 == wrong1){
 
          wrong2 = wrong2 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong2 == answer){
 
           wrong2 = wrong2 + 1;
           }
 
      }
 
 
      //Calculating the value of incorrect answer 3 (wrong3)
 
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong3 = answer + wrong3;
 
        //making sure incorrect answers do not repeat
        while(wrong3 == wrong2){
 
          wrong3 = wrong3 + 1;
          }
           
           while(wrong3 == wrong1){
 
          wrong3 = wrong3 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong3 == answer){
 
           wrong3 = wrong3 + 1;
 
          }
      }
 
      if (plusminus == 1)
      {
        wrong3 = answer - wrong3;
 
        //making sure incorrect answers do not repeat
        while(wrong3 == wrong2){
 
          wrong3 = wrong3 + 1;
          }
           
           while(wrong3 == wrong1){
 
          wrong3 = wrong3 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong3 == answer){
 
           wrong3 = wrong3 + 1;
 
          }
      }
 
 
    //Displaying the problem and the 4 multiple choice possibilities
 
    //Clearing the board and displaying the problem
    LCD.Clear();
    LCD.SetFontColor(LCD.Gray);
    LCD.WriteAt(a,60,60);
    LCD.WriteAt("x", 120, 60);
    LCD.WriteAt(b, 140, 60);
 
    //Displaying '(A)' '(B)' '(C)' and '(D)' to the screen which will be followed by answer choices
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt("(A) ",60,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt("(B) ",60,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt("(C) ",60,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt("(D) ",60,220);
 
 
    //Randomly assigning the correct answer to either '(A)', '(B)', '(C)', or '(D)'
     ansplace = RandInt() % 4;
 
 switch (ansplace)
 {
 
     //Case 0: the correct answer goes in the '(A)' slot
    case 0:  
    
    //Setting the correct answer to '(A)' and the wrong answers to the other slots
    
    LCD.SetFontColor(LCD.Blue); 
    LCD.WriteAt(answer,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong1,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong2,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
     
    //Setting countdown equal to timeadd
     countdown = timeadd;
      
    //start a for loop to display the countdown
 
    for (i=0; i <= timeadd; i++){
       
        //make a rectangle to cover the past number                 LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
    
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
 
       LCD.Touch(&x,&y);
 
    
    //Setting a while loop to wait for user to select an answer
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>114 && y<146)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if (x>60 && x<120 && y>145 && y<236)
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative so it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
  
      //Returning change in points
      return ChangeInPoints;
 
     
  }
 
  //if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
           
}
      
 
  break;
 
 
  
  //Case 1: the correct answer goes in the '(B)' slot
    case 1:  
    
    //Setting the correct answer to '(A)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(answer,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong2,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
    countdown = timeadd;
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
        //make a rectangle to cover the past number        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
        //subtract one from the variable countdown
        countdown = countdown - 1;
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
    
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>145 && y<176)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
       
    }
    
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if ((x> 60 && x< 120 && y>175 && y<236) || (x> 60 && x< 120 && y<146 && y>115))
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
      
  }
 
//if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
}
 
  break;
  
     
//Case 2: the correct answer goes in the '(C)' slot
    case 2:  
    
    //Setting the correct answer to '(C)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong2,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(answer,90,190);
 
LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
 
    //setting countdown equal to timeadd
      countdown = timeadd;
 
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
 
        //make a rectangle to cover the past number        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
 
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
   
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>175 && y<206)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if ((x> 60 && x< 120 && y>205 && y<236) || (x> 60 && x< 120 && y<176 && y>115))
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
     
  }
  
  //if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
}
 
  break;
 
 
     //Case 3: the correct answer goes in the '(D)' slot
    case 3:  
    
    //Setting the correct answer to '(D)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong2,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong3,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(answer,90,220);
 
     //Displaying how much time is left to answer the question
    countdown = timeadd;
 
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
        //make a rectangle to cover the past number           LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
 
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
   
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>205 && y<236)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
       
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if (x>60 && x<120 && y<206 && y>115)
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
     
  }
     
    //if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
} 
 
  break;
    }
}
 
//Generate Subtraction
int generateSubtraction(int difficulty){
    //declare variables
    int x = -10000 , y = - 10000;
    //declare variables for the random question generation, while loop, and points to return
    int a,b,c,i,countdown,answer,ChangeInPoints;
    int wrong1, wrong2, wrong3, plusminus, ansplace;
    //declare time variables
    double timeadd;
 
    //create a switch case statement to check for the difficulty
    switch (difficulty){
        //if the difficulty is 1 (worth 100 points)
        case 1:
            //generate 3 random integers between 1 and 10
            a = (RandInt() % 10) + 1;
            b = (RandInt() % 10) + 1;
            c = (RandInt() % 10) + 1;
            //set the time given to 15 seconds
            timeadd = 15;
            break;
        //if the difficulty is 2 (worth 200 points)
        case 2:
            //generate 3 random integers between 1 and 100
            a = (RandInt() % 100) + 1;
            b = (RandInt() % 100) + 1;
            c = (RandInt() % 100) + 1;
            //set the time given to 12 seconds
            timeadd = 12;
            break;
        //if the difficulty is 3 (worth 300 points)
        case 3:
            //generate 3 random integers between 1 and 1000
            a = (RandInt() % 1000) + 1;
            b = (RandInt() % 1000) + 1;
            c = (RandInt() % 1000) + 1;
            //set the time given to 10 seconds
            timeadd = 10;
            break;
        //if the difficulty is 4 (worth 400 points)
        case 4:
            //generate 3 random integers between 1 and 10000
            a = (RandInt() % 10000) + 1;
            b = (RandInt() % 10000) + 1;
            c = (RandInt() % 10000) + 1;
            //set the time given to 7 seconds
            timeadd = 12;
            break;
    }
    //store the answer
    answer = a - b - c;
 
      //Calculating how far off the incorrect answers will be from the answer
      //Incorrect answers are no more than 10 numbers away from the correct answer
      wrong1 = RandInt() % 10 + 1;
      wrong2 = RandInt() % 10 + 1;
      wrong3 = RandInt() % 10 + 1;
 
      //Calculating the value of incorrect answer 1 (wrong1)
      
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong1 = answer + wrong1;    
      }
 
      if (plusminus == 1)
      {
        wrong1 = answer - wrong1;
      }
 
      //Calculating the value of incorrect answer 2 (wrong2)
 
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong2 = answer + wrong2;
        
        //making sure incorrect answers do not repeat
        while(wrong2 == wrong1){
 
          wrong2 = wrong2 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong2 == answer){
 
           wrong2 = wrong2 + 1;
 
          }
      }
 
      if (plusminus == 1)
      {
        wrong2 = answer - wrong2;
 
        //making sure incorrect answers do not repeat
        while(wrong2 == wrong1){
 
          wrong2 = wrong2 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong2 == answer){
 
           wrong2 = wrong2 + 1;
           }
 
      }
 
 
      //Calculating the value of incorrect answer 3 (wrong3)
 
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong3 = answer + wrong3;
 
        //making sure incorrect answers do not repeat
        while(wrong3 == wrong2){
 
          wrong3 = wrong3 + 1;
          }
           
           while(wrong3 == wrong1){
 
          wrong3 = wrong3 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong3 == answer){
 
           wrong3 = wrong3 + 1;
 
          }
      }
 
      if (plusminus == 1)
      {
        wrong3 = answer - wrong3;
 
        //making sure incorrect answers do not repeat
        while(wrong3 == wrong2){
 
          wrong3 = wrong3 + 1;
          }
           
           while(wrong3 == wrong1){
 
          wrong3 = wrong3 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong3 == answer){
 
           wrong3 = wrong3 + 1;
 
          }
      }
 
 
    //Displaying the problem and the 4 multiple choice possibilities
 
    //Clearing the board and displaying the problem
    LCD.Clear();
    LCD.SetFontColor(LCD.Gray);
    LCD.WriteAt(a,60,60);
    LCD.WriteAt("-", 120, 60);
    LCD.WriteAt(b, 140, 60);
    LCD.WriteAt("-", 200, 60);
    LCD.WriteAt(c, 220, 60);
 
    //Displaying '(A)' '(B)' '(C)' and '(D)' to the screen which will be followed by answer choices
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt("(A) ",60,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt("(B) ",60,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt("(C) ",60,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt("(D) ",60,220);
 
 
    //Randomly assigning the correct answer to either '(A)', '(B)', '(C)', or '(D)'
     ansplace = RandInt() % 4;
 
 switch (ansplace)
 {
 
     //Case 0: the correct answer goes in the '(A)' slot
    case 0:  
    
    //Setting the correct answer to '(A)' and the wrong answers to the other slots
    
    LCD.SetFontColor(LCD.Blue); 
    LCD.WriteAt(answer,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong1,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong2,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
     
    //Setting countdown equal to timeadd
     countdown = timeadd;
      
    //start a for loop to display the countdown
 
    for (i=0; i <= timeadd; i++){
       
        //make a rectangle to cover the past number                 LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
    
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
 
       LCD.Touch(&x,&y);
 
    
    //Setting a while loop to wait for user to select an answer
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>114 && y<146)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if (x>60 && x<120 && y>145 && y<236)
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative so it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
  
      //Returning change in points
      return ChangeInPoints;
 
     
  }
 
  //if the user clicks but not on one of the answer choices
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
           
}
      
 
  break;
 
 
  
  //Case 1: the correct answer goes in the '(B)' slot
    case 1:  
    
    //Setting the correct answer to '(A)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(answer,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong2,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
    countdown = timeadd;
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
        //make a rectangle to cover the past number        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
        //subtract one from the variable countdown
        countdown = countdown - 1;
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
    
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>145 && y<176)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
       
    }
    
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if ((x> 60 && x< 120 && y>175 && y<236) || (x> 60 && x< 120 && y<146 && y>115))
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the scren 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
      
  }
 
//if the user clicks but not on one of the answer choices or failed to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
}
 
  break;
  
     
//Case 2: the correct answer goes in the '(C)' slot
    case 2:  
    
    //Setting the correct answer to '(C)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong2,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(answer,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
 
    //setting countdown equal to timeadd
      countdown = timeadd;
 
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
 
        //make a rectangle to cover the past number        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
 
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
   
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>175 && y<206)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if ((x> 60 && x< 120 && y>205 && y<236) || (x> 60 && x< 120 && y<176 && y>115))
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
     
  }
  
  //if the user clicks but not on one of the answer choices
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
}
 
  break;
 
 
     //Case 3: the correct answer goes in the '(D)' slot
    case 3:  
    
    //Setting the correct answer to '(D)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong2,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong3,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(answer,90,220);
 
     //Displaying how much time is left to answer the question
    countdown = timeadd;
 
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
        //make a rectangle to cover the past number           LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
 
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
   
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>205 && y<236)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
       
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if (x>60 && x<120 && y<206 && y>115)
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
     
  }
     
    //if the user clicks but not on one of the answer choices
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
} 
 
  break;
    }
}
 
 
//Generate Division
int generateDivision(int difficulty){
    //declare variables
    int x = -10000 , y = - 10000;
    //declare variables for the random question generation, while loop, and points to return
    int i,countdown,ChangeInPoints,plusminus,ansplace;
    float a,b,wrong1, wrong2, wrong3,answer;
    //declare time variables
    double timeadd;
 
    //create a switch case statement to check for the difficulty
    switch (difficulty){
        //if the difficulty is 1 (worth 100 points)
        case 1:
            //generate 3 random integers between 1 and 10
            a = (RandInt() % 10) + 1;
            b = (RandInt() % 10) + 1;
            
            //set the time given to 10 seconds
            timeadd = 10;
            break;
        //if the difficulty is 2 (worth 200 points)
        case 2:
            //generate 3 random integers between 1 and 100
            a = (RandInt() % 100) + 1;
            b = (RandInt() % 100) + 1;
            //set the time given to 10 seconds
            timeadd = 10;
            break;
        //if the difficulty is 3 (worth 300 points)
        case 3:
            //generate 3 random integers between 1 and 1000
            a = (RandInt() % 1000) + 1;
            b = (RandInt() % 1000) + 1;
            //set the time given to 8 seconds
            timeadd = 8;
            break;
        //if the difficulty is 4 (worth 400 points)
        case 4:
            //generate 3 random integers between 1 and 10000
            a = (RandInt() % 10000) + 1;
            b = (RandInt() % 10000) + 1;
            //set the time given to 6 seconds
            timeadd = 6;
            break;
    }
    //store the answer
    answer = a / b;
 
      //Calculating how far off the incorrect answers will be from the answer
      //Incorrect answers are no more than 3 whole numbers away from the correct answer
      wrong1 = RandInt() % 2 + 1;
      wrong2 = RandInt() % 2 + 1;
      wrong3 = RandInt() % 2 + 1;
 
      //Calculating the value of incorrect answer 1 (wrong1)
      
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong1 = answer + wrong1;    
      }
 
      if (plusminus == 1)
      {
        wrong1 = answer - wrong1;
      }
 
      //Calculating the value of incorrect answer 2 (wrong2)
 
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong2 = answer + wrong2;
        
        //making sure incorrect answers do not repeat
        while(wrong2 == wrong1){
 
          wrong2 = wrong2 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong2 == answer){
 
           wrong2 = wrong2 + 1;
 
          }
      }
 
      if (plusminus == 1)
      {
        wrong2 = answer - wrong2;
 
        //making sure incorrect answers do not repeat
        while(wrong2 == wrong1){
 
          wrong2 = wrong2 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong2 == answer){
 
           wrong2 = wrong2 + 1;
           }
 
      }
 
 
      //Calculating the value of incorrect answer 3 (wrong3)
 
      plusminus = RandInt() % 2;
 
      if (plusminus == 0)
      {
        wrong3 = answer + wrong3;
 
        //making sure incorrect answers do not repeat
        while(wrong3 == wrong2){
 
          wrong3 = wrong3 + 1;
          }
           
           while(wrong3 == wrong1){
 
          wrong3 = wrong3 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong3 == answer){
 
           wrong3 = wrong3 + 1;
 
          }
      }
 
      if (plusminus == 1)
      {
        wrong3 = answer - wrong3;
 
        //making sure incorrect answers do not repeat
        while(wrong3 == wrong2){
 
          wrong3 = wrong3 + 1;
          }
           
           while(wrong3 == wrong1){
 
          wrong3 = wrong3 + 1;
          }
          
          //making sure adjustment does not repeat the real answer
          while(wrong3 == answer){
 
           wrong3 = wrong3 + 1;
 
          }
      }
 
 
    //Displaying the problem and the 4 multiple choice possibilities
 
    //Clearing the board and displaying the problem
    LCD.Clear();
    LCD.SetFontColor(LCD.Gray);
    LCD.WriteAt(a,55,60);
    LCD.WriteAt("/",140, 60);
    LCD.WriteAt(b, 160, 60);
 
    //Displaying '(A)' '(B)' '(C)' and '(D)' to the screen which will be followed by answer choices
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt("(A) ",60,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt("(B) ",60,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt("(C) ",60,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt("(D) ",60,220);
 
 
    //Randomly assigning the correct answer to either '(A)', '(B)', '(C)', or '(D)'
     ansplace = RandInt() % 4;
 
 switch (ansplace)
 {
 
     //Case 0: the correct answer goes in the '(A)' slot
    case 0:  
    
    //Setting the correct answer to '(A)' and the wrong answers to the other slots
    
    LCD.SetFontColor(LCD.Blue); 
    LCD.WriteAt(answer,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong1,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong2,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
     
    //Setting countdown equal to timeadd
     countdown = timeadd;
      
    //start a for loop to display the countdown
 
    for (i=0; i <= timeadd; i++){
       
        //make a rectangle to cover the past number                 LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
    
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
 
       LCD.Touch(&x,&y);
 
    
    //Setting a while loop to wait for user to select an answer
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>114 && y<146)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if (x>60 && x<120 && y>145 && y<236)
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative so it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
  
      //Returning change in points
      return ChangeInPoints;
 
     
  }
 
  //if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
           
}
      
 
  break;
 
 
  
  //Case 1: the correct answer goes in the '(B)' slot
    case 1:  
    
    //Setting the correct answer to '(A)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(answer,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong2,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
    countdown = timeadd;
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
        //make a rectangle to cover the past number        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
        //subtract one from the variable countdown
        countdown = countdown - 1;
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
    
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>145 && y<176)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
       
    }
    
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer or answered incorrectly
  if ((x> 60 && x< 120 && y>175 && y<236) || (x> 60 && x< 120 && y<146 && y>115))
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the scren 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
      
  }
 
//if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
}
 
  break;
  
     
//Case 2: the correct answer goes in the '(C)' slot
    case 2:  
    
    //Setting the correct answer to '(C)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong2,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(answer,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(wrong3,90,220);
 
     //Displaying how much time is left to answer the question
 
    //setting countdown equal to timeadd
      countdown = timeadd;
 
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
 
        //make a rectangle to cover the past number        LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
 
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
   
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>175 && y<206)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if ((x> 60 && x< 120 && y>205 && y<236) || (x> 60 && x< 120 && y<176 && y>115))
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
     
  }
  
  //if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
}
 
  break;
 
 
     //Case 3: the correct answer goes in the '(D)' slot
    case 3:  
    
    //Setting the correct answer to '(D)' and the wrong answers to the other slots
    LCD.SetFontColor(LCD.Blue);
    LCD.WriteAt(wrong1,90,130);
 
    LCD.SetFontColor(LCD.Scarlet);
    LCD.WriteAt(wrong2,90,160);
 
    LCD.SetFontColor(LCD.Green);
    LCD.WriteAt(wrong3,90,190);
 
    LCD.SetFontColor(PURPLE);
    LCD.WriteAt(answer,90,220);
 
     //Displaying how much time is left to answer the question
    countdown = timeadd;
 
    //start a for loop to display the countdown
    for (i=0; i <= timeadd; i++){
        //make a rectangle to cover the past number           LCD.SetDrawColor(LCD.Black);
        LCD.FillRectangle(290,0,29,20);
 
        //write the countdown to the screen
        LCD.WriteAt(countdown,300,0);
 
        //subtract one from the variable countdown
        countdown = countdown - 1;
 
        //make sure that countdown displays to the screen for one second
        Sleep(1.0);
    }
   
 
    //Setting a while loop to wait for user to select an answer
     LCD.Touch(&x,&y);
 
     //Displaying 'Correct!!!' to the screen and adding the correct point value to the users score if they answer correctly
 
    //Checking if the user clicked on the correct answer
    if (x> 60 && x< 120 && y>205 && y<236)
    {
 
       //Clearing the screen
       LCD.Clear();
 
       //Writing 'Correct!!!' to the screen
       LCD.SetFontColor(LCD.Green);
       LCD.WriteAt("Correct!!!",140,120);
 
       //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
       
 
       //Setting ChangeInPoints to the displayed value so it is added to the users score
       ChangeInPoints = (difficulty * 100);
       
 
       //Returning ChangeInPoints
        return ChangeInPoints ; 
 
       
    }
    
    //Displaying 'Incorrect :(' and deducting the correct point value user's score if they answer incorrectly
 
    //Checking if the user selected an incorrect answer
  if (x>60 && x<120 && y<206 && y>115)
  {
      //Clearing the screen
      LCD.Clear();
 
      //Writing 'Incorrect :(' to the screen 
      LCD.SetFontColor(LCD.Red);
      LCD.WriteAt("Incorrect :(",140,120);
 
      //Only having ‘Correct!!!’ display for 4 seconds
       Sleep(4.0);
 
      //Setting ChangeinPoints to the displayed point value but negative to it is deducted from the user's score
      ChangeInPoints = 0 - (difficulty * 100);
 
      //Returning change in points
      return ChangeInPoints ;
 
     
  }
     
    //if the user clicks but not on one of the answer choices or fails to answer
else{
    //erase the question off the screen
            LCD.Clear();
            //write to screen that they ran out of time
            LCD.Write("You ran out of time!");
            //Keep the message on the screen for 4 seconds
            Sleep(4.0);
            //set ChangeInPoints to negative value
            ChangeInPoints = 0 - (difficulty*100);
            //returnChangeInPoints
            return ChangeInPoints ;
            
} 
 
  break;
    }
}
 
 
 
 //Generate Multiplication
int GenerateMultiplication(int difficulty){return 1;}
 
//Generate Subtraction
int GenerateSubtraction(int difficulty){return 1;}
 
//Generate Division
int GenerateDivision(int difficulty){return 1;}
 
//main
int main()
{
    //declare variables and data types
    int x, y, a, b;
    double timeNow, timeEnd;
    Game game;
    Stats stats;
    int scores[5]={0,0,0,0,0};
    int gamesPlayed=0;
    //loading screen
    LCD.Clear();
    //create the background graphics
    for (a=0;a<=5;a++){
        for (b=0; b<=7; b++){
            if (b%2 == 0){
                if (a%2 == 0){
                    LCD.SetDrawColor(NAVY);
                    LCD.FillRectangle(b*40,a*40,40,40);
                    //LCD.SetDrawColor(BLUE);
                    //LCD.DrawLine(b*40,(a*40)+40,(b*40)+40,(a*40));
                }
                else{
                    LCD.SetDrawColor(BLUE);
                    LCD.FillRectangle(b*40,a*40,40,40);
                    //LCD.SetDrawColor(NAVY);
                    //LCD.DrawLine(b*40,a*40,(b*40)+40,(a*40)+40);
                }
            }
            else{
                if (a%2 == 0){
                    LCD.SetDrawColor(BLUE);
                    LCD.FillRectangle(b*40,a*40,40,40);
                    //LCD.SetDrawColor(NAVY);
                    //LCD.DrawLine(b*40,(a*40)+40,(b*40)+40,(a*40));
                }
                else{
                    LCD.SetDrawColor(NAVY);
                    LCD.FillRectangle(b*40,a*40,40,40);
                   // LCD.SetDrawColor(BLUE);
                    //LCD.DrawLine(b*40,a*40,(b*40)+40,(a*40)+40);
                }
            }
        }
    }
    //heart graphic
    LCD.SetDrawColor(WHITE);
    for (int c=260;c<=303;c++){
        if (c<=276){
            LCD.DrawPixel(c,170);
            LCD.DrawPixel(c,171);
            LCD.DrawPixel(c,172);
            LCD.DrawPixel(c,173);
        }
        else if (c>=288){
            LCD.DrawPixel(c,170);
            LCD.DrawPixel(c,171);
            LCD.DrawPixel(c,172);
            LCD.DrawPixel(c,173);
        }
    }
    for (int r=256;r<=259;r++){
        for(int s=174;s<=178;s++){
            LCD.DrawPixel(r,s);
        }
    }
    for (int r=304;r<=307;r++){
        for(int s=174;s<=178;s++){
            LCD.DrawPixel(r,s);
        }
    }
    for (int r=252;r<=255;r++){
        for(int s=179;s<=198;s++){
            LCD.DrawPixel(r,s);
        }
    }
    for (int r=308;r<=311;r++){
        for(int s=179;s<=198;s++){
            LCD.DrawPixel(r,s);
        }
    }    
      for (int r=256;r<=259;r++){
        for(int s=199;s<=202;s++){
            LCD.DrawPixel(r,s);
        }
    }
    for (int r=304;r<=307;r++){
        for(int s=199;s<=202;s++){
            LCD.DrawPixel(r,s);
        }
    }
    for (int q=0;q<=5;q++){
        for (int r=260+(q*4);r<=263+(q*4);r++){
            for (int s=203+(q*4);s<=206+(q*4);s++){
                LCD.DrawPixel(r,s);
            }
        }
    }
    for (int q=0;q<=5;q++){
        for (int r=300-(q*4);r<=303-(q*4);r++){
            for (int s=203+(q*4);s<=206+(q*4);s++){
                LCD.DrawPixel(r,s);
            }
        }
    }
    for (int r=277;r<=280;r++){
        for (int s=174; s<=178; s++){
            LCD.DrawPixel(r,s);
        }
    }
    for (int r=285;r<=288;r++){
        for (int s=174; s<=178; s++){
            LCD.DrawPixel(r,s);
        }
    }
    for (int r=281;r<=284;r++){
        for (int s=179; s<=182; s++){
            LCD.DrawPixel(r,s);
        }
    }
 
    LCD.WriteAt("Loading JeoPARTY!", 90, 90);
    LCD.SetDrawColor(GRAY);
    LCD.FillRectangle(70, 130, 180, 20);
    LCD.SetDrawColor(RED);
    for(int i=1; i<7; i++)
    {
        timeNow=TimeNow();
        timeEnd=timeNow+1;
        while(timeNow<timeEnd)
        {
            LCD.FillRectangle(70, 130, i*30, 20);
            timeNow=TimeNow();
        }
    }
    //loop continuously
    while(1){
    //display menu
    DrawMenu();
    //wait for a touch
    while(!LCD.Touch(&x, &y)){}
    //top quarter, play game
    if(y<YMAX/4)
    {
        LCD.Clear();
        //store games score in a vector of 5 most recent scores
        scores[gamesPlayed]=game.Play();
        gamesPlayed++;
        if(gamesPlayed==5)
        {
           gamesPlayed=0;
        }
    }
    //top half, stats
    else if(y<YMAX/2)
    {
        LCD.Clear();
        stats.Show(scores);
    }
    //top three quarters, instructions
    else if(y<YMAX*3/4)
    {
        LCD.Clear();
        ShowInstructions();
    }
    //bottom fourth, credits
    else
    {
        ShowCredits();
    }
    }
}