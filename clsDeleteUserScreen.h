#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsUser.h";
#include "clsInputValidate.h";

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private :

	static void _PrintUser(clsUser User)
	{
		cout << "\n~~ User Card ~~\n";
		cout << "____________________________\n";
		cout << "\nFirst Name      : " << User.FirstName;
		cout << "\nLast Name       : " << User.LastName;
		cout << "\nFull Name       : " << User.FullName();
		cout << "\nEmail           : " << User.Email;
		cout << "\nPhone Number    : " << User.PhoneNumber;
		cout << "\nUser Name       : " << User.UserName;
		cout << "\nPassword        : " << User.Password;
		cout << "\nPermissions     : " << User.Permissions;
		cout << "\n____________________________\n";
		cout << "\n\n";
	}

public :

	static void ShowDeleteUserScreen()
	{
		_DrawScreenHeader("\tDelete User Screen");

		string UserName = "";

		UserName = clsInbutValidate::ReadString("Enter User Name : ");

		while (!clsUser::IsUserExists(UserName) || UserName == "Admin")
		{
			cout << "\nUser Name Is not (Exists/Valid) ... Please Enter another One\n";
			UserName = clsInbutValidate::ReadString("Enter User Name : ");
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'y';

		cout << "\nAre you sure u Want to delete this User ? (y/Y) or (n/N) : ";
		cin >> Answer;

		if ('y' == tolower(Answer))
		{
			if (User.Delete())
			{
				cout << "\nUser Deleted Successfully! ... After Deleted :\n\n";
				_PrintUser(User);
			}

			else
			{
				cout << "\nError ... Unsuccessfull to Delete User ";
			}
		}

		else
			cout << "\nDelete Operation Was Cancelled ...\n";
	}
};

