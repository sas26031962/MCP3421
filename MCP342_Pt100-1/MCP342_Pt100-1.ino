#include "Wire.h"

float I0 = 0.5205;            //Значение тока через датчик
float Kt = 3.88;              //Коэффициент температурный датчика
float Range = 131072.0;       //Полный размах вольтметра 
float Uref = 2.48;            //Значение опорного напряжения

float U0 = 0.5205;            //Напряжение на датчике при 0 градусов Цельсия
float Weight = Uref / Range;  //Вес одного разряда вольтметра
float Temperature;            //Измеренное значение температуры 

float Voltage;

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
  
  //Voltage = value * Weight; 
  Voltage = value * 2.048 /131072 ; // LSB=15uV
  Temperature = ((Voltage - U0)*1000)/ (I0 * Kt);  
  Serial.print ("ExtADC= ");
  Serial.print(value); Serial.print("     Voltage= ");
  Serial.print(Voltage,6);
  Serial.print("     Temperature= ");
  Serial.println(Temperature,6);
  delay(300);
}
