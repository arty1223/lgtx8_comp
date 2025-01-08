/*
  Пример работы с компаратором AC0 в дефолтной конфигурации библиотеки.
  
  Конфигурация по умолчанию для AC0
  Включен компаратор AC0
  Инвертирующий вход - ACXN - общий, пин D7
  Неинвертирующий вход - AC0P - пин D6
  Включен гистерезис и цифровой фильтр на 96мкс

  
  Конфигурация по умолчанию для AC1
  Включен компаратор AC1
  Инвертирующий вход - AC1N - пин A7
  Неинвертирующий вход - AC1P - пин D13
  Включен гистерезис и цифровой фильтр на 96мкс

  Вышеуказанные конфигурации активны сразу после подключения библиотеки

  Дополнительно в setup():
  Включено прерывание по восходящему фронту (пример настройки прерывания в самом конце)
  Включен вывод состояния компаратора на пин, для AC0 это пин D2
*/

#include <Arduino.h>
#include <lgtx8_comp.h>

void setup()
{
  Serial.begin(115200);  
  AC0.outputEnable(true);
  AC0.enableISR(1,AC_RISING);
}

void loop()
{   
  // Serial.print("C0SR ");
  // Serial.print(C0SR, BIN);
  // Serial.print(" C0XR ");
  // Serial.print(C0XR, BIN);
  // Serial.print(" ADCSRB ");
  // Serial.print(ADCSRB, BIN); 
  Serial.print("AС0 ");
  Serial.println(AC0.read()); 
  delay(1000);
}
AC0_interupt(){
  Serial.println("Interrupt caught");
}