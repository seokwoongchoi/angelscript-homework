#pragma once
#include "stdafx.h"
#include "./Subsystem/ISubsystem.h"

class Context
{
public:
	Context() {}
	virtual ~Context() 
	{
		for (uint i = subsystems.size() - 1; i > 0; i--)
			SAFE_DELETE(subsystems[i]);
	}

	void RegistSubsystem(class ISubsystem* subsystem)
	{
		if (!subsystem)
			assert(false);

		subsystems.push_back(subsystem);
	}

	template <typename T>
	T* GetSubsystem();

private:
	vector<class ISubsystem*> subsystems;
};

template<typename T>
inline T * Context::GetSubsystem()
{
	for (auto subsystem : subsystems)
	{
		if (typeid(T) == typeid(*subsystem))
			return static_cast<T*>(subsystem);
	}
	return nullptr;
}
