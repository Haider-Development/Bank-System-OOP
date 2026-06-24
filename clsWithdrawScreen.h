#pragma once

#include <iostream>
#include "clsBankClient.h";
#include "clsInputValidate.h";
#include "clsScreen.h";

using namespace std;

class clsWithdrawScreen : protected clsScreen
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

	static string _ReadAccountNumber()
	{
		string AccountNumebr = clsInbutValidate::ReadString("Please Enter Account Number : ");

		return AccountNumebr;
	}

public:

	static void ShowWithdrawScreen()
	{
		_DrawScreenHeader("\tWithdraw Screen");

		string AccountNumber = _ReadAccountNumber();

		while (!clsBankClient::IsClientExists(AccountNumber))
		{
			cout << "\nClient With Account Number [" << AccountNumber << "] Wasn't Found ... Enter A valid one.\n";
			AccountNumber = _ReadAccountNumber();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);

		double Amount = 0;
		cout << "Please Enter Withdraw Amount : ";
		Amount = clsInbutValidate::ReadDblNumber("\nInvalid Number ... Please Enter a valid One : ");

		char Answer = 'y';

		cout << "\nAre You Sure You Want To Perform This Transaction ? (y/Y) Or (n/N) : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			if (Client.Withdraw(Amount))
				cout << "\nAmount [" << Amount << "] Withdrew Successfully ... New Balance is : " << Client.AccountBalance;

			else
			{
				cout << "\nCannot Withdraw ... Insufficient Balance." << endl;
				cout << "\nThe Amount You Ordered To Withdraw : " << Amount;
				cout << "\nYou Can Only Withdraw Amount Up To : " << Client.AccountBalance;
			}
		}

		else
			cout << "\nOperation Was Cancelled.";
	}

};

