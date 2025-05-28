#include "FileInfo.h"
#include "DirectoryInfo.h"
#include "String.h"
int main(int argc, const char* argv[])
{
	std::string arg = argv[1];
	String str(arg.c_str());
	auto c = str.charAt(0);
	printf("char %c\n",c);
	auto sub = str.substring(10,20);
	printf("sub %s\n", sub.c_str());
	std::string indexOfStr = "P";
	printf("indexOf %d %d\n",str.indexOf('C'),str.indexOf(indexOfStr));
	printf("lastIndexOf %d %d\n", str.lastIndexOf('C'), str.lastIndexOf(indexOfStr));
	auto lowerCaseStr = str.toLowerCase();
	printf("toLowerCase %s toUpperCase %s\n", lowerCaseStr.c_str(),str.toUpperCase().c_str());

	printf("replace a to b %s\n",str.replace('a','b').c_str());
	std::string regexStr = "xiong";
	std::string replaceStr = "hello";
	printf("replace all %s\n",str.replaceAll(regexStr,replaceStr).c_str());
	printf("replace first %s\n", str.replaceFirst(regexStr, replaceStr).c_str());
	String hasTrimStr = " a ";
	auto trimStr = hasTrimStr.trim();
	printf("trim %s\n", trimStr.c_str());
	printf("start with %d\n",str.startsWith(trimStr));
	printf("end with %d\n", str.endWith(trimStr));
	printf("contains %d\n", str.contains(trimStr));

	auto splitStrs = str.split("\\");
	for (std::string s : splitStrs) {
		printf("split char str %s\n",s.c_str());
	}
	std::string splitStr = "xiong";
	splitStrs = str.split(splitStr);
	for (std::string s : splitStrs) {
		printf("split string str %s\n", s.c_str());
	}
	/*FileInfo fileInfo(argv[1], true);

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
	}*/
	//fileInfo.CopyTo("/home/xlzhen/测试中文/Clash.for.Windows-0.20.39-Opt.1-linux-x64.拷贝.tar.gz",true);
	//fileInfo.MoveTo("/home/xlzhen/测试中文/Clash.for.Windows-0.20.39-Opt.1-linux-x64.粘贴.tar.gz", true);
}