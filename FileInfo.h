#include <fstream>
#pragma once
class DirectoryInfo;
class FileInfo
{
public:

	FileInfo(std::string absPath, bool isFile);

	~FileInfo();
	std::string GetName();
	long long GetSize();
	std::string GetSizeFormatString(int precision);
	long long GetLength();
	std::string GetParentDirPath();
	std::string GetDirectoryPath();
	DirectoryInfo* GetParentDir();
	DirectoryInfo* GetDirectory();
	bool isReadOnly();
	bool Exists();
	std::string GetFullPath();
	FileInfo* CopyTo(std::string destPath, bool overwrite);
	FileInfo* MoveTo(std::string destPath, bool overwrite);
	bool Delete();
protected:
	std::ifstream file;
	std::streamsize fileSize;
	std::string path;
	bool isFile = true;
private:
	long long GetFileSize(const std::string& filepath);
};

