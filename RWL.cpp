#include "RWL.h"

void RWL::startRead()
{

	std::unique_lock<std::mutex> u_lock(writer_mutex_);
	writer_cv_.wait(u_lock, [this]() { return writer_count_ == 0 && !is_writer_active_; });

	std::lock_guard<std::mutex> l_guard(reader_mutex_);
	reader_count_++;
}

void RWL::startWrite()
{
	std::unique_lock<std::mutex> u_lock(writer_mutex_);
	writer_count_++;
	reader_cv_.wait(u_lock, [this]() { return reader_count_ == 0; });
	u_lock.unlock();

	writer_mutex_.lock();
	is_writer_active_ = true;
	writer_count_--;
}

void RWL::stopRead()
{
	std::lock_guard<std::mutex> l_guard(reader_mutex_);
	reader_count_--;
	reader_cv_.notify_one();
}

void RWL::stopWrite()
{
	is_writer_active_ = false;
	writer_mutex_.unlock();
	writer_cv_.notify_all();
}
