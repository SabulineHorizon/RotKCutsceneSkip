#pragma once
#include "framework.h"
#include "resource.h"

void AttachToProcess(HWND hWnd);
void UpdateStatusText(HWND hWnd, LPCSTR text, std::vector<byte> color = {});