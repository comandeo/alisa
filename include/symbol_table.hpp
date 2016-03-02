//
// Created by Dmitry Rybakov on 29/02/16.
//

#ifndef ALISA_SYMBOL_TABLE_HPP
#define ALISA_SYMBOL_TABLE_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include "nameable.hpp"

class SymbolTable
{
public:
	typedef std::unordered_map<std::string, std::shared_ptr<Nameable>>::iterator tableIterator;

	class Iterator {
	public:
		Iterator(tableIterator iterator, tableIterator end);
		std::shared_ptr<Nameable> next();
		bool hasNext();
	private:
		tableIterator iterator_;
		tableIterator end_;
	};

public:
	void Put(std::shared_ptr<Nameable> item);
	std::shared_ptr<Nameable> Get(const std::string& name);
	size_t size() const;
	SymbolTable::Iterator GetIterator();
private:
	std::unordered_map<std::string, std::shared_ptr<Nameable>> table_;
};

#endif //ALISA_SYMBOL_TABLE_HPP
