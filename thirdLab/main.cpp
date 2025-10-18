#include <iostream>
/*
Битовая операция — действие над отдельными битами целого числа
Работает побитно (над каждой парой битов)


логические работают с булевыми значениями
битовые с целыми - результат - целое

&  И  0011 & 0101 == 00
| ИЛИ
 ^(XOR)  0011 ^ 0101 - 0110
~  0011  - 1100
<< -  <<0011 0110
>> - >>0011  0001


| a | b | a & b | a | b | a ^ b |
| - | - | ----- | ----- | ----- |
| 0 | 0 | 0     | 0     | 0     |
| 0 | 1 | 0     | 1     | 1     |
| 1 | 0 | 0     | 1     | 1     |
| 1 | 1 | 1     | 1     | 0     |

сдвиг влево - умножение на 2 k раз 
0001 - 1 << 3 1000   - 1 * 2**3

сдвиг вправо деление на 2 
3 1000 >> 3 0001 - 1 

Битовая маска — это число, у которого важные для операции биты равны 1, а остальные 0
1 0000`0001 & 
Маска используется вместе с битовыми операциями (& | ^ ~) чтобы получать/изменять конкретные
биты в числе


		0b00000010
		char lamp_status = 0b0000'0000;
    int i = 5;
    std::cout << (lamp_status | (1<<i)) << std::endl;
    // 0b00000001 = 1
    // 0b00000010 = (1<<1)
    // 0b00000000 | 0b00000010
		// 0b00000010
*/


int main() {

	unsigned int x;
	unsigned int i;
	std::cout << "Введите x (0 < x < 10^9) и i (0..31):" << std::endl;
	std::cin >> x >> i;
	if (x >= 1000000000 || i > 31 ){
		std::cout << "некорректный ввод" << std::endl;
		return 0;
	} else {
		unsigned int ith = (x >> i) & 1u;
		std::cout << "i-й бит числа x = " << ith << std::endl;
	}

	// extra task

	unsigned int a;

	std::cout << "Введите a(0 < a < 10^9): ";
	std::cin >> a;

	unsigned int maxShift = 0;
	unsigned int maxVal = a;

	if (a >= 1000000000 ){
		std::cout << "неккоректный ввод числа" << std::endl;
	  return 0;
	} else {
		for (unsigned int k = 1; k<32; ++k){
			unsigned int left  = a << k;
			unsigned int right = a >> k;

			if (left > maxVal){
				maxVal = left;
				maxShift = k;
			}
			if (right > maxVal){
				maxVal = right;
				maxShift = k;
			}
		}
	}

	std::cout << "Максимальное значение: " << maxVal << std::endl;
  std::cout << "Получено при сдвиге на " << maxShift << " бит(а)" << std::endl;
	return 0;
}