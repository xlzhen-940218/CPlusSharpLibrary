#pragma once

#include "FileInfo.h"
#include <vector>

/**
 * @brief 目录信息类，继承自FileInfo
 *
 * 该类扩展了目录相关操作，如获取子文件和子目录列表等。
 */
class DirectoryInfo : public FileInfo
{
public:
    using FileInfo::FileInfo;  ///< 继承FileInfo的构造函数

    /**
     * @brief 获取目录下的所有文件
     * @return 文件信息对象指针数组
     */
    std::vector<FileInfo*> GetFiles();

    /**
     * @brief 获取目录下的所有子目录
     * @return 目录信息对象指针数组
     */
    std::vector<DirectoryInfo*> GetDirectories();

private:
    /**
     * @brief 列出目录内容(内部使用)
     */
    void ListDirectory();

    std::vector<std::pair<bool, std::string>> entries;  ///< 目录条目列表(pair中bool表示是否为文件)
};

