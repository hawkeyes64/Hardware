/*********************************
 * Filename: LCDTest.ino
 * Author  : Jesmigel A. Cantos
 * Purpose : To manipulate a 16x2 LCD display
 * Sample  : Custom clock
 * Style   : Modular coding
**********************************/

/******(Declaration of Objects)********/
// include the library code:
#include <LiquidCrystal.h>

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
**********************************/
// Note: array elements are the arduino board pins
LiquidCrystal lcd(8,9,10,11,12,13);

String str_Title = "Are you ready?";
String str_Time = "";

//Entire variable declaration(time)
int int_sec=0,int_min=0,int_hr=0;

/*************************************/

/**********( adjustTimeVariables )***********
 * Purpose: To modify each time variable
 *  accordingly
/********************************************/
void adjustTimeVariables(){
  delay(1000); // Waits for 1 second   
  int_sec += 1;

  if(int_sec > 59){
    int_sec = 0;
    int_min += 1;
  }

  if(int_min > 59){
    int_min = 0;
    int_hr += 1;    
  }

  
  if(int_hr > 23){
    int_hr = 0;
    int_min = 0;
    int_sec = 0; 
  }
}

/****************( setStringTime )***********
 * Purpose: To interpret integer values and
 *  translate them to a time format with a 
 *  string datatype
/********************************************/
String setStringTime(int int_sec,int int_min,int int_hr){
  String tmp_str = "";
  
  if(int_hr > 9){
    tmp_str = String(int_hr);
  }else{
    tmp_str = "0" + String(int_hr);
  }

  tmp_str += ":";
  
  if(int_min > 9){
    tmp_str += String(int_min);
  }else{
    tmp_str += "0" + String(int_min);
  }
  
  tmp_str += ":";
  
  if(int_sec > 9){
    tmp_str += String(int_sec);
  }else{
    tmp_str += "0" + String(int_sec);
  }

  return tmp_str;
}

void setup() {
  lcd.begin(16, 2); //LCD begins. dimension: 16x2(Coluns x Rows)  
  lcd.setCursor(0, 0); // Positions the cursor in the first column (0) and the firt row (1) at LCD  
  lcd.print(str_Title); //LCD write comand
  lcd.setCursor(0, 1); // Positions the cursor in the first column (0) and the second row (1) at LCD  
  lcd.print("Timer:"); // LCD write command "GarageLab"
}

void loop() {
  lcd.setCursor(07, 1); // Positions the cursor on the fourteenth column (07) and the second line (1) LCD   

  str_Time = setStringTime(int_sec,int_min,int_hr);
  
  lcd.print(str_Time); // Write the current value of the count variable in the LCD   
  adjustTimeVariables();
}
