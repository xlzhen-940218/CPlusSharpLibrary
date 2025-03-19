#pragma once
#include "FileInfo.h"
#include <vector>
class DirectoryInfo :public FileInfo
{
public:
	using FileInfo::FileInfo;
	std::vector<FileInfo*> GetFiles();
	std::vector<DirectoryInfo*> GetDirectories();
private:
	void ListDirectory();
	std::vector<std::pair<bool,std::string>> entries;
};

