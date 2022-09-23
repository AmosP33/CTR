void stack_manualMode() {
  // switch into manual mode and use joysticks to control carriage movement

  // drive_UP  drive_DWN  up_dwn_break  drive_FWD  drive_REV  fwd_rev_break
  //
  // joy_Manual_UP       joy_Manual_FWD
  // joy_Manual_DWN      joy_Manual_REV
  //
  // at_Top  at_Bottom  at_Home  at_Front  at_Back

  Serial.println("Entering Manual Mode");

  while (btnPressed(&manual_Mode)) {


    //===================================
    // UP/DWN Drive manaul controls

    if (btnPressed(&joy_Manual_UP) && !btnPressed(&at_Top)) {
      while (btnPressed(&joy_Manual_UP) && !btnPressed(&at_Top)) {
        goUP();
      }
      turnOff(&drive_UP);
      delay(200);
      turnOff(&up_dwn_break);
    }
    //===================================

    //===================================
    if (btnPressed(&joy_Manual_DWN) && !btnPressed(&at_Bottom)) {
      while (btnPressed(&joy_Manual_DWN) && !btnPressed(&at_Bottom) && !btnPressed(&unit_Level)) {
        goDWN();
      }
      turnOff(&drive_DWN);
      delay(185);
      turnOff(&up_dwn_break);
    }
    //===================================


    //===================================
    // FWD/REV Drive manaul controls
    if (btnPressed(&joy_Manual_FWD) && !btnPressed(&at_Front)) {
      while (btnPressed(&joy_Manual_FWD) && !btnPressed(&at_Front)) {
        goFWD();
      }
      turnOff(&drive_FWD);
      delay(425);
      turnOff(&fwd_rev_break);
    }
    //===================================


    //===================================
    if (btnPressed(&joy_Manual_REV) && !btnPressed(&at_Back)) {
      while (btnPressed(&joy_Manual_REV) && !btnPressed(&at_Back)) {
        goREV();
      }
      turnOff(&drive_REV);
      delay(475);
      turnOff(&fwd_rev_break);
    }
    //===================================




  } // end of while loop

  stopMovment();


}
