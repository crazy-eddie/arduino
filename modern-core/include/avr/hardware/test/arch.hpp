#ifndef AVR_HARDWARE_TEST_HPP
#define AVR_HARDWARE_TEST_HPP

#include "../../pins.hpp"
#include "ports.hpp"
#include "../tags.hpp"

namespace avr { namespace hardware { namespace test {


struct arch_
{
    static bool SREG;
    static void cli();
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

        *(pin.port.mode_register()) |= pin.mask;

        SREG = old;
    }

    template < typename Pin >
    static void high(Pin pin)
    {
        auto const old = SREG;
        cli();

        *(pin.port.output_register()) |= pin.mask;

        SREG = old;
    }

    template < typename Pin >
    static void low(Pin pin)
    {
        auto const old = SREG;
        cli();

        *(pin.port.output_register()) &= ~pin.mask;

        SREG = old;
    }

    constexpr arch_() {}
};

bool arch_::SREG = false;

}}}



#endif
