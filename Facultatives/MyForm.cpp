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
//	int** arr; // �������, ��� ������ - ���, ������� - ����������� �������. ������ ����������� ����. �����������
//	arr = new int* [wl + 1];
//	for (int i = 0; i < wl + 1; i++)
//		arr[i] = new int[max_capacity + 1];
//	for (int i = 0; i <= wl; i++) {
//		for (int j = 0; j <= max_capacity; j++) {
//			if (i == 0 || j == 0) arr[i][j] = 0; // ������� ������ � ������� ����������� ������
//			else {
//				if (weights[i - 1] > j) arr[i][j] = arr[i - 1][j]; // ���� ��� �������� ������ ������� ����������� - ��������� ���������� �������� � �������
//				else arr[i][j] = max(arr[i - 1][j], values[i - 1] + arr[i - 1][j - weights[i - 1]]); // �����, ���������� �������� �� �������: �������� �� ���������� ������ � ������� � ����� ��������� ����. �������� � ����. ���������� � ���������� ������, ������� ������ � ������� ����� � �������
//			}
//		}
//	}
//	int answer = arr[wl][max_capacity];
//	findAns(wl, max_capacity, weights, arr);
//	for (int i = 0; i < wl + 1; i++)
//		delete[]arr[i];
//	delete[]arr;
//	return answer; // � ��������� ������ ������������ ���������
//}

int main() {
	//file.open("facs.txt"); // ��������� ����
	//while (!file.eof()) { // ���� �� �����
	//	file >> i; // ��������� �� ����� ������
	//	n++; // ����������� ������ ��������
	//} // ������ � n �������� ���-�� ����� � �����
	//file.close(); // ������� ����

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Facultatives::MyForm form;
	Application::Run(% form);
}