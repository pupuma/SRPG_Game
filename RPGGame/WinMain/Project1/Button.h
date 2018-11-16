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
�ݹ� �Լ��� os�� ȣ��� �Լ��� ȣ��ǵ��� �Ѵ�. 

// �Լ� ������ : �ݹ� �Լ��� ���� �� �Լ� �����͸� ����Ѵ�.

// �Լ� �����Ͷ� ? 

// ��ȯ�� (*�Լ���) ( �Ű����� ����Ʈ ) ; 

// �Լ� ������
typedef void(*Func)(int);

// void �����ͷ� ��ȯ�Ѵ�.
typedef void* Func(int);

Func(10);

typedef void(*Func)(int);
Func pFunc = Function;					// �Ű�������� �Լ��� ���ؿ� ���� �ؾ� �Ѵ�.  
�Լ������ʹ� ���Կ� ���� ȣ���� �����ϴ�.
����Ǿ� �ִ� �Լ����������� ���� ( ��ȯ��, �Ű����� �ڷ���) �� ���� ��ġ �ؾ� �Ѵ�. 
�Լ��������� ���� = �Լ���(��ȣ�� ���� �Լ���) ;
����� �Լ������ʹ� �Լ� ���·� ��� ���� ; 
(*pFunc)(10); => pFunc(10); ���ڿ� ���� ���·� ȣ���� ���
�Լ� �������������� ĳ������ �����ϴ�. 
ex> 
int (*Func1)(int), float (*Func2)(float)

Func1 = (int (*) (int))Func2;

static : ���������� ����� �� 

Ŭ���� ���� �ɹ��Լ��� ����� �� static �϶� ���� ������ ���� ������ �޴´�.\

public: Ŭ���� ���ο����� publicó�� ��� �Ѵ�. 
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


// ����
Ŭ���� �ɹ� �Լ� �����ͷ� ����ϸ� �������� �ش������� ���ѵȴ�. 
Ŭ������ ȣ�� �ؾ� ����� �����ؼ� ���������� ����ϱ� �����.

c++ ��Ÿ�� �Լ� ������ 
// �Լ� ������
//std::function<void(*)()> pFunc;
			    <��ȯ��(�Ű�����)>

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

