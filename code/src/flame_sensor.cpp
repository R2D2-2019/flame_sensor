#include <flame_sensor.hpp>

namespace r2d2::flame_sensor {
//    flame_sensor_c::flame_sensor_c(
//        hwlib::pin_oc &ir_led_1, hwlib::pin_oc &ir_led_2 = hwlib::pin_oc_dummy,
//        hwlib::pin_oc &ir_led_3 = hwlib::pin_oc_dummy,
//        hwlib::pin_oc &ir_led_4 = hwlib::pin_oc_dummy,
//        hwlib::pin_oc &ir_led_5 = hwlib::pin_oc_dummy,
//        int &flame_threshhold)
//        : ir_led_1(ir_led_1),
//          ir_led_2(ir_led_2),
//          ir_led_3(ir_led_3),
//          ir_led_4(ir_led_4),
//          ir_led_5(ir_led_5) {
//    }

	template<size_t SIZE, class T>
	size_t flame_sensor_c::array_size(T (&arr)[SIZE]) {
		return SIZE;
	}

	flame_sensor_c::flame_sensor_c(
			hwlib::target::pin_adc &ir_led_1,
			hwlib::target::pin_adc &ir_led_2,
			hwlib::target::pin_adc &ir_led_3,
			hwlib::target::pin_adc &ir_led_4,
			hwlib::target::pin_adc &ir_led_5,
			unsigned int flame_threshhold)
			: leds{ir_led_1, ir_led_2, ir_led_3, ir_led_4, ir_led_5},
			flame_threshhold(flame_threshhold){
	}

    bool flame_sensor_c::is_flame_detected() {
        bool return_value = 0;
        unsigned int total = 0;
        for(size_t i = 0; i < array_size(leds); ++i) {
        	hwlib::cout << (leds[i].read()) << " : ";
            if (leds[i].read() >= flame_threshhold) {
                return_value = 1;
            }
        }
        hwlib::wait_ms(100);
        return return_value;
    }

    int flame_sensor_c::get_flame_direction() {
        return 0;
    }
} // namespace r2d2::flame_sensor