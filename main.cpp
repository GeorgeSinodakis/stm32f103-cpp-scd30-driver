#include <stdint.h>
#include <string>
#include <vector>
#include "nvic.h"
#include "tim2345.h"
#include "delay.h"
#include "rcc.h"
#include "gpio.h"
#include "adc.h"
#include "st7735.h"
#include "i2c.h"
#include "scd30.h"

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

using namespace std;

int main(void)
{
	clock_72Mhz();
	Led_init();

	st7735_init(4);
	st7735_fill(BLACK);

	ms(3000);
	scd30 sensor;
	sensor.triggerContinuousMeasurement(1009);
	sensor.AutomaticSelfCalibration(true);

	string str;

	while (1)
	{
		ms(3000);
		if (sensor.getDataReadyStatus())
			sensor.readMeasurement();
		st7735_fill(BLACK);
		st7735_print_str(5, 5, 2, WHITE, BLACK, "CO2:");
		str = to_string(sensor.co2);
		str.erase(str.end() - 4, str.end());
		st7735_print_str(5, 25, 2, WHITE, BLACK, str);

		st7735_print_str(5, 45, 2, WHITE, BLACK, "Temperature:");
		str = to_string(sensor.temperature);
		str.erase(str.end() - 4, str.end());
		st7735_print_str(5, 65, 2, WHITE, BLACK, str);

		st7735_print_str(5, 85, 2, WHITE, BLACK, "Humidity:");
		str = to_string(sensor.humidity);
		str.erase(str.end() - 4, str.end());
		st7735_print_str(5, 105, 2, WHITE, BLACK, str);
		GPIOB_ODR ^= 1<<12;
	}
}