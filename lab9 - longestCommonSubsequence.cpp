#include<iostream>
#include<string>

using namespace std;

int longestCommonSubsequence(string, int, string, int);

int main()
{
	string str0 = "xmjyauz";
	string str1 = "mzjawxu";

	cout << "String0: " << str0 << endl << "String1: " << str1 << endl;

	cout << longestCommonSubsequence(str0, str0.size(), str1, str1.size()) << endl;
	
	system("PAUSE");
	return 0;
}

int longestCommonSubsequence(string str0, int rows, string str1, int columns)
{
	int** matrix = new int* [rows + 1];		//dynamically instantiate matrix
	for (size_t i = 0; i < rows + 1; i++)
		matrix[i] = new int[columns + 1];

	for (size_t i = 0; i < rows+1; i++)
	{
		for (size_t j = 0; j < columns+1; j++)
		{
			if (i == 0 || j == 0)					//if i and j are 0
				matrix[i][j] = 0;										//set to 0
			else if (str0[i] == str1[j])			//if current chars are the same
				matrix[i][j] = matrix[i - 1][j - 1] + 1;				//set to diagonal + 1
			else if (str0[i] != str1[j])			//if current chars are different
				matrix[i][j] = max(matrix[i][j - 1], matrix[i - 1][j]);	//set to max of top and left
		}
	}

	int answer = matrix[rows][columns];

	//memory management - delete matrix
	for (size_t i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;

	return answer;
}