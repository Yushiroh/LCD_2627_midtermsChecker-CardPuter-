#include <Arduino.h>
#include "M5Cardputer.h"

String bitIn[4];
int binVals[16][4] = { {0,0,0,0},
                       {0,0,0,1},
                       {0,0,1,0},
                       {0,0,1,1},
                       {0,1,0,0},
                       {0,1,0,1},
                       {0,1,1,0},
                       {0,1,1,1},
                       {1,0,0,0},
                       {1,0,0,1},
                       {1,0,1,0},
                       {1,0,1,1},
                       {1,1,0,0},
                       {1,1,0,1},
                       {1,1,1,0},
                       {1,1,1,1}};

int stateSelect = 1;

int pinInMode(){

  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(6, INPUT);
  pinMode(40, INPUT);

  bitIn[0] = digitalRead(3);
  bitIn[1] = digitalRead(4);
  bitIn[2] = digitalRead(6);
  bitIn[3] = digitalRead(40);

  String data = bitIn[0] + bitIn[1] + bitIn[2] + bitIn[3]; 

  int convert = strtol(data.c_str(),NULL,2);

  return convert;
}

int pinOutMode(){


  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(40, OUTPUT);

    digitalWrite(3, 1);
    digitalWrite(4, 1);
    digitalWrite(6, 1);
    digitalWrite(40, 1);

  for (size_t i = 0; i < 15; i++)
  {
    M5Cardputer.Display.drawNumber(i, M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);
    digitalWrite(3, binVals[i][0]);
    digitalWrite(4, binVals[i][1]);
    digitalWrite(6, binVals[i][2]);
    digitalWrite(40, binVals[i][3]);
    delay(1000);
    M5Cardputer.Display.clear();

  }
  
  for (size_t i = 15; i > 0; i--)
  {
    M5Cardputer.Display.drawNumber(i, M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);
    digitalWrite(3, binVals[i][0]);
    digitalWrite(4, binVals[i][1]);
    digitalWrite(6, binVals[i][2]);
    digitalWrite(40, binVals[i][3]);
    delay(1000);
    M5Cardputer.Display.clear();

  }


  return 0;

}

void setup() {
  USBSerial.begin(9600);


  auto cfg = M5.config();
  M5Cardputer.begin(cfg, true);
  M5Cardputer.Display.setRotation(1);
  M5Cardputer.Display.setTextColor(WHITE);
  M5Cardputer.Display.setTextDatum(middle_center);
  M5Cardputer.Display.setFont(&fonts::FreeSansBold12pt7b);
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.drawString("Midterms Checker", M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);
  delay(1000);
  M5Cardputer.Display.clear();

}

void loop() {

  M5Cardputer.update();

  if(M5Cardputer.Keyboard.isKeyPressed('1')){

    stateSelect = 1;
    M5Cardputer.Display.clear();

  }else if (M5Cardputer.Keyboard.isKeyPressed('2')){

    stateSelect = 2;
    M5Cardputer.Display.clear();

  }
  else{

    switch (stateSelect)
    {
    case 1:
    M5Cardputer.Display.setTextSize(5);
    M5Cardputer.Display.drawNumber(pinInMode(), M5Cardputer.Display.width() / 2, M5Cardputer.Display.height() / 2);
    delay(500);
    M5Cardputer.Display.clear();

      break;
    
    case 2:
    M5Cardputer.Display.setTextSize(5);
    pinOutMode();
      break;

    default:
      break;
    }

  }

}