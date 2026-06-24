#pragma once

#include <iostream>
#include "clsScreen.h";
#include <iomanip>
#include "clsInputValidate.h";
#include "clsClientsListScreen.h";
#include "clsAddNewClientScreen.h";
#include "clsDeleteClientsScreen.h";
#include "clsUdpateClientScreen.h";
#include "clsFindClientScreen.h";
#include "clsTransactionsScreen.h";
#include "clsManageUsersScreen.h";
#include "clsLoginRegisterScreen.h";
#include "clsCurrencyExchangeMainScreen.h";
#include "Global.h";

using namespace std;

class clsMainScreen : protected clsScreen
{

	enum enMainMenuOption {
		enClientsList = 1, enAddNewClient = 2, enDeleteClient = 3, enUpdateClient = 4, enFindClient = 5,
		enTransactions = 6, enManageUsers = 7, enLoginRegister = 8, enCurrencyExchange = 9, enLogOut = 10
	};

	static short _ReadMainMenuOption()
	{
		cout << setw(40) << left << "" << "Choose What You Want To Do Between [1 - 10] : ";
		short Choice = clsInbutValidate::ReadIntNumberBetween(1, 10, "Please enter Number Between[1 - 10] : ");

		return Choice;
	}

	static void _GoBackToMainMenu()
	{
		cout << "\n\t\tPress Any Key To Go Back To Main Menu Screen ...";
		system("Pause>0");
		ShowMainMenu();
	}

	static void _ShowClientsListScreen()
	{
		/*cout << "Show Clients Screen Will be here ...\n\n";*/

		clsClientsListScreen::ShowClientsList();
	}

	static void _ShowAddNewClientScreen()
	{
		/*cout << "Show Add New Client Screen Will be here ...\n\n";*/
		clsAddNewClientScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteClientScreen()
	{
		/*cout << "Show Delete Client Screen Will be here ...\n\n";*/

		clsDeleteClientsScreen::ShowDeleteClientScreen();
	}

	static void _ShowUpdateClientScreen()
	{
		/*cout << "Show Update Client Screen Will be here ...\n\n";*/

		clsUdpateClientScreen::ShowUpdateClientScreen();
	}

	static void _ShowFindClientScreen()
	{
		/*cout << "Show Find Client Screen Will be here ...\n\n";*/

		clsFindClientScreen::ShowFindClientScreen();
	}

	static void _ShowTransactionsMenuScreen()
	{
		/*cout << "Show Transactions Menu Screen Will be here ...\n\n";*/

		clsTransactionsScreen::ShowTransactionsMenuScreen();
	}

	static void _ShowManageUsersScreen()
	{
		/*cout << "Show Manage Users Screen Will be here ...\n\n";*/

		clsManageUsersScreen::ShowManageUsersMenu();
	}

	static void _ShowLoginRegisterScreen()
	{
		clsLoginRegisterScreen::ShowLoginRegisterScreen();
	}

	static void _ShowCurrencyExchangeMenuScreen()
	{
		/*cout << "Currencies Menu Screen Will Be Here ...\n";*/

		clsCurrencyExchangeMainScreen::ShowCurrencyExchangeMenuScreen();
	}

	static void _LogOut()
	{
		CurrentUser = clsUser::Find("", "");

		// this will go back to main function
	}

	static void _PerformMainMenuOption(enMainMenuOption Option)
	{
		switch (Option)
		{

		case enMainMenuOption::enClientsList:
		{
			system("cls");
			_ShowClientsListScreen();
			_GoBackToMainMenu();
			break;
		}

		case enMainMenuOption::enAddNewClient:
		{
			system("cls");
			_ShowAddNewClientScreen();
			_GoBackToMainMenu();
			break;
		}

		case enMainMenuOption::enDeleteClient:
		{
			system("cls");
			_ShowDeleteClientScreen();
			_GoBackToMainMenu();
			break;
		}

		case enMainMenuOption::enUpdateClient:
		{
			system("cls");
			_ShowUpdateClientScreen();
			_GoBackToMainMenu();
			break;
		}

		case enMainMenuOption::enFindClient:
		{
			system("cls");
			_ShowFindClientScreen();
			_GoBackToMainMenu();
			break;
		}

		case enMainMenuOption::enTransactions:
		{
			system("cls");
			_ShowTransactionsMenuScreen();
			_GoBackToMainMenu();
			break;
		}

		case enMainMenuOption::enManageUsers:
		{
			system("cls");
			_ShowManageUsersScreen();
			_GoBackToMainMenu();
			break;
		}

		case enMainMenuOption::enLoginRegister:
		{
			system("cls");
			_ShowLoginRegisterScreen();
			_GoBackToMainMenu();
			break;
		}

		case enMainMenuOption::enCurrencyExchange:
		{
			system("cls");
			_ShowCurrencyExchangeMenuScreen();
			_GoBackToMainMenu();
			break;
		}

		case enMainMenuOption::enLogOut:
		{
			system("cls");
			_LogOut();
			break;
		}

		}
	}

public:

	static void ShowMainMenu()
	{
		system("cls");
		_DrawScreenHeader("\tMain Menu Screen");

		cout << setw(40) << left << "" << "==============================================================\n\n";
		cout << setw(40) << left << "" << "\t\t\tMain Menu\n\n";
		cout << setw(40) << left << "" << "==============================================================\n\n";

		cout << setw(40) << left << "" << "[1]  : Show Clients List.\n\n";
		cout << setw(40) << left << "" << "[2]  : Add New Client.\n\n";
		cout << setw(40) << left << "" << "[3]  : Delete Client.\n\n";
		cout << setw(40) << left << "" << "[4]  : Update Client.\n\n";
		cout << setw(40) << left << "" << "[5]  : Find Client.\n\n";
		cout << setw(40) << left << "" << "[6]  : Transactions.\n\n";
		cout << setw(40) << left << "" << "[7]  : Manage Users.\n\n";
		cout << setw(40) << left << "" << "[8]  : Login Register.\n\n";
		cout << setw(40) << left << "" << "[9]  : Currency Exchange.\n\n";
		cout << setw(40) << left << "" << "[10] : Log Out.\n" << endl;

		cout << setw(40) << left << "" << "==============================================================\n\n";

		_PerformMainMenuOption((enMainMenuOption)_ReadMainMenuOption());
	}
};

