# 🔥 Simulación de Distribución de Calor en 2D

## 📝 Descripción del Proyecto
Este proyecto consiste en el desarrollo de un simulador numérico para modelar la propagación de la temperatura sobre una superficie bidimensional. 

A través de este desarrollo, se recrea de forma computacional el fenómeno físico de la conducción térmica (difusión), permitiendo observar cómo evoluciona el estado del sistema desde unas condiciones iniciales y de contorno específicas hasta alcanzar un estado de equilibrio termodinámico (estado estacionario).

## 🧮 Fundamentos Matemáticos y Enfoque Técnico
La resolución del problema se aborda desde la perspectiva de la **Física Computacional** y el **Análisis Numérico**, fundamentándose en los siguientes pilares:

* **Ecuación de la Conducción del Calor:** Se resuelve la Ecuación en Derivadas Parciales (EDP) parabólica clásica definida como:
  $$\frac{\partial u}{\partial t} = \alpha \left( \frac{\partial^2 u}{\partial x^2} + \frac{\partial^2 u}{\partial y^2} \right)$$
  Donde $u(x, y, t)$ representa la temperatura en una coordenada espacial y un instante de tiempo, y $\alpha$ es la difusividad térmica del material.
* **Discretización por Diferencias Finitas:** Para aproximar las derivadas continuas en un entorno informático, se discretiza el dominio espacial y temporal mediante una rejilla o malla (*grid*). Se aplica el esquema **FTCS** (*Forward-Time Central-Space*), utilizando diferencias hacia adelante para el tiempo y diferencias centrales de segundo orden para el espacio.
* **Condiciones de Contorno (Fronteras):** El sistema permite configurar condiciones tipo **Dirichlet** (mantener los bordes de la placa a una temperatura constante fija) y analizar el flujo de calor interno de la matriz hacia sus extremos.
* **Criterio de Estabilidad (CFL):** Para garantizar que el método iterativo numérico converja y no diverja exponencialmente, se asegura estrictamente el cumplimiento de la condición de estabilidad de Courant-Friedrichs-Lewy en dos dimensiones:
  $$\Delta t \le \frac{\Delta x^2 + \Delta y^2}{8\alpha}$$

## 🛠️ Tecnologías Utilizadas
* **Python 3**
* **NumPy:** Para la manipulación y actualización iterativa de las matrices 2D que representan la malla térmica de forma óptima.
* **SciPy:** Para el soporte de operaciones matemáticas avanzadas y algoritmos de optimización/convolución si aplica.
* **Matplotlib:** Para la generación de gráficos dinámicos (mapas de calor interactivos o *heatmaps*) utilizando `imshow` o `contourf`, permitiendo visualizar visualmente el gradiente de temperatura.
  
---

 ## 📦 Cómo Ejecutar el Proyecto:
 1. Dar clic aqui:
   [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/Niebla-313/Projects/blob/main/Computacion-Cientifica/Simulacion-Distribucion-Calor/Taller3_27321522.ipynb)

---

---
[⬆️ Volver a Computacion-Cientifica](https://github.com/Niebla-313/Projects/tree/main/Computacion-Cientifica)

---
[⬆️ Volver al inicio](https://github.com/Niebla-313/Projects/tree/main)
