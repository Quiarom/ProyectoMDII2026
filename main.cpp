#include <cmath>
#include <iostream>
#include <string>

using namespace std;

const int MAXI = 40;// max de islas (no recuerdo si eso lo decia el enunciado lol)
const int INF = INT_MAX;//El infinitoooo

string nombres[MAXI];
int cantidad = 0;
int ady[MAXI][MAXI];          // matriz de adyacencia (0 = sin ruta directa)

// Devuelve el indice de la isla; si no existe, la registra
int indiceIsla(const string &nombre) {
    for (int i = 0; i < cantidad; i++) {
        if (nombres[i] == nombre) return i;
    }
    nombres[cantidad] = nombre;
    return cantidad++;
}

int main() {
    int N, M, Pinicial, C;
    cin >> N >> M;
    if (N < 2 || N > 10 || M < 1 || M > 20) {
        //error
        return 1;
    }

    cin >> Pinicial >> C;
    if (Pinicial < 1 || Pinicial > 1000 || C < 1 || C > 50) {
        //error 
        return 1;
    }

    string origenNombre, destinoNombre;
    cin >> origenNombre >> destinoNombre;

    for (int i = 0; i < MAXI; i++)
        for (int j = 0; j < MAXI; j++)
            ady[i][j] = 0;

    int origen = indiceIsla(origenNombre);
    int destino = indiceIsla(destinoNombre);

    // Lectura de las rutas | Un grafo no dirigido 
    for (int k = 0; k < M; k++) {
        string a, b;
        int d;
        cin >> a >> b >> d;
        if (d < 1 || d > 1000) {
            //error
            return 1;
        }
        int u = indiceIsla(a);
        int v = indiceIsla(b);
        if (cantidad > N) {
            //error
            return 1;
        }
        // iffff hay rutas repetidas entre las mismas islas tons c queda la menor
        if (ady[u][v] == 0 || d < ady[u][v]) {
            ady[u][v] = d;
            ady[v][u] = d;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////
    //                   Algoritmo de Dijkstra                                   //
    //////////////////////////////////////////////////////////////////////////////
    
    int dist[MAXI];
    int prev[MAXI];
    bool visitado[MAXI];

    for (int i = 0; i < cantidad; i++) {
        dist[i] = INF;
        prev[i] = -1;
        visitado[i] = false;
    }
    dist[origen] = 0;

    for (int iter = 0; iter < cantidad; iter++) {
        // ni hay un nodo no visitado con la menor distanciaa
        int u = -1;
        for (int i = 0; i < cantidad; i++) {
            if (!visitado[i] && dist[i] != INF && (u == -1 || dist[i] < dist[u]))
                u = i;
        }
        if (u == -1) break;       // no quedan nodos alcanzables :o
        visitado[u] = true;

        
        for (int v = 0; v < cantidad; v++) {
            if (ady[u][v] > 0 && !visitado[v] && dist[u] + ady[u][v] < dist[v]) {
                dist[v] = dist[u] + ady[u][v];
                prev[v] = u;
            }
        }
    }

    // Recosnstruir el camino desde origen hasta destino
    int camino[MAXI];
    int largo = 0;
    for (int v = destino; v != -1; v = prev[v]) {
        camino[largo++] = v;
    }

    // Camino optimooooooooooooooooooooooo
    for (int i = largo - 1; i >= 0; i--) {
        cout << nombres[camino[i]];
        if (i > 0) cout << " -> ";
    }
    cout << endl;


    int Dfinal = dist[destino];
    int Rfinal = Pinicial - (Dfinal * C);

    if (Rfinal > 0) {
        cout << "Atenea los guio sabiamente en " << Dfinal
                << " dias. Provisiones restantes: " << Rfinal << endl;
    } else if (Rfinal == 0) {
        cout << "Los hombres llegaron con lo justo. Atenea los guio en "
            << Dfinal << " días a su destino " << endl;
    } else {
        cout << "Los hombres no sobrevivieron a la furia de Poseidon, "
                "lamentablemente todos han perecido en el viaje, "
                "Atenea se encuentra decepcionada" << endl;
    }

    return 0;
}