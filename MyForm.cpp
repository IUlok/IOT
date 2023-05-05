#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Data::OleDb;

[STAThreadAttribute]

int main() {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	Facultatives::MyForm form;
	Application::Run(% form);
}

System::Void Facultatives::MyForm::btn_exit_Click(System::Object^ sender, System::EventArgs^ e) {
	Application::Exit(); // Выход из программы
}

System::Void Facultatives::MyForm::btn_result_Click(System::Object^ sender, System::EventArgs^ e) {
	// Вывод выборки на экран
	res_table->Rows->Clear(); // Обнуляем таблицу результата
	j = 0; // И вспомогательные переменные
	counter_values = 0;

	if (wl == 0) { // Если дисциплины не загружены - ошибка
		MessageBox::Show("Таблица не загружена!", "Ошибка!");
		return System::Void();
	}
	else if (max_capacity_label->Text == "") { // Если поле часов пустое - ошибка
		MessageBox::Show("Не введено кол-во часов!", "Ошибка!");
		return System::Void();
	}
	else { // Иначе в max_capacity количество часов для ВЧ
		max_capacity = Convert::ToInt32(max_capacity_label->Text);
	}
	for (i = 0; i < wl; i++) { // Если есть пустоты в столбце приоритетов - ошибка
		if (database->Rows[i]->Cells[3]->Value->ToString() == "") {
			MessageBox::Show("Не все приоритеты заполнены!", "Ошибка!");
			return System::Void();
		}
		else { // Если пустот нету - формируем массивы весов и стоимостей
			string_buffer = database->Rows[i]->Cells[2]->Value->ToString();
			weights[i] = Convert::ToInt32(string_buffer);
			string_buffer = database->Rows[i]->Cells[3]->Value->ToString();
			values[i] = Convert::ToInt32(string_buffer);
		}
	}
	for (i = 1; i < wl; i++) if (values[i] == values[0]) counter_values++; // Сравниваем приоритет первой строки с остальными
	// При каждом совпадении инкрементируем. Если counter_values = кол-ву дисциплин - все приоритеты одинаковые - ошибка
	if (counter_values == wl - 1) {
		MessageBox::Show("Введены одинаковые приоритеты!", "Ошибка!");
		return System::Void();
	} // Иначе - вызов функции построения матрциы весов
	else Facultatives::MyForm::one_item(wl, max_capacity, weights, values);

	j--; // j в конце рекурсии получился на единицу больше, поэтому сперва уменьшаем его на 1
	while (j >= 0) { // В рез. таблцу записываем индекс, название и длительность дисциплины, индекс которой равен ans[j]
		res_table->Rows->Add(database->Rows[ans[j]]->Cells[0]->Value, database->Rows[ans[j]]->Cells[1]->Value, database->Rows[ans[j]]->Cells[2]->Value);
		j--; // Обходим массив до нулевого элемента включительно
	}
	return System::Void();
}

System::Void Facultatives::MyForm::btn_add_db_Click(System::Object^ sender, System::EventArgs^ e) {
	database->Rows->Clear();
	// Подключение базы данных
	String^ connectionString = "provider = Microsoft.ACE.OLEDB.12.0; Data Source=Facultatives.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	dbConnection->Open();
	String^ query = "SELECT * FROM [Facultatives]";
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);
	OleDbDataReader^ dbReader = dbComand->ExecuteReader();

	if (dbReader->HasRows == false) {
		MessageBox::Show("Ошибка считывания данных!", "Ошибка!");
	}
	else {
		while (dbReader->Read()) {
			database->Rows->Add(dbReader["id"], dbReader["name"], dbReader["weight"], dbReader["price"]);
			wl++; // В переменную wl записывается кол-во строк - дисциплин
		}
	}
	dbReader->Close();
	dbConnection->Close();
	return System::Void();
}

System::Void Facultatives::MyForm::one_item(int wl, int max_capacity, int weights[], int values[]) {
	int** arr; // М-ца весов
	arr = new int* [wl + 1]; // arr[n+1][m+1], где n - кол-во дисциплин, m - кол-во часов на ВЧ
	for (int i = 0; i < wl + 1; i++)
		arr[i] = new int[max_capacity + 1];
	for (int i = 0; i <= wl; i++) {
		for (int j = 0; j <= max_capacity; j++) {
			if (i == 0 || j == 0) arr[i][j] = 0; // Нулевые строка и столбец заполняются нулями
			else {
				if (weights[i - 1] > j) arr[i][j] = arr[i - 1][j]; // если вес предмета больше текущей вместимости - вписываем предыдущее значение в столбце
				else arr[i][j] = max(arr[i - 1][j], values[i - 1] + arr[i - 1][j - weights[i - 1]]); // Иначе, записываем значение по формуле: максимум из предыдущей ячейки в столбце и суммы стоимости пред. предмета с макс. стоимостью в предыдущей строке, которая влазит в остаток места в рюкзаке
			}
		}
	}
	//int answer = arr[wl][max_capacity]; // Тут макс. стоимость, мб пригодится
	find_ans(wl, max_capacity, weights, arr); // Вызов ф-ции формирования искомого массива индексов дисциплин
	for (int i = 0; i < wl + 1; i++) // Очистка памяти
		delete[]arr[i];
	delete[]arr;
	return System::Void();
}

System::Void Facultatives::MyForm::find_ans(int wl, int max_capacity, int weights[], int** arr) {
	if (arr[wl][max_capacity] == 0) return; // Рекурсивная ф-ция построения искомой выборки. Если значение ячейки = 0 - алгоритм "упёрся в стенку" и заканчивает обход м-цы
	if (arr[wl - 1][max_capacity] == arr[wl][max_capacity]) find_ans(wl - 1, max_capacity, weights, arr); // Если стоимости предметов равны, вызываем ф-цию для wl-1
	else { // Если не равны, значит там однозначно меньшая цена. Записываем текущий предмет в выборку и вызываем ф-цию для предыдущего предметы и цены предметов до предыдущего
		ans[j] = wl-1; // Искомая выборка
		j++; // Счетчик выборки
		find_ans(wl - 1, max_capacity - weights[wl - 1], weights, arr);
	}
	return System::Void();
}