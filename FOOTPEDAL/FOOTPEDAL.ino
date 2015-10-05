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
  
  #define BUTTONUP 6         //CHECK IF THESE ARE THE CORRECT PINS
  #define BUTTONDOWN 11         //two of the buttons are bank switches
  #define CNTROLBUTTONS_N 13
  #define NUM_BANKS 3
  #define CNTRL_START 70      //begin of control values available to footpedal (71-128) 1 gets added in the code
  int bank = 0;

  #define CNTRLBUTTONS_N 13
  int buttonPins[] = {2,3,4,5,/*6,*/7,8,9,10,/*11,*/12,20,21,22,23};  //All button pins except up and down button
  // int buttons[CNTRLBUTTONS_N];
  
  //TODO Maybe keep play and stop button independent of bank!

  Bounce buttonUp = Bounce(BUTTONUP, 50);                  
  Bounce buttonDown = Bounce(BUTTONDOWN, 50);
  
  /*for(int i = 0; i < CNTRLBUTTONS_N; i++){                    //BOUNCE FORLOOP HOW???
  Bounce buttons[i] = Bounce (buttonPins[i], 20); 
  }
  */

  Bounce buttons0 = Bounce (buttonPins[0], 50); 
  Bounce buttons1 = Bounce (buttonPins[1], 50); 
  Bounce buttons2 = Bounce (buttonPins[2], 50); 
  Bounce buttons3 = Bounce (buttonPins[3], 50);
  Bounce buttons4 = Bounce (buttonPins[4], 50);
  Bounce buttons5 = Bounce (buttonPins[5], 50);
  Bounce buttons6 = Bounce (buttonPins[6], 50);
  Bounce buttons7 = Bounce (buttonPins[7], 50);
  Bounce buttons8 = Bounce (buttonPins[8], 50);
  Bounce buttons9 = Bounce (buttonPins[9], 50);
  Bounce buttons10 = Bounce (buttonPins[10], 50);
  Bounce buttons11 = Bounce (buttonPins[11], 50);
  Bounce buttons12 = Bounce (buttonPins[12], 50);
  
  int bankadd = 0;

void setup(){  
                              //begin serial monitor at 9600bps
  Serial.begin(9600);
                              //LCD 
                              // set up the LCD's number of columns and rows: 
  
  pinMode (BUTTONUP, INPUT_PULLUP);
  pinMode (BUTTONDOWN, INPUT_PULLUP);
  
//  for(int i=0; i<CNTRLBUTTONS_N; i++){                    //PULLUP FORLOOP
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
  pinMode(buttonPins[12], INPUT_PULLUP);
                          
  lcd.begin(16, 2);
                              // Print a message to the LCD. We track how long it takes since
                              // this library has been optimized a bit and we're proud of it :)
 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("START");
 
  Serial.println("serial start"); 
  
}

void loop(){
  
  while (usbMIDI.read()) ;   

  readButtons();


  if(buttonUp.fallingEdge()) {     //3 banks, Button+/-, Print LCD and Serial 
    bank++;
    bank %= NUM_BANKS;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bank ");
    lcd.print(bank);
    Serial.print("Bank ");
    Serial.println(bank);
  }
  else if(buttonDown.fallingEdge()) {
    bank=bank-1;
    if (bank<=-1) bank=NUM_BANKS-1;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bank ");
    lcd.print(bank);
    Serial.print("Bank ");
    Serial.println(bank);
  }

  bankadd = bank * 13;
              
                              // PUSHBUTTON EDGE DECLARATION
 // for(int i=0; i<CNTRLBUTTONS_N; i++){   

 
    if (buttons0.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+1), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+1);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+1) + ("Velocity=127"));
    }
    else if (buttons1.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+2), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+2);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+2) + ("Velocity=127"));
    }
    else if (buttons2.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+3), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+3);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+3) + ("Velocity=127"));
    }
    else if (buttons3.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+4), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+4);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+4) + ("Velocity=127"));
    }
    else if (buttons4.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+5), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+5);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+5) + ("Velocity=127"));
    }
    else if (buttons5.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+6), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+6);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+6) + ("Velocity=127"));
    }
    else if (buttons6.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+7), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+7);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+7) + ("Velocity=127"));
    }
    else if (buttons7.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+8), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+8);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+8) + ("Velocity=127"));
    }
    else if (buttons8.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+9), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+9);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+9) + ("Velocity=127"));
    }
    else if (buttons9.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+10), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+10);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+10) + ("Velocity=127"));
    }
     else if (buttons10.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+11), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+11);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+11) + ("Velocity=127"));
    }
    else if (buttons11.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+12), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+12);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+12) + ("Velocity=127"));
    }
     else if (buttons12.fallingEdge()) {
      usbMIDI.sendControlChange((CNTRL_START+bankadd+13), 127, MIDI_CHAN);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Button ");
      lcd.print (bankadd+13);
      Serial.println(String("ch=") + MIDI_CHAN + (", Control=") + (CNTRL_START+bankadd+13) + ("Velocity=127"));
    }





  
}


void readButtons(){
  buttonUp.update();
  buttonDown.update();
  buttons0.update();
  buttons1.update();
  buttons2.update();
  buttons3.update();
  buttons4.update();
  buttons5.update();
  buttons6.update();
  buttons7.update();
  buttons8.update();
  buttons9.update();
  buttons10.update();
  buttons11.update();
  buttons12.update();
}


