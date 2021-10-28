# Cant Hash Dis

## Usage
	
	Modo de uso chachash.c:
		[NO FLAGS] => varios strings a hashear ( separados por ' ')
		-f [FILE] hashear valores de un archivo
		

# CHACHA HASH V/S OTHER KNOWN HASH FUNCTIONS 
Chachash has a output length of 32 hex nums (64 chars).
| Algorithm | Entropy [bits] |
|-----------|----------------|
| MD5       | 128            |
| SHA1      | 160            |
| SHA256    | 256            |
| CHACHASH  | 256            |

# SPEED TESTS
For this tests we used the first N words from *rockyou.txt*
### 1 HASH
| Algoritmo | Tiempo [s] |
|-----------|------------|
| MD5       | 0.002      |
| SHA1      | 0.002      |
| SHA256    | 0.003      |
| CHACHASH  | 0.002      |
## 10 HASHES
| Algoritmo | Tiempo [s] |
|-----------|------------|
| MD5       | 0.002      |
| SHA1      | 0.002      |
| SHA256    | 0.003      |
| CHACHASH  | 0.003      |
## 20 HASHES
| Algoritmo | Tiempo [s] |
|-----------|------------|
| MD5       | 0.002      |
| SHA1      | 0.002      |
| SHA256    | 0.003      |
| CHACHASH  | 0.003      |
## 50 HASHES
| Algoritmo | Tiempo [s] |
|-----------|------------|
| MD5       | 0.002      |
| SHA1      | 0.002      |
| SHA256    | 0.003      |
| CHACHASH  | 0.004      |
## Análisis 
Aun que *CHACHASH* muestra tiempos mayores a SHA1 y MD5 debemos tener en cuenta que la base ocupada es mayor, al igual que SHA256. Por lo tanto
podemos ver que este algoritmo presenta un rendimiento bastante bueno para el nivel de robustes que presenta en un primer análisis. Aparte *CHACHASH*
tiene la posibilidad de permitir un salt (WIP) por lo que resultaria un producto interesante (asumiendo que no demostrara terribles fallos en un
análisis más extenso).

Teniendo lo anterior en cuenta, este algoritmo podria ser ocupado para corroborar la integridad de documentos. Este no seria ideal para ser utilizado
para almacenar contraseñas ya que su rendimiento le jugaria en contra al igual que a varios algoritmos de hash, es por eso que se han desarrollado otros
productos como Argon2 o Blowfish que son más especializados para estos casos.

