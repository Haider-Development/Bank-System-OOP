#pragma once

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;



class clsString
{
	string _Value;

	enum enwhattocount { smallletters = 0, capitalletters = 1, all = 2 };

	enum enMatchCase { WithMatchCase = 0, WithoutMatchCase = 1 };

	static char ConvertCharLetter(char char1)
	{
		return isupper(char1) ? tolower(char1) : toupper(char1);
	}

	static bool IsVowel(char letter)
	{
		char lowletter = tolower(letter);

		return (lowletter == 'a') || (lowletter == 'i') || (lowletter == 'e') || (lowletter == 'o') || (lowletter == 'u');
	}

public:

	clsString()
	{

	}

	clsString(string Value)
	{
		_Value = Value;
	}

	void SetValue(string Value)
	{
		_Value = Value;
	}

	string GetValue()
	{
		return _Value;
	}

	__declspec(property(get = GetValue, put = SetValue)) string Value;

	static void PrintFirstLetterOfEachWord(string line)
	{
		bool isfirstletter = true;

		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] != ' ' && isfirstletter)
			{
				cout << line[i] << "  ";
			}

			isfirstletter = (line[i] == ' ') ? true : false;
		}
	}

	void PrintFirstLetterOfEachWord()
	{
		PrintFirstLetterOfEachWord(_Value);
	}

	static void UpperFirstLetterOfEachWord(string line)
	{
		bool isfirstletter = true;

		for (int i = 0; i < line.length(); i++)
		{
			if (line.at(i) != ' ' && isfirstletter)
			{
				line.at(i) = toupper(line.at(i));
			}

			isfirstletter = (line.at(i) == ' ' || line.at(i) == '-') ? true : false;
		}

		cout << line << endl;
	}

	void UpperFirstLetterOfEachWord()
	{
		UpperFirstLetterOfEachWord(_Value);
	}

	static void LowerFirstletterOfEachWord(string line)
	{
		bool isfirstletter = true;

		for (int i = 0; i < line.length(); i++)
		{
			if (line.at(i) != ' ' && isfirstletter)
			{
				line.at(i) = tolower(line.at(i));
			}

			isfirstletter = (line.at(i) == ' ' || line.at(i) == '-') ? true : false;
		}

		cout << line << endl;
	}

	void LowerFirstletterOfEachWord()
	{
		LowerFirstletterOfEachWord(_Value);
	}

	static string UpperAllString(string line)
	{
		for (int i = 0; i < line.length(); i++)
		{
			line[i] = toupper(line[i]);
		}

		return line;
	}

	string UpperAllString()
	{
		return UpperAllString(_Value);
	}

	static string LowerAllString(string line)
	{
		for (int i = 0; i < line.length(); i++)
		{
			line[i] = tolower(line[i]);
		}

		return line;
	}

	string LowerAllString()
	{
		return LowerAllString(_Value);
	}

	static string ConvertAllStringLetters(string line)
	{
		for (int i = 0; i < line.length(); i++)
		{
			line[i] = ConvertCharLetter(line[i]);
		}

		return line;
	}

	string ConvertAllStringLetters()
	{
		return ConvertAllStringLetters(_Value);
	}

	static int CountLetters(string line, enwhattocount whattocount = enwhattocount::all)
	{
		short counter = 0;

		if (whattocount == enwhattocount::all)
		{
			return line.length();
		}

		for (int i = 0; i < line.length(); i++)
		{
			if (isupper(line[i]) && whattocount == enwhattocount::capitalletters)
			{
				counter += 1;
			}
		}

		for (int i = 0; i < line.length(); i++)
		{
			if (islower(line[i]) && whattocount == enwhattocount::smallletters)
			{
				counter += 1;
			}
		}

		return counter;
	}

	int CountLetters(enwhattocount whattocount = enwhattocount::all)
	{
		return CountLetters(_Value, whattocount);
	}

	static short CountVowelLetters(string line)
	{
		short counter = 0;

		for (int i = 0; i < line.length(); i++)
		{
			if (IsVowel(line.at(i)))
				counter += 1;
		}

		return counter;
	}

	short CountVowelLetters()
	{
		return CountVowelLetters(_Value);
	}

	static void PrintVowelLetters(string line)
	{
		short counter = 0;

		for (int i = 0; i < line.length(); i++)
		{
			if (IsVowel(line.at(i)))
				cout << line.at(i) << "  ";
		}

	}

	void PrintVowelLetters()
	{
		PrintVowelLetters(_Value);
	}

	static void PrintEachWordInString(string line)
	{
		cout << "\nyour string words are :\n\n";

		string delime = " ";

		short pos = 0;
		string word;

		while ((pos = line.find(delime)) != string::npos)
		{
			word = line.substr(0, pos);

			if (word != "")
			{
				cout << word << endl;
			}

			line.erase(0, pos + delime.length());
		}

		if (line != "")
		{
			cout << line << endl;
		}

	}

	void PrintEachWordInString()
	{
		PrintEachWordInString(_Value);
	}

	static short CountWordsInString(string line)
	{
		short counter = 0;
		string delime = " ";

		short pos = 0;
		string word;

		while ((pos = line.find(delime)) != string::npos)
		{
			word = line.substr(0, pos);

			if (word != "")
			{
				counter += 1;
			}

			line.erase(0, pos + delime.length());
		}

		if (line != "")
		{
			counter += 1;
		}

		return counter;
	}

	short CountWordsInString()
	{
		return CountWordsInString(_Value);
	}

	static vector <string> vSplitString(string line, string delime)
	{
		vector <string> vwords;

		short pos = 0;
		string word;

		while ((pos = line.find(delime)) != string::npos)
		{
			word = line.substr(0, pos);

			if (word != "")
			{
				vwords.push_back(word);
			}

			line.erase(0, pos + delime.length());
		}

		if (line != "")
		{
			vwords.push_back(line);
		}

		return vwords;
	}

	vector <string> vSplitString(string Delime)
	{
		return vSplitString(_Value, Delime);
	}

	static string TrimLift(string line)
	{
		for (short i = 0; i < line.length(); i++)
		{
			if (line[i] != ' ')
			{
				return line.substr(i, line.length() - 1);
			}
		}

		return "";
	}

	string TrimLift()
	{
		return TrimLift(_Value);
	}

	static string TrimRight(string line)
	{
		for (short i = line.length() - 1; i >= 0; i--)
		{
			if (line.at(i) != ' ')
			{
				return line.substr(0, i + 1);
			}
		}

		return "";
	}

	string TrimRight()
	{
		return TrimRight(_Value);
	}

	static string Trim(string line)
	{
		return TrimLift(TrimRight(line));
	}

	string Trim()
	{
		return Trim(_Value);
	}

	static string JoinString(vector <string> vwords, string Delime)
	{
		string line = "";

		for (string& word : vwords)
		{
			line = line + word + Delime;
		}

		return line.substr(0, line.length() - Delime.length());
	}

	static string ReverseStringWords(string line, string delime)
	{
		vector <string> vwords;

		vwords = vSplitString(line, delime);

		vector <string>::iterator iter = vwords.end();

		line = "";

		while (iter != vwords.begin())
		{
			--iter;

			line = line + *iter + delime;
		}

		line = line.substr(0, line.length() - delime.length());

		return line;
	}

	string ReverseStringWords(string Delime)
	{
		return ReverseStringWords(_Value, Delime);
	}

	static string ReplaceWordsInString(string Line, string Delime, string precord, string nrecord, enMatchCase MatchCase)
	{
		vector <string> vWords;

		vWords = vSplitString(Line, Delime);

		if (MatchCase == enMatchCase::WithoutMatchCase)
		{
			for (string& record : vWords)
			{
				if (LowerAllString(record) == LowerAllString(precord))
				{
					record = nrecord;
				}
			}
		}

		else
		{
			for (string& record : vWords)
			{
				if (record == precord)
				{
					record = nrecord;
				}
			}
		}

		return JoinString(vWords, Delime);
	}

	string ReplaceWordsInString(string Delime, string precord, string nrecord, enMatchCase MatchCase)
	{
		return ReplaceWordsInString(_Value, Delime, precord, nrecord, MatchCase);
	}

	static string RemovePunctuaction(string line)
	{
		string nstring = "";

		for (short i = 0; i < line.length(); i++)
		{
			if (!ispunct(line.at(i)))
			{
				nstring.push_back(line.at(i)); // || nstring += line.at(i); || nstring += line[i];
			}
		}

		return nstring;
	}

	string RemovePunctuaction()
	{
		return RemovePunctuaction(_Value);
	}

};

