#pragma once
#include"Lexical/Core.h"
#include"Lexical/Lexan/Colision.h"
#include"amcpch.h"
namespace Amc {

	enum class numberenum {
		NONE = -1,
		INT,
		REAL,
		STRING,
		MINS

	};
	class AMC_API Numbers{
	public:
		Numbers():
			enumnumber(numberenum::NONE){
			hashnumber[0] = (0);
			hashnumber[1] = (1);
			hashnumber[2] = (2);
			hashnumber[3] = (3);
			hashnumber[4] = (4);
			hashnumber[5] = (5);
			hashnumber[6] = (6);
			hashnumber[7] = (7);
			hashnumber[8] = (8);
			hashnumber[9] = (9);
		}
		bool check(char x) {
			if (x == '-' || x == '+')
				return true;
			if (x == '.') {
				if(enumnumber!= numberenum::REAL &&enumnumber != numberenum::STRING)
					enumnumber = numberenum::REAL;
				return true;
			}
			//else if(!stringNumber.empty()&&( x<'0'||x>'9'))
			int code = (x-'0') % 10;
			if (hashnumber[code] == x - '0') {
				if(enumnumber != numberenum::REAL && enumnumber != numberenum::STRING)
					enumnumber = numberenum::INT;
				return true;
			}
			if(enumnumber != numberenum::NONE )
			enumnumber = numberenum::STRING;
			return false;
		}
		bool print(const std::string& string, int row, int col) {
			if (string[0] != '-' && string[0] != '+' && string[0] != '.' && (string[0] < '0' || string[0]>'9')) return false;
			if (string.find_last_of('-') != 0 && string.find_last_of('-') != std::string::npos || enumnumber == numberenum::STRING || string.find('.') == string.length()-1) {
				//std::cout << string << "\t unvalid nubmer\n";
				ss << string << "\t unvaild number " << "line(" << row << ")" << "col(" << col << ")"<<"\n";
				AMC_CORE_ERROR("{} {} {} {}) col({})", string, "\t unvalid number", "line(", row, col);
				valid = false;
				return true;
			}

			if (string[0] != '-' && string[0] != '+' && string[0] != '.' && (string[0] < '0' || string[0]>'9')) return false;
			if (enumnumber==numberenum::NONE || string.empty())
				return false;
	
			else {
				ss <<((enumnumber == numberenum::REAL ? "realLiteral" : "intLiteral"))<<"\n";
				AMC_CORE_TRACE("{} {}", string, (enumnumber == numberenum::REAL ? "\t real_litteral" : "\t int_litteral"));
			}
			//	std::cout << string << (enumnumber == numberenum::REAL ? "\treal_litteral\n" : "\tint_litteral\n");
			return true;		}
		void reset() {
			enumnumber = numberenum::NONE;
		}
	private:
		int hashnumber[10];
		numberenum enumnumber;
	};
}