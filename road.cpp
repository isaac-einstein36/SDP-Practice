// #include "includeHeaders.h"
#include "includeFile.h"

ROAD::ROAD(int start)
{

        roadStartY = start;
        roadHeight = 50;
        numCars = 0;
        animated = false;
}

ROAD::ROAD(int start, bool pause)
{
        roadStartY = start;
        roadHeight = 50;
        numCars = 0;
        animated = pause;
}

/**
 * Draws a road at a set starting height. 
 * Takes up the whole screen (320 pixels wide).
*/

void ROAD::drawRoad()
{
        // Draw road for car to drive on
        int numSpots = 5, roadWidth = XDIM, spotLength = 30, spotHeight = 10;

        LCD.SetFontColor(GRAY);
        LCD.FillRectangle(0, roadStartY, roadWidth, roadHeight);
        LCD.Update();

        // For loop to draw each rectangle
        for (int i = 0; i < 5; i++)
        {
                // Draws a yellow rectangle of height 10, centered along the midline of the road
                LCD.SetFontColor(YELLOW);
                LCD.FillRectangle(i * (roadWidth / numSpots) + 15, ((roadStartY + (roadHeight / 2)) - (spotHeight / 2)), spotLength, spotHeight);

                // Slow for the animation
                if (animated)
                {
                        // Wait a second before drawing each line
                        usleep(carSpeed * 1E6);
                        LCD.Update();
                }
        }
        // Make sure everything is drawn to the screen
        LCD.Update();
}