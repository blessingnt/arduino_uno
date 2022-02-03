#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


int neoPin = 6;
int x = 0;
int y = 1;
int cols = 32;
int rows = 8;
Adafruit_NeoMatrix neo(cols, rows, neoPin,
                       NEO_MATRIX_BOTTOM  + NEO_MATRIX_RIGHT +
                       NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                       NEO_GRB            + NEO_KHZ800);

#include <Wire.h>
#include <DS3231.h>

DS3231 rtc;

bool useCentury;
bool use12hour;
bool useMeridiem;

void setup()
{
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();

  Serial.println("Setting RTC time");

  rtc.setClockMode(false); // use 24 hour clock
  rtc.setYear(20);
  rtc.setMonth(10);
  rtc.setDate(13);
  rtc.setDoW(2);
  rtc.setHour(14);
  rtc.setMinute(28);
  rtc.setSecond(00);
  
  Serial.println("Done setting RTC time!");
  
  neo.begin();
neo.setTextWrap(false);
neo.setBrightness(10);
neo.fillScreen(0);
}

void loop()
{
neo.clear();
drawTime(y, rtc.getHour(use12hour, useMeridiem), rtc.getMinute());
drawDate(y + 10, rtc.getMonth(useCentury), rtc.getDoW());
y = y - 1;
neo.show();
delay(1000);

}

void printTime()
{
  Serial.print(rtc.getYear(), DEC);
  Serial.print("-");
  Serial.print(rtc.getMonth(useCentury), DEC);
  Serial.print("-");
  Serial.print(rtc.getDate(), DEC);
  Serial.print(" ");
  Serial.print(rtc.getHour(use12hour, useMeridiem), DEC); //24-hr
  Serial.print(":");
  Serial.print(rtc.getMinute(), DEC);
  Serial.print(":");
  Serial.println(rtc.getSecond(), DEC);
}

void drawTime(int ypos, int hour, int min)
{
  String msg = "";
  msg = msg + String(hour) + ":";
  msg = msg + min;

  neo.setCursor(x, ypos);
  neo.println(msg);
}

void drawDate(int ypos, int mon, int date)
{
  String msg = "";
  msg = msg + String(mon) + ".";
  msg = msg + date;

  neo.setCursor(x, ypos);
  neo.println(msg);
}