#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h";
#include "clsBankClient.h";

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private :

	static void _PrintTransferLog(clsBankClient::stTransferLog TransferLog)
	{
		cout << left << setw(7) << "";
		cout << " | " << left << setw(20) << TransferLog.DateAndTime;
		cout << " | " << left << setw(16) << TransferLog.SAccountNumber;
		cout << " | " << left << setw(20) << TransferLog.DAccountNumber;
		cout << " | " << left << setw(12) << TransferLog.Amount;
		cout << " | " << left << setw(18) << TransferLog.SAccountBalance;
		cout << " | " << left << setw(18) << TransferLog.DAccountBalance;
		cout << " | " << left << setw(10) << TransferLog.User;
	}

public :

	static void ShowTransferLogListScreen()
	{
		vector <clsBankClient::stTransferLog> vTransferLog;
		vTransferLog = clsBankClient::GetTransferLogList();

		_DrawScreenHeader("\tTransfer Log List Screen", "\t[" + to_string(vTransferLog.size()) + "] Transfer(s)");

		cout << left << setw(7) << "" << "-------------------------------------------------------------------------------------------------------------------------------------------\n";
		cout << left << setw(7) << "" << " | " << left << setw(20) << "Date And Time";
		cout << " | " << left << setw(16) << "S.Account Number";
		cout << " | " << left << setw(20) << "D.Account Number";
		cout << " | " << left << setw(12) << "Amount";
		cout << " | " << left << setw(18) << "S.Account Balance";
		cout << " | " << left << setw(18) << "D.Account Balance";
		cout << " | " << left << setw(10) << "User";

		cout << "\n" << endl;

		if (vTransferLog.empty())
			cout << "\n\n" << setw(50) << left << "" << "No Transfers Available in The System.";

		else
			for (clsBankClient::stTransferLog& TransferLog : vTransferLog)
			{
				_PrintTransferLog(TransferLog);
				cout << endl;
			}

		cout << "\n" << left << setw(7) << "";
		cout << "---------------------------------------------------------------------------------------------------------------------------------------------\n";

	}
};

