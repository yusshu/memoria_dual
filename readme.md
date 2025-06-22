# memoria_dual

an arduino game that’s more expensive than fun

```flow
st=>start: Inicio
gen=>operation: generarSecuencia
most=>operation: mostrarSecuencia
res=>condition: ¿Respuesta correcta?
fail=>operation: Mostrar "¡Fallaste!"
bien=>operation: Mostrar "¡Bien!"
inc=>operation: Incrementar nivel
end=>end: Fin del juego

st->gen->most->res
res(no)->fail->end
res(yes)->bien->inc->gen
```