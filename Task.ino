#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C
#define PM A0
#define TM A1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
const float A=0.7292022908e-03,B=2.159994283e-04,C=0.9045086282e-07, R1=100000;
void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
  int l = analogRead(PM),t=analogRead(TM);
  double dC = map(l, 0, 1023, 0, 45), Temp;
  double R2 = R1 * (1023.0 / t - 1.0);
  double logR2 = log(R2);
  Temp = (1.0 / (A + B*logR2 + C*logR2*logR2*logR2));
  Temp = Temp - 273.15;
  if(Temp <= dC)
  {
    digitalWrite(13, HIGH);
  }
  else if(Temp > dC)
  {
    digitalWrite(13, LOW);
  }
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,2);
  display.println("Desired Temperature:");
  display.setCursor(0,20);
  display.println(dC);
  display.setCursor(0,40);
  display.println("Temperature: ");
  display.setCursor(80,40);
  display.println(Temp);
  display.display();
  delay(200);
  display.clearDisplay();
}
