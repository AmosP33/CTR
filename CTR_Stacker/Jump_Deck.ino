


void jumpUnit() {
  // checks to make sure there is nothing in the way before moving the
  // unit out. Then pushes the unit out on the jump deck then lowers it
  // onto the roll case to be rolled out

  // black_Btn  jump_All_Up  jump_All_Down  unit_Out
  // jump_deck_motor  jump_Up

  if (btnNO(&black_Btn)) {
    if (btnPressed(&jump_All_Down)) {

      // lift the jump deck
      if (isOff(jump_Up)) {
        turnOn(&jump_Up);
      }

      while (!btnPressed(&jump_All_Up)) {
        checkMove();
        // waiting for the jump deck to be all the way up
        // add in e-stop or break ability or cancel if gets stuck
        delay(100);

        if (!E_Stop_Pulled(&E_Stop)) {
          break;
        }
      }

      do {
        checkMove();
        if (isOff(jump_deck_motor)) {
          turnOn(&jump_deck_motor);
        }

        if (!E_Stop_Pulled(&E_Stop)) {
          break;
        }
        // add in e-stop and cancel function here

      } while (!btnPressed(&unit_Out));

      turnOff(&jump_deck_motor);
      turnOff(&jump_Up);
      jumpCheck = true;

      do
      {
        delay(25);
        infeedChain();

        if (btnPressed(&jump_All_Down))
        {
          for (int i = 0; i < 30; i++)
          {
            delay(100);
            infeedChain();
            if (!E_Stop_Pulled(&E_Stop)) {
              break;
            }
          }
          jumpCheck = false;
        }

        if (!E_Stop_Pulled(&E_Stop)) {
          break;
        }
      } while (jumpCheck == true);

    }
  }
}






void rollCase01() {
  // controls the roll cae before the jump deck


}

void rollCase02() {
  // controls the roll case in front of the jump deck


}

void rollCase03() {
  // controls the roll case after the jump roll section


}
