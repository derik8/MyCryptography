#include "lab3.h"

void NSlab3::lab3()
{
	int	option;
	const char *FName = "text\\lab3.txt";
	int KEY[3];
	std::ifstream fin(FName);

	std::cout << "LAB3" << std::endl;
	std::cout << "encrypt file-1 ------- decrypt file-2" << std::endl;
	std::cin >> option;

	std::cout << "Enter KEY:" << std::endl;

	for (int i = 0; i < sizeof(KEY) / sizeof(*KEY); i++)
		std::cin >> KEY[i];

	

	if (option == 1)
	{

		encrypt(*KEY, fin, FName);
	}
	else
	{
		decrypt(*KEY,fin, FName);
	}
	

}

//███ █  █ ████ ████ ██ ██ ████ ███
//█   ██ █ █  █ █  █  ███  █  █  █
//███ █ ██ █    ████   █   ████  █
//█   █  █ █  █ █ █    █   █     █
//███ █  █ ████ █ █    █   █     █

int NSlab3::encrypt(int &KEY, std::ifstream & fin, const char * FName)
{
	

	std::string s = GetString(fin);
	int *message = new int[s.size()];
	
	int m = 26,size_gama=0;
	std::cout << std::endl;
	
	
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i]!=' ')
		{
			size_gama++;
		}
	}

	int *Y = new int[size_gama+1];

	std::cout << std::endl;
	//перевід текста в символи
	for (int i = 0; i < s.size(); i++)
	{
		
			message[i] = (int)s[i] - 97;
			std::cout << message[i] << " ";
		
	}

	std::cout << std::endl;

	//створенння гамми
	/*for (int i = 0; i < 3; i++)
	{

		Y[i] = *(&KEY + i);
		std::cout << Y[i] << " ";
	}
	for (int i = 3; i < (size_gama+1); i++)
	{
		Y[i] = Y[i - 1] + Y[i - 3];
		
		while (Y[i]>=m)
		{
			Y[i] -= m;
		}

		std::cout << Y[i] << " ";
	}

	std::cout << std::endl;

	for (int i = 0; i < size_gama; i++)
	{
		Y[i] = Y[i] + Y[i + 1];
		while (Y[i] >= m)
		{
			Y[i] -= m;
		}
		std::cout <<Y[i]<<" ";

	}*/
	*Y = CreateGama(KEY,*Y, size_gama,m);
	

	std::cout << std::endl;
	//gama+message
	for (int i = 0,j=0; i < s.size(); i++,j++)
	{
		if (message[i] == -65)
		{
			j--;
			continue;
		}
		message[i] = message[i] + Y[j];

		while (message[i] >= m)
		{
			message[i] -= m;
		}

		std::cout << message[i] << " ";
	}


	std::cout << std::endl;
	//перевід символів у текст
	for (int i = 0; i < s.size(); i++)
	{

		s[i] = (char)(message[i] + 97);
		std::cout << s[i] << " ";

	}
	std::cout << std::endl;

	fin.close();
	

	std::ofstream fof(FName);
	for (int i = 0; i < s.size(); i++)
		fof << s[i];
	fof.close();
	delete []message;
	delete[]Y;
	return 0;
}

//████  ███ ████ ████ ██ ██ ████ ███
//█  ██ █   █  █ █  █  ███  █  █  █
//█  ██ ███ █    ████   █   ████  █
//█  ██ █   █  █ █ █    █   █     █
//████  ███ ████ █ █    █   █     █

int NSlab3::decrypt(int &KEY, std::ifstream & fin, const char * FName)
{
	std::string s = GetString(fin);
	int *message = new int[s.size()];
	int m = 26, size_gama = 0;
	std::cout << std::endl;


	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			size_gama++;
		}
	}

	int *Y = new int[size_gama + 1];

	for (int i = 0; i < s.size(); i++)
	{

		message[i] = (int)s[i] - 97;
		std::cout << message[i] << " ";

	}

	*Y = CreateGama(KEY, *Y, size_gama, m);
	std::cout << std::endl;
	//ti= C^-1(s(i)+(33-ki)) mod 33
	for (int i = 0, j = 0; i < s.size(); i++, j++)
	{
		if (message[i] == -65)
		{
			j--;
			continue;
		}
		message[i] = message[i] +(26-Y[j]);

		while (message[i] >= m)
		{
			message[i] -= m;
		}

		
	}

	for (int i = 0; i < s.size(); i++)
	{

		s[i] = (char)(message[i] + 97);
		std::cout << s[i] << " ";

	}

	fin.close();
	std::ofstream fof(FName);
	for (int i = 0; i < s.size(); i++)
		fof << s[i];
	std::cout << std::endl;

	fof.close();
	delete[]message;
	delete[]Y;
	return 0;
}

int & NSlab3::CreateGama(int &KEY, int &Y, int size_gama, int m)
{
	//додаємо в масив ключ
	for (int i = 0; i < 3; i++)
	{

		*(&Y + i) = *(&KEY + i);
		

	}
	//Y(i)=Y(i-1)+Y(i-3)
	for (int i = 3; i < (size_gama + 1); i++)
	{
		*(&Y + i) = *(&Y + i - 1) + *(&Y + i - 3);

		while (*(&Y + i) >= m)
		{
			*(&Y + i) -= m;
		}

		std::cout << *(&Y + i) << " ";
	}

	std::cout << std::endl;
	//Y(i)=Y(i)+Y(i+1)
	for (int i = 0; i < size_gama; i++)
	{
		*(&Y + i) = *(&Y + i) + *(&Y + i + 1);
		while (*(&Y + i) >= m)
		{
			*(&Y + i) -= m;
		}
		std::cout << *(&Y + i) << " ";

	}
	return Y;
}