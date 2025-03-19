#include "FileInfo.h"
#include "DirectoryInfo.h"
int main(int argc, const char* argv[]) {
	FileInfo fileInfo(argv[1], true);

	printf("name = %s\r\n", fileInfo.GetName().c_str());
	printf("size = %lld\r\n", fileInfo.GetSize());
	printf("sizeFormatStr = %s\r\n", fileInfo.GetSizeFormatString(2).c_str());
	printf("directoryPath = %s\r\n", fileInfo.GetDirectoryPath().c_str());
	printf("readonly = %d\r\n", fileInfo.isReadOnly());
	printf("exist = %d\r\n", fileInfo.Exists());
	auto directory = fileInfo.GetDirectory();
	auto directorys = directory->GetDirectories();
	for (const auto& dir : directorys) {
		printf("dir %s\r\n",dir->GetName().c_str());
	}
	auto files = directory->GetFiles();
	for (const auto& file : files) {
		printf("file %s\r\n",file->GetName().c_str());
	}
	//fileInfo.CopyTo("/home/xlzhen/测试中文/Clash.for.Windows-0.20.39-Opt.1-linux-x64.拷贝.tar.gz",true);
	//fileInfo.MoveTo("/home/xlzhen/测试中文/Clash.for.Windows-0.20.39-Opt.1-linux-x64.粘贴.tar.gz", true);
}