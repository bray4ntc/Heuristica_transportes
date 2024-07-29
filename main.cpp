#include <iostream>

using namespace std;

void encontrar_minimos(const int* arr, const int* indices_excluidos, int tamano, int& min_indice, int& segundo_min_indice) {
    min_indice = -1;
    segundo_min_indice = -1;
    int min_valor = 1000000; // Un valor lo suficientemente grande para las comparaciones
    int segundo_min_valor = 1000000;

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

    // para ingresar el numero de filas y columnas de la matriz de costos
    cout << "Ingrese el numero de filas: ";
    cin >> filas;
    cout << "Ingrese el numero de columnas: ";
    cin >> columnas;

    // Crear matrices dinámicas
    int** costos = new int* [filas];
    for (int i = 0; i < filas; ++i) {
        costos[i] = new int[columnas];
    }
    int* oferta = new int[filas];
    int* demanda = new int[columnas];
    int** asignacion = new int* [filas];
    for (int i = 0; i < filas; ++i) {
        asignacion[i] = new int[columnas]();
    }
    int costo_total = 0; // Variable para acumular el costo total

    // Para ingresar la matriz de costos
    cout << "Ingrese los costos (matriz " << filas << "x" << columnas << "):\n";
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cin >> costos[i][j];
        }
    }
    //Para ingresar por teclado la oferta
    cout << "Ingrese la oferta (" << filas << " elementos):\n";
    for (int i = 0; i < filas; ++i) {
        cin >> oferta[i];
    }
    //para ingresar por teclado las respectivas demandas
    cout << "Ingrese la demanda (" << columnas << " elementos):\n";
    for (int j = 0; j < columnas; ++j) {
        cin >> demanda[j];
    }

    // Para recorrer las columnas de izquierda a derecha
    for (int j = 0; j < columnas; ++j) {
        int* indices_excluidos = new int[filas];
        int cuenta_excluidos = 0;

        while (demanda[j] > 0 && cuenta_excluidos < filas) {
            int min_indice, segundo_min_indice;
            int* columna = new int[filas];
            for (int i = 0; i < filas; ++i) {
                columna[i] = costos[i][j];
            }
            encontrar_minimos(columna, indices_excluidos, filas, min_indice, segundo_min_indice);

            int fila = (demanda[j] > 0) ? min_indice : segundo_min_indice;
            int cantidad = (oferta[fila] < demanda[j]) ? oferta[fila] : demanda[j];
            asignacion[fila][j] = cantidad;
            costo_total += cantidad * costos[fila][j];
            oferta[fila] -= cantidad;
            demanda[j] -= cantidad;
            indices_excluidos[cuenta_excluidos++] = fila;

            delete[] columna;
        }

        delete[] indices_excluidos;
    }

    cout << "Asignacion inicial o solucion inicial :\n";
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            cout << asignacion[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\n";

    cout << "\nCosto total inicial: " << costo_total << "\n";

    for (int i = 0; i < filas; ++i) {
        delete[] costos[i];
        delete[] asignacion[i];
    }
    delete[] costos;
    delete[] oferta;
    delete[] demanda;
    delete[] asignacion;

    return 0;
}
