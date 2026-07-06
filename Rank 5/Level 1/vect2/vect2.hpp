#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
private:
    int x;
    int y;

public:
    vect2();
    vect2(int num1, int num2);
    vect2(const vect2& source);
    vect2& operator=(const vect2& source);

    int operator[](int index) const;
    int& operator[](int index); // NON-CONST

    vect2 operator-() const;
    
    // Scalar multiplication
    vect2 operator*(int num) const;
    vect2& operator*=(int num);

    // Vector addition / subtraction
    vect2& operator+=(const vect2& obj);
    vect2& operator-=(const vect2& obj);
    vect2 operator+(const vect2& obj) const;
    vect2 operator-(const vect2& obj) const;

    // Increment / Decrement
    vect2& operator++();    // Pre
    vect2 operator++(int);  // Post
    vect2& operator--();    // Pre
    vect2 operator--(int);  // Post

    // Comparison
    bool operator==(const vect2& obj) const;
    bool operator!=(const vect2& obj) const;

    ~vect2();
};

// Left-hand scalar multiplication (e.g., 3 * v)
vect2 operator*(int num, const vect2& obj);

// Stream output
std::ostream& operator<<(std::ostream& os, const vect2& obj);

#endif