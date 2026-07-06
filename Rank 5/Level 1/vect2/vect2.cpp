#include "vect2.hpp"

// Using member initializer lists
vect2::vect2() : x(0), y(0) {}

vect2::vect2(int num1, int num2) : x(num1), y(num2) {}

vect2::vect2(const vect2& source) : x(source.x), y(source.y) {}

vect2& vect2::operator=(const vect2& source)
{
    if(this != &source)
    {
        this->x = source.x;
        this->y = source.y;
    }
    return *this;
}

int vect2::operator[](int index) const
{
    if(index == 0)
        return this->x;
    return this->y;
}

int& vect2::operator[](int index)
{
    if(index == 0)
        return this->x;
    return this->y;
}

vect2 vect2::operator-() const
{
    return vect2(-x, -y);
}

vect2 vect2::operator*(int num) const
{
    return vect2(this->x * num, this->y * num);
}

vect2& vect2::operator*=(int num)
{
    this->x *= num;
    this->y *= num;
    return *this;
}

vect2& vect2::operator+=(const vect2& obj)
{
    this->x += obj.x;
    this->y += obj.y;
    return *this;
}

vect2& vect2::operator-=(const vect2& obj)
{
    this->x -= obj.x;
    this->y -= obj.y;
    return *this;
}

vect2 vect2::operator+(const vect2& obj) const
{
    return vect2(this->x + obj.x, this->y + obj.y);
}

vect2 vect2::operator-(const vect2& obj) const
{
    return vect2(this->x - obj.x, this->y - obj.y);
}

vect2& vect2::operator++()
{
    this->x += 1;
    this->y += 1;
    return *this;
}

vect2 vect2::operator++(int)
{
    vect2 temp = *this;
    ++(*this);
    return temp;
}

vect2& vect2::operator--()
{
    this->x -= 1;
    this->y -= 1;
    return *this;
}

vect2 vect2::operator--(int)
{
    vect2 temp = *this;
    --(*this);
    return temp;
}

bool vect2::operator==(const vect2& obj) const
{
    return (this->x == obj.x) && (this->y == obj.y);
}

bool vect2::operator!=(const vect2& obj) const
{
    return !(*this == obj);
}

vect2::~vect2()
{
}

// BUG FIXED: Now uses 'os' instead of 'std::cout'
std::ostream& operator<<(std::ostream& os, const vect2& obj)
{
    os << "{" << obj[0] << ", " << obj[1] << "}";
    return os;
}

vect2 operator*(int num, const vect2& obj)
{
    return obj * num;
}