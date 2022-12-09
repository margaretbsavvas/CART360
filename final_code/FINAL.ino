//TOUCH SENSOR TESTING
#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//number of pixel LEDs
#define NUMPIXELS   7
//pin numbers for inputs and outputs 
#define LIGHT       8
#define LUL_IN      7 
#define PINK_IN     5
#define LUL_OUT     6
#define PINK_OUT    4


const int SENSOR = 10; //pin slot in arduino for sensor
int capsensorlight; // new value of sensor
int dt = 100; // time delay 100ms
boolean active = false; //used to keep light ON or OFF. false is OFF. true is ON. 
int cnt = -1; //when int is -1 then light is OFF. when int is 0 light is ON. 


Adafruit_NeoPixel pixels(NUMPIXELS, LIGHT, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(57600);

  pinMode(LUL_IN, INPUT); //lullaby switch input
  pinMode(PINK_IN, INPUT);// pink noise switch input 
  pinMode(LUL_OUT, OUTPUT); //lullaby switch output
  pinMode(PINK_OUT, OUTPUT); //pink noise switch output

  digitalWrite(LUL_OUT, HIGH); //function for lullaby sound
  digitalWrite(PINK_OUT, HIGH); //function for pink noise sound
  
  pinMode(SENSOR, INPUT);
  pixels.begin(); // Initialize neopixel
 
}

void pixelss(int dir) {
  pixels.clear(); // sets all pixel colors to OFF

  if(dir) { 
    for(int i=0; i<NUMPIXELS; i++) { // when i=0 then it is TRUE
      // pixels.Color() 
      pixels.setPixelColor(i, pixels.Color(0, 0, 255)); //set pixels to blue
      //pixels.show();   // Send the updated pixel colors to the hardware.
      delay(dt);// Pause before next pass through loop
    } 
  }
  else {
    for(int i=NUMPIXELS-1; i>=0; i--) { // when i= -1 then it is FALSE
      // pixels.Color() 
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); //clear color of pixels
      //pixels.show();   // Send the updated pixel colors to the hardware.
      delay(dt);// Pause before next pass through loop
    }
  }
   pixels.show(); //makes sure that the pixels are ON 
}

void loop() {
  
  capsensorlight = digitalRead(SENSOR); 
  if(capsensorlight && !active) {
    Serial.println("on");
    pixelss(1);
    active = true; //when boolean is true then pixels are ON
    } else if (capsensorlight && active) {
  Serial.println("off");
  pixelss(0);
  active = false; // when boolean is false then pixels are OFF
  }

    int lullaby =digitalRead(LUL_IN); //integer for lullaby 
    int pink =digitalRead(PINK_IN); //integer for pink noise 

      //digitalWrite(PINK_OUT, LOW); 
    
    if(lullaby) {
      digitalWrite(LUL_OUT, LOW); //then sound will play 
      //Serial.println(lullaby);
    }
     else digitalWrite(LUL_OUT, HIGH); //then sound will NOT play 
   // Serial.println(pink);

   if(pink) {
      digitalWrite(PINK_OUT, LOW); //then sound will play 
      //Serial.println(lullaby);
    }
     else digitalWrite(PINK_OUT, HIGH); //then sound will NOT play 
}
