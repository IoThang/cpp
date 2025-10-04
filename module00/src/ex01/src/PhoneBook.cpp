#include <iostream>
#include <PhoneBook.h>

void PhoneBook::getInput(Contact& cont_element)
{

    std::vector<std::string> inputs;
    std::string input;
    std::cout << "Enter inputs (press Ctrl+D/Ctrl+Z to finish): ";
    while (std::cin >> input) { // Reads until whitespace or EOF

        inputs.push_back(input);
    }

    std::cout << "You entered:\n";
    for (const auto& w : inputs) {
        std::cout << w << "\n";
    }

    cont_element.SET_firstName(inputs[0]);
    cont_element.SET_lastName(inputs[1]);
    cont_element.SET_nickName(inputs[2]);
    cont_element.SET_phoneNumber(inputs[3]);
    cont_element.SET_DarkestSecret(inputs[4]);
}


void PhoneBook::Add(Contact& cont_element)
{
    PhoneBook::getInput(cont_element);

    if(PhoneBook::contact_list_.size() < MAX_OF_CONTACTS)
    {
        PhoneBook::contact_list_.push_back(cont_element);
    }
    else{
        std::cout << "Can not add since the number of contacts is enough \n";
    }

}