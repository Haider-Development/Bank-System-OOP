#pragma once

#include <iostream>
#include "clsDate.h";
using namespace std;

class clsInbutValidate
{
public:

	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
	}

	static int ReadIntNumber(string Message)
	{
		int X = 0;

		cin >> X;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;
			cin >> X;
		}

		return X;
	}

	static int ReadIntNumberBetween(int From, int To, string Message)
	{
		int Number = 0;

		do
		{
			Number = ReadIntNumber("Invalid Number, Please enter a valid one : ");

			if (Number < From || Number > To)
				cout << Message;

		} while (Number < From || Number > To);

		return Number;
	}

	//Sample Of Reuseability

	/*static int ReadIntNumberBetween(int From, int To, string Message)
	{
		int Number = ReadIntNumber("Invalid Number, Please enter a valid one.");

		while (!IsNumberBetween(Number, From, To))
		{
			cout << Message;

			Number = ReadIntNumber("Invalid Number, Please enter a valid one.");
		}

		return Number;
	}*/

	static double ReadDblNumber(string Message)
	{
		double X = 0;

		cin >> X;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			cout << Message;
			cin >> X;
		}

		return X;
	}

	static double ReadDblNumberBetween(double From, double To, string Message)
	{
		double Number = 0;

		do
		{
			Number = ReadIntNumber("Invalid Number, Please enter a valid one.");

			if (Number < From || Number > To)
				cout << Message;

		} while (Number < From || Number > To);

		return Number;
	}

	static bool IsDateBetween(clsDate Date, clsDate DateStart, clsDate DateEnd)
	{
		if (clsDate::IsDate1AfterDate2(DateStart, DateEnd))
			clsDate::SwapDates(DateStart, DateEnd);

		return (
			clsDate::CompareDates(Date, DateStart) == enCompareDates::eAfter
			&&
			clsDate::CompareDates(Date, DateEnd) == enCompareDates::eBefore
			);
	}

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidateDate(Date);
	}

	static string ReadString(string Message)
	{
		string Sub = "";

		cout << Message;
		getline(cin >> ws, Sub);

		return Sub;
	}
};

