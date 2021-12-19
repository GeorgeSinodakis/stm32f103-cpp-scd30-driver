#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "gpio.h"

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define I2C1_BASE	0x40005400
#define I2C2_BASE	0x40005800

#define I2C_CR1			0x00
#define I2C_CR2			0x04
#define I2C_OAR1		0x08
#define I2C_OAR2		0x0C
#define I2C_DR			0x10
#define I2C_SR1			0x14
#define I2C_SR2			0x18
#define I2C_CCR			0x1C
#define I2C_TRISE		0x20

#define I2C1_CR1		(*(volatile u32*)(I2C1_BASE + I2C_CR1))
#define I2C1_CR2		(*(volatile u32*)(I2C1_BASE + I2C_CR2))
#define I2C1_OAR1		(*(volatile u32*)(I2C1_BASE + I2C_OAR1))
#define I2C1_OAR2		(*(volatile u32*)(I2C1_BASE + I2C_OAR2))
#define I2C1_DR			(*(volatile u32*)(I2C1_BASE + I2C_DR))
#define I2C1_SR1		(*(volatile u32*)(I2C1_BASE + I2C_SR1))
#define I2C1_SR2		(*(volatile u32*)(I2C1_BASE + I2C_SR2))
#define I2C1_CCR		(*(volatile u32*)(I2C1_BASE + I2C_CCR))
#define I2C1_TRISE		(*(volatile u32*)(I2C1_BASE + I2C_TRISE))

#define I2C2_CR1		(*(volatile u32*)(I2C1_BASE + I2C_CR1))
#define I2C2_CR2		(*(volatile u32*)(I2C1_BASE + I2C_CR2))
#define I2C2_OAR1		(*(volatile u32*)(I2C1_BASE + I2C_OAR1))
#define I2C2_OAR2		(*(volatile u32*)(I2C1_BASE + I2C_OAR2))
#define I2C2_DR			(*(volatile u32*)(I2C1_BASE + I2C_DR))
#define I2C2_SR1		(*(volatile u32*)(I2C1_BASE + I2C_SR1))
#define I2C2_SR2		(*(volatile u32*)(I2C1_BASE + I2C_SR2))
#define I2C2_CCR		(*(volatile u32*)(I2C1_BASE + I2C_CCR))
#define I2C2_TRISE		(*(volatile u32*)(I2C1_BASE + I2C_TRISE))

#define I2C_read (uint8_t)1
#define I2C_write (uint8_t)0

////////////////////i2c1///////////////////////////

void I2C1_clock_enable(void);

void I2C1_Init(void);

void I2C1_Start(void);

void I2C1_Send_Address(uint8_t address, uint8_t RW);

void I2C1_Send_Data(uint8_t data);

uint8_t I2C1_Receive_Data(bool sendACK);

void I2C1_Stop(void);
