#include "Modul_Open_CL.h"

//wskaźniki na funkcje rozszerzeń
clCreateFromD3D11Texture2DKHR_fn   ptrToFunction_clCreateFromD3D11Texture2DKHR = NULL;
clEnqueueAcquireD3D11ObjectsKHR_fn ptrToFunction_clEnqueueAcquireD3D11ObjectsKHR = NULL;
clEnqueueReleaseD3D11ObjectsKHR_fn ptrToFunction_clEnqueueReleaseD3D11ObjectsKHR = NULL;

void GetDX11SharingFunctionsFromCL()
{

	ptrToFunction_clCreateFromD3D11Texture2DKHR = (clCreateFromD3D11Texture2DKHR_fn)clGetExtensionFunctionAddressForPlatform(g_platformToUse, "clCreateFromD3D11Texture2DKHR");
	if(ptrToFunction_clCreateFromD3D11Texture2DKHR == NULL)throw OpenClError{"Nieudane utworzenie wskaxnika na funckje"};
	
	ptrToFunction_clEnqueueAcquireD3D11ObjectsKHR = (clEnqueueAcquireD3D11ObjectsKHR_fn)clGetExtensionFunctionAddressForPlatform(g_platformToUse, "clEnqueueAcquireD3D11ObjectsKHR");
	if(ptrToFunction_clEnqueueAcquireD3D11ObjectsKHR == NULL)throw OpenClError{"Nieudane utworzenie wskaxnika na funckje"};
	
	ptrToFunction_clEnqueueReleaseD3D11ObjectsKHR = (clEnqueueReleaseD3D11ObjectsKHR_fn)clGetExtensionFunctionAddressForPlatform(g_platformToUse, "clEnqueueReleaseD3D11ObjectsKHR");
	if(ptrToFunction_clEnqueueReleaseD3D11ObjectsKHR == NULL)throw OpenClError{"Nieudane utworzenie wskaxnika na funckje"};

}

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
