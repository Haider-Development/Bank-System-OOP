#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsBankClient.h";

class clsAddNewClientScreen : protected clsScreen
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

	static void ShowAddNewClientScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::enPAddNewClient))
		{
			return; //this will exit the function and back to main menu
		}

		_DrawScreenHeader("\tAdd New Client Screen");

		string AccountNumber = "";

		AccountNumber = clsInbutValidate::ReadString("Enter Account Number : ");

		while (clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nAccount Number Already Exists ... Please Enter another One\n";
			AccountNumber = clsInbutValidate::ReadString("Enter Account Number : ");
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObj(AccountNumber);

		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults Result;
		Result = NewClient.Save();

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
			_PrintClient(NewClient);
			break;
		}

		case clsBankClient::enSaveResults::SaveFailedAccNumExist:
		{
			cout << "\nError ... Cannot Save Account Number Already in Use!";
			break;
		}

		}
	}

};

