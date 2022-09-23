

void stack_step01() {
  // carriage lifts up when btn is pressed to top position then stops
  if (E_Stop_Pulled(&E_Stop)) {

    goUP();
    do {
      checkMove();
      delay(25);
      if (!E_Stop_Pulled(&E_Stop)) {
        checkMove();
        stopMovment();
      }
      Serial.println("step 01");
    } while (!btnPressed(&at_Top) && E_Stop_Pulled(&E_Stop) && e_stopPressed == false);
    checkMove();
    if (e_stopPressed == false) {
      turnOff(&drive_UP);
      delay(200);
      turnOff(&up_dwn_break);
      step01 = true;
    }

  }
  checkMove();
  stopMovment();
}

void stack_step02() {
  // carriage goes forward to max forward postion then stops
  if (E_Stop_Pulled(&E_Stop) && step01 == true) {

    goFWD();
    do {
      checkMove();
      delay(25);
      if (!E_Stop_Pulled(&E_Stop)) {
        checkMove();
        stopMovment();
      }
      Serial.println("step 01");
    } while (!btnPressed(&at_Front) && E_Stop_Pulled(&E_Stop) && e_stopPressed == false);
    checkMove();
    if (e_stopPressed == false) {
      turnOff(&drive_FWD);
      delay(425);  // timer for turning on the brake
      turnOff(&fwd_rev_break);
      step02 = true;
    }

  }
  checkMove();
  stopMovment();
}
void stack_step03() {
  // carriage goes down to layer 1 or unit level postion then stops
  if (E_Stop_Pulled(&E_Stop) && step02 == true) {
    checkMove();
    goDWN();

    while (!btnPressed(&unit_Level) && !btnPressed(&at_Bottom) && e_stopPressed == false) {
      delay(25);
      checkMove();
      if (!E_Stop_Pulled(&E_Stop)) {
        checkMove();
        stopMovment();
      }
      Serial.println("step 01");
    }

    if (e_stopPressed == false) {
      turnOff(&drive_DWN);
      delay(350);
      turnOff(&up_dwn_break);
      step03 = true;
    }

  }
  checkMove();
  stopMovment();
}
void stack_step04() {
  // carriage moves backwards to max back position then stops
  if (E_Stop_Pulled(&E_Stop) && step03 == true) {
    checkMove();
    goREV();
    do {
      checkMove();
      delay(25);
      if (!E_Stop_Pulled(&E_Stop)) {
        checkMove();
        stopMovment();
      }
      Serial.println("step 01");
    } while (!btnPressed(&at_Back) && e_stopPressed == false);
    checkMove();
    if (e_stopPressed == false) {
      turnOff(&drive_REV);
      delay(600);
      turnOff(&fwd_rev_break);
      step04 = true;
    }


  }
  checkMove();
  stopMovment();
}
void stack_step05() {
  // carriage goes up until reaches the home height position
  if (E_Stop_Pulled(&E_Stop) && step04 == true) {

    goUP();
    do {
      checkMove();
      delay(25);
      if (!E_Stop_Pulled(&E_Stop)) {
        checkMove();
        stopMovment();
      }
    } while (!btnPressed(&at_Home) && E_Stop_Pulled(&E_Stop) && e_stopPressed == false);
    checkMove();
    if (e_stopPressed == false) {
      turnOff(&drive_UP);
      delay(200);
      turnOff(&up_dwn_break);
      stackComplete = true;
    }


  }
  checkMove();
  stopMovment();
}

void stopMovment() {
  checkMove();
  turnOff(&drive_DWN);
  turnOff(&drive_UP);
  turnOff(&drive_REV);
  turnOff(&drive_FWD);
  turnOff(&fwd_rev_break);
  turnOff(&up_dwn_break);

  if (!E_Stop_Pulled(&E_Stop)) {
    e_stopPressed == false;
  }
}

void goFWD() {
  if (!btnPressed(&at_Front)) {
    turnOff(&drive_REV);
    turnOn(&drive_FWD);
    turnOn(&fwd_rev_break);
  }
}

void goREV() {
  if (!btnPressed(&at_Back)) {
    turnOff(&drive_FWD);
    turnOn(&drive_REV);
    turnOn(&fwd_rev_break);
  }
}

void goUP() {
  if (!btnPressed(&at_Top)) {
    turnOff(&drive_DWN);
    turnOn(&drive_UP);
    turnOn(&up_dwn_break);
  }
}

void goDWN() {
  if (!btnPressed(&at_Bottom)) {
    turnOff(&drive_UP);
    turnOn(&drive_DWN);
    turnOn(&up_dwn_break);
  }
}
