#pragma once

enum BUTTTONDIR
{
	BUTTONDIR_NONE,
	BUTTONDIR_UP,
	BUTTONDIR_DOWN, 

};

typedef void(*FUNC)();
//typedef std::function<void(*)()> pFunc;

class Button
{
private:
	BUTTTONDIR		_direction;
	std::string		_imageName;
	Image*			_image;
	RECT			_rc;
	POINT			_btnDownFramePoint;
	POINT			_btnUpFramePoint;

	FUNC			_callBackFunc;

	float			_x;
	float			_y;
	

public:
	Button();
	~Button();
public:
	bool Init(const std::string imageName, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint,
		FUNC pFunc);

	void Release();
	void Update();
	void Render(HDC hdc);

};

/*
콜백 함수는 os가 호출된 함수를 호출되도록 한다. 

// 함수 포인터 : 콜백 함수를 만들 때 함수 포인터를 사용한다.

// 함수 포인터란 ? 

// 반환형 (*함수명) ( 매개변수 리스트 ) ; 

// 함수 포인터
typedef void(*Func)(int);

// void 포인터로 반환한다.
typedef void* Func(int);

Func(10);

typedef void(*Func)(int);
Func pFunc = Function;					// 매개변수들과 함수를 스텍에 저장 해야 한다.  
함수포인터는 대입에 대한 호출이 가능하다.
선언되어 있는 함수포인터형의 정보 ( 반환형, 매개변수 자료형) 이 완전 일치 해야 한다. 
함수포인터형 변수 = 함수명(괄호가 빠진 함수명) ;
선언된 함수포인터는 함수 형태로 사용 가능 ; 
(*pFunc)(10); => pFunc(10); 후자와 같은 형태로 호출이 허용
함수 포인터형간에는 캐스팅이 가능하다. 
ex> 
int (*Func1)(int), float (*Func2)(float)

Func1 = (int (*) (int))Func2;

static : 전역적으로 사용할 때 

클래스 에게 맴버함수로 사용할 때 static 일땐 접근 지정자 에게 영향을 받는다.\

public: 클래스 내부에서만 public처럼 사용 한다. 
private: 

class AAA
{
public:
	void Func1() {;}
	static void Func2() { ; } 
};

int mian()
{
	AAA a;
	a.Func1();

	void(*pFunc1)() = &AAA::Func1;


	a.pFunc1();
	(a.*pFunc1)();

	void(*pFunc2)() = &AAA::Func2;


	return 0;
}


// 단점
클래스 맴버 함수 포인터로 사용하면 사용범위가 극단적으로 제한된다. 
클래스를 호출 해야 사용이 가능해서 범용적으로 사용하기 힘들다.

c++ 스타일 함수 포인터 
// 함수 포인터
//std::function<void(*)()> pFunc;
			    <반환형(매개변수)>

class AAA
{
public
	int operator()(int n)
	{
		return (n + 1);
	}
}

int Func1(int n)
{
	return (n + 10);
}

class AAA
{
public:
	static void Func2()
	{
		std::cout << "AAA::Func2() Exec " << std::endl;
	}
}

std::function<int(int)> pFunc = Func1;
int n = pFunc(10);

std::function<void()> pFunc1 = AAA::Func2;
pFunc1();


*/

