#include <flame_sensor.hpp>

namespace r2d2::flame_sensor {

    flame_sensor_c::flame_sensor_c(
        hwlib::adc *ir_led_1, hwlib::adc *ir_led_2,
        hwlib::adc *ir_led_3, hwlib::adc *ir_led_4,
        hwlib::adc *ir_led_5, unsigned int flame_threshhold,
        unsigned int threshhold_offset, unsigned int total_detection_angle)
        : leds{ir_led_1, ir_led_2, ir_led_3, ir_led_4, ir_led_5},
          flame_threshhold(flame_threshhold),
          threshhold_error(threshhold_offset),
          total_detection_angle(total_detection_angle) {
    }

    unsigned int flame_sensor_c::get_sensor_average() {
        unsigned int sensor_average = 0;

        for (auto led : leds) {
            sensor_average += led->read();
        }
        sensor_average = (sensor_average / leds.size());
        return sensor_average;
    }

    unsigned int flame_sensor_c::get_flame_threshhold() {
        return flame_threshhold;
    }

    bool flame_sensor_c::is_flame_detected() {
        bool return_value = 0;
        unsigned int sensor_average = get_sensor_average();

        for (size_t i = 0; i < leds.size(); ++i) {
            return_value += is_single_flame_detected(leds[i], sensor_average);
        }
        return return_value;
    }

    bool flame_sensor_c::is_single_flame_detected(
        hwlib::adc *pin_to_check, unsigned int sensor_average) {
        return (pin_to_check->read() >= flame_threshhold ||
                pin_to_check->read() >=
                    (sensor_average * (threshhold_error + 100)) / 100);
    }

    int flame_sensor_c::get_flame_direction() {
        int return_value = 0;

        unsigned int sensor_average = get_sensor_average();
        unsigned int sensor_total = sensor_average * leds.size();

        for (size_t i = 0; i < leds.size(); ++i) {
            int led_percentage = (leds[i]->read() * 100 / sensor_total);
            return_value += (led_percentage * ((total_detection_angle / (leds.size() - 1)) * i));
        }
        return (return_value / 100 - (total_detection_angle / 2)) * 2;
    }
} // namespace r2d2::flame_sensor