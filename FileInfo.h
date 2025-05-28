#include <fstream>
#pragma once
/**
 * @brief 前置声明DirectoryInfo类
 */
class DirectoryInfo;

/**
 * @brief 文件信息类，封装文件相关操作和属性
 *
 * 该类提供了文件的常用操作，如获取文件信息、复制、移动、删除等，
 * 以及文件属性的访问，如文件名、大小、路径等。
 */
class FileInfo
{
public:
    /**
     * @brief 构造函数
     * @param absPath 文件的绝对路径
     * @param isFile 是否为文件(true)或目录(false)
     */
    FileInfo(std::string absPath, bool isFile);

    /**
     * @brief 析构函数
     */
    ~FileInfo();

    /**
     * @brief 获取文件名(不含路径)
     * @return 文件名
     */
    std::string GetName();

    /**
     * @brief 获取文件大小(字节)
     * @return 文件大小(字节)
     */
    long long GetSize();

    /**
     * @brief 获取格式化后的文件大小字符串(如"1.23 MB")
     * @param precision 小数精度
     * @return 格式化后的文件大小字符串
     */
    std::string GetSizeFormatString(int precision);

    /**
     * @brief 获取文件大小(字节)，同GetSize()
     * @return 文件大小(字节)
     */
    long long GetLength();

    /**
     * @brief 获取父目录路径
     * @return 父目录路径
     */
    std::string GetParentDirPath();

    /**
     * @brief 获取所在目录路径
     * @return 目录路径
     */
    std::string GetDirectoryPath();

    /**
     * @brief 获取父目录信息对象
     * @return 父目录信息对象指针
     */
    DirectoryInfo* GetParentDir();

    /**
     * @brief 获取所在目录信息对象
     * @return 目录信息对象指针
     */
    DirectoryInfo* GetDirectory();

    /**
     * @brief 检查文件是否只读
     * @return 只读返回true，否则false
     */
    bool isReadOnly();

    /**
     * @brief 检查文件/目录是否存在
     * @return 存在返回true，否则false
     */
    bool Exists();

    /**
     * @brief 获取完整路径
     * @return 完整路径字符串
     */
    std::string GetFullPath();

    /**
     * @brief 复制文件到指定路径
     * @param destPath 目标路径
     * @param overwrite 是否覆盖已存在文件
     * @return 新文件信息对象指针
     */
    FileInfo* CopyTo(std::string destPath, bool overwrite);

    /**
     * @brief 移动文件到指定路径
     * @param destPath 目标路径
     * @param overwrite 是否覆盖已存在文件
     * @return 新文件信息对象指针
     */
    FileInfo* MoveTo(std::string destPath, bool overwrite);

    /**
     * @brief 删除文件
     * @return 删除成功返回true，否则false
     */
    bool Delete();

protected:
    std::ifstream file;          ///< 文件输入流
    std::streamsize fileSize;    ///< 文件大小
    std::string path;            ///< 文件路径
    bool isFile = true;          ///< 是否为文件标志

private:
    /**
     * @brief 获取文件大小(内部实现)
     * @param filepath 文件路径
     * @return 文件大小(字节)
     */
    long long GetFileSize(const std::string& filepath);

#ifdef _WIN32
    /**
     * @brief GB2312编码转UTF-8编码(Windows平台)
     * @param gb2312 GB2312编码字符串
     * @return UTF-8编码字符串
     */
    std::string GB2312ToUtf8(std::string& gb2312);

    /**
     * @brief UTF-8编码转宽字符串(Windows平台)
     * @param utf8 UTF-8编码字符串
     * @return 宽字符串
     */
    std::wstring UTF8ToWString(std::string& utf8);
#endif // _WIN32
};


