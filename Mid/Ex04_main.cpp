#include "Ex04_Game.h"
#include "Ex04_GameFuncIntro.h"
#include "Ex04_GameFuncStage.h"
#include "EX04_GameFuncEnding.h"

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

	// 배경 음악
	// Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT, 2, 4096);
	// Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096); 
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		cout << "Mix_OpenAudio" << Mix_GetError() << endl;
		exit(2);
	}

	g_window = SDL_CreateWindow("Plane Game", 100, 100, 800, 600, 0);
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

	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}
