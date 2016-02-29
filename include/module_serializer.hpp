#ifndef __MODULE_SERIALIZER_H
#define __MODULE_SERIALIZER_H 1

#include <memory>
#include "logger.hpp"
#include "module.hpp"

class ModuleSerializer
{
public:
	virtual void Serialize(const char* filename, std::shared_ptr<Module> module) = 0;
	virtual std::shared_ptr<Module> Deserialize(const char* filename) = 0;
};

class ModuleSerializerImpl : public ModuleSerializer
{
public:
	virtual void Serialize(const char* filename, std::shared_ptr<Module> module);
	virtual std::shared_ptr<Module> Deserialize(const char* filename);
private:
	std::shared_ptr<Logger> logger_ = LoggerFactory::GetLogger("ModuleSerializerImpl");
};

#endif
