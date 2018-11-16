#pragma once

class Animation;

class Image
{
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		// 리소스에서
		LOAD_FILE,			// 파일로부터
		LOAD_EMPTY,			// 빈 비트맵으로부터
		LOAD_END
	};

private:
	typedef struct tagImageInfo
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit, hOldBit;
		float		x, y;
		int			width;			// 이미지 전체 넓이
		int			height;			// 이미지 전체 높이

		int			currentFrameX;	// 프레임 이미지 중에 현재 랜더링 순서인 X쪽 인덱스
		int			currentFrameY;  // 프레임 이미지 중에 현재 랜더링 순서인 Y쪽 인덱스
		int			maxFrameX;		// X쪽의 마지막 인덱스
		int			maxFrameY;		// Y쪽의 마지막 인덱스
		int			frameWidth;		// 프레임 이미지 한장의 넓이
		int			frameHeight;	// 프레임 이미지 한장의 높이
		BYTE		loadType;
		RECT		boundingBox;

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOldBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
			boundingBox = RectMake(0, 0, 0, 0);
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;			// 이미지 정보 구조체
	TCHAR*			_fileName;			// 파일 이름
	bool			_trans;				// 트랜스컬러 유무
	COLORREF		_transColor;		// 키 컬러(제거할 색)
	BLENDFUNCTION	_blendFunc;			// 블랜드 구조체 
	LPIMAGE_INFO	_blendImage;		// 블랜딩 이미지 정보 구조체 


public:
	Image();
	~Image();
public:
	// 빈비트맵 로딩용
	bool Init(int width, int height);

	// 파일로부터의 로딩용
	bool Init(const TCHAR* fileName, int width, int height, bool trans = false, COLORREF transColor = false);
	bool Init(const TCHAR* fileName, float x, float y, int width, int height, bool trans = false, COLORREF transColor = false);

	// 프레임 이미지용
	bool Init(const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY,
		bool trans = false, COLORREF transColor = false);
	bool Init(const TCHAR* fileName, int width, int height, int frameX, int frameY,
		bool trans = false, COLORREF transColor = false);

	// 기타 상태 설정 용
	void SetTransColor(bool trans, COLORREF transColor);

	// 정리용
	void Release();

	// 일반 이미지 랜더용
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// 루프 랜더
	void LoopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	// 애니 랜더
	void AniRender(HDC hdc, int destX, int destY, Animation* ani);

	// 스프라이트 이미지 랜더용
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// 알파 랜더 
	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

public:
	// 편의를 위한 기타 함수들
	inline void		SetX(float x) { _imageInfo->x = x; }
	inline float	GetX() { return _imageInfo->x; }

	inline void		SetY(float y) { _imageInfo->y = y; }
	inline float	GetY() { return _imageInfo->y; }

	inline void		SetCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float	GetCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ? _imageInfo->x + (_imageInfo->width / 2) : _imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float	GetCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ? _imageInfo->y + (_imageInfo->height / 2) : _imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int		GetWidth() { return _imageInfo->width; }
	inline int		GetHeight() { return _imageInfo->height; }

	inline RECT		BoundingBox()
	{
		RECT rc = { int(_imageInfo->x),
		int(_imageInfo->y),
		int(_imageInfo->frameWidth),
		int(_imageInfo->frameHeight) };

		return rc;
	}

	inline void SetFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX) _imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}

	inline void SetFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY) _imageInfo->currentFrameY = _imageInfo->maxFrameY;
	}

	inline int GetMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int GetFrameX() { return _imageInfo->currentFrameX; }
	inline int GetFrameY() { return _imageInfo->currentFrameY; }

	inline int GetFrameWidth() { return _imageInfo->frameWidth; }
	inline int GetFrameHeight() { return _imageInfo->frameHeight; }

	inline POINT GetSize() { return POINT{ _imageInfo->width, _imageInfo->height }; }
	inline POINT GetFrameSize() { return POINT{ _imageInfo->frameWidth, _imageInfo->frameHeight }; }
	inline POINT GetMaxFrame() { return POINT{ _imageInfo->maxFrameX, _imageInfo->maxFrameY }; }

	inline HDC	 GetMemDC() { return _imageInfo->hMemDC; }
};

