/*
 * Ardrumo sketch
 *
 * Use with the Ardrumo software here:
 * http://code.google.com/p/ardrumo/
 * This is designed to let an Arduino act as a drum machine
 * in GarageBand (sorry, Mac OS X only).
 */
 #include <Adafruit_NeoPixel.h>

 
#define PIN 6
#define LEDPIN     13     // status LED pin
#define PIEZOTHRESHOLD 5  // analog threshold for piezo sensing
#define PADNUM 1          // number of pads

int val, val_max = 5, val_min = 1023;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(33, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(19200);   // set serial output rate
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  // Loop through each piezo and send data
  // on the serial output if the force exceeds
  // the piezo threshold
  for(int i = 0; i < PADNUM; i++) {
    val = analogRead(i);

    if(val>=val_max) val_max = val;
    if(val<=val_min) val_min = val;

      Serial.print("PAD: ");
      Serial.print(val);
      Serial.print("\tMax :");
      Serial.print(val_max);
      Serial.print("\tMin :");
      Serial.println(val_min);

    if( val >= PIEZOTHRESHOLD ) {


      strip.show();
      digitalWrite(LEDPIN,HIGH);  // indicate we're sending MIDI data
      /*
      Serial.print(i);
      Serial.print(",");
      Serial.print(val);
      Serial.println();
      */
      digitalWrite(LEDPIN,LOW);

      val=map(val,0,1023,0,255);

      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(val, 0, 0));
       }
      strip.show();
      
    }

      for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 0));
      }
      strip.show();
  }


}
