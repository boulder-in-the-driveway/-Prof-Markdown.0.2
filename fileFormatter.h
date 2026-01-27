#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "MarkdownConverter.h"

using namespace std;

class fileFormatter
{
public:
fileFormatter(string filePath);
string getLine(int pos);

private:
vector<string> eachLine;
void readFileLines(const string& filePath);

};