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
    if (E_Stop_Pulled(&E_Stop)) {
      //===================================
      // UP/DWN/FWD/REV Drive manaul controls
      manual_UP();
      manual_DWN();
      manual_FWD();
      manual_REV();

      manual_JumpControl();


    } // end of while loop




  }
}


void manual_FWD() {
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
}

void manual_REV() {
  if (btnPressed(&joy_Manual_REV) && !btnPressed(&at_Back)) {
    while (btnPressed(&joy_Manual_REV) && !btnPressed(&at_Back)) {
      goREV();
    }
    turnOff(&drive_REV);
    delay(475);
    turnOff(&fwd_rev_break);
  }
  //===================================

}

void manual_UP() {
  if (btnPressed(&joy_Manual_UP) && !btnPressed(&at_Top)) {
    while (btnPressed(&joy_Manual_UP) && !btnPressed(&at_Top)) {
      goUP();
    }
    turnOff(&drive_UP);
    delay(200);
    turnOff(&up_dwn_break);
  }
  //===================================
}

void manual_DWN() {
  if (btnPressed(&joy_Manual_DWN) && !btnPressed(&at_Bottom)) {
    while (btnPressed(&joy_Manual_DWN) && !btnPressed(&at_Bottom) && !btnPressed(&unit_Level)) {
      goDWN();
    }
    turnOff(&drive_DWN);
    delay(185);
    turnOff(&up_dwn_break);
  }
  //===================================
}


void manual_JumpControl() {
  checkMove();

  if (btnNO(&deck_Jump_ControlMode)) {
    jumpingControl = true;
    while (jumpingControl == true) {

      // lift the jump deck
      if (isOff(jump_Up)) {
        turnOn(&jump_Up);
      }

      if (btnPressed(&joy_Roll_FWD) && btnPressed(&jump_All_Up) && E_Stop_Pulled(&E_Stop)) {
        turnOn(&jump_deck_motor_FWD);
      } else {
        turnOff(&jump_deck_motor_FWD);
      }

      if (btnPressed(&joy_Roll_REV ) && btnPressed(&jump_All_Up) && E_Stop_Pulled(&E_Stop)) {
        turnOn(&jump_deck_motor_REV );
      } else {
        turnOff(&jump_deck_motor_REV);
      }


      if (!E_Stop_Pulled(&E_Stop)) {
        jumpingControl = false;
        stopMovment();
      }

      if (btnNO(&deck_Jump_ControlMode)) {
        jumpingControl = false;
        turnOff(&jump_Up);
      }

    }
  }
}
