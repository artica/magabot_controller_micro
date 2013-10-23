
int state1 = HIGH;      // the current state1 of the output pin
int reading1;           // the current reading1 from the input pin
int previous1 = LOW;    // the previous1 reading1 from the input pin
long time1 = 0;         // the last time1 the output pin was toggled
long debounce1 = 200;   // the  time1, increase if the output flickers

int state2 = HIGH;      // the current state1 of the output pin
int reading2;           // the current reading1 from the input pin
int previous2 = LOW;    // the previous1 reading1 from the input pin
long time2 = 0;         // the last time1 the output pin was toggled
long debounce2 = 200;   // the  time1, increase if the output flickers

int state3 = HIGH;      // the current state1 of the output pin
int reading3;           // the current reading1 from the input pin
int previous3 = LOW;    // the previous1 reading1 from the input pin
long time3 = 0;         // the last time1 the output pin was toggled
long debounce3 = 200;   // the  time1, increase if the output flickers

int state4 = HIGH;      // the current state1 of the output pin
int reading4;           // the current reading1 from the input pin
int previous4 = LOW;    // the previous1 reading1 from the input pin
long time4 = 0;         // the last time1 the output pin was toggled
long debounce4 = 200;   // the  time1, increase if the output flicker


void updateDeb()
{
  if(joyStickState)
  {
   // active1();
   // active2();
   // active3();
   // active4();
  }
  else
  {
    debouncer1();
    debouncer2();
    debouncer3();
    debouncer4();
  }
}

void active1()
{
  state2 = HIGH;
  state3 = HIGH;
  state4 = HIGH;
}

void active2()
{
  state1 = HIGH;
  state3 = HIGH;
  state4 = HIGH;
}

void active3()
{
  state2 = HIGH;
  state1 = HIGH;
  state4 = HIGH;
}

void active4()
{
  state2 = HIGH;
  state3 = HIGH;
  state1 = HIGH;
}
void debouncer1() {
   reading1 = digitalRead(PIN_BUTTON_01);
  // if we just pressed the button (i.e. the input went from LOW to HIGH),
  // and we've waited long enough since the last press to ignore any noise...  
  if (reading1 == HIGH && previous1 == LOW && millis() - time1 > debounce1) {
    // ... invert the output
    if (state1 == HIGH) {
      state1 = LOW;
      active1();
      v1= -MAX_VELOCITY;
      v2= MAX_VELOCITY;
      pressedButton = 3;
    } else {
      state1 = HIGH;
      v1=0;
      v2=0;
    }
    // ... and remember when the last button press was
    time1 = millis();    
  }
  previous1 = reading1;
}
void debouncer2() {
   reading2 = digitalRead(PIN_BUTTON_03);
  // if we just pressed the button (i.e. the input went from LOW to HIGH),
  // and we've waited long enough since the last press to ignore any noise...  
  if (reading2 == HIGH && previous2 == LOW && millis() - time2 > debounce2) {
    // ... invert the output
    if (state2 == HIGH) {
      state2 = LOW;
      active2();
      v1= MAX_VELOCITY;
      v2= -MAX_VELOCITY;
      pressedButton = 1;
    } else {
      state2 = HIGH;
      v1= 0;
      v2= 0;
    }
    // ... and remember when the last button press was
    time2 = millis();    
  }
  previous2 = reading2;
}
void debouncer3() {
   reading3 = digitalRead(PIN_BUTTON_04);
  // if we just pressed the button (i.e. the input went from LOW to HIGH),
  // and we've waited long enough since the last press to ignore any noise...  
  if (reading3 == HIGH && previous3 == LOW && millis() - time3 > debounce3) {
    // ... invert the output
    if (state3 == HIGH) {
      state3 = LOW;
      active3();
      v1=MAX_VELOCITY;
      v2=MAX_VELOCITY;
      pressedButton = 4;
    } else {
      state3 = HIGH;
      v1= 0;
      v2= 0;
    }
    // ... and remember when the last button press was
    time3 = millis();    
  }
  previous3 = reading3;
}
void debouncer4() {
   reading4 = digitalRead(PIN_BUTTON_02);
  // if we just pressed the button (i.e. the input went from LOW to HIGH),
  // and we've waited long enough since the last press to ignore any noise...  
  if (reading4 == HIGH && previous4 == LOW && millis() - time4 > debounce4) {
    // ... invert the output
    if (state4 == HIGH) {
      state4 = LOW;
      active4();
      v1= -MAX_VELOCITY;
      v2= -MAX_VELOCITY;
      pressedButton = 2;
    } else {
      state4 = HIGH;
      v1= 0;
      v2= 0;
    }
    // ... and remember when the last button press was
    time4 = millis();    
  }
  previous4 = reading4;
}

void Motors(int left, int right)
{
    
    while(Serial1.available()!=0)
      Serial.println(Serial1.read());
    
    /*
    //This is for the ORIGINAL MAGABOT
    int val = map(Esplora.readSlider(),1023,0,-5,5);
    if(val >0 && left >0)
      left += val;
    else if (val >0 && right >0)
      right += val;
    else if (val <0 && left <0)
      left += val;
    else if(val <0 && right <0)
      right+= val;
    */
    
    // this is for the CUSTOM MAGABOT with Arduino Leonardo and a L298 driver
    
    slider_val = analogRead(SLIDER);
    
    if (slider_val > SLIDER_THRESHOLD_LOW && slider_val < SLIDER_THRESHOLD_HIGH)
      motorBalance = 0;
    
    if (slider_val < SLIDER_THRESHOLD_LOW)
      motorBalance = map(slider_val, SLIDER_THRESHOLD_LOW, 0, 0, -100);
    
    if (slider_val > SLIDER_THRESHOLD_HIGH)
      motorBalance = map(slider_val, SLIDER_THRESHOLD_HIGH, 1023, 0, 200);

    
    
    if(motorBalance < 0 && left < 0)
      left -= motorBalance;
      
    else if (motorBalance < 0 && right < 0)
      right -= motorBalance;
    
    else if (motorBalance > 0 && left > 0)
      left -= motorBalance;
    
    else if(motorBalance > 0 && right > 0)
      right -= motorBalance;
      
     left = constrain(left, -255, 255);
     right = constrain(right, -255, 255);
     
     
    
    if (activeComm)
    {
      digitalWrite(13, HIGH);
      //This is the Serial1 protocol to Magabot LOW LEVEL comm
      Serial1.write(0x86);
      Serial1.write((byte)(left>>8));
      Serial1.write((byte)(left&0xFF));
      Serial1.write((byte)(right>>8));
      Serial1.write((byte)(right&0xFF));
    delay(25);
    }
   
   if (debug) 
   {
      Serial.print(analogRead(SLIDER));
      Serial.print(" ");
      Serial.print(motorBalance);
      Serial.print("  ||  ");
      Serial.print(x_position);
      Serial.print(" ");
      Serial.print(y_position);
      Serial.print("  ||  ");
      Serial.print(left);
      Serial.print(" ");
      Serial.print(right);
      Serial.print("  ||  ");
      Serial.print(joyStickState);
      debugFunction(pressedButton);
    }
   
}

void debugFunction(int bt)
{
  Serial.print("  ||  ");
  Serial.print("button: ");
  Serial.println(bt);
  delay(100);
}

