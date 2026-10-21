# SGPlantaReciclaje — Sistema de Gestión de Planta de Reciclaje

![C++/CLI](https://img.shields.io/badge/C%2B%2B-CLI-blue)
![.NET Framework](https://img.shields.io/badge/.NET-Framework-purple)
![Windows Forms](https://img.shields.io/badge/UI-Windows%20Forms-0078D7)
![Visual Studio](https://img.shields.io/badge/IDE-Visual%20Studio%202026-5C2D91)
![License](https://img.shields.io/badge/license-Academic-lightgrey)

Sistema de escritorio para la **gestión del parque de estaciones clasificadoras** de una planta de reciclaje, desarrollado en **C++/CLI** con **Windows Forms** y **.NET Framework**.

El proyecto implementa una **arquitectura en capas** (Modelo – DAO – Controller – Vista) y operaciones **CRUD** completas sobre las entidades del dominio. Utiliza **archivos de texto plano (TXT)** para las estaciones y **archivos binarios (BIN)** para las celdas de proceso, preparando el terreno para una futura migración a base de datos (SQL Server).

---

## 📋 Tabla de Contenidos

- [Descripción General](#-descripción-general)
- [Características Principales](#-características-principales)
- [Arquitectura del Proyecto](#-arquitectura-del-proyecto)
- [Estructura de Carpetas](#-estructura-de-carpetas)
- [Modelo de Datos](#-modelo-de-datos)
- [Capturas de Pantalla](#-capturas-de-pantalla)
- [Requisitos Previos](#-requisitos-previos)
- [Instalación y Ejecución](#-instalación-y-ejecución)
- [Uso del Sistema](#-uso-del-sistema)
- [Patrones de Diseño](#-patrones-de-diseño)
- [Tecnologías Utilizadas](#-tecnologías-utilizadas)
- [Autor](#-autor)
- [Licencia](#-licencia)

---

## 📖 Descripción General

**SGPlantaReciclaje** es un sistema de información que permite administrar el inventario de las **estaciones clasificadoras** y los **módulos de proceso (celdas)** dentro de una planta de reciclaje. 

**Estaciones Clasificadoras:**
- **Serial ID** único.
- **Alias** o nombre descriptivo.
- **Tipo** de estación (Neumática, Magnética, Óptica, Otros).
- **Estado operativo** (Operativo, En Mantenimiento, Falla Crítica, Apagado).
- **Ubicación** específica dentro de la planta.

**Celdas de Proceso:**
- **ID** único de la celda.
- **Nombre** (e.g., "Módulo de Trituración Primaria").
- **Tipo** (Trituración, Lavado, Compactación, Clasificación).
- **Estado** (Activa, En Configuración, Detenida por Alerta, Mantenimiento).
- **Capacidad Máxima** en kg/h.

El sistema permite realizar operaciones **CRUD** sobre ambas entidades, gestionando sus catálogos maestros y garantizando la persistencia de los datos.

---

## ✨ Características Principales

- ✅ **CRUD completo** de estaciones clasificadoras (TXT) y celdas de proceso (BIN).
- ✅ **Búsqueda combinada** por Serial ID, tipo y estado operativo en estaciones.
- ✅ **Catálogos maestros** para estaciones y celdas, cargados dinámicamente en ComboBox no editables.
- ✅ **Persistencia híbrida:** Texto plano (`.txt`) para catálogos y estaciones; Binario (`.bin`) para celdas de proceso.
- ✅ **Ruta centralizada** de los archivos de datos mediante la clase base `BaseDAO`.
- ✅ **Arquitectura en capas** claramente separadas y preparada para migración a SQL Server.
- ✅ **Validaciones** robustas en controladores (IDs únicos, capacidades numéricas mayores a 0) y en la vista.
- ✅ **Helper centralizado (`ComboHelper`)** para el llenado uniforme de todos los ComboBox del sistema.
- ✅ **Interfaz gráfica amigable** con DataGridView y MessageBox de confirmación.

---

## 🏗 Arquitectura del Proyecto

El sistema sigue una arquitectura en capas, donde cada capa reside en su propio proyecto de Visual Studio:

```
┌─────────────────────────────────────────────────────┐
│              CAPA DE PRESENTACIÓN                   │
│           SGPlantaReciclajeView (GUI)               │
│   frmMantEstacion │ frmNuevaEstacion │ frmEditar    │
└──────────────────────┬──────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────┐
│              CAPA DE CONTROL                        │
│          SGPlantaReciclajeController                │
│  EstacionController │ TipoEstacionCtrl │ EstadoCtrl │
└──────────────────────┬──────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────┐
│              CAPA DE PERSISTENCIA                   │
│             SGPlantaReciclajeDAO                    │
│  BaseDAO │ EstacionDAO │ TipoEstacionDAO │ EstadoDAO│
└──────────────────────┬──────────────────────────────┘
                       │
                       ▼
┌─────────────────────────────────────────────────────┐
│              CAPA DE MODELO                         │
│            SGPlantaReciclajeModel                   │
│  EstacionClasificadora │ TipoEstacion │ EstadoOp.   │
└─────────────────────────────────────────────────────┘
```

### Descripción de cada capa

| Capa | Proyecto | Responsabilidad |
|------|----------|-----------------|
| **Modelo** | `SGPlantaReciclajeModel` | Define las entidades (`EstacionClasificadora`, `CeldaProceso`, `TipoEstacion`, `EstadoOperativo`, `TipoCelda`, `EstadoCelda`). |
| **Persistencia** | `SGPlantaReciclajeDAO` | Gestiona archivos TXT y BIN. `BaseDAO` centraliza las rutas `BD\TXT\` y `BD\BIN\`. |
| **Control** | `SGPlantaReciclajeController` | Lógica de negocio, validaciones y sincronización de los repositorios en memoria. |
| **Vista** | `SGPlantaReciclajeView` | Interfaz gráfica Windows Forms y el `ComboHelper` para poblar los ComboBox. |

---

## 📂 Estructura de Carpetas

```
LPOO.2026_2_C07/
│
├── SGPlantaReciclaje.sln                # Solución de Visual Studio
│
├── BD/ # Carpeta de datos (auto-creada)
│ ├── TXT/ # Persistencia en texto plano
│ │ ├── Estaciones.txt
│ │ ├── EstadoOperativo.txt
│ │ ├── TipoEstaciones.txt
│ │ ├── EstadoCeldas.txt # Catálogo de estados de celda
│ │ └── TipoCeldas.txt # Catálogo de tipos de celda
│ └── BIN/ # Persistencia binaria
│ └── celdasProceso.bin # Datos serializados de celdas
│
├── SGPlantaReciclajeModel/ # Capa de Modelo
│ ├── EstacionClasificadora.h / .cpp
│ ├── CeldaProceso.h / .cpp # [Serializable] para binario
│ ├── TipoEstacion.h / .cpp
│ ├── EstadoOperativo.h / .cpp
│ ├── TipoCelda.h / .cpp
│ └── EstadoCelda.h / .cpp
│
├── SGPlantaReciclajeDAO/ # Capa de Persistencia
│ ├── BaseDAO.h / .cpp # Rutas centralizadas
│ ├── EstacionDAO.h / .cpp
│ ├── CeldaProcesoDAO.h / .cpp # Serialización binaria
│ ├── TipoEstacionDAO.h / .cpp
│ ├── EstadoOperativoDAO.h / .cpp
│ ├── TipoCeldaDAO.h / .cpp
│ └── EstadoCeldaDAO.h / .cpp
│
├── SGPlantaReciclajeController/ # Capa de Control
│ ├── EstacionController.h / .cpp
│ ├── CeldaProcesoController.h / .cpp
│ ├── TipoEstacionController.h / .cpp
│ ├── EstadoOperativoController.h / .cpp
│ ├── TipoCeldaController.h / .cpp
│ └── EstadoCeldaController.h / .cpp
│
├── SGPlantaReciclajeView/ # Capa de Presentación (GUI)
│ ├── main.cpp # Punto de entrada
│ ├── ComboHelper.h / .cpp # Helper para todos los ComboBox
│ ├── frmMantEstacion.h / .cpp
│ ├── frmNuevaEstacion.h / .cpp
│ ├── frmEditarEstacion.h / .cpp
│ ├── frmMantCelda.h / .cpp # CRUD de celdas (en desarrollo)
│ └── frmNuevaCelda.h / .cpp
│
├── .gitignore
└── README.md
```

---

## 🗄 Modelo de Datos

### Entidades del dominio

#### `EstacionClasificadora`

| Atributo | Tipo | Descripción |
|----------|------|-------------|
| `serialId` | `String^` | Identificador único visible (PK lógica). |
| `alias` | `String^` | Nombre descriptivo de la estación. |
| `tipo` | `int` | FK → `TipoEstacion.idTipoEstacion`. |
| `estado` | `int` | FK → `EstadoOperativo.idEstadoOperativo`. |
| `ubicacion` | `String^` | Ubicación física dentro de la planta. |

#### `TipoEstacion`

| Atributo | Tipo | Descripción |
|----------|------|-------------|
| `idTipoEstacion` | `int` | Identificador único (PK). |
| `descripcion` | `String^` | Descripción del tipo. |

**Valores del catálogo:**
| ID | Descripción |
|----|-------------|
| 1 | Neumática |
| 2 | Magnética |
| 3 | Óptica |
| 4 | Otros |

#### `EstadoOperativo`

| Atributo | Tipo | Descripción |
|----------|------|-------------|
| `idEstadoOperativo` | `int` | Identificador único (PK). |
| `descripcion` | `String^` | Descripción del estado. |

**Valores del catálogo:**
| ID | Descripción |
|----|-------------|
| 1 | Operativo |
| 2 | En Mantenimiento |
| 3 | Falla Crítica |
| 4 | Apagado |

#### `CeldaProceso` (Persistencia Binaria)
Clase marcada con `[Serializable]` para su uso con `BinaryFormatter`.

| Atributo | Tipo | Descripción |
|----------|------|-------------|
| `id` | `String^` | Identificador único visible (PK lógica). |
| `nombre` | `String^` | Nombre descriptivo de la celda. |
| `tipo` | `int` | FK → `TipoCelda.idTipoCelda`. |
| `estado` | `int` | FK → `EstadoCelda.idEstadoCelda`. |
| `capacidad` | `double` | Capacidad máxima en kg/h. |

#### `EstacionClasificadora` (Persistencia TXT)
*(Se mantiene la estructura original detallada previamente)*

#### Catálogos Maestros (TXT)
- **TipoEstacion / EstadoOperativo** (para Estaciones)
- **TipoCelda / EstadoCelda** (para Celdas): 
  - Tipos: 1-Trituración, 2-Lavado, 3-Compactación, 4-Clasificación.
  - Estados: 1-Activa, 2-En Configuración, 3-Detenida por Alerta, 4-Mantenimiento.

### Formato de los archivos de persistencia

**Archivos TXT (`Estaciones.txt`, etc.):** Formato delimitado por `;` en codificación UTF-8.

**Archivo Binario (`celdasProceso.bin`):** Serialización directa de un `List<CeldaProceso^>` mediante `BinaryFormatter`.

### Formato de los archivos TXT

**`Estaciones.txt`**
```
serialId;alias;tipo;estado;ubicacion
```

Ejemplo:
```
EST-NEU-001;Clasificadora-Neumatica-01;1;1;Linea de Clasificación de Polímeros
SEP-MAG-002;Separadora-Mag-05;2;1;Zona de Extracción de Metales
EST-OPT-003;Clasificadora-Optica-01;3;1;Linea de Clasificación de Polímeros
```

**`TipoEstaciones.txt`**
```
idTipoEstacion;descripcion
```

**`EstadoOperativo.txt`**
```
idEstadoOperativo;descripcion
```

---

## 📸 Capturas de Pantalla

> _Agrega aquí las capturas de pantalla de los formularios una vez que las tengas disponibles._

- **Formulario principal** (`frmMantEstacion`): Listado con DataGridView y criterios de búsqueda.
- **Formulario de registro** (`frmNuevaEstacion`): Alta de una nueva estación.
- **Formulario de edición** (`frmEditarEstacion`): Modificación de una estación existente.
- **Formulario de Celdas** (`frmMantCelda`): Listado de celdas de proceso con validación de capacidad.

---

## ⚙ Requisitos Previos

Antes de compilar y ejecutar el proyecto, asegúrate de tener instalado:

- **Visual Studio 2026** (o superior) con la carga de trabajo **Desarrollo para escritorio con C++**.
- **.NET Framework 4.7.2** o superior.
- **Soporte para C++/CLI** (incluido en la carga de trabajo de C++ de Visual Studio).
- **Windows 10 / 11** (para ejecutar la aplicación Windows Forms).

---

## 🚀 Instalación y Ejecución

### 1. Clonar el repositorio

```bash
git clone https://github.com/ManoloPeru/LPOO.2026_2_C07.git
cd LPOO.2026_2_C07
```

### 2. Abrir la solución en Visual Studio

Haz doble clic en el archivo `SGPlantaReciclaje.sln` o ábrelo desde Visual Studio:

```
Archivo → Abrir → Proyecto/Solución → SGPlantaReciclaje.sln
```

### 3. Compilar la solución

```
Compilar → Compilar solución (Ctrl + Shift + B)
```

### 4. Ejecutar la aplicación

Establece `SGPlantaReciclajeView` como **proyecto de inicio** (clic derecho → Establecer como proyecto de inicio) y presiona `F5` o:

```
Depurar → Iniciar depuración
```

### 5. Verificar la carpeta de datos

Al ejecutarse por primera vez, la aplicación creará automáticamente la carpeta `BD\TXT\` en la raíz de la solución con los archivos de datos correspondientes.

---

## 🖥 Uso del Sistema

### Formulario principal — `frmMantEstacion`

Al iniciar la aplicación, se muestra el formulario de **Mantenimiento de Estaciones** con las siguientes funcionalidades:

| Acción | Descripción |
|--------|-------------|
| **Buscar** | Filtra las estaciones por Serial ID, Tipo y/o Estado operativo. |
| **Limpiar** | Restablece los criterios de búsqueda y muestra todas las estaciones. |
| **Nuevo** | Abre el formulario `frmNuevaEstacion` para registrar una nueva estación. |
| **Editar** | Abre el formulario `frmEditarEstacion` con los datos de la estación seleccionada. |
| **Eliminar** | Elimina la estación seleccionada previa confirmación. |

### Formulario de registro — `frmNuevaEstacion`

Permite ingresar los datos de una nueva estación:

- **Serial ID** (obligatorio, único).
- **Alias** (obligatorio).
- **Tipo** (ComboBox no editable, cargado desde `TipoEstaciones.txt`).
- **Estado** (ComboBox no editable, cargado desde `EstadoOperativo.txt`).
- **Ubicación** (obligatorio).

Al presionar **Grabar**, se valida que todos los campos estén completos y que el Serial ID no exista.

### Formulario de edición — `frmEditarEstacion`

Carga los datos de la estación seleccionada y permite modificar:

- **Serial ID** (solo lectura — es el identificador único).
- **Alias**, **Tipo**, **Estado** y **Ubicación**.

Al presionar **Grabar**, se aplican los cambios y se actualiza el archivo de datos.

---

## 🎨 Patrones de Diseño

| Patrón | Descripción | Aplicación |
|--------|-------------|------------|
| **DAO (Data Access Object)** | Separa la lógica de acceso a datos de la lógica de negocio. | `EstacionDAO`, `TipoEstacionDAO`, `EstadoOperativoDAO` |
| **Controller** | Capa intermedia que gestiona las operaciones y validaciones. | `EstacionController`, `TipoEstacionController`, `EstadoOperativoController` |
| **Herencia** | Clase base con funcionalidad común reutilizable. | `BaseDAO` → DAOs concretos |
| **Encapsulamiento** | Atributos privados con getters/setters públicos. | Todas las clases del modelo |
| **MVC simplificado** | Separación Modelo-Vista-Controlador. | Arquitectura general del sistema |

---

## 🛠 Tecnologías Utilizadas

| Tecnología | Versión | Uso |
|------------|---------|-----|
| **C++/CLI** | — | Lenguaje de programación principal. |
| **.NET Framework** | 4.7.2+ | Plataforma de ejecución. |
| **Windows Forms** | — | Framework de interfaz gráfica. |
| **Visual Studio** | 2026 | IDE de desarrollo. |
| **Git / GitHub** | — | Control de versiones. |
| **Archivos TXT** | — | Persistencia de datos. |

---

## 👨‍💻 Autor

**ManoloPeru**

- GitHub: [@ManoloPeru](https://github.com/ManoloPeru)
- Repositorio: [LPOO.2026_2_C07](https://github.com/ManoloPeru/LPOO.2026_2_C07)

---

## 📄 Licencia

Este proyecto es de uso **académico** y fue desarrollado como parte del curso **LPOO.2026_2_C07** (Laboratorio de Programación Orientada a Objetos).

---

## 📝 Notas Adicionales

### Ruta centralizada de los archivos de datos

La clase `BaseDAO` calcula la ruta de la carpeta `BD\TXT\` de forma dinámica, subiendo desde el directorio de ejecución (`AppDomain::CurrentDomain->BaseDirectory`) hasta encontrar la raíz de la solución (donde está el archivo `.sln`). Esto permite que **todos los proyectos** (Consola y GUI) compartan los mismos archivos de datos, sin duplicación.

Si la carpeta `BD\TXT\` no existe al iniciar la aplicación, `BaseDAO` la crea automáticamente.

### Encoding de los archivos

Los archivos `.txt` se guardan con codificación **UTF-8** para soportar caracteres especiales como tildes (á, é, í, ó, ú) y la letra ñ.

### Validaciones

Todas las operaciones CRUD pasan por una doble validación:

1. **Capa de control** (`EstacionController`): valida reglas de negocio (unicidad, existencia).
2. **Capa de presentación** (`frmNuevaEstacion`, `frmEditarEstacion`): valida campos obligatorios y formato.

---

⭐ **Si este proyecto te resultó útil, no olvides darle una estrella en GitHub.** ⭐
