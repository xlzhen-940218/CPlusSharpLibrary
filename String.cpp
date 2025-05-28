#include "String.h"
#include <algorithm> // 用于 std::max 和 std::min
#include <regex>
#include <sstream>

char String::charAt(int index)
{
	if (index < 0 || index > length()) {
		return -1;
	}
	return at(index);
}

std::string String::substring(int begin, int end)
{
    int len = length();

    begin = std::max(0, begin);    
    begin = std::min(begin, len);   

    end = std::max(0, end);     
    end = std::min(end, len);    

    if (begin >= end) {
        return std::string();
    }

    return std::string(data() + begin, end - begin);
}

std::string String::substring(int begin)
{
	return substring(begin,length());
}

bool String::equals(std::string& str)
{
    if (str.empty()) {
        return false;
    }
    return (*this) == (str);
}

std::string String::concat(std::string& str)
{
    return (*this) + str;
}

int String::indexOf(char c)
{
    // 直接调用 std::string 的 find 方法
    size_t pos = this->find(c);

    // 如果未找到 (pos == std::string::npos)，返回 -1
    // 否则返回位置（转换为 int）
    return (pos == std::string::npos) ? -1 : static_cast<int>(pos);
}

int String::indexOf(std::string& str)
{
    // 处理空子字符串
    if (str.empty()) {
        return 0; // 空字符串视为在位置 0 匹配
    }

    // 调用 std::string 的 find 方法
    size_t pos = this->find(str);

    // 检查是否找到
    return (pos == std::string::npos) ? -1 : static_cast<int>(pos);
}

int String::lastIndexOf(char c)
{
    // 调用 std::string 的 rfind 方法从末尾反向查找
    size_t pos = this->rfind(c);

    // 处理未找到的情况
    return (pos == std::string::npos) ? -1 : static_cast<int>(pos);
}

int String::lastIndexOf(std::string& str)
{
    // 处理空子字符串的特殊情况
    if (str.empty()) {
        return this->length(); // 空字符串约定返回字符串长度（如Java行为）
    }

    // 调用 std::string 的 rfind 方法
    size_t pos = this->rfind(str);

    // 检查是否找到
    return (pos == std::string::npos) ? -1 : static_cast<int>(pos);
}

std::string String::toLowerCase()
{
    std::string result = *this; // 创建副本
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::tolower(c); }); // 逐字符转小写
    return result;
}

std::string String::toUpperCase()
{
    std::string result = *this; // 创建副本
    std::transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return std::toupper(c); }); // 逐字符转大写
    return result;
}

std::string String::replace(char oldChar, char newChar)
{
    std::string result = *this; // 复制当前字符串
    for (char& c : result) {    // 遍历每个字符
        if (c == oldChar) {
            c = newChar;       // 替换匹配的字符
        }
    }
    return result;
}


std::string String::replaceFirst(std::string& regex, std::string& replacement)
{
    try {
        std::regex re(regex); // 编译正则表达式
        // 替换第一个匹配项
        return std::regex_replace(
            *this,
            re,
            replacement,
            std::regex_constants::format_first_only
        );
    }
    catch (const std::regex_error& e) {
        // 正则表达式无效时返回原字符串
        return *this;
    }
}



std::string String::replaceAll(std::string& regex, std::string& replacement)
{
    try {
        std::regex re(regex); // 编译正则表达式
        // 替换所有匹配项
        return std::regex_replace(*this, re, replacement);
    }
    catch (const std::regex_error& e) {
        // 正则表达式无效时返回原字符串
        return *this;
    }
}

std::string String::trim()
{
    auto start = this->begin();
    while (start != this->end() && std::isspace(*start)) {
        start++;
    }

    auto end = this->end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

bool String::startsWith(std::string& str)
{
    if (str.length() > this->length()) return false;
    return std::equal(str.begin(), str.end(), this->begin());
}

bool String::endWith(std::string& str)
{
    if (str.length() > this->length()) return false;
    return std::equal(str.rbegin(), str.rend(), this->rbegin());
}

bool String::contains(std::string& str)
{
    return this->find(str) != std::string::npos;
}

std::list<std::string> String::split(char delimiter) {
    std::list<std::string> result;
    std::stringstream ss(*this);
    std::string item;

    while (std::getline(ss, item, delimiter)) {
        result.push_back(item);
    }

    return result;
}

std::list<std::string> String::split(std::string delimiter) {
    std::list<std::string> result;
    size_t pos = 0;
    size_t prev = 0;

    while ((pos = this->find(delimiter, prev)) != std::string::npos) {
        result.push_back(this->substr(prev, pos - prev));
        prev = pos + delimiter.length();
    }

    // 添加最后一段
    result.push_back(this->substr(prev));
    return result;
}
