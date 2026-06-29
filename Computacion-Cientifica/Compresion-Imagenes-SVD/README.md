# 🖼️ Compresión de Imágenes mediante SVD

## 📝 Descripción del Proyecto
Este proyecto implementa un sistema de compresión de imágenes basado en la **Descomposición en Valores Singulares (SVD)**, una técnica avanzada de álgebra lineal numérica. 

El objetivo es reducir de forma drástica el tamaño de almacenamiento de una imagen digital mediante la aproximación de matrices de bajo rango. El algoritmo permite encontrar un equilibrio óptimo entre el porcentaje de compresión (ahorro de espacio) y la fidelidad o calidad visual de la imagen reconstruida.

## 🧮 Fundamentos Matemáticos y Enfoque Técnico
El procesamiento digital de imágenes trata a cada canal de una imagen como una matriz de píxeles. El algoritmo opera bajo los siguientes principios:

* **Factorización de Matrices (SVD):** Cualquier matriz real $A$ de dimensiones $m \times n$ se puede descomponer en el producto de tres matrices:
  $$A = U \Sigma V^T$$
  Donde $U$ ($m \times m$) y $V^T$ ($n \times n$) son matrices ortogonales que contienen los vectores singulares, y $\Sigma$ ($m \times n$) es una matriz diagonal que contiene los **valores singulares** ($\sigma_i$) ordenados de mayor a menor valor de magnitud.
* **Aproximación de Bajo Rango (Teorema de Eckart-Young-Mirsky):** Los primeros valores singulares contienen la mayor parte de la información geométrica y de contraste de la imagen. Al conservar únicamente los primeros $k$ valores singulares (donde $k \ll \min(m, n)$) y truncar el resto a cero, se obtiene la mejor aproximación posible de rango $k$ de la matriz original ($A_k$).
* **Eficiencia de Almacenamiento:** En lugar de almacenar $m \times n$ píxeles, el sistema solo necesita almacenar $(m \times k) + k + (n \times k)$ datos. A medida que $k$ disminuye, el archivo pesa considerablemente menos, simulando un algoritmo de compresión con pérdida (*lossy compression*).
* **Procesamiento Multicanal:** Para imágenes a color, el algoritmo descompone y procesa de forma independiente las tres matrices correspondientes a los canales **RGB** (Rojo, Verde y Azul) para luego unificar el resultado en la reconstrucción final.

## 🛠️ Tecnologías Utilizadas
* **Python 3**
* **NumPy:** Uso específico de la función estandarizada `numpy.linalg.svd` para realizar la factorización matricial de alto rendimiento.
* **Matplotlib:** Para mostrar la comparación visual lado a lado de la imagen original versus la comprimida y graficar la curva de decaimiento de los valores singulares (demostrando matemáticamente cómo se concentra la energía de la información).

 ## 📦 Cómo Ejecutar el Proyecto (Opcion 2):
 1. Dar clic aqui:
   [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/Niebla-313/Projects/blob/main/Computacion-Cientifica/Compresion-Imagenes-SVD/Taller1.ipynb)

---

---
[⬆️ Volver a Computacion-Cientifica](https://github.com/Niebla-313/Projects/tree/main/Computacion-Cientifica)

---
<p align="center">
  <a href="https://github.com/Niebla-313/Projects">
    <img src="https://img.shields.io/badge/Volver%20al%20Portafolio%20Principal-00599C?style=for-the-badge&logo=github&logoColor=white" alt="Volver al inicio">
  </a>
</p>
