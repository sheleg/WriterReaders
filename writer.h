#pragma once
#include <iostream>
#include <string>

class writer
{
	std::ostream& stream_;
	writer* writer_ = nullptr;

	writer(std::ostream& stream)
		: stream_(stream) {}

public:
	writer * get_writer(std::ostream& stream)
	{
		if (writer_ == nullptr)
		{
			writer_ = new writer(stream);
		}

		return writer_;
	}

	void write(std::string data)
	{
		stream_ << data;
	}
};