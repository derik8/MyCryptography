#include "lab5.h"

void NSlab5::lab5()
{
	int	option=1,p,q,n,E,D=0,s;
	const char *FName = "text\\lab5.txt";
	
	std::ifstream fin(FName);

	std::cout << "LAB5" << std::endl;
	std::cout << "encrypt file ------- decrypt file  (1/2):" << std::endl;
	//std::cin >> option;


	p=3;
	q=11;
	n = p * q;
	E = 7;

	while (true)
	{
		
		s = D * E;
		while (s>(p-1)*(q-1))
		{
			s -= (p - 1)*(q - 1);
		}
		if (s == 1)break;
		D++;

	}

	if (option == 1)
	{

		encrypt(n,D, fin, FName);
	}
	else
	{
		//decrypt(*KEY, fin, FName);
	}
	
}

//шифрування за допомогою приватного ключа та створення цифрового підпису
void NSlab5::encrypt(int n, int D, std::ifstream & fin, const char * FName)
{
	std::string  s= GetString(fin);
	int *message = new int[s.size()];

	//переводим текст в символи
	for (int i = 0; i < s.size(); i++)
	{

		message[i] = (int)s[i] - 97;
		std::cout << message[i] << " ";

	}

}
