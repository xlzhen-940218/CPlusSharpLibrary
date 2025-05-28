#pragma once
#include <string>
#include <list>
/**
 * @brief 扩展自std::string的字符串类，提供更多便捷的字符串操作方法
 *
 * 该类继承自标准库std::string，并添加了类似Java字符串操作的常用方法，
 * 包括子串提取、大小写转换、查找替换、分割等常用功能。
 */
class String : public std::string
{
public:
    using std::string::string;  // 继承std::string的所有构造函数

    /**
     * @brief 获取指定索引位置的字符
     * @param index 字符位置索引
     * @return 返回指定位置的字符
     */
    char charAt(int index);

    /**
     * @brief 获取子字符串[begin, end)
     * @param begin 起始位置(包含)
     * @param end 结束位置(不包含)
     * @return 子字符串
     */
    std::string substring(int begin, int end);

    /**
     * @brief 从begin位置开始到字符串末尾的子串
     * @param begin 起始位置
     * @return 子字符串
     */
    std::string substring(int begin);

    /**
     * @brief 比较当前字符串与另一字符串是否相等
     * @param str 要比较的字符串
     * @return 相等返回true，否则false
     */
    bool equals(std::string& str);

    /**
     * @brief 连接当前字符串与另一字符串
     * @param str 要连接的字符串
     * @return 连接后的新字符串
     */
    std::string concat(std::string& str);

    /**
     * @brief 查找字符第一次出现的位置
     * @param c 要查找的字符
     * @return 字符位置索引，未找到返回-1
     */
    int indexOf(char c);

    /**
     * @brief 查找子串第一次出现的位置
     * @param str 要查找的子串
     * @return 子串起始位置索引，未找到返回-1
     */
    int indexOf(std::string& str);

    /**
     * @brief 查找字符最后一次出现的位置
     * @param c 要查找的字符
     * @return 字符位置索引，未找到返回-1
     */
    int lastIndexOf(char c);

    /**
     * @brief 查找子串最后一次出现的位置
     * @param str 要查找的子串
     * @return 子串起始位置索引，未找到返回-1
     */
    int lastIndexOf(std::string& str);

    /**
     * @brief 将字符串转换为小写
     * @return 新的小写字符串
     */
    std::string toLowerCase();

    /**
     * @brief 将字符串转换为大写
     * @return 新的大写字符串
     */
    std::string toUpperCase();

    /**
     * @brief 替换字符串中的所有指定字符
     * @param oldChar 要被替换的字符
     * @param newChar 替换后的字符
     * @return 替换后的新字符串
     */
    std::string replace(char oldChar, char newChar);

    /**
     * @brief 使用正则表达式替换第一个匹配的子串
     * @param regex 正则表达式
     * @param replacement 替换字符串
     * @return 替换后的新字符串
     */
    std::string replaceFirst(std::string& regex, std::string& replacement);

    /**
     * @brief 使用正则表达式替换所有匹配的子串
     * @param regex 正则表达式
     * @param replacement 替换字符串
     * @return 替换后的新字符串
     */
    std::string replaceAll(std::string& regex, std::string& replacement);

    /**
     * @brief 去除字符串首尾的空白字符
     * @return 去除空白后的新字符串
     */
    std::string trim();

    /**
     * @brief 检查字符串是否以指定子串开头
     * @param str 要检查的子串
     * @return 如果以该子串开头返回true，否则false
     */
    bool startsWith(std::string& str);

    /**
     * @brief 检查字符串是否以指定子串结尾
     * @param str 要检查的子串
     * @return 如果以该子串结尾返回true，否则false
     */
    bool endWith(std::string& str);

    /**
     * @brief 检查字符串是否包含指定子串
     * @param str 要查找的子串
     * @return 包含返回true，否则false
     */
    bool contains(std::string& str);

    /**
     * @brief 使用指定字符分割字符串
     * @param c 分隔符字符
     * @return 分割后的字符串列表
     */
    std::list<std::string> split(char c);

    /**
     * @brief 使用指定字符串分割字符串
     * @param str 分隔符字符串
     * @return 分割后的字符串列表
     */
    std::list<std::string> split(std::string str);
};

