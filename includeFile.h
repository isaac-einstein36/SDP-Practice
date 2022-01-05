// HEADERS
#include "simulator_libraries/FEHLCD.h"
#include "simulator_libraries/FEHImages.h"
#include "simulator_libraries/FEHFile.h"

#include <string>
#include <unistd.h>
#include <iostream>
#include "time.h"
#include "fstream"
#include <array>
using namespace std;

#include "globals.h"
#include "road.h"
#include "vehicle.h"

// FUNCTIONS
// Menu functions
const char *runMenu();
void initializeMenu();
void menuGraphics();
void carWithTitle(VEHICLE);
void credits();
const char *showMenuOptions();
