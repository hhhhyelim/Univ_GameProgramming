#include "Ex05_GameFunc.h"
#include "Ex05_Ending.h"


// 초기 프로그램 호출될 때 한 번
Ending::Ending() {
	SDL_Surface* ending_surface = IMG_Load("../Resources/game_over_bg.png");
	ending_texture = SDL_CreateTextureFromSurface(g_renderer, ending_surface);
	SDL_FreeSurface(ending_surface);

	ending_rect = { 0, 0, 960, 720 };
	ending_dest_rect = { 0,0, 800, 600 };


}
//  페이지 끝나서 더 이상 필요 없을 때
Ending::~Ending() {
	SDL_DestroyTexture(ending_texture);
}

void Ending::Update() {

}

void Ending::Render() {

	SDL_RenderClear(g_renderer);
	SDL_RenderCopy(g_renderer, ending_texture, &ending_rect, &ending_dest_rect);
	SDL_RenderPresent(g_renderer);
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

				if (mouse_x >= 302 && mouse_x <= 495 && mouse_y >= 450 && mouse_y <= 506)
					g_current_game_phase = PHASE_INTRO;
			}
			break;

		default:
			break;
		}
	}

}

