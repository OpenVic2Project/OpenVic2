#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <vector>
#include <chrono>

namespace OpenVic2 {
	class Simulation : public godot::Object {
		GDCLASS(Simulation, godot::Object)
		std::vector<uint64_t> exampleProvinces;

		struct Date {
		private:
			uint64_t year;
			uint64_t month;
			uint64_t day;

		public:
			Date();
			~Date();
			Date(uint64_t day, uint64_t month, uint64_t year);

			void incrementDate();
			void setDate(uint64_t day, uint64_t month, uint64_t year);
			Date getDate();

		};

		enum class Speed { Speed1 = 4000, Speed2 = 3000, Speed3 = 2000, Speed4 = 1000, Speed5 = 100, Speed6 = 1 };

		//BEGIN BOILERPLATE
		static Simulation* _simulation;

		private:
		std::chrono::time_point<std::chrono::high_resolution_clock> lastPolledTime;
		bool isPaused;
		Date inGameDate;
		Speed currentSpeed;


		protected:
		static void _bind_methods() {
			godot::ClassDB::bind_method(godot::D_METHOD("conductSimulationStep"), &Simulation::conductSimulationStep);
			godot::ClassDB::bind_method(godot::D_METHOD("queryProvinceSize"), &Simulation::queryProvinceSize);
		}

		public:
		inline static Simulation* get_singleton() { return _simulation; }
		int getCurrentTime();
		void setCurrentTime(std::chrono::time_point<std::chrono::high_resolution_clock> time);
		void togglePauseState();
		void getPauseState();
		void increaseSimulationSpeed();
		void decreaseSimulationSpeed();
		void setSimulationSpeed(int speed);
		int getSimulationSpeed();


		inline Simulation() {
			ERR_FAIL_COND(_simulation != nullptr);
			_simulation = this;
			this->lastPolledTime = std::chrono::high_resolution_clock::now();
			this->isPaused = false;
			this->inGameDate = Date(1,1,1836);
			this->currentSpeed = Speed::Speed1;
			exampleProvinces.resize(10, 1);
		}
		inline ~Simulation() {
			ERR_FAIL_COND(_simulation != this);
			_simulation = nullptr;
		}
		//END BOILERPLATE

		inline void conductSimulationStep() {
			for (uint64_t x = 0; x < exampleProvinces.size(); x++) {
				exampleProvinces[x] += (x + 1);
			}
		}

		inline uint64_t queryProvinceSize(uint64_t provinceID) {
			if (provinceID >= exampleProvinces.size()) {
				return 0;
			}
			return exampleProvinces[provinceID];
		}

		void conditionallyAdvanceSimulation();
	};

	Simulation* Simulation::_simulation = nullptr;
}
