#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_NeoPixel.h>

#define PIN_HOUR_RING 8
#define PIN_MINUTE_RING 7
#define PIN_SECOND_RING 6

#define NUM_LEDS_HOUR 12  
#define NUM_LEDS_MINUTE 60  
#define NUM_LEDS_SECOND 60  

Adafruit_NeoPixel hourRing(NUM_LEDS_HOUR, PIN_HOUR_RING, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel minuteRing(NUM_LEDS_MINUTE, PIN_MINUTE_RING, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel secondRing(NUM_LEDS_SECOND, PIN_SECOND_RING, NEO_GRB + NEO_KHZ800);

RTC_DS1307 rtc;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  
  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  hourRing.begin();
  minuteRing.begin();
  secondRing.begin();
}

void loop() {
  DateTime now = rtc.now();

  hourRing.clear();
  minuteRing.clear();
  secondRing.clear();

  int hourPosition;
  if (now.hour() == 12) {
    hourPosition = 0; 
  } else {
    hourPosition = now.hour() % 12; 
  }
  
  int minutePosition = now.minute();
  int secondPosition = now.second();


  uint32_t hourColor;
  if (now.hour() >= 12) {
    hourColor = hourRing.Color(0, 255, 0); 
  } else {
    hourColor = hourRing.Color(255, 0, 0); 
  }


  hourRing.setPixelColor(hourPosition, hourColor);
  minuteRing.setPixelColor(minutePosition, minuteRing.Color(0, 255, 0)); 
  secondRing.setPixelColor(secondPosition, secondRing.Color(0, 0, 255)); 


  hourRing.show();
  minuteRing.show();
  secondRing.show();


}
