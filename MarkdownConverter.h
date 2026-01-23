#pragma once
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class MarkdownConverter
{
public:
    MarkdownConverter(string toInput);
    MarkdownConverter(string toInput, string toPreviousLine);
    MarkdownConverter(string toInput, string toPreviousLine, string toNextLine);
    MarkdownConverter(string toInput, string toNextLine);
    //toBold must ALWAYS be called before toItalic
    string toBold();
    string toItalic();
    string toHeader();
    string toOneLineCode();
    string toList();

private:
    //-- The line of Markdown before the current line, if there is one
    string previousLine;
    string inputLine;
    //-- The line of Markdown after the current line, if there is one
    string nextLine;
    string replaceNotation(string markdownSyntax, string HtmlStart, string HtmlEnd);
    string replaceNotationOneLine(string markdownSyntax, string HtmlStart, string HtmlEnd);
};