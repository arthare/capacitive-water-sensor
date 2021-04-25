
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int lastBacklight = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lastBacklight = 1;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  { // handling light level
    int lightLevel=analogRead(A0);
    int shouldHaveBacklight = lightLevel > 350 ? 1 : 0;
    if(shouldHaveBacklight != lastBacklight)
    {
      if(shouldHaveBacklight)
      {
        lcd.backlight();
      }
      else
      {
        lcd.noBacklight();
      }
      lastBacklight = shouldHaveBacklight;
    }
    char buf[16];
    sprintf(buf, "Light: %05d", lightLevel);
    
    lcd.setCursor(2,0);
    lcd.print(buf);
  }

  { // handling water level
    int waterLevel = analogRead(A1);
    char buf[16];
    sprintf(buf, "Water: %05d", waterLevel);
    Serial.println(buf);
    lcd.setCursor(2,1);
    lcd.print(buf);
  }
  delay(200);
}
