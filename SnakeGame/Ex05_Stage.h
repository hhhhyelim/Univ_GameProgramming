#pragma once

#include <iostream>
#include <string>


class Stage :public PhaseInterface
{
public:
	Stage();
	~Stage();

	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	void Reset();

private:

};
