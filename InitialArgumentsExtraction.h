#pragma once
#ifndef INITIAL_ARGUMENTS_EXTRACTION__H__
#define INITIAL_ARGUMENTS_EXTRACTION__H__

#define _CRT_SECURE_NO_DEPRECATE

#include<iostream>
#include<stdio.h>

#pragma warning(disable: 4244)

	class InitialArgumentsExtractionFromTextFile
	{
		private:
			char* Address = nullptr;
			FILE* fp;
			char str[100], Num1[100], Num2[100], Num3[100], Num4[100];
			int x, y, wi, hi;
			const char* _address_;
			void CharArrayToNumber(const char*, int*);
			const char* CharArrayToAddressConvert(char*);
		public:
			InitialArgumentsExtractionFromTextFile();
			const char* Get_address() noexcept;
			int Get_x() noexcept;
			int Get_y() noexcept; 
			int Get_Wi() noexcept;
			int Get_Hi() noexcept;
			~InitialArgumentsExtractionFromTextFile();
	};

#endif // !INITIAL_ARGUMENTS_EXTRACTION__H__
