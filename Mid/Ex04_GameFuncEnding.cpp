#include "Ex04_Game.h"
#include "Ex04_GameFuncEnding.h"


// 초기 프로그램 호출될 때 한 번
Ending::Ending() {
	// Ending 이미지
	SDL_Surface* tmp_surface = IMG_Load("../resources/ending.jpg");
	m_ending_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

	SDL_QueryTexture(m_ending_texture, NULL, NULL, &m_ending_rect.w, &m_ending_rect.h);
	m_ending_destination_rect = { m_ending_rect.x = 0, m_ending_rect.y = 0, 800,600 };

	// retry 버튼
	m_retry_btn_rect = {300, 400, 180, 70};

	// retry 글자
	m_font = TTF_OpenFont("../resources/DungGeunMo.ttf", 60);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface* tmp2_surface = TTF_RenderText_Blended(m_font, "RETRY", white);
	m_retry_rect = { 0, 0,tmp2_surface->w, tmp2_surface->h };
	m_retry_texture = SDL_CreateTextureFromSurface(g_renderer, tmp2_surface);
	SDL_FreeSurface(tmp2_surface);


}
// Intro 페이지 끝나서 더 이상 필요 없을 때
Ending::~Ending() {
	SDL_DestroyTexture(m_retry_texture);
	SDL_DestroyTexture(m_retry_texture);
	TTF_CloseFont(m_font);
}

void Ending::Update() {

}

void Ending::Render() {
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color

	// ending 배경
	SDL_RenderCopy(g_renderer, m_ending_texture, &m_ending_rect, &m_ending_destination_rect);
	
	// retry box
	SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 0); 
	SDL_RenderFillRect(g_renderer, &m_retry_btn_rect);

	// retry 글씨
	SDL_Rect tmp2_r;
	tmp2_r = { 315, 405, m_retry_rect.w, m_retry_rect.h };
	SDL_RenderCopy(g_renderer, m_retry_texture, &m_retry_rect, &tmp2_r);


	SDL_RenderPresent(g_renderer); // draw to the screen

}

void Ending::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:

			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;
				if (mouse_x > m_retry_btn_rect.x &&
					mouse_y > m_retry_btn_rect.y &&
					mouse_x < m_retry_btn_rect.x + m_retry_btn_rect.w &&
					mouse_y < m_retry_btn_rect.y + m_retry_btn_rect.h)
					g_current_game_phase = PHASE_INTRO;
			}
			break;

		default:
			break;
		}
	}

}

