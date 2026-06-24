#include <iostream>
#include "clsLoginScreen.h";
#include "clsCurrency.h";

using namespace std;

int main()
{
	while (true)
	{
		clsLoginScreen::ShowLoginScreen();

		if (clsLoginScreen::GetFailedLoginCounter() == 0)
		{
			cout << "You Are Locked After 3 Failed Trials .\n";
			break;
		}

		else
		{
			clsLoginScreen::SetFailedLoginCounter(3);
		}
	}

	system("pause>0");
	return 0;
}