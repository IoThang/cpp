#ifndef FIXED_H
#define FIXED_H

#include <cmath>
#include <iostream>

class Fixed{
    int itg_num_;
    static int const no_fractional_bits = 8;
public:
    Fixed();

    explicit Fixed(int const&);
    explicit Fixed(float const&);

    Fixed(Fixed const&);
    Fixed& operator = (Fixed const &);
    Fixed(Fixed&&) noexcept;
    Fixed& operator = (Fixed &&) noexcept;

    ~Fixed() noexcept;

    int getRawBits(void) const;
    void setRawBits(int const);

    float toFloat(void) const;
    int toInt(void) const;

    // Overload comparison operators
    bool operator > (Fixed const&);
    bool operator < (Fixed const&);
    bool operator == (Fixed const&);
    bool operator != (Fixed const&);

    // Overload arithmetic operators
    Fixed operator + (Fixed const&);
    Fixed operator - (Fixed const&);
    Fixed operator * (Fixed const&);
    Fixed operator / (Fixed const&);

    // Overload increment and decrement (pre/post++)
    Fixed operator ++ (void);   //++a
    Fixed operator -- (void);
    Fixed operator ++ (int);    //a++
    Fixed operator -- (int);

    // Function overloaded
    static Fixed& Min(Fixed&, Fixed&);
    static Fixed const& Min(Fixed const&, Fixed const&);
    static Fixed& Max(Fixed&, Fixed&);
    static Fixed const& Max(Fixed const&, Fixed const&);
};

std::ostream& operator<< (std::ostream& os, const Fixed& obj);

#endif