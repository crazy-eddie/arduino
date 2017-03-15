#ifndef AVR_HARDWARE_STANDARD_ARCH_HPP
#define AVR_HARDWARE_STANDARD_ARCH_HPP

#include <Arduino.h>

#include "../tags.hpp"
#include "../../../mpl/integral_constant.hpp"

#include "ports.hpp"

namespace avr { namespace hardware { namespace standard {

struct empty_pins
{
    constexpr empty_pins(){}
};

template < typename PinCollection = empty_pins >
struct arch_
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

    template < typename PinTag, typename Port, typename Mask >
    constexpr arch_<> register_pin(PinTag pin, Port port, Mask mask)
    {
        return arch_<>{};
    }

    constexpr arch_() {}

private:
    PinCollection pins;
};

//constexpr auto arch = arch_<>{};
//constexpr arch_<> arch;
constexpr arch_<> arch() { return arch_<>{}; } // why does this work when the above doesn't?

#define BV(X) mpl::integral_constant<uint8_t, _BV(5)>{}

constexpr auto standard = arch()
        .register_pin(pin13, ports::PB, BV(5));
    ;

/*
 * constexpr auto standard = arch.register_pin(pin13, PB, i<_BV(5)>{});
 * constexpr auto pgm_hardware_initializer = standard.set_mode(pin13, output);
 *
 * auto const pgm_hardware = pgm_hardware_initializer.init();
 *
 * auto const pin = pgm_hardware.pin(pin13);
 * pin.high();
 */

}}} // avr::hardware::standard


#endif
