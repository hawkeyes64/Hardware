/***************************************************************************
 * Filename: Project1.ino
 * Author  : Jesmigel A. Cantos
 * Purpose : To make the 16x2 lCD liston to data coming from a joystick
 * Sample  : Custom clock
 * Style   : Modular coding
**************************************************************************/

/******(Declaration of LCD Objects)********/
// include the LCD library:
#include <LiquidCrystal.h>
#include <Stepper.h>
 
/*********************************
 * initialize the lcd object with 
 * the numbers of the interface pins
 * Pin assignment
 * AB     LCD     Description
 * 08     04      Register Select
 * 09     06      Enable Signal
 * 10     11      Digital I/O pin
 * 11     12      Digital I/O pin
 * 12     13      Digital I/O pin
 * 13     14      Digital I/O pin
 *        Stepper Motor
 * 50     1       Digital I/O pin
 * 51     2       Digital I/O pin
 * 52     3       Digital I/O pin
 * 53     4       Digital I/O pin
**********************************/

// Note: array elements are the arduino board pins
LiquidCrystal lcd(8,9,10,11,12,13);

int in1Pin = 50;
int in2Pin = 51;
int in3Pin = 52;
int in4Pin = 53;
 
Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);  

/******( Declaration of Joystick Objects )********/
int xPin = A1;
int yPin = A0;
int buttonPin = 7;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

/******( Declaration and Initialisation of Board Objects )********/

String str_Title = "JoystickListener";
String str_x;
String str_y;
String str_b;

/***************************************************************************
 * Function Name: updateCoordinates
 * Purpose : To obtain x and y coordinates interpreted from the joystick
 * Parameters: None
 * Return: None
**************************************************************************/

void updateCoordinates(){
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);
}

/***************************************************************************
 * Function Name: intToString
 * Purpose : To convert coordinate of integer datatype to a string datatype
 * Parameters: integer tmp_int
 * Return: string tmp_int // max of 4 characters - 0000 to 1024
**************************************************************************/

String intToString(int tmp_int){
  String tmp_string = "";
  for(int ctr = String(tmp_int).length();ctr<4;ctr++){
    tmp_string += "0";
  }
  tmp_string += String(tmp_int);
  return tmp_string;
}

/***************************************************************************
 * Function Name: updateLCDMessage
 * Purpose : Print characters to string, max length is 16
 * Parameters: None
 * Return: None
**************************************************************************/

void updateLCDMessage(){
  delay(100);
  
  updateCoordinates();
  
  str_x = "x:" + intToString(xPosition);
  str_y = "y:" + intToString(yPosition);
  str_b = "b" + String(buttonState);
  
}

void setup() {
  Serial.begin(115200);
  
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP); 

  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);

  motor.setSpeed(30);
  
  lcd.begin(16, 2); //LCD begins. dimension: 16x2(Coluns x Rows)  
  lcd.setCursor(0, 0); // Positions the cursor in the first column (0) and the firt row (1) at LCD  
  lcd.print(str_Title); //LCD write comand  
}

void loop() {
  lcd.setCursor(0, 1); // Positions the cursor on the fourteenth column (07) and the second line (1) LCD    

  updateLCDMessage();

  Serial.println(str_x + " " + str_y + " " + str_b);
  
  lcd.print(str_x + " " + str_y + " " + str_b); // Write the current value of the count variable in the LCD   

  if (xPosition > 750)
  {
    motor.step(200);
  }  

  if (xPosition < 250)
  {
    motor.step(-200);
  }
}
