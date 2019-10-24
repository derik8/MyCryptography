#include "lab4.h"
#define DEBUG
void NSlab4::lab4()
{
	int	option;
	
	std::string key_str,message_str;	

	std::cout << "LAB5" << std::endl;
	std::cout << "encrypt  ------- decrypt (1/2)?" << std::endl;
	std::cin >> option;

	std::cout << "Enter KEY:" << std::endl;	
	std::cin >> message_str;
	

	//Створення ключа
	std::bitset<10> KEY(key_str);

	std::bitset<8> KEY_1, KEY_2;

	
	std::tie(KEY_1,KEY_2) = CreateKey(KEY);
	
	
	std::cout << "Enter message :" << std::endl;
	std::cin >> message_str;
	std::bitset<8> message(message_str);

	if (option == 1)
	{
		std::cout << "\nEncrypt message:" << std::endl;
		encrypt_decrypt(message,KEY_1,KEY_2);
	}
	else
	{
		std::cout << "\nDecrypt message:" << std::endl;
		encrypt_decrypt(message, KEY_2, KEY_1);
	}
}



//███ █  █ ████ ████ ██ ██ ████ ███       ████─█──█─████         ████  ███ ████ ████ ██ ██ ████ ███
//█   ██ █ █  █ █  █  ███  █  █  █	      █──█─██─█─█──██        █  ██ █   █  █ █  █  ███  █  █  █
//███ █ ██ █    ████   █   ████  █	      ████─█─██─█──██        █  ██ ███ █    ████   █   ████  █
//█   █  █ █  █ █ █    █   █     █	      █──█─█──█─█──██        █  ██ █   █  █ █ █    █   █     █
//███ █  █ ████ █  █   █   █     █        █──█─█──█─████         ████  ███ ████ █  █   █   █     █ 
void NSlab4::encrypt_decrypt(std::bitset<8> message, std::bitset<8> KEY_1, std::bitset<8> KEY_2)
{	
	std::bitset<4> L,R;

	message = IP(message);
	std::tie(L,R) = Fk(message,KEY_1);
	message = SW(L,R);
	std::tie(L,R) = Fk(message,KEY_2);
	message=IP_invert(L, R);

	std::cout << message << std::endl;
	
}


std::tuple<std::bitset<8>, std::bitset<8>> NSlab4::CreateKey(std::bitset<10> KEY)
{// К1
 //
	std::bitset<8> KEY_1;
	std::bitset<8> KEY_2;
	//P10
	std::bitset<10> KEY_P10;



	KEY_P10[0] = KEY[4];
	KEY_P10[1] = KEY[2];
	KEY_P10[2] = KEY[1];
	KEY_P10[3] = KEY[9];
	KEY_P10[4] = KEY[0];
	KEY_P10[5] = KEY[6];
	KEY_P10[6] = KEY[3];
	KEY_P10[7] = KEY[8];
	KEY_P10[8] = KEY[5];
	KEY_P10[9] = KEY[7];


	//Зсув вліво
	std::bitset<5> KEY_Left;
	std::bitset<5> KEY_Right;

	for (int i = 0, j = 5; i < 5; i++, j++)
	{
		KEY_Right[i] = KEY_P10[i];
		KEY_Left[i] = KEY_P10[j];
	}

	int t = KEY_Left[4];
	KEY_Left = KEY_Left << 1;
	KEY_Left[0] = t;

	t = KEY_Right[4];
	KEY_Right = KEY_Right << 1;
	KEY_Right[0] = t;


	for (int i = 0, j = 5; i < 5; i++, j++)
	{
		KEY_P10[j] = KEY_Left[i];
		KEY_P10[i] = KEY_Right[i];

	}
	//запис К1
	KEY_1[0] = KEY_P10[1];
	KEY_1[1] = KEY_P10[0];
	KEY_1[2] = KEY_P10[5];
	KEY_1[3] = KEY_P10[2];
	KEY_1[4] = KEY_P10[6];
	KEY_1[5] = KEY_P10[3];
	KEY_1[6] = KEY_P10[7];
	KEY_1[7] = KEY_P10[4];

	// К2
	for (int i = 0; i < 2; i++)
	{
		t = KEY_Left[4];
		KEY_Left = KEY_Left << 1;
		KEY_Left[0] = t;

		t = KEY_Right[4];
		KEY_Right = KEY_Right << 1;
		KEY_Right[0] = t;
	}

	for (int i = 0, j = 5; i < 5; i++, j++)
	{
		KEY_P10[j] = KEY_Left[i];
		KEY_P10[i] = KEY_Right[i];

	}
	//запис К2
	KEY_2[0] = KEY_P10[1];
	KEY_2[1] = KEY_P10[0];
	KEY_2[2] = KEY_P10[5];
	KEY_2[3] = KEY_P10[2];
	KEY_2[4] = KEY_P10[6];
	KEY_2[5] = KEY_P10[3];
	KEY_2[6] = KEY_P10[7];
	KEY_2[7] = KEY_P10[4];

	return   std::make_tuple(KEY_1, KEY_2);
}

std::bitset<8> NSlab4::IP(std::bitset<8> message)
{ 
	std::bitset<8> btst;

	btst[0] = message[1];
	btst[1] = message[3];
	btst[2] = message[0];
	btst[3] = message[4];
	btst[4] = message[7];
	btst[5] = message[5];
	btst[6] = message[2];
	btst[7] = message[6];

	return btst;
}

std::tuple<std::bitset<4>, std::bitset<4>> NSlab4::Fk(std::bitset<8> message, std::bitset<8> KEY)
{
	std::bitset<4> L, R,P4,C;
	
	int S0[4][4] ={{1,0,3,2},
				 {3,2,1,0},
			     {0,2,1,3},
				 {3,1,3,2}
				};

	int S1[4][4] = { {0,1,2,3},
				   {2,0,1,3},
			       {3,0,1,0},
				   {2,1,0,3}
	};

	for (int i = 0; i < 4; i++)
	{
		L[i] = message[i+4];
		R[i] = message[i];
	}

//    E/P
	message[0] = R[3];
	message[1] = R[0];
	message[2] = R[1];
	message[3] = R[2];
	message[4] = R[1];
	message[5] = R[2];
	message[6] = R[3];
	message[7] = R[0];

	message = message ^ KEY;
// S0  та  S1
	int i,j;
// S0
	i=Switch_S(message[7], message[4]);
	j=Switch_S(message[6], message[5]);

	switch (S0[i][j])
	{
	case 0:{C[3] = 0; C[2] = 0; break;}
	case 1:{C[3] = 0; C[2] = 1; break;}
	case 2:{C[3] = 1; C[2] = 0; break;}
	case 3:{C[3] = 1; C[2] = 1; break;}	
	}
//S1	
	i = Switch_S(message[3], message[0]);
	j = Switch_S(message[2], message[1]);

	switch (S1[i][j])
	{
	case 0: {C[1] = 0; C[0] = 0; break; }
	case 1: {C[1] = 0; C[0] = 1; break; }
	case 2: {C[1] = 1; C[0] = 0; break; }
	case 3: {C[1] = 1; C[0] = 1; break; }
	}
//P4
	P4[0] = C[3];
	P4[1] = C[1];
	P4[2] = C[0];
	P4[3] = C[2];

// L^P4;
	L = L ^ P4;

	return std::make_tuple(L, R);
}

std::bitset<8> NSlab4::SW(std::bitset<4> L, std::bitset<4> R)
{
	std::bitset<8> mess;
	for (int i = 0; i < 4; i++)
	{
		mess[i] = L[i];
		mess[i + 4] = R[i];
	}

	return mess;
}

std::bitset<8> NSlab4::IP_invert(std::bitset<4> L, std::bitset<4> R)
{
	std::bitset<8> mess;	

	mess[0] =R[2]; 	 // mess1[2];
	mess[1] =R[0]; 	 // mess1[0];
	mess[2] =L[2]; 	 // mess1[6];
	mess[3] =R[1]; 	 // mess1[1];
	mess[4] =R[3]; 	 // mess1[3];
	mess[5] =L[1]; 	 // mess1[5];
	mess[6] =L[3]; 	 // mess1[7];
	mess[7] =L[0]; 	 // mess1[4];

	return mess;
}

int NSlab4::Switch_S(int a, int b)
{
	int i;
	if (a == 0)
	{

		if (b == 0)
			i = 0;
		else
			i = 1;

	}
	else
	{

		if (b == 0)
			i = 2;
		else
			i = 3;
	}
	return i;
}


