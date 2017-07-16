/***********************************************************************
* Program:
*    Week 13, Homograph Program
*    Brother Wilson, CS470
* Author:
*    Wellesley Shumway
* Summary: 
*    Please include a detailed description of:
*    1. What this program is designed to do
*    This program will state whether to file paths are the same
*    2. How this program will go about solving the problem
*    This program will do this by reaching the files and comparing whether
*    they represent the same file
*    3. What assumptions about input (file or user) is made
*    The user inputs file names without quotes according to Linux standards.
*    4. Citations if the algorithm was borrowed or inspired from any source
************************************************************************/
#include <iostream>
#include <string>
#include <stack>
using namespace std;

void getFileName(string & fileName1, string & fileName2)
{
  cout << "Specify the first filename:   ";
  cin >> fileName1;
  cout << "Specify the second filename:   ";
  cin >> fileName2;
}
vector<string> splitFilePath(string stringToSplit)
{
  vector<string> vTokens;

  for (int i = 0; i < stringToSplit.length(); i++)
  {
    if (
  }

  return vTokens;
}

bool filesAreHomographs(string fileName1, string fileName2)
{
  stack<string> file1Stack;
  stack<string> file2Stack; 

  for (int i = 0; i < fileName1.length(); i++)
  {
    
  }

  return false;
}

int main()
{
  string fileName1;
  string fileName2;
  getFileName(fileName1, fileName2);
  return 0;
}
