

void infeedChain() {
  // turns on and off the infeed chains
  if (E_Stop_Pulled(&E_Stop))
  {
    if (btnNO(&blue_Btn)) {
      onoff(&chain_deck_motor);
      Serial.println("I turn on or off");
    }
  }
}


void rollFWD() {

  if (btnPressed(&joy_Roll_FWD) && btnPressed(&jump_All_Down) && E_Stop_Pulled(&E_Stop)) {
    turnOn(&outfeed_Rolls_FWD);
  } else {
    turnOff(&outfeed_Rolls_FWD);
  }

}


void rollREV() {

  if (btnPressed(&joy_Roll_REV ) && btnPressed(&jump_All_Down) && E_Stop_Pulled(&E_Stop)) {
    turnOn(&outfeed_Rolls_REV );
  } else {
    turnOff(&outfeed_Rolls_REV);
  }

}

void checkRollsMove() {
  rollREV();
  rollFWD();
}


void checkMove() {
  checkRollsMove();
  infeedChain();
}
