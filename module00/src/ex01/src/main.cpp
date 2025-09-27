#include <iostream>
#include <vector>
#include <Contact.h>
#include <PhoneBook.h>

#define CMD_ADD      1
#define CMD_SREACH   2
#define CMD_EXIT     3

int main(void)
{
    std::string	input;
    Contact cont;
    PhoneBook pb;

    while(true){

        std::cout << "Please select the command: ADD(1) or SEARCH(2) or EXIT(3)";
        std::cin >> input;

        if(input.compare("add") == 0){
            pb.Add(cont);
        }
        else if(input.compare("search") == 0){

        }
        else if(input.compare("exit") == 0){
            break;
        }
        else{
            std::cout << "Invalid\n";
        }

    }



    return 0;
}