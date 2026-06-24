#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include "clsScreen.h";
#include "clsCurrency.h";

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private :

	static void _PrintCurrencyRecordLine(clsCurrency Currency)
	{
		cout << left << setw(7) << "";
		cout << " | " << left << setw(30) << Currency.Country();
		cout << " | " << left << setw(15) << Currency.CurrencyCode();
		cout << " | " << left << setw(50) << Currency.CurrencyName();
		cout << " | " << left << setw(15) << Currency.Rate;
	}

public :

	static void ShowCurrenciesListScreen()
	{
		vector <clsCurrency> vCurrencies;
		vCurrencies = clsCurrency::GetCurrencyiesList();

		_DrawScreenHeader("\tCurrencies List", "\t[" + to_string(vCurrencies.size()) + "] Currency(ies)");

		cout << left << setw(7) << "" << "--------------------------------------------------------------------------------------------------------------------------------------------\n";
		cout << left << setw(7) << "";
		cout << " | " << left << setw(30) << "Country Name";
		cout << " | " << left << setw(15) << "Code";
		cout << " | " << left << setw(50) << "Currency Name";
		cout << " | " << left << setw(15) << "Rate / (1$)\n";
		cout << left << setw(4) << "" << "--------------------------------------------------------------------------------------------------------------------------------------------";


		cout << "\n" << endl;

		if (vCurrencies.empty())
			cout << "\n\n" << setw(50) << left << "" << "No Currencies Available in The System.";

		else
			for (clsCurrency& Currency : vCurrencies)
			{
				_PrintCurrencyRecordLine(Currency);
				cout << endl;
			}

		cout << "\n" << left << setw(7) << "";
		cout << "---------------------------------------------------------------------------------------------------------------------------------------------\n";
	}
};

