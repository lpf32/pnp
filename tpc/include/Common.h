#ifndef PNP_COMMON_H
#define PNP_COMMON_H

#include <string>

class noncopyable
{
protected:
    noncopyable() {}

private:
    noncopyable(const noncopyable&) = delete;
    void operator=(const noncopyable&) = delete;
};

struct copyable
{

};

class StringArg : copyable
{
public:
    StringArg(const char* str)
        : str_(str)
    { }

    StringArg(const std::string& str)
        : str_(str.c_str())
    { }

    const char* c_str() const { return str_; }

private:
    const char* str_;
};

template <typename To, typename From>
inline To implicit_cast(From f)
{
    return f;
};

template <typename T>
void UNUSED(const T& t)
{ }

#endif //PNP_COMMON_H
