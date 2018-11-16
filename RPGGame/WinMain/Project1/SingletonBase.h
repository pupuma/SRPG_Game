#pragma once

// �ϳ��� ���¸� �˰� �־�� �ϱ� ������ �ν��Ͻ��� ���� ����ƽ���� �����ؾ� �Ѵ�.
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