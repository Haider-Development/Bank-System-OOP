#pragma once

#include <iostream>
#include "clsScreen.h";
#include "clsUser.h";
#include <iomanip>

using namespace std;

class clsUsersListScreen : protected clsScreen
{
private:

	static void _PrintUsersRecordLine(clsUser User)
	{
		cout << left << setw(7) << "";
		cout << " | " << left << setw(14) << User.UserName;
		cout << " | " << left << setw(22) << User.FullName();
		cout << " | " << left << setw(30) << User.Email;
		cout << " | " << left << setw(18) << User.PhoneNumber;
		cout << " | " << left << setw(20) << User.Password;
		cout << " | " << left << setw(10) << User.Permissions;
	}

public:

	static void ShowUsersList()
	{
		vector <clsUser> vUsers;
		vUsers = clsUser::GetUsersList();

		_DrawScreenHeader("\tUsers List", "\t[" + to_string(vUsers.size()) + "] User(s)");

		cout << left << setw(7) << "" << "-------------------------------------------------------------------------------------------------------------------------------------------\n";
		cout << left << setw(7) << "" << " | " << left << setw(14) << "User Name";
		cout << " | " << left << setw(22) << "Full Name";
		cout << " | " << left << setw(30) << "Email";
		cout << " | " << left << setw(18) << "Phone Number";
		cout << " | " << left << setw(20) << "Password";
		cout << " | " << left << setw(10) << "Permissions";

		cout << "\n" << endl;

		if (vUsers.empty())
			cout << "\n\n" << setw(50) << left << "" << "No Users Available in The System.";

		else
			for (clsUser& User : vUsers)
			{
				_PrintUsersRecordLine(User);
				cout << endl;
			}

		cout << "\n" << left << setw(7) << "";
		cout << "---------------------------------------------------------------------------------------------------------------------------------------------\n";

	}
};

