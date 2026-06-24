#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include "clsUser.h";
#include "clsScreen.h";

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _PrintUsersLoginRegisterLine(clsUser::stLoginRegister User)
	{
		cout << left << setw(7) << "";
		cout << " | " << left << setw(20) << User.DateAndTime;
		cout << " | " << left << setw(14) << User.UserName;
		cout << " | " << left << setw(20) << User.Password;
		cout << " | " << left << setw(10) << User.Permissions;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::enPLoginRegister))
		{
			return; //this will exit the function and back to main menu
		}

		vector <clsUser::stLoginRegister> vUsers;
		vUsers = clsUser::GetLoginRegisterUsersList();

		_DrawScreenHeader("\tLogin Register Screen", "\t[" + to_string(vUsers.size()) + "] Login(s)");

		cout << left << setw(7) << "" << "-------------------------------------------------------------------------------------------------------------------------------------------\n";
		cout << left << setw(7) << "" << " | " << left << setw(20) << "Date And Time";
		cout << " | " << left << setw(14) << "User Name";
		cout << " | " << left << setw(20) << "Password";
		cout << " | " << left << setw(10) << "Permissions";

		cout << "\n" << endl;

		if (vUsers.empty())
			cout << "\n\n" << setw(50) << left << "" << "No Logins Available in The System.";

		else
			for (clsUser::stLoginRegister& User : vUsers)
			{
				_PrintUsersLoginRegisterLine(User);
				cout << endl;
			}

		cout << "\n" << left << setw(7) << "";
		cout << "---------------------------------------------------------------------------------------------------------------------------------------------\n";

	}
};

