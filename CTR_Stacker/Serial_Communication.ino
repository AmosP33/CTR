
void serialEvent() {
	while (Serial.available()) {
		// get the new byte:
		char inChar = (char)Serial.read();
		// add it to the inputString:
		inputString += inChar;
		// if the incoming character is a newline, set a flag
		// so the main loop can do something about it:
		if (inChar == '\n') {
			stringComplete = true;
		}
	}

	if (stringComplete)
	{
		getCommand();
	}
}

void getCommand()
{
	if (inputString.length() > 0)
	{
		commandString = inputString.substring(1, 6);
		commandStateString = inputString.substring(6, 8);
		Serial.print(commandString);
		Serial.print("  ");
		Serial.println(commandStateString);

		commands(commandString, commandStateString);
	}
}

void commands(String pos, String state) {

	String tempSlot = pos.substring(1);
	String tempPos = pos.substring(3, 5);
	String tempState = state.substring(0, 2);

	Serial.print(tempSlot);
	Serial.print("  ");
	Serial.print(tempPos);
	Serial.print("  ");
	Serial.println(tempState);

	int tempslot = tempSlot.toInt();
	int temppos  = tempPos.toInt();

	Serial.print(tempslot);
	Serial.print("  ");
	Serial.print(temppos);
	Serial.print("  ");
	Serial.println(tempState);

	// #S5P16ON
	// # S 5 P 1 6 O N
	// 0 1 2 3 4 5 6 7 8 9

	if (tempState == "ON") 
	{
		//temp->state = true;
		P1.writeDiscrete(ON, tempslot, temppos);
	}
	else
	{
		//temp->state = false;
		P1.writeDiscrete(OFF, tempslot, temppos);
	}
		

	

	inputString = "";
	stringComplete = false;

}

