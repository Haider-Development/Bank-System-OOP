#pragma once

#include <iostream>
#include <string>
#include "clsString.h";
#include <vector>
#include <fstream>

using namespace std;

class clsCurrency
{
private :

	enum enMode { enEmptyMode = 0, enUpdateMode = 1 };
	enMode _Mode;

	enum enWhichDollar { enFirstIsDollar = 1, enSecondIsDollar = 2, enSameCurrencyies = 3, enNoneIsDollar = 4 };

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static string _ConvertCurrencyObectToLine(clsCurrency Currency, string Separator = "#//#")
	{
		string DataLine = "";

		DataLine += Currency._Country + Separator;
		DataLine += Currency._CurrencyCode + Separator;
		DataLine += Currency._CurrencyName + Separator;
		DataLine += to_string(Currency.Rate);

		return DataLine;
	}

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
	{
		vector <string> _vCurrencies;
		_vCurrencies = clsString::vSplitString(Line, Separator);

		return clsCurrency(enMode::enUpdateMode, _vCurrencies[0], _vCurrencies[1], _vCurrencies[2], stof(_vCurrencies[3]));
	}

	static vector <clsCurrency> _LoadCurrecnciesDataFromFile()
	{
		vector <clsCurrency> _vCurrencies;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string DataLine;

			while (getline(MyFile, DataLine))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(DataLine);

				_vCurrencies.push_back(Currency);
			}

			MyFile.close();
		}

		return _vCurrencies;
	}

	static void _SaveCurrenciesDataToFile(vector <clsCurrency> _vCurrencies)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);

		if (MyFile.is_open())
		{
			string DataLine = "";

			for (clsCurrency& C : _vCurrencies)
			{
				DataLine = _ConvertCurrencyObectToLine(C);

				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> _vCurrencies;
		_vCurrencies = _LoadCurrecnciesDataFromFile();

		for (clsCurrency& C : _vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;

				_SaveCurrenciesDataToFile(_vCurrencies);
				return;
			}
		}
	}

	static enWhichDollar WhichDollar(clsCurrency Currency1, clsCurrency Currency2)
	{
		enWhichDollar Situation;

		if (Currency1.CurrencyCode() == "USD")
		{
			Situation = enWhichDollar::enFirstIsDollar;
			return Situation;
		}

		else if (Currency2.CurrencyCode() == "USD")
		{
			Situation = enWhichDollar::enSecondIsDollar;
			return Situation;
		}

		else if (Currency1.CurrencyCode() == Currency2.CurrencyCode())
		{
			Situation = enWhichDollar::enSameCurrencyies;
			return Situation;
		}

		else
			Situation = enWhichDollar::enNoneIsDollar;

		return Situation;
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::enEmptyMode, "", "", "", 0);
	}

public :

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::enEmptyMode;
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float GetRate()
	{
		return _Rate;
	}

	__declspec(property(get = GetRate, put = UpdateRate)) float Rate;

	static clsCurrency FindByCode(string CurrencyCode)
	{
		vector <clsCurrency> vCurrencies;
		vCurrencies = _LoadCurrecnciesDataFromFile();

		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		for (clsCurrency& C : vCurrencies)
		{
			if (clsString::UpperAllString(C.CurrencyCode()) == CurrencyCode)
			{
				clsCurrency Currency = C;
				return Currency;
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		vector <clsCurrency> vCurrencies;
		vCurrencies = _LoadCurrecnciesDataFromFile();

		Country = clsString::UpperAllString(Country);

		for (clsCurrency& C : vCurrencies)
		{
			if (clsString::UpperAllString(C.Country()) == Country)
			{
				clsCurrency Currency = C;
				return Currency;
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);

		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrencyiesList()
	{
		return _LoadCurrecnciesDataFromFile();
	}

	enum enFindMode { enCodeMode = 1, enCountryMode = 2, enBack = 3 };

	static clsCurrency PerformFindModeOption(string FindMethod, enFindMode Option)
	{
		switch (Option)
		{

		case enFindMode::enCodeMode :
		{
			return clsCurrency::FindByCode(FindMethod);
			break;
		}

		case enFindMode::enCountryMode :
		{
			return clsCurrency::FindByCountry(FindMethod);
			break;
		}

		case enFindMode::enBack :
		{

		}

		}
	}

	static float ConvertFromCrurrencyToAnother(clsCurrency Currency1, clsCurrency Currency2, float Amount)
	{
		float ConvertingAmount = 0;
		enWhichDollar Situation = WhichDollar(Currency1, Currency2);

		switch (Situation)
		{
		case enWhichDollar::enFirstIsDollar :
		{
			ConvertingAmount = Currency2.Rate * Amount;
			return ConvertingAmount;
			break;
		}

		case enWhichDollar::enSecondIsDollar :
		{
			ConvertingAmount = Amount / Currency1.Rate;
			return ConvertingAmount;
			break;
		}

		case enWhichDollar::enSameCurrencyies :
		{
			return Amount;
		}

		case enWhichDollar::enNoneIsDollar :
		{
			ConvertingAmount = Amount / Currency1.Rate;
			ConvertingAmount *= Currency2.Rate;
			return ConvertingAmount;
			break;
		}

		}
	}
};

