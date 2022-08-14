#include "Address.h"
#include <iostream>
#include <string>

//ReadBytes(processName, offsets, numBytes, compareValues)
std::vector<byte> ADDRESS::ReadBytes(const wchar_t* processName, std::vector<unsigned int> offsets, unsigned int numBytes, std::vector<byte> compareValues)
{
	//if compareValues == Null, skip compare step and set initialValues = currentValues
	if (numBytes < compareValues.size())
	{
		currentValues.resize(compareValues.size());
	}
	else
	{
		currentValues.resize(numBytes);
	}


	// ------------------------------------------------------------------------------------------------------
	//baseOffset = 0x10C4EA; //Cutscene Skip
	baseOffset = offsets[0]; //Get base offset
	std::vector<unsigned int> otherOffsets(offsets.begin() + 1, offsets.end()); //Gets all offsets after the first

	offsets = { }; //Cutscene Skip { 0x0, 0x0, 0x0 }
	processId = GetProcId(processName);											//Get pID
	moduleBase = GetModuleBaseAddress(processId, processName);					//Get module base address
	processHandle = 0;															//Get process handle
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);			//Open process
	pointerBase = moduleBase + baseOffset;										//Calculate offsets
	uintptr_t address = FindDMAAddy(processHandle, pointerBase, otherOffsets);	//Get address
	uintptr_t globalTargetAddress = address;

	modifiedValues = { 0x74, 0x90 };

	ReadProcessMemory(processHandle, (BYTE*)address, currentValues.data(), currentValues.size(), nullptr);

	//MessageBox for debug output
	int n = 1;
	if (currentValues.size() >= n)
	{
		std::string outputText = std::to_string(currentValues[n]);
		//std::string outputText = std::to_string(address);
		MessageBoxA(NULL, outputText.c_str(), "Title", MB_OK);
	}

	//currentValues = modifiedValues;

	//WriteProcessMemory(processHandle, (BYTE*)address, modifiedValues.data(), modifiedValues.size(), nullptr);
	// ------------------------------------------------------------------------------------------------------

	//Prepare return values
	std::vector<byte> currentValuesReturn = currentValues;
	currentValuesReturn.resize(numBytes);

	return currentValues;
}

//// Write Byte Values
//std::vector<byte> ADDRESS::ReadBytes(const wchar_t* processName, std::vector<unsigned int> offsets, std::vector<byte> initialValues, std::vector<byte> modifiedValues, std::vector<bool> byteMask)
//std::vector<byte> ADDRESS::WriteBytes(unsigned int numberOfBytes)
//{
//	//Write the addresses like what was happening in main() of the test program
//	return currentValues;
//}