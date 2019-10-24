#include"lab2.h"

void NSlab2::lab2()
{
	int a, b, m = 26;
	float nck;
	int	option = 2;
	const char *FName = "text\\lab2.txt";
	std::ifstream fin(FName);



	std::cout << "LAB2\n" << std::endl;
	std::cout << "encrypt file-1 ------- decrypt file-2" << std::endl;
	std::cin >> option;

	if (option == 1)
	{
		while (true)
		{

			std::cout << "\nenter a  (0<a)  :  ";
			std::cin >> a;
			for (int i = a; i > 0; i--) {
				if (a % i == 0 && m % i == 0) {
					std::cout << "\nnod = " << i;
					nck = i;
					break;
				}
			}

			if (nck == 1)
				break;
		}

		std::cout << "\nenter b  (b<26)  :  ";
		std::cin >> b;

		std::ofstream fofB("text\\lab2B.txt");
		fofB << a;
		fofB << ' ';
		fofB << b;
		fofB.close();

		encrypt(a, b, m, fin, FName);

	}
	else
	{
		
		std::ifstream finB("text\\lab2B.txt");
		decrypt(m,fin, finB, FName);
	}
	
}


void NSlab2::encrypt(int a,int b,int m, std::ifstream & fin, const char * FName)
{
	int t;

	std::string s=GetString(fin);
	std::cout << std::endl;
	

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			t=(int)(s[i]) - 97;
			int y = (a * t + b);
			if ((a * t + b) >= m)
			{
				y = (a * t + b) - m;
				while (true)
				{
					if (y >= m)
						y-=m;
					else
						break;
				}

				s[i] = (char)(97+y);
			}
			else
			{
				s[i]=(char)(97+(a * t + b));
			}

		}

	}

	
	for (int i = 0; i < s.size(); i++)
	{
		std::cout << s[i];
	}
	std::cout << std::endl;

	fin.close();
	std::ofstream fof(FName);
	for (int i = 0; i < s.size(); i++)
		fof << s[i];
	fof.close();
}

void NSlab2::decrypt(int &m,std::ifstream & fin, std::ifstream & finB, const char * FName)
{
	char buff[6];
	int b, k = 0,t,a;
	float not_a;
	std::string s = GetString(fin);

	finB.getline(buff,4);
	finB.close();

	a = atoi(buff);
	buff[0] = ' ';
	buff[1] = ' ';
	b= atoi(buff);

	do
	{
		not_a = (float)(1 + k * m) / (float)a;
		k++;
	} while (floor(not_a + 0.5) != not_a);

	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] != ' ')
		{
			if ((int)s[i]-97 >= b)
			{
				t = (not_a * ((int)s[i] - 97 - b));
				while (t > m)
					t =t- m;
				s[i] = t + 97;
			}
			else
			{
				t=not_a * ((int)s[i] - 97 - b);
				while (t <0)
					t = t + m;
				s[i] =t+ 97;
			}



			
		}
	}
	
	std::cout <<"\n"<< std::endl;
	for (int i = 0; i < s.size(); i++)
	{
		std::cout << s[i];
	}
	std::cout << std::endl;

	std::ofstream fof(FName);
	for (int i = 0; i < s.size(); i++)
		fof << s[i];
	fof.close();
}
