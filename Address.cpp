#include "Address.h"
#include <iostream>
#include <string>

//GetAddress
uintptr_t ADDRESS::GetAddress(const wchar_t* processName, std::vector<unsigned int> offsets) //Returns the bytes that were read
{
	baseOffset = offsets[0]; //Get base offset
	std::vector<unsigned int> otherOffsets(offsets.begin() + 1, offsets.end()); //Gets all offsets after the first
	offsets = { };																//{ 0x0, 0x0, 0x0 }
	processId = GetProcId(processName);											//Get pID
	moduleBase = GetModuleBaseAddress(processId, processName);					//Get module base address
	processHandle = 0;															//Get process handle
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);			//Open process
	pointerBase = moduleBase + baseOffset;										//Calculate offsets
	address = FindDMAAddy(processHandle, pointerBase, otherOffsets);			//Get address

	return address;
}

//ReadBytes(processName, offsets, numBytes, compareValues)
std::vector<byte> ADDRESS::ReadBytes(const wchar_t* processName, std::vector<unsigned int> offsets, unsigned int numBytes)
{
	if (numBytes)
	{
		currentValues.resize(numBytes);
		if (GetAddress(processName, offsets))
			ReadProcessMemory(processHandle, (BYTE*)address, currentValues.data(), currentValues.size(), nullptr);

		////MessageBox for debug output
		//int n = 1;
		//if (currentValues.size() >= n)
		//{
		//	std::string outputText = std::to_string(currentValues[n]);
		//	//std::string outputText = std::to_string(address);
		//	MessageBoxA(NULL, outputText.c_str(), "Title", MB_OK);
		//}
	}
	return currentValues;
}

//// Write Byte Values
std::vector<byte> ADDRESS::WriteBytes(const wchar_t* processName, std::vector<unsigned int> offsets, std::vector<byte> modifiedValues) //Returns the bytes that were written
{
	//modifiedValues = { 0x74, 0x90 };

	currentValues = modifiedValues;
	if (!WriteProcessMemory(processHandle, (BYTE*)address, currentValues.data(), currentValues.size(), nullptr))
		currentValues = {};
	return currentValues;
}

std::vector<byte> ADDRESS::SetRestore(std::vector<byte> restore)
{
	restoreValues == restore;
	return restoreValues;
}