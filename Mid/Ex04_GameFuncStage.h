#pragma once

#include <iostream>
#include <string>


class Stage:public PhaseInterface
{
public:
	Stage();
	~Stage();

	virtual void HandleEvents();
	virtual void Update();
	void TimePrint();
	void ScorePrint(int score);
	virtual void Render();
	virtual void Reset();
	//virtual void ClearGame();

private:
	
};
