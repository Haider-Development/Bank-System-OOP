#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsBankClient.h";
#include <iomanip>
using namespace std;

class clsClientsListScreen : protected clsScreen
{

private :

	static void _PrintClientsRecordLine(clsBankClient Client)
	{
		cout << left << setw(7) << "";
		cout << " | " << left << setw(10) << Client.FirstName;
		cout << " | " << left << setw(10) << Client.LastName;
		cout << " | " << left << setw(15) << Client.FullName();
		cout << " | " << left << setw(30) << Client.Email;
		cout << " | " << left << setw(18) << Client.PhoneNumber;
		cout << " | " << left << setw(14) << Client.AccountNumber();
		cout << " | " << left << setw(8) << Client.PinCode;
		cout << " | " << left << setw(10) << Client.AccountBalance;
	}

public :

	static void ShowClientsList()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::enPShowClientsList))
		{
			return; //this will exit the function and back to main menu
		}

		vector <clsBankClient> vClients;
		vClients = clsBankClient::GetClientsList();

		_DrawScreenHeader("\tClients List", "\t[" + to_string(vClients.size()) + "] Client(s)");

		cout << left << setw(7) << "" << "-------------------------------------------------------------------------------------------------------------------------------------------\n";
		cout << left << setw(7) << "" << " | " << left << setw(10) << "First Name";
		cout << " | " << left << setw(10) << "Last Name";
		cout << " | " << left << setw(15) << "Full Name";
		cout << " | " << left << setw(30) << "Email";
		cout << " | " << left << setw(18) << "Phone Number";
		cout << " | " << left << setw(14) << "Account Number";
		cout << " | " << left << setw(8) << "Pin Code";
		cout << " | " << left << setw(10) << "Accoun Balance";

		cout << "\n" << endl;

		if (vClients.empty())
			cout << "\n\n" << setw(50) << left << "" << "No Clients Available in The System.";

		else
			for (clsBankClient& Client : vClients)
			{
				_PrintClientsRecordLine(Client);
				cout << endl;
			}

		cout << "\n" << left << setw(7) << "";
		cout << "---------------------------------------------------------------------------------------------------------------------------------------------\n";

	}
};

