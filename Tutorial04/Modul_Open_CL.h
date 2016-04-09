#pragma once
#include <CL\opencl.h>
#include <string>

class OpenCLError {
public:
	std::string komunikat;
};

//funkcja wczytuj¹ca program rdzenia
char* loadProgSource(const char*,const char*, size_t*);
void inicjacja(char*);

