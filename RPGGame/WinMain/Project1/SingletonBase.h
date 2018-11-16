#pragma once

// 하나의 상태를 알고 있어야 하기 때문에 인스턴스에 대한 스태틱으로 선언해야 한다.
//

template <typename T>
class SingletonBase
{
protected:
	static T* signletonInstace;
protected:
	SingletonBase() {}
	~SingletonBase() {}

public:
	static T*	GetSingleton();
	void		ReleaseSingleton();
};

template <typename T>
T* SingletonBase<T>::signletonInstace = 0;

template <typename T>
T* SingletonBase<T>::GetSingleton()
{
	if (!signletonInstace)	
	{
		signletonInstace = new T();
	}

	return signletonInstace;
}

template <typename T>
void SingletonBase<T>::ReleaseSingleton()
{
	if (signletonInstace)
	{
		delete signletonInstace;
		signletonInstace = 0;
	}

}