#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h";
#include "clsString.h";
#include "clsDate.h";
#include "clsUtil.h";
#include <vector>
#include <fstream>

using namespace std;

class clsUser : public clsPerson
{
private :

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _UserName;
	string _Password;
	int _Permissions;

	bool _MarkForDelete = false;

	static clsUser _ConvertLineToUserObject(string Line, string Separator = "#//#")
	{
		vector <string> vClients = clsString::vSplitString(Line, Separator);

		return clsUser(enMode::UpdateMode, vClients[0], vClients[1], vClients[2], vClients[3], vClients[4], vClients[5],
			stod(vClients[6]));
	}

	static string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
	{
		string DataLine = "";

		DataLine += User.FirstName + Separator;
		DataLine += User.LastName + Separator;
		DataLine += User.Email + Separator;
		DataLine += User.PhoneNumber + Separator;
		DataLine += User.UserName + Separator;
		DataLine += clsUtil::Encryption(User.Password, 10) + Separator;
		DataLine += to_string(User.Permissions);

		return DataLine;
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		vector <clsUser> _vUsers;

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				clsUser User = _ConvertLineToUserObject(DataLine);

				User.Password = clsUtil::Decryption(User.Password, 10);

				_vUsers.push_back(User);
			}

			MyFile.close();
		}

		return _vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine = "";

			for (clsUser& U : vUsers)
			{
				if (U._MarkForDelete == false)
				{
					U.Password = clsUtil::Encryption(U.Password, 10);

					DataLine = _ConvertUserObjectToLine(U);

					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> _vClients;
		_vClients = _LoadUsersDataFromFile();

		for (clsUser& U : _vClients)
		{
			if (U.UserName == UserName)
			{
				U = *this;
				break;
			}
		}

		_SaveUsersDataToFile(_vClients);
	}

	static void _AddDataLineToFile(string DateLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DateLine << endl;

			MyFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	string _ConvertLoginRegisterToLine(string Separator = "#//#")
	{
		string Line = "";

		string Date = clsDate::FormatDate(clsDate(), "dd/mm/yyyy");
		string Time = clsDate::CurrentTime();

		Line += Date + " - ";
		Line += Time + Separator;
		Line += UserName + Separator;
		Line += Password + Separator;
		Line += to_string(Permissions);

		return Line;
	}

	struct stLoginRegister;

	static stLoginRegister _ConvertLineToLoginRegisterObject(string DataLine, string Separator = "#//#")
	{
		vector <string> _vLoginRegisterParts;
		_vLoginRegisterParts = clsString::vSplitString(DataLine, Separator);

		stLoginRegister LoginRegister;

		LoginRegister.DateAndTime = _vLoginRegisterParts[0];
		LoginRegister.UserName = _vLoginRegisterParts[1];
		LoginRegister.Password = _vLoginRegisterParts[2];
		LoginRegister.Permissions = stoi(_vLoginRegisterParts[3]);
		
		return LoginRegister;
	}

	static vector <stLoginRegister> _LoadLoginRegisterUsersDataFromFile()
	{
		vector <stLoginRegister> _vUsers;

		fstream MyFile;
		MyFile.open("Login Register.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				stLoginRegister User = _ConvertLineToLoginRegisterObject(DataLine);

				User.Password = clsUtil::Decryption(User.Password, 10);

				_vUsers.push_back(User);
			}

			MyFile.close();
		}

		return _vUsers;
	}

public :

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber, string UserName, string PassWord, int Permissions) 
		: clsPerson(FirstName, LastName, Email, PhoneNumber)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = PassWord;
		_Permissions = Permissions;
	}

	struct stLoginRegister
	{
		string DateAndTime;
		string UserName;
		string Password;
		int Permissions;
	};

	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}

	string GetUserName()
	{
		return _UserName;
	}

	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	string GetPassword()
	{
		return _Password;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}

	int GetPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				if (User.UserName == UserName)
				{
					MyFile.close();

					User.Password = clsUtil::Decryption(User.Password, 10);
					return User;
				}

			}

			MyFile.close();

		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);

				string DecryptedPassword = clsUtil::Decryption(User.Password, 10);

				if (User.UserName == UserName &&  DecryptedPassword == Password)
				{
					MyFile.close();

					return User;
				}
			}

			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool IsUserExists(string UserName)
	{
		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());
	}

	enum enSaveResults { SaveFailedEmptyObj = 0, SaveSucceded = 1, SaveFailedUsrNameExist = 2 };

	static clsUser GetAddNewUserObj(string UserName)
	{
		return clsUser(AddNewMode, "", "", "", "", UserName, "", 0);
	}

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case enMode::EmptyMode:
		{
			return enSaveResults::SaveFailedEmptyObj;
			break;
		}

		case enMode::UpdateMode:
		{
			_Update();

			return enSaveResults::SaveSucceded;
			break;
		}

		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExists(UserName))
				return enSaveResults::SaveFailedUsrNameExist;

			_AddNew();
			return enSaveResults::SaveSucceded;
		}

		}
	}

	bool Delete()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.UserName == UserName)
			{
				U._MarkForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUsersDataFromFile();
	}
	
	enum enPermissions {
		enAll = -1, enPShowClientsList = 1, enPAddNewClient = 2, enPDeleteClient = 4,
		enPUpdateClient = 8, enPFindClient = 16, enPTransacions = 32, enPManageUsers = 64,
		enPLoginRegister = 128
	};

	bool CheckAccessPermissions(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::enAll)
			return true;

		if ((Permission & this->Permissions) == Permission)
			return true;

		return false;
	}

	void SaveLoginRegisterToFile()
	{
		string DataLine = _ConvertLoginRegisterToLine();

		fstream MyFile;
		MyFile.open("Login Register.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	static vector <stLoginRegister> GetLoginRegisterUsersList()
	{
		return _LoadLoginRegisterUsersDataFromFile();
	}

	static void AddFirstAdmin()
	{

	}
};

