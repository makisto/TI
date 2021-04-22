#include <map>
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

double count_pairs(int n, int size, string file)
{
    int counter = 0;
    double sum = 0.0;
    string pair = "";
    map <string, int> f_pair_prop;
    double* pair_propabilities = new double[n * n];

    f_pair_prop["00"] = 0;
    f_pair_prop["01"] = 0;
    f_pair_prop["10"] = 0;
    f_pair_prop["11"] = 0;

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
            }
            switch (j)
            {
                case 0:
                    pair += "0";
                    break;
                case 1:
                    pair += "1";
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

    f_pair_prop["000"] = 0;
    f_pair_prop["001"] = 0;
    f_pair_prop["010"] = 0;
    f_pair_prop["011"] = 0;
    f_pair_prop["100"] = 0;
    f_pair_prop["101"] = 0;
    f_pair_prop["110"] = 0;
    f_pair_prop["111"] = 0;

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
                }
                switch (j)
                {
                case 0:
                    pair += "0";
                    break;
                case 1:
                    pair += "1";
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
    q[0] = 0;
    l[0] = (int)(-1 * log2(p[0]) + 1);
    for (int i = 1; i < size; i++)
    {
        q[i] = q[i - 1] + p[i - 1];
        if (p[i] > 0)
        {
            l[i] = (int)(-1 * log2(p[i]) + 1);
        }
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < l[i]; j++)
        {
            q[i] *= 2;
            if ((char)(q[i] + 48) == '2')
            {
                codewords[i] += "0";
            }
            else
            {
                codewords[i] += (char)(q[i] + 48);
            }
            if (q[i] > 1)
            {
                q[i]--;
            }
        }
    }
}

double erge(string* codewords, double *entropy, double* p, int size)
{
    double length = 0;

    for (int i = 0; i < size; i++)
    {
        if (p[i] > 0)
        {
            *entropy += -1 * p[i] * log2(p[i]);
            length += codewords[i].length() * p[i];
        }
    }

    return length;
}

int up(int n, double q, double* p)
{
    int j;
    int i;
    for (i = (n - 2); i > 0; i--)
    {
        if (p[i - 1] <= q)
        {
            p[i] = p[i - 1];
        }
        else
        {
            j = i;
            break;
        }
    }
    if (!i)
        j = 0;
    p[j] = q;
    return j;
}

void down(int n, int j, string* codewords)
{
    string s = codewords[j];
    for (int i = j; i < (n - 2); i++)
    {
        codewords[i] = codewords[i + 1];
    }
    codewords[n - 2].clear();
    codewords[n - 1].clear();
    codewords[n - 2] = s + "0";
    codewords[n - 1] = s + "1";
}

void huffman(int n, double* p, string* codewords)
{
    int j;
    double q;
    if (n == 2)
    {
        codewords[n - 2] = "0";
        codewords[n - 1] = "1";
    }
    else
    {
        q = p[n - 2] + p[n - 1];
        j = up(n, q, p);
        huffman(n - 1, p, codewords);
        down(n, j, codewords);
    }
}

int med(int l, int r, double* p)
{
    double sumL, sumR;
    sumL = 0;
    for (int i = l; i < r - 1; i++)
    {
        sumL += p[i];
    }
    sumR = p[r - 1];
    int m = r - 1;
    while (sumL >= sumR)
    {
        m--;
        sumL -= p[m];
        sumR += p[m];
    }
    return m;
}

void fano(int l, int r, string* codewords, double* p)
{
    if (l < r - 1)
    {
        int m = med(l, r, p);
        for (int i = l; i < r; i++)
        {
            if (i <= m)
            {
                codewords[i] += "0";
            }
            else
            {
                codewords[i] += "1";
            }
        }
        fano(l, m + 1, codewords, p);
        fano(m + 1, r, codewords, p);
    }
}

void gilbmur(string* codewords, int* l, double* q, double* p, int size)
{
    q[0] = 0;
    l[0] = (int)(-1 * log2(p[0]) + 1);
    for (int i = 1; i < size; i++)
    {
        q[i] = q[i - 1] + p[i - 1];
        if (p[i] > 0)
        {
            l[i] = (int)(-1 * log2(p[i]) + 2);
        }
    }
    for (int i = 0; i < size; i++)
    {
        q[i] += p[i] / 2;
    }
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < l[i]; j++)
        {
            q[i] *= 2;
            if ((char)(q[i] + 48) == '2')
            {
                codewords[i] += "0";
            }
            else
            {
                codewords[i] += (char)(q[i] + 48);
            }
            if (q[i] > 1)
            {
                q[i]--;
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Rus");

    string line;
    int size = 33;
    //int size = 256;
    double code_length = 0.0;
    double code_entropy = 0.0;

    string tail_file = "";
    string code_tail_file = "";
    ifstream f1("voyna-i-mir-tom-1.txt");
    //ifstream f1("i-svet-vo-tme-svetit.txt");
    //ifstream f1("utro-pomeschika.txt");

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

    /*for (int i = 0; i < size; i++)
    {
        alphabet[i] = i;
    }*/

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
        //propabilities[symbol]++;
    }

    double sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        if (propabilities[i] > 0)
        {
            propabilities[i] /= tail_file.size();
            sum += propabilities[i];
        }
    }
    cout << sum << endl;

    //gilbmur(codewords, l, q, propabilities, size);
    
    InsertSort(propabilities, alphabet, size);
    
    for (int i = 0; i < size; i++)
    {
        sum += propabilities[i];
    }
    cout << sum << endl;
    int lk = 0;
    while (propabilities[lk] != 0)
    {
        lk++;
    }
    int kl = lk;
    double *p1 = new double[size];
    for (int i = 0; i < size; i++)
    {
        p1[i] = propabilities[i];
    }

    fano(0, kl, codewords, propabilities);
    //huffman(kl, p1, codewords);

    //shennon(propabilities, codewords, l, q, size);

    for (int i = 0; i < size; i++)
    {
        if (propabilities[i] > 0)
        {
            cout << alphabet[i] << " " << codewords[i] << " " << propabilities[i] << endl;
        }
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

    double code_propabilities[2]{};
    code_propabilities[0] = 0;
    code_propabilities[1] = 0;

    for (int i = 0; i < code_tail_file.size(); i++)
    {
        if (code_tail_file[i] == '0')
        {
            code_propabilities[0]++;
        }
        else
        {
            code_propabilities[1]++;
        }
    }

    code_propabilities[0] /= code_tail_file.size();
    code_propabilities[1] /= code_tail_file.size();

    cout << code_propabilities[0] + code_propabilities[1] << endl;
    cout << "0 - " << code_propabilities[0] << endl;
    cout << "1 - " << code_propabilities[1] << endl;

    cout << count_shennon(2, code_propabilities) << endl;
    cout << count_pairs(2, code_tail_file.size(), code_tail_file) << endl;
    cout << count_triples(2, code_tail_file.size(), code_tail_file) << endl;
}

