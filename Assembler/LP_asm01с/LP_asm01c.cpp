#include <iostream>
#pragma comment (lib, "..\\Debug\\LP_asm01a.lib")


extern "C"
{
	int __stdcall getmin(int*, int);
	int __stdcall getmax(int*, int);
}

int main()
{
	int arr[10] = { 3, 5, 15, 71, 32, 14, -1, 10, 2, 4 };
	int max = getmax(arr, sizeof(arr) / sizeof(int));
	int min = getmin(arr, sizeof(arr) / sizeof(int));
	std::cout << "getmax-getmin= " << max - min << std::endl;

	system("pause");
}