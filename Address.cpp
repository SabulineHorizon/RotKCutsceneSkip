#include "Address.h"

//GetAddress
uintptr_t ADDRESS::GetAddress(const wchar_t* processName, std::vector<unsigned int> offsets) //Returns the bytes that were read
{
	std::vector<unsigned int> otherOffsets(offsets.begin() + 1, offsets.end()); //Gets all offsets after the first
	processId = GetProcId(processName);											//Get pID
	moduleBase = GetModuleBaseAddress(processId, processName);					//Get module base address
	processHandle = 0;															//Get process handle
	processHandle = OpenProcess(PROCESS_ALL_ACCESS, NULL, processId);			//Open process
	pointerBase = moduleBase + offsets[0];										//Calculate offsets
	address = FindDMAAddy(processHandle, pointerBase, otherOffsets);			//Get address

	return address;
}

//ReadBytes
std::vector<byte> ADDRESS::ReadBytes(const wchar_t* processName, std::vector<unsigned int> offsets, unsigned int numBytes)
{
	if (numBytes)
	{
		currentValues.resize(numBytes);
		if (GetAddress(processName, offsets))
			ReadProcessMemory(processHandle, (BYTE*)address, currentValues.data(), currentValues.size(), nullptr);
	}
	return currentValues;
}

// WriteBytes
std::vector<byte> ADDRESS::WriteBytes(const wchar_t* processName, std::vector<unsigned int> offsets, std::vector<byte> modifiedValues) //Returns the bytes that were written
{
	currentValues = modifiedValues;
	if (!WriteProcessMemory(processHandle, (BYTE*)address, currentValues.data(), currentValues.size(), nullptr))
		currentValues = {};
	return currentValues;
}