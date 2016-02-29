#include <cstdint>
#include <algorithm>
#include <fstream>
#include "module_serializer.hpp"

const unsigned int sizeBytes = 4;

void ModuleSerializerImpl::Serialize(const char* filename, std::shared_ptr<Module> module)
{
	using namespace std;
	ofstream outputFile(filename, ios::out | ios::binary | ios::trunc);
	if (!outputFile.is_open()) {
		logger_->Info("Cannot open output file");
		throw "Cannot open output file";
	}
	// Write type table
	uint32_t tableNameSize = static_cast<uint32_t>(module->typeTable.size());
	outputFile.write(reinterpret_cast<char*>(&tableNameSize), sizeof(uint32_t));
	for (auto& typeEntry : module->typeTable) {
		uint32_t typeNameSize = static_cast<uint32_t>(typeEntry.second.name.size());
		outputFile.write(reinterpret_cast<char*>(&typeNameSize), sizeof(uint32_t));
		outputFile.write(typeEntry.second.name.c_str(), typeNameSize);
	}
}

std::shared_ptr<Module> ModuleSerializerImpl::Deserialize(const char* filename)
{
	using namespace std;
	shared_ptr<Module> module = make_shared<Module>();
	ifstream inputFile(filename, ios::in | ios::binary);
	if (!inputFile.is_open()) {
		logger_->Info("Cannot open input file");
		throw "Cannot open input file";
	}
	char sizeBuf[4] = {0};
	inputFile.read(sizeBuf, 4);
	uint32_t tableNameSize = *(reinterpret_cast<uint32_t*>(sizeBuf));
	logger_->Debug("Type table size is loaded");
	logger_->Debug(to_string(tableNameSize));
	for (int i = 0; i < tableNameSize; i++) {
		fill(sizeBuf, sizeBuf + 4, 0);
		inputFile.read(sizeBuf, 4);
		uint32_t typeNameSize = *(reinterpret_cast<uint32_t*>(sizeBuf));
		char* nameBuffer = new char[typeNameSize + 1]();
		inputFile.read(nameBuffer, typeNameSize);
		logger_->Debug(nameBuffer);
		Type type;
		type.name = string(nameBuffer);
		delete[] nameBuffer;
		module->typeTable[type.name] = type;
		logger_->Debug("Type loaded");
		logger_->Debug(type.name);
	}
	return module;
}
