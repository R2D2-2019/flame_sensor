#pragma once

#include <base_module.hpp>
#include <comm.hpp>
#include <hwlib.hpp>


 class test_module : public r2d2::base_module_c {
 public:
	/**
	 * The constructor initializes:
	 * base_module_c
	 *
	 * @param comm
	 */
	test_module(r2d2::base_comm_c &comm)
			: base_module_c(comm) {
			comm.listen_for_frames({r2d2::frame_type::FLAME_DETECTION});
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