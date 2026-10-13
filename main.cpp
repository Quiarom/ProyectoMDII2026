#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Viaje {
  string origen;
  string destino;
  int dias;
  int suministros;
};

int main() {
  vector<Viaje> viajes;

  Viaje nueva = {"A", "B", 4, 100};
  viajes.push_back(nueva);

  for (Viaje viaje : viajes) {
    cout << viajes.size() << endl;
  }
}
