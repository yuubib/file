#include <iostream>
#include <string.h>
class String
{
public:
    String(const char *str)
    {
        std::cout << "Create" << std::endl;
        len = strlen(str) + 1;
        data = new char[len];
        memcpy(data, str, len);
        data[len - 1] = '\0';
    }
    String(const String &other)
    {
        std::cout << "Copy" << std::endl;
        len = other.len;
        data = new char[len];
        memcpy(data, other.data, len);
    }
    String(String &&other)
    {
        std::cout << "Move" << std::endl;
        len = other.len;
        data = other.data;

        other.len = 0;
        other.data = nullptr;
    }

    String &operator=(String &other) noexcept
    {
        if (this != &other)
        {
            std::cout << "=" << std::endl;
            delete[] data;
            len = other.len;
            data = new char[len];
            memcpy(data, other.data, len);
        }
        return *this;
        /*
        String copy(other);
        copy.swap(*this);
        return *this;
        */
    }
    String &operator=(String &&other) noexcept
    {
        if (this != &other)
        {
            std::cout << "=" << std::endl;
            delete[] data;
            len = other.len;
            data = other.data;

            other.len = 0;
            other.data = nullptr;
        }
        return *this;
        /*
        String copy(std::move(other));
        copy.swap(*this);
        return *this;
        */
    }
    char operator[](uint32_t i)
    {
        return data[i];
    }
    ~String()
    {
        printf("delete: %s\n", data);
        delete[] data;
    }

private:
    uint32_t len;
    char *data;
};

class Entity
{
public:
    Entity(const String &x) : m_x(x)
    {
    }
    Entity(const String &&x) : m_x(std::move(x))
    {
    }

private:
    String m_x;
};

class StringPtr
{
public:
    String *ptr;
    StringPtr(String *p) : ptr(p)
    {
        std::cout << "create ptr" << std::endl;
    }
    ~StringPtr()
    {
        delete ptr;
        std::cout << "delete ptr" << std::endl;
    }
};

void f()
{
    try
    {
        StringPtr(new String("123"));
        throw std::runtime_error("example");
        std::cout << "in" << std::endl;
    }
    catch (const std::exception &ex)
    {
        std::cout << "Caught" << std::endl;
    }
    std::cout << "out" << std::endl;
}
int main()
{
    String str("123");
}