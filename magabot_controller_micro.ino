
#define X_THRESHOLD_LOW 500
#define X_THRESHOLD_HIGH 530    
#define Y_THRESHOLD_LOW 500
#define Y_THRESHOLD_HIGH 530

#define SLIDER_THRESHOLD_LOW 450
#define SLIDER_THRESHOLD_HIGH 550

// buttons
const byte PIN_BUTTON_01 = 5;
const byte PIN_BUTTON_02 = 9;
const byte PIN_BUTTON_03 = 8;
const byte PIN_BUTTON_04 = 6;

//joystick
const byte PIN_ANALOG_X = 1;
const byte PIN_ANALOG_Y = 0;

const byte SLIDER = 4;
int slider_val;
int motorBalance;


// max and min vel to ORIGINAL MAGABOT CODE
//int MAX_VELOCITY = 8;
//int MIN_VELOCITY = -8;

// max and min vel to GUIBOT CUSTOM MAGABOT CODE
int MAX_VELOCITY = 255;
int MIN_VELOCITY = -255;

int fwd = false, bwd = false, left = false, right = false;
int v1=0;
int v2=0;

boolean debug = false;
boolean activeComm = true;

int pressedButton = 0;

void setup() {
  
  Serial1.begin(19200);
  Serial.begin(19200);
  
  pinMode(PIN_BUTTON_01, INPUT_PULLUP);
  pinMode(PIN_BUTTON_02, INPUT_PULLUP);
  pinMode(PIN_BUTTON_03, INPUT_PULLUP);
  pinMode(PIN_BUTTON_04, INPUT_PULLUP);
  
  pinMode(3, OUTPUT);
  digitalWrite(3,HIGH);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  delay(100);
}
void loop() 
{
  /**/
  checkJoystick();
  
  updateDeb();
  
  Motors(v1, v2);
  /**/
  
  /*
  Motors(255,-255);
  delay(5000);
  Motors(-255,255);
  delay(2000);
  /**/
}
boolean joyStickState = true;
int oldv1=0;
int oldv2=0;

int x_position;
int y_position;

void checkJoystick()
{
  int linearVelocity, rotationVelocity;
  
  x_position = map(analogRead(PIN_ANALOG_X), 0, 1023, 1023, 0);        // read the joystick's X position
  y_position = map(analogRead(PIN_ANALOG_Y), 0, 1023, 1023, 0);         // read the joystick's Y position
  //Serial1.println(x_position);
  //Serial1.println(x_position);
  if (x_position > X_THRESHOLD_LOW && x_position < X_THRESHOLD_HIGH && y_position > Y_THRESHOLD_LOW && y_position < Y_THRESHOLD_HIGH) 
  {
    if(joyStickState)
    {
      v1=oldv1;
      v2=oldv2;
      joyStickState = false;
    }
  }
  else {
    if(!joyStickState)
    {
      oldv1=v1;
      oldv2=v2;
    }
    joyStickState = true;
    int linearVelocity = map(y_position, 0, 1023, MIN_VELOCITY, MAX_VELOCITY);
    int rotationVelocity = map(x_position, 1023, 0, MIN_VELOCITY/1.5, MAX_VELOCITY/1.5);

    v1 = linearVelocity + rotationVelocity;  
    v2 = -(linearVelocity - rotationVelocity);
  }  
}
