#ifndef __LOGGER_H
#define __LOGGER_H 1

#include <memory>
#include <string>

enum LogLevel
{
	DEBUG,
	INFO
};

class Logger
{
public:
	virtual void Debug(const std::string& message) = 0;
	virtual void Debug(const char* message) = 0;
	virtual void Info(const std::string& message) = 0;
	virtual void Info(const char* message) = 0;
};

class AbstractLogger : public Logger
{
	virtual void Debug(const std::string& message);
	virtual void Debug(const char* message) = 0;
	virtual void Info(const std::string& message);
	virtual void Info(const char* message) = 0;
};

class StdoutLogger : public AbstractLogger
{
public:
	StdoutLogger(const char* context, LogLevel minLogLevel);
	virtual void Debug(const char* message);
	virtual void Info(const char* message);
private:
	void trace(const char* message, LogLevel level);
	LogLevel minLogLevel_;
	std::string context_;
};

class LoggerFactory
{
public:
	static std::shared_ptr<Logger> GetLogger(const char* context);
};

#endif
