#include <map>
#include <list>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

double count_shennon(int n, double* propabilities)
{
    double result = 0.0;
    for (int i = 0; i < n; i++)
    {
        if (propabilities[i] == 0.0)
        {
            continue;
        }
        result += -propabilities[i] * log2(propabilities[i]);
    }
    return result;
}

double count_pairs(int n, int size, list<char> alphabet, string file)
{
    int counter = 0;
    string pair = "";
    double sum = 0.0;
    map <string, int> f_pair_prop;
    double* pair_propabilities = new double[n * n];

    for (int i : alphabet)
    {
        for (int j : alphabet)
        {
            pair += static_cast<char> (i);
            pair += static_cast<char> (j);
            f_pair_prop[pair] = 0;
            pair = "";
        }
    }

    pair = "";
    for (int i = 0; i < size - 1; i++)
    {
        pair += file[i];
        pair += file[i + 1];
        f_pair_prop[pair]++;
        pair = "";
    }

    pair = "";
    for (int i : alphabet)
    {
        for (int j : alphabet)
        {
            pair += static_cast<char> (i);
            pair += static_cast<char> (j);
            pair_propabilities[counter] = f_pair_prop[pair] / (double)(size - 1);
            if (f_pair_prop[pair] != 0)
            {
                //cout << pair << " " << f_pair_prop[pair] << " " << pair_propabilities[counter] << endl;
            }
            sum += pair_propabilities[counter];
            counter++;
            pair = "";
        }
    }
    //cout << sum << endl;
    return count_shennon(counter, pair_propabilities) / 2;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    int all_symbols = 0;
    int unique_symbols = 0;

    string line;
    list <char> alphabet;
    map<char, int> file_prop;

    string code_file = "";
    ifstream f1("c#.txt");
    //ifstream f1("c++.txt");
    //ifstream f1("c.txt");
    //ifstream f1("python.txt");
    //ifstream f1("lisp.txt");

    if (f1.is_open())
    {
        while (getline(f1, line))
        {
            code_file += line;
        }
    }
    f1.close();

    for (int i = 0; i < code_file.size(); i++)
    {
        if (file_prop.count(code_file[i]) != 1)
        {
            file_prop[code_file[i]] = 0;
            alphabet.push_front(code_file[i]);
            unique_symbols++;
        }
        file_prop[code_file[i]]++;
        all_symbols++;
    }
    //cout << unique_symbols << " " << all_symbols << endl;

    double* propabilities = new double[unique_symbols];

    int counter = 0;
    double sum = 0.0;
    for (int n : alphabet)
    {
        propabilities[counter] = (file_prop[static_cast<char> (n)] / (double)all_symbols);
        sum += propabilities[counter];
        //cout << static_cast<char> (n) << " " << file_prop[static_cast<char> (n)] <<  " " << propabilities[counter] << endl;
        counter++;
    }
    //cout << sum << endl;

    cout << count_shennon(unique_symbols, propabilities) << endl;
    cout << count_pairs(unique_symbols, all_symbols, alphabet, code_file) << endl;
}
