#include "Logger.h"

Logger* Logger::_instance = NULL;

Logger* Logger::instance() {

	if (!_instance)
	{
		_instance = new Logger();
	}

	return _instance;
}
void Logger::WriteToFile(const std::string& buffer)
{
	FILE* logFile = NULL;

	fopen_s(&logFile, "error.log", "at");

	if (!logFile)
		return;

	fprintf_s(logFile, buffer.c_str());

	fclose(logFile);
}
