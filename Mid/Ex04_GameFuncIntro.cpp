#include "Ex04_Game.h"
#include "Ex04_GameFuncIntro.h"


// 초기 프로그램 호출될 때 한 번
Intro::Intro() {

	// intro 이미지
	SDL_Surface* tmp_surface = IMG_Load("../resources/intro.jpg");
	m_intro_texture = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
	SDL_FreeSurface(tmp_surface);

	SDL_QueryTexture(m_intro_texture, NULL, NULL, &m_intro_rect.w, &m_intro_rect.h);
	m_intro_destination_rect = { m_intro_rect.x=0, m_intro_rect.y=0, 800, 600 };

	// 시작 버튼
	m_start_btn_rect = {300, 400, 200, 80};

	// start 글자
	m_font = TTF_OpenFont("../resources/DungGeunMo.ttf", 60);
	SDL_Color black = { 0, 0, 0, 0 }; //black
	SDL_Surface* tmp2_surface = TTF_RenderText_Blended(m_font, "START", black);
	m_start_rect = { 0, 0,tmp2_surface->w, tmp2_surface->h };
	m_start_texture = SDL_CreateTextureFromSurface(g_renderer, tmp2_surface);
	SDL_FreeSurface(tmp2_surface);

	// title box
	// m_title_btn_rect = { 150, 150, 500, 80 };

	// Airplane game 글자
	m_font2 = TTF_OpenFont("../resources/DungGeunMo.ttf", 80);
	SDL_Surface* tmp3_surface = TTF_RenderText_Blended(m_font2, "AIRPLANE GAME..", black);
	m_title_rect = { 0, 0,tmp3_surface->w, tmp3_surface->h };
	m_title_texture = SDL_CreateTextureFromSurface(g_renderer, tmp3_surface);
	SDL_FreeSurface(tmp3_surface);

}

void Intro::Update() {
	
}

void Intro::Render() {
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	
	// intro 배경
	SDL_RenderCopy(g_renderer, m_intro_texture, &m_intro_rect, &m_intro_destination_rect);
	
	// 시작버튼
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 0); // white
	SDL_RenderFillRect(g_renderer, &m_start_btn_rect);

	// start 글씨
	SDL_Rect tmp2_r;
	tmp2_r = { 325, 410, m_start_rect.w, m_start_rect.h };
	SDL_RenderCopy(g_renderer, m_start_texture, &m_start_rect, &tmp2_r);

	// title 
	//SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 0); // "#FFCC00"
	//SDL_RenderFillRect(g_renderer, &m_title_btn_rect);

	// Airplane game 글씨
	SDL_Rect tmp3_r;
	tmp3_r = { 125, 155, m_title_rect.w, m_title_rect.h };
	SDL_RenderCopy(g_renderer, m_title_texture, &m_title_rect, &tmp3_r);

	SDL_RenderPresent(g_renderer); // draw to the screen
}

void Intro::HandleEvents() {
	SDL_Event event;

	if(SDL_PollEvent(&event))
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
				if(mouse_x > m_start_btn_rect.x &&
					mouse_y > m_start_btn_rect.y &&
					mouse_x < m_start_btn_rect.x+m_start_btn_rect.w &&
					mouse_y < m_start_btn_rect.y+m_start_btn_rect.h)
					g_current_game_phase = PHASE_STAGE;
				
			}
			break;

		default:
			break;
		}
	}

}

// Intro 페이지 끝나서 더 이상 필요 없을 때
Intro::~Intro() {
	SDL_DestroyTexture(m_intro_texture);
	SDL_DestroyTexture(m_start_texture);
	SDL_DestroyTexture(m_title_texture);
	TTF_CloseFont(m_font);
}