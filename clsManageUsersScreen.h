#pragma once

#include <iostream>
#include <iomanip>
#include "clsInputValidate.h";
#include "clsScreen.h";
#include "clsUsersListScreen.h";
#include "clsAddNewUserScreen.h";
#include "clsDeleteUserScreen.h";
#include "clsUpdateUserScreen.h";
#include "clsFindUserScreen.h";

using namespace std;

class clsManageUsersScreen : protected clsScreen
{

private :

	enum enManageUsersMenuOption { enShowUsersList = 1,enAddNewUser = 2,enDeleteUser = 3
		, enUpdateUser = 4, enFindUser = 5, enMainMenu = 6
	};

	static short _ReadManageUsersMenuOption()
	{
		cout << left << setw(40) << "" << "Choose What You Want To Do Between[1-6] : ";
		short Choice = clsInbutValidate::ReadIntNumber("Invalid Number ... Please Enter a Valid One : ");

		return Choice;
	}

	static void _GoBackToMangeUsersMenu()
	{
		cout << "\n\t\tPress Any Key To Go Back To Manage Users Menu Screen ...";
		system("Pause>0");
		ShowManageUsersMenu();
	}

	static void _ShowUsersListScreen()
	{
		/*cout << "Show Users List Screen Will Be Here ...\n";*/

		clsUsersListScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		/*cout << "Show Add New User Screen Will Be Here ...\n";*/

		clsAddNewUserScreen::ShowAddNewClientScreen();
	}

	static void _ShowDeleteUsersScreen()
	{
		/*cout << "Show Delete Users Screen Will Be Here ...\n";*/

		clsDeleteUserScreen::ShowDeleteUserScreen();
	}

	static void _ShowUpdateUsersScreen()
	{
		/*cout << "Show Update Users Screen Will Be Here ...\n";*/

		clsUpdateUserScreen::ShowUpdateUserScreen();
	}

	static void _ShowFindUsersScreen()
	{
		/*cout << "Show Find Users Screen Will Be Here ...\n";*/

		clsFindUserScreen::ShowFindUserScreen();
	}

	static void _PerformManageUsersMenuOption(enManageUsersMenuOption Option)
	{
		switch (Option)
		{

		case enManageUsersMenuOption::enShowUsersList :
		{
			system("cls");
			_ShowUsersListScreen();
			_GoBackToMangeUsersMenu();
			break;
		}

		case enManageUsersMenuOption::enAddNewUser :
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToMangeUsersMenu();
			break;
		}

		case enManageUsersMenuOption::enDeleteUser :
		{
			system("cls");
			_ShowDeleteUsersScreen();
			_GoBackToMangeUsersMenu();
			break;
		}

		case enManageUsersMenuOption::enUpdateUser:
		{
			system("cls");
			_ShowUpdateUsersScreen();
			_GoBackToMangeUsersMenu();
			break;
		}

		case enManageUsersMenuOption::enFindUser :
		{
			system("cls");
			_ShowFindUsersScreen();
			_GoBackToMangeUsersMenu();
			break;
		}

		case enManageUsersMenuOption::enMainMenu:
		{
			// No Code Here ... Main Screen Will Complete the Task.
		}

		}
	}

public :

	static void ShowManageUsersMenu()
	{
		if (!_CheckAccessRights(clsUser::enPermissions::enPManageUsers))
		{
			return; //this will exit the function and back to main menu
		}

		system("cls");
		_DrawScreenHeader("\tManage Users Menu Screen");

		cout << setw(40) << left << "" << "==============================================================\n\n";
		cout << setw(40) << left << "" << "\t\t\tManage Users Menu\n\n";
		cout << setw(40) << left << "" << "==============================================================\n\n";

		cout << setw(40) << left << "" << "[1] : Show Users List.\n\n";
		cout << setw(40) << left << "" << "[2] : Add New User.\n\n";
		cout << setw(40) << left << "" << "[3] : Delete User.\n\n";
		cout << setw(40) << left << "" << "[4] : Update User.\n\n";
		cout << setw(40) << left << "" << "[5] : Find User.\n\n";
		cout << setw(40) << left << "" << "[6] : Main Menu.\n" << endl;

		cout << setw(40) << left << "" << "==============================================================\n\n";

		_PerformManageUsersMenuOption((enManageUsersMenuOption)_ReadManageUsersMenuOption());
	}

};

