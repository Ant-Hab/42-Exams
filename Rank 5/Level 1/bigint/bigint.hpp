#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>

class bigint {
private:
    std::string str;
    void trim(); // Helper to remove leading zeros

public:
    // Constructors
    bigint();
    bigint(unsigned int num);
    bigint(const bigint& source);

    // Assignment
    bigint& operator=(const bigint& source);

    // Addition
    bigint operator+(const bigint& other) const;
    bigint& operator+=(const bigint& other);

    // Increment
    bigint& operator++();   // Prefix
    bigint operator++(int); // Postfix

    // Shift Operations (unsigned int)
    bigint operator<<(unsigned int n) const;
    bigint operator>>(unsigned int n) const;
    bigint& operator<<=(unsigned int n);
    bigint& operator>>=(unsigned int n);

    // Shift Operations (bigint)
    bigint operator<<(const bigint& other) const;
    bigint operator>>(const bigint& other) const;
    bigint& operator<<=(const bigint& other);
    bigint& operator>>=(const bigint& other);

    // Comparison Operators
    bool operator==(const bigint& other) const;
    bool operator!=(const bigint& other) const;
    bool operator<(const bigint& other) const;
    bool operator>(const bigint& other) const;
    bool operator<=(const bigint& other) const;
    bool operator>=(const bigint& other) const;

    // Output Stream
    friend std::ostream& operator<<(std::ostream& output, const bigint& obj);
};

#endif