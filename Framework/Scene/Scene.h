#pragma once

class Scene
{
public:
	Scene(class Context* context);
	virtual ~Scene();

	const string& GetName() const { return name; }
	class GameObject* GetMainCamera() const { return mainCamera; }
	const vector<class GameObject*>& GetObjects() const { return objects; }

	void SetName(const string& name) { this->name = name; }

	class GameObject* CreateObject();
	void AddObject(class GameObject* object);
	void RemoveObject(class GameObject* object);
	const bool IsExistObject(class GameObject* object);
	void SaveSetting(bool& bSave);
	
	void Update();

private:
	class Context* context;	
	class Renderer* renderer;
	class GameObject* mainCamera;
	vector<class GameObject*> objects;
	string name;
	bool bEditorMode;
	bool bAdded;
	
};