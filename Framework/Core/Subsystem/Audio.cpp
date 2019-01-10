#include "stdafx.h"
#include "Audio.h"

Audio::Audio(Context * context)
	: ISubsystem(context)
	, system(nullptr)
	, maxChannel(32)
	, distanceFactor(1.0f)
	, result(FMOD_OK)
	, bInitialized(false)
{
}

Audio::~Audio()
{
	if (!bInitialized)
		return;

	result = system->close();
	assert(result == FMOD_OK);

	result = system->release();
	assert(result == FMOD_OK);
}

const bool Audio::Initialize()
{
	if (bInitialized)
		return false;

	//FMOD System 생성
	result = System_Create(&system);
	assert(result == FMOD_OK);

	//FMOD Version Check
	uint version = 0;
	result = system->getVersion(&version);
	assert(result == FMOD_OK);
	assert(version >= FMOD_VERSION);

	//시스템에 사운드 카드 장치가 있는지 확인
	int driverCount = 0;
	result = system->getNumDrivers(&driverCount);
	assert(result == FMOD_OK);
	assert(driverCount > 0);

	//FMOD System 초기화
	result = system->init(maxChannel, FMOD_INIT_NORMAL, nullptr);
	assert(result == FMOD_OK);

	//FMOD 3D 세팅
	result = system->set3DSettings
	(
		1.0f,
		distanceFactor,
		0.0f
	);
	assert(result == FMOD_OK);

	bInitialized = true;

	return true;
}

void Audio::Update()
{
	if (!bInitialized)
		return;

	result = system->update();
	assert(result == FMOD_OK);

	//TODO : listener 만들고 처리
}
