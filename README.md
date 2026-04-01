# Ape-3 - Ejercicio Integrador: Arreglos y Estructuras - Algoritmos y Lógica de Programación

## 📌 Información General

* **Institución:** Universidad Técnica de Ambato (UTA).
* **Facultad:** Ingeniería en Sistemas, Electrónica e Industrial.
* **Ciclo Académico:** Enero 2026 - Julio 2026.
* **Nivel:** Primero.

## 🎯 Objetivo

Utilizar estructuras de datos (`struct`), arreglos dinámicos y estructuras de control en el análisis y diseño de algoritmos para resolver problemas de lógica de programación mediante la implementación de un sistema de gestión en C++.

## 1. Sistema de Análisis de Rendimiento Académico

Programa que simula el control de rendimiento para un grupo de *N* estudiantes. Permite ingresar información académica, validarla estrictamente y procesarla para generar clasificaciones y reportes. Cuenta con las siguientes funcionalidades:

* **Gestión y validación de ingresos:**
  * Control de datos para garantizar que las notas estén en el rango de 0 a 10.
  * Validación de porcentaje de asistencia (0 a 100%).
  * Restricción de paralelos únicamente a las opciones A, B o C.
* **Cálculo de promedios ponderados:**
  * Primer parcial (30%).
  * Segundo parcial (30%).
  * Prácticas (40%).
* **Clasificación y estado final:**
  * Asignación de categorías según el promedio: Excelente, Muy bueno, Bueno, En riesgo o Reprobado.
  * Reprobación automática si el porcentaje de asistencia es inferior al 70%, independientemente del promedio académico.
* **Sistema de alertas de rendimiento:**
  * **Inconsistencia:** Se genera si un estudiante tiene un promedio >= 9 pero una asistencia menor al 80%.
  * **Rendimiento estable:** Se marca si las tres notas (parciales y prácticas) son exactamente iguales.
  * **Rendimiento inestable:** Se marca si la diferencia entre la nota mayor y la menor supera los 4 puntos.
* **Generación de Reportes:**
  * **General:** Estadísticas globales del curso, incluyendo promedios totales y por paralelo, cantidad de aprobados/reprobados y métricas extremas.
  * **Detallado:** Tabla tabulada con la información individual de cada estudiante procesado y sus respectivas alertas.
* **Flujo iterativo:** El sistema incluye un menú al finalizar que permite al usuario decidir si desea repetir todo el análisis para un nuevo curso.
