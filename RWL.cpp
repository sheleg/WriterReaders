#include "RWL.h"
#include <sstream>
#include <string>

std::mutex cout_mutex;

void RWL::start_read()
{
	std::unique_lock<std::mutex> u_lock(mutex_);
	reader_cv_.wait(u_lock, [this]() { return writer_count_ == 0 && !is_writer_active_; });
	++reader_count_;
}

void RWL::stop_read()
{
	{
		std::lock_guard<std::mutex> l_guard(mutex_);
		reader_count_--;
	}

	writer_cv_.notify_one();
}

void RWL::start_write()
{
	std::unique_lock<std::mutex> u_lock(mutex_);
	++writer_count_;
	writer_cv_.wait(u_lock, [this]() { return reader_count_ == 0 && !is_writer_active_; });
	u_lock.unlock();

	mutex_.lock();
	is_writer_active_ = true;
	--writer_count_;
}

void RWL::stop_write()
{
	is_writer_active_ = false;
	mutex_.unlock();

	if (writer_count_ != 0)
	{
		writer_cv_.notify_one();
	}
	else
	{
		reader_cv_.notify_all();
	}
}




