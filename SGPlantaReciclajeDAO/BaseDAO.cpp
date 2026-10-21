#include "BaseDAO.h"

using namespace SGPlantaReciclajeDAO;
using namespace System;
using namespace System::IO;   // ← Necesario para DirectoryInfo, Directory, Path, File

// ============================================================
// CONSTRUCTOR
// ============================================================
BaseDAO::BaseDAO() {
	// Calcular la ruta de la carpeta TXT
	this->rutaCarpeta = ObtenerRutaCarpetaTXT();

	// Asegurar que la carpeta exista (por si acaso no fue creada)
	AsegurarExistenciaCarpeta();
}

// getRutaCarpeta: devuelve la ruta absoluta de la carpeta TXT o BIN.
String^ BaseDAO::getRutaCarpeta() {
	return rutaCarpeta;
}

// ============================================================
// MÉTODOS AUXILIARES
// ============================================================

// ObtenerRutaCarpetaTXT: calcula la ruta absoluta de BD\TXT\
// subiendo desde BaseDirectory hasta encontrar la raíz del proyecto
// (la carpeta que contiene el archivo .sln).
String^ BaseDAO::ObtenerRutaCarpetaTXT() {

	// Usar AppDomain::CurrentDomain->BaseDirectory en lugar de
	// Application::StartupPath, porque este último pertenece a
	// System::Windows::Forms y no está disponible en un proyecto DAO.
	String^ startupPath = AppDomain::CurrentDomain->BaseDirectory;

	DirectoryInfo^ dirActual = gcnew DirectoryInfo(startupPath);

	// Subir hasta encontrar la carpeta que contiene un .sln
	while (dirActual != nullptr) {
		array<String^>^ archivosSln = Directory::GetFiles(dirActual->FullName, "*.sln");

		if (archivosSln->Length > 0) {
			// ¡Encontramos la raíz de la solución!
			String^ raizProyecto = dirActual->FullName;
			return Path::Combine(raizProyecto, "BD\\TXT\\");
		}

		dirActual = dirActual->Parent;
	}

	// FALLBACK: si no encontramos .sln, subimos 2 niveles desde BaseDirectory
	DirectoryInfo^ startupDir = gcnew DirectoryInfo(startupPath);
	DirectoryInfo^ parent1 = startupDir->Parent;
	DirectoryInfo^ parent2 = (parent1 != nullptr) ? parent1->Parent : nullptr;
	String^ raizFallback = (parent2 != nullptr) ? parent2->FullName : startupPath;

	return Path::Combine(raizFallback, "BD\\TXT\\");
}

// ObtenerRutaCarpetaBIN: devuelve la ruta absoluta de BD\BIN\
// reutilizando la lógica de búsqueda de la raíz del proyecto.
String^ BaseDAO::ObtenerRutaCarpetaBIN() {
	String^ startupPath = AppDomain::CurrentDomain->BaseDirectory;
	DirectoryInfo^ dirActual = gcnew DirectoryInfo(startupPath);

	// Subir hasta encontrar la carpeta que contiene un .sln
	while (dirActual != nullptr) {
		array<String^>^ archivosSln = Directory::GetFiles(dirActual->FullName, "*.sln");
		if (archivosSln->Length > 0) {
			String^ raizProyecto = dirActual->FullName;
			String^ rutaBIN = Path::Combine(raizProyecto, "BD\\BIN\\");
			// Asegurar que exista la carpeta BIN
			if (!Directory::Exists(rutaBIN)) {
				Directory::CreateDirectory(rutaBIN);
			}
			return rutaBIN;
		}
		dirActual = dirActual->Parent;
	}

	// FALLBACK
	DirectoryInfo^ startupDir = gcnew DirectoryInfo(startupPath);
	DirectoryInfo^ parent2 = (startupDir->Parent != nullptr) ? startupDir->Parent->Parent : nullptr;
	String^ raizFallback = (parent2 != nullptr) ? parent2->FullName : startupPath;
	String^ rutaFallbackBIN = Path::Combine(raizFallback, "BD\\BIN\\");
	if (!Directory::Exists(rutaFallbackBIN)) {
		Directory::CreateDirectory(rutaFallbackBIN);
	}
	return rutaFallbackBIN;
}

// ObtenerRutaArchivo: devuelve la ruta completa de un archivo
// dentro de la carpeta BD\TXT\.
String^ BaseDAO::ObtenerRutaArchivo(String^ nombreArchivo) {
	return Path::Combine(rutaCarpeta, nombreArchivo);
}

// AsegurarExistenciaCarpeta: verifica que la carpeta BD\TXT\
// exista; si no, la crea.
void BaseDAO::AsegurarExistenciaCarpeta() {
	if (!Directory::Exists(rutaCarpeta)) {
		Directory::CreateDirectory(rutaCarpeta);
	}
}