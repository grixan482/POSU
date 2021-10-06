#include <Windows.h>
#include <conio.h>
#include <ctime>
#include <iostream>
using namespace std;
int g_array[100];
int g_count = 0;
HANDLE g_hMutex = NULL;
HANDLE hStdout;
int Lid = 0;

static DWORD WINAPI Kulagin(void* pv)
{
	int i = 0;
	int sync = 0;
	COORD pos;
	pos.X = 1;
	while (i < 50)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		srand(time(NULL));
		g_array[g_count] = rand() % 256;
		pos.Y = i;
		SetConsoleCursorPosition(hStdout, pos);
		if (!sync)
		{
			cout << "Kulagin" << endl;
			sync++;
		}
		cout << g_array[g_count++];
		Sleep(40);
		i++;
		ReleaseMutex(g_hMutex);
	}
	if (!Lid)
		Lid = 1;
	return 0;
}
static DWORD WINAPI Grigoriy(void* pv)
{
	int i = 0;
	int sync = 0;
	COORD pos;
	pos.X = 18;
	while (i < 50)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		srand(time(NULL));
		g_array[g_count] = rand() % 1000;
		pos.Y = i;
		SetConsoleCursorPosition(hStdout, pos);
		if (!sync)
		{
			cout << "Grigoriy" << endl;
			sync++;
		}
		cout << g_array[g_count++];
		Sleep(40);
		i++;
		ReleaseMutex(g_hMutex);
	}
	if (!Lid)
		Lid = 2;
	return 0;
}
static DWORD WINAPI Vladimirovich(void* pv)
{
	int i = 0;
	int sync = 0;
	COORD pos;
	pos.X = 36;
	while (i < 50)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		srand(time(NULL));
		g_array[g_count] = rand() % 256;
		pos.Y = i;
		SetConsoleCursorPosition(hStdout, pos);
		if (!sync)
		{
			cout << "Vladimirovich" << endl;
			sync++;
		}
		cout << g_array[g_count++];
		Sleep(40);
		i++;
		ReleaseMutex(g_hMutex);
	}
	if (!Lid)
		Lid = 3;
	return 0;
}
static DWORD WINAPI Gruppa(void* pv)
{
	int i = 0;
	int sync = 0;
	COORD pos;
	pos.X = 54;
	while (i < 50)
	{
		WaitForSingleObject(g_hMutex, INFINITE);
		srand(time(NULL));
		g_array[g_count] = rand() % 256;
		pos.Y = i;
		SetConsoleCursorPosition(hStdout, pos);
		if (!sync)
		{
			cout << "Gruppa" << endl;
			sync++;
		}
		cout << g_array[g_count++];
		Sleep(40);
		i++;
		ReleaseMutex(g_hMutex);
	}
	if (!Lid)
		Lid = 4;
	return 0;
}

int main()
{
	DWORD dw;
	HANDLE hThreads[4];
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	g_hMutex = CreateMutex(NULL, FALSE, NULL);

	hThreads[0] = ::CreateThread(NULL, 0, Kulagin, NULL, 0, &dw);
	hThreads[1] = ::CreateThread(NULL, 0, Grigoriy, NULL, 0, &dw);
	hThreads[2] = ::CreateThread(NULL, 0, Vladimirovich, NULL, 0, &dw);
	hThreads[3] = ::CreateThread(NULL, 0, Gruppa, NULL, 0, &dw);

	::WaitForMultipleObjects(4, hThreads, TRUE, INFINITE);

	::CloseHandle(hThreads[0]);
	::CloseHandle(hThreads[1]);
	::CloseHandle(hThreads[2]);
	::CloseHandle(hThreads[3]);

	::CloseHandle(g_hMutex);
	switch (Lid)
	{
	case 1: cout << "\n 1 thread finished first!\n"; break;
	case 2: cout << "\n 2 thread finished first!\n"; break;
	case 3: cout << "\n 3 thread finished first!\n"; break;
	case 4: cout << "\n 4 thread finished first!\n"; break;
	default: break;
	}
	cout << endl << "Press Any Key...";
	_getch();
	return 0;
}

