#pragma once
#include"Lexical/Core.h"
#include"Lexical/Lexan/Colision.h"
#include"amcpch.h"
namespace Amc {

	class AMC_API Operater {
	public:
		bool check(char c, const std::string& stringI) {
			if (c == '{')
				para = true;
			if (c == '(' && para && stringI == "id") { para = false; return para; }
			if (c == 59 || c == 123 || c == 125 || c == '^'||c >= 40 && c < 43) {
				if (string + c == "!=" || string + c == ">=" || string + c == "<=" || string + c == "||" || string + c == "&&" || string + c == "==" || string.empty()) {
					string += c;
					return true;
				}
			}

			switch (c)
			{
			case '!':
			case ',':
			case '=':
			case '>':
			case '<':
			case '&':
			case '|':
			case '+':
			case '-':
			case '%':
			case '[':
			case ']':
			case '{':
			case '}':
			case '/':
				if (c == '{')
					para = true;
				if (string+c == "!=" || string + c == "//" || string+c == ">=" || string+c == "<=" || string+c == "||" || string+c == "&&"||string+c == "==" ||string.empty()) {
					string += c;
					return true;
				}
			default:
				return false;
				}

		}
		bool comment() {
			return (string == "//" ? true : false);
		}
		bool print(int row, int col) {
			if (string == "//")return false;
			if (string.length() == 1) {
				if (string == "|" || string == "&") {
					ss << string << "\t unvaild operater " << "line(" << row << ")" << "col(" << col << ")" << "\n";
					AMC_CORE_ERROR("{} {} {} {}) col({})", string, "\t unvalid operater", "line(", row, col);
					valid = false;
					return false;
				}
				ss << string << "\n";
				AMC_CORE_TRACE("{} {}", string, "\t operater");
				return true;
			}
			else {
				if(string=="!=" || string == ">=" || string == "<=" || string == "||" || string == "&&" || string == "==") {
					ss << string << "\n";
					AMC_CORE_TRACE("{} {}", string, "\t operater");
					return true;
					}
			}
			ss << string << "\t unvaild operater " << "line(" << row << ")" << "col(" << col << ")" << "\n";
			AMC_CORE_ERROR("{} {} {} {}) col({})", string, "\t unvalid operater", "line(",row,col);
			valid = false;
			return false;
			string.clear();
		}
		void rest() { string.clear(); }
	private:
		std::string string = "";
	};
}