#include <iostream>
#include <string>


using namespace std;

const int MAXI = 10;
const int INF = 1000000000;

string nombres[MAXI];
int cantidad = 0;
int ady[MAXI][MAXI];

int indiceIsla(const string& nombre) {
    for (int i = 0; i < cantidad; i++) {
        if (nombres[i] == nombre) {
            return i;
        }
    }

    if (cantidad == MAXI) {
        return -1;
    }

    nombres[cantidad] = nombre;
    cantidad++;
    return cantidad - 1;
}

int main() {
    int N, M;
    int Pinicial, C;

    cin >> N >> M;
    if (N < 2 || N > MAXI || M < 1 || M > 20) {
        return 1;
    }

    cin >> Pinicial >> C;
    if (Pinicial < 1 || Pinicial > 1000 || C < 1 || C > 50) {
        return 1;
    }

    string origenNombre, destinoNombre;
    cin >> origenNombre >> destinoNombre;

    for (int i = 0; i < MAXI; i++) {
        for (int j = 0; j < MAXI; j++) {
            ady[i][j] = 0;
        }
    }

    int origen = indiceIsla(origenNombre);
    int destino = indiceIsla(destinoNombre);
    if (origen == -1 || destino == -1) {
        return 1;
    }

    for (int i = 0; i < M; i++) {
        string a, b;
        int dias;

        cin >> a >> b >> dias;
        if (dias < 1 || dias > 1000) {
            return 1;
        }

        int u = indiceIsla(a);
        int v = indiceIsla(b);
        if (u == -1 || v == -1 || cantidad > N) {
            return 1;
        }

        if (ady[u][v] == 0 || dias < ady[u][v]) {
            ady[u][v] = dias;
            ady[v][u] = dias;
        }
    }

    int dist[MAXI];
    int previo[MAXI];
    bool visitado[MAXI];

    for (int i = 0; i < cantidad; i++) {
        dist[i] = INF;
        previo[i] = -1;
        visitado[i] = false;
    }
    dist[origen] = 0;

    for (int i = 0; i < cantidad; i++) {
        int u = -1;

        for (int j = 0; j < cantidad; j++) {
            if (!visitado[j] && dist[j] != INF && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1) {
            break;
        }

        visitado[u] = true;

        for (int v = 0; v < cantidad; v++) {
            if (ady[u][v] > 0 && !visitado[v] && dist[u] + ady[u][v] < dist[v]) {
                dist[v] = dist[u] + ady[u][v];
                previo[v] = u;
            }
        }
    }

    if (dist[destino] == INF) {
        return 1;
    }

    int camino[MAXI];
    int largo = 0;

    for (int i = destino; i != -1; i = previo[i]) {
        camino[largo] = i;
        largo++;
    }

    for (int i = largo - 1; i >= 0; i--) {
        cout << nombres[camino[i]];
        if (i > 0) {
            cout << " -> ";
        }
    }
    cout << endl;

    int Dfinal = dist[destino];
    int Rfinal = Pinicial - Dfinal * C;

    if (Rfinal > 0) {
        cout << "Atenea los guio sabiamente en " << Dfinal
            << " dias. Provisiones restantes: " << Rfinal << endl;
    } else if (Rfinal == 0) {// Si bien en el proyecto, dice "llegaron a su hogar con lo justo", en el ejemplo de salida, dice "llegaron con lo justo", para respetar la del caso"
        cout << "Los hombres llegaron con lo justo. Atenea los guio en "
            << Dfinal << " dias a su destino" << endl;
    } else {
        cout << "Los hombres no sobrevivieron a la furia de Poseidon, lamentablemente "
            << "todos han perecido en el viaje, Atenea se encuentra decepcionada" << endl;
    } 

    return 0;
}
