#include "Ex05_GameFunc.h"
#include "Ex05_Stage.h"
#include <windows.h>
#include <atlstr.h>
#include <string.h>
#include <iostream>

using namespace std;

// snake 
list <SDL_Rect> snake;
SDL_Texture* snake_texture;
SDL_Rect snake_rect; 
SDL_Rect snake_dest_rect; // 화면에서의 위치

// item
SDL_Texture* item_texture;
SDL_Rect item_rect;
SDL_Rect item_dest_rect;

// potato
SDL_Texture* potato_texture;
SDL_Rect potato_rect;
SDL_Rect potato_dest_rect;

// font
TTF_Font* font2;
SDL_Color white;

// game_over
SDL_Texture* game_over_texture;
SDL_Rect game_over_rect;
SDL_Rect game_over_dest_rect;

// game_ready
SDL_Texture* game_ready_texture;
SDL_Rect game_ready_rect;
SDL_Rect game_ready_dest_rect;

// score
SDL_Texture* score_texture;
SDL_Rect score_rect;
SDL_Rect score_dest_rect;

const int WIDTH = 20;
const int HEIGHT = 20;

int snakes_x;
int snakes_y;

int snake_x;
int snake_y;
int item_x;
int item_y;
int potato_x;
int potato_y;

int state; // left:0 right:1 up:2 down:3 stop: 4
int snakeLeft = 0;
int snakeRight = 1;
int snakeUp = 2;
int snakeDown = 3;
int snakeStop = 4;

bool game_ready = true;
bool game_over = false;
bool item_appear = false;
int score;
int final_score;

int g_elapsed_time_ms; // 흘러간 시간 기록


Stage::Stage() {

	srand(time(NULL));

	snakes_x = 400;
	snakes_y = 300;

	// snake rect 받아오기
	SDL_Surface* snake_surface = IMG_Load("../Resources/snake_rect.png");
	snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_surface);
	SDL_FreeSurface(snake_surface);
	snake_rect = { 0, 0, 592, 592 };
	snake.push_front({ snakes_x, snakes_y, WIDTH,HEIGHT });
	
	// item 받아오기
	SDL_Surface* item_surface = IMG_Load("../Resources/item.png");
	item_texture = SDL_CreateTextureFromSurface(g_renderer, item_surface);
	SDL_FreeSurface(item_surface);
	item_rect = { 0, 0, 179, 161 };
	item_appear = false;

	// 고구마 이미지 로드
	SDL_Surface* potato_surface = IMG_Load("../Resources/sweetpotato.png");
	potato_texture = SDL_CreateTextureFromSurface(g_renderer, potato_surface);
	SDL_FreeSurface(potato_surface);
	potato_rect = { 0, 0, 2000, 2000 };


	// game ready
	SDL_Surface* game_ready_surface = IMG_Load("../Resources/ready.png");
	game_ready_texture = SDL_CreateTextureFromSurface(g_renderer, game_ready_surface);
	SDL_FreeSurface(game_ready_surface);
	game_ready_rect = { 0, 0, game_ready_surface->w, game_ready_surface->h };
	game_ready_dest_rect = { 100, 165, game_ready_rect.w, game_ready_rect.h };

	// 최종 score 
	font2 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 50);
	white = { 255, 255, 255, 0 };

	//game_over
	SDL_Surface* game_over_surface = IMG_Load("../Resources/game_over.png");
	game_over_texture = SDL_CreateTextureFromSurface(g_renderer, game_over_surface);
	SDL_FreeSurface(game_over_surface);
	game_over_rect = { 0, 0, game_over_surface->w, game_over_surface->h };
	game_over_dest_rect = { 17, 230, game_over_rect.w, game_over_rect.h };


	// 초기화
	score = 0;
	game_over = false;
	game_ready = true;
	state = 4;
}

Stage::~Stage() {
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(snake_texture);
	SDL_DestroyTexture(item_texture);
	SDL_DestroyTexture(potato_texture);
	SDL_DestroyTexture(game_ready_texture);
	SDL_DestroyTexture(game_over_texture);
	SDL_DestroyTexture(score_texture);
}



void Stage::Update() {
	if (game_over)
		return;

	// item random으로 나오게 하기
	item_x = rand() % 750 + 5;
	item_y = rand() % 550 + 5;

	potato_x = rand() % 750 + 5;
	potato_y = rand() % 550 + 5;

	if (item_appear == false) {
		for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
			if ((*iter).x == item_x && (*iter).y == item_y) {
				item_x = rand() % 750 + 5;
				item_y = rand() % 550 + 5;

				potato_x = rand() % 750 + 5;
				potato_y = rand() % 550 + 5;

			}
			else continue;
		}
		item_dest_rect = { item_x, item_y, WIDTH + 10, HEIGHT + 10 };
		potato_dest_rect = { potato_x, potato_y, WIDTH + 20, HEIGHT + 20 };
		item_appear = true;
	}


	// snake 움직이기
	snake_x = snake_y = 0;
	if (state == snakeLeft) { // snakeLeft = 0
		snake_x = -10;
		snake_y = 0;
	}
	else if (state == snakeRight) { // snakeRight = 1
		snake_x = 10;
		snake_y = 0;
	}
	else if (state == snakeUp) { // snakeUp = 2
		snake_x = 0;
		snake_y = -10;
	}
	else if (state == snakeDown) { // snakeDown = 3
		snake_x = 0;
		snake_y = 10;
	}

	if (score > 20) {
		snake_x *= 2;
		snake_y *= 2;
	}


	snake.push_front({ snake.front().x + snake_x , snake.front().y + snake_y, WIDTH, HEIGHT });
	snake.pop_back();

	// snake가 item 먹으면 snake 길이 증가, 점수 1 증가
	if ((snake.front().x >= item_dest_rect.x - 20) && (snake.front().x <= item_dest_rect.x + 20)
		&& (snake.front().y >= item_dest_rect.y - 20) && (snake.front().y <= item_dest_rect.y + 20)) {
		
		snake.push_front({ snake.front().x + snake_x, snake.front().y + snake_y, WIDTH, HEIGHT });
		score += 1;
		item_appear = false;
	
	}
	// snake가 potato 먹으면 snake 길이 감소, 점수 1 감소
	if ((snake.front().x >= potato_dest_rect.x - 20) && (snake.front().x <= potato_dest_rect.x + 20)
		&& (snake.front().y >= potato_dest_rect.y - 20) && (snake.front().y <= potato_dest_rect.y + 20)) {
			snake.pop_back();
			score -= 1;
			item_appear = false;
	}

	// snake 800*600 넘어가면 game over
	if ((snake.front().x < 0) || (snake.front().x > 780) || (snake.front().y < 0) || (snake.front().y > 580)) {
		game_over = true;
	}

	// snake head가 몸통이랑 충돌하면 game over
	int head_x = snake.front().x;
	int head_y = snake.front().y;
	for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
		if ((*iter).x == head_x && (*iter).y == head_y) {
			game_over = true;
		}
	}
}


void Stage::Render() {

	SDL_RenderClear(g_renderer);
	
	// 검정 배경 화면
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);

	// item
	SDL_RenderCopy(g_renderer, item_texture, &item_rect, &item_dest_rect);
	SDL_RenderCopy(g_renderer, potato_texture, &potato_rect, &potato_dest_rect);

	// snake
	for (auto iter = snake.begin(); iter != snake.end(); iter++) {
		SDL_RenderCopy(g_renderer, snake_texture, &snake_rect, &(*iter));
	}
	// score
	SDL_Surface* score_surface = TTF_RenderText_Blended(font2, to_string(score).c_str(), white);
	score_texture = SDL_CreateTextureFromSurface(g_renderer, score_surface);
	SDL_FreeSurface(score_surface);
	score_rect = { 0, 0, score_surface->w, score_surface->h };
	score_dest_rect = { 740, 20, score_rect.w, score_rect.h };
	SDL_RenderCopy(g_renderer, score_texture, &score_rect, &score_dest_rect);

	
	if (game_ready) { // game_ready
		SDL_RenderCopy(g_renderer, game_ready_texture, &game_ready_rect, &game_ready_dest_rect);
	}
	else if (game_over) { // game_over
		
		SDL_RenderCopy(g_renderer, game_over_texture, &game_over_rect, &game_over_dest_rect);
	}
	
	SDL_RenderPresent(g_renderer);
}


void Stage::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			
			break;

		case SDL_KEYDOWN:
			if (game_ready) {
				if (event.key.keysym.sym == SDLK_LEFT ||
					event.key.keysym.sym == SDLK_RIGHT ||
					event.key.keysym.sym == SDLK_UP ||
					event.key.keysym.sym == SDLK_DOWN) {
					game_ready = false;
					if (event.key.keysym.sym == SDLK_LEFT) {
						state = snakeLeft;
					}
					else if (event.key.keysym.sym == SDLK_RIGHT) {
						state = snakeRight;
					}
					else if (event.key.keysym.sym == SDLK_UP) {
						state = snakeUp;
					}
					else if (event.key.keysym.sym == SDLK_DOWN) {
						state = snakeDown;
					}
				}
				
			}
			else {
				if (event.key.keysym.sym == SDLK_LEFT) {
					if (state != snakeRight && state != snakeLeft) {
						state = snakeLeft;
					}
				}
				else if (event.key.keysym.sym == SDLK_RIGHT) {
					if (state != snakeRight && state != snakeLeft) {
						state = snakeRight;
					}
				}
				else if (event.key.keysym.sym == SDLK_UP) {
					if (state != snakeUp && state != snakeDown) {
						state = snakeUp;
					}
						
				}
				else if (event.key.keysym.sym == SDLK_DOWN) {
					if (state != snakeUp && state != snakeDown) {
						state = snakeDown;
					}						
				}
			}
			
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (game_over) {
					
					g_current_game_phase = PHASE_ENDING;
					Reset();
				}
			}
			break;

		default:
			break;
		}
	}
}

void Stage::Reset()
{
	snake.clear();
	snakes_x = 400;
	snakes_y = 300;
	snake.push_front({ snakes_x, snakes_y, WIDTH, HEIGHT });

	state = 4;
	game_over = false;
	game_ready =true;
	score = 0;

	SDL_RenderCopy(g_renderer, item_texture, &item_rect, &item_dest_rect);
	SDL_RenderCopy(g_renderer, potato_texture, &potato_rect, &potato_dest_rect);
	SDL_RenderCopy(g_renderer, snake_texture, &snake_rect, &(snake.front()));
	
}