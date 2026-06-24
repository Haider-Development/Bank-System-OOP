#pragma once

#include <iostream>
#include "clsUser.h";
#include "clsDate.h";
#include "Global.h";

using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "\t\t\t\t\t-------------------------------------------------------------------\n\n";
		cout << "\t\t\t\t\t\t\t" << Title << "\n";

		if (SubTitle != "")
		{
			cout << "\t\t\t\t\t\t\t" << SubTitle << "\n\n";
		}
		cout << "\t\t\t\t\t-------------------------------------------------------------------\n\n";

		cout << "\t\t\t\t\t\t\t\tUser : " << CurrentUser.UserName;
		cout << "\n\t\t\t\t\t\t\t\tDate : " << clsDate::FormatDate(clsDate(), "dd/mm/yyyy") << "\n\n";
	}

	static bool _CheckAccessRights(clsUser::enPermissions Permission)
	{
		if (!CurrentUser.CheckAccessPermissions(Permission))
		{
			cout << "\t\t\t\t\t-------------------------------------------------------------------\n\n";
			cout << "\t\t\t\t\t\t\t" << "Access Denied ! ... Please Contact Your Admin.\n" << endl;
			cout << "\t\t\t\t\t-------------------------------------------------------------------\n\n";
			return false;
		}

		else
			return true;
	}
};

