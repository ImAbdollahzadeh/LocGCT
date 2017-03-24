#include"InitialArgumentsExtraction.h"
#include<fstream>
#include<math.h>

void 
InitialArgumentsExtractionFromTextFile::
CharArrayToNumber(const char* ch, int* number)
{
	int size = 0;
	while (ch[size] != '\n')
	{
		++size;
	}
	*number = 0;
	for (int i = 0; i != size; ++i)
	{
		*number += (int)((ch[i] - '0')) * (pow(10, size - i - 1));
	}
	return;
}
const char* 
InitialArgumentsExtractionFromTextFile::
CharArrayToAddressConvert(char* ch)
{
	int size = 0;
	while (ch[size] != '\n')
	{
		++size;
	}
	Address = (char*)malloc(sizeof(char)*size + 0x01);
	int i = 0;
	while (i != size)
	{
		Address[i] = ch[i];
		++i;
	}
	Address[i] = '\0';
	return const_cast<const char*>(Address);
}
InitialArgumentsExtractionFromTextFile::
InitialArgumentsExtractionFromTextFile() :
	fp(fopen("C:\\Users\\...\\.txt", "r"))
{
	fgets(str, 100, fp);
	_address_ = this->CharArrayToAddressConvert(str);
	fgets(Num1, 100, fp);
	this->CharArrayToNumber(Num1, &x);
	fgets(Num2, 100, fp);
	this->CharArrayToNumber(Num2, &y);
	fgets(Num3, 100, fp);
	this->CharArrayToNumber(Num3, &wi);
	fgets(Num4, 100, fp);
	this->CharArrayToNumber(Num4, &hi);
}
const char* 
InitialArgumentsExtractionFromTextFile::Get_address() noexcept
{
	return _address_;
}
int
InitialArgumentsExtractionFromTextFile::Get_x() noexcept
{
	return x;
}
int
InitialArgumentsExtractionFromTextFile::Get_y() noexcept
{
	return y;
}
int
InitialArgumentsExtractionFromTextFile::Get_Wi() noexcept
{
	return wi;
}
int
InitialArgumentsExtractionFromTextFile::Get_Hi() noexcept
{
	return hi;
}
InitialArgumentsExtractionFromTextFile::
~InitialArgumentsExtractionFromTextFile()
{
	fclose(fp);
	free(Address);
	Address = nullptr;
	std::cout << "resource cleaned" << std::endl;
}
