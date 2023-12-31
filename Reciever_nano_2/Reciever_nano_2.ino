#include "SoftwareSerial.h" 

SoftwareSerial zigbee(5, 7);
int songNum;
int motor = 11;
int color = 0;
char on = 1;
char off = 0;
void(* resetFunc) (void) = 0;

char AmericaTheBeautiful[40][4] = {{off, off, off, off}, 
  {off, off, on, off},
  {off, on, off, on},
  {off, off, off, on},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, off, off},
  {off, off, on, off},
  {off, on, off, off},
  {off, on, off, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, on, off, on},
  {off, on, off, on},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, off, on},
  {on, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {on, on, off, on},
  {off, on, off, on},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, off, on},
  {on, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, off, on},
  {on, off, on, off},
  {off, off, off, off}
};
char DoReMi[31][4] =  {{off, off, off, off}, 
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, off, off},
  {on, off, off, on},
  {on, on, off, off},
  {off, on, off, off},
  {off, off, on, off},
  {on, off, off, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, off, off},
  {on, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, on, off, on},
  {off, off, on, off},
  {off, on, off, on},
  {off, off, on, off},
  {off, on, off, on},
  {off, off, on, off},
  {off, off, off, on},
  {on, off, on, off},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, off, off}
};
char Friends[34][4] =  {{off, off, off, off}, 
  {off, on, off, off},
  {off, off, on, off},
  {on, off, on, off},
  {on, on, off, off},
  {off, on, off, off},
  {off, off, on, off},
  {off, off, on, off},
  {off, on, off, off},
  {on, on, off, on},
  {off, on, off, off},
  {on, off, on, off},
  {off, off, off, off},
  {off, on, off, off},
  {off, off, on, off},
  {off, off, on, off},
  {off, on, off, off},
  {on, on, off, off},
  {off, on, off, off},
  {off, on, off, off},
  {off, on, off, off},
  {off, on, off, off},
  {off, off, on, off},
  {off, on, off, off},
  {off, on, off, off},
  {off, on, off, off},
  {off, off, on, off},
  {off, on, off, off},
  {off, off, on, off},
  {off, off, on, off},
  {on, off, on, off},
  {off, on, off, off},
  {on, on, off, off},
  {off, off, off, off}
};
char ItsASmallWorld[50][4] = {{off, off, off, off}, 
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, off, off}
};
char OverTheRainbow[45][4] = {{off, off, off, off}, 
  {off, off, on, off},
  {on, off, on, off},
  {off, off, on, off},
  {off, off, off, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, off, off, on},
  {off, off, on, off},
  {off, off, on, off},
  {on, on, off, off},
  {off, on, off, on},
  {off, off, off, on},
  {off, off, on, off},
  {off, off, on, off},
  {on, off, on, off},
  {off, off, on, off},
  {off, off, off, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, off, off, on},
  {off, off, on, off},
  {off, off, on, off},
  {on, on, off, off},
  {off, on, off, on},
  {off, off, off, on},
  {off, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {off, off, off, off},
  {off, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {off, off, off, off}
};
char BallGame[21][4] = {{off, off, off, off}, 
  {on, off, on, off},
  {off, on, off, on},
  {on, off, on, off},
  {off, on, off, on},
  {off, off, on, off},
  {off, on, off, on},
  {on, on, off, off},
  {off, on, off, on},
  {on, off, on, off},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, off, on},
  {on, off, off, on},
  {on, off, off, off},
  {off, off, on, off},
  {off, off, on, off},
  {on, off, off, off},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, off, off}
};
char FelizNavidad[82][4] = {{off, off, off, off}, 
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {on, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, off}
};
char Rudolph[40][4] =  {{off, off, off, off},
  {off, off, on, off},
  {on, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, off, on},
  {off, off, on, off},
  {off, on, off, on},
  {on, off, on, off},
  {off, on, off, off},
  {on, on, off, off},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, on, off},
  {off, off, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, on, off, off},
  {on, on, off, off},
  {off, on, off, on},
  {off, off, on, off},
  {on, off, on, off},
  {off, on, off, on},
  {off, on, off, on},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, off, off}
};
char SilentNight[28][4] =  {{off, off, off, off}, 
  {off, off, on, off},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, off, on},
  {off, off, on, off},
  {off, off, off, on},
  {off, off, on, off},
  {off, on, off, off},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, off, off, on},
  {off, off, on, off},
  {off, off, on, off},
  {off, on, off, on},
  {on, off, on, off},
  {off, off, off, on},
  {off, off, on, off},
  {off, off, off, on},
  {off, off, on, off},
  {off, on, off, off},
  {on, off, on, off},
  {on, off, on, off},
  {off, off, off, on},
  {off, off, off, on},
  {off, off, on, off},
  {off, off, off, off}
};
char *songs[9] = {&(AmericaTheBeautiful[0][0]), &(DoReMi[0][0]), &(Friends[0][0]),
 &(ItsASmallWorld[0][0]), &(OverTheRainbow[0][0]), &(BallGame[0][0]), &(FelizNavidad[0][0]), &(Rudolph[0][0]), &(SilentNight[0][0])
};


void setup() {
  Serial.begin(9600);
  zigbee.begin(9600);
  pinMode(motor, OUTPUT);

  bool notKnowSong = true;
  while (notKnowSong){
    if (zigbee.available() > 0){
      int read = zigbee.read();
      if (read != NULL){
        songNum = read - 48;
        notKnowSong = false;
      }
    }
    delay(100);
  }
  Serial.println(songNum);
}


int cardNum = 0;
void loop() {
  if (cardNum < 96){
    if (zigbee.available() > 0){
      Serial.println("zigbee is available");
      int receive = zigbee.read();
      Serial.println(receive);
      if (receive == 49){
        Serial.println("New card");
        cardNum += 1;
      }
      else if (receive == 42){
        digitalWrite(motor, LOW);
        resetFunc();
      }
    }

    if (*(songs[songNum] + 4*cardNum + color) == on){
      digitalWrite(motor, HIGH);
      Serial.print(motor);
      Serial.println(" is on!!");
    }
    else if (*(songs[songNum] + 4*cardNum + color) == off){
      digitalWrite(motor, LOW);
      Serial.print(motor);
      Serial.println(" is off!!");
    }
  
  }
  delay(100);
 }
