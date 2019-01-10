#include "stdafx.h"
#include "ColliderManager.h"
#include "../../Scene/Component/Collider.h"

ColliderManager::ColliderManager(Context * context)
	: ISubsystem(context)
{
}

ColliderManager::~ColliderManager()
{
	Clear();
}

void ColliderManager::RegistCollider(const string & layer, Collider * collider)
{
	colliderTable[layer].emplace_back(collider);
}

void ColliderManager::RegistColliders(const string & layer, const vector<class Collider*>& colliders)
{
	colliderTable[layer].insert
	(
		colliderTable[layer].end(),
		colliders.begin(),
		colliders.end()
	);
}

void ColliderManager::Clear()
{
	colliderTable.clear();
}

void ColliderManager::HitCheck_AABB(const string & attacker, const string & receiver)
{
	for (auto receiverCollider : colliderTable[receiver])
		for (auto attackerCollider : colliderTable[attacker])
		{
			bool bCheck = receiverCollider->AABB(attackerCollider);

			if (bCheck)
			{
				if (receiverCollider->Event != nullptr)
					receiverCollider->Event();
			}
		}
}

void ColliderManager::HitCheck_OBB(const string & attacker, const string & receiver)
{
	for (auto receiverCollider : colliderTable[receiver])
		for (auto attackerCollider : colliderTable[attacker])
		{
			bool bCheck = receiverCollider->OBB(attackerCollider);

			if (bCheck)
			{
				if (receiverCollider->Event != nullptr)
					receiverCollider->Event();
			}
		}
}
