#include "Ex05_GameFunc.h"
#include "Ex05_Intro.h"
#include "Ex05_Stage.h"
#include "EX05_Ending.h"

using namespace std;

SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

// Game Phase
int g_current_game_phase;


int main(int argc, char* argv[]) {

	// Initializing SDL library
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	g_window = SDL_CreateWindow("Snake Game", 100, 100, 800, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	InitGame();

	PhaseInterface* game_phases[3];
	game_phases[PHASE_INTRO] = new Intro;
	game_phases[PHASE_STAGE] = new Stage;
	game_phases[PHASE_ENDING] = new Ending;

	g_current_game_phase = PHASE_INTRO;

	g_last_time_ms = SDL_GetTicks();

	while (g_flag_running) {

		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33)
			continue;

		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();

		g_last_time_ms = cur_time_ms;
	}


	// ClearIntro 할 필요 없이 자동으로 clear됨
	ClearGame();

	for (int i = 0; i < 3; i++) {
		delete game_phases[i];
	}

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	TTF_Quit();
	SDL_Quit();

	return 0;
}
