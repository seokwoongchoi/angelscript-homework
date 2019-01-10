#pragma once

enum class IconType : uint
{
	Audio,
	Camera,
	Light,
	Folder,
	File,
	Play,
	Pause,
	Stop,
	Custom,
};

struct Thumbnail
{
	Thumbnail()
		: type(IconType::Custom)
		, texture(nullptr)
		, filePath("")
	{}

	Thumbnail(const IconType& type, Texture* texture, const string& filePath)
		: type(type)
		, texture(texture)
		, filePath(filePath)
	{}

	IconType type;
	Texture* texture;
	string filePath;
};

class IconProvider
{
public:
	static IconProvider& Get()
	{
		static IconProvider instance;
		return instance;
	}

	void Initialize(class Context* context);

	const Thumbnail& Load
	(
		const string& filePath,
		const IconType& type = IconType::Custom
	);

	ID3D11ShaderResourceView* GetShaderResourceFromType(const IconType& type);
	ID3D11ShaderResourceView* GetShaderResourceFromPath(const string& filePath);

	const bool ImageButton(const IconType& type, const float& size);
	const bool ImageButton(const string& filePath, const float& size);

private:
	IconProvider() {}
	~IconProvider() {}

	const Thumbnail& GetThumbnailFromType(const IconType& type);

private:
	class Context* context;
	vector<Thumbnail> thumbnails;
};