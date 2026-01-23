#pragma once
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class MarkdownConverter
{
public:
    MarkdownConverter(string toInput);
    //toBold must ALWAYS be called before toItalic
    string toBold();
    string toItalic();
    string toHeader();
    string toOneLineCode();
    string toList();

private:
    string inputLine;
    string replaceNotation(string markdownSyntax, string HtmlStart, string HtmlEnd);
    string replaceNotationOneLine(string markdownSyntax, string HtmlStart, string HtmlEnd);
};