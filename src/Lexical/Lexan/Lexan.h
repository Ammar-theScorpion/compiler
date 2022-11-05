#pragma once
#include"amcpch.h"
#include"Lexical/Core.h"
#include"Lexical/Lexan/Reserved.h"
#include"Lexical/Lexan/Operators.h"
#include"Lexical/Lexan/Numbers.h"
namespace Amc {

//#define EVENT_ClASS_TYPE(type)const char* GetEventType()const  {return (#type);}	 
//#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags()const override {return category;} 

	class __declspec(dllexport) Tooken {
		public:

			Tooken():
				row(1), col(0){
				std::cout << "Enter File Name:\t"; std::cin >> stringPath;
				valid = true;
				para = false;
				readFile();
			} 
			void readFile() {
				std::fstream fstream;
				std::string line;
				fstream.open(stringPath);
				std::stringstream stringstream[3];
				std::string string = "";
				char s = '-';
				while (std::getline(fstream, line)) {
					line.erase(0, line.find_first_not_of(" \t\r\n"));
					size_t length = line.length();

					for (int i = 0; i < length; i++)
					{
						string = "";
						bool isnumber = false;
						while ( i < length && line[i] != ' ' && line[i]!='\t' &&line[i] != '\n' && line[i] != '\r')
						{
						
							if (line[i] == '\"') {
								int at = line.find('\"');
								line.erase(0, at);
								int la = line.find('\"',1);
								if (la == std::string::npos) {
									ss << line.substr(0, line.length()) << "\t unvaild string_littral"<<"\n";
									AMC_CORE_ERROR("{} {}", line.substr(0, line.length()), "\t unvaild string_littral");
									valid = false;
									length = 0;
									line.clear();
								}
								if (reserved.check(line.substr(0, la + 1), false, row, i)) {
									line.erase(0, la + 1);
									i = -1;
									length = line.length();
								}
							}
							else if(reserved.getid(line[i]))
								string += line[i];
							else if (operators.comment()) {
								AMC_CORE_WARN("{} \t ({} {})", "//", line.substr(i + 1, length), " ignored comment");
								i = length;
								break;
							}
							else if((line[i] == '-' || line[i] == '+') &&(!i || s=='=')) {
								isnumber = number.check(line[i]);
								string += line[i];
							}
							else if (!operators.check(line[i], string)) {
									isnumber = number.check(line[i]);
								string += line[i];
							}
							else {
								 
								 if (number.print(string, row, i));
								 else {
									 if(line[i]=='(')
										 reserved.check(string, true, row, i);
									 else
										 reserved.check(string, false, row, i);
								 }
								if (i + 1 < length && operators.check(line[i + 1], string) && operators.print(row, i)) {
									operators.rest();
									i++;
								}
							
								else if (operators.print(row, i))
									operators.rest();
							
								string = "";
							}
							if(i>=0 && i<length)
								s = line[i];
							i++;
						}
						if (number.print(string, row, i));
						else
							reserved.check(string, false, row, i);
						if (string == "id(") {
							std::string t = "";
							string += " ";
							i++;
							while (line[i] == ' ')
								i++;
							while (line[i] != ')') {
								if (line[i] == ',') {
									AMC_CORE_TRACE("{} {}", ",", "\t ID");
									string += ", ";
									t = "";
								}
								else if (line[i] == ' ') {
									string += "id ";
									AMC_CORE_TRACE("{} {}", t, "\t ID");
									t = "";
								}
								else if (line[i] >= 'A' && line[i] <= 'z') {
									t += line[i];
								}
								else {
									valid = false;
									ss << t << "\t unvaild ID " << "line(" << row << ")" << "col(" << col << ")" << "\n";
								}
								i++;
							}
							string += ")";
							ss << string<<"\n";
						}
						string = "";
						reserved.set();
						number.reset();
						operators.rest();

					}
					reserved.set();
					std::cout << "\t--------------(" << row << ")---------------\n";
					++row;
				}
			}
			~Tooken(){
				std::ofstream ofstream;
				ofstream.open("lex.txt");
				ofstream << ss.str();
				ofstream.flush();
				ofstream.close();
			}
		private:
			Reserved reserved;
			Numbers number;
			Operater operators;
			std::string stringPath;
			int row;
			int col;
	};
}