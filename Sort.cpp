#include <iostream>
using namespace std;

void InterchangeSort(int[], int);
void SelectionSort(int[], int);
void BubbleSort(int[], int);
void ShakerSort(int[], int);
void InsertionSort(int[], int);
void ShellSort(int[], int);
void QuickSort(int[], int);
void MergeSort(int[], int);
void HeapSort(int[], int);
void RadixSort(int[], int);

void CreateArr(int a[], int n)
{
	srand(time(0));
	for (int i = 0; i < n; i++)
		a[i] = rand() % 1001;
}
void PrintArr(int a[], int n)
{
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}

int main()
{
	int a[] = { 1,2,9,3,5,6,9,7,8 };
	int n = 8;
	PrintArr(a, n);

	//QuickSort(a, n);

	cout << endl;
	PrintArr(a, n);
	return 0;
}


/*
* O(n*n)
*/

void InterchangeSort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (a[i] > a[j])
				swap(a[i], a[j]);
}

void SelectionSort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		int min = i;
		for (int j = i + 1; j < n; j++)
			if (a[min] > a[j])
				min = j;
		swap(a[min], a[i]);
	}
}

void BubbleSort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = n - 1; j > i; j--)
			if (a[j] < a[j - 1])
				swap(a[j], a[j - 1]);
}

void ShakerSort(int a[], int n)
{
	int left = 0, right = n - 1, k = n - 1;
	while (left < right)
	{
		for (int i = right; i > left; i--)
			if (a[i] < a[i - 1])
			{
				swap(a[i], a[i - 1]);
				k = i;
			}
		left = k;
		for (int i = left; i < right; i++)
			if (a[i] > a[i + 1])
			{
				swap(a[i], a[i + 1]);
				k = i;
			}
		right = k;
	}
}

void InsertionSort(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int temp = a[i];
		int pos = i - 1;
		while (pos >= 0 && a[pos] > temp)
		{
			a[pos + 1] = a[pos];
			pos--;
		}
		a[pos + 1] = temp;
	}
}
void BInsertion(int a[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int temp = a[i];
		int l = 0, r = i - 1;
		while (l <= r)
		{
			int mid = (l + r) / 2;
			if (temp < a[mid]) r = mid - 1;
			else l = mid + 1;
		}
		for (int j = i - 1; j >= l; j--)
			a[j + 1] = a[j];
		a[l] = temp;
	}
}

/*
* O(nlogn)
*/ 

void ShellSort(int a[], int n)
{
	for (int step = n / 2; step > 0; step /= 2)
		for (int i = step; i < n; i++) {
			int temp = a[i];
			int j = i;
			while (j >= step && a[j - step] > temp)
			{
				a[j] = a[j - step];
				j -= step;
			}
			a[j] = temp;
		}
}

void QuickSort(int a[], int left, int right)
{
	int x = a[(left + right) / 2];
	int i = left, j = right;
	do
	{
		while (a[i] < x)i++;
		while (a[j] > x)j--;
		if (i <= j)
		{
			swap(a[i], a[j]);
			i++; j--;
		} 
	} while (i <= j);
	if (j > left) QuickSort(a, left, j);
	if (i < right) QuickSort(a, i, right);
}
void QuickSort(int a[], int n)
{
	QuickSort(a, 0, n - 1);
}

void Merge(int a[], int m, int b[], int n, int c[], int k)
{
	int bIndex = 0, cIndex = 0;
	int aIndex = 0;
	do
	{
		if (bIndex > n)
		{
			for (int i = cIndex; i < k; i++)
				a[i] = c[i];
			break;
		}
		else if (cIndex > k)
		{
			for (int i = bIndex; i < n; i++)
				a[i] = b[i];
			break;
		}
		if (b[bIndex] <= c[cIndex])
			a[aIndex++] = b[bIndex++];
		else 
			a[aIndex++] = c[cIndex++];
	} while (true);
}
void Merge(int a[], int left, int mid, int right)
{
	int* b = new int[mid - left + 1]; 
	int n = 0;
	int* c = new int[right - mid]; //ko tinh mid
	int m = 0;
	int* temp = new int[right - left + 1];
	int k = 0;

	for (int i = left; i <= mid; i++)
		b[n++] = a[i];
	for (int i = mid + 1; i < right; i++)
		c[m++] = a[i];
	Merge(temp, k, b, n, c, m);
	for (int i = 0; i < k; i++)
		a[left + i] = temp[i];
	delete[] b, c, temp;
}
void MergeSort(int a[], int left, int right)
{
	if (left <= right)
	{
		int mid = left + (right - left) / 2;
		MergeSort(a, left, mid);
		MergeSort(a, mid + 1, right);
		Merge(a, left, mid, right);
	}
}
void MergeSort(int a[], int n)
{
	MergeSort(a, 0, n - 1);
}


void shift(int a[], int l, int r)
{
	int x, i, j;
	i = l;
	j = 2 * i + 1;
	x = a[i];
	while (j <= r)
	{
		if (j < r)
			if (a[j] < a[j + 1])
				j++; 
		if (a[j] <= x) return;
		else
		{
			a[i] = a[j];
			a[j] = x;
			i = j;
			j = 2 * i + 1;
			x = a[i];
		}
	}
}
void CreateHeap(int a[], int n)
{
	int l;
	l = n / 2 - 1;
	while (l >= 0)
	{
		shift(a, l, n - 1);
		l = l - 1;
	}
}
void HeapSort(int a[], int n)
{
	int r;
	CreateHeap(a, n);
	r = n - 1;
	while (r > 0)
	{
		swap(a[0], a[r]);
		r--;
		if (r > 0)
			shift(a, 0, r);
	}
}

void RadixSort(int a[], int n)
{
	int i, b[10], m = a[0], exp = 1;
	for (i = 0; i < n; i++)
	{
		if (a[i] > m)
			m = a[i];
	}
	while (m / exp > 0)
	{
		int bucket[10] = { 0 };
		for (i = 0; i < n; i++)
			bucket[a[i] / exp % 10]++;
		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];
		for (i = n - 1; i >= 0; i--)
			b[--bucket[a[i] / exp % 10]] = a[i];
		for (i = 0; i < n; i++)
			a[i] = b[i];
		exp *= 10;
	}
}