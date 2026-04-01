Algoritmo SistemaRendimientoAcademico
    Definir continuar Como Caracter
    Definir n, i Como Entero
    
    // Variables para el reporte
    Definir cntA, cntB, cntC, cExcelente, cMuyBueno, cBueno, cEnRiesgo, cReprobado Como Entero
    Definir repNota, repAsistencia, aprobados, cEstable, cInestable Como Entero
    Definir sumaTotal, sumaA, sumaB, sumaC, maxProm, minProm, mayor, menor Como Real
    Definir nombreMax, nombreMin Como Caracter
    
    Repetir
        Escribir "============================================================"
        Escribir " SISTEMA DE ANALISIS DE RENDIMIENTO ACADEMICO"
        Escribir "============================================================"
        
        // 1. Ingreso de cantidad de estudiantes
        Repetir
            Escribir " Ingrese el numero de estudiantes del curso: "
            Leer n
            Si n <= 0 Entonces
                Escribir "  [X] El valor debe ser mayor que 0. Intente de nuevo."
            FinSi
        Hasta Que n > 0
        
        // 2. Arreglos paralelos (Simulando el Struct)
        Dimension nombres[n], paralelos[n], categorias[n], estadosFinales[n]
        Dimension notas1[n], notas2[n], notasP[n], asistencias[n], promedios[n]
        Dimension alertasInconsistencia[n], rendimientosEstables[n], rendimientosInestables[n]
        
        // 3. Ingreso de datos y calculos por estudiante
        Para i <- 1 Hasta n Hacer
            Escribir "------------------------------------------------------------"
            Escribir " ESTUDIANTE ", i, " DE ", n
            Escribir "------------------------------------------------------------"
            
            Escribir " Nombre: "
            Leer nombres[i]
            
            Repetir
                Escribir " Paralelo (A/B/C): "
                Leer paralelos[i]
                paralelos[i] <- Mayusculas(paralelos[i])
                Si paralelos[i] <> "A" Y paralelos[i] <> "B" Y paralelos[i] <> "C" Entonces
                    Escribir "  [X] El paralelo solo puede ser A, B o C."
                FinSi
            Hasta Que paralelos[i] = "A" O paralelos[i] = "B" O paralelos[i] = "C"
            
            Repetir
                Escribir " Nota primer parcial (0-10): "
                Leer notas1[i]
            Hasta Que notas1[i] >= 0 Y notas1[i] <= 10
            
            Repetir
                Escribir " Nota segundo parcial (0-10): "
                Leer notas2[i]
            Hasta Que notas2[i] >= 0 Y notas2[i] <= 10
            
            Repetir
                Escribir " Nota practicas (0-10): "
                Leer notasP[i]
            Hasta Que notasP[i] >= 0 Y notasP[i] <= 10
            
            Repetir
                Escribir " Porcentaje de asistencia (0-100): "
                Leer asistencias[i]
            Hasta Que asistencias[i] >= 0 Y asistencias[i] <= 100
            
            // Calculos
            promedios[i] <- (notas1[i] * 0.30) + (notas2[i] * 0.30) + (notasP[i] * 0.40)
            
            Si promedios[i] >= 9.0 Entonces
                categorias[i] <- "Excelente"
            Sino
                Si promedios[i] >= 8.0 Entonces
                    categorias[i] <- "Muy bueno"
                Sino
                    Si promedios[i] >= 7.0 Entonces
                        categorias[i] <- "Bueno"
                    Sino
                        Si promedios[i] >= 6.0 Entonces
                            categorias[i] <- "En riesgo"
                        Sino
                            categorias[i] <- "Reprobado"
                        FinSi
                    FinSi
                FinSi
            FinSi
            
            Si asistencias[i] < 70.0 Entonces
                estadosFinales[i] <- "Reprobado por asistencia"
            Sino
                estadosFinales[i] <- categorias[i]
            FinSi
            
            alertasInconsistencia[i] <- (promedios[i] >= 9.0 Y asistencias[i] < 80.0)
            rendimientosEstables[i] <- (notas1[i] = notas2[i] Y notas2[i] = notasP[i])
            
            // Calcular mayor y menor para inestabilidad
            mayor <- notas1[i]
            Si notas2[i] > mayor Entonces mayor <- notas2[i]; FinSi
            Si notasP[i] > mayor Entonces mayor <- notasP[i]; FinSi
            
            menor <- notas1[i]
            Si notas2[i] < menor Entonces menor <- notas2[i]; FinSi
            Si notasP[i] < menor Entonces menor <- notasP[i]; FinSi
            
            rendimientosInestables[i] <- ((mayor - menor) > 4.0)
            
            // Resumen Inmediato
            Escribir "  [OK] Promedio final: ", promedios[i], " | Estado: ", estadosFinales[i]
            Si alertasInconsistencia[i] Entonces Escribir "  [!] ALERTA: promedio >= 9 pero asistencia < 80%"; FinSi
            Si rendimientosEstables[i] Entonces Escribir "  [E] Rendimiento ESTABLE"; FinSi
            Si rendimientosInestables[i] Entonces Escribir "  [I] Rendimiento INESTABLE"; FinSi
        FinPara
        
        // 4. Reporte general (Inicializar variables)
        cntA <- 0; cntB <- 0; cntC <- 0
        cExcelente <- 0; cMuyBueno <- 0; cBueno <- 0; cEnRiesgo <- 0; cReprobado <- 0
        repNota <- 0; repAsistencia <- 0; aprobados <- 0; cEstable <- 0; cInestable <- 0
        sumaTotal <- 0; sumaA <- 0; sumaB <- 0; sumaC <- 0
        maxProm <- -1.0; minProm <- 11.0
        
        Para i <- 1 Hasta n Hacer
            Si paralelos[i] = "A" Entonces
                cntA <- cntA + 1; sumaA <- sumaA + promedios[i]
            Sino
                Si paralelos[i] = "B" Entonces
                    cntB <- cntB + 1; sumaB <- sumaB + promedios[i]
                Sino
                    cntC <- cntC + 1; sumaC <- sumaC + promedios[i]
                FinSi
            FinSi
            
            Si categorias[i] = "Excelente" Entonces cExcelente <- cExcelente + 1; FinSi
            Si categorias[i] = "Muy bueno" Entonces cMuyBueno <- cMuyBueno + 1; FinSi
            Si categorias[i] = "Bueno" Entonces cBueno <- cBueno + 1; FinSi
            Si categorias[i] = "En riesgo" Entonces cEnRiesgo <- cEnRiesgo + 1; FinSi
            Si categorias[i] = "Reprobado" Entonces cReprobado <- cReprobado + 1; FinSi
            
            Si promedios[i] < 6.0 Y asistencias[i] >= 70.0 Entonces repNota <- repNota + 1; FinSi
            Si asistencias[i] < 70.0 Entonces repAsistencia <- repAsistencia + 1; FinSi
            Si estadosFinales[i] <> "Reprobado" Y estadosFinales[i] <> "Reprobado por asistencia" Entonces aprobados <- aprobados + 1; FinSi
            
            sumaTotal <- sumaTotal + promedios[i]
            
            Si promedios[i] > maxProm Entonces
                maxProm <- promedios[i]; nombreMax <- nombres[i]
            FinSi
            Si promedios[i] < minProm Entonces
                minProm <- promedios[i]; nombreMin <- nombres[i]
            FinSi
            
            Si rendimientosEstables[i] Entonces cEstable <- cEstable + 1; FinSi
            Si rendimientosInestables[i] Entonces cInestable <- cInestable + 1; FinSi
        FinPara
        
        Escribir "============================================================"
        Escribir "  R E P O R T E   G E N E R A L   D E L   C U R S O"
        Escribir "============================================================"
        Escribir " 1. Total de estudiantes procesados : ", n
        Escribir " 2. Promedio general del curso      : ", sumaTotal / n
        Escribir " 3. Mayor promedio : ", maxProm, " -> ", nombreMax
        Escribir " 4. Menor promedio : ", minProm, " -> ", nombreMin
        Escribir " 5. Porcentaje de aprobados         : ", (aprobados / n) * 100, "%"
        
        Escribir "============================================================"
        Escribir "  DETALLE POR ESTUDIANTE"
        Escribir "============================================================"
        Para i <- 1 Hasta n Hacer
            Escribir i, ". ", nombres[i], " | Par: ", paralelos[i], " | Prom: ", promedios[i], " | Est: ", estadosFinales[i]
        FinPara
        Escribir "============================================================"
        
        // 6. Preguntar si se repite
        Escribir " Desea analizar otro curso? (S/N): "
        Leer continuar
        continuar <- Mayusculas(continuar)
        
    Hasta Que continuar <> "S"
    
    Escribir " Gracias por usar el sistema. Hasta pronto!"
FinAlgoritmo
