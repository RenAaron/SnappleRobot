#define LDirO = 2;
#define LDirT = 3;
#define LSpeed = 4;

#define RDirO = 5;
#define RDirT = 6;
#define RSpeed = 7;
#define LDirO = 2;
#define LDirT = 3;
#define LSpeed = 4;

#define RDirO = 5;
#define RDirT = 6;
#define RSpeed = 7;

#define piezo = 8;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

uint32_t a = strip.Color(255, 0, 0); // 0x00ff00
//uint32_t b = strip.Color(255, 132, 0); //0x84ff00
//uint32_t c = strip.Color(34, 255, 0); //0xff2200
//uint32_t d = strip.Color(0, 51, 255); //0x3300ff
//uint32_t e = strip.Color(49, 0, 145); //0x002e91

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//no clue
//no clue
//no clue

//#include <Adafruit_DotStar.h>
//#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET
//#define NUMPIXELS 20 // Number of LEDs in strip

//#define DATAPIN    4
//#define CLOCKPIN   5

//no clue
//no clue
//no clue
//no clue

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

int state;
int flag = 0;

void setup() {
  
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'


  for(int i = 0; i < 5; i++){
    tone(8, 1000);
    delay(10);
    noTone(8);
    delay(10);
  }

  delay(5000);
  
  randomSeed(analogRead(A4));
  
  pinMode(LDirO,OUTPUT); 
  pinMode(LDirT, OUTPUT);
  pinMode(LSpeed, OUTPUT);

  pinMode(RDirO,OUTPUT); 
  pinMode(RDirT, OUTPUT);
  pinMode(RSpeed, OUTPUT);

  pinMode(piezo, OUTPUT);

  Serial.begin(9600);

  strip.begin();
  strip.show();
}

int randomNumba(int Max, int Min){
  int rv = random(Max, Min);
  return rv;
}

void randomLights(uint32_t color){
  for(int i = 0; i < 5; i++){
    int rColor = randomNumba(1, 5);
    strip.setPixelColor(randomNumba(1, 20), color);
      //??????
  }
}

char randomDirec(){
  int choice = randomNumba(1,3);

  //Serial.print(choice);
  //Serial.print('\n');
  
  if(choice == 1){
    return 'F';
  }

  if(choice == 2){
    return 'B';
  }
}

char randomSide(){
  int choice = randomNumba(1,3);

  //Serial.print(choice);
  if(choice == 1){
    return 'L';
  }

  if(choice == 2){
    return 'R';
  }
}

void trackMove(char side, char direc){

  if(side == 'R'){
    
    if(direc == 'F'){
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
      digitalWrite(2, 1); //forward 
      //Serial.print("right forward");
      //Serial.print('\n');
    }

    if(direc == 'B'){
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(2, 1); //backward 
      //Serial.print("right backward");
      //Serial.print('\n');
    }
  }

  if(side == 'L'){

    if(direc == 'F'){
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, 1); //forward
      //Serial.print("left forward");
      //Serial.print('\n');
    }

    if(direc == 'B'){
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, 1); //backward 
      //Serial.print("right backward");
      //Serial.print('\n');
    }
  }
        
          

}
  
void alarmOn(){
  
  for(int i = 0; i < 20; i++){
    strip.setPixelColor(i, 255, 5, 5);
  }
}

void trackStop(char side){

  if(side == 'R'){
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, 0);
  }

  if(side == 'L'){
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, 0);
  }
}

void commandAndFunction(int lis){
  if(state == lis){

    int choi = randomNumba(1, 6);
    uint32_t rColo;
    float mult; 
    
    if(choi == 1){
      rColo = 0x00ff00;
      mult = 1.0;
    }

    if(choi == 2){
      rColo = 0x84ff00;
      mult = 3;
    }

    if(choi == 3){
      rColo = 0xff2200;
      mult = 2;
    }

    if(choi == 4){
      rColo = 0x3300ff;
      mult = .5;
    }

    if(choi == 5){
      rColo = 0x002e91;
      mult = .01;
    }

    if(lis == '1'){ //random
      
      trackMove('L', randomDirec());
      trackMove('R', randomDirec());
      
      for(int i = 0; i < 4; i++){
        tone(8, 600);
        for(int j = 0; j < 10; j++){
          strip.setPixelColor(j*2, 0xff2600);
        }
        strip.show();
        delay(500);
        noTone(8);
        strip.clear();
        strip.show();
        delay(500);
      }

      flag = 1;
      state = '4';
      lis = '9';
      Serial.print("done 1");
      Serial.print('\n');

      trackStop('L');
      trackStop('R');
    }

    if(lis == '2'){
      
      for(int i = 0; i < randomNumba(10,20); i++){
        tone(8, randomNumba(100* mult, 2001* mult));
        randomLights(rColo);
        strip.show();
        delay(randomNumba(50,200));
        noTone(8);
        //delay(100);
        strip.clear();
        strip.show();
        delay(randomNumba(20, 101));
      }

      flag = 1;
      state = '4';
      lis = '9';
      Serial.print("done 1");
      Serial.print('\n');

      trackStop('L');
      trackStop('R');

    }

    if(lis == '6'){

      Serial.print("i did");

      for(int i = 0; i < 20; i++){
        alarmOn();
        strip.show();
        tone(8, 500);
        delay(50);
        noTone(8);
        strip.clear();
        strip.show();
        delay(60);
      }

    }
    
    if(lis == '9'){
      for(int i = 0; i < 50; i++){
        tone(8, 100 + (i*40));
        delay(5);
        Serial.print("9");
      }
      
      noTone(8);
    }
    //Serial.print("eeed");

    Serial.print(lis);
    Serial.print('\n');
    
    flag = 1;
    state = '4';
    lis = '9';
    Serial.print("done 2");
    Serial.print('\n');
  }
}

void loop() {

  if (Serial.available() > 0) {
    state = Serial.read();
    flag = 0;
  }
  
  commandAndFunction('1'); // s&m
  commandAndFunction('2'); // s
  
  commandAndFunction('9'); // ^
  
  commandAndFunction('6'); //alarm 
  

}
