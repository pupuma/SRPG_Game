#pragma once

class Animation;

class Effect
{
private:
	Image*		_effectImage;
	Animation* _effectAnimation;

	int			_x;
	int			_y;
	bool		_isRunning;

	float		_fps;
	float		_elapsedTime;

public:
	Effect();
	Effect(const Effect& effect);
	
	~Effect();
private:
	Effect& operator=(const Effect& effect)
	{
		_effectImage = effect._effectImage;
		_effectAnimation = nullptr;
		_x = effect._x;
		_y = effect._y;
		_fps = effect._fps;
		_elapsedTime = effect._elapsedTime;
		_isRunning = false;

		return *this;
	}
public:
	bool Init(Image* effectImage, int frameW, int frameY, int fps, float elapsedTime);
	void Release();
	void Update();
	void Render(HDC hdc);

	void KillEffect();
	void StartEffect(int x, int y);
	bool GetIsRunning() { return _isRunning; }
	Image* GetImage() { return _effectImage; }
	Animation* GetAni() {return _effectAnimation;}
	float GetFPS() { return _fps;}
	void SetFPS(float fps) { _fps = fps; }
	float GetElapsedTime() { return _elapsedTime; }
	void SetElapsedTime(float elapsedTime) { _elapsedTime = elapsedTime; }
};

