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
	Application::Exit();
}

System::Void Facultatives::MyForm::btn_result_Click(System::Object^ sender, System::EventArgs^ e) {
	// Вывод выборки на экран
	for (int i = 0; i < wl; i++) label4->Text += Convert::ToString(weights[i]);
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
			wl++;
		}
		for(int i = 0; i < wl; i++) {
			weights[i] = Convert::ToInt32(database->Rows[2]->Cells[i]->Value->ToString());
		}
	}
	dbReader->Close();
	dbConnection->Close();
	return System::Void();
}