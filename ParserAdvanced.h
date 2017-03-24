#pragma once
#ifndef ADVANCED__ParserTxtFile__H__
#define ADVANCED__ParserTxtFile__H__

#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<chrono>

#pragma warning(disable: 4838)
#pragma warning(disable: 4309)
#pragma warning(disable: 4244)

	class ParserTxtFile
	{
		private:
			double* a = nullptr;
			double* b = nullptr;
			int   * c = nullptr;
			const char* __address__;
			int LOCS;
			FILE* fp0;
			FILE* fp;
			std::chrono::steady_clock::time_point start;
			std::chrono::steady_clock::time_point end;
			void CharArrayToInteger(char*, int*) noexcept;
			void EnterAtTheEndofFile();
			void OpenAndParse() noexcept;
			void InitialParser(char*, char*);
			void CloseFile();
		public:
			ParserTxtFile(const char*);
			int& NumberOfLinesInFile() noexcept;
			void Print(const int&) const noexcept;
			void GiveTime() const noexcept;
			double* XCoordination();
			double* YCoordination();
			int* Frame();
			~ParserTxtFile();
	};
#endif // !ADVANCED__ParserTxtFile__H__

