# memoria_dual

an arduino game that’s more expensive than fun

```mermaid
graph TD
    Start([Inicio])
    Gen[Generar secuencia aleatoria]
    Show[Mostrar secuencia (letras o números)]
    Input[Leer respuesta del jugador]
    Correct{¿Respuesta correcta?}
    Fail[Mostrar "¡Fallaste!"\nNivel alcanzado\nFin del juego]
    Win[Mostrar "¡Bien!"\n+1 Nivel]
    Max{¿Nivel > 20?}
    Reset[Nivel = 1]
    
    Start --> Gen
    Gen --> Show
    Show --> Input
    Input --> Correct

    Correct -- No --> Fail
    Correct -- Sí --> Win
    Win --> Max
    Max -- Sí --> Reset --> Gen
    Max -- No --> Gen
```
