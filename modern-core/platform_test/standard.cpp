
#include "../include/avr/pins.hpp"
#include "../include/avr/hardware/standard/arch.hpp"
#include "../include/avr/hardware/standard/ports.hpp"
#include "../include/avr/hardware/standard/pins.hpp"

using namespace avr::hardware::standard;
using namespace avr::hardware;

using namespace avr;

void setup()
{
    arch_<>::set_mode(pins::pin(pin13), pin_config::output);
}

void loop() {

    arch_<>::high(pins::pin(pin13));
    delay(1000);              // wait for a second
    arch_<>::low(pins::pin(pin13));
    delay(500);              // wait for a second
}





/*
 *
 * original:
text       data     bss     dec     hex filename
   1064       0       9    1073     431 /home/satan/github/arduino/modern-core/platform/platform_test/standard.elf
      0       0       0       0       0 /home/satan/github/arduino/modern-core/platform/platform_test/standard.eep
 *
 * set_mode:
text       data     bss     dec     hex filename
    934       0       9     943     3af /home/satan/github/arduino/modern-core/platform/platform_test/standard.elf
      0       0       0       0       0 /home/satan/github/arduino/modern-core/platform/platform_test/standard.eep
 *
 * high/low:
text       data     bss     dec     hex filename
    690       0       9     699     2bb /home/satan/github/arduino/modern-core/platform/platform_test/standard.elf
      0       0       0       0       0 /home/satan/github/arduino/modern-core/platform/platform_test/standard.eep

 */
