#include "MarkdownConverter.h"

MarkdownConverter::MarkdownConverter(string toInput)
{
    inputLine = toInput;
}
    
string MarkdownConverter::toBold()
{
    return replaceNotation("**", "<strong>", "</strong>");
}

string MarkdownConverter::toItalic()
{
    return replaceNotation("*", "<em>", "</em>");
}

string MarkdownConverter::toHeader()
{
    string retVal = "";
    return retVal;
}

    string MarkdownConverter::toOneLineCode()
    {
        return replaceNotation("`", "<code>", "</code>");
    }

string MarkdownConverter::toLink()
{
    return swapNotation("[", "]", '(', ")", "<a href=\"", "</a>");
}

string MarkdownConverter::replaceNotation(string markdownSyntax, string HtmlStart, string HtmlEnd)
{
    string retVal = inputLine;
    int timesReplaced = 0;
    int syntaxLength = markdownSyntax.length();
    int loopHelper = syntaxLength - 1;

    for (int i = 0; i < retVal.length()-loopHelper; i++)
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