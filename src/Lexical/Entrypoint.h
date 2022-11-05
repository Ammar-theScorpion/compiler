#pragma once
#include"Application.h"
extern Amc::Application* Amc::createApplication();

int main()
{
	Amc::Log::init();
	AMC_CORE_INFO("Intialized The System");
	auto a = Amc::createApplication();
	delete a;
}