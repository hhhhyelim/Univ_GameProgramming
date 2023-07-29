#pragma once

class Ending: public PhaseInterface
{
public:

	// 생성자 함수
	Ending();
	// 파괴자 함수
	~Ending();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	SDL_Texture* m_ending_texture; // the SDL_Texture 
	SDL_Rect m_ending_rect; // the rectangle for source image
	SDL_Rect m_ending_destination_rect; // for destination

	// retry 버튼 box
	SDL_Rect m_retry_btn_rect;

	// retry 글자
	TTF_Font* m_font;
	SDL_Texture* m_retry_texture;
	SDL_Rect m_retry_rect;

	
};
