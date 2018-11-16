#pragma once

class Animation;

class Image
{
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,		// ���ҽ�����
		LOAD_FILE,			// ���Ϸκ���
		LOAD_EMPTY,			// �� ��Ʈ�����κ���
		LOAD_END
	};

private:
	typedef struct tagImageInfo
	{
		DWORD		resID;
		HDC			hMemDC;
		HBITMAP		hBit, hOldBit;
		float		x, y;
		int			width;			// �̹��� ��ü ����
		int			height;			// �̹��� ��ü ����

		int			currentFrameX;	// ������ �̹��� �߿� ���� ������ ������ X�� �ε���
		int			currentFrameY;  // ������ �̹��� �߿� ���� ������ ������ Y�� �ε���
		int			maxFrameX;		// X���� ������ �ε���
		int			maxFrameY;		// Y���� ������ �ε���
		int			frameWidth;		// ������ �̹��� ������ ����
		int			frameHeight;	// ������ �̹��� ������ ����
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
	LPIMAGE_INFO	_imageInfo;			// �̹��� ���� ����ü
	TCHAR*			_fileName;			// ���� �̸�
	bool			_trans;				// Ʈ�����÷� ����
	COLORREF		_transColor;		// Ű �÷�(������ ��)
	BLENDFUNCTION	_blendFunc;			// ���� ����ü 
	LPIMAGE_INFO	_blendImage;		// ���� �̹��� ���� ����ü 


public:
	Image();
	~Image();
public:
	// ���Ʈ�� �ε���
	bool Init(int width, int height);

	// ���Ϸκ����� �ε���
	bool Init(const TCHAR* fileName, int width, int height, bool trans = false, COLORREF transColor = false);
	bool Init(const TCHAR* fileName, float x, float y, int width, int height, bool trans = false, COLORREF transColor = false);

	// ������ �̹�����
	bool Init(const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY,
		bool trans = false, COLORREF transColor = false);
	bool Init(const TCHAR* fileName, int width, int height, int frameX, int frameY,
		bool trans = false, COLORREF transColor = false);

	// ��Ÿ ���� ���� ��
	void SetTransColor(bool trans, COLORREF transColor);

	// ������
	void Release();

	// �Ϲ� �̹��� ������
	void Render(HDC hdc);
	void Render(HDC hdc, int destX, int destY);
	void Render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	// ���� ����
	void LoopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	// �ִ� ����
	void AniRender(HDC hdc, int destX, int destY, Animation* ani);

	// ��������Ʈ �̹��� ������
	void FrameRender(HDC hdc, int destX, int destY);
	void FrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	// ���� ���� 
	void AlphaRender(HDC hdc, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, BYTE alpha);
	void AlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);

public:
	// ���Ǹ� ���� ��Ÿ �Լ���
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

