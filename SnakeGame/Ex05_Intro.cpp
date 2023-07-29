#include "Ex05_GameFunc.h"
#include "Ex05_Intro.h"


// 초기 프로그램 호출될 때 한 번
Intro::Intro() {
	SDL_Surface* intro_surface = IMG_Load("../Resources/intro_bg.png");
	intro_texture = SDL_CreateTextureFromSurface(g_renderer, intro_surface);
	SDL_FreeSurface(intro_surface);

	intro_rect = {0, 0, 960, 720};
	intro_dest_rect = { 0,0, 800, 600 };
}

void Intro::Update() {
	
}

void Intro::Render() {
	
	SDL_RenderClear(g_renderer); 
	SDL_RenderCopy(g_renderer, intro_texture, &intro_rect, &intro_dest_rect);
	SDL_RenderPresent(g_renderer); 
}

void Intro::HandleEvents() {
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
				
				if (mouse_x >= 302 && mouse_x <= 495 && mouse_y >= 450 && mouse_y <= 506)
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
	SDL_DestroyTexture(intro_texture);
}