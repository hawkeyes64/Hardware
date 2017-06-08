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
#include <Servo.h>

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
 *        Mic
 * 15     A0       Analogue I/O pin
 * 53     D0       Digital I/O pin
**********************************/

// Note: array elements are the arduino board pins
LiquidCrystal lcd(8,9,10,11,12,13);

/******( Declaration of Joystick Objects )********/
int volume = 0;
int triggerState = 0;

/******( Declaration and Initialisation of Board Objects )********/

String str_Title = "Volume Listener";
String str_v;
String str_t;

/***************************************************************************
 * Function Name: updateCoordinates
 * Purpose : To obtain x and y coordinates interpreted from the joystick
 * Parameters: None
 * Return: None
**************************************************************************/

void updateCoordinates(){
  volume = analogRead(A15);
  triggerState = digitalRead(53);
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
  delay(10);
  
  updateCoordinates();
  
  str_v = "v: " + intToString(volume);
  str_t = "t: " + intToString(triggerState);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(A15, INPUT);
  pinMode(53, INPUT_PULLUP);
  
  lcd.begin(16, 2); //LCD begins. dimension: 16x2(Coluns x Rows)  
  lcd.setCursor(0, 0); // Positions the cursor in the first column (0) and the firt row (1) at LCD  
  lcd.print(str_Title); //LCD write comand
}

void loop() {
  lcd.setCursor(0, 1); // Positions the cursor on the fourteenth column (07) and the second line (1) LCD    

  updateLCDMessage();

  lcd.print(str_v + " " + str_t); // Write the current value of the count variable in the LCD   
}
