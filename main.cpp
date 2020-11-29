#include<iostream>
#include<fstream>
#include<string>
#include<locale.h>
#include<cstdlib>
#include<cassert>

using namespace std;
void connect(char *filename);

bool comp(string s, string t)
{
	if (s.empty()) return 1;
	if (t.empty()) return 0;
	int i = 0;
	while (s[i] != '(') i++;
	char tmp[] = { s[i + 1], s[i + 2], s[i + 3], s[i + 4], 0 };
	int s_year = atoi(tmp);
	i = 0;
	while (t[i] != '(') i++;
	char tmp2[] = { t[i + 1], t[i + 2], t[i + 3], t[i + 4], 0 };
	int t_year = atoi(tmp2);
	return s_year <= t_year;
}


void split(char* filename)
{
	ifstream fin(filename);
	ofstream fout1("1.txt");
	ofstream fout2("2.txt");

	int file = 0;
	string s1, s2;
	getline(fin, s1);
	getline(fin, s2);
	fout1 << s1 << endl;

	while (!fin.eof())
	{
		if (comp(s1, s2))
		{
			if (file) fout2 << s2 << endl;
			else fout1 << s2 << endl;
		}
		else
		{
			if (file)
			{
				fout1 << s2 << endl;
			}
			else
			{
				fout2 << s2 << endl;
			}
			file = (file + 1) % 2;
		}
		s1 = s2;
		getline(fin, s2);
	}
	fin.close();
	fout1.close();
	fout2.close();
	connect(filename);
}

void connect(char* filename)
{
	ifstream fin1("1.txt");
	ifstream fin2("2.txt");
	ofstream fout(filename);

	string s2, s1, lastString = "";
	int file = 0;
	getline(fin1, s1);
	getline(fin2, s2);
	if (fin2.eof())
    {
		while (!fin1.eof())
		{
			fout << s1 << endl;
			getline(fin1, s1);
		}
	}
	else
	{
		while (!fin1.eof() && !fin2.eof())
        {
			if (comp(s1, s2)) {								//
				if (comp(lastString, s1))
				{
					fout << s1 << endl;
					file = 0;
					lastString = s1;
					getline(fin1, s1);
				}
				else
				{
					while (comp(lastString, s2))
					{
						fout << s2 << endl;
						lastString = s2;
						getline(fin2, s2);
					}
					lastString = "";
				}
			}
			else {
				if (comp(lastString, s2))
				{
					fout << s2 << endl;
					file = 1;
					lastString = s2;
					getline(fin2, s2);
				}
				else {
					while (comp(lastString, s1))
					{
						fout << s1 << endl;
						lastString = s1;
						getline(fin1, s1);
					}
					lastString = "";
				}
			}
		}
		while (!fin1.eof())
        {
			fout << s1 << endl;
			getline(fin1, s1);
		}

		while (!fin2.eof())
        {
			fout << s2 << endl;
			getline(fin2, s2);
		}
		split(filename);
	}
}


int main()
{
	split("films.txt");
	return 0;
}

