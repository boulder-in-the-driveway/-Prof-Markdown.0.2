#include "fileFormatter.h"

fileFormatter::fileFormatter(string filePath)
{
    readFileLines(filePath);
    for (int i = 0; i < eachLine.size(); i++)
    {
        convertMDtoHTML(i);
    }
    printToConsole();
    newHTML();
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
    }
    else if (pos == 0)
    {
        MarkdownConverter line = MarkdownConverter(eachLine[pos], "", eachLine[pos+1]);
        string temp = line.runConverter();
        eachLine[pos] = temp;
    }
    else
    {
        MarkdownConverter line = MarkdownConverter(eachLine[pos], eachLine[pos-1], "");
        string temp = line.runConverter();
        eachLine[pos] = temp;
    }
}

void fileFormatter::printToConsole()
{
    for (int i = 0; i < eachLine.size(); i++)
    {
        cout << eachLine[i] << endl;
    }
}

void fileFormatter::newHTML()
{
    ofstream MyFile("Converted.html");
    if (!MyFile.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    MyFile << "<!DOCTYPE html>" << endl;
    MyFile << "<html lang=\"en\">" << endl;
    MyFile << "<head>" << endl;
    MyFile << "<meta charset=\"UTF-8\">" << endl;
    MyFile << "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << endl;
    MyFile << "<title>Document</title>" << endl;
    MyFile << "</head>" << endl;
    MyFile << "<body>" << endl;

    for (int i = 0; i < eachLine.size(); i++)
    {
        MyFile << eachLine[i] << endl;
    }

    MyFile << "</body>" << endl;
    MyFile << "</html>";
}