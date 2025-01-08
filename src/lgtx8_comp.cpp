#include "lgtx8_comp.h"
// ============== AC0 ==============

uint8_t AC_0::read()
{
    return bitRead(C0SR, C0O);
}

void AC_0::reset(uint8_t mode)
{
    C0SR = 0;
    C0XR = 0;
    ADCSRB = (ADCSRB & 0x7F) | (0 << CME01);
    ADCSRB = (ADCSRB & 0xBF) | (0 << CME00);
    C0SR = (C0SR & 0x7F) | ((mode & 0b01) << C0D);
}

void AC_0::setInputP(uint8_t channel)
{
    C0SR = (C0SR & 0xBF) | (((channel & 0b10) >> 1) << C0BG);
    C0XR = (C0XR & 0xEF) | ((channel & 0b01) << C0PS0);
}

void AC_0::setInputN(uint8_t channel)
{
    ADCSRB = (ADCSRB & 0x7F) | (((channel & 0b10) >> 1) << CME01);
    ADCSRB = (ADCSRB & 0xBF) | ((channel & 0b01) << CME00);
}

void AC_0::enableHyster(uint8_t mode)
{
    C0XR = (C0XR & 0xDF) | ((mode & 0b01) << C0HSYE);
}

void AC_0::enableDF(uint8_t mode, uint8_t DFwidth)
{
    C0XR = (C0XR & 0xFB) | ((mode & 0b01) << C0FEN);
    C0XR = (C0XR & 0xFD) | (((DFwidth & 0b10) >> 1) << C0FS1);
    C0XR = (C0XR & 0xFE) | ((DFwidth & 0b01) << C0FS0);
}

void AC_0::enableISR(uint8_t mode, uint8_t edge)
{
    C0SR = (C0SR & 0xF7) | ((mode & 0b01) << C0IE);
    C0SR = (C0SR & 0xFD) | (((edge & 0b10) >> 1) << C0IS1);
    C0SR = (C0SR & 0xFE) | ((edge & 0b01) << C0IS0);
}

void AC_0::outputEnable(uint8_t mode)
{
    C0XR = (C0XR & 0x7F) | ((mode & 0b01) << C0OE);
}


// ============== AC1 ==============

uint8_t AC_1::read()
{
    return bitRead(C1SR, C1O);
}

void AC_1::reset(uint8_t mode)
{
    C1SR = 0;
    C1XR = 0;
    ADCSRB = (ADCSRB & 0xDF) | (0 << CME11);
    ADCSRB = (ADCSRB & 0xEF) | (0 << CME10);
    C1SR = (C1SR & 0x7F) | ((mode & 0b01) << C1D);
}

void AC_1::setInputP(uint8_t channel)
{
    C1SR = (C1SR & 0xBF) | (((channel & 0b10) >> 1) << C1BG);
    C1XR = (C1XR & 0xEF) | ((channel & 0b01) << C1PS0);
}

void AC_1::setInputN(uint8_t channel)
{
    ADCSRB = (ADCSRB & 0xDF) | (((channel & 0b10) >> 1) << CME11);
    ADCSRB = (ADCSRB & 0xEF) | ((channel & 0b01) << CME10);
}

void AC_1::enableHyster(uint8_t mode)
{
    C1XR = (C1XR & 0xDF) | ((mode & 0b01) << C1HSYE);
}

void AC_1::enableDF(uint8_t mode, uint8_t DFwidth)
{
    C1XR = (C1XR & 0xFB) | ((mode & 0b01) << C1FEN);
    C1XR = (C1XR & 0xFD) | (((DFwidth & 0b10) >> 1) << C1FS1);
    C1XR = (C1XR & 0xFE) | ((DFwidth & 0b01) << C1FS0);
}

void AC_1::enableISR(uint8_t mode, uint8_t edge)
{
    C1SR = (C1SR & 0xF7) | ((mode & 0b01) << C1IE);
    C1SR = (C1SR & 0xFD) | (((edge & 0b10) >> 1) << C1IS1);
    C1SR = (C1SR & 0xFE) | ((edge & 0b01) << C1IS0);
}

void AC_1::outputEnable(uint8_t mode)
{
    C1XR = (C1XR & 0x7F) | ((mode & 0b01) << C1OE);
}


AC_0 AC0 = AC_0();
AC_1 AC1 = AC_1();