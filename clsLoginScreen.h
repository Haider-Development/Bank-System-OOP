#pragma warning (disable : 4996);
#pragma once

#include <iostream>
#include "iomanip"
#include "clsUser.h";
#include "clsMainScreen.h";
#include "clsScreen.h";
#include "clsInputValidate.h";
#include "Global.h";
#include "clsFirstAdmin.h"


using namespace std;

class clsLoginScreen : protected clsScreen
{
private :

	static short _FailedLoginCounter;

	static void _Login()
	{
		bool LoginFailed = false;
		string UserName, Password;
		vector <clsUser> vUsers = clsUser::GetUsersList();

		if (vUsers.empty())
		{
			clsFirstAdmin::ShowAddFirstAdminScreen();
			CurrentUser = clsUser::Find("Admin");
			cout << "\n\n\t\t\tPress any Key to confirm you are ready to enter the System ...";
			system("Pause>0");

			clsMainScreen::ShowMainMenu();
		}

		else
		{
			do
			{

				UserName = clsInbutValidate::ReadString("Please Enter User Name : ");
				Password = clsInbutValidate::ReadString("Please Enter Password : ");

				CurrentUser = clsUser::Find(UserName, Password);

				LoginFailed = CurrentUser.IsEmpty();

				if (LoginFailed)
				{
					_FailedLoginCounter--;
					cout << "\nInvalid User Name / Password !\n";
					cout << "You Have " << _FailedLoginCounter << " Trials To Login.\n\n";
				}

				if (!LoginFailed)
				{
					CurrentUser.SaveLoginRegisterToFile();
				}

			} while (LoginFailed && _FailedLoginCounter > 0);

			if (_FailedLoginCounter != 0)
				clsMainScreen::ShowMainMenu();
		}
	}

	//Another Way To Solve extension 2 : [ lock the system after 3 failed login ]

	/*static bool _Login() _ [ and public methode should return bool ]
	{
	    _FailedLoginCounter = 3; (not a static member)
		bool LoginFailed = false;
		string UserName, Password;

		do
		{

			UserName = clsInbutValidate::ReadString("Please Enter User Name : ");
			Password = clsInbutValidate::ReadString("Please Enter Password : ");

			CurrentUser = clsUser::Find(UserName, Password);

			LoginFailed = CurrentUser.IsEmpty();

			if (LoginFailed)
			{
				_FailedLoginCounter--;
				cout << "\nInvalid User Name / Password !\n";
				cout << "You Have " << _FailedLoginCounter << " Trials To Login.\n\n";
			}

			if (_FailedLoginCounter = 0)
			{
			   cout << "You are locked after 3 failed login.\n";
			   return false;
			}

		} while (LoginFailed && _FailedLoginCounter > 0);

		clsMainScreen::ShowMainMenu();
	}*/

	// and in main function we but this condition :
	/*if (!clsLoginScreen::ShowLoginScreen())
	{
		break;
	}*/

public :

	static void ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\tLogin Screen");
		_Login();
	}

	static short GetFailedLoginCounter()
	{
		return _FailedLoginCounter;
	}

	static void SetFailedLoginCounter(short Counter)
	{
		_FailedLoginCounter = Counter;
	}
};

short clsLoginScreen::_FailedLoginCounter = 3;
