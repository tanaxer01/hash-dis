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
- 4 galoid ops: "Understanding Crypto - Christof Paar"
                https://en.wikipedia.org/wiki/Finite_field_arithmetic#Rijndael's_(AES)_finite_field

### My Own
- definir bloques de 256 bits ( 32 bytes ) pq somos AES kool. 
- tener K iteraciones, donde en cada iteración se agrega otro bloque de texto.

#### Resistencia a Colisiones
Para saber la probabilidad de una colision, nos podemos apoyar en la "paradoja del cumpleaños".
> Cuántas personas serian necesarias dentro de una fiesta para que exista X% de probabilidad
> de que 2 personas tengan el mismo cumpleaños? 
Donde por ej. con X=50% solamente necesitamos 23 personas. ( Revisar libro )


### Pendiente 
- Cómo hacer menos determinista la custion.
- Qué hacer para normalizar el input (aka padding)
- Tmb tiene que ser "reproducible" ( lo que eso signifique xd )

- diff AES128 & AES256 , todo en GF(2^8) ?



