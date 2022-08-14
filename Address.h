#pragma once
#include "framework.h"
//#include "Address.cpp"

class ADDRESS
{
	uintptr_t					baseOffset; //base offset //ToDo:Remove this and set as the first element of "offsets"
	std::vector<unsigned int>	offsets; //offsets

	DWORD						processId; //process id
	uintptr_t					moduleBase;//module base address
	HANDLE						processHandle; //process handle
	uintptr_t					pointerBase; //pointer base
	uintptr_t					address; //Get address
	std::vector<byte>			currentValues; //Addresses are read to and from here
	std::vector<byte>			initialValues; //Expected values, used to verify initial values and to revert changes
	std::vector<byte>			modifiedValues; //Modified values to copy into currentValues
	std::vector<byte>			restoredValues; //Should be unnecessary once we can read/write a custom number of bytes from vector

public:
	std::vector<byte>	ReadBytes(const wchar_t* processName, std::vector<unsigned int> offsets, unsigned int numBytes = 1, std::vector<byte> compareValues = {}); //Returns the bytes that were read
	//std::vector<byte>   WriteBytes(const wchar_t* processName, std::vector<unsigned int> offsets, std::vector<byte> modifiedValues, std::vector<bool> byteMask) //Returns the bytes that were written
	//uintptr_t			CreatePointer(processName, offsets, initialValues, modifiedValues); //Returns memory address
	//uintptr_t			UpdatePointer(); //Returns memory address
};