#include <iostream>

using namespace std;

// Función auxiliar para encontrar el índice del menor y segundo menor costo en una columna
void encontrar_min_y_segundo_min_indices(const int* arr, const int* indices_excluidos, int tamano, int& min_indice, int& segundo_min_indice) {
    min_indice = -1;
    segundo_min_indice = -1;
    int min_valor = 1000000; // Un valor lo suficientemente grande
    int segundo_min_valor = 1000000; // Un valor lo suficientemente grande

    for (int i = 0; i < tamano; ++i) {
        bool excluido = false;
        for (int j = 0; j < tamano; ++j) {
            if (i == indices_excluidos[j]) {
                excluido = true;
                break;
            }
        }
        if (!excluido) {
            if (arr[i] < min_valor) {
                segundo_min_valor = min_valor;
                segundo_min_indice = min_indice;
                min_valor = arr[i];
                min_indice = i;
            }
            else if (arr[i] < segundo_min_valor) {
                segundo_min_valor = arr[i];
                segundo_min_indice = i;
            }
        }
    }

    // Si no se encuentra un segundo menor índice, devuelve el mismo índice
    if (segundo_min_indice == -1) {
        segundo_min_indice = min_indice;
    }
}

int main() {
    int filas, columnas;

    // Ingresar el número de filas y columnas
    cout << "Ingrese el número de filas: ";
    cin >> filas;
    cout << "Ingrese el número de columnas: ";
    cin >> columnas;

    // Crear matrices dinámicas
    int** costos = new int* [filas];
    for (int i = 0; i < filas; ++i) {
        costos[i] = new int[columnas];
    }
    int* suministro = new int[filas];
    int* demanda = new int[columnas];
    int** asignacion = new int* [filas];
    for (int i = 0; i < filas; ++i) {
        asignacion[i] = new int[columnas]();
    }
    int costo_total = 0; // Variable para acumular el costo total

    // Ingresar datos del problema
    cout << "Ingrese los costos (matriz " << filas << "x" << columnas << "):\n";
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cin >> costos[i][j];
        }
    }

    cout << "Ingrese el suministro (" << filas << " elementos):\n";
    for (int i = 0; i < filas; ++i) {
        cin >> suministro[i];
    }

    cout << "Ingrese la demanda (" << columnas << " elementos):\n";
    for (int j = 0; j < columnas; ++j) {
        cin >> demanda[j];
    }

    // Recorrer las columnas de izquierda a derecha
    for (int j = 0; j < columnas; ++j) {
        int* indices_excluidos = new int[filas];
        int cuenta_excluidos = 0;

        while (demanda[j] > 0 && cuenta_excluidos < filas) {
            int min_indice, segundo_min_indice;
            int* columna = new int[filas];
            for (int i = 0; i < filas; ++i) {
                columna[i] = costos[i][j];
            }
            encontrar_min_y_segundo_min_indices(columna, indices_excluidos, filas, min_indice, segundo_min_indice);

            int fila = (demanda[j] > 0) ? min_indice : segundo_min_indice;
            int cantidad = (suministro[fila] < demanda[j]) ? suministro[fila] : demanda[j];
            asignacion[fila][j] = cantidad;
            costo_total += cantidad * costos[fila][j]; // Acumular el costo
            suministro[fila] -= cantidad;
            demanda[j] -= cantidad;
            indices_excluidos[cuenta_excluidos++] = fila;

            delete[] columna;
        }

        delete[] indices_excluidos;
    }

    // Imprimir la solución inicial
    cout << "Asignación inicial basada en la heurística personalizada:\n";
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << asignacion[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nSuministros restantes:";
    for (int i = 0; i < filas; ++i) {
        cout << " " << suministro[i];
    }
    cout << "\nDemandas restantes:";
    for (int j = 0; j < columnas; ++j) {
        cout << " " << demanda[j];
    }
    cout << "\n";

    // Imprimir el costo total óptimo
    cout << "\nCosto total óptimo: " << costo_total << "\n";

    // Liberar memoria dinámica
    for (int i = 0; i < filas; ++i) {
        delete[] costos[i];
        delete[] asignacion[i];
    }
    delete[] costos;
    delete[] suministro;
    delete[] demanda;
    delete[] asignacion;

    return 0;
}
