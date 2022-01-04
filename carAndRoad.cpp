// #include "includes.h"

// /**
//  * USED FOR STATIC BACKGROUND IMAGES 
//  * SUCH AS DRAWING A ROAD, CAR, TREE, ETC.
//  */

// /**
//  * Draws a road at a set starting height. 
//  * Takes up the whole screen (320 pixels wide).
//  * @param startHeight starting height of the road
//  * @param roadHeight height of road
//  * @param slowMotion Road can annimate when drawn if boolean "true" is sent to function
// */
// void drawRoad(int roadStartY, int roadHeight, bool animate)
// {
//         // Draw road for car to drive on
//         int numSpots = 5, roadWidth = XDIM, spotLength = 30, spotHeight = 10;

//         LCD.SetFontColor(GRAY);
//         LCD.FillRectangle(0, roadStartY, roadWidth, roadHeight);
//         LCD.Update();

//         // For loop to draw each rectangle
//         for (int i = 0; i < 5; i++)
//         {
//                 // Draws a yellow rectangle of height 10, centered along the midline of the road
//                 LCD.SetFontColor(YELLOW);
//                 LCD.FillRectangle(i * (roadWidth / numSpots) + 15, ((roadStartY + (roadHeight / 2)) - (spotHeight / 2)), spotLength, spotHeight);

//                 // Slow for the animation
//                 if (animate)
//                 {
//                         // Wait a second before drawing each line
//                         usleep(0.6 * 1E6);
//                         LCD.Update();
//                 }
//         }
//         // Make sure everything is drawn to the screen
//         LCD.Update();
// }
