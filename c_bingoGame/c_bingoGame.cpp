#include <iostream>
#include<time.h>

using namespace std;

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
};

int main()
{
	srand((unsigned int)time(0));

	int	iNumber[25] = {};
	int iAINumber[25] = {};


	// Put numbers from 1 to 25.
	for (int i = 0; i < 25; ++i)
	{
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
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

		// Shuffle the numbers for AI
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = iTemp;
	}

	int iBingo = 0, iAIBingo = 0;
	int iAIMode;

	// Choose the AI difficulty.
	while (true)
	{
		system("cls");
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI 모드를 선택하세요 : ";
		cin >> iAIMode;

		if (iAIMode >= AM_EASY && iAIMode <= AM_HARD)
			break;
	}
	
	// Array of unselected numbers.
	int iNoneSelect[25] = {};
	// Stores the number of unselected numbers.
	int iNoneSelectCount = 0;

	while (true)
	{
		system("cls");

		// Output the number 5 x 5.
		cout << "============== Player ==============" << endl;

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

		cout << "Bingo Line : " << iBingo << endl << endl;

		// Output AI bingo board 
		cout << "================ AI ================" << endl;

		switch (iAIMode)
		{
		case AM_EASY:
			cout << "AIMode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "AIMode : Hard" << endl;
			break;
		}
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (iAINumber[i * 5 + j] == INT_MAX)
					cout << "*\t";

				else
					cout << iAINumber[i * 5 + j] << "\t";
			}

			cout << endl;
		}

		// Count number of AI bingo line
		cout << "AIBingo Line : " << iAIBingo << endl;

		// If there are more than five lines of bingo, the game ends.
		if (iBingo >= 5)
		{
			cout << "Player win" << endl;
			break;
		}

		else if(iAIBingo >= 5)
		{
			cout << "AI win" << endl;
			break;  
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
		
		// replace AI number to *.
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		// AI turn. AI chooses depends on the AI mode.
		switch (iAIMode)
		{

			/*
			AI Easy Mode: Creates a list of numbers
			that are not changed to * among the current AI number lists,
			and lets you randomly select one of the lists.
			*/ 
		case AM_EASY:
			// list of unselected numbers.
			iNoneSelectCount = 0;
			for (int i = 0; i < 25; ++i)
			{
				// If the current number is not *.
				if (iAINumber[i] != INT_MAX)
				{
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					++iNoneSelectCount;
				}
			}

			iInput = iNoneSelect[rand() % iNoneSelectCount];
			break;
		case AM_HARD:
			break;
		}

		//The number selected by AI is changed to *.
		for (int i = 0; i < 25; ++i)
		{
			if (iNumber[i] == iInput)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}
		
		for (int i = 0; i < 25; ++i)
		{
			if (iAINumber[i] == iInput)
			{
				iAINumber[i] = INT_MAX;
				break;
			}
		}

		// Checking the number of bingo lines will count from the beginning every time 
		// you enter a number. So Assign 0 to the iBingo variable each time.
		iBingo = 0;
		iAIBingo = 0;

		// Find the number of horizontal and vertical lines.
		int iStar1 = 0, iStar2 = 0;
		int iAIStar1 = 0, iAIStar2 = 0;
		for (int i = 0; i < 5; ++i)
		{
			iStar1 = iStar2 = 0;
			iAIStar1 = iAIStar2 = 0;
			for (int j = 0; j < 5; ++j)
			{
				// Find the horizontal * number
				if (iNumber[i * 5 + j] == INT_MAX)
					++iStar1;
				
				// Find the vertical * number
				if (iNumber[j * 5 + i] == INT_MAX)
					++iStar2;

				// AI bingo line check
				if (iAINumber[i * 5 + j] == INT_MAX)
					++iAIStar1;

				if (iAINumber[j * 5 + i] == INT_MAX)
					++iAIStar2;
			}

			// If iStar1 is  5, bingo
			if (iStar1 == 5)
				++iBingo;

			if (iStar2 == 5)
				++iBingo;

			if (iAIStar1 == 5)
				++iAIBingo;

			if (iAIStar2 == 5)
				++iAIBingo;
		}

		// Upper left -> lower right diagonal check.
		iStar1 = 0;
		iAIStar1 = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;

			if (iAINumber[i] == INT_MAX)
				++iAIStar1;
		}

		if (iStar1 == 5)
			++iBingo;

		if (iAIStar1 == 5)
			++iAIBingo;
		// Upper right -> lower left diagonal check.
		iStar1 = 0;
		iAIStar1 = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				++iStar1;

			if (iAINumber[i] == INT_MAX)
				++iAIStar1;
		}

		if (iStar1 == 5)
			++iBingo;

		if (iAIStar1 == 5)
			++iAIBingo;
	}

	return 0;
}
