#include <stdio.h>

#include "hardware/pwm.h"
#include "pico/stdlib.h"

int main(void) {
	stdio_init_all();

	while (true)
		sleep_ms(1000);

	return 0;
}
