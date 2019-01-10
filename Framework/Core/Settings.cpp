#include "stdafx.h"
#include "Settings.h"

Settings* Settings::instance = nullptr;

Settings * Settings::Get()
{
	if (!instance)
		instance = new Settings();

	return instance;
}

void Settings::Delete()
{
	SAFE_DELETE(instance);
}

Settings::Settings()
	: appName(L"")
	, hInstance(nullptr)
	, handle(nullptr)
	, width(0)
	, height(0)
	, bVsync(true)
	, bFullScreen(false)
	, relative(0, 0)
{
}
