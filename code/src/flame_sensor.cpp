#include <flame_sensor.hpp>

namespace r2d2::flame_sensor {

    flame_sensor_c::flame_sensor_c(hwlib::adc *ir_led_1, hwlib::adc *ir_led_2,
                                   hwlib::adc *ir_led_3, hwlib::adc *ir_led_4,
                                   hwlib::adc *ir_led_5,
                                   unsigned int flame_threshhold,
                                   unsigned int threshhold_offset,
                                   unsigned int total_detection_angle)
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

    bool flame_sensor_c::is_single_flame_detected(hwlib::adc *pin_to_check,
                                                  unsigned int sensor_average) {
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
            /*
             * Math to map a percentage from each led to an angle.
             * total detection angle / amount of leds -1 to get the angle each
             * led has that multiplied by the which led it is to get what angle
             * it is detecting that multiplied by the percentage it contributes
             * to the total fire detected by all the leds that added to an total
             * value for further calculation
             */
            return_value += (led_percentage *
                             ((total_detection_angle / (leds.size() - 1)) * i));
        }
        /*
         * return_value = total value gathered from the sensors with the
         * contribution of each led. total value / 100 because the value got
         * multiplied by 100 to make non float values for calculations that -
         * half the total detection range to get positive values in one
         * direction and negative values in the other that multiplied by 2 to
         * account for the ambient light and the impossibility for 1 sensor to
         * be getting values and not the others
         */
        return (return_value / 100 - (total_detection_angle / 2)) * 2;
    }
} // namespace r2d2::flame_sensor