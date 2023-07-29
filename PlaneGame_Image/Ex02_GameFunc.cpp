#include "Ex02_GameFunc.h"
#include <windows.h>
#include "SDL_image.h"

using namespace std;
int g_elapsed_time_ms; // �귯�� �ð� ���

// Background
SDL_Texture* bg_texture; // ��� ���� ���� ��
SDL_Rect bg_rect; // ��� �߶�� ���� rect
SDL_Rect bg_destination_rect; // ��� �� �� rect

// Plane
SDL_Texture* plane_texture; // ����� ���� ���� ��
SDL_Rect plane_rect; // ����� �߶�� ���� rect
SDL_Rect plane_pos; // ����� �� �� rect

// Missile
SDL_Texture* missile_texture; // �̻��� ���� ���� ��
SDL_Rect missile_rect; // �̻��� �߶�� ���� rect
SDL_Rect missile_pos[30]; // �̻��� �� �� rect


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
// ���α׷��� ���۵� �� ���ʿ� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���ӿ� �ʿ��� �ڿ�(�̹���, ���� ��)�� �ε��ϰ�, ���� �������� �ʱ�ȭ �ؾ��Ѵ�.

void InitGame() {
	g_flag_running = true;
	g_elapsed_time_ms = 0;


	//f_state = 0;
	//m_state = 0;

	//f_x = 10;
	//f_y = 29;
	//cnt = 0;


	// ��� �̹��� �ε��ϱ�
	SDL_Surface* bg_surface = IMG_Load("../resources/background.png");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface); // GPU�� �ű�� 
	SDL_FreeSurface(bg_surface);

	// ����� �̹��� �ε��ϱ�
	SDL_Surface* plane_surface = IMG_Load("../resources/plane.png");
	plane_texture = SDL_CreateTextureFromSurface(g_renderer, plane_surface); // GPU�� �ű�� 
	SDL_FreeSurface(plane_surface);


	// �̻��� �̹��� �ε��ϱ�
	SDL_Surface* missile_surface = IMG_Load("../resources/missile.png");
	missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface); // GPU�� �ű�� 
	SDL_FreeSurface(missile_surface);


	// ��� �߶�� ��
	bg_rect.x = 0; 
	bg_rect.y = 0;
	bg_rect.w = 2500;
	bg_rect.h = 2500;
	// ��� ũ��
	bg_destination_rect.x = 0;
	bg_destination_rect.y = 0;
	bg_destination_rect.w = 800;
	bg_destination_rect.h = 600;


	// ����� �߶�� ��
	plane_rect.x = 0;
	plane_rect.y = 0;
	plane_rect.w = 512;
	plane_rect.h = 512;
	// ����� ó�� ��ġ
	plane_pos.x = 400;
	plane_pos.y = 500;
	plane_pos.w = 50;
	plane_pos.h = 50;

	// �̻��� �߶�� ��
	missile_rect.x = 0;
	missile_rect.y = 0;
	missile_rect.w = 512;
	missile_rect.h = 512;
	

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
// �׸��� �׸��� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void Render() {
	// background - �߶�� ���� �簢��, �ҷ��� ���� �簢��
	SDL_RenderCopy(g_renderer, bg_texture, &bg_rect, &bg_destination_rect);

	// plane
	SDL_RenderCopy(g_renderer, plane_texture, &plane_rect, &plane_pos);

	// missile
	for (int i = 0; i < 30; i++) {
		if (m[i]) {
			if (missile_pos[i].y < 0) m[i] = false;
			// �̻��� �߻�
			missile_pos[i].y -= 10;
			SDL_RenderCopy(g_renderer, missile_texture, &missile_rect, &missile_pos[i]); // �߶�� ���� �簢��, ���� ���� �簢��
		}
	}


	// double buffering - back buffer�� �ִ� front buffer�� �ٲ���
	// �������� �� �� ���ֱ�
	SDL_RenderPresent(g_renderer);

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
// ���α׷��� ���� �� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���� �ڿ�(�̹���, ���� ��)�� �޸� ���� �����ؾ��Ѵ�.
void ClearGame()
{
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(plane_texture);
	SDL_DestroyTexture(missile_texture);

}