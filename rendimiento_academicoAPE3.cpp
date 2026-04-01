
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>     // max(), min() con initializer_list
#include <limits>        // numeric_limits — para limpiar el buffer de cin
using namespace std;

// ─────────────────────────────────────────────
//  ESTRUCTURA DE DATOS DEL ESTUDIANTE
// ─────────────────────────────────────────────
struct Estudiante {
    string nombre;
    char   paralelo;
    double nota1;        // Primer parcial  (30 %)
    double nota2;        // Segundo parcial (30 %)
    double notaP;        // Practicas       (40 %)
    double asistencia;
    double promedio;
    string categoria;
    string estadoFinal;
    bool   alertaInconsistencia;
    bool   rendimientoEstable;
    bool   rendimientoInestable;
};

// ─────────────────────────────────────────────
//  PROTOTIPOS
// ─────────────────────────────────────────────
int    leerEnteroPositivo(const string& mensaje);
double leerNota(const string& mensaje);
double leerAsistencia();
char   leerParalelo();
void   calcularEstudiante(Estudiante& e);
void   mostrarReporteGeneral(const Estudiante estudiantes[], int n);
void   separador(char c = '-', int ancho = 60);
void   titulo(const string& texto);          // CORREC. 8: sin parametro 'ancho'

// ─────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────
int main() {
    char repetir;

    cout << "\n";
    separador('=');
    titulo("SISTEMA DE ANALISIS DE RENDIMIENTO ACADEMICO");
    separador('=');

    do {
        // ── 1. Numero de estudiantes ───────────────────────
        int n = leerEnteroPositivo("\n  Ingrese el numero de estudiantes del curso: ");

        // ── 2. Arreglo dinamico ────────────────────────────
        Estudiante* estudiantes = new Estudiante[n];

        // ── 3. Ingreso de datos ────────────────────────────
        //
        // CORREC. 1: cin.ignore() UNA SOLA VEZ antes del bucle.
        // Limpia el '\n' que deja "cin >> n".  Si estuviera dentro
        // del bucle consumiria el primer caracter del nombre a partir
        // del segundo estudiante.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        for (int i = 0; i < n; i++) {
            separador();
            cout << "  ESTUDIANTE " << (i + 1) << " DE " << n << "\n";
            separador();

            // Nombre (getline requiere buffer limpio)
            cout << "  Nombre: ";
            getline(cin, estudiantes[i].nombre);

            // Paralelo
            estudiantes[i].paralelo = leerParalelo();

            // Notas
            estudiantes[i].nota1 = leerNota("  Nota primer parcial  (0-10): ");
            estudiantes[i].nota2 = leerNota("  Nota segundo parcial (0-10): ");
            estudiantes[i].notaP = leerNota("  Nota practicas       (0-10): ");

            // Asistencia
            estudiantes[i].asistencia = leerAsistencia();

            // Calcular y clasificar
            calcularEstudiante(estudiantes[i]);

            // Resumen inmediato
            cout << fixed << setprecision(2);
            cout << "\n  [OK] Promedio final: "
                 << estudiantes[i].promedio
                 << "  |  Estado: " << estudiantes[i].estadoFinal << "\n";

            if (estudiantes[i].alertaInconsistencia)
                cout << "  [!] ALERTA: promedio >= 9 pero asistencia < 80%\n";
            if (estudiantes[i].rendimientoEstable)
                cout << "  [E] Rendimiento ESTABLE (tres notas iguales)\n";
            if (estudiantes[i].rendimientoInestable)
                cout << "  [I] Rendimiento INESTABLE (diferencia entre notas > 4)\n";

            // Limpiar '\n' que deja la ultima lectura numerica,
            // para que el getline del proximo estudiante funcione bien.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // ── 4. Reporte general ─────────────────────────────
        mostrarReporteGeneral(estudiantes, n);

        // ── 5. Liberar memoria ─────────────────────────────
        delete[] estudiantes;

        // ── 6. Repetir? ────────────────────────────────────
        cout << "\n  Desea analizar otro curso? (S/N): ";
        cin >> repetir;
        repetir = toupper((unsigned char)repetir);

        // CORREC. 2: limpiar el '\n' que deja "cin >> repetir"
        // para que el cin.ignore() del inicio del proximo ciclo
        // no quede desfasado.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (repetir == 'S');

    separador('=');
    cout << "  Gracias por usar el sistema. Hasta pronto!\n";
    separador('=');
    cout << "\n";

    return 0;
}

// ─────────────────────────────────────────────
//  CALCULO Y CLASIFICACION
// ─────────────────────────────────────────────
void calcularEstudiante(Estudiante& e) {
    // Promedio ponderado
    e.promedio = e.nota1 * 0.30 + e.nota2 * 0.30 + e.notaP * 0.40;

    // Categoria por promedio
    if      (e.promedio >= 9.0) e.categoria = "Excelente";
    else if (e.promedio >= 8.0) e.categoria = "Muy bueno";
    else if (e.promedio >= 7.0) e.categoria = "Bueno";
    else if (e.promedio >= 6.0) e.categoria = "En riesgo";
    else                        e.categoria = "Reprobado";

    // Estado final (asistencia < 70 % sobreescribe la categoria)
    if (e.asistencia < 70.0)
        e.estadoFinal = "Reprobado por asistencia";
    else
        e.estadoFinal = e.categoria;

    // Alerta de inconsistencia
    e.alertaInconsistencia = (e.promedio >= 9.0 && e.asistencia < 80.0);

    // Rendimiento estable: las tres notas son exactamente iguales
    e.rendimientoEstable = (e.nota1 == e.nota2 && e.nota2 == e.notaP);

    // Rendimiento inestable: diferencia max-min > 4
    double mayor = max({e.nota1, e.nota2, e.notaP});
    double menor = min({e.nota1, e.nota2, e.notaP});
    e.rendimientoInestable = ((mayor - menor) > 4.0);
}

// ─────────────────────────────────────────────
//  REPORTE GENERAL
// ─────────────────────────────────────────────
void mostrarReporteGeneral(const Estudiante estudiantes[], int n) {

    int cntA = 0, cntB = 0, cntC = 0;
    int cExcelente = 0, cMuyBueno = 0, cBueno = 0, cEnRiesgo = 0, cReprobado = 0;
    int repNota = 0, repAsistencia = 0;
    double sumaTotal = 0, sumaA = 0, sumaB = 0, sumaC = 0;
    double maxProm = -1.0, minProm = 11.0;
    string nombreMax, nombreMin;
    int cEstable = 0, cInestable = 0;

    for (int i = 0; i < n; i++) {
        const Estudiante& e = estudiantes[i];

        // Por paralelo
        if      (e.paralelo == 'A') { cntA++; sumaA += e.promedio; }
        else if (e.paralelo == 'B') { cntB++; sumaB += e.promedio; }
        else                        { cntC++; sumaC += e.promedio; }

        // Por categoria (promedio academico, independiente de asistencia)
        if      (e.categoria == "Excelente") cExcelente++;
        else if (e.categoria == "Muy bueno") cMuyBueno++;
        else if (e.categoria == "Bueno")     cBueno++;
        else if (e.categoria == "En riesgo") cEnRiesgo++;
        else                                 cReprobado++;

        // Reprobado por nota (promedio < 6 con asistencia suficiente)
        if (e.promedio < 6.0 && e.asistencia >= 70.0) repNota++;

        // Reprobado por asistencia
        if (e.asistencia < 70.0) repAsistencia++;

        sumaTotal += e.promedio;

        if (e.promedio > maxProm) { maxProm = e.promedio; nombreMax = e.nombre; }
        if (e.promedio < minProm) { minProm = e.promedio; nombreMin = e.nombre; }

        if (e.rendimientoEstable)   cEstable++;
        if (e.rendimientoInestable) cInestable++;
    }

    double promedioGeneral = sumaTotal / n;

    // CORREC. 3: variable inicializada directamente en 0.
    // La version anterior calculaba "n - repNota - repAsistencia" y
    // luego lo sobreescribia con 0 en la linea siguiente (codigo muerto).
    int aprobados = 0;
    for (int i = 0; i < n; i++) {
        if (estudiantes[i].estadoFinal != "Reprobado" &&
            estudiantes[i].estadoFinal != "Reprobado por asistencia")
            aprobados++;
    }

    // ── Imprimir reporte ───────────────────────────────────
    cout << fixed << setprecision(2);
    cout << "\n";
    separador('=');
    titulo("  R E P O R T E   G E N E R A L   D E L   C U R S O");
    separador('=');

    cout << "\n  1.  Total de estudiantes procesados : " << n << "\n";

    cout << "\n  2.  Estudiantes por paralelo:\n";
    cout << "        Paralelo A : " << cntA << "\n";
    cout << "        Paralelo B : " << cntB << "\n";
    cout << "        Paralelo C : " << cntC << "\n";

    cout << "\n  3.  Estudiantes por categoria (por promedio):\n";
    cout << "        Excelente  : " << cExcelente << "\n";
    cout << "        Muy bueno  : " << cMuyBueno  << "\n";
    cout << "        Bueno      : " << cBueno     << "\n";
    cout << "        En riesgo  : " << cEnRiesgo  << "\n";
    cout << "        Reprobado  : " << cReprobado << "\n";

    cout << "\n  4.  Reprobados por nota            : " << repNota << "\n";
    cout << "  5.  Reprobados por asistencia      : " << repAsistencia << "\n";

    cout << "\n  6.  Promedio general del curso     : " << promedioGeneral << "\n";

    cout << "\n  7.  Promedio por paralelo:\n";
    cout << "        Paralelo A : " << (cntA > 0 ? sumaA / cntA : 0.0) << "\n";
    cout << "        Paralelo B : " << (cntB > 0 ? sumaB / cntB : 0.0) << "\n";
    cout << "        Paralelo C : " << (cntC > 0 ? sumaC / cntC : 0.0) << "\n";

    cout << "\n  8.  Mayor promedio : " << maxProm << "  ->  " << nombreMax << "\n";
    cout << "  9.  Menor promedio : " << minProm << "  ->  " << nombreMin << "\n";

    double pctAprobados = (double)aprobados / n * 100.0;
    cout << "\n  10. Porcentaje de aprobados        : "
         << pctAprobados << "% (" << aprobados << " de " << n << ")\n";

    double pctEstable = (double)cEstable / n * 100.0;
    cout << "  11. Rendimiento estable            : "
         << pctEstable << "% (" << cEstable << " estudiantes)\n";

    double pctInestable = (double)cInestable / n * 100.0;
    cout << "  12. Rendimiento inestable          : "
         << pctInestable << "% (" << cInestable << " estudiantes)\n";

    separador('=');

    // ── Tabla detalle ──────────────────────────────────────
    cout << "\n";
    titulo("  DETALLE POR ESTUDIANTE");
    separador();
    cout << setw(4)  << "#"
         << setw(22) << "Nombre"
         << setw(5)  << "Par"
         << setw(7)  << "P1"
         << setw(7)  << "P2"
         << setw(7)  << "Prac"
         << setw(8)  << "Asist"
         << setw(7)  << "Prom"
         << "  Estado\n";
    separador();

    for (int i = 0; i < n; i++) {
        const Estudiante& e = estudiantes[i];

        // CORREC. 4: "87%" se forma como string antes de pasarlo a setw().
        // Sin esto, setw(8) solo afectaba al numero; el '%' se imprimia
        // fuera del campo, desalineando la columna "Prom" y el estado.
        string celAsist = to_string((int)e.asistencia) + "%";

        cout << setw(4)  << (i + 1)
             << setw(22) << e.nombre.substr(0, 20)
             << setw(5)  << e.paralelo
             << setw(7)  << e.nota1
             << setw(7)  << e.nota2
             << setw(7)  << e.notaP
             << setw(8)  << celAsist
             << setw(7)  << e.promedio
             << "  " << e.estadoFinal;

        if (e.alertaInconsistencia) cout << " [!]";
        if (e.rendimientoEstable)   cout << " [E]";
        if (e.rendimientoInestable) cout << " [I]";
        cout << "\n";
    }

    separador('=');
    cout << "  Leyenda: [!] Alerta inconsistencia  [E] Estable  [I] Inestable\n";
    separador('=');
}

// ─────────────────────────────────────────────
//  FUNCIONES DE VALIDACION / ENTRADA
//
//  CORREC. 5-7: se usa un bucle while(true) con rama de error que
//  llama a cin.clear() + cin.ignore() cuando la entrada no es
//  numerica, evitando el bucle infinito del do-while original.
// ─────────────────────────────────────────────

int leerEnteroPositivo(const string& mensaje) {
    int val;
    while (true) {
        cout << mensaje;
        if (cin >> val) {
            if (val > 0) break;
            cout << "  [X] El valor debe ser mayor que 0. Intente de nuevo.\n";
        } else {
            cout << "  [X] Entrada invalida. Ingrese un numero entero positivo.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return val;
}

double leerNota(const string& mensaje) {
    double val;
    while (true) {
        cout << mensaje;
        if (cin >> val) {
            if (val >= 0.0 && val <= 10.0) break;
            cout << "  [X] La nota debe estar entre 0 y 10. Intente de nuevo.\n";
        } else {
            cout << "  [X] Entrada invalida. Ingrese un numero (ej: 7.5).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return val;
}

double leerAsistencia() {
    double val;
    while (true) {
        cout << "  Porcentaje de asistencia (0-100): ";
        if (cin >> val) {
            if (val >= 0.0 && val <= 100.0) break;
            cout << "  [X] La asistencia debe estar entre 0 y 100. Intente de nuevo.\n";
        } else {
            cout << "  [X] Entrada invalida. Ingrese un numero (ej: 85).\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return val;
}

char leerParalelo() {
    char c;
    do {
        cout << "  Paralelo (A/B/C): ";
        cin >> c;
        c = toupper((unsigned char)c);
        if (c != 'A' && c != 'B' && c != 'C')
            cout << "  [X] El paralelo solo puede ser A, B o C. Intente de nuevo.\n";
    } while (c != 'A' && c != 'B' && c != 'C');
    return c;
}

// ─────────────────────────────────────────────
//  UTILIDADES DE PRESENTACION
// ─────────────────────────────────────────────

void separador(char c, int ancho) {
    cout << "  ";
    for (int i = 0; i < ancho; i++) cout << c;
    cout << "\n";
}

// CORREC. 8: eliminado el parametro 'ancho' que estaba declarado
// pero nunca se usaba dentro del cuerpo de la funcion.
void titulo(const string& texto) {
    cout << "  " << texto << "\n";
}
