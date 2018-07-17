#pragma once
#include "RWL.h"
#include <thread>

RWL rwl;

void write()
{
	rwl.start_write();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	rwl.stop_write();
}

void read()
{
	rwl.start_read();
	std::this_thread::sleep_for(std::chrono::seconds(2));
	rwl.stop_read();
}

int main()
{
	std::thread r1(read);
	std::thread r2(read);
	std::thread w1(write);
	std::thread r3(read);
	std::thread r4(read);
	std::thread w2(write);

	r1.join();
	r2.join();
	w1.join();
	r3.join();
	r4.join();
	w2.join();
	return 0;
}