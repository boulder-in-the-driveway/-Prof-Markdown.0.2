#include "MarkdownConverter.h"

MarkdownConverter::MarkdownConverter(string toInput)
{
    inputLine = toInput;
    previousLine = "";
    nextLine = "";
}

MarkdownConverter::MarkdownConverter(string toInput, string toPreviousLine, string toNextLine)
{
    inputLine = toInput;
    previousLine = toPreviousLine;
    nextLine = toNextLine;
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

string MarkdownConverter::toImage()
{
    return swapNotation("![", "]", '(', ")", "<img src=\"", "\" alt=\"");
}

string MarkdownConverter::toOneLineCode()
{
    return replaceNotation("`", "<code>", "</code>");
}

string MarkdownConverter::toList()
{
    string retVal = inputLine;

    if (retVal[0] == '-')
    {
        retVal.replace(0,1,"<li>");
        retVal.append("</li>");
        if (previousLine[0] != '-')
        {
            retVal.insert(0,"<ul>\n");
        }
        if (nextLine[0] != '-')
        {
            retVal.append("\n</ul>");
        }
    }
    if (isdigit(retVal[0]))
    {
        int i = 0;
        while (isdigit(retVal[i]) || retVal[i] == '.')
        {
            i++;
        }
        retVal.replace(0,i,"<li>");
        retVal.append("</li>");
        if (!isdigit(previousLine[0]))
        {
            retVal.insert(0,"<ol>\n");
        }
        if (!isdigit(nextLine[0]))
        {
            retVal.append("\n</ol>");
        }
    }

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

string MarkdownConverter::swapNotation(string firstPart, string secondPart, char thirdPart, string fourthPart, string htmlOpen, string htmlClosed)
{
    string retVal = inputLine;
    size_t searchPosition = 0;

    while (retVal.find(firstPart, searchPosition) != string::npos)
    {
        size_t imageStart = retVal.find(firstPart, searchPosition);
        if (imageStart == string::npos) break; 

        size_t altTextEnd = retVal.find(secondPart, imageStart);
        if (altTextEnd == string::npos)
        {
            searchPosition = imageStart + 2; 
            continue;
        }

        if (altTextEnd + 1 >= retVal.size() || retVal[altTextEnd + 1] != thirdPart)
        {
            searchPosition = altTextEnd + 1; 
            continue;
        }

        size_t urlStart = altTextEnd + 2;               
        size_t urlEnd = retVal.find(fourthPart, urlStart);     
        if (urlEnd == string::npos)
        {
            searchPosition = urlStart; 
            continue;
        }

        string altText = retVal.substr(imageStart + 2, altTextEnd - (imageStart + 2));
        string imageUrl = retVal.substr(urlStart, urlEnd - urlStart);

        
        string htmlFormat = htmlOpen + imageUrl + htmlClosed + altText + "\">";

        
        retVal.replace(imageStart, urlEnd - imageStart + 1, htmlFormat);

        searchPosition = imageStart + htmlFormat.size();
    }

    return retVal;
}


string MarkdownConverter::toParagraph()
{
    string retVal = inputLine;
    size_t pos = retVal.find("\n\n"); //look for the characters for the paragraph

    if (pos != string::npos){

        string before = retVal.substr(0, pos); //breaks up the continued string
        string after = retVal.substr(pos + 2); //so we don't put tags on all of it

        // trim trailing space from paragraph
        while (!before.empty() && before.back() == ' ')
        { //we don't want a space
            before.pop_back();
        }

        retVal = "<p>" + before + "</p>" + after; //puts in the tags, 
        //and includes the remaining string 
    }

    return retVal;
}