// Visual Micro is in vMicro>General>Tutorial Mode
//
/*
    Name:     CTR_Stacker.ino
    Created:	9/27/2020 2:28:35 PM
    Author:   Amos Parmenter

    This is for Stacker #2 with the jump deck
*/

// Define User Types below here or use a .h file
#include <P1AM.h>

//

// --- this section is for communication to Application ---

String inputString = "";         // a string to hold incoming data
String commandString = "";		 // a string to hold command
String commandStateString = "";  // a string to hold state of command
boolean stringComplete = false;  // whether the string is complete
boolean isConnected = false;
//-----------------------------------------------------------

#define ON HIGH
#define OFF LOW
#define delayTime 250

bool menu1 = false;
bool menu2 = false;
bool menuRunText = false;
int menuSelection;

bool jumpCheck = false;
bool stacking = false;
bool e_stopPressed = false;
bool jumpingControl = false;

bool step01 = false;
bool step02 = false;
bool step03 = false;
bool step04 = false;
bool stackComplete = false;

const int slot1 = 1;
const int slot2 = 2;
const int slot3 = 3;
const int slot4 = 4;
const int slot5 = 5;

const int pos01 = 1;
const int pos02 = 2;
const int pos03 = 3;
const int pos04 = 4;
const int pos05 = 5;
const int pos06 = 6;
const int pos07 = 7;
const int pos08 = 8;
const int pos09 = 9;
const int pos10 = 10;
const int pos11 = 11;
const int pos12 = 12;
const int pos13 = 13;
const int pos14 = 14;
const int pos15 = 15;
const int pos16 = 16;

struct input {
  int slot;
  int pos;
  bool state;
};

struct output {
  int slot;
  int pos;
  bool state;
  bool trip;
};


// Sensor Inputs Slot 1 ------------------------
struct input E_Stop         = { slot1, pos01, false };
struct input stack          = { slot1, pos02, false };
struct input s1Input03      = { slot1, pos03, false };
struct input deck_Jump_ControlMode  = { slot1, pos04, false };
struct input joy_Roll_FWD   = { slot1, pos05, false };
struct input joy_Manual_UP  = { slot1, pos06, false };
struct input joy_Manual_FWD = { slot1, pos07, false };
struct input joy_Roll_REV   = { slot1, pos08, false };
struct input joy_Manual_REV = { slot1, pos09, false };
struct input joy_Manual_DWN = { slot1, pos10, false };
struct input black_Btn      = { slot1, pos11, false };
struct input blue_Btn       = { slot1, pos12, false };
struct input manual_Mode    = { slot1, pos13, false };
struct input unit_Out       = { slot1, pos14, false };
struct input jump_All_Up    = { slot1, pos15, false };
struct input jump_All_Down  = { slot1, pos16, false };
//----------------------------------------------

// Sensor Inputs Slot 2 ------------------------
struct input s2Input01  = { slot2, pos01, false };
struct input s2Input02  = { slot2, pos02, false };
struct input at_Bottom  = { slot2, pos03, false };  // sensor seeing up/down carriage max bottom
struct input at_Home    = { slot2, pos04, false };  // sensor seeing up/down carriage at home/middle position
struct input at_Top     = { slot2, pos05, false };  // sensor seeing up/down carriage max up
struct input s2Input06  = { slot2, pos06, false };
struct input at_Front   = { slot2, pos07, false };  // sensor seeing fwd/rev carriage max forward
struct input at_Back    = { slot2, pos08, false };  // sensor seeing fwd/rev carriage max reverse
struct input s2Input09  = { slot2, pos09, false };
struct input s2Input10  = { slot2, pos10, false };
struct input s2Input11  = { slot2, pos11, false };
struct input s2Input12  = { slot2, pos12, false };
struct input s2Input13  = { slot2, pos13, false };
struct input s2Input14  = { slot2, pos14, false };
struct input s2Input15  = { slot2, pos15, false };
struct input unit_Level = { slot2, pos16, false };  // sees the level of the unit when stacking
//----------------------------------------------

// Relay Outputs Slot 3 ---------------------------------
// Freq Drive Control Relays ----------------------------
struct output drive_UP      = { slot3, pos01, false, false };   // UP/DWN Drive UP
struct output drive_DWN     = { slot3, pos02, false, false };   // UP/DWN Drive DWN
struct output s3Relay04      = { slot3, pos03, false, false };   // UP/DWN Drive External Reset
struct output up_dwn_break  = { slot3, pos04, false, false };
struct output drive_FWD     = { slot3, pos05, false, false };   // FWD/REV Drive FWD
struct output drive_REV     = { slot3, pos06, false, false };   // FWD/REV Drive REV
struct output fwd_rev_break = { slot3, pos07, false, false };   // FWD/REV Drive External Reset
struct output s3Relay08     = { slot3, pos08, false, false };
//-------------------------------------------------------

// Relay Outputs Slot 4 ---------------------------------
// Motor Control Relays ---------------------------------
struct output jump_deck_motor_FWD = { slot4, pos01, false, false };  // motor control of starter
struct output chain_deck_motor    = { slot4, pos02, false, false };  // motor control of starter
struct output jump_deck_motor_REV = { slot4, pos03, false, false };
struct output s4Relay04 = { slot4, pos04, false, false };
struct output s4Relay05 = { slot4, pos05, false, false };
struct output s4Relay06 = { slot4, pos06, false, false };
struct output s4Relay07 = { slot4, pos07, false, false };
struct output s4Relay08 = { slot4, pos08, false, false };
//-------------------------------------------------------

// Relay Outputs Slot 5 ---------------------------------
struct output outfeed_Rolls_FWD = { slot5, pos01, false, false };   // control of mag in other stacker to move one set of rolls FWD
struct output jump_Up           = { slot5, pos02, false, false };   // air selnoid to lift deck up and down to push out the unit
struct output outfeed_Rolls_REV = { slot5, pos03, false, false };   // control of mag in other stacker to move one set of rolls REV
struct output s5Relay04 = { slot5, pos04, false, false };
struct output s5Relay05 = { slot5, pos05, false, false };
struct output s5Relay06 = { slot5, pos06, false, false };
struct output s5Relay07 = { slot5, pos07, false, false };
struct output s5Relay08 = { slot5, pos08, false, false };
struct output s5Relay09 = { slot5, pos09, false, false };
struct output s5Relay10 = { slot5, pos10, false, false };
struct output s5Relay11 = { slot5, pos11, false, false };
struct output s5Relay12 = { slot5, pos12, false, false };
struct output s5Relay13 = { slot5, pos13, false, false };
struct output s5Relay14 = { slot5, pos14, false, false };
struct output s5Relay15 = { slot5, pos15, false, false };
struct output s5Relay16 = { slot5, pos16, false, false };
//-------------------------------------------------------


// The setup() function runs once each time the micro-controller starts
void setup()
{

  Serial.begin(115200);

  while (!P1.init()) {
    ; //Wait for Modules to Sign on
  }
  Serial.setTimeout(25);


}

// Add the main program code into the continuous loop() function
void loop()
{
  // this is for the communication
  // between the Ardunio and the PC Application
  //serialEvent();
  //Serial.write("Hello World");

  if (!E_Stop_Pulled(&E_Stop)) {
    e_stopPressed = false;
    turnOff(&chain_deck_motor);
  }

  if (E_Stop_Pulled(&E_Stop))
  {

    infeedChain();  // turns on and off the chain infeed deck to the stacker
    jumpUnit();     // pushes a unit to the roll case
    rollFWD();      // Outfeed roll case FWD
    rollREV();      // Outfeed roll case REV

    // this section is for manual mode and can be used to reset the stacker or make adjustments
    while (btnPressed(&manual_Mode)) {
      stack_manualMode();
    }



    if (btnPressed(&stack) || stacking == true) {

      stacking = false;
      step01 = false;
      step02 = false;
      step03 = false;
      step04 = false;
      stackComplete = false;

      stack_step01();

      stack_step02();

      stack_step03();

      stack_step04();

      stack_step05();

    }

  }


  stacking = false;

}
