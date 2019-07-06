#include <hwlib.hpp>
#include <module.hpp>

#include <ostream>

#define CATCH_CONFIG_MAIN
#include <catch.hpp>


TEST_CASE("") {
	// analog pins
	auto test_pin_1 = hwlib::pin_adc_test();
	auto test_pin_2 = hwlib::pin_adc_test();
	auto test_pin_3 = hwlib::pin_adc_test();
	auto test_pin_4 = hwlib::pin_adc_test();
	auto test_pin_5 = hwlib::pin_adc_test();


	r2d2::flame_sensor::flame_sensor_c flame_sensor =
			r2d2::flame_sensor::flame_sensor_c(&test_pin_1, &test_pin_2, &test_pin_3,
											   &test_pin_4, &test_pin_5, 2000, 40,
											   120);

	test_pin_1.set_pin_value(0);
	test_pin_2.set_pin_value(0);
	test_pin_3.set_pin_value(0);
	test_pin_4.set_pin_value(0);
	test_pin_5.set_pin_value(4096);
	REQUIRE((flame_sensor.get_flame_direction() - 60) < 5);
}