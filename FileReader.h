#pragma once
# include <iostream>
# include <sstream>
# include <fstream>

using namespace std;


static class FileReader
{
public:
	FileReader();
	static char* ReadFromFile(char *filename)
	{
		std::ifstream file;
		file.exceptions(std::ifstream::badbit);
		stringstream str_stream;
		std::string str;
		char *buffer = NULL;
		try
		{
			file.open(filename);
			if (file.is_open())
			{
				str_stream << file.rdbuf();
				str = str_stream.str();
				buffer = _strdup(str.c_str());
				return buffer;
			}
			else
				return NULL;
			file.close();
		}
		catch (std::exception e)
		{
			ofstream g;
			g.open("log.txt", std::ofstream::app);
			g << "\nEroare la citirea index-ului\n";
		}
	}
	static void BinaryRead(char * &sir, int & lenght)
	{
		std::ifstream file;
		file.open(sir, std::istream::in | std::ios::binary);
		std::streampos fsize = 0;
		fsize = file.tellg();
		file.seekg(0, std::ios::end);
		fsize = file.tellg() - fsize;
		file.close();
		int n = fsize;
		file.open(sir, istream::in | ios::binary);
		std::cout << n << " " << endl;
		int z = 0;
		char *p = new  char[n + 1];
		for (int i = 0;i < n;i++)
		{
			char ch;
			file.get(ch);
			p[i] = ch;
		}
		file.close();
		delete sir;
		lenght = n;
		sir = p;
	}
	static void CBinaryRead(char * &sir, int & lenght)
	{
		std::ifstream file;
		file.open(sir, std::istream::in | std::ios::binary);
		std::streampos fsize = 0;
		fsize = file.tellg();
		file.seekg(0, std::ios::end);
		fsize = file.tellg() - fsize;
		file.close();
		int n = fsize;
		char *p = new  char[n + 1];
		/*file.open(sir, istream::in | ios::binary);
		std::cout << n << " " << endl;
		int z = 0;
		
		for (int i = 0;i < n;i++)
		{
			char ch;
			file.get(ch);
			p[i] = ch;
		}
		file.close();*/
		FILE *filee = NULL;
		filee = fopen(sir, "rb");
		if (filee != NULL)
			fread(p, 1, n, filee);
		else
			p = NULL;
		delete sir;
		lenght = n;
		sir = p;
	}
	~FileReader();
};

