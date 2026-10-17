#include <iostream>
#include <string>

using namespace std;

const int MAX_ISLANDS = 10;
const int INF = 1000000000;

string islandNames[MAX_ISLANDS];
int islandCount = 0;
int adjacency[MAX_ISLANDS][MAX_ISLANDS];

int islandIndex(const string& name) {
    for (int index = 0; index < islandCount; ++index) {
        if (islandNames[index] == name) {
            return index;
        }
    }

    if (islandCount == MAX_ISLANDS) {
        return -1;
    }

    islandNames[islandCount] = name;
    return islandCount++;
}

int main() {
    int islandTotal;
    int routeTotal;
    int initialProvisions;
    int dailyConsumption;

    if (!(cin >> islandTotal >> routeTotal) || islandTotal < 2 || islandTotal > MAX_ISLANDS ||
        routeTotal < 1 || routeTotal > 20) {
        return 1;
    }

    if (!(cin >> initialProvisions >> dailyConsumption) || initialProvisions < 1 ||
        initialProvisions > 1000 || dailyConsumption < 1 || dailyConsumption > 50) {
        return 1;
    }

    string originName;
    string destinationName;
    if (!(cin >> originName >> destinationName)) {
        return 1;
    }

    for (int row = 0; row < MAX_ISLANDS; ++row) {
        for (int column = 0; column < MAX_ISLANDS; ++column) {
            adjacency[row][column] = 0;
        }
    }

    int origin = islandIndex(originName);
    int destination = islandIndex(destinationName);
    if (origin == -1 || destination == -1) {
        return 1;
    }

    for (int route = 0; route < routeTotal; ++route) {
        string fromName;
        string toName;
        int days;

        if (!(cin >> fromName >> toName >> days) || days < 1 || days > 1000) {
            return 1;
        }

        int from = islandIndex(fromName);
        int to = islandIndex(toName);
        if (from == -1 || to == -1 || islandCount > islandTotal) {
            return 1;
        }

        if (adjacency[from][to] == 0 || days < adjacency[from][to]) {
            adjacency[from][to] = days;
            adjacency[to][from] = days;
        }
    }

    int distance[MAX_ISLANDS];
    int previous[MAX_ISLANDS];
    bool visited[MAX_ISLANDS];

    for (int index = 0; index < islandCount; ++index) {
        distance[index] = INF;
        previous[index] = -1;
        visited[index] = false;
    }
    distance[origin] = 0;

    for (int step = 0; step < islandCount; ++step) {
        int current = -1;

        for (int index = 0; index < islandCount; ++index) {
            if (!visited[index] && distance[index] != INF &&
                (current == -1 || distance[index] < distance[current])) {
                current = index;
            }
        }

        if (current == -1) {
            break;
        }

        visited[current] = true;

        for (int neighbor = 0; neighbor < islandCount; ++neighbor) {
            if (adjacency[current][neighbor] > 0 && !visited[neighbor] &&
                distance[current] + adjacency[current][neighbor] < distance[neighbor]) {
                distance[neighbor] = distance[current] + adjacency[current][neighbor];
                previous[neighbor] = current;
            }
        }
    }

    if (distance[destination] == INF) {
        return 1;
    }

    int path[MAX_ISLANDS];
    int pathLength = 0;
    for (int current = destination; current != -1; current = previous[current]) {
        path[pathLength++] = current;
    }

    for (int index = pathLength - 1; index >= 0; --index) {
        cout << islandNames[path[index]];
        if (index > 0) {
            cout << " -> ";
        }
    }
    cout << '\n';

    int finalDays = distance[destination];
    int remainingProvisions = initialProvisions - finalDays * dailyConsumption;

    if (remainingProvisions > 0) {
        cout << "Atenea los guió sabiamente en " << finalDays
             << " días. Provisiones restantes: " << remainingProvisions << '\n';
    } else if (remainingProvisions == 0) {
        cout << "Los hombres llegaron con lo justo. Atenea los guió en "
             << finalDays << " días a su destino" << '\n';
    } else {
        cout << "Los hombres no sobrevivieron a la furia de Poseidón, lamentablemente "
             << "todos han perecido en el viaje, Atenea se encuentra decepcionada" << '\n';
    }

    return 0;
}
