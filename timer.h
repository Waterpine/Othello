#pragma once
#include <ctime>
class timer
{
	private:
		clock_t start_time;

	public:
		timer() { };
		void start()
		{
			start_time = clock();
		}
		int get_time()
		{
			clock_t now = clock();
			return now - start_time;
		}
		void restart()
		{
			start();
		}
};