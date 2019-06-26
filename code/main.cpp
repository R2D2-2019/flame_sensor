#include <comm.hpp>
#include <mock_bus.hpp>
#include <module.hpp>
#include <hwlib.hpp>


class test_module : public r2d2::base_module_c {
public:
	/**
	 * The constructor initializes:
	 * base_module_c
	 * the pointer to the flame_sensor
	 *
	 * @param comm
	 * @param flame_sensor
	 */
	test_module(r2d2::base_comm_c &comm)
			: base_module_c(comm) {
			comm.listen_for_frames({r2d2::frame_type::ALL});
	}

	/**
	 * Let the module process data.
	 */
	void process() override {
		auto led = hwlib::target::pin_out(hwlib::target::pins::d13);
		led.write(true);
		comm.request(r2d2::frame_type::FLAME_DETECTION);

		while (comm.has_data()) {
			auto frame = comm.get_data();

			// This module doesn't handle requests
			if (!frame.request) {
				const auto flame_detected = frame.as_frame_type<
						r2d2::frame_type::FLAME_DETECTION
				>().flame_detected;

				const auto flame_angle = frame.as_frame_type<
						r2d2::frame_type::FLAME_DETECTION
				>().flame_angle;

				if (flame_detected) {
					hwlib::cout << flame_angle << hwlib::endl;
				} else {
					hwlib::cout << "no flames" << hwlib::endl;
				}
			}
		}
		hwlib::wait_ms(10);
		led.write(false);
	}
};


int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    hwlib::cout << "Starting up...";

    // analog pins
    auto test_pin_1 = hwlib::target::pin_adc(hwlib::target::ad_pins::a4);
    auto test_pin_2 = hwlib::target::pin_adc(hwlib::target::ad_pins::a3);
    auto test_pin_3 = hwlib::target::pin_adc(hwlib::target::ad_pins::a2);
    auto test_pin_4 = hwlib::target::pin_adc(hwlib::target::ad_pins::a1);
    auto test_pin_5 = hwlib::target::pin_adc(hwlib::target::ad_pins::a0);

    r2d2::comm_c comm;

//	r2d2::flame_sensor::flame_sensor_c flame_sensor =
//			r2d2::flame_sensor::flame_sensor_c(test_pin_1, test_pin_2, test_pin_3,
//											   test_pin_4, test_pin_5, 2000, 40,
//											   120);
//
//	r2d2::flame_sensor::module_c module = r2d2::flame_sensor::module_c(comm, &flame_sensor);

	test_module module = test_module(comm);

	for (;;) {
        module.process();

        hwlib::wait_ms(1000);
  }
}