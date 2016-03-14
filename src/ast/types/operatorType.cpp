#include "ast/types/operatorType.h"

namespace ast {

	namespace types {

		std::map<operatorType, char> operatorNames = {
			{operatorType::PLUS, '+'},
			{operatorType::MINUS, '-'},
			{operatorType::TIMES, '*'},
			{operatorType::DIVISION, '/'},
		};

		char operatorName(operatorType type) {
			return operatorNames[type];
		}

	}

}