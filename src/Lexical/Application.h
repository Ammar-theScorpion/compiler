#pragma once
#include"amcpch.h"
#include"Core.h"
#include"Lexan/Lexan.h"
#include"Lexan/Reserved.h"
namespace Amc {

	class AMC_API Application
	{
	public:
		Application();
		virtual ~Application();
		 
	private:
	};
	Application* createApplication();


}