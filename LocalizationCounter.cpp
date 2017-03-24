#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<string>
#include"LocalizationCounter.h"
#include"ParserAdvanced.h"
#include"InitialArgumentsExtraction.h"

void LocalizationCounter::LocsInROI (
	const double& ROI_X_Coordinate,
	const double& ROI_Y_Coordinate,
	const int& width,
	const int& height
)
{
	for (; loop_counter != MainTextFile->NumberOfLinesInFile(); ++loop_counter)
	{
		if (X[loop_counter] >= ROI_X_Coordinate && X[loop_counter] <= (ROI_X_Coordinate + (double)(width))
			&& Y[loop_counter] >= ROI_Y_Coordinate && Y[loop_counter] <= (ROI_Y_Coordinate + (double)(height))
			)
		{
			ROI_By_Coordination[FinalStructCounter] = { X[loop_counter], Y[loop_counter], frame[loop_counter] };
			++FinalStructCounter;
			++LocCountsAfterROI;
		}
	}
	ROI_By_Coordination[FinalStructCounter] = { -1, -1, -10 }; // terminating condition
	void* i = ROI_By_Coordination;
	void* j = CopyOf_ROI_By_Coordination;
	while (((FinalArray*)i)->_x_ != -1
		&& ((FinalArray*)i)->_y_ != -1
		&& ((FinalArray*)i)->_frm_ != -10
	)
	{
		*(FinalArray*)j = *(FinalArray*)i;
		i = (char*)i + sizeof(FinalArray);
		j = (char*)j + sizeof(FinalArray);
	}
	((FinalArray*)j)->_x_ = -1;
	((FinalArray*)j)->_y_ = -1;
	((FinalArray*)j)->_frm_ = -10;
	std::cout << "Finding Locs in the provided ROI completed!\n";
	return;
}
void LocalizationCounter::GenerateOutputTextFile(const char* _address) noexcept
{
	size_t tempCounter = 0;
	std::fstream roiGeneratedLocsOutputTextFile;
	roiGeneratedLocsOutputTextFile.open(_address, std::ios::out);
	roiGeneratedLocsOutputTextFile << "All Counts = " << LocCountsAfterROI << '\n';
	roiGeneratedLocsOutputTextFile << "Refined Counts = " << 0x00 << '\n';
	roiGeneratedLocsOutputTextFile << "-----------------------------------\n";
	while ((ROI_By_Coordination[tempCounter])._x_ != -1
		&& (ROI_By_Coordination[tempCounter])._y_ != -1
		&& (ROI_By_Coordination[tempCounter])._frm_ != -10
	)
	{
		roiGeneratedLocsOutputTextFile << "x(px): " <<
			(ROI_By_Coordination[tempCounter])._x_ << "\ty(px): " <<
			(ROI_By_Coordination[tempCounter])._y_ << "\tframe: " <<
			(ROI_By_Coordination[tempCounter])._frm_ << '\n';
		++tempCounter;
	}
	roiGeneratedLocsOutputTextFile.close();
	std::cout << "Saving Locs in ROI completed!\n";
	return;
}
void LocalizationCounter::GenerateGroupedByCoordinationOutputTextFile (
	const double& precision,
	const char*  _address
) const noexcept
{
	size_t GroupedLocs  = 0;
	void* StartPointer  = nullptr;
	void* MovingPointer = nullptr;
	StartPointer = ROI_By_Coordination;
	MovingPointer = (char*)ROI_By_Coordination + sizeof(FinalArray);
	std::fstream RefinedroiGeneratedLocsOutputTextFile;
	RefinedroiGeneratedLocsOutputTextFile.open(_address, std::ios::out);
	while (((FinalArray*)StartPointer)->_x_ != -1
		&& ((FinalArray*)StartPointer)->_y_ != -1
		&& ((FinalArray*)StartPointer)->_frm_ != -10
	)
	{
		RefinedroiGeneratedLocsOutputTextFile << "x(px): " <<
			((FinalArray*)(StartPointer))->_x_ << "\ty(px): " <<
			((FinalArray*)(StartPointer))->_y_ << "\tframe: " <<
			((FinalArray*)(StartPointer))->_frm_ << '\n';
		while (((FinalArray*)MovingPointer)->_x_ != -1
			&& ((FinalArray*)MovingPointer)->_y_ != -1
			&& ((FinalArray*)MovingPointer)->_frm_ != -10
		)
		{
			double tmp_x = (((FinalArray*)(MovingPointer))->_x_ - ((FinalArray*)StartPointer)->_x_);
			double tmp_y = (((FinalArray*)(MovingPointer))->_y_ - ((FinalArray*)StartPointer)->_y_);
			double tmp_frm = (((FinalArray*)(MovingPointer))->_frm_ - ((FinalArray*)StartPointer)->_frm_);
			if ((tmp_x*tmp_x) + (tmp_y*tmp_y) <= (precision*precision))
			{
				RefinedroiGeneratedLocsOutputTextFile << "x(px): " <<
					((FinalArray*)(MovingPointer))->_x_ << "\ty(px): " <<
					((FinalArray*)(MovingPointer))->_y_ << "\tframe: " <<
					((FinalArray*)(MovingPointer))->_frm_ << '\n';
				// dumping condition
				((FinalArray*)MovingPointer)->_x_ = -2;
				((FinalArray*)MovingPointer)->_y_ = -2;
				((FinalArray*)MovingPointer)->_frm_ = -20;
				MovingPointer = (char*)MovingPointer + sizeof(FinalArray);
			}
			else
			{
				MovingPointer = (char*)MovingPointer + sizeof(FinalArray);
			}
		}
		StartPointer = (char*)StartPointer + sizeof(FinalArray);
		while (((FinalArray*)StartPointer)->_x_ == -2
			&& ((FinalArray*)StartPointer)->_y_ == -2
			&& ((FinalArray*)StartPointer)->_frm_ == -20
		)
		{
			StartPointer = (char*)StartPointer + sizeof(FinalArray);
		}
		MovingPointer = (char*)StartPointer + sizeof(FinalArray);
		++GroupedLocs;
		RefinedroiGeneratedLocsOutputTextFile << "---------------------------------------------\n";
	}
	RefinedroiGeneratedLocsOutputTextFile << "The number of Grouped Locs = " << GroupedLocs << '\n';
	RefinedroiGeneratedLocsOutputTextFile.close();
	std::cout << "Saving Refined_Locs in ROI completed!\n";
	return;
}
void LocalizationCounter::GenerateGroupedByCoordination_and_FrameDarkTimeOutputTextFile (
	const double& precision,
	const int&   DarkTime,
	const char*  _address
) const noexcept
{
	size_t GroupedLocs = 0;
	void* StartPointer = nullptr;
	void* MovingPointer = nullptr;

	StartPointer = CopyOf_ROI_By_Coordination;
	MovingPointer = (char*)CopyOf_ROI_By_Coordination + sizeof(FinalArray);
	int internal_frm = ((FinalArray*)(StartPointer))->_frm_;
	std::fstream RefinedroiGeneratedLocsOutputTextFile;
	RefinedroiGeneratedLocsOutputTextFile.open(_address, std::ios::out);
	while (((FinalArray*)StartPointer)->_x_ != -1
		&& ((FinalArray*)StartPointer)->_y_ != -1
		&& ((FinalArray*)StartPointer)->_frm_ != -10
	)
	{
		RefinedroiGeneratedLocsOutputTextFile << "x(px): " <<
			((FinalArray*)(StartPointer))->_x_ << "\ty(px): " <<
			((FinalArray*)(StartPointer))->_y_ << "\tframe: " <<
			((FinalArray*)(StartPointer))->_frm_ << '\n';
		while (((FinalArray*)MovingPointer)->_x_ != -1
			&& ((FinalArray*)MovingPointer)->_y_ != -1
			&& ((FinalArray*)MovingPointer)->_frm_ != -10
		)
		{
			double tmp_x = (((FinalArray*)(MovingPointer))->_x_ - ((FinalArray*)StartPointer)->_x_);
			double tmp_y = (((FinalArray*)(MovingPointer))->_y_ - ((FinalArray*)StartPointer)->_y_);
			double tmp_frm = (((FinalArray*)(MovingPointer))->_frm_ - internal_frm);
			if ((tmp_x*tmp_x) + (tmp_y*tmp_y) <= (precision*precision))
			{
				if (tmp_frm <= DarkTime)
				{
					RefinedroiGeneratedLocsOutputTextFile << "x(px): " <<
						((FinalArray*)(MovingPointer))->_x_ << "\ty(px): " <<
						((FinalArray*)(MovingPointer))->_y_ << "\tframe: " <<
						((FinalArray*)(MovingPointer))->_frm_ << '\n';
					internal_frm = ((FinalArray*)MovingPointer)->_frm_;
					// dumping condition
					((FinalArray*)MovingPointer)->_x_ = -2;
					((FinalArray*)MovingPointer)->_y_ = -2;
					((FinalArray*)MovingPointer)->_frm_ = -20;
					MovingPointer = (char*)MovingPointer + sizeof(FinalArray);
				}
				else
				{
					MovingPointer = (char*)MovingPointer + sizeof(FinalArray);
				}
			}
			else
			{
				MovingPointer = (char*)MovingPointer + sizeof(FinalArray);
			}
		}
		StartPointer = (char*)StartPointer + sizeof(FinalArray);
		while (((FinalArray*)StartPointer)->_x_ == -2
			&& ((FinalArray*)StartPointer)->_y_ == -2
			&& ((FinalArray*)StartPointer)->_frm_ == -20
		)
		{
			StartPointer = (char*)StartPointer + sizeof(FinalArray);
		}
		MovingPointer = (char*)StartPointer + sizeof(FinalArray);
		++GroupedLocs;
		RefinedroiGeneratedLocsOutputTextFile << "---------------------------------------------\n";
	}
	RefinedroiGeneratedLocsOutputTextFile << "The number of Grouped Locs = " << GroupedLocs << '\n';
	RefinedroiGeneratedLocsOutputTextFile.close();
	std::cout << "Saving Refined_Locs in ROI completed!\n";
	return;
}
LocalizationCounter::LocalizationCounter()
{
	const char* FileAddress = CoordinatesFile.Get_address();
	MainTextFile = new ParserTxtFile(FileAddress);
	X = MainTextFile->XCoordination();
	Y = MainTextFile->YCoordination();
	frame = MainTextFile->Frame();
	ROI_By_Coordination = (FinalArray*)malloc(MainTextFile->NumberOfLinesInFile() * sizeof(FinalArray));
	CopyOf_ROI_By_Coordination = (FinalArray*)malloc(MainTextFile->NumberOfLinesInFile() * sizeof(FinalArray));
	this->LocsInROI(
		CoordinatesFile.Get_x() /5,
		CoordinatesFile.Get_y() /5, 
		CoordinatesFile.Get_Wi()/5, 
		CoordinatesFile.Get_Hi()/5
	);
	this->GenerateOutputTextFile("C:\\Users\\...\\.txt");
	this->GenerateGroupedByCoordinationOutputTextFile (
		0.5,
		"C:\\Users\\...\\.txt"
	);
	this->GenerateGroupedByCoordination_and_FrameDarkTimeOutputTextFile (
		0.5,
		100,
		"C:\\Users\\...\\.txt"
	);
}
LocalizationCounter::~LocalizationCounter()
{
	if(ROI_By_Coordination != nullptr)
		free(ROI_By_Coordination);
	if(CopyOf_ROI_By_Coordination != nullptr)
		free(CopyOf_ROI_By_Coordination);
	if(MainTextFile != nullptr)
		delete(MainTextFile);
	MainTextFile = nullptr;
	ROI_By_Coordination = nullptr;
	CopyOf_ROI_By_Coordination = nullptr;
}