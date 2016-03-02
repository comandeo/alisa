//
// Created by Dmitry Rybakov on 29/02/16.
//

#ifndef ALISA_NAMEABLE_HPP
#define ALISA_NAMEABLE_HPP

#include <string>

class Nameable
{
public:
	virtual std::string name() const = 0;
	virtual void setName(const std::string& name) = 0;
};


#endif //ALISA_NAMEABLE_HPP
