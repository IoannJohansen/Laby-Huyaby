#include <cstdlib>
extern "C"
{
	int getmin(int* a, int n)
	{
		int min = *a;
		for (int i = 1; i < n; ++i)
			if (a[i] < min)
				min = a[i];
		return min;
	}

	int getmax(int* a, int n)
	{
		int max = *a;
		for (int i = 1; i < n; ++i)
			if (a[i] > max)
				max = a[i];
		return max;
	}
}