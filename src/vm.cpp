#include <iostream>
#include "vm.hpp"

void VM::Process(Module& module)
{
	stack_ = std::stack<int>();
	ip_ = module.entryPoint;
	bool isRunning = true;
	int idx;
	std::string str;
	while(isRunning) {
		//char c;
		//std::cin >> c;
		auto instruction = module.instructions[ip_];
		instruction.Trace();
		switch (instruction.opcode) {
		case PUSHI:
			stack_.push(instruction.arg1);
			ip_++;
			break;
		case JUMP:
			ip_ = stack_.top();
			stack_.pop();
			break;
		case RETURN:
			ip_ = stack_.top();
			stack_.pop();
			break;
		case PRINT:
			idx = stack_.top();
			stack_.pop();
			str = module.stringTable.GetStringByIndex(idx);
			std::cout << str << std::endl;
			ip_++;
			break;
		case HLT:
			isRunning = false;
		}
		std::cout << "IP: " << ip_ << std::endl;
	}
}
