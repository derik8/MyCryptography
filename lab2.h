#pragma once
#include<iostream>
#include <fstream>
#include <string.h>
#include<map>
namespace NSlab2 {

	void lab2();
	void encrypt(int a, int b, int m, std::ifstream &fin, const char *FName);
	void decrypt(int &m,std::ifstream &fin, std::ifstream & finB, const char *FName);
}
std::string GetString(std::ifstream &fin);

