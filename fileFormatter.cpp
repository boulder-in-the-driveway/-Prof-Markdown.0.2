#include "fileFormatter.h"

fileFormatter::fileFormatter(string filePath)
{
    readFileLines(filePath);
    for (int i = 0; i < eachLine.size(); i++)
    {
        convertMDtoHTML(i);
    }
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
    int last = eachLine.size() -1;
    if(pos > 0 && pos < last){
        MarkdownConverter line = MarkdownConverter(eachLine[pos], eachLine[pos-1], eachLine[pos+1]);
        string temp = line.runConverter();
        eachLine[pos] = temp;
        //cout << temp << endl;
    }
    else if (pos == 0)
    {
        MarkdownConverter line = MarkdownConverter(eachLine[pos], "", eachLine[pos+1]);
        string temp = line.runConverter();
        eachLine[pos] = temp;
        //cout << temp << endl;
    }
    else
    {
        MarkdownConverter line = MarkdownConverter(eachLine[pos], eachLine[pos-1], "");
        string temp = line.runConverter();
        eachLine[pos] = temp;
        //cout << temp << endl;
    }
}