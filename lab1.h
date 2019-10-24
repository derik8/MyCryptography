#pragma once
#include<iostream>
#include <fstream>
#include <string.h>
#include<map>

namespace NSlab1
{
	void lab1();
	int encrypt(int key, std::ifstream &fin, const char *FName);
	int decrypt(std::ifstream &fin, const char *FName);
}
std::string GetString(std::ifstream &fin);

