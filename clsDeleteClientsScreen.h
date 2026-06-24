#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsBankClient.h";
using namespace std;

class clsDeleteClientsScreen : protected clsScreen
{
private :

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n~~ Cliet Card ~~\n";
		cout << "____________________________\n";
		cout << "\nFirst Name      : " << Client.FirstName;
		cout << "\nLast Name       : " << Client.LastName;
		cout << "\nFull Name       : " << Client.FullName();
		cout << "\nEmail           : " << Client.Email;
		cout << "\nPhone Number    : " << Client.PhoneNumber;
		cout << "\nAccount Number  : " << Client.AccountNumber();
		cout << "\nPin Code        : " << Client.PinCode;
		cout << "\nAccount Balance : " << Client.AccountBalance;
		cout << "\n____________________________\n";
		cout << "\n\n";
	}

public :

	static void ShowDeleteClientScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::enPDeleteClient))
		{
			return; //this will exit the function and back to main menu
		}

		_DrawScreenHeader("\tDelete Client Screen");

		string AccountNumber = "";

		AccountNumber = clsInbutValidate::ReadString("Enter Account Number : ");

		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nAccount Number Is not Exists ... Please Enter another One\n";
			AccountNumber = clsInbutValidate::ReadString("Enter Account Number : ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer = 'y';

		cout << "\nAre you sure u Want to delete this client ? (y/Y) or (n/N) : ";
		cin >> Answer;

		if ('y' == tolower(Answer))
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfully! ... After Deleted :\n\n";
				_PrintClient(Client);
			}

			else
			{
				cout << "\nError ... Unsuccessfull to Delete Client ";
			}
		}

		else
			cout << "\nDelete Operation Was Cancelled ...\n";
	}
};

