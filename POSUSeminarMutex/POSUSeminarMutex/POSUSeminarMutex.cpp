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

/// <summary>
///Первый поток
/// </summary>
/// <param name="pv"></param>
/// <returns></returns>
static DWORD WINAPI Kulagin(void* pv)
{
	COORD pos;   //Переменная, которая будет хранить текующую координату курсора 
	int i = 0;
	int sync = 0;
	pos.X = 1;  //Столбец отображения задержки первого потока
	while (i < 50)
	{
		WaitForSingleObject(g_hMutex, INFINITE); // Ожидание запуска мютекса на длительном интервале времени
		srand(time(NULL)); //Включение генератора случайных чисел
		g_array[g_count] = rand() % 256;  //Генерируем случайное число
		pos.Y = i;
		SetConsoleCursorPosition(hStdout, pos); //Установка курсора в i-ую строку
		if (!sync)
		{
			cout << "Kulagin" << endl;  // Выводим фамилию в название столбца
			sync++;
		}
		cout << g_array[g_count++];
		Sleep(40);  //Осуществление задержки на 40 миллисекунд
		i++;
		ReleaseMutex(g_hMutex); //Освообождение мютекса
	}
	if (!Lid)
		Lid = 1;  //Флаг лидирующего потока
	return 0;
}

/// <summary>
/// Второй поток 
/// </summary>
/// <param name="pv"></param>
/// <returns></returns>
static DWORD WINAPI Grigoriy(void* pv)
{
	COORD pos; //Переменная, которая будет хранить текующую координату курсора
	int i = 0;
	int sync = 0;
	pos.X = 18;   //Столбец отображения задержки второго потока
	while (i < 50)
	{
		WaitForSingleObject(g_hMutex, INFINITE); // Ожидание запуска мютекса на длительном интервале времени
		srand(time(NULL));  //Включение генератора случайных чисел
		g_array[g_count] = rand() % 256; //Генерируем случайное число
		pos.Y = i;
		SetConsoleCursorPosition(hStdout, pos); //Установка курсора в i-ую строку
		if (!sync)
		{
			cout << "Grigoriy" << endl; // Выводим имя в название второго столбца
			sync++;
		}
		cout << g_array[g_count++];
		Sleep(40); //Осуществление задержки на 40 миллисекунд
		i++;
		ReleaseMutex(g_hMutex);  //Освообождение мютекса
	}
	if (!Lid)
		Lid = 2; //Флаг лидирующего потока
	return 0;
}

/// <summary>
/// Третий поток
/// </summary>
/// <param name="pv"></param>
/// <returns></returns>
static DWORD WINAPI Vladimirovich(void* pv)
{
	COORD pos;  //Переменная, которая будет хранить текующую координату курсора
	int i = 0;
	int sync = 0;
	pos.X = 36;   //Столбец отображения задержки третьего потока
	while (i < 50)
	{
		WaitForSingleObject(g_hMutex, INFINITE); // Ожидание запуска мютекса на длительном интервале времени
		srand(time(NULL)); //Включение генератора случайных чисел
		g_array[g_count] = rand() % 256;  //Генерируем случайное число
		pos.Y = i;
		SetConsoleCursorPosition(hStdout, pos); //Установка курсора в i-ую строку
		if (!sync)
		{
			cout << "Vladimirovich" << endl; //Выводим отчество в название третьего столбца
			sync++;
		}
		cout << g_array[g_count++];
		Sleep(40); //Осуществление задержки на 40 миллисекунд
		i++;
		ReleaseMutex(g_hMutex);  //Освообождение мютекса
	}
	if (!Lid)
		Lid = 3;  //Флаг лидирующего потока
	return 0;
}

/// <summary>
/// Четвертый поток
/// </summary>
/// <param name="pv"></param>
/// <returns></returns>
static DWORD WINAPI Gruppa(void* pv)
{
	COORD pos; //Переменная, которая будет хранить текующую координату курсора
	int i = 0;
	int sync = 0;
	pos.X = 54; //Столбец отображения задержки четвертого потока
	while (i < 50)
	{
		WaitForSingleObject(g_hMutex, INFINITE); // Ожидание запуска мютекса на длительном интервале времени
		srand(time(NULL)); //Включение генератора случайных чисел
		g_array[g_count] = rand() % 256; //Генерируем случайное число
		pos.Y = i;
		SetConsoleCursorPosition(hStdout, pos);//Установка курсора в i-ую строку
		if (!sync)
		{
			cout << "Gruppa" << endl; //Выводим группу в название четвертого столбца 
			sync++;
		}
		cout << g_array[g_count++];
		Sleep(40); //Осуществление задержки на 40 миллисекунд
		i++;
		ReleaseMutex(g_hMutex); //Освообождение мютекса
	}
	if (!Lid)
		Lid = 4; //Флаг лидирующего потока
	return 0;
}

int main()
{
	DWORD dw;
	HANDLE hThreads[4];
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//Создание мютекса
	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	//Создание 4-х потоков 
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

	//Выводим какой поток финишировал первым 
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

