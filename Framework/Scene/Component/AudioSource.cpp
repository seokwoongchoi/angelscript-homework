#include "stdafx.h"
#include "AudioSource.h"

AudioSource::AudioSource(Context * context, GameObject * object, Transform * transform)
	: IComponent(context, object, transform)
	, audioClip(nullptr)
	, filePath("")
	, bMute(false)
	, bLoop(false)
	, priority(128)
	, volume(1.0f)
	, pitch(0.0f)
	, pan(0.0f)
{
}

AudioSource::~AudioSource()
{
	SAFE_DELETE(audioClip);
}

void AudioSource::OnInitialize()
{
}

void AudioSource::OnStart()
{
}

void AudioSource::OnUpdate()
{
}

void AudioSource::OnStop()
{
}

void AudioSource::OnDestroy()
{
}

void AudioSource::OnSave()
{
}





void AudioSource::SetAudioClip(const string & filePath)
{
	SAFE_DELETE(audioClip);

	auto resourceManager = context->GetSubsystem<ResourceManager>();
	auto clip = resourceManager->Load<AudioClip>(filePath);

	audioClip = new AudioClip(*clip);
}

void AudioSource::SetAudioClip(AudioClip * audioClip)
{
	SAFE_DELETE(this->audioClip);
	this->audioClip = new AudioClip(*audioClip);
}

void AudioSource::Play()
{
	if (!audioClip)
		return;

	audioClip->Play();
	audioClip->SetMute(bMute);
	audioClip->SetLoop(bLoop);
	audioClip->SetVolume(volume);
	audioClip->SetPriority(priority);
	audioClip->SetPitch(pitch);
	audioClip->SetPan(pan);
}

void AudioSource::Stop()
{
	if (!audioClip)
		return;

	audioClip->Stop();
}

void AudioSource::SetIsMute(const bool & bMute)
{
	if (!audioClip)
		return;

	if (this->bMute == bMute)
		return;

	this->bMute = bMute;
	audioClip->SetMute(this->bMute);
}

void AudioSource::SetPriority(const int & priority)
{
	//채널 우선순위
	//0			: 가장 중요
	//256		: 가장 중요하지 않음
	//128		: default

	if (!audioClip)
		return;

	if (this->priority == priority)
		return;

	this->priority = Math::Clamp(priority, 0, 256);
	audioClip->SetPriority(this->priority);
}

void AudioSource::SetVolume(const float & volume)
{
	if (!audioClip)
		return;

	if (this->volume == volume)
		return;

	this->volume = Math::Clamp(volume, 0.0f, 1.0f);
	audioClip->SetVolume(this->volume);
}

void AudioSource::SetPitch(const float & pitch)
{
	if (!audioClip)
		return;

	if (this->pitch == pitch)
		return;

	this->pitch = Math::Clamp(pitch, 0.0f, 3.0f);
	audioClip->SetPitch(this->pitch);
}

void AudioSource::SetPan(const float & pan)
{
	if (!audioClip)
		return;

	if (this->pan == pan)
		return;

	this->pan = Math::Clamp(pan, -1.0f, 1.0f);
	audioClip->SetPan(this->pan);
}
