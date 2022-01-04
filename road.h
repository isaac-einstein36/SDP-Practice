class ROAD
{

public:
        ROAD(int startY);
        ROAD(int startY, bool motion);
        void drawRoad();

        

private:
        int roadStartY;
        int roadHeight;
        int numCars;
        bool animated;
};
