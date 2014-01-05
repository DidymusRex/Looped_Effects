#include <Adafruit_NeoPixel.h>

const int N_PIN = 1;  // Gemma data pin
const int N_PXS = 16; // Loop size

uint8_t i;
uint16_t color, style;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PXS, N_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize all pixels to 'off'
  strip.begin();
  strip.show(); 
  
  //Serial.begin(9600);

  // hope there is enough variation in instruction timing
  // to generate a decent random seed
  randomSeed(analogRead(1) + millis());
  for (i = 0; i < random(256); i++) {i = random(256);}
  
  color = strip.Color(random(255), random(255), random(255));
  style = random(5); // 1 = Wrap
                     // 2 = Pulse
                     // 3 = Heartbeat
                     // 4 = Four-way
                     // 5 = Two-Way 
  i = 0;   
}

void loop() {  
  switch (style) {
  case 1: // Wrap around clockwise
    pxl_wrap_cw(i, 5, color);
    delay(64);

    if (i >= N_PXS) {i = -1;}
    break;

  case 2: // Pulse
    pxl_pulse(16, color);
    break; 
    
  case 3: // Heartbeat (double pulse)
    pxl_pulse(24, color);
    pxl_pulse(24, color);
    delay(200);
    break;
  
  case 4: // Four-way rotate clockwise
    pxl_x4(i, color);
    delay(64);

    if (i >= 4) { i = -1; }
    break;
  
  case 5: // Two-way rotate clockwise
    pxl_x2(i, color);
    delay(128);

    if (i >= 8) {i = -1;}
    break;
    
//  case 9: // Trail :: todo get fade corrected
//    pxl_trail_cw(i, color, 5); // Red
//    delay(50);
//
//    if (i >= N_PXS) {i = -1;}
//    break;

  default:
  
    break;
  }
  
  i++;
}

// -------------------------------------
void pxl_blank () {
  int16_t i=0;
  // turn off all pixels
  for (i=0; i<=N_PXS; i++){
    strip.setPixelColor(i, 0);
  }
} 


// -------------------------------------
void pxl_wrap_cw(uint8_t p, uint8_t s, uint16_t c) {
  pxl_blank();
    
  // turn on p thru p + s
  for (uint8_t i = p; i < (p + s); i++) {
    if (i >= N_PXS){
      strip.setPixelColor((i - N_PXS), c);
    } else {
      strip.setPixelColor(i, c);
    }
  }
  strip.show();
}

// -------------------------------------
void pxl_pulse (uint8_t s, uint16_t c) {
  for (uint8_t i=0; i<=N_PXS; i++){
    strip.setPixelColor(i, c);
  }
  // full off
  strip.setBrightness(1);
  strip.show();
  
  // run up
  for (i=1; i< (256 - s); i += s) {
    strip.setBrightness(i);
    strip.show();
    delay(50);
  }
  
  // full on
  strip.setBrightness(255);
  strip.show();
  
  // run down
  for (i=255; i >= s; i -= s) {
    strip.setBrightness(i);
    strip.show();
    delay(50);
  }
   
  // full off
  strip.setBrightness(1);
  strip.show();
}

// -------------------------------------
void pxl_x4 (uint8_t p, int16_t c) {
    pxl_blank();
    strip.show();
    
    //Serial.println(p);
    
    // works because 0 < p < 5. Effect 1 px wide
    strip.setPixelColor(p, c);
    strip.setPixelColor(p + 4, c);
    strip.setPixelColor(p + 8, c);
    strip.setPixelColor(p + 12, c);
    strip.show();
}

// -------------------------------------
void pxl_x2 (uint8_t p, int16_t c) {
    uint8_t q;
    
    pxl_blank();
    
    // work when 0 < p < 9. Effect three px wide
    strip.setPixelColor(p, c);
    strip.setPixelColor(p + 1, c);
    strip.setPixelColor(p + 2, c);
    
    q=p+8;
    if (q >= N_PXS) {q = (p + 8) - N_PXS;}
    strip.setPixelColor(q, c);
    
    q=p+9;
    if (q >= N_PXS) {q = (p + 9) - N_PXS;}
    strip.setPixelColor(q, c);
    
    q=p+10;
    if (q >= N_PXS) {q = (p + 10) - N_PXS;}
    strip.setPixelColor(q, c);
    
    strip.show();
}


// -------------------------------------
/*
void pxl_wrap_ccw(uint8_t p, uint32_t c, uint8_t s) {
  pxl_blank();

  // turn on p thru p + s
  for (uint8_t i = p; i > (p - s); i--) {
    if (i < 1){
      strip.setPixelColor((N_PXS + i), c);
    } else {
      strip.setPixelColor(i, c);
    }
  }
  strip.show();
}
*/

// -------------------------------------
/*
void pxl_trail_cw(uint8_t p, int8_t c, uint8_t s) {
  int16_t i,j=0;
  
  pxl_blank(); 
  
  j=0;
  // turn on p thru p + s
  for (i = p; i < (p + s); i++) {
    j++;
    
      //if (r - (j * 32) > 0) { r = r - (j * 32); } else { r = 0; }
      //if (g - (j * 32) > 0) { g = g - (j * 32); } else { g = 0; }
      //if (b - (j * 32) > 0) { b = b - (j * 32); } else { b = 0; }
    
    c=strip.Color(r,g,b); // fading each pixel by 16
    
    if (i >= N_PXS){
      strip.setPixelColor((i - N_PXS), c);
    } else {
      strip.setPixelColor(i, c);
    }
  }
  strip.show();
}
*/
