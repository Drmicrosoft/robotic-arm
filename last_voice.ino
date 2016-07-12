/**
  EasyVR Tester

  Dump contents of attached EasyVR module
  and exercise it with playback and recognition.

  Serial monitor can be used to send a few basic commands:
  '?' - display the module setup
  'l' - cycles through available languages
  'c' - cycles through available command groups
  'b' - cycles through built-in word sets
  'g' - cycles through custom grammars
  's123' - play back sound 123 if available (or beep)
  'd0123456789ABCD*#' - dials the specified number ('_' is dial tone)
  'k' - starts detection of tokens
  '4' or '8' - sets token length to 4 or 8 bits
  'n123' - play back token 123 (not checked for validity)
  'm1' - set mic distance to HEADSET
  'm2' - set mic distance to ARMS_LENGTH (default)
  'm3' - set mic distance to FAR_MIC
  'w' - enter sleep mode without audio wakeup (any command interrupts)
  'ww' - enter sleep mode with "whistle" wakeup
  'w2' - enter sleep mode with "double-clap" wakeup
  'w3' - enter sleep mode with "triple-clap" wakeup
  'wl' - enter sleep mode with "loud-sound" wakeup
  'r12' - record message 12 if empty
  'p12' - play back message 12 if recorded
  'e12' - erase message 12

  With EasyVR Shield, the green LED is ON while the module
  is listening (using pin IO1 of EasyVR).
  Successful recognition is acknowledged with a beep.
  Details are displayed on the serial monitor window.

**
  Example code for the EasyVR library v1.7.1
  Written in 2015 by RoboTech srl for VeeaR <http:://www.veear.eu>

  To the extent possible under law, the author(s) have dedicated all
  copyright and related and neighboring rights to this software to the
  public domain worldwide. This software is distributed without any warranty.

  You should have received a copy of the CC0 Public Domain Dedication
  along with this software.
  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
*/

  // Shield Jumper on SW (using pins 12/13 or 8/9 as RX/TX)
  #include "SoftwareSerial.h"
  SoftwareSerial port(12, 13);

#include "EasyVR.h"

EasyVR easyvr(port);

int8_t bits = 4;
int8_t set = 0;
int8_t group = 0;
uint32_t mask = 0;
uint8_t train = 0;
int8_t grammars = 0;
int8_t lang = 0;
char name[33];
bool useCommands = false;
bool useGrammars = true;
bool useTokens = false;
bool isSleeping = false;
bool isBusy = false;



#include <Servo.h> 
 
Servo myservo0;
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
int pos = 0;
int led1=26;
int gnd1=27;
int led2=28;
int gnd2=29;
int led3=30;
int gnd3=31;
// create servo object to control a servo 
                // a maximum of eight servo objects can be created 
int pos0=90,pos1=90,pos2=90,pos3=90,pos4=90,pos5=90; 

  char x ;
int i = 0;
int y0=90,y1=90,y2=90,y3=90,y4=90,y5=90;

void setup()
{
  // setup  serial port
 pinMode(8,OUTPUT);
                             Serial.begin(9600);
  pinMode(led1,OUTPUT);
    pinMode(gnd1,OUTPUT);

  pinMode(led2,OUTPUT);
    pinMode(gnd2,OUTPUT);

  pinMode(led3,OUTPUT);
    pinMode(gnd3,OUTPUT);


  // bridge mode?
  int mode = easyvr.bridgeRequested(Serial);
  switch (mode)
  {
  case EasyVR::BRIDGE_NONE:
    // setup EasyVR serial port
    port.begin(9600);
    // run normally
    break;
   
  case EasyVR::BRIDGE_NORMAL:
    // setup EasyVR serial port (low speed)
    port.begin(9600);
    // soft-connect the two serial ports ( and EasyVR)
    easyvr.bridgeLoop(Serial);
    // resume normally if aborted
    break;
   
  case EasyVR::BRIDGE_BOOT:
    // setup EasyVR serial port (high speed)
    port.begin(115200);
    // soft-connect the two serial ports ( and EasyVR)
    easyvr.bridgeLoop(Serial);
    // resume normally if aborted
    break;
  }

  // initialize EasyVR 
  while (!easyvr.detect())
  {
    delay(1000);
  }

  easyvr.setPinOutput(EasyVR::IO1, LOW);
 
  easyvr.setTimeout(5);
  lang = EasyVR::ENGLISH;
  easyvr.setLanguage(lang);

  int16_t count = 0;


  group = 0;
  set = 3;

  mask |= 1; // force to use trigger
  isSleeping = false;

    easyvr.stop();
    easyvr.setMicDistance(1);

}






const char* ws0[] =
{
  "ROBOT",
};
const char* ws1[] =
{
  "ACTION",
  "MOVE",
  "TURN",
  "RUN",
  "LOOK",
  "ATTACK",
  "STOP",
  "HELLO",
};
const char* ws2[] =
{
  "LEFT",
  "RIGHT",
  "UP",
  "DOWN",
  "FORWARD",
  "BACKWARD",
};
const char* ws3[] =
{
  "ZERO",
  "ONE",
  "TWO",
  "THREE",
  "FOUR",
  "FIVE",
  "SIX",
  "SEVEN",
  "EIGHT",
  "NINE",
  "TEN",
};
const char** ws[] = { ws0, ws1, ws2, ws3 };






int readNum()
{
  int rx;
  int num = 0;
  delay(5);
  while ((rx = Serial.read()) >= 0)
  {
    delay(5);
    if (isdigit(rx))
      num = num * 10 + (rx - '0');
    else
      break;
  }
  return num;
}





bool checkMonitorInput()
{

  if (Serial.available() <= 0)
    return false;

  // check console commands
  int16_t rx = 'b';
  if (rx == '?')
  {
    setup();
    return true;
  }
  if (isSleeping)
  {
    // any character received will exit sleep
    isSleeping = false;
    easyvr.stop();
    Serial.println(F("Forced wake-up!"));
    return true;
  }
  if (rx == 'l')
  {
    easyvr.stop();
    lang++;
    if (easyvr.setLanguage(lang) || easyvr.setLanguage(lang = 0))
    {
      Serial.print(F("Language set to "));
      Serial.println(lang);
    }
    else
      Serial.println(F("Error while setting language!"));
  }
  if (rx == 'b')
  {
    useTokens = false;
    useCommands = false;
    useGrammars = true;

  }
  if (rx == 'g' && grammars > 4)
  {
    useTokens = false;
    useCommands = false;
    useGrammars = true;
    set++;
    if (set >= grammars)
      set = 4;
  }
  if (rx == 'c')
  {
    useTokens = false;
    useCommands = true;
    useGrammars = false;
    do
    {
      group++;
      if (group > EasyVR::PASSWORD)
        group = 0;
    }
    while (!((mask >> group) & 1));
  }
  if (rx == 'k')
  {
    useTokens = true;
    useCommands = false;
    useGrammars = false;
  }
  if (rx == '4')
  {
    bits = 4;
  }
  if (rx == '8')
  {
    bits = 8;
  }
  if (rx == 'n')
  {
    int16_t num = readNum();
    Serial.print(F("Play token "));
    Serial.println(num);
    easyvr.stop();
    easyvr.sendToken(bits, num);
  }
  if (rx == 's')
  {
    int16_t num = 0;
    delay(5);
    while ((rx = Serial.read()) >= 0)
    {
      delay(5);
      if (isdigit(rx))
        num = num * 10 + (rx - '0');
      else
        break;
    }
    Serial.print(F("Play sound "));
    Serial.println(num);
    easyvr.stop();
    easyvr.playSound(num, EasyVR::VOL_DOUBLE);
  }
  if (rx == 'd')
  {
    easyvr.stop();
    Serial.println(F("Play tones:"));
    int16_t num = 0;
    delay(5);
    while ((rx = Serial.read()) >= 0)
    {
      delay(5);
      if (isdigit(rx))
        num = rx - '0';
      else if (rx == '*')
        num = 10;
      else if (rx == '#')
        num = 11;
      else if (rx >= 'A' && rx <= 'D')
        num = rx - 'A';
      else if (rx == '_')
        num = -1;
      else
        break;
      Serial.print(num);
      if (easyvr.playPhoneTone(num, 3))
        Serial.println(F(" OK"));
      else
        Serial.println(F(" ERR"));
    }
  }
  if (rx == 'm')
  {
    int16_t num = readNum();
    Serial.print(F("Mic distance "));
    Serial.println(num);
    easyvr.stop();
    easyvr.setMicDistance(num);
  }
  if (rx == 'w')
  {
    int8_t mode = 0;
    delay(5);
    while ((rx = Serial.read()) >= 0)
    {
      delay(5);
      if (rx == 'w')
        mode = EasyVR::WAKE_ON_WHISTLE;
      if (rx == '2')
        mode = EasyVR::WAKE_ON_2CLAPS;
      if (rx == '3')
        mode = EasyVR::WAKE_ON_3CLAPS;
      if (rx == 'l')
        mode = EasyVR::WAKE_ON_LOUDSOUND;
    }
    Serial.print(F("Sleep mode "));
    Serial.println(mode);
    easyvr.stop();
    easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off
    isSleeping = easyvr.sleep(mode);
    return true;
  }
  if (rx == 'r')
  {
    int8_t num = readNum();
    Serial.print(F("Record (5 seconds) message "));
    Serial.println(num);
    easyvr.stop();
    easyvr.recordMessageAsync(num, 8, 5);
    useTokens = false;
    useCommands = false;
    useGrammars = false;
    isBusy = true;
    return true;
  }
  if (rx == 'p')
  {
    int8_t num = readNum();
    Serial.print(F("Play message "));
    Serial.println(num);
    easyvr.stop();
    easyvr.playMessageAsync(num, EasyVR::SPEED_NORMAL, EasyVR::ATTEN_NONE);
    useTokens = false;
    useCommands = false;
    useGrammars = false;
    isBusy = true;
    return true;
  }
  if (rx == 'e')
  {
    int8_t num = readNum();
    Serial.print(F("Erase message "));
    Serial.println(num);
    easyvr.stop();
    easyvr.eraseMessageAsync(num);
    useTokens = false;
    useCommands = false;
    useGrammars = false;
    isBusy = true;
    return true;
  }

  if (rx >= 0)
  {
    easyvr.stop();
    Serial.flush();
    return true;
  }
  return false;
}








void loop()
{
  digitalWrite(8,HIGH);
    digitalWrite(gnd1,LOW);
        digitalWrite(gnd2,LOW);
            digitalWrite(gnd3,LOW);

 digitalWrite(led1,LOW);
        digitalWrite(led2,LOW);
            digitalWrite(led3,LOW);




    digitalWrite(8,LOW);

  checkMonitorInput();

  if (!isSleeping && !isBusy)
  {
    easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)
    if (useTokens)
    {
      Serial.print(F("Detect a "));
      Serial.print(bits);
      Serial.println(F(" bit token ..."));
      easyvr.detectToken(bits, EasyVR::REJECTION_AVG, 0);
    }
    else if (useCommands)
    {
      Serial.print(F("Say a command in Group "));
      Serial.println(group);
      easyvr.recognizeCommand(group);
    }
    else if (useGrammars)
    {
      easyvr.recognizeWord(set);
    }
  }
  do
  {
    if (checkMonitorInput())
      return;
  }
  while (!easyvr.hasFinished());
  isSleeping = false;
  isBusy = false;

  easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off

  if (easyvr.isAwakened())
  {
    Serial.println(F("Audio wake-up!"));
    return;
  }

  int16_t idx;
  if (useTokens)
  {
    idx = easyvr.getToken();
    if (idx >= 0)
    {
      Serial.print(F("Token: "));
      Serial.println(idx);
      easyvr.playSound(0, EasyVR::VOL_FULL);
    }
  }
  // handle voice recognition
  idx = easyvr.getWord();
  if (idx >= 0)
  {

    Serial.print(easyvr.getWord());
    if(idx==0)
    {
      digitalWrite(led1,HIGH);
pos0=91;
pos1=30;
    }
    
    else if(idx==1)
    {
            digitalWrite(led2,HIGH);
pos0=71;
pos1=90;     
    }
    
else    if(idx==2)
    {
            digitalWrite(led3,HIGH);
pos0=120;
pos1=0;     
     
    }
    
else    if(idx==3)
    {
            digitalWrite(led1,HIGH);
pos0=20;
pos1=150;     

    }
    
else    if(idx==4)
    {
            digitalWrite(led2,HIGH);
pos0=120;
pos1=120;     

    }
    
else    if(idx==5)
    {
            digitalWrite(led3,HIGH);
pos0=0;
pos1=170;     

    }
    
else    if(idx==6)
    {
            digitalWrite(led1,HIGH);
pos0=71;
pos1=90;     

    }
    
else    if(idx==7)
    {
            digitalWrite(led2,HIGH);
pos0=90;
pos1=71;     
     
    }
    
else    if(idx==8)
    {
            digitalWrite(led3,HIGH);
      pos2=111;
pos0=71;
pos1=90;     

    }
    
    
else    if(idx==9)
    {
            digitalWrite(led1,HIGH);
      pos2=81;
pos0=71;
pos1=90;     
     
    }
    
    
else    if(idx==10)
    {
            digitalWrite(led2,HIGH);
      pos2=91;
pos0=71;
pos1=90;     
     
    }
    

    set=3;
    // ok, let's try another set
    easyvr.playSound(0, EasyVR::VOL_FULL);
  }
  else
  {
    idx = easyvr.getCommand();
    if (idx >= 0)
    {
      Serial.print(F("Command: "));
      Serial.print(easyvr.getCommand());
      if (easyvr.dumpCommand(group, idx, name, train))
      {
        Serial.print(F(" = "));
        Serial.println(name);
      }
      else
        Serial.println();
      // ok, let's try another group
      do
      {
        group++;
        if (group > EasyVR::PASSWORD)
          group = 0;
      }
      while (!((mask >> group) & 1));
      easyvr.playSound(0, EasyVR::VOL_FULL);
    }
    else // errors or timeout
    {
      int16_t err = easyvr.getError();
    }
  }
  
  
    move();
}



void move()
{
  if(y0!=pos0)
{
  myservo0.attach(2);
   if(y0<pos0) 
  for(pos = y0; pos < pos0; pos += 1)  // goes from 0 degrees to 180 degrees 
{    myservo0.write(pos);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
}
  else if (y0>pos0)
  for(pos = y0; pos>=pos0; pos-=1)     // goes from 180 degrees to 0 degrees 
 {   myservo0.write(pos);       
     delay(15);                       // waits 15ms for the servo to reach the position 
 }

   y0=pos0;
}
 
    if(y1!=pos1)
{  
    myservo0.attach(3);
   if(y1<pos1) 
  for(pos = y1; pos < pos1; pos += 1)  // goes from 0 degrees to 180 degrees 
    {myservo0.write(pos);              // tell servo to go to position in variable 'pos' 
        delay(15);                       // waits 15ms for the servo to reach the position 
    }
    
  else if (y1>pos1)
  for(pos = y1; pos>=pos1; pos-=1)     // goes from 180 degrees to 0 degrees 
{    myservo0.write(pos);       
    delay(15);                       // waits 15ms for the servo to reach the position 
}

   y1=pos1;
   delay(3000);
}

    if(y2!=pos2)
{
      myservo0.attach(4);
   if(y2<pos2) 
  for(pos = y2; pos < pos2; pos += 1)  // goes from 0 degrees to 180 degrees 
 {   myservo0.write(pos);              // tell servo to go to position in variable 'pos' 
     delay(15);                       // waits 15ms for the servo to reach the position 
 }
  else if (y2>pos2)
  for(pos = y2; pos>=pos2; pos-=1)     // goes from 180 degrees to 0 degrees 
  {  myservo0.write(pos);       
      delay(15);                       // waits 15ms for the servo to reach the position 
  }
             // tell servo to go to position in variable 'pos' 
   y2=pos2;
   delay(3000);   
}

    if(y3!=pos3)
{
      myservo0.attach(5);
  if(y3<pos3) 
  for(pos = y3; pos < pos3; pos += 1)  // goes from 0 degrees to 180 degrees 
 {   myservo0.write(pos);              // tell servo to go to position in variable 'pos' 
     delay(15);                       // waits 15ms for the servo to reach the position 
 }
  else if (y3>pos3)
  for(pos = y3; pos>=pos3; pos-=1)     // goes from 180 degrees to 0 degrees 
  {  myservo0.write(pos);       
      delay(15);                       // waits 15ms for the servo to reach the position 
  }
   y3=pos3;
      delay(3000);
}

    if(y4!=pos4)
{
      myservo0.attach(6);
  if(y4<pos4) 
  for(pos = y4; pos < pos4; pos += 1)  // goes from 0 degrees to 180 degrees 
 {   myservo0.write(pos);              // tell servo to go to position in variable 'pos' 
     delay(15);                       // waits 15ms for the servo to reach the position 
 }
  else if (y4>pos4)
  for(pos = y4; pos>=pos4; pos-=1)     // goes from 180 degrees to 0 degrees 
  {  myservo0.write(pos);       
      delay(15);                       // waits 15ms for the servo to reach the position 
  }
   y4=pos4;
      delay(3000);
}

    if(y5!=pos5)
{
      myservo0.attach(7);
  if(y5<pos5) 
  for(pos = y5; pos < pos5; pos += 1)  // goes from 0 degrees to 180 degrees 
 {   myservo0.write(pos);              // tell servo to go to position in variable 'pos' 
     delay(15);                       // waits 15ms for the servo to reach the position 
 }
  else if (y5>pos5)
  for(pos = y5; pos>=pos5; pos-=1)     // goes from 180 degrees to 0 degrees 
  {  myservo0.write(pos);       
      delay(15);                       // waits 15ms for the servo to reach the position 
  }
   y5=pos5;
      delay(3000);
}



}



