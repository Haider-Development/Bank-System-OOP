#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsUser.h";
#include "clsInputValidate.h";

using namespace std;

class clsFindUserScreen : protected clsScreen
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

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\tFind User Screen");

		string UserName = "";
		UserName = clsInbutValidate::ReadString("Please Enter User Name : ");

		while (!clsUser::IsUserExists(UserName))
		{
			cout << "\nUser with User Name [" << UserName << "] wasn't found ... enter another one.\n";
			UserName = clsInbutValidate::ReadString("Please Enter User Name : ");
		}

		clsUser User = clsUser::Find(UserName);

		cout << "\nUser Found! ... Here Are User Info : \n\n";

		_PrintUser(User);
	}
};

