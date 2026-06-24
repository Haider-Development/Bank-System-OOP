#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsBankClient.h";

using namespace std;

class clsUdpateClientScreen : protected clsScreen
{
private :

	static void _ReadClientInfo(clsBankClient& Client)
	{
		Client.FirstName = clsInbutValidate::ReadString("\nEnter First Name      : ");
		Client.LastName = clsInbutValidate::ReadString("\nEnter Last Name       : ");
		Client.Email = clsInbutValidate::ReadString("\nEnter Email           : ");
		Client.PhoneNumber = clsInbutValidate::ReadString("\nEnter Phone Number    : ");
		Client.PinCode = clsInbutValidate::ReadString("\nEnter Pin Code        : ");

		cout << "\nEnter Account Balance : ";
		Client.AccountBalance = clsInbutValidate::ReadDblNumber("\nNot Valid, Enter A Valid Account Balance : ");

		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
	}

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

	static void ShowUpdateClientScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::enPUpdateClient))
		{
			return; //this will exit the function and back to main menu
		}

		_DrawScreenHeader("\tUpdate Client Screen");

		string AccountNumber = "";

		AccountNumber = clsInbutValidate::ReadString("Enter Account Number : ");

		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nInvalid Account Number ... Please Enter a Valid One\n\n";
			AccountNumber = clsInbutValidate::ReadString("Enter Account Number : ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		char Answer = 'y';

		cout << "\nAre You Sure You Want To Update This Client ? (y/Y) or (n/N) : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			cout << "\n\n    Update Client Info :\n";
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

			_ReadClientInfo(Client);

			clsBankClient::enSaveResults Result;
			Result = Client.Save();

			switch (Result)
			{

			case clsBankClient::enSaveResults::SaveFailedEmptyObj:
			{
				cout << "\nError ... Cannot Save an empty object!";
				break;
			}

			case clsBankClient::enSaveResults::SaveSucceded:
			{
				cout << "\nSave Succeded! ... New Info about The Client :\n\n";
				_PrintClient(Client);
				break;
			}

			}
		}

		else
			cout << "\nUpdate Operation Was Cancelled ...";
	}
};

