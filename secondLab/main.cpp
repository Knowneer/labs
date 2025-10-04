#include <iostream>


int main(){
	int A; 
	int B;
	int C;

	std::cout << "Введите A,B,C - целые числа(стороны параллелепипеда) (0 < A,B,C < 10^4)" << std::endl;
	std::cin >> A >> B >> C;

	if (A < 0 || B<0 || C < 0 || A>10000 || B >10000|| C > 10000){
		std::cout << "Неверные входные данные" << std::endl;
		return 0;
	}



	long long V = A*B*C;
	std::cout << "Объем параллелепипеда: " << V << std::endl;
	
	return 0;
}