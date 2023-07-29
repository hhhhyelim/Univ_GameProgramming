#include "Ex01_GameFunc.h"
#include <windows.h>

using namespace std;
// 0:STOP, 1:LEFT, 2:RIGHT, 3:UP, 4:DOWN
int f_state;  	  
int f_x;
int f_y;

// 0: IN FLIGHT 1:FLYING
int m_state;
int m_X;
int m_Y;

bool m[30];
int m_pos[30][2];
int cnt;

/////////////////////////////////////////////////////////////
// InitGame() 
// 프로그램이 시작될 때 최초에 한 번 호출되는 함수.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.

void InitGame() {
	g_flag_running = true;

	f_state = 0;
	m_state = 0;

	f_x = 10;
	f_y = 29;
	cnt = 0;

	
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
		if (f_x > 0) {
			f_x -= 1;
		}
	}
	else if (f_state == 2) { // RIGHT
		if (f_x < 19) {
			f_x += 1;
		}
	}
	else if (f_state == 3) { // UP
		if (f_y > 0) {
			f_y -= 1;
		}
	}
	else if (f_state == 4) { // DOWN
		if (f_y < 29) {
			f_y += 1;
		}
	}
	else {
		f_x = f_x;
		f_y = f_y;
	}
	
}


/////////////////////////////////////////////////////////////
// Render() 
// 그림을 그리는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Render() {
	//// 1. 배경 그리기.
	// 1.1. 커서를 콘솔 화면의 왼쪽 위 모서리 부분으로 옮긴다. 좌표(0, 0)
	// <windows.h>에서 제공하는 함수를 사용한다.
	COORD cur;
	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	//// 1.2. 배경 부분을 '_'으로 채운다.
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 20; j++) {
			cout << "_";
		}
		cout << endl;
	}



	//// 2. 비행기 그리기.
	// 2.1. 커서를 캐릭터가 그려질 위치로 옮긴다. 
	cur.X = f_x;
	cur.Y = f_y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	// 2.2. 비행기 그린다.
	cout << '*';

	// 3. 미사일
	for (int i = 0; i < 30; i++) {
		if (m[i]) {
			COORD pos = { m_pos[i][0], m_pos[i][1]-- };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			if (m_pos[i][1] < 0)
				m[i] = false;
			// 미사일 발사
			cout << "!";
		}
	}
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
				m_pos[cnt][0] = f_x;
				m_pos[cnt][1] = f_y;
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
}