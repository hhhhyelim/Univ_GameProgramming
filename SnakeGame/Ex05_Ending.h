#pragma once

class Ending : public PhaseInterface
{
public:

	// 생성자 함수
	Ending();
	// 파괴자 함수
	~Ending();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	SDL_Texture* ending_texture;
	SDL_Rect ending_rect;
	SDL_Rect ending_dest_rect;

};
