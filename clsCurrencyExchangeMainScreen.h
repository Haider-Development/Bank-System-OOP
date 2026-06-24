#pragma once

#include <iostream>
#include <string>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrenciesClaculatorScreen.h"

using namespace std;

class clsCurrencyExchangeMainScreen : protected clsScreen
{
private :

	enum enCurrencyMenuOption {
		enListCurrencies = 1, enFindCurrency = 2,
		enUpdateRate = 3, enCurrencyCalculator = 4, enMainMenu = 5
	};

	static short _ReadCurrencyMenuOption()
	{
		cout << setw(40) << left << "" << "Choose What You Want To Do Between [1 _ 5} : ";
		short Choice = clsInbutValidate::ReadIntNumberBetween(1, 5, "\nInvalid Number ... Enter Number In Range [1 _ 5} : ");

		return Choice;
	}

	static void _GoBackToCurrenciesMenu()
	{
		cout << "\n\n\t\tPress Any Key To Go Back To Currencies Exchange Menu Screen ...";
		system("pause>0");
		clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMenuScreen();
	}

	static void _ShowCurrenciesListScreen()
	{
		/*cout << "Currencies List Screen Will Be Here ...\n";*/

		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		/*cout << "Find Currency Screen Will be here ...\n";*/

		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		/*cout << "Update Rate Screen Will Be here ...\n";*/

		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrenciesCalculatorScreen()
	{
		/*cout << "Currencies Calculator Screen Will Be Here ...\n";*/

		clsCurrenciesClaculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static void _PerformCurrenciesMenuOption(enCurrencyMenuOption Option)
	{
		switch (Option)
		{

		case enCurrencyMenuOption::enListCurrencies :
		{
			system("cls");
			_ShowCurrenciesListScreen();
			_GoBackToCurrenciesMenu();
			break;
		}

		case enCurrencyMenuOption::enFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrenciesMenu();
			break;
		}

		case enCurrencyMenuOption::enUpdateRate:
		{
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrenciesMenu();
			break;
		}

		case enCurrencyMenuOption::enCurrencyCalculator:
		{
			system("cls");
			_ShowCurrenciesCalculatorScreen();
			_GoBackToCurrenciesMenu();
			break;
		}

		case enCurrencyMenuOption::enMainMenu:
		{
			// the Main Screen Will complete the task
		}

		}
	}

public :

	static void ShowCurrencyExchangeMenuScreen()
	{
		system("cls");
		_DrawScreenHeader("Currency Exchange Menu Screen");

		cout << setw(40) << left << "" << "==============================================================\n\n";
		cout << setw(40) << left << "" << "\t\tCurrency Exchange Menu\n\n";
		cout << setw(40) << left << "" << "==============================================================\n\n";

		cout << setw(40) << left << "" << "[1]  : List Currencies.\n\n";
		cout << setw(40) << left << "" << "[2]  : Find Currency.\n\n";
		cout << setw(40) << left << "" << "[3]  : Update Rate.\n\n";
		cout << setw(40) << left << "" << "[4]  : Currency Calculator.\n\n";
		cout << setw(40) << left << "" << "[5]  : Main Menu.\n\n";

		cout << setw(40) << left << "" << "==============================================================\n\n";

		_PerformCurrenciesMenuOption((enCurrencyMenuOption)_ReadCurrencyMenuOption());
	}
};

