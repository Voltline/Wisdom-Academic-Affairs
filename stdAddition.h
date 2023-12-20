#ifndef STDADDITION_H
#define STDADDITION_H
#include <QString>
#include <unordered_map>
#include <QHash> // 包含 Qt 的 QHash

// 定义 std 命名空间内的哈希函数特化
namespace std
{
    template <>
    struct hash<QString>
    {
        std::size_t operator()(const QString &s) const noexcept
        {
            return qHash(s); // 使用 Qt 的 qHash 函数
        }
    };
}
#endif // STDADDITION_H
