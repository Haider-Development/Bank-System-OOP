#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsFirstAdmin : protected clsScreen
{
	static void _ReadAdminInfo(clsUser& User)
	{
		User.FirstName = clsInbutValidate::ReadString("\nEnter First Name      : ");
		User.LastName = clsInbutValidate::ReadString("\nEnter Last Name       : ");
		User.Email = clsInbutValidate::ReadString("\nEnter Email           : ");
		User.PhoneNumber = clsInbutValidate::ReadString("\nEnter Phone Number    : ");
		User.Password = clsInbutValidate::ReadString("\nEnter Password        : ");

		User.Permissions = -1;
	}

	static void _PrintAdmin(clsUser User)
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

	static void ShowAddFirstAdminScreen()
	{
		system("cls");
		_DrawScreenHeader("\tAdd First Admin Screen");

		cout << "You Are the First User in the System!\n";
		cout << "Note that your Username will be {Admin} and you will be full access on the System.\n";

		string UserName = "";

		UserName = "Admin";

		clsUser NewUser = clsUser::GetAddNewUserObj(UserName);

		_ReadAdminInfo(NewUser);

		clsUser::enSaveResults Result;
		Result = NewUser.Save();

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
			_PrintAdmin(NewUser);
			break;
		}

		case clsUser::enSaveResults::SaveFailedUsrNameExist:
		{
			cout << "\nError ... Cannot Save User Name Already in Use!";
			break;
		}

		}
	}
};

