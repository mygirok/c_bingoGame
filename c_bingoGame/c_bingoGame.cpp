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

	int iBingo = 0;

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

		cout << "Bingo Line : " << iBingo << endl;

		// If there are more than five lines of bingo, the game ends.
		if (iBingo >= 5)
			break;

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

		// Checking the number of bingo lines will count from the beginning every time 
		// you enter a number. So Assign 0 to the iBingo variable each time.
		iBingo = 0;

		// Find the number of horizontal and vertical lines.
		int iStar1 = 0, iStar2 = 0;
		for (int i = 0; i < 5; ++i)
		{
			iStar1 = iStar2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				// Find the horizontal * number
				if (iNumber[i * 5 + j] == INT_MAX)
					++iStar1;
				
				// Find the vertical * number
				if (iNumber[j * 5 + i] == INT_MAX)
					++iStar2;
			}

			// If iStar1 is  5, bingo
			if (iStar1 == 5)
				++iBingo;

			if (iStar2 == 5)
				++iBingo;
		}

		// Upper left -> lower right diagonal check.
		iStar1 = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;
		}

		if (iStar1 == 5)
			++iBingo;

		// Upper right -> lower left diagonal check.
		iStar1 = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;
		}

		if (iStar1 == 5)
			++iBingo;
	}

	return 0;
}
