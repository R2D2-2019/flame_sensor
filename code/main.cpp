#include <comm.hpp>
#include <hwlib.hpp>
#include <module.hpp>
#include <example_controller.hpp>


int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    hwlib::cout << "Starting up...";

    // Status led
    auto led = hwlib::target::pin_out(hwlib::target::pins::d13);

    // analog pins
	auto test_pin_1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a4);
	auto test_pin_2 = hwlib::target::pin_adc(hwlib::target::ad_pins::a3);
	auto test_pin_3 = hwlib::target::pin_adc(hwlib::target::ad_pins::a2);
	auto test_pin_4 = hwlib::target::pin_adc(hwlib::target::ad_pins::a1);
	auto test_pin_5 = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);

    r2d2::comm_c comm;

    r2d2::flame_sensor::flame_sensor_c flame_sensor =
        r2d2::flame_sensor::flame_sensor_c(&test_pin_1, &test_pin_2, &test_pin_3,
                                           &test_pin_4, &test_pin_5, 2000, 40,
                                           120);

    r2d2::flame_sensor::module_c module =
        r2d2::flame_sensor::module_c(comm, &flame_sensor);

//    	test_module module = test_module(comm);

    for (;;) {
        module.process();

        led.write(true);
        hwlib::wait_ms(50);
        led.write(false);
        hwlib::wait_ms(50);
    }
}