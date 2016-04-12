#pragma once
#include <CL\opencl.h>
#include <CL\cl_d3d11.h>
#include <string>

class OpenCLError {
public:
	std::string komunikat;
};

//funkcja wczytuj¹ca program rdzenia
char* loadProgSource(const char*,const char*, size_t*);
void system1(ID3D11Buffer*, const char* kernel_name);

