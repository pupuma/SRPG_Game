#pragma once
#include "SingletonBase.h"

class Image;

class ImageManager : public SingletonBase<ImageManager>
{
private:
	typedef std::map<std::string, Image*>				mapImageList;
	typedef std::map<std::string, Image*>::iterator		mapImageIter;

private:
	mapImageList			_mImageList;

public:
	ImageManager();
	~ImageManager();
public:
	bool	Init();
	void	Release();

public:
	Image*	AddImage(std::string strKey, int width, int height);
	Image*	AddImage(std::string strKey, const TCHAR* fileName, int width, int height, bool trans, COLORREF transColor);
	Image*	AddImage(std::string strKey, const TCHAR* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor);

	Image*	AddFrameImage(std::string strKey, const TCHAR* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);
	Image*	AddFrameImage(std::string strKey, const TCHAR* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor);

	Image*	FindImage(std::string strKey);

	bool	DeleteImage(std::string strKey);
	bool	DeleteAll();

	void	Render(std::string strKey, HDC hdc);
	void	Render(std::string strKey, HDC hdc, int destX, int destY);
	void	Render(std::string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void	FrameRender(std::string strKey, HDC hdc, int destX, int destY);
	void	FrameRender(std::string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void	LoopRender(std::string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);

	//
	


};

