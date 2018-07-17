#pragma once
#include <iostream>
#include <mutex>

class RWL
{
private:
	std::mutex mutex_;

	std::condition_variable reader_cv_;
	std::condition_variable writer_cv_;

	int reader_count_ = 0;
	int writer_count_ = 0;

	bool is_writer_active_ = false;

public:
	RWL() {}

	void start_read();
	void stop_read();

	void start_write();
	void stop_write();
};