#pragma once

#include "Ex05_GameFunc.h"

class Intro : public PhaseInterface
{
public:
	// 생성자 함수
	Intro();
	// 파괴자 함수
	~Intro();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;


private:
	SDL_Texture* intro_texture; 
	SDL_Rect intro_rect; 
	SDL_Rect intro_dest_rect; 
	
};