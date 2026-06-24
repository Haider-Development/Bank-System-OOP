#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsDepositScreen.h";
#include "clsWithdrawScreen.h";
#include "clsTotalBalancesScreen.h";
#include "clsTransferScreen.h";
#include "clsTransferLogScreen.h";

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private :

	enum enTransactionsMenuOption { enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enTransfer = 4, enTransferLog = 5, enMainMenu = 6 };

	static short _ReadTransactionsMenuOption()
	{
		cout << left << setw(40) << "" << "Choose What You Want To Do Between [1 - 6] : ";
		short Choice = clsInbutValidate::ReadIntNumberBetween(1, 6, "Invalid Number ... Enter Number In Range [1 - 6] : ");
		
		return Choice;
	}

	static void _GoBackToTransactionsMenuScreen()
	{
		cout << "\n\n\t\tPress Any Key To Go Back To Transactions Menu Screen ...";
		system("Pause>0");
		ShowTransactionsMenuScreen();
	}

	static void _ShowDepositScreen()
	{
		/*cout << "Deposit Screen Will Be Here ...";*/
		clsDepositScreen::ShowDepositScreen();
	}

	static void _ShowWithDrawScreen()
	{
		/*cout << "Withdraw Screen Will Be Here ...";*/

		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _ShowTotalBalancesScreen()
	{
		/*cout << "Total Balances Screen Will Be Here ...";*/

		clsTotalBalancesScreen::ShowTotalBalancesList();
	}

	static void _ShowTransferScreen()
	{
		/*cout << "Transfer Screen Will Be Here ... \n";*/

		clsTransferScreen::ShowTransferScreen();
	}

	static void _ShowTransferLogListScreen()
	{
		/*cout << "Transfer Log Screen Will Be here ...\n";*/

		clsTransferLogScreen::ShowTransferLogListScreen();
	}

	static void _PerformTransactionsMenuScreen(enTransactionsMenuOption Option)
	{
		switch (Option)
		{

		case enTransactionsMenuOption::enDeposit :
		{
			system("cls");
			_ShowDepositScreen();
			_GoBackToTransactionsMenuScreen();
			break;
		}

		case enTransactionsMenuOption::enWithdraw :
		{
			system("cls");
			_ShowWithDrawScreen();
			_GoBackToTransactionsMenuScreen();
			break;
		}

		case enTransactionsMenuOption::enTotalBalances :
		{
			system("cls");
			_ShowTotalBalancesScreen();
			_GoBackToTransactionsMenuScreen();
			break;
		}

		case enTransactionsMenuOption::enTransfer:
		{
			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenuScreen();
			break;
		}

		case enTransactionsMenuOption::enTransferLog:
		{
			system("cls");
			_ShowTransferLogListScreen();
			_GoBackToTransactionsMenuScreen();
			break;
		}

		case enTransactionsMenuOption::enMainMenu :
		{
			// No Code Here Because Main Screen Will Complete the task
		}

		}
	}

public :

	static void ShowTransactionsMenuScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::enPTransacions))
		{
			return; //this will exit the function and back to main menu
		}

		system("cls");
		_DrawScreenHeader("\tTransactions Menu Screen");

		cout << setw(40) << left << "" << "==============================================================\n\n";
		cout << setw(40) << left << "" << "\t\t\tTransactions Menu\n\n";
		cout << setw(40) << left << "" << "==============================================================\n\n";

		cout << setw(40) << left << "" << "[1] : Deposit.\n\n";
		cout << setw(40) << left << "" << "[2] : Withdraw.\n\n";
		cout << setw(40) << left << "" << "[3] : Total Balances.\n\n";
		cout << setw(40) << left << "" << "[4] : Transfer.\n\n";
		cout << setw(40) << left << "" << "[5] : Transfer Log.\n\n";
		cout << setw(40) << left << "" << "[6] : Main Menu.\n\n";

		cout << setw(40) << left << "" << "==============================================================\n\n";

		_PerformTransactionsMenuScreen((enTransactionsMenuOption)_ReadTransactionsMenuOption());
	}
};

