#pragma once

#include <iostream>
#include "clsInputValidate.h";
#include "clsBankClient.h";
#include "clsScreen.h";

using namespace std;

class clsFindClientScreen : protected clsScreen
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

	static void ShowFindClientScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::enPFindClient))
		{
			return; //this will exit the function and back to main menu
		}

		_DrawScreenHeader("\tFind Client Screen");

		string AccountNumber = "";
		AccountNumber = clsInbutValidate::ReadString("Please Enter Account Number : ");

		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nClient with Account Number [" << AccountNumber << "] wasn't found ... enter another one.\n";
			AccountNumber = clsInbutValidate::ReadString("Please Enter Account Number : ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		cout << "\nClient Found! ... Here Are Client Info : \n\n";

		_PrintClient(Client);
	}
};

