#pragma once

class Camera : public SingletonBase<Camera>
{
	POINT*		pTarget;
	POINT*		pPos;

	RECT		rcClient;
	RECT		rcWorld;

public:
	Camera();
	~Camera();
public:
	bool Init(POINT* _pt, const RECT& _client, const RECT& _world);

	void Update();

public:
	void setTargetPos(POINT* _pt) { pTarget = _pt; }
	void setPosition(POINT* _pt) { pPos = _pt; }

	const POINT* GetTargetPos() const { return pTarget; }
	const POINT* GetPosition() const { return pPos; }

	void SetClientRect(const RECT& _rt) { rcClient = _rt; }
	void SetWorldRect(const RECT& _rt) { rcWorld = _rt; }

	const RECT& GetClientRect() const { return rcClient; }
	const RECT& GetWorldRect() const { return rcWorld; }

	bool operator==(const POINT* pObj) { return pTarget == pObj; }
	bool operator!=(const POINT* pObj) { return pTarget != pObj; }


};

