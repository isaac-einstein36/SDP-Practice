class VEHICLE
{

public:
        VEHICLE(char type[], int startY);
        void drawVehicle();
        void eraseVehicle();
        void moveVehicle();
        void setDelay(float delay);

        // Make the car's position accessible outside of the class
        int carPosX;
        int carPosY;

private:
        float delayTime;
        char type[100];
        char name[100];
};
