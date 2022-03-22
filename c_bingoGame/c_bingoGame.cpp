#include <iostream>
#include<time.h>

using namespace std;

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
};

enum LINE_NUMBER
{
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT,
};

// Function declaration
void SetNumber(int* pArray);
void Shuffle(int* pArray);
AI_MODE SelectAIMode();
void OutputNumber(int* pArray, int iBingo);
bool ChangeNumber(int* pArray, int iInput);
int SelectAINumber(int* pArray, AI_MODE eMode);
int BingoCounting(int* pArray);
int BingoCountingH(int* pArray);
int BingoCountingV(int* pArray);
int BingoCountingLTD(int* pArray);
int BingoCountingRTD(int* pArray);

int main()
{
	srand((unsigned int)time(0));

	int	iNumber[25] = {};
	int iAINumber[25] = {};

	SetNumber(iNumber);
	SetNumber(iAINumber);

	// Shuffle the numbers.
	Shuffle(iNumber);
	Shuffle(iAINumber);

	int iBingo = 0, iAIBingo = 0;

	// Choose the AI difficulty.  
	AI_MODE eAIMode = SelectAIMode();


	while (true)
	{
		system("cls");

		// Output the number 5 x 5.
		cout << "============== Player ==============" << endl;
		OutputNumber(iNumber, iBingo);

		// Output AI bingo board 
		cout << "================ AI ================" << endl;

		switch (eAIMode)
		{
		case AM_EASY:
			cout << "AIMode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "AIMode : Hard" << endl;
			break;
		}

		OutputNumber(iAINumber, iAIBingo);

		// If there are more than five lines of bingo, the game ends.
		if (iBingo >= 5)
		{
			cout << "Player win" << endl;
			break;
		}

		else if (iAIBingo >= 5)
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
		bool bAcc = ChangeNumber(iNumber, iInput);

		if (bAcc)
			continue;

		// replace AI number to *.
		ChangeNumber(iAINumber, iInput);

		// AI picked a number
		iInput = SelectAINumber(iAINumber, eAIMode);


		//The number selected by AI is changed to *.
		ChangeNumber(iNumber, iInput);

		ChangeNumber(iAINumber, iInput);

		// Checking the number of bingo lines will count from the beginning every time 
		// you enter a number. So Assign 0 to the iBingo variable each time.
		iBingo = BingoCounting(iNumber);
		iAIBingo = BingoCounting(iAINumber);
	}

	return 0;
}

// Function definition
void SetNumber(int* pArray)
{
	for (int i = 0; i < 25; ++i)
	{
		pArray[i] = i + 1;
	}
}

void Shuffle(int* pArray)
{
	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; ++i)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = pArray[idx1];
		pArray[idx1] = pArray[idx2];
		pArray[idx2] = iTemp;
	}
}


AI_MODE SelectAIMode()
{
	int iAIMode;
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

	return (AI_MODE)iAIMode;
}

void OutputNumber(int* pArray, int iBingo)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			if (pArray[i * 5 + j] == INT_MAX)
				cout << "*\t";

			else
				cout << pArray[i * 5 + j] << "\t";
		}

		cout << endl;
	}

	cout << "Bingo Line : " << iBingo << endl << endl;

}

bool ChangeNumber(int* pArray, int iInput)
{
	for (int i = 0; i < 25; ++i)
	{
		// If there's the same number
		if (iInput == pArray[i])
		{
			// INT_MAX will be changed to *.
			pArray[i] = INT_MAX;
			return false;
		}
	}
	// If enter selected number
	return true;
}

int SelectAINumber(int* pArray, AI_MODE eMode)
{
	// Array of unselected numbers.
	int iNoneSelect[25] = {};
	// Stores the number of unselected numbers.
	int iNoneSelectCount = 0;

	// AI turn. AI chooses depends on the AI mode.
	switch (eMode)
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
			if (pArray[i] != INT_MAX)
			{
				iNoneSelect[iNoneSelectCount] = pArray[i];
				++iNoneSelectCount;
			}
		}

		return iNoneSelect[rand() % iNoneSelectCount];
	case AM_HARD:
		// Choose the number of lines with the highest chance of bingo.
		int iLine;
		int iStarCount = 0;
		int iSaveCount = 0;

		// Find the line with the most * of the horizontal lines.
		for (int i = 0; i < 5; ++i)
		{
			iStarCount = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (pArray[i * 5 + j] == INT_MAX)
				{
					++iStarCount;
				}
			}

			// Excludes lines with 5 stars
			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				// horizontal is 0 ~ 4
				iLine = i;
				iSaveCount = iStarCount;
			}
		}

		// Find the line with the most * of the vertical lines.
		for (int i = 0; i < 5; ++i)
		{
			iStarCount = 0;
			for (int j = 0; j < 5; ++j)
			{
				if (pArray[j * 5 + i] == INT_MAX)
					++iStarCount;
			}

			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				// vertical is 5 ~ 9
				iLine = i + 5;
				iSaveCount = iStarCount;
			}
		}

		// Upper left -> lower right diagonal check.
		iStarCount = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (pArray[i] == INT_MAX)
				++iStarCount;
		}

		if (iStarCount < 5 && iSaveCount < iStarCount)
		{
			iLine = LN_LT;
			iSaveCount = iStarCount;
		}


		// Upper right -> lower left diagonal check.
		iStarCount = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (pArray[i] == INT_MAX)
				++iStarCount;
		}

		if (iStarCount < 5 && iSaveCount < iStarCount)
		{
			iLine = LN_RT;
			iSaveCount = iStarCount;
		}

		// Choose one number from the selected lines.
		if (iLine <= LN_H5)
		{
			// horizontal: iLine = 0 ~ 4
			for (int i = 0; i < 5; ++i)
			{
				if (pArray[iLine * 5 + i] != INT_MAX)
				{
					return pArray[iLine * 5 + i];
				}

			}
		}

		else if (iLine <= LN_V5)
		{
			// vertical, iLine = 5 ~ 9
			for (int i = 0; i < 5; ++i)
			{
				if (pArray[i * 5 + (iLine - 5)] != INT_MAX)
				{
					return pArray[i * 5 + (iLine - 5)];
				}
			}
		}

		else if (iLine == LN_LT)
		{
			for (int i = 0; i < 25; i += 6)
			{
				if (pArray[i] != INT_MAX)
				{
					return pArray[i];
				}
			}
		}

		else if (iLine == LN_RT)
		{
			for (int i = 4; i <= 20; i += 4)
			{
				if (pArray[i] != INT_MAX)
				{
					return pArray[i];
				}
			}
		}
		break;
	}

	return -1;
}

int BingoCounting(int* pArray)
{
	int iBingo = 0;

	// Check horizontal line
	iBingo += BingoCountingH(pArray);

	// Check vertical line
	iBingo += BingoCountingV(pArray);

	// Upper left -> lower right diagonal check.
	iBingo += BingoCountingLTD(pArray);

	// Upper right -> lower left diagonal check.  
	iBingo += BingoCountingRTD(pArray);

	return iBingo;
}

int BingoCountingH(int* pArray)
{
	// Find the number of vertical lines.
	int iStar1 = 0, iBingo = 0;

	for (int i = 0; i < 5; ++i)
	{
		iStar1 = 0;
		for (int j = 0; j < 5; ++j)
		{
			// Find the vertical * number
			if (pArray[j * 5 + i] == INT_MAX)
				++iStar1;
		}

		// If iStar1 is  5, bingo
		if (iStar1 == 5)
			++iBingo;
	}

	return iBingo;
}

int BingoCountingV(int* pArray)
{
	// Find the number of horizontal lines.
	int iStar1 = 0, iBingo = 0;

	for (int i = 0; i < 5; ++i)
	{
		iStar1 = 0;
		for (int j = 0; j < 5; ++j)
		{
			// Find the horizontal * number
			if (pArray[i * 5 + j] == INT_MAX)
				++iStar1;
		}

		// If iStar1 is  5, bingo
		if (iStar1 == 5)
			++iBingo;
	}

	return iBingo;
}

int BingoCountingLTD(int* pArray)
{
	// Upper left -> lower right diagonal check.
	int iStar1 = 0, iBingo = 0;
	for (int i = 0; i < 25; i += 6)
	{
		if (pArray[i] == INT_MAX)
			++iStar1;
	}

	if (iStar1 == 5)
		++iBingo;

	return iBingo;
}

int BingoCountingRTD(int* pArray)
{
	// Upper right -> lower left diagonal check.
	int iStar1 = 0, iBingo = 0;
	for (int i = 4; i <= 20; i += 4)
	{
		if (pArray[i] == INT_MAX)
			++iStar1;
	}

	if (iStar1 == 5)
		++iBingo;

	return iBingo;
}

