#pragma once
#include<iostream>
#include <fstream>
#include <string.h>


namespace NSlab5
{
	void lab5();
	void encrypt(int n,int D, std::ifstream &fin, const char *FName);
	void decrypt(int &KEY, std::ifstream &fin, const char *FName);
}
std::string GetString(std::ifstream &fin);

