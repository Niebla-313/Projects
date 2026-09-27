# 🦠 Modelación Epidemiológica

## 📝 Descripción del Proyecto

Este proyecto consiste en la resolución numérica del **Modelo SEIR** (Susceptibles-Expuestos-Infectados-Recuperados) mediante la implementación manual del método de Runge-Kutta de 4to Orden (RK4). Desarrollado en el contexto de la asignatura de Cálculo Científico, el objetivo principal es simular el comportamiento dinámico de una epidemia en una población, evaluando cómo las intervenciones no farmacológicas (como el confinamiento) alteran la propagación del virus a lo largo del tiempo.

## 🧮 Fundamentos Matemáticos y Enfoque Técnico

A nivel de Ciencias de la Computación y Modelado Matemático, el problema se aborda mediante sistemas de Ecuaciones Diferenciales Ordinarias (EDO):

* **Sistemas Compartimentales (SEIR):** La población total $N$ se divide en cuatro estados interconectados donde se introduce un periodo de latencia ($E$), simulando que un individuo infectado aún no es contagioso inicialmente.

* **No Linealidad:** El sistema presenta términos no lineales (como el producto $\frac{\beta S I}{N}$), lo que impide hallar una solución analítica cerrada.

* **Método Numérico (RK4):** Se implementa de forma nativa el algoritmo de Runge-Kutta de 4to Orden para aproximar la solución paso a paso, logrando un error de truncamiento local de $\mathcal{O}(h^5)$ sin depender de librerías externas de integración.

* **Análisis de Umbral y Conservación:** Se evalúa analítica y numéricamente el Número Básico de Reproducción ($R_0$) y se comprueba la conservación estricta de la población total ($S + E + I + R = N$) en cada paso de tiempo.
---
## 🛠️ Tecnologías Utilizadas

* Python 3

* NumPy (Para el manejo estructurado de arreglos y trazado de curvas)

* Matplotlib (Para la visualización de la evolución temporal de los compartimientos)
---
## 📦 Cómo Ejecutar el Proyecto:

1. Descargar la carpeta correspondiente a Modelización de Epidemias.

2. Ejcutar el archivo con `python codigo.py`. 

⬆️ Volver a [Computacion-Cientifica](../README.md)

---

<p align="center">
  <a href="https://github.com/Niebla-313/Projects">
    <img src="https://img.shields.io/badge/Volver%20al%20Portafolio%20Principal-00599C?style=for-the-badge&logo=github&logoColor=white" alt="Volver al inicio">
  </a>
</p>
