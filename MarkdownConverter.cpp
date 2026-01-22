#include "MarkdownConverter.h"

MarkdownConverter::MarkdownConverter(string toInput)
{
    inputLine = toInput;
}
    
string MarkdownConverter::toBold()
{
    /*
    string retVal = inputLine;
    int timesReplaced = 0;
    string HtmlStart = "<strong>";
    string HtmlEnd = "</strong>";

    for (int i = 0; i < retVal.length()-1; i++)
    {
        if (retVal[i] == '*' && retVal[i+1] == '*')
        {
            timesReplaced++;
            if (timesReplaced%2 != 0)
            {
                retVal.replace(i,2,HtmlStart);
            } 
            else
            {
                retVal.replace(i,2,HtmlEnd);
            }
        }
    }
    return retVal;
    */

    return replaceNotation("**", "<strong>", "</strong>");
}

string MarkdownConverter::toItalic()
{
    string retVal = "";
    return retVal;
}

string MarkdownConverter::toHeader()
{
    string retVal = "";
    return retVal;
}

string MarkdownConverter::replaceNotation(string markdownSyntax, string HtmlStart, string HtmlEnd)
{
    string retVal = inputLine;
    int timesReplaced = 0;
    int syntaxLength = markdownSyntax.length();

    for (int i = 0; i < retVal.length()-1; i++)
    {
        if (retVal.substr(i, syntaxLength) == markdownSyntax)
        {
            timesReplaced++;
            if (timesReplaced%2 != 0)
            {
                retVal.replace(i,syntaxLength,HtmlStart);
            } 
            else
            {
                retVal.replace(i,syntaxLength,HtmlEnd);
            }
        }
    }
    return retVal;
}

string MarkdownConverter::replaceNotationOneLine(string markdownSyntax, string HtmlStart, string HtmlEnd)
{
    return "";
}