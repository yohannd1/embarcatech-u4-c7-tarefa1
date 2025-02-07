#include <stdio.h>

#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#define SERVO_PWM_PIN 22

const uint32_t wrap = 62500;
const float clock_div = 40.0f;

int main(void) {
	stdio_init_all();

	// (1) inicializando o pwm a 50Hz
	gpio_set_function(SERVO_PWM_PIN, GPIO_FUNC_PWM);
	uint slice = pwm_gpio_to_slice_num(SERVO_PWM_PIN);
	pwm_set_clkdiv(slice, clock_div);
	pwm_set_wrap(slice, wrap);
	pwm_set_enabled(slice, true);

	// (2) duty cycle de 0.12% para 180°, durante 5s
	pwm_set_gpio_level(SERVO_PWM_PIN, (uint32_t)(wrap * 0.12f));
	sleep_ms(5000);

	// (3) duty cycle de 0.0735% para 90°, durante 5s
	pwm_set_gpio_level(SERVO_PWM_PIN, (uint32_t)(wrap * 0.0735f));
	sleep_ms(5000);

	// (4) duty cycle de 0.025% para 0°, durante 5s
	pwm_set_gpio_level(SERVO_PWM_PIN, (uint32_t)(wrap * 0.025f));
	sleep_ms(5000);

	// (5)
	// 50Hz = 1/50 s = 20ms
	// Um ajuste de 5us seria um ajuste de 5us/20ms = 5us/20000us = 0.00025 no duty cycle
	float bound1 = 0.025f;
	float bound2 = 0.12f;
	float step = 0.00025f;
	while (true) {
		for (float dc = bound1; dc < bound2; dc += step) {
			pwm_set_gpio_level(SERVO_PWM_PIN, (uint32_t)(wrap * dc));
			sleep_ms(10);
		}
		for (float dc = bound2; dc > bound1; dc -= step) {
			pwm_set_gpio_level(SERVO_PWM_PIN, (uint32_t)(wrap * dc));
			sleep_ms(10);
		}
	}

	return 0;
}
