#include <iostream>
#include "vm.hpp"

void VM::Process(Module& module)
{
	stack_ = std::stack<int>();
	ip_ = module.entryPoint;
	bool isRunning = true;
	int idx;
    int ret;
	std::string str;
	while(isRunning) {
		auto instruction = module.instructions[ip_];
		switch (instruction.opcode) {
        case Opcode::PUSHI:
			stack_.push(instruction.arg1);
			ip_++;
			break;
		case Opcode::JUMP:
			ip_ = stack_.top();
			stack_.pop();
			break;
		case Opcode::RETURN:
            ret = stack_.top();
            stack_.pop();
			ip_ = stack_.top();
			stack_.pop();
            stack_.push(ret);
			break;
		case Opcode::PRINT:
			idx = stack_.top();
			stack_.pop();
			str = module.stringTable.GetStringByIndex(idx);
			std::cout << str << std::endl;
			ip_++;
			break;
		case Opcode::HLT:
			isRunning = false;
		}
	}
}
