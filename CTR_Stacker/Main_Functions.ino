
void turnOn(output* temp) {
  temp->state = true;
  P1.writeDiscrete(ON, temp->slot, temp->pos);
}
void turnOff(output* temp) {
  temp->state = false;
  P1.writeDiscrete(OFF, temp->slot, temp->pos);
}
//================================================


bool isOn(output temp) {
  return temp.state == true;
}
bool isOff(output temp) {
  return temp.state == false;
}
//==============================



bool btnPressed(input* temp) {
  if (P1.readDiscrete(temp->slot, temp->pos) == true) {
    temp->state = true;
    return (P1.readDiscrete(temp->slot, temp->pos));
  }
  else {
    temp->state = false;
    return (P1.readDiscrete(temp->slot, temp->pos));
  }
}
//===================================================

bool btnPulled(input* temp) {
  if (P1.readDiscrete(temp->slot, temp->pos) == true) {
    temp->state = true;
    return (P1.readDiscrete(temp->slot, temp->pos));
  }
  else {
    temp->state = false;
    return (P1.readDiscrete(temp->slot, temp->pos));
  }
}
//===================================================


bool E_Stop_Pulled(input* temp) {
  if (P1.readDiscrete(temp->slot, temp->pos) == true) {
    temp->state = true;
    return (P1.readDiscrete(temp->slot, temp->pos));
  }
  else {
    temp->state = false;
    return (P1.readDiscrete(temp->slot, temp->pos));
  }
}
//===================================================


bool btnNO(input* temp) {
  //Serial.println("i got in");
  if (P1.readDiscrete(temp->slot, temp->pos) == true) {
    temp->state = true;
    Serial.println("did i make it here");
    while (P1.readDiscrete(temp->slot, temp->pos) == true) {
      delay(25);
      Serial.println("waiting to release btn");
    }
    
    Serial.println("done waiting");
  }
}
//===================================================


void onoff(output* temp) {
  temp->state = !temp->state;
  //Serial.println(temp->state);
  if (temp->state == true) {
    //Serial.println("ON");
    P1.writeDiscrete(ON, temp->slot, temp->pos);
  }
  if (temp->state == false) {
    //Serial.println("OFF");
    P1.writeDiscrete(OFF, temp->slot, temp->pos);
  }
}
//===================================================
