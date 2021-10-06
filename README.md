# Cant Hash Dis

## Funcionamiento
## Ideas
### ~~Stealing AES~~
### Cha Cha
  - Fast 
  - "Easy"
  - Secure
  - (Update) Es la base para BLAKE

## Restricciones
  - [+] el output debe ser >= 25 chars.
  - [+] Debe tener gran difusión.
  - [ ] % de colisionar debe ser complejo *
  - [+] Procesamiento debe ser "rápido"
 

#### Resistencia a Colisiones
Para saber la probabilidad de una colision, nos podemos apoyar en la "paradoja del cumpleaños".
> Cuántas personas serian necesarias dentro de una fiesta para que exista X% de probabilidad
> de que 2 personas tengan el mismo cumpleaños? 
Donde por ej. con X=50% solamente necesitamos 23 personas. ( Revisar libro )

> "The most important consequence of the birthday attack is that the num of messages needed to
> find a collision is roughly equal to the square root of the num of possible output  values"
