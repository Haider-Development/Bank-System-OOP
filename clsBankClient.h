#pragma once

#include <iostream>
#include "clsPerson.h";
#include "clsString.h";
#include "clsDate.h";
#include <string>
#include <cctype>
#include <vector>
#include <fstream>
#include "Global.h";

using namespace std;

class clsBankClient : public clsPerson
{
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector <string> vClients = clsString::vSplitString(Line, Separator);

		return clsBankClient(enMode::UpdateMode, vClients[0], vClients[1], vClients[2], vClients[3], vClients[4], vClients[5],
			stod(vClients[6]));
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		string DataLine = "";

		DataLine += Client.FirstName + Separator;
		DataLine += Client.LastName + Separator;
		DataLine += Client.Email + Separator;
		DataLine += Client.PhoneNumber + Separator;
		DataLine += Client.AccountNumber() + Separator;
		DataLine += Client.PinCode + Separator;
		DataLine += to_string(Client.AccountBalance);

		return DataLine;
	}

	bool _IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		vector <clsBankClient> _vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				clsBankClient Client = _ConvertLineToClientObject(DataLine);

				_vClients.push_back(Client);
			}

			MyFile.close();
		}

		return _vClients;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine = "";

			for (clsBankClient& C : vClients)
			{
				if (C._MarkForDelete == false)
				{
					DataLine = _ConvertClientObjectToLine(C);

					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClients;
		_vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string DateLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << DateLine << endl;

			MyFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	string _ConvertTransferLogToLine(float Amount, clsBankClient Client, string Separator = "#//#")
	{
		string DataLine = "";

		string Date = clsDate::FormatDate(clsDate(), "dd/mm/yyyy");
		string Time = clsDate::CurrentTime();

		DataLine += Date + " - " + Time + Separator;
		DataLine += AccountNumber() + Separator;
		DataLine += Client.AccountNumber() + Separator;
		DataLine += to_string(Amount) + Separator;
		DataLine += to_string(AccountBalance) + Separator;
		DataLine += to_string(Client.AccountBalance) + Separator;
		DataLine += CurrentUser.UserName;

		return DataLine;
	}

	void _SaveTransferLogToFile(float Amount, clsBankClient Client)
	{
		fstream MyFile;
		MyFile.open("Transfer Log.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			string DataLine = _ConvertTransferLogToLine(Amount, Client);

			MyFile << DataLine << endl;

			MyFile.close();
		}
	}

	struct stTransferLog;

	static stTransferLog _ConvertLineToTransferLog(string Line, string Separator="#//#")
	{
		stTransferLog TransferLog;

		vector <string> _vTransferLogs;
		_vTransferLogs = clsString::vSplitString(Line, Separator);

		TransferLog.DateAndTime = _vTransferLogs[0];
		TransferLog.SAccountNumber = _vTransferLogs[1];
		TransferLog.DAccountNumber = _vTransferLogs[2];
		TransferLog.Amount = stod(_vTransferLogs[3]);
		TransferLog.SAccountBalance = stod(_vTransferLogs[4]);
		TransferLog.DAccountBalance = stod(_vTransferLogs[5]);
		TransferLog.User = _vTransferLogs[6];

		return TransferLog;
	}

public:

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string PhoneNumber, string AccountNumber, string PinCode, double AccountBalance)
		: clsPerson(FirstName, LastName, Email, PhoneNumber)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

	static clsBankClient GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	struct stTransferLog
	{
		string DateAndTime;
		string SAccountNumber;
		string DAccountNumber;
		float Amount;
		float SAccountBalance;
		float DAccountBalance;
		string User;
	};

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	string GetPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(double AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	double GetAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))double AccountBalance;

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

			}

			MyFile.close();

		}

		return GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client._AccountNumber == AccountNumber && Client._PinCode == PinCode)
				{
					MyFile.close();

					return Client;
				}
			}

			MyFile.close();
		}

		return GetEmptyClientObject();
	}

	static bool IsClientExists(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client._IsEmpty());
	}

	enum enSaveResults { SaveFailedEmptyObj = 0, SaveSucceded = 1, SaveFailedAccNumExist = 2 };

	static clsBankClient GetAddNewClientObj(string AccountNumber)
	{
		return clsBankClient(AddNewMode, "", "", "", "", AccountNumber, "", 0);
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
			if (clsBankClient::IsClientExists(AccountNumber()))
				return enSaveResults::SaveFailedAccNumExist;

			_AddNew();
			return enSaveResults::SaveSucceded;
		}

		}
	}

	bool Delete()
	{
		vector <clsBankClient> vClients;
		vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = GetEmptyClientObject();

		return true;
	}

	static vector <clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector <clsBankClient> vClients;
		vClients = GetClientsList();

		double TotalBalances = 0;

		for (clsBankClient& C : vClients)
		{
			TotalBalances += C.AccountBalance;
		}

		return TotalBalances;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > AccountBalance)
			return false;

		else
		{
			AccountBalance -= Amount;
			Save();
		}
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient)
	{
		if (Amount > AccountBalance)
			return false;

		else
		{
			Withdraw(Amount);
			DestinationClient.Deposit(Amount);

			_SaveTransferLogToFile(Amount, DestinationClient);
		}
	}

	static vector <stTransferLog> GetTransferLogList()
	{
		vector <stTransferLog> vTransferLog;
		
		fstream MyFile;
		MyFile.open("Transfer Log.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;
			stTransferLog TransferLog;

			while (getline(MyFile, DataLine))
			{
				TransferLog = _ConvertLineToTransferLog(DataLine);

				vTransferLog.push_back(TransferLog);
			}

			MyFile.close();
		}

		return vTransferLog;
	}
};

