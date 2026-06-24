#pragma once

#include <iostream>
#include <string>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h";

using namespace std;

class clsCurrenciesClaculatorScreen : protected clsScreen
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

	static string _ReadCurrencyCode(string Message)
	{
		string CurrencyCode = clsInbutValidate::ReadString(Message);

		while (!clsCurrency::IsCurrencyExist(CurrencyCode))
		{
			cout << "\nInvalid Currency Code ... Please enter a valid one.\n";
			CurrencyCode = clsInbutValidate::ReadString(Message);
		}

		return CurrencyCode;
	}

public :

	static void ShowCurrencyCalculatorScreen()
	{
		char Answer = 'y';

		do
		{
			system("cls");

			_DrawScreenHeader("\tCurrency Calculator Screen");

			string CurrencyCode1 = _ReadCurrencyCode("Enter Currency Code To Convert From : ");
			clsCurrency Currency1 = clsCurrency::FindByCode(CurrencyCode1);

			string CurrencyCode2 = _ReadCurrencyCode("Enter Currency Code To Convert To : ");
			clsCurrency Currency2 = clsCurrency::FindByCode(CurrencyCode2);

			float Amount = 0;

			cout << "\nEnter Amount To Exchange : ";
			Amount = clsInbutValidate::ReadDblNumber("Invalid Number ... Please Enter a Valid One : ");

			cout << "\nConvert From :\n";
			_PrintCurrencyCard(Currency1);

			cout << "\nConvert To :\n";
			_PrintCurrencyCard(Currency2);

			float Result = clsCurrency::ConvertFromCrurrencyToAnother(Currency1, Currency2, Amount);

			cout << "\nResult :\n";
			cout << Amount << " " << Currency1.CurrencyCode() << " = " << Result << " " << Currency2.CurrencyCode();

			cout << "\n\nDo You Want To Do Another Calculation ? : ";
			cin >> Answer;

		} while (tolower(Answer) == 'y');
	}
};

