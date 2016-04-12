#include "Modul_Open_CL.h"

void system1(ID3D11Buffer* DirectXBuffer, const char* kernel_name)
{
	//tworzenie kontekstu obliczeñ dla danej platformy i urz¹dzenia obliczeniowego
	cl_platform_id  platform;
	cl_device_id  devices;
	cl_int errcode;
	//Bufor ramki
	cl_mem Buffer;
	errcode=clGetPlatformIDs(1, &platform, NULL);
	//zg³oszenie wyj¹tku w przypadku niepowodzenia
	if (platform == 0 || errcode != CL_SUCCESS)throw OpenCLError{ "Blad - Brak dostepnych platform OpenCL" };
	clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &devices, NULL);
	cl_context context = clCreateContext(0, 1, &devices,NULL, NULL, NULL);
	
	//tworzenie kolejki poleceñ
	cl_command_queue  cmdQueue = clCreateCommandQueue(context, devices, 0, &errcode);
	
	size_t kernelLength;

	//za³adowanie programu z pliku podanego jako argument funkcji
	char* programSource = loadProgSource(kernel_name, "", &kernelLength);

	//struktura opisuj¹ca bufor
	D3D11_BUFFER_DESC buffor_desc;

	DirectXBuffer->GetDesc(&buffor_desc);
	//rozmiar bufora
	UINT buff_size=buffor_desc.ByteWidth;
	
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&programSource, &kernelLength, &errcode);
	clBuildProgram(program, 0, 0, 0, 0, 0);
	cl_kernel kernel = clCreateKernel(program, "funkcja1", &errcode);
	cl_mem clVec = clCreateBuffer(context, CL_MEM_READ_WRITE, buff_size, 0, &errcode);

}


char* loadProgSource(const char* filename, const char* preamble,size_t* finalLength)
{
	FILE* file = fopen(filename,"rb");
	if(file == 0)return	NULL;
	size_t preambleLength = strlen(preamble);
	fseek(file, 0, SEEK_END);
	size_t sourceLength = ftell(file);
	fseek(file, 0, SEEK_SET);
	char* sourceString = (char*)malloc(sourceLength + preambleLength + 1);
	memcpy(sourceString, preamble, preambleLength);
	if (fread((sourceString)+preambleLength, sourceLength, 1, file) != 1)
	{
		fclose(file);
		free(sourceString);
		return 0;
	}
	fclose(file);
	*finalLength = sourceLength + preambleLength;
	sourceString[sourceLength + preambleLength] = '\0';
	return	sourceString;
}