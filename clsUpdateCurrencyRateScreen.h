#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private :

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "\n---- Currency Card ----\n";
		cout << "_________________________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCurrency Code : " << Currency.CurrencyCode();
		cout << "\nCurrency Name : " << Currency.CurrencyName();
		cout << "\nRate (1$)     : " << Currency.Rate;
		cout << "\n_________________________________________\n";
	}

public :

	static void ShowUpdateCurrencyRateScreen()
	{
		_DrawScreenHeader("\tUpdate Currency Screen");

		string CurrencyCode = clsInbutValidate::ReadString("\nEnter Currency Code : ");

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nCurrency Wasn't Found ... Please Try Again.\n";
			string CurrencyCode = clsInbutValidate::ReadString("\nEnter Currency Code : ");
		}

		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		_PrintCurrencyCard(Currency);

		char Answer = 'y';

		cout << "\nAre You Sure You Want To Update Currency Rate ? (y/Y) or (n/N) : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			cout << "\nPlease Enter New Rate : ";
			float NewRate = clsInbutValidate::ReadDblNumber("Invalid Number ... Enter A Valid One : ");

			Currency.Rate = NewRate;

			cout << "\nCurrency Rate Updated Successfully ... Here Is The New Currency Card :\n";
			_PrintCurrencyCard(Currency);
		}

		else
			cout << "\nOperation Was Cancelled ...";
	}
};

