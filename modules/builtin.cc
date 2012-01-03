#include <iostream>
#include <string>
#include <sstream>

class string;

class object {
    public:
        object() {}
        virtual ~object() {}

        virtual string str() const;
};

class string : public object {
    public:
        string(const char *value="") : _value(value) {};
        string(const string& s) : _value(s._value) {}
        string(const std::string& s) : _value(s) {}
        virtual ~string() {}

        const string& operator=(const string& s) { _value = s._value; return *this; }
        operator const char *() { return _value.c_str(); }

        const char *data() const { return _value.c_str(); }

        string str() const;

    private:
        std::string _value;

        friend string operator+(const string& a, const string& b);
};

string
operator+(const string& a, const string& b)
{
    return string(a._value + b._value);
}

string
object::str() const
{
    return string("<object>");
}

string
string::str() const
{
    return *this;
}

template <class T>
class integer : public object {
    public:
        integer<T>(T value=0) : _value(value) {}
        virtual ~integer<T>() {}

        string str() const {
            std::stringstream ss;
            ss << _value;
            return string(ss.str().c_str());
        }

        operator int() const { return (int)_value; }
        operator long() const { return (long)_value; }
        operator char() const { return (char)_value; }
        operator long long() const { return (long long)_value; }

    private:
        T _value;
};

typedef integer<char> int8;
typedef integer<short> int16;
typedef integer<int> int32;
typedef integer<long long> int64;
typedef integer<unsigned char> uint8;
typedef integer<unsigned short> uint16;
typedef integer<unsigned int> uint32;
typedef integer<unsigned long long> uint64;

class pointer : public object {
    public:
        pointer(void *value) : _value(value) {}

        string str() const {
            return "<pointer>";
        }

        void *data() const { return _value; };

    private:
        void *_value;
};

