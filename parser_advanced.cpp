#define _CRT_SECURE_NO_DEPRECATE
#include"ParserAdvanced.h"
#include<stdio.h>
#include<iostream>
#include<math.h>
#define LENGTH_OF_INITIAL_BUFFER 285
#define LENGTH_OF_BUFFER 15

void ParserTxtFile::InitialParser(char* ch, char* target)
{
	int i = 0;
	while (ch[i] != ':')
	{
		++i;
	}
	++i;
	++i;
	int j = 0;
	while (ch[i] != '\n')
	{
		target[j] = ch[i];
		++j;
		++i;
	}
	target[j] = '\n';
	return;
}
void ParserTxtFile::CharArrayToInteger(char* ch, int* number) noexcept
{
	int __tmp = 0;
	while (ch[__tmp] != '\n')
		++__tmp;
	for (size_t i = 0; i != __tmp; ++i)
	{
		*number += (int)((ch[i] - '0') * pow(10, (__tmp - i - 1)));
	}
	if (*number % 2 == 0)
	{
		EnterAtTheEndofFile();
	}
	return;
}
void ParserTxtFile::EnterAtTheEndofFile()
{
	fp0 = fopen(__address__, "a+");
	fprintf(fp0, "%c", '\n');
	fclose(fp0);
	return;
}
void ParserTxtFile::OpenAndParse() noexcept
{
	fp = fopen(__address__, "r");
	char hiddenHeader[40] = { 0 };
	char hiddenHeader_II[LENGTH_OF_INITIAL_BUFFER] = { 0 };
	fgets(hiddenHeader, LENGTH_OF_INITIAL_BUFFER, fp);
	char tmp[10] = { 171, 171, 171, 171, 171, 171, 171, 171, 171, 171 };
	InitialParser(hiddenHeader, tmp);
	CharArrayToInteger(tmp, &LOCS);
	fgets(hiddenHeader_II, LENGTH_OF_INITIAL_BUFFER, fp);
	a = (double*)malloc(sizeof(double) * LOCS);
	b = (double*)malloc(sizeof(double) * LOCS);
	c = (int*)malloc(sizeof(int) * LOCS);
	char _a[LENGTH_OF_BUFFER], _b[LENGTH_OF_BUFFER], 
		 _c[LENGTH_OF_BUFFER], str[LENGTH_OF_INITIAL_BUFFER];
	void
		*p_a = _a,
		*p_b = _b,
		*p_c = _c,
		*p_str = str;
	int counter = 0;
	while (true)
	{
		if (fgets(str, LENGTH_OF_INITIAL_BUFFER, fp) != NULL)
		{
			if (str[0] == '\n')
			{
				break;
			}
			a[counter] = 0.0;
			b[counter] = 0.0;
			c[counter] = 0;
			int i = 0;
			while (str[i] != ' ')
				++i;
			++i;
			int j = 0;
			int floatCounter1 = 0;
			int floatBoolean1 = false;
			while (str[i] != ' ')
			{
				*(char*)((char*)p_a + j) = *(char*)((char*)p_str + i);
				//_b[j] = str[i];
				if (str[i] != '.' && floatBoolean1 == false)
				{
					++floatCounter1;
				}
				if (str[i] == '.')
				{
					floatBoolean1 = true;
				}
				++i;
				++j;
			}
			_a[j] = '\0';
			for (int n = 0; n != floatCounter1; ++n)
			{
				a[counter] += (double)(_a[n] - '0')*(pow(10, (floatCounter1 - n - 1)));
			}
			for (int n = floatCounter1 + 1; n != j; ++n)
			{
				a[counter] += (double)(_a[n] - '0')*(pow(10, (floatCounter1 - n)));
			}
			/*First Double Done*/

			++i;
			int k = 0;
			int floatCounter2 = 0;
			int floatBoolean2 = false;
			while (str[i] != ' ')
			{
				*(char*)((char*)p_b + k) = *(char*)((char*)p_str + i);
				//_c[k] = str[i];
				if (str[i] != '.' && floatBoolean2 == false)
				{
					++floatCounter2;
				}
				if (str[i] == '.')
				{
					floatBoolean2 = true;
				}
				++i;
				++k;
			}
			_b[k] = '\0';
			for (int n = 0; n != floatCounter2; ++n)
			{
				b[counter] += (double)(_b[n] - '0')*(pow(10, (floatCounter2 - n - 1)));
			}
			for (int n = floatCounter2 + 1; n != k; ++n)
			{
				b[counter] += (double)(_b[n] - '0')*(pow(10, (floatCounter2 - n)));
			}
			/*Second Double Done*/

			++i;
			for (size_t WhileLooper = 0; WhileLooper != 10; ++WhileLooper)
			{
				while (str[i] != ' ')
					++i;
				++i;
			}
			int N = 0;
			while (str[i] != '\n')
			{
				*(char*)((char*)p_c + N) = *(char*)((char*)p_str + i);
				//_a[i] = str[i];
				++i;
				++N;
			}
			_c[N] = '\0';
			for (int j = 0; j != N; ++j)
			{
				c[counter] += (_c[j] - '0')*(pow(10, (N - j - 1)));
			}
			++counter;
		}
		else
		{
			break;
		}
	}
}
int& ParserTxtFile::NumberOfLinesInFile() noexcept
{
	return LOCS;
}
void ParserTxtFile::Print(const int& Size) const noexcept
{
	for (int i = 0; i != Size; ++i)
	{
		std::cout << a[i] << ", " << b[i] << ", " << c[i] << std::endl;
	}
}
void ParserTxtFile::CloseFile()
{
	fclose(fp);
}
void ParserTxtFile::GiveTime() const noexcept
{
	std::chrono::duration<double> diff = end - start;
	std::cout << "Time (ms): " << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << '\n';
}
double* ParserTxtFile::XCoordination()
{
	return a;
}
double* ParserTxtFile::YCoordination()
{
	return b;
}
int* ParserTxtFile::Frame()
{
	return c;
}
ParserTxtFile::ParserTxtFile(const char* AddressOfFile) :
	__address__ (AddressOfFile)
	, LOCS(0)
{
	start = std::chrono::high_resolution_clock::now();
	this->EnterAtTheEndofFile();
	this->OpenAndParse();
	this->CloseFile();
	end = std::chrono::high_resolution_clock::now();
}
ParserTxtFile::~ParserTxtFile()
{
	if(a != nullptr)
		free(a);
	if(b != nullptr)
		free(b);
	if(c != nullptr)
		free(c);
	a = nullptr;
	b = nullptr;
	c = nullptr;
}