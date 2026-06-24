#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsUser.h";
#include "clsInputValidate.h";

using namespace std;

class clsUpdateUserScreen : protected clsScreen
{
private :

	static void _ReadUserInfo(clsUser& User)
	{
		User.FirstName = clsInbutValidate::ReadString("\nEnter First Name      : ");
		User.LastName = clsInbutValidate::ReadString("\nEnter Last Name       : ");
		User.Email = clsInbutValidate::ReadString("\nEnter Email           : ");
		User.PhoneNumber = clsInbutValidate::ReadString("\nEnter Phone Number    : ");
		User.Password = clsInbutValidate::ReadString("\nEnter Password        : ");

		cout << "\nEnter Permissions     :\n\n";
		User.Permissions = _ReadPermissionsToSet();
	}

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

	static short _ReadPermissionsToSet()
	{
		char Answer = 'y';

		cout << "Do You Want To Give Full Access To This User ? (y/Y) or (n/N) : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			return -1;

		short Permissions = 0;

		cout << "Do you Want to give access to [Show Clients List] ? : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::enPShowClientsList;

		cout << "Do you Want to give access to [Add New Client] ? : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::enPAddNewClient;

		cout << "Do you Want to give access to [Delete Client] ? : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::enPDeleteClient;

		cout << "Do you Want to give access to [Update Client] ? : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::enPUpdateClient;

		cout << "Do you Want to give access to [Find Client] ? : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::enPFindClient;

		cout << "Do you Want to give access to [Transactions] ? : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::enPTransacions;

		cout << "Do you Want to give access to [Manage Users Menu] ? : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::enPManageUsers;

		cout << "Do you Want to give access to [Show Login Register] ? : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
			Permissions += clsUser::enPermissions::enPLoginRegister;

		return Permissions;
	}

public :

	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\tUpdate User Screen");

		string UserName = "";

		UserName = clsInbutValidate::ReadString("Enter User Name : ");

		while (!clsUser::IsUserExists(UserName))
		{
			cout << "\nInvalid User Name ... Please Enter a Valid One\n\n";
			UserName = clsInbutValidate::ReadString("Enter User Name : ");
		}

		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);

		char Answer = 'y';

		cout << "\nAre You Sure You Want To Update This User ? (y/Y) or (n/N) : ";
		cin >> Answer;

		if (tolower(Answer) == 'y')
		{
			cout << "\n\n    Update User Info :\n";
			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";

			_ReadUserInfo(User);

			clsUser::enSaveResults Result;
			Result = User.Save();

			switch (Result)
			{

			case clsUser::enSaveResults::SaveFailedEmptyObj:
			{
				cout << "\nError ... Cannot Save an empty object!";
				break;
			}

			case clsUser::enSaveResults::SaveSucceded:
			{
				cout << "\nSave Succeded! ... New Info about The User :\n\n";
				_PrintUser(User);
				break;
			}

			}
		}

		else
			cout << "\nUpdate Operation Was Cancelled ...";
	}
};

