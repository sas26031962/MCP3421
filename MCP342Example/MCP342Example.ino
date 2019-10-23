#include "Wire.h"

void setup() 
{
Serial.begin(9600);
Wire.begin();
Wire.beginTransmission(0x68);//i2c адрес MCP3421= B1101000
Wire.write(B11100); // настройка АЦП: постоянное преобразование, 18бит, усиление=1.
Wire.endTransmission();
}

void loop() 
{
  Wire.requestFrom(0x68,3); //запросить 3 байта данных
  long value= ((Wire.read()<<8) | Wire.read());//упаковка в одну переменную.
  value= ((value<<8)| Wire.read()); //упаковка в одну переменную.
  Serial.print ("ExtADC= ");
  Serial.print(value); Serial.print("     Voltage= ");
  float voltage = value * 2.048 /131072 ; // LSB=15uV
  Serial.println(voltage,6);
  delay(300);
}
