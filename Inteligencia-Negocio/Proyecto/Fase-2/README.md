# 📊 Proyecto de Inteligencia de Negocios (BI) End-to-End

En esta fase se encuentra una solución completa y **100% reproducible** de **Business Intelligence (BI)**. Incluye la infraestructura contenerizada de la base de datos, el pipeline de datos automatizado y el reporte interactivo final listo para su análisis.

---

## 📁 Estructura del Proyecto y Componentes

El proyecto está organizado de la siguiente manera para facilitar su despliegue local:

* **`database/`**: Infraestructura de la base de datos.
    * `Dockerfile` & `.yml`: Configuración para desplegar el motor de base de datos en un contenedor Docker.
    * `.sql`: Scripts DDL de creación del Data Warehouse (Esquema Constelación), Modelo Relacional y su insert de datos.
    * `.txt`: Semaforo para dar paso al uso de los ETL.
* **`etl/`**: Extracción, Transformación y Carga.
    * `data-integration/`: Entorno para la ejecución de **Pentaho Data Integration (PDI)**.
    * `*.ktr` & `*.kjb`: Transformaciones y Jobs de Pentaho que automatizan la carga hacia el DW.
    * `*.xlsx`: Archivos de datos locales utilizados como fuentes para el proceso.
* **`dashboard/`**: Capa de presentación y analítica.
    * `*.pbix`: Archivo interactivo de **Power BI** con el modelo semántico y los tableros diseñados.

---

## 🛠️ Stack Tecnológico
* **Infraestructura:** Docker & Docker Compose
* **Orquestación y ETL:** Pentaho Data Integration
* **Data Warehouse:** PostgreSQL
* **Visualización:** Power BI Desktop
---
### 📋 Prerrequisitos
Antes de comenzar, asegúrate de tener instalado en tu equipo:
*   [Docker Desktop](https://www.docker.com/products/docker-desktop/) activo y corriendo.
*   [Power BI Desktop](https://powerbi.microsoft.com/desktop/) (para la visualización de tableros).
---
## 📦 Cómo Ejecutar el Proyecto :
1. Descargar la carpeta `Proyecto-Datos-BI`.
<p align="center">
  <a href="https://github.com/Niebla-313/Projects/releases/download/v1.0.0/Proyecto-Datos-BI.rar" target="_blank">
    <img src="https://img.shields.io/badge/Descargar%20esta%20carpeta-🚀-00599C?style=for-the-badge" alt="Descargar carpeta">
  </a>
</p>
 2. Ejecutar script: `python taller4_27321522.py`
