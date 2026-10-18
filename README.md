# La Odisea y el Camino de Atenea

Después de la caída de Troya, Odiseo y sus guerreros quieren regresar a Ítaca. Poseidón convierte el viaje por el mar Egeo en una travesía difícil, con muchas rutas posibles entre las islas.

Atenea guía a Odiseo para encontrar el camino marítimo con menor cantidad de días. La nave parte con provisiones iniciales y consume una cantidad fija cada día, así que el programa también determina si la tripulación llega con provisiones, llega justo o no sobrevive al viaje.

## Compilar y ejecutar

```bash
g++ main.cpp
./a.out < entrada.txt
```

## Entrada

```text
N M
P C
origen destino
isla1 isla2 dias
...
```

- `N`: número de islas, entre 2 y 10.
- `M`: número de rutas marítimas, entre 1 y 20.
- `P`: provisiones iniciales, entre 1 y 1000.
- `C`: consumo diario de provisiones, entre 1 y 50.
- Cada una de las siguientes `M` líneas contiene dos islas y los días de navegación entre ellas.

Las rutas son bidireccionales. Se garantiza que existe al menos un camino entre el origen y el destino.

## Salida

El programa imprime el camino de menor duración, separando las islas con `->`, y luego informa el resultado de las provisiones durante el viaje.
