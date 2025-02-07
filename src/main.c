#include <stdio.h>

#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "pico/stdlib.h"

#define SERVO_PWM_PIN 22

int main(void) {
	stdio_init_all();

	const uint32_t wrap = 62500;
	const float clock_div = 40.0f;
	const float duty_cycle_f = 0.75f;

	const uint32_t duty_cycle = (uint32_t)(wrap * duty_cycle_f);

	gpio_set_function(SERVO_PWM_PIN, GPIO_FUNC_PWM);
	uint slice = pwm_gpio_to_slice_num(SERVO_PWM_PIN);
	pwm_set_clkdiv(slice, clock_div);
	pwm_set_wrap(slice, wrap);
	pwm_set_gpio_level(SERVO_PWM_PIN, duty_cycle);
	pwm_set_enabled(slice, true);

	while (true)
		sleep_ms(1000);

	return 0;
}
