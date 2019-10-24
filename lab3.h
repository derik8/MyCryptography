#pragma once
#include<iostream>
#include <fstream>
#include <string.h>


namespace NSlab3
{
	void lab3();
	int encrypt(int &KEY, std::ifstream &fin, const char *FName);
	int decrypt(int &KEY, std::ifstream &fin, const char *FName);
	int& CreateGama(int &KEY, int &Y, int size_gama, int m);
}
std::string GetString(std::ifstream &fin);

