#include "lab1.h"

void NSlab1::lab1()
{
	int key;
	int	option;
	const char *FName = "text\\lab1.txt";
	std::ifstream fin(FName);

	std::cout << "LAB1"<< std::endl;
	std::cout << "encrypt file-1 ------- decrypt file-2" << std::endl;
	std::cin >> option;

	if (option == 1)
	{
		std::cout << "enter key:  ";
		std::cin >> key;
		encrypt(key, fin,FName);
	}
	else
		decrypt(fin, FName);
	
}



int NSlab1::encrypt(int key, std::ifstream &fin,const char *FName)
{
	char ch1;
	std::string s;

	GetString(fin);

	fin.clear();
	std::cout << std::endl;
	fin.seekg(0);

	while ((ch1 = fin.get()) != EOF) //output text
	{
		if (ch1 == ' ')
		{
			std::cout << " ";
			s += " ";
		}
		else
			if ((int)ch1 + key >= 122)
			{
				std::cout << (char)(((int)ch1 + key - 122) + 97);
				s += (char)(((int)ch1 + key - 122) + 97);
			}
			else
			{
				std::cout << (char)((int)ch1 + key);
				s+= (char)((int)ch1 + key);
			}
		
	}

	std::cout << std::endl;
	
	fin.close();
	std::ofstream fof(FName);
	for(int i=0;i<s.size();i++)
	fof << s[i];
	fof.close();

	return 0;
}

int NSlab1::decrypt(std::ifstream &fin, const char *FName)
{
	std::string line = GetString(fin);
	std::string line2 = line;
	std::map<float, char> ALF =   {{0.127  ,'e'},
	                          {0.0906  ,'t'},
	                          {0.0817  ,'a'},
	                          {0.0751  ,'o'},
	                          {0.0697  ,'i'},
	                          {0.0675  ,'n'},
	                          {0.0633  ,'s'},
	                          {0.0609  ,'h'},
	                          {0.0599  ,'r'},
	                          {0.0425  ,'d'},
	                          {0.0403  ,'l'},
	                          {0.0278  ,'c'},
	                          {0.0276  ,'u'},
	                          {0.0241  ,'m'},
	                          {0.0236  ,'w'},
	                          {0.0223  ,'f'},
	                          {0.0202  ,'g'},
	                          {0.0197  ,'y'},
	                          {0.0193  ,'p'},
	                          {0.0149  ,'b'},
	                          {0.0098  ,'v'},
	                          {0.0077  ,'k'},
	                          {0.0015  ,'x'},
	                          {0.0015  ,'j'},
	                          {0.001   ,'q'},
	                          {0.0005  ,'z'}
	};

	std::multimap<float, char> MyMap;
	float  count = 0, frequance(0);
	int y,option= -1;

	for (int i = 0; i < line.size(); i++)
		if (line[i] != ' ')
			count++;
	
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != ' ')
		{
			for (int j = i; j < line.size(); j++)
			{
				if (line[i] == line[j])
				{
					if (frequance != 0)
						line[j] = ' ';
					frequance++;

				}
			}
			
			MyMap.insert(std::pair<float, char>(frequance / count, line[i]));
			frequance = 0;
		}
	}

	auto a = MyMap.rbegin(), b = ALF.rbegin();

	std::string line3;
	while (true) {		

		y = (int)(b->second) - (int)(a->second);
		std::cout << std::endl << y << std::endl;
		for (int i = 0; i < line2.size(); i++)
		{
			if (line2[i] == ' ')
			{
				std::cout << " ";
				line3 += " ";
			}
			else
				if ((int)line2[i] + y >= 122)
				{
					
					std::cout << (char)(((int)line2[i] + y - 122) + 97);
					line3 += (char)(((int)line2[i] + y - 122) + 97);

				}
				else
				{
					if ((int)line2[i] + y >= 97)
					{
						std::cout << (char)((int)line2[i] + y);
						line3 += (char)((int)line2[i] + y);
					}
					else
					{

						std::cout << (char)(122 - (97 - ((int)line2[i] + y)));
						line3 += (char)(122 - (97 - ((int)line2[i] + y)));
					}
				}

		}

		std::cout << "\nReturn?----  1/0" << std::endl;
		std::cin >> option;
		if (option == 0)
			break;
		option = -1;

		b++;
	}

	fin.close();

	std::ofstream fof(FName);
	for (int i = 0; i < line3.size(); i++)
		fof << line3[i];
	fof.close();
	return 0;
}

std::string GetString(std::ifstream &fin)
{	
	std::string s;
	char ch1;
	while ((ch1 = fin.get()) != EOF) //output text
	{
		s += ch1;
	}

	for (int i = 0; i < s.size(); i++)
		std::cout << s[i];
	return s;
}

