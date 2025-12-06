# A01715498-Pensamiento-Computacional-Orientado-a-Objetos
El objetivo de este proyecto es simular la gestión de un inventario básico de una biblioteca digital. El problema a resolver es cómo organizar y manejar la información de diferentes tipos de materiales que pueden ser prestados a los usuarios.
El programa estará diseñado para realizar las siguientes tareas principales:
Creación de Objetos: Crear diferentes objetos que representen cada tipo de material (un Libro, una revista, etc...), inicializándolos con sus respectivos atributos (título, autor, ISBN, etc...).
Consulta de Detalles: Permitir consultar los detalles específicos de cada objeto, como el titulo, el autor, o si esta disponible para ser prestado.
Gestión de Préstamo (Simulada): Simular las acciones que se realizan con el material, como marcar un ítem como prestado, devuelto o no prestado.
El programa corre para Windows 11 con el archivo .exe

Ejecucion:

#Crear .exe/.o
g++ biblioteca.cpp -o biblioteca.exe (crear .exe) (Para Windows)
g++ biblioteca.cpp -o biblioteca.o (crear.o) (Linux/Mac)

#Correr programa
.\biblioteca.exe (Windows)
./biblioteca.o (Linux/Mac)

Resultado

En la terminal saltra primero el catalogo seguido de las pruebas de prestamo, devolucion y muestra de informacion.
