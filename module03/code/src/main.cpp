#include <ClapTrap.h>
#include <ScavTrap.h>
#include <FragTrap.h>

void logger(ClapTrap);

int main(void)
{
    ClapTrap thang("Thang");
    ClapTrap thang_2 = thang;

    ScavTrap nam("Nam");
    ScavTrap nam_2(nam);

    FragTrap tan("Tan");
    FragTrap tan_2 = tan;

    thang.SetAttackDamage(1);

    thang.attack(tan); // 9
    tan.attack(nam);
    nam.attack(thang);


    thang.TakeDamage(200); 
    tan.TakeDamage(6);
    nam.TakeDamage(50);

    thang.BeRepaired(10);
    tan.BeRepaired(100);
    nam.BeRepaired(1000);

    return 0;
}

// void logger(ClapTrap a){
//     std::cout << "\t\t\t LOGGER\n";
//     std::cout << "name: " << a.GetName() << "\n";
//     std::cout << "hit point: " << a.GetHitPoints() << "\n";
//     std::cout << "energy point: " << a.GetEnergyPoints() << "\n";
//     std::cout << "State: " << a.getState() << "\n";
// }