/*
    Настройка и контроль компараторов и их прерываний в МК семейства LGT8F

    read() - считывание значения компаратора
    void reset(режим) - сброс регистров компаратора, вызов без аргумента или с 0 включает компаратор, вызов с 1 выключает
    void setInputP(пин) - установка пина неинвертирующего входа, доступные для каждого компаратора пины указаны ниже
    void setInputN(пин) - установка пина инвертирующего входа, доступные для каждого компаратора пины указаны ниже.
    void enableHyster(режим) - режим работы гистерезиса
    void enableDF(режим, ширина в мкс из списка) - режим работы и ширина цифрового фильтра, доступные варианты ширины указаны ниже
    void enableISR(режим, фронт) - разрешить прерывание. фронты указаны ниже
    void outputEnable(режим); - разрешить вывод состояния компаратора на пин (для AC0 - D2, для AC1 - PE5 (есть не во всех корпусах))
*/
#ifndef lgtcomp_h
#define lgtcomp_h
#pragma once
#include <Arduino.h>

//  Interrupt modes
#define AC_CHANGING 0b00
#define AC_FALLING 0b10
#define AC_RISING 0b11

//  Interrupt handlers
#define AC0_interupt() ISR(ANALOG_COMP_0_vect)
#define AC1_interupt() ISR(ANALOG_COMP_1_vect)

//  Non-inverting inputs
#define AC0P 0b00 // D6
#define AC1P 0b00 // D13
#define ACXP 0b01 // A6
#define DAO 0b10  // DAC output
#define disableP 0b11

//  Inverting input
#define ACXN 0b00     // D7
#define AC1N 0b01     // A7
#define ADCMUX 0b01   // ADC Multiplexer (AC0 only)
#define DFFO_AC0 0b10 // diff. amplifier AC0
#define DFFO_AC1 0b11 // diff. amplifier AC1
#define VDO 0b10      // internal 1/5 divider (AC1 only)
#define disableN 0b11 // AC0 only

//  Digital filter width
#define _00us 0b00
#define _32us 0b01
#define _64us 0b10
#define _96us 0b11

//  ADCSRB undefined bits
#define CME01 7
#define CME00 6
#define CME11 5
#define CME10 4


class AC_0
{
public:
    AC_0()
    {
        reset(0);
        setInputP(AC0P);
        setInputN(ACXN);
        enableHyster(0b01);
        enableDF(0b01, _96us);
    };

    uint8_t read();
    void reset(uint8_t mode);
    void setInputP(uint8_t channel);
    void setInputN(uint8_t channel);
    void enableHyster(uint8_t mode);
    void enableDF(uint8_t mode, uint8_t DFwidth);
    void enableISR(uint8_t mode, uint8_t edge);
    void outputEnable(uint8_t mode); // вывод состояния компаратора на пин D2
};

class AC_1
{
public:
    AC_1()
    {
        reset(0);
        setInputP(AC1P);
        setInputN(AC1N);
        enableHyster(0b01);
        enableDF(0b01, _96us);
    };
    
    uint8_t read();
    void reset(uint8_t mode);
    void setInputP(uint8_t channel);
    void setInputN(uint8_t channel);
    void enableHyster(uint8_t mode);
    void enableDF(uint8_t mode, uint8_t DFwidth);
    void enableISR(uint8_t mode, uint8_t edge);
    void outputEnable(uint8_t mode); // вывод состояния компаратора на пин PE5 (есть не во всех корпусах)
};

extern AC_0 AC0;
extern AC_1 AC1;
#endif