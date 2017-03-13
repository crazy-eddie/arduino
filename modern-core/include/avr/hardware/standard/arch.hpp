#ifndef AVR_HARDWARE_STANDARD_ARCH_HPP
#define AVR_HARDWARE_STANDARD_ARCH_HPP

#include <Arduino.h>

#include "../tags.hpp"

#include "ports.hpp"

namespace avr { namespace hardware { namespace standard {

struct arch
{
    template < typename Pin >
    static void set_mode(Pin pin, pin_config::input_tag)
    {
        auto old = SREG;
        cli();

        *(pin.port.mode_register()) &= ~pin.mask;
        *(pin.port.output_register()) &= ~pin.mask;

        SREG = old;
    }

    template < typename Pin >
    static void set_mode(Pin pin, pin_config::output_tag)
    {
        auto old = SREG;
        cli();

        //*reinterpret_cast<volatile uint8_t*>(reg) |= mask;
        *(pin.port.mode_register()) |= pin.mask;

        SREG = old;
    }

    template < typename Pin >
    static void high(Pin pin)
    {
        auto const old = SREG;
        cli();

        //*reinterpret_cast<volatile uint8_t*>(reg) |= mask;
        *(pin.port.output_register()) |= pin.mask;

        SREG = old;
    }

    template < typename Pin >
    static void low(Pin pin)
    {
        auto const old = SREG;
        cli();

        //*reinterpret_cast<volatile uint8_t*>(reg) |= mask;
        *(pin.port.output_register()) &= ~pin.mask;

        SREG = old;
    }
};

}}} // avr::hardware::standard


#endif
