//Instead Of void functions we can declare object functions and it will return object same as structure
//no difference because classes and objects are data types

#pragma once
#pragma warning(disable : 4996);

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include "clsString.h";

using namespace std;

enum class enCompareDates { eBefore = -1, eEqual = 0, eAfter = 1 };

class clsDate
{
	vector <string> vWords;

	short _Day;
	short _Month;
	short _Year;

	void DateFromDayOrderInYear(short NumberOfDays, short Year)
	{
		short RemainingDays = NumberOfDays;
		short Month = 1;

		while (RemainingDays > NumberOfDaysInAMonth(Month, Year))
		{
			RemainingDays -= NumberOfDaysInAMonth(Month, Year);
			Month += 1;
		}

		_Day = RemainingDays;
		_Month = Month;
		_Year = Year;
	}

	string UnderScore(short Number)
	{
		string Unscore = "";

		for (short i = 0; i < Number; i++)
		{
			Unscore += "_";
		}

		return Unscore;
	}

	void SystemDate()
	{
		time_t t = time(0);
		tm* Now = localtime(&t);

		_Day = Now->tm_mday;
		_Month = Now->tm_mon + 1;
		_Year = Now->tm_year + 1900;
	}

	void AccurateDays(clsDate& Date)
	{
		short NumberOfDaysInCurrentMonth = NumberOfDaysInAMonth(Date._Month, Date._Year);

		if (Date._Day > NumberOfDaysInCurrentMonth)
		{
			Date._Day = NumberOfDaysInCurrentMonth;
		}
	}

	bool IsFirstDayInAMonth(short Day)
	{
		return Day == 1;
	}

	bool IsFirstMonthInAYear(short Month)
	{
		return Month == 1;
	}

	string _ReplaceWordInString(string StringToEdit, string StringToReplace, string ReplaceTo)
	{
		short Pos = StringToEdit.find(StringToReplace);

		while (Pos != string::npos)
		{
			StringToEdit = StringToEdit.replace(Pos, StringToReplace.length(), ReplaceTo);

			Pos = StringToEdit.find(StringToReplace);
		}

		return StringToEdit;
	}

public:

	clsDate()
	{
		SystemDate();
	}

	clsDate(string Date)
	{
		ConvertStringToDate(Date);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DaysFromTheBeginningOfTheYear, short Year)
	{
		DateFromDayOrderInYear(DaysFromTheBeginningOfTheYear, Year);
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}

	short GetDay()
	{
		return _Day;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;

	void SetMonth(short Month)
	{
		_Month = Month;
	}

	short GetMonth()
	{
		return _Month;
	}

	__declspec(property(get = GetMonth, put = SetMonth)) short Month;

	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetYear()
	{
		return _Year;
	}

	__declspec(property(get = GetYear, put = SetYear)) short Year;

	static short DayOfWeekOrder(short Day, short Month, short Year)
	{
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + (12 * a) - 2;

		// Gregorian
		// // 0:sunday, 1:monday, 2:tuesday....etc
		return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}

	static bool IsYearLeap(short Year)
	{
		return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
	}

	static short NumberOfDaysInAMonth(short Month, short Year)
	{
		if (Month < 1 || Month>12)
		{
			return 0;
		}

		return (Month == 2) ? ((IsYearLeap(Year)) ? 29 : 28) :
			((Month < 8 && Month % 2 != 0) || (Month > 7 && Month % 2 == 0)) ? 31 : 30;
	}

	void Print()
	{
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}

	void ConvertStringToDate(string Date)
	{
		vWords = clsString::vSplitString(Date, "/");
		_Day = stoi(vWords[0]);
		_Month = stoi(vWords[1]);
		_Year = stoi(vWords[2]);
	}

	static string ConvertDateToString(clsDate Date, string Separator = "/")
	{
		string sDate = "";

		sDate += to_string(Date._Day) + Separator;
		sDate += to_string(Date._Month) + Separator;
		sDate += to_string(Date._Year);

		return sDate;
	}

	static string NumberToText(int number)
	{
		if (number == 0)
		{
			return "zero";
		}

		else
		{
			if (number >= 1 && number <= 19)
			{
				string arr[] = { "","One","Two","Three" ,"Four" ,"Five" ,"Six", "Seven" ,"Eight" ,"Nine" ,
								"Ten" ,"Eleven","Twelve" ,"Thirteen" ,"Fourteen" ,"Fifteen" ,
								"Sixteen" ,"Seventeen" ,"Eighteen" ,"Nineteen" };

				return arr[number];
			}

			if (number >= 20 && number <= 99)
			{
				string arr[] = { "","","Twenty ","Thirty ","Forty ","Fifty ","Sixty ","Seventy ","Eighty ","Ninety " };

				return arr[number / 10] + NumberToText(number % 10);
			}

			if (number >= 100 && number <= 199)
			{
				return "One Hundred " + NumberToText(number % 100);
			}

			if (number >= 200 && number <= 999)
			{
				return NumberToText(number / 100) + " Hundreds " + NumberToText(number % 100);
			}

			if (number >= 1000 && number <= 1999)
			{
				return "One Thousand " + NumberToText(number % 1000);
			}

			if (number >= 2000 && number <= 99999)
			{
				return NumberToText(number / 1000) + " Thousands " + NumberToText(number % 1000);
			}

			if (number >= 100000 && number <= 199999)
			{
				return "One Hundred Thousand " + NumberToText(number % 100000);
			}

			if (number >= 200000 && number <= 999999)
			{
				return NumberToText(number / 100000) + " Thousands " + NumberToText(number % 100000);
			}

			if (number >= 1000000 && number <= 1999999)
			{
				return "One Million " + NumberToText(number % 1000000);
			}

			if (number >= 2000000 && number <= 999999999)
			{
				return NumberToText(number / 1000000) + " Millions " + NumberToText(number % 1000000);
			}

			if (number >= 1000000000 && number <= 1999999999)
			{
				return "One Billion  " + NumberToText(number % 1000000000);
			}

			if (number >= 2000000000 && number <= 999999999999)
			{
				return NumberToText(number / 1000000000) + " Billions " + NumberToText(number % 1000000000);
			}
		}
	}

	static short NumberOfDaysInAYear(int Year)
	{
		return (IsYearLeap(Year)) ? 366 : 365;
	}

	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}

	static short NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}

	static short NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}

	static short NumberOfHoursInAMonth(short Year, short Month)
	{
		return NumberOfDaysInAMonth(Year, Month) * 24;
	}

	static int NumberOfMinutesInAMonth(short Year, short Month)
	{
		return NumberOfHoursInAMonth(Year, Month) * 60;
	}

	static int NumberOfSecondsInAMonth(short Year, short Month)
	{
		return NumberOfMinutesInAMonth(Year, Month) * 60;
	}

	static string DayOfWeekName(clsDate Date)
	{
		string arrDayNames[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };

		return arrDayNames[Date.DayOfWeekOrder(Date._Day, Date._Month, Date._Year)];
	}

	string DayOfWeekName()
	{
		return DayOfWeekName(*this);
	}

	static void PrintMonthCalendar(short Month, short Year, clsDate Date = clsDate())
	{
		short MonthDays = NumberOfDaysInAMonth(Month, Year);
		string ArrWeekDays[] = { "Sun","Mon","Tus","Wed","Thurs","Fri","Sat" };
		string ArrMonthName[] = { "jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };

		cout << "\n " << Date.UnderScore(20);
		cout << ArrMonthName[Month - 1];
		cout << Date.UnderScore(20) << "\n\n ";

		for (string Day : ArrWeekDays)
		{
			cout << left << setw(5) << Day << "  ";
		}

		cout << endl;

		short counter = 0;

		while (true)
		{
			if (ArrWeekDays[DayOfWeekOrder(1, Month, Year)] != ArrWeekDays[counter])
			{
				cout << "       ";
			}


			else
				break;

			counter++;
		}

		for (short i = 0; i < MonthDays; i++)
		{
			cout << " " << left << setw(6) << i + 1;

			if (DayOfWeekOrder(i + 1, Month, Year) == 6)
			{
				cout << endl;
			}
		}

		cout << "\n " << Date.UnderScore(43) << endl;
	}

	void PrintMonthCalendar()
	{
		PrintMonthCalendar(this->_Month, this->_Year);
	}

	static void PrintYearCalendar(short Year)
	{
		printf("\n    ______________________________________\n\n");
		printf("              Calendar - %d\n", Year);
		printf("    ______________________________________\n");

		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}
	}

	void PrintYearCalendar()
	{
		PrintYearCalendar(this->_Year);
	}

	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year)
	{
		short TotalDays = 0;

		for (short i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInAMonth(i, Year);
		}

		TotalDays += Day;

		return TotalDays;
	}

	short NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
	}

	static void GetDateFromDayOrderInYear(short NumberOfDays, short Year)
	{
		short RemainingDays = NumberOfDays;
		short Month = 1;

		while (RemainingDays > NumberOfDaysInAMonth(Month, Year))
		{
			RemainingDays -= NumberOfDaysInAMonth(Month, Year);
			Month += 1;
		}

		cout << "Day : " << RemainingDays;
		cout << "\nMonth : " << Month;
		cout << "\nYear : " << Year;
	}

	static void DateAddDays(short DaysToAdd, clsDate& Date)
	{
		short RemainingDays = DaysToAdd + NumberOfDaysFromTheBeginingOfTheYear(Date._Day, Date._Month, Date._Year);
		short MonthDays = 0;
		Date._Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInAMonth(Date._Month, Date._Year);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date._Month += 1;

				if (Date._Month > 12)
				{
					Date._Year += 1;
					Date._Month = 1;
				}
			}

			else
			{
				Date._Day = RemainingDays;
				break;
			}
		}
	}

	void DateAddDays(short DaysToAdd)
	{
		DateAddDays(DaysToAdd, *this);
	}

	static bool IsDate1Lower(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year < Date2._Year) ? true : ((Date1._Year == Date2._Year) ?
			(Date1._Month < Date2._Month ? true : (Date1._Month == Date2._Month ?
				Date1._Day < Date2._Day : false)) : false);
	}

	bool IsDate1Lower(clsDate Date)
	{
		return IsDate1Lower(*this, Date);
	}

	static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1._Year == Date2._Year) ? ((Date1._Month == Date2._Month) ? Date1._Day == Date2._Day : false) : false;
	}

	bool IsDate1EqualToDate2(clsDate Date)
	{
		return IsDate1EqualToDate2(*this, Date);
	}

	static bool IsLastDay(short Day, short Month, short Year)
	{
		return Day == NumberOfDaysInAMonth(Month, Year);
	}

	bool IsLastDay()
	{
		return IsLastDay(_Day, _Month, _Year);
	}

	static bool IsLastMonth(short Month)
	{
		return Month == 12;
	}

	bool IsLastMonth()
	{
		return IsLastMonth(_Month);
	}

	static void IncreaseDateByOneDay(clsDate& Date)
	{
		if (IsLastDay(Date._Day, Date._Month, Date._Year))
		{

			if (IsLastMonth(Date._Month))
			{
				Date._Year += 1;
				Date._Month = 1;
				Date._Day = 1;
			}

			else
			{
				Date._Day = 1;
				Date._Month += 1;
			}
		}

		else
		{
			Date._Day += 1;
		}
	}

	void IncreaseDateByOneDay()
	{
		IncreaseDateByOneDay(*this);
	}

	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate Date;

		Date._Day = Date1._Day;
		Date._Month = Date1._Month;
		Date._Year = Date1._Year;

		Date1._Day = Date2._Day;
		Date1._Month = Date2._Month;
		Date1._Year = Date2._Year;

		Date2._Day = Date._Day;
		Date2._Month = Date._Month;
		Date2._Year = Date._Year;
	}

	void SwapDates(clsDate& Date)
	{
		SwapDates(*this, Date);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short SwapFlagValue = 1;

		if (!IsDate1Lower(Date1, Date2))
		{
			Date1.SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (IsDate1Lower(Date1, Date2))
		{
			Days += 1;
			IncreaseDateByOneDay(Date1);
		}

		return (IncludeEndDay) ? (++Days) * SwapFlagValue : Days * SwapFlagValue;
	}

	int GetDifferenceInDays(clsDate Date, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date, IncludeEndDay);
	}

	static int YourAgeInDays(clsDate BirthDate, bool IncludeEndDay = false)
	{
		clsDate SysDate;
		SysDate.SystemDate();

		return GetDifferenceInDays(BirthDate, SysDate, IncludeEndDay);
	}

	static void IncreaseDateByXDays(clsDate& Date, short NumberOfDays)
	{
		for (short i = 1; i <= NumberOfDays; i++)
		{
			IncreaseDateByOneDay(Date);
		}
	}

	void IncreaseDateByXDays(short NumberOfDays)
	{
		IncreaseDateByXDays(*this, NumberOfDays);
	}

	static void IncreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			IncreaseDateByOneDay(Date);
		}
	}

	void IncreaseDateByOneWeek()
	{
		IncreaseDateByOneWeek(*this);
	}

	static void IncreaseDateByXWeeks(clsDate& Date, short NumberOfWeeks)
	{
		for (short i = 1; i <= NumberOfWeeks; i++)
		{
			IncreaseDateByOneWeek(Date);
		}
	}

	void IncreaseDateByXWeeks(short NumberOfWeeks)
	{
		IncreaseDateByXWeeks(*this, NumberOfWeeks);
	}

	static void IncreaseDateByOneMonth(clsDate& Date)
	{
		if (IsLastMonth(Date._Month))
		{
			Date._Month = 1;
			Date._Year += 1;
		}

		else
		{
			Date._Month += 1;
		}

		Date.AccurateDays(Date);
	}

	void IncreaseDateByOneMonth()
	{
		IncreaseDateByOneMonth(*this);
	}

	static void IncreaseDateByXMonths(clsDate& Date, short NumberOfMonths)
	{
		for (short i = 1; i <= NumberOfMonths; i++)
		{
			IncreaseDateByOneMonth(Date);
		}
	}

	void IncreaseDateByXMonths(short NumberOfMonths)
	{
		IncreaseDateByXMonths(*this, NumberOfMonths);
	}

	static void IncreaseDateByOneYear(clsDate& Date)
	{
		Date._Year += 1;

		Date.AccurateDays(Date);
	}

	void IncreaseDateByOneYear()
	{
		IncreaseDateByOneYear(*this);
	}

	static void IncreaseDateByXYears(clsDate& Date, short NumberOfYears)
	{
		for (short i = 1; i <= NumberOfYears; i++)
		{
			IncreaseDateByOneYear(Date);
		}

		Date.AccurateDays(Date);
	}

	void IncreaseDateByXYears(short NumberOfYears)
	{
		IncreaseDateByXYears(*this, NumberOfYears);
	}

	static void IncreaseDateByXYearsFaster(clsDate& Date, short NumberOfYears)
	{
		Date._Year += NumberOfYears;
		Date.AccurateDays(Date);
	}

	void IncreaseDateByXYearsFaster(short NumberOfYears)
	{
		IncreaseDateByXYearsFaster(*this, NumberOfYears);
	}

	static void IncreaseDateByOneDecade(clsDate& Date)
	{
		Date._Year += 10;
		Date.AccurateDays(Date);
	}

	void IncreaseDateByOneDecade()
	{
		IncreaseDateByOneDecade(*this);
	}

	static void IncreaseDateByXDecades(clsDate& Date, short NumberOfDecades)
	{
		for (short i = 1; i <= NumberOfDecades; i++)
		{
			IncreaseDateByOneDecade(Date);
		}

		Date.AccurateDays(Date);
	}

	void IncreaseDateByXDecades(short NumberOfDecades)
	{
		IncreaseDateByXDecades(*this, NumberOfDecades);
	}

	static void IncreaseDateByXDecadesFaster(clsDate& Date, short NumberOfDecades)
	{
		Date._Year += NumberOfDecades * 10;
		Date.AccurateDays(Date);
	}

	void IncreaseDateByXDecadesFaster(short NumberOfDecades)
	{
		IncreaseDateByXDecadesFaster(*this, NumberOfDecades);
	}

	static void IncreaseDateByOneCentury(clsDate& Date)
	{
		Date._Year += 100;
		Date.AccurateDays(Date);
	}

	void IncreaseDateByOneCentury()
	{
		IncreaseDateByOneCentury(*this);
	}

	static void IncreaseDateByOneMillenium(clsDate& Date)
	{
		Date._Year += 1000;
		Date.AccurateDays(Date);
	}

	void IncreaseDateByOneMillenium()
	{
		IncreaseDateByOneMillenium(*this);
	}

	static void DecreaseDateByOneDay(clsDate& Date)
	{
		if (Date.IsFirstDayInAMonth(Date._Day))
		{
			if (Date.IsFirstMonthInAYear(Date._Month))
			{
				Date._Year -= 1;
				Date._Month = 12;
				Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
			}

			else
			{
				Date._Month -= 1;
				Date._Day = NumberOfDaysInAMonth(Date._Month, Date._Year);
			}
		}

		else
		{
			Date._Day -= 1;
		}
	}

	void DecreaseDateByOneDay()
	{
		DecreaseDateByOneDay(*this);
	}

	static void DecreaseDateByXDays(clsDate& Date, short NumberOfDays)
	{
		for (short i = 1; i <= NumberOfDays; i++)
		{
			DecreaseDateByOneDay(Date);
		}
	}

	void DecreaseDateByXDays(short NumberOfDays)
	{
		DecreaseDateByXDays(*this, NumberOfDays);
	}

	static void DecreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			DecreaseDateByOneDay(Date);
		}
	}

	void DecreaseDateByOneWeek()
	{
		DecreaseDateByOneWeek(*this);
	}

	static void DecreaseDateByXWeeks(clsDate& Date, short NumberOfWeeks)
	{
		for (short i = 1; i <= NumberOfWeeks; i++)
		{
			DecreaseDateByOneWeek(Date);
		}
	}

	void DecreaseDateByXWeeks(short NumberOfWeeks)
	{
		DecreaseDateByXWeeks(*this, NumberOfWeeks);
	}

	static void DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.IsFirstMonthInAYear(Date._Month))
		{
			Date._Year -= 1;
			Date._Month = 12;
		}

		else
		{
			Date._Month -= 1;
			Date.AccurateDays(Date);
		}
	}

	void DecreaseDateByOneMonth()
	{
		DecreaseDateByOneMonth(*this);
	}

	static void DecreaseDateByXMonths(clsDate& Date, short NumberOfMonths)
	{
		for (short i = 1; i <= NumberOfMonths; i++)
		{
			DecreaseDateByOneMonth(Date);
		}
	}

	void DecreaseDateByXMonths(short NumberOfMonths)
	{
		DecreaseDateByXMonths(*this, NumberOfMonths);
	}

	static void DecreaseDateByOneYear(clsDate& Date)
	{
		Date._Year -= 1;
		Date.AccurateDays(Date);
	}

	void DecreaseDateByOneYear()
	{
		DecreaseDateByOneYear(*this);
	}

	static void DecreaseDateByXYears(clsDate& Date, short NumberOfYears)
	{
		for (short i = 1; i <= NumberOfYears; i++)
		{
			DecreaseDateByOneYear(Date);
		}
	}

	void DecreaseDateByXYears(short NumberOfYears)
	{
		DecreaseDateByXYears(*this, NumberOfYears);
	}

	static void DecreaseDateByXYearsFaster(clsDate& Date, short NumberOfYears)
	{
		Date._Year -= NumberOfYears;
		Date.AccurateDays(Date);
	}

	void DecreaseDateByXYearsFaster(short NumberOfYears)
	{
		DecreaseDateByXYearsFaster(*this, NumberOfYears);
	}

	static void DecreaseDateByOneDecade(clsDate& Date)
	{
		Date._Year -= 1;
		Date.AccurateDays(Date);
	}

	void DecreaseDateByOneDecade()
	{
		DecreaseDateByOneDecade(*this);
	}

	static void DecreaseDateByXDecades(clsDate& Date, short NumberOfDecades)
	{
		for (short i = 1; i <= NumberOfDecades; i++)
		{
			DecreaseDateByOneDecade(Date);
		}
	}

	void DecreaseDateByXDecades(short NumberOfDecades)
	{
		DecreaseDateByXDecades(*this, NumberOfDecades);
	}

	static void DecreaseDateByXDecadesFaster(clsDate& Date, short NumberOfDecades)
	{
		Date._Year -= (NumberOfDecades * 10);
		Date.AccurateDays(Date);
	}

	void DecreaseDateByXDecadesFaster(short NumberOfDecades)
	{
		DecreaseDateByXDecadesFaster(*this, NumberOfDecades);
	}

	static void DecreaseDateByOneCentury(clsDate& Date)
	{
		Date._Year -= 100;
		Date.AccurateDays(Date);
	}

	void DecreaseDateByOneCentury()
	{
		DecreaseDateByOneCentury(*this);
	}

	static void DecreaseDateByOneMillennium(clsDate& Date)
	{
		Date._Year -= 1000;
		Date.AccurateDays(Date);
	}

	void DecreaseDateByOneMillennium()
	{
		DecreaseDateByOneMillennium(*this);
	}

	static bool IsDayEndOfWeek(clsDate Date)
	{
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year) == 6;
	}

	bool IsDayEndOfWeek()
	{
		return IsDayEndOfWeek(*this);
	}

	static bool IsDayWeekEnd(clsDate Date)
	{
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year) == 5 || DayOfWeekOrder(Date._Day, Date._Month, Date._Year) == 6;
	}

	bool IsDayWeekEnd()
	{
		return IsDayWeekEnd(*this);
	}

	static bool IsDayBusinessDay(clsDate Date)
	{
		return (!IsDayWeekEnd(Date));
	}

	bool IsDayBusinessDay()
	{
		return IsDayBusinessDay(*this);
	}

	static short DaysUntilEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}

	short DaysUntilEndOfWeek()
	{

		return DaysUntilEndOfWeek(*this);
	}

	static short DaysUntilEndOfMonth(clsDate Date)
	{
		return NumberOfDaysInAMonth(Date._Month, Date._Year) - Date._Day + 1;
	}

	short DaysUntilEndOfMonth()
	{
		return DaysUntilEndOfMonth(*this);
	}

	static short DaysUntilEndOfYear(clsDate Date)
	{
		return NumberOfDaysInAYear(Date._Year) - NumberOfDaysFromTheBeginingOfTheYear(Date._Day, Date._Month, Date._Year) + 1;
	}

	short DaysUntilEndOfYear()
	{
		return DaysUntilEndOfYear(*this);
	}

	static int CalculateVacationDays(clsDate Date1, clsDate Date2)
	{
		int ActualVacationDays = 0;
		short SwapFlagValue = 1;

		if (!IsDate1Lower(Date1, Date2))
		{
			Date1.SwapDates(Date1, Date2);
			SwapFlagValue = -1;
		}

		while (IsDate1Lower(Date1, Date2))
		{
			if (IsDayBusinessDay(Date1))
			{
				ActualVacationDays += 1;
			}

			IncreaseDateByOneDay(Date1);
		}

		return ActualVacationDays * SwapFlagValue;
	}

	int CalculateVacationDays(clsDate Date)
	{
		return CalculateVacationDays(*this, Date);
	}

	static void CalculateDateByVacationDays(clsDate Date, short VacationDays)
	{
		while (VacationDays > 0)
		{
			if (IsDayBusinessDay(Date))
			{
				VacationDays -= 1;
			}

			IncreaseDateByOneDay(Date);
		}

		Date.Print();
	}

	void CalculateDateByVacationDays(short VacationDays)
	{
		CalculateDateByVacationDays(*this, VacationDays);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1Lower(Date1, Date2)) && (!IsDate1EqualToDate2(Date1, Date2));
	}

	bool IsDate1AfterDate2(clsDate Date)
	{
		return IsDate1AfterDate2(*this, Date);
	}

	static enCompareDates CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1AfterDate2(Date1, Date2))
			return enCompareDates::eAfter;

		if (IsDate1EqualToDate2(Date1, Date2))
			return enCompareDates::eEqual;

		/* if (IsDate1Lower(Date1, Date2))
			return enCompareDates::eBefore; */

			// Faster
		return enCompareDates::eBefore;
	}

	enCompareDates CompareDates(clsDate Date)
	{
		return CompareDates(*this, Date);
	}

	static bool IsValidateMonth(short Month)
	{
		return (Month >= 1 && Month <= 12);
	}

	bool IsValidateMonth()
	{
		return IsValidateMonth(_Month);
	}

	static bool IsValidateDay(clsDate Date)
	{
		return (Date._Day >= 1 && Date._Day <= NumberOfDaysInAMonth(Date._Month, Date._Year));
	}

	bool IsValidateDay()
	{
		return IsValidateDay(*this);
	}

	static bool IsValidateDate(clsDate Date)
	{
		return IsValidateDay(Date) && IsValidateMonth(Date._Month);
	}

	bool IsValidateDate()
	{
		return IsValidateDate(*this);
	}

	static string FormatDate(clsDate Date, string Format = "dd/mm/yyyy")
	{
		string DateFormat = "";

		DateFormat = Date._ReplaceWordInString(Format, "dd", to_string(Date._Day));
		DateFormat = Date._ReplaceWordInString(DateFormat, "mm", to_string(Date._Month));
		DateFormat = Date._ReplaceWordInString(DateFormat, "yyyy", to_string(Date._Year));

		return DateFormat;
	}

	string FormatDate(string Format = "dd/mm/yyyy")
	{
		return FormatDate(*this, Format);
	}

	static string CurrentTime()
	{
		time_t t = time(0);

		tm* Now = localtime(&t);

		string Time = "";

		Time += to_string(Now->tm_hour) + ":";
		Time += to_string(Now->tm_min) + ":";
		Time += to_string(Now->tm_sec);

		return Time;
	}

};

