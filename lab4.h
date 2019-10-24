#pragma once
#include<iostream>
#include <fstream>
#include <string.h>
#include<bitset>
#include <tuple>

namespace NSlab4
{
	void lab4();
	void encrypt_decrypt(std::bitset<8> message,std::bitset<8> KEY_1, std::bitset<8> KEY_2);
	std::tuple<std::bitset<8>, std::bitset<8>> CreateKey(std::bitset<10> KEY);

	std::bitset<8> IP(std::bitset<8> message);
	
	std::tuple<std::bitset<4>, std::bitset<4>> Fk(std::bitset<8> message, std::bitset<8> KEY);

	std::bitset<8> SW(std::bitset<4> L, std::bitset<4> R);

	std::bitset<8> IP_invert(std::bitset<4> L, std::bitset<4> R);

	int Switch_S(int a, int b);
}


