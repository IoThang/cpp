//
// Created by TUO8HC on 9/28/2025.
//

#include <iostream>
#include <string>
#include <vector>
#define ON 1
#define OFF 0
#define ISMUTLTITHREAD ON




#if (ISMUTLTITHREAD == ON)
#include <thread>



int main() {

}

#else
int main() {
    const std::vector <std::string> name{"Thang", "Tan", "Nam"};
    int count = 1;
    while (count <= 50) {
        for (auto const &str : name) {
            int check = 0;
            std::cout << str << ": ";
            if (count % 3 == 0) {
                std::cout << "Fizz";
                check = 1;
            }
            if (count % 5 == 0) {
                std::cout << "Buzz";
                check = 1;
            }
            if (!check) {
                std::cout << count;
            }
            std::cout << std::endl;
            count++;
        }
    }
}
#endif