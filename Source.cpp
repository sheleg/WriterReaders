#pragma once
#include "reader.h"
#include "writer.h"
#include <fstream>

int main()
{
	std::ofstream fout("data.txt");
	writer<std::ofstream> writer_ (fout);
	writer_.write("HELLO\n");
	fout.close();

	std::ifstream fin("data.txt");
	reader<std::ifstream> reader_(fin);
	std::cout << reader_.read();
	fin.close();

	return 0;
}