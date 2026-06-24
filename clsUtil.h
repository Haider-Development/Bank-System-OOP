#pragma once

#include <iostream>
#include "clsDate.h";
#include <ctime>
#include <cstdlib>
using namespace std;

enum class enCharacterType { smallletter = 1, capitalletter = 2, specialcharacter = 3, digit = 4, Mix = 5 };

class clsUtil
{
public:

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{
		int RandomNum = 0;

		RandomNum = rand() % (To - From + 1) + From;

		return RandomNum;
	}

	static char GetRandomCharacter(enCharacterType Character)
	{
		switch (Character)
		{
		case enCharacterType::smallletter:
			return RandomNumber(97, 122);

		case enCharacterType::capitalletter:
			return RandomNumber(65, 90);

		case enCharacterType::specialcharacter:
			return RandomNumber(33, 47);

		case enCharacterType::digit:
			return RandomNumber(48, 57);

		case enCharacterType::Mix:
		{
			int X;

			while (true)
			{
				X = RandomNumber(48, 122);

				if (X >= 48 && X <= 57)
				{
					X = 1;
					break;
				}

				else if (X >= 65 && X <= 90)
				{
					X = 2;
					break;
				}

				else if (X >= 97 && X <= 122)
				{
					X = 3;
					break;
				}
			}

			return (X == 1) ? RandomNumber(48, 122) : (X == 2) ? RandomNumber(65, 90) : RandomNumber(97, 122);
		}

		}

	}

	static string GenerateWord(enCharacterType characters, short length)
	{
		string word = "";

		for (int i = 1; i <= length; i++)
		{
			word = word + GetRandomCharacter(characters);
		}

		return word;
	}

	static string GenerateKey()
	{
		string word = "";

		word = GenerateWord(enCharacterType::capitalletter, 4) + "_";
		word = word + GenerateWord(enCharacterType::capitalletter, 4) + "_";
		word = word + GenerateWord(enCharacterType::capitalletter, 4) + "_";
		word = word + GenerateWord(enCharacterType::capitalletter, 4);

		return word;
	}

	static void GenerateKeys(short numberofkeys)
	{
		cout << endl;

		for (int i = 1; i <= numberofkeys; i++)
		{
			cout << " key number (" << i << ") : " << GenerateKey() << endl;
		}
	}

	static void Swap(int& X, int& Y)
	{
		int temp;

		temp = Y;
		Y = X;
		X = temp;
	}

	static void Swap(double& X, double& Y)
	{
		double temp;

		temp = Y;
		Y = X;
		X = temp;
	}

	static void Swap(string& X, string& Y)
	{
		string temp;

		temp = Y;
		Y = X;
		X = temp;
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate Date;

		Date.Day = Date1.Day;
		Date.Month = Date1.Month;
		Date.Year = Date1.Year;

		Date1.Day = Date2.Day;
		Date1.Month = Date2.Month;
		Date1.Year = Date2.Year;

		Date2.Day = Date.Day;
		Date2.Month = Date.Month;
		Date2.Year = Date.Year;
	}

	static void ShuffleArray(int array[100], int arraylength)
	{
		for (int i = 0; i < arraylength; i++)
		{
			Swap(array[RandomNumber(1, arraylength) - 1], array[RandomNumber(1, arraylength) - 1]);
		}
	}

	static void ShuffleArray(string array[100], int arraylength)
	{
		for (int i = 0; i < arraylength; i++)
		{
			Swap(array[RandomNumber(1, arraylength) - 1], array[RandomNumber(1, arraylength) - 1]);
		}
	}

	static void FillArrayWithRandomNumbers(int array[100], int arraylength)
	{
		for (int i = 0; i < arraylength; i++)
		{
			array[i] = RandomNumber(1, 100);
		}
	}

	static void FillArrayWithRandomWords(string array[100], int arraylength, short NumberOfCharacters)
	{
		for (int i = 0; i < arraylength; i++)
		{
			array[i] = GenerateWord(enCharacterType::Mix, NumberOfCharacters);
		}
	}

	static void FillArrayWithRandomKeys(string array[100], int arraylength)
	{
		for (int i = 0; i < arraylength; i++)
		{
			array[i] = GenerateKey();
		}
	}

	static string Tab(short NumberOfTabs)
	{
		string sTab = "";

		for (short i = 0; i < NumberOfTabs; i++)
		{
			sTab += "\t";
		}

		return sTab;
	}

	static string Encryption(string text, short encryptionkye)
	{
		for (int i = 0; i <= text.length(); i++)
		{
			text[i] = char((int)text[i] + encryptionkye);
		}

		return text;
	}

	static string Decryption(string text, short encryptionkye)
	{
		for (int i = 0; i <= text.length(); i++)
		{
			text[i] = char((int)text[i] - encryptionkye);
		}

		return text;
	}

	static string NumberToText(int Number)
	{
		return clsDate::NumberToText(Number);
	}

};

