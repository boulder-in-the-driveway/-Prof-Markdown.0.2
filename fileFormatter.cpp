#include "fileFormatter.h"

fileFormatter::fileFormatter(string filePath)
{
    inCodeBlock = false;
    readFileLines(filePath);
    makeReadableCode();
    for (int i = 0; i < eachLine.size(); i++)
    {
        if (eachLine[i] == "```" || eachLine[i] == "``` ")
        {
            if (inCodeBlock)
            {
                eachLine[i] = "</code>";
            }
            else
            {
                eachLine[i] = "<code>";
            }
            inCodeBlock = !inCodeBlock;
        } 
        else if (inCodeBlock)
        {
            convertCodeHTML(i);
        } 
        else 
        {
            convertMDtoHTML(i);
        }
    }
    //printToConsole();
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
        string temp = line.runConverter(inCodeBlock);
        eachLine[pos] = temp;
    }
    else if (pos == 0)
    {
        MarkdownConverter line = MarkdownConverter(eachLine[pos], "", eachLine[pos+1]);
        string temp = line.runConverter(inCodeBlock);
        eachLine[pos] = temp;
    }
    else
    {
        MarkdownConverter line = MarkdownConverter(eachLine[pos], eachLine[pos-1], "");
        string temp = line.runConverter(inCodeBlock);
        eachLine[pos] = temp;
    }
}

void fileFormatter::convertCodeHTML(int pos)
{
    if (eachLine[pos] != "")
    {
        int last = eachLine.size() -1;
        if(pos > 0 && pos < last){
            MarkdownConverter line = MarkdownConverter(eachLine[pos], eachLine[pos-1], eachLine[pos+1]);
            string temp;
            temp = line.toHighlight();
            eachLine[pos] = temp;
        }
        else if (pos == 0)
        {
            MarkdownConverter line = MarkdownConverter(eachLine[pos], "", eachLine[pos+1]);
            string temp;
            temp = line.toHighlight();
            eachLine[pos] = temp;
        }
        else
        {
            MarkdownConverter line = MarkdownConverter(eachLine[pos], eachLine[pos-1], "");
            string temp;
            temp = line.toHighlight();
            eachLine[pos] = temp;
        }
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

void fileFormatter::makeReadableCode()
{
    for (int i = 0; i < eachLine.size(); i++)
    {
        if (eachLine[i].substr(0,8) == "``` file")
        {
            string name;
            for (int j = 0; j < eachLine[i].length(); j++)
            {
                if (eachLine[i][j] == '"')
                {
                    name = eachLine[i].substr(j+1, eachLine[i].find('"', j)-1);
                    break;
                }
            }
            string markName = "# " + name;
            eachLine.insert(eachLine.begin() + i-1, markName);
            eachLine[i+1] = "```";
        }
    }
}