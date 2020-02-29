//
// Created by Dmitry Rybakov on 29/02/16.
//

#include <iterator>
#include "symbol_table.hpp"

size_t SymbolTable::size() const
{
    return table_.size();
}

void SymbolTable::Put(std::shared_ptr<Nameable> item)
{
    table_[item->name()] = item;
}

std::shared_ptr<Nameable> SymbolTable::Get(const std::string &name)
{
    auto item = table_.find(name);
    if (item == table_.end()) {
        return nullptr;
    }
    return item->second;
}

SymbolTable::Iterator SymbolTable::GetIterator()
{
    return Iterator(table_.begin(), table_.end());
}

SymbolTable::Iterator::Iterator(tableIterator iterator, tableIterator end)
: iterator_(iterator), end_(end)
{
    
}

bool SymbolTable::Iterator::hasNext()
{
    return iterator_ != end_;
}

std::shared_ptr<Nameable> SymbolTable::Iterator::next()
{
    auto result = iterator_->second;
    iterator_++;
    return result;
}
