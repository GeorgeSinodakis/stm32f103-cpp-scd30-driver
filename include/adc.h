#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define ADC2_BASE		0x40012800
#define ADC1_BASE		0x40012400

#define ADC_SR          0x00              
#define ADC_CR1         0x04    
#define ADC_CR2         0x08
#define ADC_SMPR1       0x0C    
#define ADC_SMPR2       0x10    
#define ADC_JOFR1       0x14    
#define ADC_JOFR2       0x18    
#define ADC_JOFR3       0x1C    
#define ADC_JOFR4       0x20    
#define ADC_HTR         0x24
#define ADC_LTR         0x28
#define ADC_SQR1        0x2C    
#define ADC_SQR2        0x30    
#define ADC_SQR3        0x34    
#define ADC_JSQR        0x38    
#define ADC_JDR1        0x3C    
#define ADC_JDR2        0x40    
#define ADC_JDR3        0x44    
#define ADC_JDR4        0x48    
#define ADC_DR          0x4C

#define ADC1_SR          (*(volatile u32*)(ADC1_BASE + ADC_SR))
#define ADC1_CR1         (*(volatile u32*)(ADC1_BASE + ADC_CR1))
#define ADC1_CR2         (*(volatile u32*)(ADC1_BASE + ADC_CR2))
#define ADC1_SMPR1       (*(volatile u32*)(ADC1_BASE + ADC_SMPR1))
#define ADC1_SMPR2       (*(volatile u32*)(ADC1_BASE + ADC_SMPR2))
#define ADC1_JOFR1       (*(volatile u32*)(ADC1_BASE + ADC_JOFR1))
#define ADC1_JOFR2       (*(volatile u32*)(ADC1_BASE + ADC_JOFR2))
#define ADC1_JOFR3       (*(volatile u32*)(ADC1_BASE + ADC_JOFR3))
#define ADC1_JOFR4       (*(volatile u32*)(ADC1_BASE + ADC_JOFR4))
#define ADC1_HTR         (*(volatile u32*)(ADC1_BASE + ADC_HTR))
#define ADC1_LTR         (*(volatile u32*)(ADC1_BASE + ADC_LTR))
#define ADC1_SQR1        (*(volatile u32*)(ADC1_BASE + ADC_SQR1))
#define ADC1_SQR2        (*(volatile u32*)(ADC1_BASE + ADC_SQR2))
#define ADC1_SQR3        (*(volatile u32*)(ADC1_BASE + ADC_SQR3))
#define ADC1_JSQR        (*(volatile u32*)(ADC1_BASE + ADC_JSQR))
#define ADC1_JDR1        (*(volatile u32*)(ADC1_BASE + ADC_JDR1))
#define ADC1_JDR2        (*(volatile u32*)(ADC1_BASE + ADC_JDR2))
#define ADC1_JDR3        (*(volatile u32*)(ADC1_BASE + ADC_JDR3))
#define ADC1_JDR4        (*(volatile u32*)(ADC1_BASE + ADC_JDR4))
#define ADC1_DR          (*(volatile u32*)(ADC1_BASE + ADC_DR))

#define ADC2_SR          (*(volatile u32*)(ADC2_BASE + ADC_SR))
#define ADC2_CR1         (*(volatile u32*)(ADC2_BASE + ADC_CR1))
#define ADC2_CR2         (*(volatile u32*)(ADC2_BASE + ADC_CR2))
#define ADC2_SMPR1       (*(volatile u32*)(ADC2_BASE + ADC_SMPR1))
#define ADC2_SMPR2       (*(volatile u32*)(ADC2_BASE + ADC_SMPR2))
#define ADC2_JOFR1       (*(volatile u32*)(ADC2_BASE + ADC_JOFR1))
#define ADC2_JOFR2       (*(volatile u32*)(ADC2_BASE + ADC_JOFR2))
#define ADC2_JOFR3       (*(volatile u32*)(ADC2_BASE + ADC_JOFR3))
#define ADC2_JOFR4       (*(volatile u32*)(ADC2_BASE + ADC_JOFR4))
#define ADC2_HTR         (*(volatile u32*)(ADC2_BASE + ADC_HTR))
#define ADC2_LTR         (*(volatile u32*)(ADC2_BASE + ADC_LTR))
#define ADC2_SQR1        (*(volatile u32*)(ADC2_BASE + ADC_SQR1))
#define ADC2_SQR2        (*(volatile u32*)(ADC2_BASE + ADC_SQR2))
#define ADC2_SQR3        (*(volatile u32*)(ADC2_BASE + ADC_SQR3))
#define ADC2_JSQR        (*(volatile u32*)(ADC2_BASE + ADC_JSQR))
#define ADC2_JDR1        (*(volatile u32*)(ADC2_BASE + ADC_JDR1))
#define ADC2_JDR2        (*(volatile u32*)(ADC2_BASE + ADC_JDR2))
#define ADC2_JDR3        (*(volatile u32*)(ADC2_BASE + ADC_JDR3))
#define ADC2_JDR4        (*(volatile u32*)(ADC2_BASE + ADC_JDR4))
#define ADC2_DR          (*(volatile u32*)(ADC2_BASE + ADC_DR))

void ADC1_clock_enable(void);
void ADC2_clock_enable(void);