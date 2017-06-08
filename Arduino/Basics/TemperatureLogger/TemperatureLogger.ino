

int tempSec = 0;    //Aurduino analog pin connects to LM35 output pin
int val = 0;        //Raw data from LM35 by analogRead(tempSec);

int totalsec = 0;   //to set the intervals for writing to output file
int sec = 1000;     //1000 milisecs

void ToSerialMonitor(String UnitType, float val);
void ToOutFile(String UnitType, float val);

/*****************************************************************/
/* To make a led blink
/****************************************************************/
void IWantToBlink();
int ledSwitch = 0;   //[0-false][1-true]
int ledPin = 13;     //13 digital pin on arduino board      

void setup() {
  
  /**************************************/
  /* put your setup code here, to run once:  
  /**************************************/
  
  Serial.begin(9600);

  /****************************************************************/
  /* http://electronics.stackexchange.com/questions/131326/excessively-high-temperature-reading-with-lm35
  /* voltage reference of 5v //analogReference(INTERNAL)
  /* if 1v use analogReference(INTERNAL1V1)
  /* temp = (1.1 * analogRead(tempSec) * 100.0) / 1024;
  /****************************************************************/

  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(tempSec);

  /***Equations***/
  float mv = (1.1 * analogRead(tempSec) * 100.0) / 1024;
  float cel = mv/3;
  float farh = (cel*9)/5 + 32;
  
  ToSerialMonitor("*C",cel);
  //ToSerialMonitor("*F",farh);

  /****************************************************************/
  /* after every 5 sec, record data to output file
  /****************************************************************/
  
  if(tempSec == 10){
    
    /***********************************/
    /*Call the write function
    /***********************************/
    ToOutFile("*C",cel); 

    /***********************************/
    /*Call the blink function
    /***********************************/
    
    IWantToBlink();
    
    /***********************************/
    /*Reset the count
    /***********************************/
    tempSec = 0;
  }
  
  tempSec += (sec/1000); //increment by 1 sec
  delay(sec/10);
}

void ToSerialMonitor(String UnitType, float val){
  
  /****************************************************************/
  /* Declaration and Initialisation of output string Variable
  /****************************************************************/
  
  String outstring = "Temperature = ";
  
  /**************************************************/
  /* Initialisation of output string Variable
  /**************************************************/
  
  outstring.concat(val);
  Serial.println(outstring + " " + UnitType);  
}

void ToOutFile(String UnitType, float val){
}

void IWantToBlink(){
  if(ledSwitch == 0){
    digitalWrite(ledPin,HIGH);
    ledSwitch = 1;    
  }
  else if(ledSwitch == 1){
    digitalWrite(ledPin,LOW);
    ledSwitch = 0;
  }  
}
