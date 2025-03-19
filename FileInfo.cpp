#include "FileInfo.h"
#include <vector>
#include <sstream>
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#include <sys/sendfile.h>
#endif

#include "DirectoryInfo.h"
#ifdef WIN32
#define realpath(N,R) _fullpath((R),(N),8192)
char* GB2312ToUtf8(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}
#endif

FileInfo::FileInfo(std::string absPath, bool isFile) :isFile(isFile)
{
	std::locale::global(std::locale("zh_CN.utf8"));
	if (isFile) {
		file.open(absPath, std::ios::in);
		if (!file.good()) {
			fileSize = 0;
#ifdef _WIN32
			absPath = GB2312ToUtf8(absPath.c_str());
			file.open(absPath, std::ios::in);
			if (!file.good()) {
				return;
			}
#else
			return;
#endif // _WIN32
		}
	}


	char fullpath[8192];

	path = realpath((char*)absPath.c_str(), (char*)&fullpath);

	fileSize = GetFileSize(path);
}

long long FileInfo::GetFileSize(const std::string& filepath) {
#ifdef _WIN32
	WIN32_FILE_ATTRIBUTE_DATA fileInfo;
	if (!GetFileAttributesExA(filepath.c_str(), GetFileExInfoStandard, &fileInfo)) {
		return -1; 
	}
	LARGE_INTEGER size;
	size.HighPart = fileInfo.nFileSizeHigh;
	size.LowPart = fileInfo.nFileSizeLow;
	return size.QuadPart;
#else
	struct stat stat_buf;
	if (stat(filepath.c_str(), &stat_buf) != 0) {
		return -1;
	}
	return stat_buf.st_size;
#endif
}

FileInfo::~FileInfo()
{
	if (file && file.is_open()) {
		file.close();
	}
}

std::string FileInfo::GetName()
{
	size_t pos = path.find_last_of("/\\");

	if (pos != std::string::npos) {
		return path.substr(pos + 1);
	}

	return path;
}

long long FileInfo::GetSize()
{
	return fileSize;
}

std::string FileInfo::GetSizeFormatString(int precision)
{
#ifdef __APPLE__
	double bit = 1000.0;
#elif __linux__
	double bit = 1000.0;
#else
	double bit = 1024.0;
#endif // _WIN32

	const std::vector<std::pair<double, std::string>> units = {
		{bit * bit * bit, "GB"},
		{bit * bit,    "MB"},
		{bit,       "KB"},
		{1.0,          "B"}
	};

	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision);

	for (const auto& uint : units) {
		auto unit_size = uint.first;
		auto unit_name = uint.second;
		if (fileSize >= unit_size) {
			double value = static_cast<double>(fileSize) / unit_size;
			ss << value << unit_name;
			return ss.str();
		}
	}

	return "0B";
}

long long FileInfo::GetLength()
{
	return GetSize();
}

std::string FileInfo::GetParentDirPath()
{
	size_t pos = path.find_last_of("/\\");

	if (pos != std::string::npos) {
		return path.substr(0, pos);
	}

	return path;
}

std::string FileInfo::GetDirectoryPath()
{
	return GetParentDirPath();
}

DirectoryInfo* FileInfo::GetParentDir()
{
	return new DirectoryInfo(GetParentDirPath(), false);
}

DirectoryInfo* FileInfo::GetDirectory()
{
	return new DirectoryInfo(GetParentDirPath(), false);
}

bool FileInfo::isReadOnly()
{
#ifdef _WIN32
	DWORD attrs = GetFileAttributesA(path.c_str());
	return (attrs != INVALID_FILE_ATTRIBUTES) && (attrs & FILE_ATTRIBUTE_READONLY);
#else
	return (access(path.c_str(), W_OK) != 0);
#endif
}

bool FileInfo::Exists()
{
	return file.good();
}

std::string FileInfo::GetFullPath()
{
	return path;
}

FileInfo* FileInfo::CopyTo(std::string destPath, bool overwrite)
{
#ifdef _WIN32
	if (!overwrite) {
		const DWORD attrs = GetFileAttributesA(destPath.c_str());
		if (attrs != INVALID_FILE_ATTRIBUTES &&
			!(attrs & FILE_ATTRIBUTE_DIRECTORY)) {
			return new FileInfo(destPath, true);
		}
	}

	CopyFileExA(
		path.c_str(),
		destPath.c_str(),
		nullptr,       
		nullptr,       
		nullptr,       
		overwrite ? 0 : COPY_FILE_FAIL_IF_EXISTS
	);
#else
	if (!overwrite) {
		struct stat st;
		if (stat(destPath.c_str(), &st) == 0 && S_ISREG(st.st_mode)) {
			return new FileInfo(destPath, true);
		}
	}

	FILE* srcFile = fopen(path.c_str(),"rb");
	if (srcFile == nullptr) return new FileInfo(destPath, true);

	struct stat src_stat;
	if (fstat(fileno(srcFile), &src_stat) != 0) {
		fclose(srcFile);
		return new FileInfo(destPath, true);
	}

	FILE* destFile = fopen(destPath.c_str(), "wb");
	if (destFile == nullptr) {
		fclose(destFile);
		return new FileInfo(destPath, true);
	}

	off_t offset = 0;
	const ssize_t result = sendfile(
		fileno(destFile),
		fileno(srcFile),
		&offset,
		src_stat.st_size
	);

	fclose(srcFile);
	fclose(destFile);
#endif // _WIN32
	return new FileInfo(destPath, true);
}

FileInfo* FileInfo::MoveTo(std::string destPath, bool overwrite)
{
	FileInfo* newFile = CopyTo(destPath, overwrite);
	Delete();
	return newFile;
}

bool FileInfo::Delete()
{
	int ret = std::remove(path.c_str());
	return ret >= 0;
}
