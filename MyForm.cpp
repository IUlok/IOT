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
	Application::Exit(); // ����� �� ���������
}

System::Void Facultatives::MyForm::btn_result_Click(System::Object^ sender, System::EventArgs^ e) {
	// ����� ������� �� �����
	res_table->Rows->Clear(); // �������� ������� ����������
	j = 0; // � ��������������� ����������
	counter_values = 0;

	if (wl == 0) { // ���� ���������� �� ��������� - ������
		MessageBox::Show("������� �� ���������!", "������!");
		return System::Void();
	}
	else if (max_capacity_label->Text == "") { // ���� ���� ����� ������ - ������
		MessageBox::Show("�� ������� ���-�� �����!", "������!");
		return System::Void();
	}
	else { // ����� � max_capacity ���������� ����� ��� ��
		max_capacity = Convert::ToInt32(max_capacity_label->Text);
	}
	for (i = 0; i < wl; i++) { // ���� ���� ������� � ������� ����������� - ������
		if (database->Rows[i]->Cells[3]->Value->ToString() == "") {
			MessageBox::Show("�� ��� ���������� ���������!", "������!");
			return System::Void();
		}
		else { // ���� ������ ���� - ��������� ������� ����� � ����������
			string_buffer = database->Rows[i]->Cells[2]->Value->ToString();
			weights[i] = Convert::ToInt32(string_buffer);
			string_buffer = database->Rows[i]->Cells[3]->Value->ToString();
			values[i] = Convert::ToInt32(string_buffer);
		}
	}
	for (i = 1; i < wl; i++) if (values[i] == values[0]) counter_values++; // ���������� ��������� ������ ������ � ����������
	// ��� ������ ���������� ��������������. ���� counter_values = ���-�� ��������� - ��� ���������� ���������� - ������
	if (counter_values == wl - 1) {
		MessageBox::Show("������� ���������� ����������!", "������!");
		return System::Void();
	} // ����� - ����� ������� ���������� ������� �����
	else Facultatives::MyForm::one_item(wl, max_capacity, weights, values);

	j--; // j � ����� �������� ��������� �� ������� ������, ������� ������ ��������� ��� �� 1
	while (j >= 0) { // � ���. ������ ���������� ������, �������� � ������������ ����������, ������ ������� ����� ans[j]
		res_table->Rows->Add(database->Rows[ans[j]]->Cells[0]->Value, database->Rows[ans[j]]->Cells[1]->Value, database->Rows[ans[j]]->Cells[2]->Value);
		j--; // ������� ������ �� �������� �������� ������������
	}
	return System::Void();
}

System::Void Facultatives::MyForm::btn_add_db_Click(System::Object^ sender, System::EventArgs^ e) {
	database->Rows->Clear();
	// ����������� ���� ������
	String^ connectionString = "provider = Microsoft.ACE.OLEDB.12.0; Data Source=Facultatives.mdb";
	OleDbConnection^ dbConnection = gcnew OleDbConnection(connectionString);

	dbConnection->Open();
	String^ query = "SELECT * FROM [Facultatives]";
	OleDbCommand^ dbComand = gcnew OleDbCommand(query, dbConnection);
	OleDbDataReader^ dbReader = dbComand->ExecuteReader();

	if (dbReader->HasRows == false) {
		MessageBox::Show("������ ���������� ������!", "������!");
	}
	else {
		while (dbReader->Read()) {
			database->Rows->Add(dbReader["id"], dbReader["name"], dbReader["weight"], dbReader["price"]);
			wl++; // � ���������� wl ������������ ���-�� ����� - ���������
		}
	}
	dbReader->Close();
	dbConnection->Close();
	return System::Void();
}

System::Void Facultatives::MyForm::one_item(int wl, int max_capacity, int weights[], int values[]) {
	int** arr; // �-�� �����
	arr = new int* [wl + 1]; // arr[n+1][m+1], ��� n - ���-�� ���������, m - ���-�� ����� �� ��
	for (int i = 0; i < wl + 1; i++)
		arr[i] = new int[max_capacity + 1];
	for (int i = 0; i <= wl; i++) {
		for (int j = 0; j <= max_capacity; j++) {
			if (i == 0 || j == 0) arr[i][j] = 0; // ������� ������ � ������� ����������� ������
			else {
				if (weights[i - 1] > j) arr[i][j] = arr[i - 1][j]; // ���� ��� �������� ������ ������� ����������� - ��������� ���������� �������� � �������
				else arr[i][j] = max(arr[i - 1][j], values[i - 1] + arr[i - 1][j - weights[i - 1]]); // �����, ���������� �������� �� �������: �������� �� ���������� ������ � ������� � ����� ��������� ����. �������� � ����. ���������� � ���������� ������, ������� ������ � ������� ����� � �������
			}
		}
	}
	//int answer = arr[wl][max_capacity]; // ��� ����. ���������, �� ����������
	find_ans(wl, max_capacity, weights, arr); // ����� �-��� ������������ �������� ������� �������� ���������
	for (int i = 0; i < wl + 1; i++) // ������� ������
		delete[]arr[i];
	delete[]arr;
	return System::Void();
}

System::Void Facultatives::MyForm::find_ans(int wl, int max_capacity, int weights[], int** arr) {
	if (arr[wl][max_capacity] == 0) return; // ����������� �-��� ���������� ������� �������. ���� �������� ������ = 0 - �������� "����� � ������" � ����������� ����� �-��
	if (arr[wl - 1][max_capacity] == arr[wl][max_capacity]) find_ans(wl - 1, max_capacity, weights, arr); // ���� ��������� ��������� �����, �������� �-��� ��� wl-1
	else { // ���� �� �����, ������ ��� ���������� ������� ����. ���������� ������� ������� � ������� � �������� �-��� ��� ����������� �������� � ���� ��������� �� �����������
		ans[j] = wl-1; // ������� �������
		j++; // ������� �������
		find_ans(wl - 1, max_capacity - weights[wl - 1], weights, arr);
	}
	return System::Void();
}