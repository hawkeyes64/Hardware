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
#include <IRremote.h>

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

int input_pin = 2; //set D10 as input signal pin
IRrecv irrecv(input_pin);
decode_results signals;

/******( Declaration of Joystick Objects )********/
int volume = 0;
int triggerState = 0;

/******( Declaration and Initialisation of Board Objects )********/

String str_Title = "LCD Listener";
String str_sig = "";

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

void setup() {
  Serial.begin(115200);
   
  lcd.begin(16, 2); //LCD begins. dimension: 16x2(Coluns x Rows)  
  lcd.setCursor(0, 0); // Positions the cursor in the first column (0) and the firt row (1) at LCD  
  lcd.print(str_Title); //LCD write comand

  irrecv.enableIRIn(); // enable input from IR receiver
}

void loop() {
  lcd.setCursor(0, 1); // Positions the cursor on the fourteenth column (07) and the second line (1) LCD    

  lcd.print(str_sig); // Write the current value of the count variable in the LCD   

  if (irrecv.decode(&signals)) 
  {
    lcd.print("                ");
    str_sig = "val: " + intToString(signals.value);
    irrecv.resume(); // get the next signal
  }

  delay(10);
}
