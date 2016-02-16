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
#define PIEZOTHRESHOLD 70  // analog threshold for piezo sensing
#define PADNUM 1          // number of pads

int pad_val[PADNUM];
int val_max[PADNUM], val_min[PADNUM];

Adafruit_NeoPixel strip = Adafruit_NeoPixel(33, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(19200);   // set serial output rate
  
  for(int i = 0; i < PADNUM; i++){
  	val_max[i] =0;
  	val_min[i] =1023;
  }

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  pinta(255,0,0);
  delay(200);

  pinta(255,255,0);
  delay(400);
  pinta(0,255,0);
  delay(400);
  pinta(0,255,255);
  delay(400);
  pinta(0,0,255);
  delay(400);

  pinta(255,255,255);
  delay(1000);
  pinta(0,0,0);     
}

void loop() {

  // Loop through each piezo and send data
  // on the serial output if the force exceeds
  // the piezo threshold	
  for(int i = 0; i < PADNUM; i++) pad_val[i] = analogRead(i);

  for(int i = 0; i < PADNUM; i++){

    if(pad_val[i]>=val_max[i]) val_max[i] = pad_val[i];
    if(pad_val[i]<=val_min[i]) val_min[i] = pad_val[i];

    if( pad_val[i] >= PIEZOTHRESHOLD ) {

    	Serial.print("PAD: ");
	    Serial.print(pad_val[i]);
	    Serial.print("\tMax :");
	    Serial.print(val_max[i]);
	    Serial.print("\tMin :");
	    Serial.println(val_min[i]);

    	digitalWrite(LEDPIN,HIGH);  // indicate we're sending MIDI data
    	int val=map(pad_val[i],val_min[i],600,0,255);

    	for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, strip.Color(val, val, 0));
    	strip.show();
  		delay(val);

    	for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, strip.Color(0, 0, 0));
    	strip.show();

    	digitalWrite(LEDPIN,LOW);      
    }
  }


}


void pinta(int r, int g, int b){
	for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, strip.Color(r, g, b));
	strip.show();
}