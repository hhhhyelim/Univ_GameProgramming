#pragma once

#include "Ex05_GameFunc.h"

class Intro : public PhaseInterface
{
public:
	// ������ �Լ�
	Intro();
	// �ı��� �Լ�
	~Intro();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;


private:
	SDL_Texture* intro_texture; 
	SDL_Rect intro_rect; 
	SDL_Rect intro_dest_rect; 
	
};