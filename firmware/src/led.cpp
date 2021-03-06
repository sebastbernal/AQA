/*
  LED Indicator config
*/
// https://github.com/FastLED/FastLED/wiki/ESP8266-notes
#define FASTLED_ESP8266_RAW_PIN_ORDER

#include "app.h"

#ifdef NUEVATARJETA

// Pines 16 y 14 no sirven para la librería fastled
#define NUM_LEDS 3
#define LED_PIN 4
#define LED_TYPE WS2812B
CRGB leds[NUM_LEDS];
#define COLOR_ORDER GRB

#else

// Pines 16 y 14 no sirven para la librería fastled
#define NUM_LEDS 2
#define DI D3 //4 //D3  //0  // Si se usa la tarjeta wemos d1 mini se antepone la letra D a los pines
#define CI D2 //2 //D2  //4  // si se usa la roja de uber se unas los pines directamente
CRGB leds[NUM_LEDS];
#define COLOR_ORDER GRB

#endif

void setupLeds() {
  #ifdef NUEVATARJETA
  FastLED.addLeds<LED_TYPE,LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  #else
  FastLED.addLeds<LPD8806, DI, CI, COLOR_ORDER>(leds, NUM_LEDS);
  #endif
  // https://github.com/FastLED/FastLED/issues/659
  // https://github.com/FastLED/FastLED/wiki/FastLED-Temporal-Dithering
  FastLED.setBrightness(64);
  FastLED.setDither(0);
}

void ledParticulateQuality(PlantowerData data) {

  unsigned short int pm1 = data.pm1;
  unsigned short int pm25 = data.pm25;
  unsigned short int pm10 = data.pm10;

  CRGB alert = CRGB::Black;
 
if(pm25 < 13){
     //alert = CRGB::Green; // CRGB::Green; // Alert.ok
      int color=255*pm25/13;
       alert = CRGB(0,color,0);
       DMSG_STR(color);
   }
  if(pm25 >= 13 && pm25 < 35) {
    //  alert = CRGB::Gold; // Alert.notGood;
      int color=255*pm25/35;
       alert = CRGB(255,color,0);
       DMSG_STR(color);
    }
  if(pm25 >= 35 && pm25 < 55) {
      //alert = CRGB::OrangeRed; // Alert.bad;
      int color=150*pm25/55;
       alert = CRGB(255,color,0);
       DMSG_STR(color);
    }
  if(pm25 >= 55 && pm25 < 75) {
    //alert = CRGB::DarkRed; // CRGB::Red; // Alert.dangerous;
      int color=255*pm25/75;
       alert = CRGB(color,0,0);
       DMSG_STR(color);
  }
  if(pm25 >= 75 && pm25 < 255)  {
    //alert = CRGB::Purple;  // CRGB::Purple; // Alert.VeryDangerous;
      int color=180*pm25/255;
       alert = CRGB(175,0,color);
       DMSG_STR(color);
  }



  if (pm25>= 255) alert = CRGB::Brown; // Alert.harmful;
  
  FastLED.setBrightness(millis() % 255);

  for(unsigned char i=0; i < 4; i++) {
    for(unsigned char j=0; j < NUM_LEDS; j++) leds[j] = i%2 == 0 ? alert : CRGB::Black;// para el kit diadactico y los 64 leds
    /*#ifdef NUEVATARJETA
    leds[0] = leds[1] = leds[2] = i%2 == 0 ? alert : CRGB::Black;
    #else
    leds[0] = leds[1] = i%2 == 0 ? alert : CRGB::Black;
    #endif*/
    FastLED.show();
    FastLED.delay(300);
  }
}


void ledParticulateQualityStreamming(PlantowerData data) {
    unsigned short int pm1 = data.pm1;
    unsigned short int pm25 = data.pm25;
    unsigned short int pm10 = data.pm10;

    CRGB alert = CRGB::Black;

if(pm25 < 13){
     //alert = CRGB::Green; // CRGB::Green; // Alert.ok
      int color=255*pm25/13;
       alert = CRGB(0,color,0);
       DMSG_STR(color);
   }
  if(pm25 >= 13 && pm25 < 35) {
    //  alert = CRGB::Gold; // Alert.notGood;
      int color=255*pm25/35;
       alert = CRGB(255,color,0);
       DMSG_STR(color);
    }
  if(pm25 >= 35 && pm25 < 55) {
      //alert = CRGB::OrangeRed; // Alert.bad;
      int color=150*pm25/55;
       alert = CRGB(255,color,0);
       DMSG_STR(color);
    }
  if(pm25 >= 55 && pm25 < 75) {
    //alert = CRGB::DarkRed; // CRGB::Red; // Alert.dangerous;
      int color=255*pm25/75;
       alert = CRGB(color,0,0);
       DMSG_STR(color);
  }
  if(pm25 >= 75 && pm25 < 255)  {
    //alert = CRGB::Purple;  // CRGB::Purple; // Alert.VeryDangerous;
      int color=180*pm25/255;
       alert = CRGB(175,0,color);
       DMSG_STR(color);
  }



  if (pm25>= 255) alert = CRGB::Brown; // Alert.harmful;
  

    FastLED.setBrightness(millis() % 255);

    for(unsigned char i=0; i < 4; i++) {
    for(unsigned char j=0; j < NUM_LEDS; j++) leds[j] = i%2 == 0 ? alert : CRGB::Black;// para el kit diadactico y los 64 leds
      /*#ifdef NUEVATARJETA
      leds[0] = leds[1] = leds[2] = i%2 == 0 ? alert : CRGB::Black;
      #else
      leds[0] = leds[1] = i%2 == 0 ? alert : CRGB::Black;
      #endif*/
      FastLED.show();
      FastLED.delay(100);
    }
}


