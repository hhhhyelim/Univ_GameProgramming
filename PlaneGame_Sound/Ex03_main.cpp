#include "Ex03_GameFunc.h"

using namespace std;

SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;


int main(int argc, char* argv[]) {

	// Initializing SDL library
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	// ¹è°æ À½¾Ç
	// Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT, 2, 4096);
	// Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096); 
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		cout << "Mix_OpenAudio" << Mix_GetError() << endl;
		exit(2);
	}


	g_window = SDL_CreateWindow("Game with Sound and Text", 100, 100, 800, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);
	InitGame();

	g_last_time_ms = SDL_GetTicks();

	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33)  
			continue;

		HandleEvents();
		Update();
		Render();

		g_last_time_ms = cur_time_ms;
	}

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	ClearGame();
	Mix_CloseAudio();

	TTF_Quit();
	SDL_Quit();

	return 0;
}
