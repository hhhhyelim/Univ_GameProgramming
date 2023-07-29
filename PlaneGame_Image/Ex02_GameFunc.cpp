#include "Ex02_GameFunc.h"
#include <windows.h>
#include "SDL_image.h"

using namespace std;
int g_elapsed_time_ms; // 흘러간 시간 기록

// Background
SDL_Texture* bg_texture; // 배경 복사 받을 곳
SDL_Rect bg_rect; // 배경 잘라올 곳의 rect
SDL_Rect bg_destination_rect; // 배경 둘 곳 rect

// Plane
SDL_Texture* plane_texture; // 비행기 복사 받을 곳
SDL_Rect plane_rect; // 비행기 잘라올 곳의 rect
SDL_Rect plane_pos; // 비행기 둘 곳 rect

// Missile
SDL_Texture* missile_texture; // 미사일 복사 받을 곳
SDL_Rect missile_rect; // 미사일 잘라올 곳의 rect
SDL_Rect missile_pos[30]; // 미사일 둘 곳 rect


// 0:STOP, 1:LEFT, 2:RIGHT, 3:UP, 4:DOWN
int f_state;
// int f_x;
// int f_y;

// 0: IN FLIGHT 1:FLYING
int m_state;
// int m_X;
// int m_Y;

bool m[30];
int m_pos[30][2];
int cnt;

/////////////////////////////////////////////////////////////
// InitGame() 
// 프로그램이 시작될 때 최초에 한 번 호출되는 함수.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.

void InitGame() {
	g_flag_running = true;
	g_elapsed_time_ms = 0;


	//f_state = 0;
	//m_state = 0;

	//f_x = 10;
	//f_y = 29;
	//cnt = 0;


	// 배경 이미지 로드하기
	SDL_Surface* bg_surface = IMG_Load("../resources/background.png");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface); // GPU로 옮기기 
	SDL_FreeSurface(bg_surface);

	// 비행기 이미지 로드하기
	SDL_Surface* plane_surface = IMG_Load("../resources/plane.png");
	plane_texture = SDL_CreateTextureFromSurface(g_renderer, plane_surface); // GPU로 옮기기 
	SDL_FreeSurface(plane_surface);


	// 미사일 이미지 로드하기
	SDL_Surface* missile_surface = IMG_Load("../resources/missile.png");
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface); // GPU로 옮기기 
	SDL_FreeSurface(missile_surface);


	// 배경 잘라올 곳
	bg_rect.x = 0; 
	bg_rect.y = 0;
	bg_rect.w = 2500;
	bg_rect.h = 2500;
	// 배경 크기
	bg_destination_rect.x = 0;
	bg_destination_rect.y = 0;
	bg_destination_rect.w = 800;
	bg_destination_rect.h = 600;


	// 비행기 잘라올 곳
	plane_rect.x = 0;
	plane_rect.y = 0;
	plane_rect.w = 512;
	plane_rect.h = 512;
	// 비행기 처음 위치
	plane_pos.x = 400;
	plane_pos.y = 500;
	plane_pos.w = 50;
	plane_pos.h = 50;

	// 미사일 잘라올 곳
	missile_rect.x = 0;
	missile_rect.y = 0;
	missile_rect.w = 512;
	missile_rect.h = 512;
	

	// Clear the console screen.
	// 표준출력 화면을 깨끗히 지운다.
	system("cls");

}



/////////////////////////////////////////////////////////////
// Update() 
// 게임의 내용을 업데이트하는 함수.
// 실제 게임의 룰을 구현해야하는 곳.
// 게임에서 일어나는 변화는 모두 이 곳에서 구현한다.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Update() {
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
void Render() {
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


	// double buffering - back buffer에 있는 front buffer로 바꿔줌
	// 마지막에 한 번 해주기
	SDL_RenderPresent(g_renderer);

}



/////////////////////////////////////////////////////////////
// HandleEvents() 
// 이벤트를 처리하는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
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
				m[cnt] = true;
				missile_pos[cnt].x = plane_pos.x;
				missile_pos[cnt].y = plane_pos.y-50;
				missile_pos[cnt].w = 50;
				missile_pos[cnt].h = 50;
				cnt++;
				if (cnt > 29)
					cnt = 0;
			}
			break;

		case SDL_KEYUP:
			f_state = 0;
			break;

		default:
			break;
		}
	}
}




/////////////////////////////////////////////////////////////
// ClearGame() 
// 프로그램이 끝날 때 한 번 호출되는 함수.
// 이 함수에서 사용된 자원(이미지, 사운드 등)과 메모리 등을 해제해야한다.
void ClearGame()
{
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(plane_texture);
	SDL_DestroyTexture(missile_texture);

}