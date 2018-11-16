#pragma once

class ProgressBar
{
private:
	RECT		_rcProgress;
	int			_x;
	int			_y;
	float		_width;
	
	Image*		_progressBarTop;
	Image*		_progressBarBottom;


public:
	ProgressBar();
	~ProgressBar();
public:
	bool Init(int x, int y, int width, int height);
	bool Init(std::string strTop, std::string strBack, int x, int y, int width, int height);

	void Release();
	void Update();
	
	void Render(HDC hdc);
	void Render(HDC hdc, const POINT* _pt);
public:
	void SetGauge(float currentGauge, float maxGaguge);
public:
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }

};

