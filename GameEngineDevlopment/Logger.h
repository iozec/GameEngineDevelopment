#pragma once
#include <string>

class Logger
{
private:
	static Logger* _instance;
public:
	static Logger* instance();
	void WriteToFile(const std::string& buffer);
};

