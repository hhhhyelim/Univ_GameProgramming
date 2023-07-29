#include "Ex04_Game.h"
#include "Ex04_GameFuncStage.h"
#include <windows.h>
#include <atlstr.h>
#include <string.h>
#include <iostream>

using namespace std;

int g_elapsed_time_ms; // 흘러간 시간 기록


// 시간
TTF_Font* font2;
SDL_Texture* time_texture;
SDL_Rect time_rect;
SDL_Surface* time_surface;
SDL_Rect time_title_rect;
bool gameover;

// 점수: 글자
TTF_Font* font;
SDL_Surface* title_surface;
SDL_Texture* title_texture;
SDL_Rect title_rect;

// 실제 점수
SDL_Surface* score_surface;
SDL_Texture* score_texture;
SDL_Rect score_rect;
int score = 0;

// 배경 음악
Mix_Music* bg_mus;
// 효과음
Mix_Chunk* missile_sound;

// Background
SDL_Surface* bg_surface;
SDL_Texture* bg_texture; // 배경 복사 받을 곳
SDL_Rect bg_rect; // 배경 잘라올 곳의 rect
SDL_Rect bg_destination_rect; // 배경 둘 곳 rect

// Plane
SDL_Surface* plane_surface;
SDL_Texture* plane_texture; // 비행기 복사 받을 곳
SDL_Rect plane_rect; // 비행기 잘라올 곳의 rect
SDL_Rect plane_pos; // 비행기 둘 곳 rect

// Missile
SDL_Surface* missile_surface;
SDL_Texture* missile_texture; // 미사일 복사 받을 곳
SDL_Rect missile_rect; // 미사일 잘라올 곳의 rect
SDL_Rect missile_pos[30]; // 미사일 둘 곳 rect


// 0:STOP, 1:LEFT, 2:RIGHT, 3:UP, 4:DOWN
int f_state;

// 0: IN FLIGHT 1:FLYING
// int m_state;
bool m[30];
int cnt;

/////////////////////////////////////////////////////////////
// InitGame() 
// 프로그램이 시작될 때 최초에 한 번 호출되는 함수.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.

Stage:: Stage() {
	// 시간
	g_flag_running = true;
	g_elapsed_time_ms = 0;

	// 텍스트 불러오기
	font = TTF_OpenFont("../resources/R.ttf", 17); // 사이즈
	font2 = TTF_OpenFont("../resources/R.ttf", 90); // 카운트 다운 사이즈

	// "점수: " 글자 출력
	SDL_Color black = { 0, 0, 0, 0 }; // 마지막은 투명도
	title_surface = TTF_RenderUTF8_Blended(font, CW2A(L"점수: ", CP_UTF8), black);
	title_rect = { 0, 0, title_surface->w, title_surface->h };
	title_texture = SDL_CreateTextureFromSurface(g_renderer, title_surface); // GPU로 옮기기
	SDL_FreeSurface(title_surface);

	
	// 배경 음악 로드하기
	bg_mus = Mix_LoadMUS("../resources/backgroundMusic.mp3");
	if (bg_mus == 0) {
		cout << "Mix_LoadMus(\"music.mp3\"): " << Mix_GetError() << endl;
	}
	
	Mix_VolumeMusic(100); // 배경 음악 소리 볼륨

	// Mix_PlayMusic(bg_mus, -1); // -1 : 무한 반복      
	 Mix_FadeInMusic(bg_mus, -1, 2); // 소리 서서히 커지게


	// 미사일 효과음 로드하기
	missile_sound = Mix_LoadWAV("../resources/effectMusic.wav");
	if (missile_sound == 0) {
		cout << "Mix_LoadWAV(\"effectMusic.wav\"): " << Mix_GetError() << endl;
	}

	// 배경 이미지 로드하기
	bg_surface = IMG_Load("../resources/background.png");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface); // GPU로 옮기기 
	SDL_FreeSurface(bg_surface);

	// 비행기 이미지 로드하기
	plane_surface = IMG_Load("../resources/plane.png");
	plane_texture = SDL_CreateTextureFromSurface(g_renderer, plane_surface); // GPU로 옮기기 
	SDL_FreeSurface(plane_surface);


	// 미사일 이미지 로드하기
	missile_surface = IMG_Load("../resources/missile.png");
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface); // GPU로 옮기기 
	SDL_FreeSurface(missile_surface);

	
	// 배경 잘라올 곳
	bg_rect = { 0, 0, 2500, 2500 };
	// 배경 크기
	bg_destination_rect = { 0, 0, 800, 600 };


	// 비행기 잘라올 곳
	plane_rect = { 0, 0, 512, 512 };
	// 비행기 처음 위치
	plane_pos = { 400, 500, 50, 50 };


	// 미사일 잘라올 곳
	missile_rect = { 0, 0, 512, 512 };


	// Clear the console screen.
	// 표준출력 화면을 깨끗히 지운다.
	//system("cls");

}

Stage::~Stage() {
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(plane_texture);
	SDL_DestroyTexture(missile_texture);
	SDL_DestroyTexture(score_texture);
	SDL_DestroyTexture(time_texture);

	Mix_FreeMusic(bg_mus);
	Mix_FreeChunk(missile_sound);

	TTF_CloseFont(font);
	TTF_CloseFont(font2);
}

void Stage:: TimePrint() {
	
	SDL_Color red = { 255, 0, 0, 0 };
	int startTime = SDL_GetTicks();
	g_elapsed_time_ms = 0;

	while (g_elapsed_time_ms < 3000) {
		if (time_texture != 0) {

			SDL_DestroyTexture(time_texture); // !!!중요!!! 이미 생성되어있는 score_texture가 있으면 반드시 메모리에서 지워야한다. !!
			time_texture = 0;
		}

		g_elapsed_time_ms = SDL_GetTicks()-startTime; // 경과 시간 기록
		int remainSec = 3000 - g_elapsed_time_ms;
		remainSec = remainSec / 1000 + 1;
		string s = to_string(remainSec);

		time_surface = TTF_RenderUTF8_Blended(font2, s.c_str(), red);
		time_texture = SDL_CreateTextureFromSurface(g_renderer, time_surface);
		time_rect = {380, 250, time_surface->w, time_surface->h };

		time_title_rect = { 345, 235, 120, 120 };
		SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);
		SDL_RenderFillRect(g_renderer, &time_title_rect);

		SDL_RenderCopy(g_renderer, time_texture, NULL, &time_rect);
	

		cout << s << endl;
		SDL_RenderPresent(g_renderer);

	

		SDL_FreeSurface(time_surface);
	}
}

void Stage:: ScorePrint(int score) {
	if (score_texture != 0) {

		SDL_DestroyTexture(score_texture); // !!!중요!!! 이미 생성되어있는 score_texture가 있으면 반드시 메모리에서 지워야한다. !!
		score_texture = 0;

	}
	
	string scorePrint = "00000";
	string curScore = to_string((long long)score);

	if (curScore.length() <= 5) {
		scorePrint.replace(5 - curScore.length(), curScore.length(), curScore);
	}

	SDL_Color black = { 0, 0, 0, 0 };
	score_surface = TTF_RenderUTF8_Blended(font, scorePrint.c_str(), black); // 글씨 깔끔
	score_texture = SDL_CreateTextureFromSurface(g_renderer, score_surface);

	score_rect = { 0, 0, score_surface->w, score_surface->h };
	
	SDL_RenderCopy(g_renderer, score_texture, NULL, &score_rect);
	
	SDL_FreeSurface(score_surface);
}

/////////////////////////////////////////////////////////////
// Update() 
// 게임의 내용을 업데이트하는 함수.
// 실제 게임의 룰을 구현해야하는 곳.
// 게임에서 일어나는 변화는 모두 이 곳에서 구현한다.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Stage::Update() {
	ScorePrint(score);

	if (f_state == 1) { // LEFT
		plane_pos.x -= 10;

	}
	else if (f_state == 2) { // RIGHT
		plane_pos.x += 10;

	}
	else if (f_state == 3) { // UP
		plane_pos.y -= 10;

	}
	else if (f_state == 4) { // DOWN
		plane_pos.y += 10;
	}
	else {
		plane_pos.x = plane_pos.x;
		plane_pos.y = plane_pos.y;
	}

	if (plane_pos.x > 750)
		plane_pos.x = 750;
	else if (plane_pos.x < 0)
		plane_pos.x = 0;

	if (plane_pos.y > 550)
		plane_pos.y = 550;
	else if (plane_pos.y < 0)
		plane_pos.y = 0;

	g_elapsed_time_ms += 33;
}


/////////////////////////////////////////////////////////////
// Render() 
// 그림을 그리는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Stage::Render() {
	
	SDL_RenderClear(g_renderer);
	
	// background - 잘라올 곳의 사각형, 불러올 곳의 사각형
	SDL_RenderCopy(g_renderer, bg_texture, &bg_rect, &bg_destination_rect);

	// plane
	SDL_RenderCopy(g_renderer, plane_texture, &plane_rect, &plane_pos);

	// missile
	for (int i = 0; i < 30; i++) {
		if (m[i]) {
			if (missile_pos[i].y < 0) m[i] = false;
			// 미사일 발사
			missile_pos[i].y -= 10;
			SDL_RenderCopy(g_renderer, missile_texture, &missile_rect, &missile_pos[i]); // 잘라올 곳의 사각형, 붙일 곳의 사각형
		}
	}

	// 점수:  출력
	SDL_Rect tmp_tRect;
	tmp_tRect = { 30, 50, title_rect.w, title_rect.h };
	SDL_RenderCopy(g_renderer, title_texture, &title_rect, &tmp_tRect);

	// 실제 점수 출력
	SDL_Rect tmp_sRect;
	tmp_sRect = { 70, 50, score_rect.w, score_rect.h };
	SDL_RenderCopy(g_renderer, score_texture, &score_rect, &tmp_sRect);

	

	// double buffering - back buffer에 있는 front buffer로 바꿔줌
	// 마지막에 한 번 해주기
	SDL_RenderPresent(g_renderer);

}

void Stage::Reset()
{
	plane_pos = { 400, 500, 50, 50 };
	score = 0;
	for (int i = 0; i < 30; i++) {
		missile_pos[i].y = -999;
	}
}


/////////////////////////////////////////////////////////////
// HandleEvents() 
// 이벤트를 처리하는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Stage:: HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			Mix_FadeOutMusic(2000);
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				f_state = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				f_state = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				f_state = 3;                                                                                                                                                                                                                                                                                                        
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				f_state = 4;
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				
				score += 10;
				
				Mix_PlayChannel(-1, missile_sound, 0); // (-1: 반복해서 실행할 때 동시에 실행하려고, ,0이라고 작성해야 한 번 나옴)

				m[cnt] = true;
				missile_pos[cnt] = { plane_pos.x, plane_pos.y - 50, 50, 50 };
				cnt++;
				if (cnt > 29)
					cnt = 0;
			}
			break;


		case SDL_KEYUP:
			if(event.key.keysym.sym != SDLK_SPACE)
				f_state = 0;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				TimePrint();
				g_current_game_phase = PHASE_ENDING;
				Reset();
			}
			break;

		default:
			break;
		}
	}
}