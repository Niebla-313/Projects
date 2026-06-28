# 🕸️ Algoritmo PageRank de Google

## 📝 Descripción del Proyecto
Este proyecto consiste en la implementación computacional del algoritmo **PageRank**, el sistema fundacional desarrollado por Larry Page y Sergey Brin que revolucionó los motores de búsqueda en internet. 

El objetivo principal es medir la importancia relativa de una serie de páginas web dentro de una red, asumiendo que un sitio es relevante si recibe enlaces (votos) de otras páginas que también son consideradas importantes.

## 🧮 Fundamentos Matemáticos y Enfoque Técnico
A nivel de Ciencias de la Computación, el problema se modela utilizando herramientas avanzadas de **Álgebra Lineal Numérica** y **Procesos Estocásticos**:

* **Modelado de Redes:** La web se representa como un grafo dirigido, el cual se traduce matemáticamente en una **Matriz de Adyacencia** (y posteriormente en una **Matriz de Transición** de probabilidades).
* **Cadenas de Markov:** El comportamiento del usuario se simula como un "navegador aleatorio" (Random Surfer) que salta de un enlace a otro de forma estocástica.
* **El Problema del Fin del Camino (Dead Ends):** Para resolver escenarios donde una página no tiene enlaces de salida o se generan bucles infinitos, se introduce el **Factor de Amortiguación (Damping Factor, típicamente $\alpha = 0.85$)**, permitiendo al usuario "teletransportarse" a cualquier otra página aleatoria de la red.
* **Convergencia:** El algoritmo calcula el vector propio (Eigenvector) dominante correspondiente al valor propio (Eigenvalue) $\lambda = 1$ mediante el **Método de las Potencias (Power Method)**, garantizando que las puntuaciones de relevancia converjan de forma estable.

## 🛠️ Tecnologías Utilizadas
* **Python 3**
* **NumPy** (Para el manejo eficiente de matrices de gran escala)
---

## 📦 Cómo Ejecutar el Proyecto (Opcion 1):
1. Descargar la carpeta `Algoritmo-RageRank Google`.
    <p align="center">
      <a href="https://downgit.github.io/#/home?url=https://github.com/Niebla-313/Projects/tree/main/Computacion-Cientifica/Algoritmo-PageRank-Google" target="_blank">
      <img src="https://img.shields.io/badge/Descargar%20esta%20carpeta-🚀-00599C?style=for-the-badge" alt="Descargar carpeta">
    </a>
  </p>
 2. Ejecutar script: `python taller4_27321522.py`

 ## 📦 Cómo Ejecutar el Proyecto (Opcion 2):
 1. Dar clic aqui:
   [![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/Niebla-313/Projects/blob/main/Computacion-Cientifica/Algoritmo-PageRank-Google/Taller4_27321522.ipynb)

---

---
[⬆️ Volver a Computacion-Cientifica](https://github.com/Niebla-313/Projects/tree/main/Computacion-Cientifica)

---
<p align="center">
  <a href="https://github.com/Niebla-313/Projects">
    <img src="https://img.shields.io/badge/Volver%20al%20Portafolio%20Principal-00599C?style=for-the-badge&logo=github&logoColor=white" alt="Volver al inicio">
  </a>
</p>
