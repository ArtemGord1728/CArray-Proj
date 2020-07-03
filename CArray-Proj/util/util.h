#ifndef C_ARRAY_UTILS_H_
#define C_ARRAY_UTILS_H_

#include <ctime>
#include <string>
#include "CArray.h"


template<class T>
void selection_sort(T& arr)
{
	int min = 0;
	int buf = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		min = i;
		for (int j = i + 1; j < arr.size(); j++)
		{
			min = (arr[j] < arr[min]) ? j : min;
		}

		if (i != min)
		{
			buf = arr[i];
			arr[i] = arr[min];
			arr[min] = buf;
		}
	}
}


#endif