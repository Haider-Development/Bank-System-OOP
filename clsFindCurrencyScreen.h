#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h";
#include "clsCurrency.h";
#include "clsInputValidate.h";

class clsFindCurrencyScreen : protected clsScreen
{
private :

	static void _PrintCurrencyCard(clsCurrency Currency)
	{
		cout << "---- Currency Card ----\n";
		cout << "_________________________________________\n";
		cout << "\nCountry       : " << Currency.Country();
		cout << "\nCurrency Code : " << Currency.CurrencyCode();
		cout << "\nCurrency Name : " << Currency.CurrencyName();
		cout << "\nRate (1$)     : " << Currency.Rate;
		cout << "\n_________________________________________\n";
	}

	static short _ReadFindModeOption()
	{
		cout << "Choose : [1] Find By Code  -  [2] Find By Country  -  [3] Back ? : ";
		
		short Choice = clsInbutValidate::ReadIntNumberBetween(1, 3, "Invalid Number ... Enter Number In Range [1 - 3] : ");
		return Choice;
	}

	static string _ReadFindModeOption(short Number)
	{
		string Mode = "";

		switch (Number)
		{
		case 1:
		{
			Mode = clsInbutValidate::ReadString("\nEnter Currency Code : ");
			return Mode;
			break;
		}

		case 2:
		{
			Mode = clsInbutValidate::ReadString("\nEnter Country Name : ");
			return Mode;
			break;
		}

		}
	}

public :

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\tFind Currency Screen");

		short Option = _ReadFindModeOption();

		if (Option == 3)
			return;

		string FindMethode = _ReadFindModeOption(Option);

		clsCurrency Currency = clsCurrency::PerformFindModeOption(FindMethode, clsCurrency::enFindMode (Option));

		while (!(Currency.IsCurrencyExist(Currency.CurrencyCode())))
		{
			cout << "\nCurrency wasn't Found ... Please Try Again\n";

			FindMethode = _ReadFindModeOption(Option);
			Currency = clsCurrency::PerformFindModeOption(FindMethode, clsCurrency::enFindMode(Option));
		}

		cout << "\nCurrency Was Found !\n\n";

		_PrintCurrencyCard(Currency);
	}
};

