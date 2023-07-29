#pragma once

#include "Ex04_Game.h"

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
	// 멤버 변수라고 말하기 위해 m_
	SDL_Texture* m_intro_texture; // the SDL_Texture
	SDL_Rect m_intro_rect;
	SDL_Rect m_intro_destination_rect;

	// 시작 버튼 box
	SDL_Rect m_start_btn_rect;
	
	// start 글자
	TTF_Font* m_font;
	SDL_Texture* m_start_texture;
	SDL_Rect m_start_rect;

	// title box
	// SDL_Rect m_title_btn_rect;
	// airplane game 글자
	TTF_Font* m_font2;
	SDL_Texture* m_title_texture;
	SDL_Rect m_title_rect;
};