#pragma once

#include "Ex04_Game.h"

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
	// ��� ������� ���ϱ� ���� m_
	SDL_Texture* m_intro_texture; // the SDL_Texture
	SDL_Rect m_intro_rect;
	SDL_Rect m_intro_destination_rect;

	// ���� ��ư box
	SDL_Rect m_start_btn_rect;
	
	// start ����
	TTF_Font* m_font;
	SDL_Texture* m_start_texture;
	SDL_Rect m_start_rect;

	// title box
	// SDL_Rect m_title_btn_rect;
	// airplane game ����
	TTF_Font* m_font2;
	SDL_Texture* m_title_texture;
	SDL_Rect m_title_rect;
};