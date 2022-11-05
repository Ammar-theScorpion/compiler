#pragma once
#include"Lexical/Core.h"
#include"Lexical/Lexan/Colision.h"
#include"amcpch.h"
#include"Lexical/Log.h"
namespace Amc {

	class AMC_API Reserved{
		public:
			Reserved():id(false) {
				
				collision[9].fetch("write", "while"); 
				collision[1].fetch("break", "Breakpoint", "Open");
				collision[2].fetch("continue", "Create", "Close", "print" );
				collision[3].fetch("Delete", "decl", "do");
				collision[4].fetch("else", "endif", "endwhile", "endDecl", "Exit", "Exec", "read", "real", "return");
				collision[5].fetch("Fork", "string", "Seek");
				collision[8].fetch("if", "integer");
				collision[6].fetch("then");
				collision[12].fetch("main");
			}
			bool check(const std::string& string, bool fun, int row, int col) {
				
				if (string.empty())
					return false;
				int f = string.find_first_of("\"");
				int l = string.find_last_of("\"");
				if (l - f != 0 && l != -1 && f != -1) {
					ss << "stringLiteral" << "\n";
					AMC_CORE_TRACE("{} {}", string, "\t string_littral");
					return true;
				}
				else if (l - f != 0 || l != -1 || f != -1) {
					ss << string << "\t unvaild string_littral" << "\n";
					AMC_CORE_ERROR("{} {}",string, "\t unvaild string_littral");
					valid = false;
					return false;

				}
				char compar = 'a';
				if (string[0] <= 'a')
					compar -= 32;
				if (string[0] >= '0' && string[0] <= '9') {
					ss << string << "\t unvaild number " << "line("<< row<<")"<<"col("<<col<<")" << "\n";
					AMC_CORE_ERROR("{} {} {} {}) col({})", string, "\t unvalid number", "line(", row, col);
					valid = false;

					return false;
				}
				int code = (int)(string[0]-compar) % 13;
				if (code < 0 || collision[code].nodeHead == nullptr) {
					if (!isid(string)) {
						ss << string << "\t unvaild ID " << "line(" << row << ")" << "col(" << col << ")" << "\n";
						AMC_CORE_ERROR("{} {} {} {}) col({})", string, "\t unvalid ID", "line(", row, col);
						valid = false;
					}
					else {
						ss <<"id " << string << "\n";
						AMC_CORE_TRACE("{} {}", string, "\t ID");
					}
					return false;
				}

				std::string stringCo = collision[code].value();
				Node<std::string>* node = collision[code].nodeHead;
				while (node != nullptr && stringCo != string)
				{
					stringCo = node->string;
					node = node->next;
				}
				if (stringCo != string) {
					if (!isid(string)) {
						if (string != "id(") {
							ss << string << "\t unvaild ID " << "line(" << row << ")" << "col(" << col << ")" << "\n";
							AMC_CORE_ERROR("{} {} {} {}) col({})", string, "\t unvalid ID", "line(", row, col);
							valid = false;
						}
					}
					else {
						ss << "id " << string << "\n";
						AMC_CORE_TRACE("{} {}", string, "\t ID");
					}
					return false;
				}
				else {
					ss << string << "\n";
					AMC_CORE_WARN("{} {}", string, "\t reserved word");
				}
				id = ((string == "integer" || string == "real") ? true : false);
				return true;
			}
			void set() { id = false; }
			bool getid(char c) {
				if(c!='=' && c != ';')
					return id;
				id = false;
				return false;
			}
			bool isid(const std::string& string) {
				for(char c: string)
				{
					if (c < '0' || c>'9' && c < 'A' || c > 'Z' && c < 'a' || c > 'z')
						return false;
				}
				return true;
			}
		private:
			bool id;
			std::string currentString;
			Collision<std::string> collision[13];
	};
}