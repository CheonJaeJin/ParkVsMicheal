#pragma once
class SwimmingPool2 : public Actor
{
public:
	static SwimmingPool2* Create(string name = "SwimmingPool2");


private:
	SwimmingPool2();
	~SwimmingPool2();
public:
	void	Release() override;
};

