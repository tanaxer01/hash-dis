# hash-dis

## Restricciones
    - [ ] el output debe ser >= 25 chars.
    - [ ] Debe tener gran difusión.
    - [ ] % de colisionar debe ser complejo *
    - [ ] Procesamiento debe ser "rápido"
## Ideas
### Stealing AES
- Para agregar un gran nivel de difusión, ocupar implementación 
  similar a shiftRows & mixColumn.


### My Own
- definir bloques de 256 bits ( 32 bytes ) pq somos AES kool. 
- tener K iteraciones, donde en cada iteración se agrega otro bloque de texto.

### Pendiente 
- Cómo hacer menos determinista la custion.
- Qué hacer para normalizar el input (aka padding)
- Tmb tiene que ser "reproducible" ( lo que eso signifique xd )



