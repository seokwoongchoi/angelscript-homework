#pragma once
#include "stdafx.h"

class ISubsystem
{
public:
	ISubsystem(class Context* context) : context(context) {}
	virtual ~ISubsystem() {}

	virtual const bool Initialize() = 0;

protected:
	class Context* context;
};