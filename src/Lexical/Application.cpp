#include"amcpch.h"
#include"Application.h"
#include"Syntex/GrammerTable.h"
namespace Amc {
	Application::Application()
	{
		Tooken tooken = Tooken();
		if (valid)
			GrammerTable grammerTable("lex.txt");
		else
			AMC_CORE_ERROR("LEXICAL ERRORS---fix your code---");


	}
	Application::~Application()
	{
	}
}