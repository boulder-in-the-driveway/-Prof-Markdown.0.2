#pragma once
#include <iostream>
#include <string>

using namespace std;

class MarkdownConverter
{
public:
    MarkdownConverter(string toInput);
    string toBold();
    string toItalic();
    string toHeader();
    
private:
    string inputLine;
};