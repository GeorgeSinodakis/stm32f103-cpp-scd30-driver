#include "adc.h"
#include "rcc.h"

void ADC1_clock_enable(void)
{
    RCC_APB2ENR |= 1 << 9;
}

void ADC2_clock_enable(void)
{
    RCC_APB2ENR |= 1 << 10;
}