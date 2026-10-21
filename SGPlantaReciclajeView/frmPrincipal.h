#pragma once
#include "frmMantEstacion.h"
#include "frmMantCeldaProceso.h"

namespace SGPlantaReciclajeView {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de frmPrincipal
	/// </summary>
	public ref class frmPrincipal : public System::Windows::Forms::Form
	{
	public:
		frmPrincipal(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~frmPrincipal()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^ mantenimientoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ mantenimientoToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ estaciónClasificadoraToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ celdaDeProcesosToolStripMenuItem;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->mantenimientoToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->estaciónClasificadoraToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->celdaDeProcesosToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->mantenimientoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->menuStrip1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->mantenimientoToolStripMenuItem1 });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(11, 4, 0, 4);
			this->menuStrip1->Size = System::Drawing::Size(749, 37);
			this->menuStrip1->TabIndex = 0;
			// 
			// mantenimientoToolStripMenuItem1
			// 
			this->mantenimientoToolStripMenuItem1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->mantenimientoToolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->estaciónClasificadoraToolStripMenuItem,
					this->celdaDeProcesosToolStripMenuItem
			});
			this->mantenimientoToolStripMenuItem1->Name = L"mantenimientoToolStripMenuItem1";
			this->mantenimientoToolStripMenuItem1->Size = System::Drawing::Size(153, 29);
			this->mantenimientoToolStripMenuItem1->Text = L"Mantenimiento";
			// 
			// estaciónClasificadoraToolStripMenuItem
			// 
			this->estaciónClasificadoraToolStripMenuItem->Name = L"estaciónClasificadoraToolStripMenuItem";
			this->estaciónClasificadoraToolStripMenuItem->Size = System::Drawing::Size(265, 30);
			this->estaciónClasificadoraToolStripMenuItem->Text = L"Estación clasificadora";
			this->estaciónClasificadoraToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmPrincipal::estaciónClasificadoraToolStripMenuItem_Click);
			// 
			// celdaDeProcesosToolStripMenuItem
			// 
			this->celdaDeProcesosToolStripMenuItem->Name = L"celdaDeProcesosToolStripMenuItem";
			this->celdaDeProcesosToolStripMenuItem->Size = System::Drawing::Size(265, 30);
			this->celdaDeProcesosToolStripMenuItem->Text = L"Celda de procesos";
			this->celdaDeProcesosToolStripMenuItem->Click += gcnew System::EventHandler(this, &frmPrincipal::celdaDeProcesosToolStripMenuItem_Click);
			// 
			// mantenimientoToolStripMenuItem
			// 
			this->mantenimientoToolStripMenuItem->Name = L"mantenimientoToolStripMenuItem";
			this->mantenimientoToolStripMenuItem->Size = System::Drawing::Size(32, 19);
			// 
			// frmPrincipal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->ClientSize = System::Drawing::Size(749, 417);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->IsMdiContainer = true;
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"frmPrincipal";
			this->Text = L"Sistema de Gestión - Planta de Reciclaje Automatizada de Mecatrónica";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void estaciónClasificadoraToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		frmMantEstacion^ ventana = gcnew frmMantEstacion();
		ventana->MdiParent = this;
		ventana->Show();
	}

	private: System::Void celdaDeProcesosToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		frmMantCeldaProceso^ ventana = gcnew frmMantCeldaProceso();
		ventana->MdiParent = this;
		ventana->Show();
	}
};
}
