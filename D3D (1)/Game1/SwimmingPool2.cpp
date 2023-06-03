#include "stdafx.h"

SwimmingPool2* SwimmingPool2::Create(string name)
{
	SwimmingPool2* temp = new SwimmingPool2();
	temp->LoadFile("swimmingPool4.xml");

	return temp;
}

void SwimmingPool2::Release()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}

SwimmingPool2::SwimmingPool2()
{
}

SwimmingPool2::~SwimmingPool2()
{
}




