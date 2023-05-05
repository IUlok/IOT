#pragma once
#define max(a,b) (((a) > (b)) ? (a) : (b)) // Ф-ция поиска максимума

namespace Facultatives { // ВЧ - Вариативная часть (искомая выборка)

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	int ans[100], j = 0; // Массив и счетчик для вывода результирующей таблицы
	int weights[100], values[100]; // Массив весов и приоритетов
	int wl = 0, max_capacity = 0; // Счетчик кол-ва дисциплин и кол-ва часов на ВЧ 

	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm(void) {
			InitializeComponent(); // Конструктор
		}

	protected:
		~MyForm() {
			if (components) {
				delete components; // Деструктор
			}
		}
	private: System::Windows::Forms::Button^ btn_result;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ btn_exit;
	public: System::Windows::Forms::TextBox^ max_capacity_label;
	private: System::Windows::Forms::DataGridView^ database;
	private: System::Windows::Forms::Button^ btn_add_db;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ id;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ name;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ weight;
	private: System::Windows::Forms::DataGridViewComboBoxColumn^ price;
	private: System::Windows::Forms::DataGridView^ res_table;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ dataGridViewTextBoxColumn3;
	private: System::Windows::Forms::Label^ label3;
	private: String^ string_buffer; // Переменная для чтения и записи в таблицы
	private: int i = 0; // Вспомогательный счетчик
	private: int counter_values = 0; // Счетчик проверки на неравенство приоритетов

		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			   System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			   this->btn_result = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->btn_exit = (gcnew System::Windows::Forms::Button());
			   this->max_capacity_label = (gcnew System::Windows::Forms::TextBox());
			   this->database = (gcnew System::Windows::Forms::DataGridView());
			   this->id = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->name = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->weight = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->price = (gcnew System::Windows::Forms::DataGridViewComboBoxColumn());
			   this->btn_add_db = (gcnew System::Windows::Forms::Button());
			   this->res_table = (gcnew System::Windows::Forms::DataGridView());
			   this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->database))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->res_table))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // btn_result
			   // 
			   this->btn_result->BackColor = System::Drawing::Color::Green;
			   this->btn_result->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			   this->btn_result->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btn_result->Font = (gcnew System::Drawing::Font(L"Hack", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btn_result->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->btn_result->Location = System::Drawing::Point(170, 609);
			   this->btn_result->Name = L"btn_result";
			   this->btn_result->RightToLeft = System::Windows::Forms::RightToLeft::No;
			   this->btn_result->Size = System::Drawing::Size(386, 40);
			   this->btn_result->TabIndex = 0;
			   this->btn_result->Text = L"Подобрать дисциплины\r\n\r\n";
			   this->btn_result->UseVisualStyleBackColor = false;
			   this->btn_result->Click += gcnew System::EventHandler(this, &MyForm::btn_result_Click);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Hack", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label1->Location = System::Drawing::Point(44, 9);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(659, 57);
			   this->label1->TabIndex = 1;
			   this->label1->Text = L"Выбор индивидуальной образовательной траектории\r\nУкажите приоритет от 1 до 3 кажд"
				   L"ого из перечисленных направлений,\r\nа затем нажмите \"Подобрать траекторию\"";
			   this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Hack", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label2->Location = System::Drawing::Point(32, 82);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(139, 19);
			   this->label2->TabIndex = 2;
			   this->label2->Text = L"Кол-во часов:";
			   // 
			   // btn_exit
			   // 
			   this->btn_exit->BackColor = System::Drawing::Color::Green;
			   this->btn_exit->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			   this->btn_exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btn_exit->Font = (gcnew System::Drawing::Font(L"Hack", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->btn_exit->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->btn_exit->Location = System::Drawing::Point(562, 609);
			   this->btn_exit->Name = L"btn_exit";
			   this->btn_exit->Size = System::Drawing::Size(150, 40);
			   this->btn_exit->TabIndex = 3;
			   this->btn_exit->Text = L"Выход";
			   this->btn_exit->UseVisualStyleBackColor = false;
			   this->btn_exit->Click += gcnew System::EventHandler(this, &MyForm::btn_exit_Click);
			   // 
			   // max_capacity_label
			   // 
			   this->max_capacity_label->Location = System::Drawing::Point(168, 83);
			   this->max_capacity_label->Name = L"max_capacity_label";
			   this->max_capacity_label->Size = System::Drawing::Size(100, 20);
			   this->max_capacity_label->TabIndex = 4;
			   // 
			   // database
			   // 
			   this->database->AllowUserToAddRows = false;
			   this->database->BackgroundColor = System::Drawing::SystemColors::Control;
			   this->database->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->database->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
			   this->database->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			   dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			   dataGridViewCellStyle1->BackColor = System::Drawing::Color::Transparent;
			   dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Hack", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			   dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			   dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			   dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			   this->database->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			   this->database->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->database->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				   this->id, this->name,
					   this->weight, this->price
			   });
			   this->database->GridColor = System::Drawing::SystemColors::ControlDarkDark;
			   this->database->Location = System::Drawing::Point(12, 109);
			   this->database->Name = L"database";
			   this->database->RightToLeft = System::Windows::Forms::RightToLeft::No;
			   this->database->RowHeadersVisible = false;
			   this->database->Size = System::Drawing::Size(404, 470);
			   this->database->TabIndex = 5;
			   // 
			   // id
			   // 
			   this->id->HeaderText = L"ID";
			   this->id->Name = L"id";
			   this->id->ReadOnly = true;
			   this->id->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			   this->id->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   // 
			   // name
			   // 
			   this->name->HeaderText = L"Название дисциплины";
			   this->name->Name = L"name";
			   this->name->ReadOnly = true;
			   this->name->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			   this->name->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   // 
			   // weight
			   // 
			   this->weight->HeaderText = L"Длительность курса (в ч.)";
			   this->weight->Name = L"weight";
			   this->weight->ReadOnly = true;
			   this->weight->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			   this->weight->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   // 
			   // price
			   // 
			   this->price->HeaderText = L"Приоритет";
			   this->price->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"1", L"2", L"3" });
			   this->price->Name = L"price";
			   this->price->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			   // 
			   // btn_add_db
			   // 
			   this->btn_add_db->BackColor = System::Drawing::Color::Green;
			   this->btn_add_db->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->btn_add_db->Font = (gcnew System::Drawing::Font(L"Hack", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->btn_add_db->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->btn_add_db->Location = System::Drawing::Point(12, 609);
			   this->btn_add_db->Name = L"btn_add_db";
			   this->btn_add_db->Size = System::Drawing::Size(150, 40);
			   this->btn_add_db->TabIndex = 6;
			   this->btn_add_db->Text = L"Добавить";
			   this->btn_add_db->UseVisualStyleBackColor = false;
			   this->btn_add_db->Click += gcnew System::EventHandler(this, &MyForm::btn_add_db_Click);
			   // 
			   // res_table
			   // 
			   this->res_table->AllowUserToAddRows = false;
			   this->res_table->BackgroundColor = System::Drawing::SystemColors::Control;
			   this->res_table->BorderStyle = System::Windows::Forms::BorderStyle::None;
			   this->res_table->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
			   this->res_table->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::None;
			   dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			   dataGridViewCellStyle2->BackColor = System::Drawing::Color::Transparent;
			   dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Hack", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::WindowText;
			   dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			   dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			   dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			   this->res_table->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle2;
			   this->res_table->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->res_table->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(3) {
				   this->dataGridViewTextBoxColumn1,
					   this->dataGridViewTextBoxColumn2, this->dataGridViewTextBoxColumn3
			   });
			   this->res_table->GridColor = System::Drawing::SystemColors::ControlDarkDark;
			   this->res_table->Location = System::Drawing::Point(422, 109);
			   this->res_table->Name = L"res_table";
			   this->res_table->RightToLeft = System::Windows::Forms::RightToLeft::No;
			   this->res_table->RowHeadersVisible = false;
			   this->res_table->Size = System::Drawing::Size(304, 470);
			   this->res_table->TabIndex = 7;
			   // 
			   // dataGridViewTextBoxColumn1
			   // 
			   this->dataGridViewTextBoxColumn1->HeaderText = L"ID";
			   this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			   this->dataGridViewTextBoxColumn1->ReadOnly = true;
			   this->dataGridViewTextBoxColumn1->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			   this->dataGridViewTextBoxColumn1->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   // 
			   // dataGridViewTextBoxColumn2
			   // 
			   this->dataGridViewTextBoxColumn2->HeaderText = L"Название дисциплины";
			   this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			   this->dataGridViewTextBoxColumn2->ReadOnly = true;
			   this->dataGridViewTextBoxColumn2->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			   this->dataGridViewTextBoxColumn2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   // 
			   // dataGridViewTextBoxColumn3
			   // 
			   this->dataGridViewTextBoxColumn3->HeaderText = L"Длительность курса (в ч.)";
			   this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			   this->dataGridViewTextBoxColumn3->ReadOnly = true;
			   this->dataGridViewTextBoxColumn3->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			   this->dataGridViewTextBoxColumn3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Hack", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label3->Location = System::Drawing::Point(452, 82);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(219, 19);
			   this->label3->TabIndex = 8;
			   this->label3->Text = L"Выбранные дисциплины:";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			   this->ClientSize = System::Drawing::Size(724, 665);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->res_table);
			   this->Controls->Add(this->btn_add_db);
			   this->Controls->Add(this->database);
			   this->Controls->Add(this->max_capacity_label);
			   this->Controls->Add(this->btn_exit);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->btn_result);
			   this->DoubleBuffered = true;
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->Name = L"MyForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"Образовательная траектория";
			   this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->database))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->res_table))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btn_exit_Click(System::Object^ sender, System::EventArgs^ e); // Событие: нажатие на кнопку выхода
	private: System::Void btn_result_Click(System::Object^ sender, System::EventArgs^ e); // Событие: нажатие на кнопку расчета результата
	private: System::Void btn_add_db_Click(System::Object^ sender, System::EventArgs^ e); // Событие: нажатие на кнопку добавления таблицы
	private: System::Void one_item(int wl, int max_capacity, int weights[], int values[]); // Ф-ция: построения матрицы весов
	private: System::Void find_ans(int wl, int max_capacity, int weights[], int** arr); // Ф-ция: построение обратного пути (выходных дисциплин)
	};
}