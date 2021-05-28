#include <iostream>
#include "calculator.h"
#include "salutator.h"

Calculator Calcolatrice();

int main() {
    std::cout << "Hello Lia!";
    int num1 = 5;
    int num2 = 12;
	Calculator c;
    std::cout << c.sum(num1, num2)<<std::endl;
    Salutator s;
    s.salute();
    return 0;
}
