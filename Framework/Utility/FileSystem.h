#pragma once

class FileSystem
{
public:
	static const char* EveryFilter;
	static const char* TextureFilter;
	static const char* ShaderFilter;
	static const char* XmlFilter;

public:
	static void OpenFileDialog
	(
		function<void(string)> func,
		const char* filter = EveryFilter,
		const char* directory = ""
	);
	static void SaveFileDialog
	(
		function<void(string)> func,
		const char* filter = EveryFilter,
		const char* directory = ""
	);

public:
	static const bool Create_Directory(const string& path);
	static const bool Delete_Directory(const string& directory);
	static const bool Delete_File(const string& path);
	static const bool Copy_File(const string& src, const string& dst);
	static const bool IsDirectory(const string& path);
	static const bool ExistDirectory(const string& directory);
	static const bool ExistFile(const string& path);

	static const string GetFileNameFromPath(const string& path);
	static const string GetIntactFileNameFromPath(const string& path);
	static const string GetDirectoryFromPath(const string& path);
	static const string GetExtensionFromPath(const string& path);
	static const string GetRelativeFilePath(const string& absolutePath);
	static const string GetWorkingDirectory();
	static const string GetParentDirectory(const string& directory);
	static const vector<string> GetDirectoriesInDirectory(const string& directory);
	static const vector<string> GetFilesInDirectory(const string& directory);

	static const vector<string>& GetSupportImageFormats() { return supportImageFormats; }
	static const vector<string>& GetSupportAudioFormats() { return supportAudioFormats; }
	static const vector<string>& GetSupportShaderFormats() { return supportShaderFormats; }
	static const vector<string>& GetSupportBinaryFormats() { return supportBinaryFormats; }

	static const bool IsSupportedImageFile(const string& path);
	static const bool IsSupportedAudioFile(const string& path);
	static const bool IsSupportedShaderFile(const string& path);
	static const bool IsSupportedBinaryFile(const string& path);

	static void ReplaceAll(string& str, const string& from, const string& to);
	static const string ToUpper(const string& lower);
	static const string ToLower(const string& upper);
	static const wstring ToWstring(const string& value);
	static const string ToString(const wstring& value);

private:
	static vector<string> supportImageFormats;
	static vector<string> supportAudioFormats;
	static vector<string> supportShaderFormats;
	static vector<string> supportBinaryFormats;
};