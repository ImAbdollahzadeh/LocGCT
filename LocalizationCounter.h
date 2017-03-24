#ifndef LOCALIZATION_COUNTER_H_
#define LOCALIZATION_COUNTER_H_
#include<iostream>
#include<fstream>
#include "ParserAdvanced.h"
#include "InitialArgumentsExtraction.h"

	class LocalizationCounter
	{
		private:
			InitialArgumentsExtractionFromTextFile CoordinatesFile;
			ParserTxtFile* MainTextFile = nullptr;
			struct FinalArray
			{
				double _x_, _y_;
				int   _frm_;
			} 
			*CopyOf_ROI_By_Coordination = nullptr, 
			*ROI_By_Coordination        = nullptr;
			double* X     = nullptr, 
				  * Y     = nullptr;
			int   * frame = nullptr;
			double x_LineByLine, y_LineByLine;
			int   frame_LineByLine;
			size_t NumberofLinesInTextFilecount = 0;
			size_t LocCountsAfterROI            = 0;
			size_t loop_counter                 = 0;
			size_t FinalStructCounter           = 0;
			void LocsInROI(const double&, const double&, const int&, const int&);
			void GenerateOutputTextFile(const char*) noexcept;
			void GenerateGroupedByCoordinationOutputTextFile(const double&, const char*) const noexcept;
			void GenerateGroupedByCoordination_and_FrameDarkTimeOutputTextFile(const double&, const int&, const char*) const noexcept;
		public:
			LocalizationCounter();
			~LocalizationCounter();
	};

#endif // !LOCALIZATION_COUNTER_H_
