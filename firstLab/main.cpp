#include <iostream>
#include <limits>


// переменная - именованная область памяти, хранит то что дадим
/*
типы данных:
1) целочисленные:
char (-128...127) 1 байт 
unsigned char (0...255) только положительные можно применять с short etc    
short (-32768...32767)   2 байта
int 4.147 млрд значений   4 байта 
long long 8 байт

2) символьные(принимают один символ):
char ex = 'a'; 1 байт

3) вещественные: 
float 6-7 значащих знаков  4 байта
double 15-16 значащих знаков  8байт
long double 16 байт

4) логический тип данных(передает true/false):
bool 1 байт


*/



int main(){

	std::cout << "char:" << " " <<  sizeof(char) << " " <<  (int)std::numeric_limits<char>::min() << " " << (int)std::numeric_limits<char>::max() << std::endl;
	std::cout << "unsigned char:" << " " <<  sizeof(unsigned char) << " " <<  (int)std::numeric_limits<unsigned char>::min() << " " << (int)std::numeric_limits<unsigned char>::max() << std::endl;
	std::cout << "short:" << " " <<  sizeof(short) << " " <<  std::numeric_limits<short>::min() << " " << std::numeric_limits<short>::max() << std::endl;	
	std::cout << "int:" << " " <<  sizeof(int) << " " <<  std::numeric_limits<int>::min() << " " << std::numeric_limits<int>::max() << std::endl;	
	std::cout << "long long:" << " " <<  sizeof(long long) << " " <<  std::numeric_limits<long long>::min() << " " << std::numeric_limits<long long>::max() << std::endl;	
	std::cout << "float:" << " " <<  sizeof(float) << " " <<  std::numeric_limits<float>::min() << " " << std::numeric_limits<float>::max() << std::endl;	
	std::cout << "double:" << " " <<  sizeof(double) << " " <<  std::numeric_limits<double>::min() << " " << std::numeric_limits<double>::max() << std::endl;	
	std::cout << "long double:" << " " <<  sizeof(long double) << " " <<  std::numeric_limits<long double>::min() << " " << std::numeric_limits<long double>::max() << std::endl;	
	std::cout << "bool:" << " " <<  sizeof(bool) << " " <<  std::numeric_limits<bool>::min() << " " << std::numeric_limits<bool>::max() << std::endl;	

	int a = 5, b=10;
	std::cout << a+b << std::endl;

	float f1 = 3.2, f2 = 3.14;
	std::cout << f1*f2 << std::endl;

	char n = 'N', m = 1;
	std::cout << char(n+m) << std::endl; // получает определенынй айди и выдает через кодировку utf-8 символ

	bool flag1 = true, flag2 = false;
	std::cout << (flag1||flag2) << std::endl;


	return 0;
}