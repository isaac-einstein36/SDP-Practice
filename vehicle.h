class VEHICLE
{

public:
        VEHICLE(char type[], int startY);
        void drawVehicle();
        void eraseVehicle();
        void moveVehicle();
        void setDelay(float delay);

        // Make the car's position and delay time accessible outside of the class
        int carPosX;
        int carPosY;
        float delayTime;

private:
        char type[100];
        char name[100];
};
