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
bool inCodeBlock = false;
int cBCounter;
void readFileLines(const string& filePath);
void convertMDtoHTML(int pos);
void convertCodeHTML(int pos);
void printToConsole();
void newHTML();
void makeReadableCode();
};