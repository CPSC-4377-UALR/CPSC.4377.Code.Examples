#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:
	Component(GameObject* owner);
	~Component();
	void OwnerDestroyed();
	GameObject* GetOwner();
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Finish() = 0;

protected:
	GameObject* _owner;
};


#endif