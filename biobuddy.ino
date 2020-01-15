#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <FastLED.h>
#include <DHT.h>
#define LED_PIN     5
#define NUM_LEDS    5

#define DHTPIN 2
#define DHTTYPE DHT11
#define SensorPin A0 

DHT dht(DHTPIN,DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

int brightness = 255;
static char temperature[10];
static char humidity[10];
static char moisture[10];
CRGB leds[NUM_LEDS];


void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(brightness);
  Serial.begin(115200);
  Serial.println("Starting BIO Buddy\n");
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  //initialize the liquid crystal library
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("BIO Buddy");
}

void loop() {
  getTemp();
  getMoisture();
  setLCDText();
  delay(5000);
  //looplights();
}

void setLCDText() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("H ");
  lcd.print(humidity);
  lcd.print("% ");
  lcd.print("M ");
  lcd.print(moisture);
}


void getTemp(){
float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }


  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  dtostrf(t,3,2,temperature);
  dtostrf(h,2,0,humidity);

  Serial.print("temp ");
  Serial.print(temperature);
  Serial.print("C hum ");
  Serial.print(humidity);
  Serial.println("%");

}

void getMoisture() {
  float m = analogRead(SensorPin);
  dtostrf(m,3,0,moisture);

  Serial.print("Moisture: ");
  Serial.println(moisture);  
}


void looplights() {
  Moonlight();
  delay(4000);
  Sunrise();
  delay(4000);
  Sunny();
  delay(4000);
  Midday();
  delay(4000);
  Overcast();
  delay(4000);
  Sunset();
  delay(4000);
}

void allOn(int r, int g, int b)
{
    for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB ( r, g, b);
    FastLED.show();
  }
}

void Moonlight()
{
  allOn(0, 0, 255);
 //Serial.print("Moonlight");

}

void Sunny()
{
   allOn(255, 255, 0);
//  Serial.println("Sunny");
 
}

void Midday()
{
   allOn(255, 255, 255);
//  Serial.println("Midday");
 
}

void Overcast()
{
   allOn(201, 226, 255);
//  Serial.println("Overcast");
 
}

void Sunrise()
{
   allOn(255, 255, 0);
//  Serial.println("Sunrise");
 
}

void Sunset()
{
   allOn(255, 0, 0);
//  Serial.println("Sunset");
 
}

void allOff()
{
    for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB ( 0,0,0);
    FastLED.show();
    
  }
}


void stepper(int r,int g, int b, int d)
{
   for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB ( r, g, b);
    leds[i-1] = CRGB ( 0, 0, 0);
    FastLED.show();
     delay(d);
   }
}
void slider(int r,int g, int b, int d)
{
   for (int i = 0; i <= NUM_LEDS; i++) {
    leds[i] = CRGB ( r, g, b);
    FastLED.show();
     delay(d);
   }
}

void legs()
{
   
    leds[1] = CRGB ( 255,0,0);
    leds[2] = CRGB ( 255,0,0);
    leds[3] = CRGB ( 255,0,0);
    leds[4] = CRGB ( 255,255,0);
    leds[5] = CRGB ( 255,255,0);
    leds[6] = CRGB ( 255,255,0);
    leds[7] = CRGB ( 255,255,255);
    leds[8] = CRGB ( 255,255,255);
    leds[9] = CRGB ( 255,255,255);  
    leds[10] = CRGB ( 0,255,255);
    leds[11] = CRGB ( 0,255,255);
    leds[12] = CRGB ( 0,255,255);  
    leds[13] = CRGB ( 0,0,255);
    leds[14] = CRGB ( 0,0,255);
    leds[15] = CRGB ( 0,0,255);  
    leds[16] = CRGB ( 255,0,255);
    leds[17] = CRGB ( 255,0,255);
    leds[18] = CRGB ( 255,0,255);  
    leds[19] = CRGB ( 128,128,128);
    leds[20] = CRGB ( 128,128,128);
    leds[21] = CRGB ( 128,128,128);  
    leds[22] = CRGB ( 0,128,128);
    leds[23] = CRGB ( 0,128,128);
    leds[24] = CRGB ( 0,128,128);      
    leds[25] = CRGB ( 0,128,0);
    leds[26] = CRGB ( 0,128,0);
    leds[27] = CRGB ( 0,128,0); 
    leds[28] = CRGB ( 0,0,128); 
         
        
    FastLED.show();
    
}
