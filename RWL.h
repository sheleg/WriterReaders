#pragma once
#include <mutex>

class RWL
{
	std::mutex writer_mutex_;
	std::mutex reader_mutex_;

	std::condition_variable writer_cv_;
	std::condition_variable reader_cv_;

	int writer_count_ = 0;
	int reader_count_ = 0;

	bool is_writer_active_ = false;

public:
	void startRead();

	void startWrite();

	void stopRead();

	void stopWrite();
};