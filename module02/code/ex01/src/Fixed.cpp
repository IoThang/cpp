#include <Fixed.h>


Fixed::Fixed() : itg_num_(0) {
    std::cout << "Default constructor called\n";
}

Fixed::Fixed(int const& value){
    this->itg_num_ = value << no_fractional_bits;
    std::cout << "Int constructor called\n";
}

Fixed::Fixed(float const& value){
    this->itg_num_ =(float) roundf(value *(1 << no_fractional_bits));
    std::cout << "Float constructor called\n";
}

Fixed::Fixed(Fixed const& other) : itg_num_(other.itg_num_) {
    std:: cout << "Copy constructor called\n";

}

Fixed& Fixed::operator = (Fixed const& other)
{
    this->itg_num_ = other.itg_num_;
    std:: cout << "Copy assignment called\n";
    return *this;
}


Fixed::Fixed(Fixed&& other) noexcept {
    this->itg_num_ = other.itg_num_;
    other.itg_num_ = 0;
    std:: cout << "Move constructor called\n";
} 

Fixed::~Fixed() {
    std::cout << "Default deconstructor called\n";
}

int Fixed::getRawBits(void) const{
    return itg_num_;
}

void Fixed::setRawBits(int const raw){
    this->itg_num_ = raw;
}

float Fixed::toFloat(void) const{
    return itg_num_ / (float)(1 << no_fractional_bits);
}
int Fixed::toInt(void) const{
    return itg_num_ >> no_fractional_bits;
}

// Overload comparison operators
bool Fixed::operator > (Fixed const& obj){
    return this->itg_num_ > obj.itg_num_;
}

bool Fixed::operator < (Fixed const& obj){
    return this->itg_num_ < obj.itg_num_;
}

bool Fixed::operator == (Fixed const& obj){
    return this->itg_num_ == obj.itg_num_;
}

bool Fixed::operator != (Fixed const& obj){
    return this->itg_num_ != obj.itg_num_;
}

// Overload arithmetic operators
Fixed Fixed::operator + (Fixed const& obj){
    return Fixed(this->toFloat() + obj.toFloat());
}
Fixed Fixed::operator - (Fixed const& obj){
    return Fixed(this->toFloat() - obj.toFloat());
}
Fixed Fixed::operator * (Fixed const& obj){
    return Fixed(this->toFloat() * obj.toFloat());
}
Fixed Fixed::operator / (Fixed const& obj){
    return Fixed(this->toFloat() / obj.toFloat());
}

// Overload increment and decrement (pre/post++)
Fixed Fixed::operator++ ()
{
	Fixed rt;
	itg_num_++;
	rt.itg_num_ = itg_num_;
	return (rt);
}

Fixed Fixed::operator++ (int)
{
	Fixed rt;
	rt.itg_num_ = itg_num_++;
	return (rt);
}

Fixed& Fixed::Min(Fixed& a, Fixed&b){
    return a.itg_num_ > b.itg_num_ ? b : a;
}

Fixed const& Fixed::Min(Fixed const& a, Fixed const& b){
    return a.itg_num_ > b.itg_num_ ? b : a;
}

Fixed& Fixed::Max(Fixed& a, Fixed&b){
    return a.itg_num_ > b.itg_num_ ? a : b;
}

Fixed const& Fixed::Max(Fixed const& a, Fixed const& b){
    return a.itg_num_ > b.itg_num_ ? a : b;
}


std::ostream& operator<< (std::ostream& os, const Fixed& obj){
    return os << obj.toFloat();
    // return os;
};