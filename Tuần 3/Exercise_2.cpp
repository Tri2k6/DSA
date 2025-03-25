#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#define input cin
#define output cout
#define dictionaryFile "English-Vietnamese Dictionary.txt"
#define pii pair<string, string>

const int n = 124585;

pii Process_String(string str);

int main(int argc, char *argv[])
{
    // Mo file Dictionary
    if (fopen(dictionaryFile, "r"))
    {
        freopen(dictionaryFile, "r", stdin);
    }
    else
    {
        output << "Cann't access to the database";
        return 0;
    }

    // Mo file output
    freopen(argv[argc - 1], "w", stdout);

    // Doc co so du lieu
    pii *a = new pii[n];

    for (int i = 0; i < n; i++)
    {
        string str;
        getline(input, str);
    }

    return 0;
}

pii Process_String(string str)
{
    string word = "";
    string meaning = "";

    bool isPivot = false;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ':')
        {
            isPivot = true;
        }
        else if (isPivot)
            word += str[i];
    }
}