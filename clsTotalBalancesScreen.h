#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsScreen.h";
#include "clsUtil.h";
#include <iomanip>

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{

private :

	static void _PrintClientsBalanceRecordLine(clsBankClient Client)
	{
		cout << left << setw(20) << "" << " | " << left << setw(25) << Client.FullName();
		cout << left << setw(20) << "" << " | " << left << setw(25) << Client.AccountNumber();
		cout << left << setw(20) << "" << " | " << left << setw(25) << Client.AccountBalance;
	}

public :

	static void ShowTotalBalancesList()
	{
		vector <clsBankClient> vClients;
		vClients = clsBankClient::GetClientsList();

		string Title = "\tBalances List";
		string SubTitle = "\t[" + to_string(vClients.size()) + "] Client(s)";

		_DrawScreenHeader(Title, SubTitle);

		cout << left << setw(20) << "" << "---------------------------------------------------------------------------------------------------------------------\n";
		cout << left << setw(20) << "" << " | " << left << setw(25) << "Client Name";
		cout << left << setw(20) << "" << " | " << left << setw(25) << "Account Number";
		cout << left << setw(20) << "" << " | " << left << setw(25) << "Accoun Balance";

		cout << "\n" << endl;

		if (vClients.empty())
			cout << "\n\n\t\t\t\t\tNo Clients Available in The System.";

		else
		{
			for (clsBankClient& Client : vClients)
			{
				_PrintClientsBalanceRecordLine(Client);
				cout << endl;
			}

			cout << "\n" << left << setw(20) << "" << "---------------------------------------------------------------------------------------------------------------------\n";

			double TotalBalances = clsBankClient::GetTotalBalances();

			cout << "\n" << left << setw(55) << "" << " Total Balances : " << TotalBalances;
			cout << "\n" << left << setw(55) << "" << "[" << clsUtil::NumberToText(TotalBalances) << "]" << endl;

			cout << "\n" << left << setw(20) << "" << "---------------------------------------------------------------------------------------------------------------------\n";
		}

		cout << "\n" << left << setw(20) << "" << "---------------------------------------------------------------------------------------------------------------------\n";

	}
};

