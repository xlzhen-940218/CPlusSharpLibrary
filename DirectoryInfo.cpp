#include "DirectoryInfo.h"
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <dirent.h>
#include <sys/stat.h>
#endif

void DirectoryInfo::ListDirectory() {

#ifdef _WIN32
	std::wstring wpath;
	int size = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, NULL, 0);
	if (size > 0) {
		wpath.resize(size);
		MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, &wpath[0], size);
	}
	std::wstring search_path = wpath.c_str();
	search_path.append(L"\\*");

	WIN32_FIND_DATAW find_data;
	HANDLE h_find = FindFirstFileW(search_path.c_str(), &find_data);
	if (h_find == INVALID_HANDLE_VALUE) return;

	do {
		std::wstring name = find_data.cFileName;
		if (name == L"." || name == L"..") continue;

		char utf8_name[256];
		WideCharToMultiByte(CP_UTF8, 0, name.c_str(), -1, utf8_name, 256, NULL, NULL);
		std::string fullpath = path;
		fullpath.append("\\");
		fullpath.append(utf8_name);
		entries.push_back(std::make_pair((find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0, fullpath));
	} while (FindNextFileW(h_find, &find_data));

	FindClose(h_find);

#else
	DIR* dir = opendir(path.c_str());
	if (!dir) return;

	struct dirent* entry;
	while ((entry = readdir(dir)) != nullptr) {
		std::string name = entry->d_name;
		if (name == "." || name == "..") continue;
		std::string fullpath = path;
		fullpath.append("/");
		fullpath.append(name);
		entries.push_back(std::make_pair(entry->d_type == DT_DIR, fullpath));
	}

	closedir(dir);
#endif
}


std::vector<FileInfo*> DirectoryInfo::GetFiles()
{
	std::vector<FileInfo*> files;
	if (entries.size() == 0) {
		ListDirectory();
	}
	for (const auto& entry : entries) {
		if (!entry.first) {
			files.push_back(new FileInfo(entry.second,true));
		}
	}
	return files;
}

std::vector<DirectoryInfo*> DirectoryInfo::GetDirectories()
{
	std::vector<DirectoryInfo*> directorys;
	if (entries.size() == 0) {
		ListDirectory();
	}
	for (const auto& entry : entries) {
		if (entry.first) {
			directorys.push_back(new DirectoryInfo(entry.second,false));
		}
	}
	return directorys;
}
