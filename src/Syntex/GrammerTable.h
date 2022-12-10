#pragma once
#include"amcpch.h"
#include"Lexical/Lexan/Colision.h"
namespace Amc {
	class AMC_API GrammerTable { 
	public:
		GrammerTable(const std::string& filePath) {
			set_file(filePath);
			set_grammer("globals functions mainFun");//0
			set_grammer("decls");
			set_grammer("decl moreDecls");
			set_grammer("");
			set_grammer("decl moreDecls");
			set_grammer("type id");
			set_grammer("array [ intLiteral ]");
			set_grammer("^ type id");
			set_grammer("integer");
			set_grammer("real");
			set_grammer("string");//10
			set_grammer("function moreFunctions");
			set_grammer("");
			set_grammer("function moreFunctions");
			set_grammer("returnType id ( paramList ) { body }");
			set_grammer("integer");
			set_grammer("real");
			set_grammer("string");
			set_grammer("void");
			set_grammer("decls");
			set_grammer("decls statements");//20
			set_grammer("statement moreStatements");
			set_grammer("");
			set_grammer("; statement moreStatements");
			set_grammer("assignmentStatement");
			set_grammer("ifStatement");
			set_grammer("whileStatement");
			set_grammer("inputStatement");
			set_grammer("outputStatement");
			set_grammer("functionCallStatement");
			set_grammer("id = expr");//30
			set_grammer("if ( cond ) then statement else statement endif");
			set_grammer("arg relOp arg");
			set_grammer("while ( cond ) statement endwhile");
			set_grammer("read ( id )");
			set_grammer("write ( expr )");
			set_grammer("id( exprList )");
			set_grammer("expr moreExpressions");
			set_grammer("");
			set_grammer(", expr moreExpressions");
			set_grammer("id");//40
			set_grammer("intLiteral");
			set_grammer("stringLiteral");
			set_grammer("realLiteral");
			set_grammer(">");
			set_grammer("<");
			set_grammer(">=");
			set_grammer("<=");
			set_grammer("!=");
			set_grammer("==");
			set_grammer("arg");
			set_grammer("( expr arithmOp expr )");
			set_grammer("+");
			set_grammer("*");
			set_grammer("-");
			set_grammer("/");
			set_grammer("%");
			set_grammer("main ( ) { statements }");
			set_table();
			self_check();
		}
		std::string get_grammer(int  id) const{
			return grammerVector[id];
		}
		void set_grammer(std::string && string) {
			this->grammerVector.push_back(string);
		}
		~GrammerTable(){
			grammerVector.clear();
		}
	private:
		void set_file(const std::string& filePath) {
			grammerString = "";
			std::fstream fstream;
			fstream.open(filePath);
			std::string line;
			while (std::getline(fstream, line)) {
				if (line.find("id(")!=std::string::npos) {
					grammerString += line+" ";
					continue;
				}
				size_t at = line.find(" ");
				if (at==-1)
					grammerString += line+" ";
				else {
					grammerString += line.substr(0, at)+" ";
				}
			}
		}

		std::string reverse(const std::string& string) {
			std::string temp = "";
			int j = string.length();
			int i = string.rfind(" ");
			if (i == -1)
				return string;
			while (true) {
				temp += string.substr(i + 1, j) + " ";
				j = i - 1;
				i = string.rfind(" ", i - 1);
				j -= i;
				if (i == -1) {
					temp += string.substr(0, string.find(" "));
					break;
				}
			}
			return temp;
		}

		void self_check() {
			grammerStack.push("program");
			int sp = 0;
			int u = 0;
			std::string sd = "";
			while (!grammerString.empty()) {
				if (grammerStack.empty()) {
					std::string f = grammerString.substr(u, grammerString.length());
					if(f.empty())
						return;
					AMC_CORE_ERROR("Unvaild input '{}' -> has no place in here",f);
					return;
				}
				std::string string = grammerStack.top();
				grammerStack.pop();
				for (size_t i = sp; i < u; i++)
					sd += " ";
				sp = u;
				std::string temp = grammerString.substr(u, grammerString.find(" ", u + 1) - u);
				short val = getGrammer(string, temp);

 				AMC_CORE_WARN("{}->[{}]", sd, string);
				AMC_CORE_WARN("{}|", sd);
				if (val == -2) {
					if(temp.empty())
						AMC_CORE_ERROR("Unvaild input ): A tooken is missing");
					else
						AMC_CORE_ERROR("Unvaild input ): '{}' has no place in here", temp);
					return;
				}
				else if (val == -1) {
					u = grammerString.find(" ", u+1);
					++u;
					AMC_CORE_TRACE("{}match\n", sd);
					AMC_CORE_TRACE("{}\n", ss);
					continue;
				}
				std::string stringStack = grammerVector[val];
				if (stringStack.empty()) {
				 
		 
					//++u;
					int t = ss.find(" ", u + 1);
					if (t == -1)
						t = ss.find(" ", u);
					ss = ss.substr(0, u) + stringStack + ss.substr(t, ss.length());
					AMC_CORE_TRACE("{}epsilon\n", sd);
					continue;
				}
				if (ss.empty())
					ss = stringStack;
				else {
					if (u != 0) {
						/* if (sp != 0) {
							int y = u;
							u = sp;
							sp = 0;
							ss = ss.substr(0, u) + stringStack + ss.substr(ss.find(" ", u + 1), ss.length());
							u = y;
						}*/
						int t = ss.find(" ", u + 1);
						if(t==-1)
							ss = ss.substr(0, u) + stringStack;
						else
							ss = ss.substr(0, u) + stringStack + ss.substr(t, ss.length());

					}
					else
						ss = stringStack + ss.substr(ss.find(" "), ss.length());
				}
 
				AMC_CORE_TRACE("{}\n", ss);
				stringStack = reverse(stringStack);
		 
				int i = -1, j = 0;
				while (true) {
					i=stringStack.find(" ", i+1);
					if (i == std::string::npos) {
						grammerStack.push(stringStack.substr(j, stringStack.length()));
						break;
					}
					grammerStack.push(stringStack.substr(j, i - j));
					j = i+1;
				}

			}
		}
		short getGrammer(const std::string& string, const std::string& string_value) {
			if (string == string_value) {
				return -1;
			}
			if (string == "endwhile") {
				std::cout << 1;
			}
			for (size_t i = 0; i < 29; i++){
				if (collision[i].value() == string) {
					Node<std::string>* node = collision[i].nodeHead->next;
					while (node != nullptr && node->string!=string_value)
					{
						node = node->next;
					}
					if (node!=nullptr)
						return node->grammer-1;
					return -2;
				}
				
			}
			return -2;
		}
		void set_table() {
			collision[0].fetch(1,1,1,1,1, "integer", "string", "real", "^", "array","program");
			collision[1].fetch(2,2,2,2,2, "integer", "string", "real", "^", "array","globals");
			collision[2].fetch(12,12,12,12,"void", "string", "real", "integer","functions");
			collision[3].fetch(58,"main","mainFun");
			collision[4].fetch(3, 3, 3, 3, 3, "integer", "string", "real", "^", "array", "decls");
			collision[5].fetch(6, 6, 6, 8, 7, "integer", "string", "real", "^", "array", "decl");
			collision[6].fetch(4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, "id(", "if", "while", "read", "write", "id", ")","integer", "string", "real", "^", "array", ";", "moreDecls");
			collision[7].fetch(11, 10, 9, "string", "real", "integer", "type");
			collision[8].fetch(15, 15, 15, 15,"void", "string", "real", "integer", "function");
			collision[9].fetch(14, 14, 14, 14, 13, "void", "string", "real", "integer", "main", "moreFunctions");
			collision[10].fetch(19, 18, 17, 16,"void", "string", "real", "integer", "returnType");
			collision[11].fetch(20,20,20,20,20, "integer", "string", "real", "^", "array", "paramList");
			collision[12].fetch(21,21,21,21,21, "integer", "string", "real", "^", "array", "body");
			collision[13].fetch(22, 22, 22, 22, 22,22,22, "id(", "write", "read", "while", "if", "id", "statements");
			collision[14].fetch(23, 23, 23, 24, "endif","endwhile","}", ";", "moreStatements");
			collision[15].fetch(31, "id", "assignmentStatement");
			collision[16].fetch(32, "if", "ifStatement");
			collision[17].fetch(34, "while", "whileStatement");
			collision[18].fetch(35, "read", "inputStatement");
			collision[19].fetch(36, "write", "outputStatement");
			collision[20].fetch(37, "id(", "functionCallStatement");
			collision[21].fetch(51, 51,51,52,51, "realLiteral", "stringLiteral", "intLiteral", "(", "id", "expr");
			collision[22].fetch(44, 43, 42, 41, "realLiteral", "stringLiteral", "intLiteral", "id", "arg");
			collision[23].fetch(39, 39, 39, 39, 39, 40, 39, ")", "realLiteral", "stringLiteral", "intLiteral", "(", ",", "id", "moreExpressions");
			collision[24].fetch(38, 38, 38, 38, 38, "realLiteral", "stringLiteral", "intLiteral", "(", "id", "exprList");
			collision[25].fetch(33, 33, 33, 33, "realLiteral", "stringLiteral", "intLiteral", "id", "cond");
			collision[26].fetch(49, 50, 46, 48, 47, 45, "!=", "==", "<", "<=", ">=",">", "relOp");
			collision[27].fetch(53, 55, 54, 56, 57,"+", "-", "*", "/","%", "arithmOp");
			collision[28].fetch(25, 25, 26, 27, 28, 29, 30, ",", "id", "if", "while", "read", "write", "id(", "statement");
		}
	private:
		Collision<std::string> collision[29];
		std::vector<std::string> grammerVector;
		std::stack<std::string>  grammerStack;
		std::string				   grammerString;
		std::string ss;
	};
}
