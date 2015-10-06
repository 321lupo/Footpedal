                                   //LCD & SHIELD Libraries
  #include <Wire.h>
  #include <Adafruit_MCP23017.h>
  #include <Adafruit_RGBLCDShield.h>
  Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();
                              // LCD backlight color
  #define RED 0x1
  #define YELLOW 0x3
  #define GREEN 0x2
  #define TEAL 0x6
  #define BLUE 0x4
  #define VIOLET 0x5
  #define WHITE 0x7
                              //Pushbuttons Debounce Library
  #include <Bounce.h>
                              //Midi Library
  #include <MIDI.h>
  const int MIDI_CHAN = 5;
  
  #define BUTTONBANK 6         //bankswitch button
  #define BUTTONSTOP 11        //stop button (not part of bank)
  #define BUTTONPLAY 23        //play (not part of bank)
  #define CTRLBUTTONS_N 12     //ctrl buttons used to trigger clips
  #define NUM_BANKS 2
  #define CTRL_DEL
  #define CTRL_STOP 71
  #define CTRL_PLAY 72
  #define CTRL_START 72      //begin of control values available to footpedal (71-128) 1 gets added in the code
  int bank = 0;

  #define CTRLBUTTONS_N 12
  int buttonPins[] = {2,3,4,5,/*6,*/7,8,9,10,/*11,*/12,20,21,22,/*23*/};  //All button pins except bank, stop and play button
  // int buttons[CTRLBUTTONS_N];

  Bounce buttonBank = Bounce(BUTTONBANK, 50);                  
  Bounce buttonStop = Bounce(BUTTONSTOP, 50);
  Bounce buttonPlay = Bounce (BUTTONPLAY, 50);
  
  /*for(int i = 0; i < CTRLBUTTONS_N; i++){                    //BOUNCE FORLOOP HOW???
  Bounce buttons[i] = Bounce (buttonPins[i], 20); 
  }
  */

  Bounce button0 = Bounce (buttonPins[0], 50); 
  Bounce button1 = Bounce (buttonPins[1], 50); 
  Bounce button2 = Bounce (buttonPins[2], 50); 
  Bounce button3 = Bounce (buttonPins[3], 50);
  Bounce button4 = Bounce (buttonPins[4], 50);
  Bounce button5 = Bounce (buttonPins[5], 50);
  Bounce button6 = Bounce (buttonPins[6], 50);
  Bounce button7 = Bounce (buttonPins[7], 50);
  Bounce button8 = Bounce (buttonPins[8], 50);
  Bounce button9 = Bounce (buttonPins[9], 50);
  Bounce button10 = Bounce (buttonPins[10], 50);
  Bounce button11 = Bounce (buttonPins[11], 50);
  
  int bankadd = 0;

  unsigned long millisTime;                     //millis del-keystroke variables
  unsigned long delTime[CTRLBUTTONS_N];         //for now without arrays...         
  bool delBool[CTRLBUTTONS_N];
  int delHold = 2000;                           //time to hold down buttons to send del-msg
  unsigned long redoTime;
  bool redoBool;
  int redoHold = 2000;

  
void setup(){  
                             
  Serial.begin(9600);
  
  pinMode (BUTTONBANK, INPUT_PULLUP);
  pinMode (BUTTONSTOP, INPUT_PULLUP);
  pinMode (BUTTONPLAY, INPUT_PULLUP);
  
//  for(int i=0; i<CTRLBUTTONS_N; i++){                    //PULLUP FORLOOP
//    pinMode (buttonPins[i], INPUT_PULLUP);
//  }  
  
  pinMode(buttonPins[0], INPUT_PULLUP);
  pinMode(buttonPins[1], INPUT_PULLUP);
  pinMode(buttonPins[2], INPUT_PULLUP);
  pinMode(buttonPins[3], INPUT_PULLUP);
  pinMode(buttonPins[4], INPUT_PULLUP);
  pinMode(buttonPins[5], INPUT_PULLUP);
  pinMode(buttonPins[6], INPUT_PULLUP);
  pinMode(buttonPins[7], INPUT_PULLUP);
  pinMode(buttonPins[8], INPUT_PULLUP);
  pinMode(buttonPins[9], INPUT_PULLUP);
  pinMode(buttonPins[10], INPUT_PULLUP);
  pinMode(buttonPins[11], INPUT_PULLUP);
                          
  lcd.begin(16, 2);                         //LCD START
 
  lcd.clear();            
  lcd.setCursor(0, 0);
  lcd.print("START");
 
  Serial.println("serial start"); 

  for(int i=0; i<CTRLBUTTONS_N; i++){             //reset all del and redo Variables
    delTime[i]=0;
    delBool[i]=false;
  }
  redoTime=0;
  redoBool=false;
  
}

void loop(){

  millisTime = millis();                  //time var running WHATS THE MAX MILLIS VALUE?
  
  while (usbMIDI.read());   

  readButtons();

  if(buttonBank.fallingEdge()) {     //3 banks, Button+/-, Print LCD and Serial 
    bank++;
    bank %= NUM_BANKS;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bank ");
    lcd.print(bank);
    Serial.print("Bank ");
    Serial.println(bank);
    redoTime=millisTime;
    redoBool=true;
  }
  if (buttonBank.risingEdge()) {
      redoBool=false;
    }
  if (millisTime-redoTime>=redoHold && redoBool==true) {
      redoBool=false;
      Serial.println ("Redo ");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Redo ");
    }



  bankadd = bank * CTRLBUTTONS_N;     //ATTENTION THAT HE READS 12 HERE
              
                              // PUSHBUTTON EDGE DECLARATION
 // for(int i=0; i<CTRLBUTTONS_N; i++){   


    if (buttonStop.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_STOP), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Stop ");
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_STOP) + ("Velocity=127"));
    }
   
    if (buttonPlay.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_PLAY), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Play ");
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_PLAY) + ("Velocity=127"));
    }

 
    if (button0.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+1), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+1);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+1) + ("Velocity=127"));
      delTime[0]=millisTime;
      delBool[0]=true;
    }
    if (button0.risingEdge()) {
      delBool[0]=false;
    }
    
                                                                  //put this into forloop  
    if (millisTime-delTime[0]>=delHold && delBool[0]==true) {
      delBool[0]=false;
      Serial.println ("DELETE ");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Delete ");
    }


       
    else if (button1.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+2), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+2);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+2) + ("Velocity=127"));
    }
    else if (button2.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+3), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+3);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+3) + ("Velocity=127"));
    }
    else if (button3.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+4), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+4);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+4) + ("Velocity=127"));
    }
    else if (button4.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+5), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+5);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+5) + ("Velocity=127"));
    }
    else if (button5.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+6), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+6);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+6) + ("Velocity=127"));
    }
    else if (button6.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+7), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+7);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+7) + ("Velocity=127"));
    }
    else if (button7.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+8), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+8);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+8) + ("Velocity=127"));
    }
    else if (button8.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+9), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+9);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+9) + ("Velocity=127"));
    }
    else if (button9.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+10), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+10);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+10) + ("Velocity=127"));
    }
     else if (button10.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+11), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+11);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+11) + ("Velocity=127"));
    }
    else if (button11.fallingEdge()) {
      usbMIDI.sendControlChange((CTRL_START+bankadd+12), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CTRL ");
      lcd.print (CTRL_START+bankadd+12);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CTRL_START+bankadd+12) + ("Velocity=127"));
    }

  
}


void readButtons(){
  buttonBank.update();
  buttonStop.update();
  buttonPlay.update();
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
  button6.update();
  button7.update();
  button8.update();
  button9.update();
  button10.update();
  button11.update();
}


