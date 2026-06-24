#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "clsBankClient.h";

class clsTransferScreen : protected clsScreen
{
private :

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n~~ Cliet Card ~~\n";
		cout << "____________________________\n";
		cout << "\nFull Name       : " << Client.FullName();
		cout << "\nAccount Number  : " << Client.AccountNumber();
		cout << "\nAccount Balance : " << Client.AccountBalance;
		cout << "\n____________________________\n";
		cout << "\n\n";
	}

	static string _ReadAccountNumber(string Message, clsBankClient Client = clsBankClient::GetEmptyClientObject())
	{
		string AccountNumber = clsInbutValidate::ReadString(Message);

		while (!clsBankClient::IsClientExists(AccountNumber) || Client.AccountNumber() == AccountNumber)
		{
			if (Client.AccountNumber() == AccountNumber)
			{
				cout << "\nYou Cannot Enter The Same Account Number !\n";
			}

			cout << "\nInvalid Account Number ... Please enter a valid one.\n";
			AccountNumber = clsInbutValidate::ReadString(Message);
		}

		return AccountNumber;
	}

public :

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\tTransfer Screen");

		string AccountNumber1 = _ReadAccountNumber("Enter Account Number You Want To Transfer From : ");
		clsBankClient Client1 = clsBankClient::Find(AccountNumber1);
		_PrintClient(Client1);

		string AccountNumber2 = _ReadAccountNumber("Enter Account Number You Want To Transfer To : ", Client1);
		clsBankClient Client2 = clsBankClient::Find(AccountNumber2);
		_PrintClient(Client2);

		double Amount = 0;

		do
		{
			if (Amount > Client1.AccountBalance)
			{
				cout << "\nThe Amount you entered Exceeds the Balance in the Client Account ...\n";
				cout << "You can only transfer up to : " << Client1.AccountBalance << endl;
			}

			cout << "\nPlease enter Amount you want to Transfer : ";
			Amount = clsInbutValidate::ReadDblNumber("Invalid Number ... Please Enter a Valid One : ");
			
		} while (Amount > Client1.AccountBalance);

		char Answer = 'y';

		cout << "Are you Sure you want to Perform this Transaction? (y/Y) or (n/N) : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (Client1.Transfer(Amount, Client2))
			{
				cout << "\nAmount [ " << Amount << " ] has been Transfered Successfully ... here Are New Balances :\n";
				_PrintClient(Client1);
				_PrintClient(Client2);
			}

			else
			{
				"\nCannot Transfer ... An Error was Occured";
			}
		}

		else
			cout << "\nOperation was Cancelled ...\n";
	}
};

