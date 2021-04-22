#include <map>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

double log3(double x)
{
    return log10(x) / log10(3);
}

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

double count_pairs(int n, int size, string file)
{
    int counter = 0;
    double sum = 0.0;
    string pair = "";
    map <string, int> f_pair_prop;
    double* pair_propabilities = new double[n * n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            switch (i)
            {
            case 0:
                pair += "0";
                break;
            case 1:
                pair += "1";
                break;
            case 2:
                pair += "2";
                break;
            }
            switch (j)
            {
            case 0:
                pair += "0";
                break;
            case 1:
                pair += "1";
                break;
            case 2:
                pair += "2";
                break;
            }
            f_pair_prop[pair] = 0;
            pair = "";
        }
    }

    for (int i = 0; i < size - 1; i++)
    {
        pair += file[i];
        pair += file[i + 1];
        f_pair_prop[pair]++;
        pair = "";
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            switch (i)
            {
            case 0:
                pair += "0";
                break;
            case 1:
                pair += "1";
                break;
            case 2:
                pair += "2";
                break;
            }
            switch (j)
            {
            case 0:
                pair += "0";
                break;
            case 1:
                pair += "1";
                break;
            case 2:
                pair += "2";
                break;
            }
            pair_propabilities[counter] = f_pair_prop[pair] / (double)(size - 1);
            //cout << pair << " " << f_pair_prop[pair] << " " << pair_propabilities[counter] << endl;
            sum += pair_propabilities[counter];
            counter++;
            pair = "";
        }
    }
    //cout << sum << endl;
    return count_shennon(counter, pair_propabilities) / 2;
}

double count_triples(int n, int size, string file)
{
    int counter = 0;
    double sum = 0.0;
    string pair = "";
    map <string, int> f_pair_prop;
    double* pair_propabilities = new double[n * n * n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                switch (i)
                {
                case 0:
                    pair += "0";
                    break;
                case 1:
                    pair += "1";
                    break;
                case 2:
                    pair += "2";
                    break;
                }
                switch (j)
                {
                case 0:
                    pair += "0";
                    break;
                case 1:
                    pair += "1";
                    break;
                case 2:
                    pair += "2";
                    break;
                }
                switch (k)
                {
                case 0:
                    pair += "0";
                    break;
                case 1:
                    pair += "1";
                    break;
                case 2:
                    pair += "2";
                    break;
                }
                f_pair_prop[pair] = 0;
                pair = "";
            }
        }
    }

    for (int i = 0; i < size - 2; i++)
    {
        pair += file[i];
        pair += file[i + 1];
        pair += file[i + 2];
        f_pair_prop[pair]++;
        pair = "";
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                switch (i)
                {
                case 0:
                    pair += "0";
                    break;
                case 1:
                    pair += "1";
                    break;
                case 2:
                    pair += "2";
                    break;
                }
                switch (j)
                {
                case 0:
                    pair += "0";
                    break;
                case 1:
                    pair += "1";
                    break;
                case 2:
                    pair += "2";
                    break;
                }
                switch (k)
                {
                case 0:
                    pair += "0";
                    break;
                case 1:
                    pair += "1";
                    break;
                case 2:
                    pair += "2";
                    break;
                }
                pair_propabilities[counter] = f_pair_prop[pair] / (double)(size - 2);
                //cout << pair << " " << f_pair_prop[pair] << " " << pair_propabilities[counter] << endl;
                sum += pair_propabilities[counter];
                counter++;
                pair = "";
            }
        }
    }
    //cout << sum << endl;
    return count_shennon(counter, pair_propabilities) / 3;
}

void InsertSort(double* p, char* a, int size)
{
    int i, j;
    double t1;
    char t2;
    for (i = 1; i < size; i++)
    {
        t1 = p[i];
        t2 = a[i];
        for (j = i - 1; (j >= 0) && (t1 >= p[j]); j--)
        {
            p[j + 1] = p[j];
            a[j + 1] = a[j];
        }
        p[j + 1] = t1;
        a[j + 1] = t2;
    }
}

void shennon(double* p, string* codewords, int* l, double* q, int size)
{
    q[0] = 0.0;
    l[0] = (int)(-1 * log3(p[0]) + 1);

    for (int i = 1; i < size; i++)
    {
        q[i] = q[i - 1] + p[i - 1];
        if (p[i] > 0)
        {
            l[i] = (int)(-1 * log3(p[i]) + 1);
        }
    }

    for (int i = 0; i < size; i++)
    {
        double d0 = 0.0;
        double d1 = 1.0 / 3;
        double d2 = 2.0 / 3;
        double d3 = 1.0;
        double delta = 0.0;

        for (int j = 0; j < l[i]; j++)
        {
            if (q[i] >= d0 && q[i] <= d1)
            {
                codewords[i] += "0";

                d3 = d1;
            }
            else if (q[i] > d1 && q[i] <= d2)
            {
                codewords[i] += "1";

                d0 = d1;
                d3 = d2;
            }
            else if (q[i] > d2 && q[i] <= d3)
            {
                codewords[i] += "2";

                d0 = d2;
            }

            delta = (d3 - d0) / 3;
            d1 = d0 + delta;
            d2 = d1 + delta;
        }
    }
}

double erge(string* codewords, double* entropy, double* p, int size)
{
    double length = 0;

    for (int i = 0; i < size; i++)
    {
        if (p[i] > 0)
        {
            *entropy += -1 * p[i] * log3(p[i]);
            length += codewords[i].length() * p[i];
        }
    }

    return length;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    string line;
    int size = 33;
    double code_length = 0.0;
    double code_entropy = 0.0;

    string tail_file = "";
    string code_tail_file = "";
    //ifstream f1("i-svet-vo-tme-svetit.txt");
    ifstream f1("utro-pomeschika.txt");
    //ifstream f1("voyna-i-mir-tom-1.txt");

    int* l = new int[size];
    double* q = new double[size];
    char* alphabet = new char[size];
    string* codewords = new string[size];
    double* propabilities = new double[size];

    alphabet[size - 1] = ' ';
    for (int i = 0; i < size - 1; i++)
    {
        alphabet[i] = i - 32;
    }

    for (int i = 0; i < size; i++)
    {
        l[i] = 0;
        propabilities[i] = 0.0;
    }

    if (f1.is_open())
    {
        while (getline(f1, line))
        {
            tail_file += line;
        }
    }
    f1.close();

    char symbol = ' ';
    for (int i = 0; i < tail_file.size(); i++)
    {
        symbol = static_cast<char>(tail_file[i]);
        if (symbol == ' ')
        {
            propabilities[size - 1]++;
        }
        else
        {
            propabilities[symbol + 32]++;
        }
    }

    double sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        propabilities[i] /= tail_file.size();
        sum += propabilities[i];
    }
    cout << sum << endl;

    InsertSort(propabilities, alphabet, size);
    shennon(propabilities, codewords, l, q, size);

    for (int i = 0; i < size; i++)
    {
        cout << alphabet[i] << " " << codewords[i] << " " << propabilities[i] << endl;
    }

    code_length = erge(codewords, &code_entropy, propabilities, size);

    cout << "Code length: " << code_length << endl;
    cout << "Entropy: " << code_entropy << endl;
    cout << "Relativity: " << code_length - code_entropy << endl;

    for (int i = 0; i < tail_file.size(); i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (alphabet[j] == tail_file[i])
            {
                code_tail_file += codewords[j];
                break;
            }
        }
    }

    double code_propabilities[3]{};
    code_propabilities[0] = 0;
    code_propabilities[1] = 0;
    code_propabilities[2] = 0;

    for (int i = 0; i < code_tail_file.size(); i++)
    {
        if (code_tail_file[i] == '0')
        {
            code_propabilities[0]++;
        }
        else if(code_tail_file[i] == '1')
        {
            code_propabilities[1]++;
        }
        else
        {
            code_propabilities[2]++;
        }
    }

    code_propabilities[0] /= code_tail_file.size();
    code_propabilities[1] /= code_tail_file.size();
    code_propabilities[2] /= code_tail_file.size();

    cout << code_propabilities[0] + code_propabilities[1] + code_propabilities[2] << endl;
    cout << "0 - " << code_propabilities[0] << endl;
    cout << "1 - " << code_propabilities[1] << endl;
    cout << "2 - " << code_propabilities[2] << endl;

    cout << count_shennon(3, code_propabilities) << endl;
    cout << count_pairs(3, code_tail_file.size(), code_tail_file) << endl;
    cout << count_triples(3, code_tail_file.size(), code_tail_file) << endl;
}


