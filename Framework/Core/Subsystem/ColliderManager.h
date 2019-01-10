#pragma once
#include "ISubsystem.h"

class ColliderManager : public ISubsystem
{
public:
	ColliderManager(class Context* context);
	virtual ~ColliderManager();

	const bool Initialize() override { return true; }

	void RegistCollider
	(
		const string& layer,
		class Collider* collider
	);

	void RegistColliders
	(
		const string& layer,
		const vector<class Collider*>& colliders
	);

	void Clear();

	void HitCheck_AABB
	(
		const string& attacker,
		const string& receiver
	);

	void HitCheck_OBB
	(
		const string& attacker,
		const string& receiver
	);

private:
	map<string, vector<class Collider*>> colliderTable;
};