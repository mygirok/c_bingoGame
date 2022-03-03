#include <iostream>
#include<time.h>

using namespace std;

int main()
{
	srand((unsigned int)time(0));

	int	iNumber[25] = {};

	// Put numbers from 1 to 25.
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
	}

	// Shuffle the numbers.
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	while (true)
	{
		system("cls");

		// Output the number 5 x 5.
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";

				else
					cout << iNumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}
		cout << "Enter number(0 : Quit) : ";
		int iInput;
		cin >> iInput;

		if (iInput == 0)
			break;

		else if (iInput < 1 || iInput > 25)
			continue;

		// Duplicate check.
		bool bAcc = true;

		for (int i = 0; i < 25; ++i)
		{
			// If there's the same number
			if (iInput == iNumber[i])
			{
				bAcc = false;

				// INT_MAX will be changed to *.
				iNumber[i] = INT_MAX;
				break;
			}
		}

		if (bAcc)
			continue;
	}

	return 0;
}
