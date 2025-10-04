#include <Contact.h>

void Contact::SET_firstName(const std::string& firstName)
{
    Contact::firstName_ = firstName;
}
void Contact::SET_lastName(const std::string& lastName)
{
    Contact::lastName_ = lastName;
}
void Contact::SET_nickName(const std::string& nickName)
{
    Contact::nickName_ = nickName;
}
void Contact::SET_phoneNumber(const std::string& phoneNumber)
{
    Contact::phoneNumber_ = phoneNumber;
}
void Contact::SET_DarkestSecret(const std::string& DarkestSecret)
{
    Contact::darkestSecret_ = DarkestSecret;
}

std::string Contact::GET_firstName(void) const
{
    return Contact::firstName_;
}
std::string Contact::GET_lastName(void) const
{
    return Contact::lastName_;
}
std::string Contact::GET_nickName(void) const
{
    return Contact::nickName_;
}
std::string Contact::GET_phoneNumber(void) const
{
    return Contact::phoneNumber_;
}
std::string Contact::GET_DarkestSecret(void) const
{
    return Contact::darkestSecret_;
}