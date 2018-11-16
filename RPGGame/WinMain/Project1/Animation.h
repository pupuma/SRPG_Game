#pragma once

class Image;

class Animation
{
public:
	typedef std::vector<POINT>		vFrameList;
	typedef std::vector<int>		vPlayList;

private:
	vFrameList						_frameList;
	vPlayList						_playList;

	int		_frameNum;
	int		_frameWidth;
	int		_frameHeight;

	bool	_loop;
	bool	_play;

	float	_frameUpdateSec;
	float	_elapsedSec;

	DWORD	_nowPlayIndex;

public:
	Animation();
	~Animation();

public:
	bool Init(int totalW, int totalH, int frameW, int frameH);
	bool Init(Image* image);

	void Release();
public:
	void SetDefPlayFrame(bool reverse = false, bool loop = false);
	void SetPlayFrame(int *playArr, int arLen, bool loop = false);
	void SetPlayFrame(int start, int end, bool reverse = false, bool loop = false);

	void SetFPS(int framePerSec);
	
	void FrameUpdate(float elapsedTime);
	
	void Start();
	void Stop();
	void Pause();
	void Resume();

public:
	inline bool isPlay() { return _play; }
	inline POINT getFramePos() { return _frameList[_playList[_nowPlayIndex]]; }
	inline int getFrameWidth() { return _frameWidth; }
	inline int getFrameHeight() { return _frameHeight; }
};