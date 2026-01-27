#include "fileFormatter.h"

fileFormatter::fileFormatter(string filePath)
{
    readFileLines(filePath);
    //convert and replace each line
    //create new HTML doc
}

string fileFormatter::getLine(int pos)
{
    return eachLine[pos];
}

void fileFormatter::readFileLines(const string& filePath) 
{ 
    ifstream infile; 
    infile.open(filePath); 
 
    if(infile.good()) 
    { 
        string line; 
 
        while (getline(infile, line)) 
        {
            eachLine.push_back(line);
        }
    } 
    else 
    { 
        cout<<"Cannot open the file: "<<filePath<<endl; 
    } 
}

void fileFormatter::convertMDtoHTML(int pos)
{
    if (pos != 0 || pos != eachLine.size())
    {
        MarkdownConverter line = MarkdownConverter(eachLine[pos], eachLine[pos-1], eachLine[pos+1]);
        eachLine[pos] = line.runConverter();
    }
    else if (pos == 0)
    {
        MarkdownConverter line = MarkdownConverter(eachLine[pos], "", eachLine[pos+1]);
        eachLine[pos] = line.runConverter();
    }
    else
    {
        MarkdownConverter line = MarkdownConverter(eachLine[pos], eachLine[pos-1], "");
        eachLine[pos] = line.runConverter();
    }
}