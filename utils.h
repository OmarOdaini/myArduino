#include <LiquidCrystal_I2C.h>


void lcdClearLine(int lineNum, LiquidCrystal_I2C lcd){
    lcd.setCursor(0,lineNum);
    for(int n = 0; n < 20; n++)  lcd.print(" ");
    lcd.setCursor(0,lineNum);
    delay(100);
} 

int tempConvert(double celsius) {
  return int((celsius * 1.8) + 32);
}

void blink(int period){
  digitalWrite(6, HIGH);
  delay(period);
  digitalWrite(6, LOW);
  delay(period);
}
