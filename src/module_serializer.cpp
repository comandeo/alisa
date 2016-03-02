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
	serialize(outputFile, module->typeTable);
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
	deserialize(inputFile, module->typeTable);
	return module;
}
void ModuleSerializerImpl::serialize(std::ofstream& outputFile, SymbolTable& symbolTable)
{
	uint32_t tableNameSize = static_cast<uint32_t>(symbolTable.size());
	outputFile.write(reinterpret_cast<char*>(&tableNameSize), sizeof(uint32_t));
	for (auto iterator = symbolTable.GetIterator(); iterator.hasNext(); ) {
		auto tableEntry = iterator.next();
		logger_->Debug("Type to be serialized");
		logger_->Debug(tableEntry->name());
		uint32_t typeNameSize = static_cast<uint32_t>(tableEntry->name().size());
		outputFile.write(reinterpret_cast<char*>(&typeNameSize), sizeof(uint32_t));
		outputFile.write(tableEntry->name().c_str(), typeNameSize);
	}
}

void ModuleSerializerImpl::deserialize(std::ifstream& inputFile, SymbolTable& symbolTable)
{
	using namespace std;
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
		auto type = make_shared<Type>();
		type->setName(string(nameBuffer));
		delete[] nameBuffer;
		symbolTable.Put(type);
		logger_->Debug("Type loaded");
		logger_->Debug(type->name());
	}
}
