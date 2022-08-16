#pragma once
#include "framework.h"

class ADDRESS
{
//public:
	std::vector<unsigned int>	offsets; //offsets
	DWORD						processId; //process id
	uintptr_t					moduleBase;//module base address
	HANDLE						processHandle; //process handle
	uintptr_t					pointerBase; //pointer base
	uintptr_t					address; //Get address
	std::vector<byte>			currentValues; //Addresses are read to and from here
	std::vector<byte>			modifiedValues; //Modified values to copy into currentValues

public:
	uintptr_t			GetAddress(const wchar_t* processName, std::vector<unsigned int> offsets); //Returns address
	std::vector<byte>	ReadBytes(const wchar_t* processName, std::vector<unsigned int> offsets, unsigned int numBytes = 1); //Returns the bytes that were read
	std::vector<byte>   WriteBytes(const wchar_t* processName, std::vector<unsigned int> offsets, std::vector<byte> modifiedValues); //Returns the bytes that were written
	std::vector<byte>   RestoreBytes(const wchar_t* processName, std::vector<unsigned int> offsets, std::vector<byte> modifiedValues); //Returns the bytes that were written
};