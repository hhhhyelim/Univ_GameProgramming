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
// ���α׷��� ���۵� �� ���ʿ� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���ӿ� �ʿ��� �ڿ�(�̹���, ���� ��)�� �ε��ϰ�, ���� �������� �ʱ�ȭ �ؾ��Ѵ�.

void InitGame() {
	g_flag_running = true;

	f_state = 0;
	m_state = 0;

	f_x = 10;
	f_y = 29;
	cnt = 0;

	
	// Clear the console screen.
	// ǥ����� ȭ���� ������ �����.
	system("cls");
}



/////////////////////////////////////////////////////////////
// Update() 
// ������ ������ ������Ʈ�ϴ� �Լ�.
// ���� ������ ���� �����ؾ��ϴ� ��.
// ���ӿ��� �Ͼ�� ��ȭ�� ��� �� ������ �����Ѵ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
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
// �׸��� �׸��� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void Render() {
	//// 1. ��� �׸���.
	// 1.1. Ŀ���� �ܼ� ȭ���� ���� �� �𼭸� �κ����� �ű��. ��ǥ(0, 0)
	// <windows.h>���� �����ϴ� �Լ��� ����Ѵ�.
	COORD cur;
	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	//// 1.2. ��� �κ��� '_'���� ä���.
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 20; j++) {
			cout << "_";
		}
		cout << endl;
	}



	//// 2. ����� �׸���.
	// 2.1. Ŀ���� ĳ���Ͱ� �׷��� ��ġ�� �ű��. 
	cur.X = f_x;
	cur.Y = f_y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	// 2.2. ����� �׸���.
	cout << '*';

	// 3. �̻���
	for (int i = 0; i < 30; i++) {
		if (m[i]) {
			COORD pos = { m_pos[i][0], m_pos[i][1]-- };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			if (m_pos[i][1] < 0)
				m[i] = false;
			// �̻��� �߻�
			cout << "!";
		}
	}
}



/////////////////////////////////////////////////////////////
// HandleEvents() 
// �̺�Ʈ�� ó���ϴ� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
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
// ���α׷��� ���� �� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���� �ڿ�(�̹���, ���� ��)�� �޸� ���� �����ؾ��Ѵ�.
void ClearGame()
{
}