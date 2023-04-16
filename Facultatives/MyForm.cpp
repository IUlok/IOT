#include "MyForm.h"
#include <iostream>
#include <stack>
#include <fstream>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;

stack <int> ans;
ifstream file;
string list[100];
int wl, max_capacity, counter, i = 0, n = 0;

[STAThreadAttribute]

//void findAns(int wl, int max_capacity, int weights[], int** arr) {
//	if (arr[wl][max_capacity] == 0) return;
//	if (arr[wl - 1][max_capacity] == arr[wl][max_capacity]) findAns(wl - 1, max_capacity, weights, arr);
//	else {
//		ans.push(wl);
//		findAns(wl - 1, max_capacity - weights[wl - 1], weights, arr);
//	}
//}
//
//int one_item(int wl, int max_capacity, int weights[], int values[]) {
//	int** arr; // Матрица, где строки - вес, столбцы - вместимость рюкзака. Ячейки заполняются макс. стоимостями
//	arr = new int* [wl + 1];
//	for (int i = 0; i < wl + 1; i++)
//		arr[i] = new int[max_capacity + 1];
//	for (int i = 0; i <= wl; i++) {
//		for (int j = 0; j <= max_capacity; j++) {
//			if (i == 0 || j == 0) arr[i][j] = 0; // Нулевые строка и столбец заполняются нулями
//			else {
//				if (weights[i - 1] > j) arr[i][j] = arr[i - 1][j]; // если вес предмета больше текущей вместимости - вписываем предыдущее значение в столбце
//				else arr[i][j] = max(arr[i - 1][j], values[i - 1] + arr[i - 1][j - weights[i - 1]]); // Иначе, записываем значение по формуле: максимум из предыдущей ячейки в столбце и суммы стоимости пред. предмета с макс. стоимостью в предыдущей строке, которая влазит в остаток места в рюкзаке
//			}
//		}
//	}
//	int answer = arr[wl][max_capacity];
//	findAns(wl, max_capacity, weights, arr);
//	for (int i = 0; i < wl + 1; i++)
//		delete[]arr[i];
//	delete[]arr;
//	return answer; // В последней ячейке максимальная стоимость
//}

int main() {
	//file.open("facs.txt"); // Открываем файл
	//while (!file.eof()) { // Пока не конец
	//	file >> i; // Переходим на новую строку
	//	n++; // Увеличиваем размер векторов
	//} // Теперь в n записано кол-во строк в файле
	//file.close(); // Закроем файл

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Facultatives::MyForm form;
	Application::Run(% form);
}