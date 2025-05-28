# 文件与字符串工具库 (FileSystemUtils + StringUtils)

一个轻量级的C++工具库，提供面向对象的**文件系统操作**和**增强字符串处理**功能。

## 📦 功能特性

### 1. 文件系统工具
- **文件操作**  
  - 获取文件属性（大小、路径、只读状态等）
  - 文件复制/移动/删除
  - 文件存在性检查
  - 格式化文件大小显示

- **目录操作**  
  - 遍历子目录和文件
  - 获取父目录信息

### 2. 字符串工具（String类）
- 继承自 `std::string`，兼容标准库
- 支持Java风格字符串操作：
  - 子串提取 `substring()`
  - 大小写转换 `toLowerCase()/toUpperCase()`
  - 分割/替换/去空格 `split()/replace()/trim()`
  - 查找/匹配 `indexOf()/contains()`

### 3. 跨平台支持
- Windows自动处理GB2312/UTF-8编码
- 标准C++11实现

---

## 🛠 快速开始

### 字符串工具示例
```cpp
#include "String.h"

String str = "  Hello,World!  ";

// 去空格+转小写
String processed = str.trim().toLowerCase(); // "hello,world!"

// 分割字符串
auto parts = str.split(','); // ["Hello", "World!"]

// 替换操作
String newStr = str.replace("World", "C++"); // "Hello,C++!"
```

### 文件操作示例
```cpp
#include "FileInfo.h"

// 获取文件信息
FileInfo file("data.txt");
if (file.Exists()) {
    std::cout << "大小: " << file.GetSizeFormatString(2); // 例如 "4.50 KB"
}
```

---

## 📖 API参考（新增String类）

### String 类核心方法
| 方法 | 示例 | 描述 |
|------|------|------|
| `substring(begin, end)` | `"hello".substring(1,3)` → `"el"` | 提取子串 |
| `trim()` | `" abc ".trim()` → `"abc"` | 去除首尾空格 |
| `split(delimiter)` | `"a,b,c".split(',')` → `["a","b","c"]` | 按分隔符分割 |
| `replace(old, new)` | `"foo".replace("o","a")` → `"faa"` | 全局替换 |
| `toUpperCase()` | `"Hi".toUpperCase()` → `"HI"` | 转大写 |

### FileInfo 类（简略）
| 方法 | 描述 |
|------|------|
| `GetSize()` | 返回文件字节数 |
| `CopyTo()` | 复制文件 |

---

## 🌟 设计优势
1. **无缝兼容**  
   ```cpp
   String s = "标准字符串";
   std::string stdStr = s; // 自动转换
   ```
2. **链式调用**  
   ```cpp
   str.trim().toUpperCase().replace("A","B");
   ```
3. **线程安全**  
   所有方法返回新对象，原始数据不变
