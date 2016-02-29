#include <iostream>
#include "logger.hpp"

void AbstractLogger::Debug(const std::string& message)
{
	Debug(message.c_str());
}

void AbstractLogger::Info(const std::string& message)
{
	Info(message.c_str());
}

StdoutLogger::StdoutLogger(const char* context, LogLevel minLogLevel)
	: context_(context), minLogLevel_(minLogLevel)
{

}

void StdoutLogger::Debug(const char* message)
{
	trace(message, DEBUG);
}

void StdoutLogger::Info(const char* message)
{
	trace(message, INFO);
}

void StdoutLogger::trace(const char* message, LogLevel level)
{
	if (level < minLogLevel_) {
		return;
	}
	std::string msg = "";
	switch (level) {
	case DEBUG:
		msg.append("[DEBUG]");
		break;
	case INFO:
		msg.append("[INFO]");
		break;
	default:
		msg.append("[UNKNOWN]");
	}
	msg.append(" [");
	msg.append(context_);
	msg.append("]: ");
	msg.append(message);
	std::cout << msg << std::endl;
}

std::shared_ptr<Logger> LoggerFactory::GetLogger(const char* context)
{
	return std::make_shared<StdoutLogger>(context, DEBUG);
}
