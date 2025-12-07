#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

// Clase base abstracta para materiales de biblioteca
class MaterialBiblioteca {
protected:
    string titulo;
    int id;
    bool prestado;
    static int contadorID; // Contador estático para generar IDs únicos

public:
    MaterialBiblioteca(string t) : titulo(t), prestado(false) {
        id = ++contadorID; // Asigna ID automáticamente al crear material
    }

    virtual ~MaterialBiblioteca() {}

    // Métodos virtuales puros para polimorfismo
    virtual void mostrarInfo() const = 0;
    virtual string getTipo() const = 0;

    void prestar() {
        if (!prestado) {
            prestado = true;
            cout << "Material prestado exitosamente." << endl;
        } else {
            cout << "Este material ya esta prestado." << endl;
        }
    }

    void devolver() {
        if (prestado) {
            prestado = false;
            cout << "Material devuelto exitosamente." << endl;
        } else {
            cout << "Este material no estaba prestado." << endl;
        }
    }

    string getTitulo() const { return titulo; }
    int getID() const { return id; }
    bool estaPrestado() const { return prestado; }
};

// Inicialización del contador estático
int MaterialBiblioteca::contadorID = 0;

// Clases derivadas: Libro, Revista y DVD
class Libro : public MaterialBiblioteca {
private:
    string autor;
    string isbn;
    int numPaginas;
    string genero;

public:
    Libro(string t, string a, string i, int p, string g)
        : MaterialBiblioteca(t), autor(a), isbn(i), numPaginas(p), genero(g) {}

    void mostrarInfo() const override {
        cout << "\nLIBRO" << endl;
        cout << "ID: " << id << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Paginas: " << numPaginas << endl;
        cout << "Genero: " << genero << endl;
        cout << "Estado: " << (prestado ? "PRESTADO" : "DISPONIBLE") << endl;
    }

    string getTipo() const override { return "Libro"; }
    string getAutor() const { return autor; }
    string getISBN() const { return isbn; }
    int getNumPaginas() const { return numPaginas; }
    string getGenero() const { return genero; }
};

class Revista : public MaterialBiblioteca {
private:
    string autor;
    int numPaginas;
    string genero;

public:
    Revista(string t, string a, int p, string g)
        : MaterialBiblioteca(t), autor(a), numPaginas(p), genero(g) {}

    void mostrarInfo() const override {
        cout << "\nREVISTA" << endl;
        cout << "ID: " << id << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "Paginas: " << numPaginas << endl;
        cout << "Genero: " << genero << endl;
        cout << "Estado: " << (prestado ? "PRESTADO" : "DISPONIBLE") << endl;
    }

    string getTipo() const override { return "Revista"; }
    string getAutor() const { return autor; }
    int getNumPaginas() const { return numPaginas; }
    string getGenero() const { return genero; }
};

class DVD : public MaterialBiblioteca {
private:
    string director;
    int duracion;
    string genero;

public:
    DVD(string t, string d, int dur, string g)
        : MaterialBiblioteca(t), director(d), duracion(dur), genero(g) {}

    void mostrarInfo() const override {
        cout << "\nDVD" << endl;
        cout << "ID: " << id << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Director: " << director << endl;
        cout << "Duracion: " << duracion << " minutos" << endl;
        cout << "Genero: " << genero << endl;
        cout << "Estado: " << (prestado ? "PRESTADO" : "DISPONIBLE") << endl;
    }

    string getTipo() const override { return "DVD"; }
    string getDirector() const { return director; }
    int getDuracion() const { return duracion; }
    string getGenero() const { return genero; }
};

// Clase que gestiona la colección de materiales (composición)
class Biblioteca {
private:
    string nombre;
    vector<unique_ptr<MaterialBiblioteca>> catalogo; // Composición: la biblioteca posee los materiales

public:
    Biblioteca(string n) : nombre(n) {
        cout << "\nBiblioteca " << nombre << " creada" << endl;
    }

    // Destructor libera automáticamente memoria con unique_ptr
    ~Biblioteca() {
        cout << "\nBiblioteca " << nombre << " cerrada" << endl;
        cout << "Liberando " << catalogo.size() << " materiales del catalogo" << endl;
    }

    void agregarLibro(string titulo, string autor, string isbn, int paginas, string genero) {
        catalogo.push_back(make_unique<Libro>(titulo, autor, isbn, paginas, genero));
        cout << "Libro '" << titulo << "' agregado al catalogo." << endl;
    }

    void agregarRevista(string titulo, string autor, int paginas, string genero) {
        catalogo.push_back(make_unique<Revista>(titulo, autor, paginas, genero));
        cout << "Revista '" << titulo << "' agregada al catalogo." << endl;
    }

    void agregarDVD(string titulo, string director, int duracion, string genero) {
        catalogo.push_back(make_unique<DVD>(titulo, director, duracion, genero));
        cout << "DVD '" << titulo << "' agregado al catalogo." << endl;
    }

    void mostrarCatalogo() const {
        cout << "\nCATALOGO DE " << nombre << endl;
        cout << "Total de materiales: " << catalogo.size() << endl;
        
        // Recorre e imprime información de cada material usando polimorfismo
        for (const auto& material : catalogo) {
            material->mostrarInfo();
        }
    }

    // Busca un material por su ID y retorna un puntero al mismo
    MaterialBiblioteca* buscarPorID(int id) {
        for (auto& material : catalogo) {
            if (material->getID() == id) {
                return material.get();
            }
        }
        return nullptr;
    }

    void prestarMaterial(int id) {
        MaterialBiblioteca* material = buscarPorID(id);
        if (material) {
            cout << "\nPrestando: " << material->getTitulo() << endl;
            material->prestar();
        } else {
            cout << "\nMaterial con ID " << id << " no encontrado." << endl;
        }
    }

    void devolverMaterial(int id) {
        MaterialBiblioteca* material = buscarPorID(id);
        if (material) {
            cout << "\nDevolviendo: " << material->getTitulo() << endl;
            material->devolver();
        } else {
            cout << "\nMaterial con ID " << id << " no encontrado." << endl;
        }
    }

    // Muestra resumen con estadísticas de disponibilidad
    void mostrarResumen() const {
        cout << "\nRESUMEN " << nombre << endl;
        
        int disponibles = 0, prestados = 0;
        for (const auto& material : catalogo) {
            cout << "ID " << material->getID() << ": " 
                 << material->getTipo() << " - " << material->getTitulo() << " - "
                 << (material->estaPrestado() ? "PRESTADO" : "DISPONIBLE") << endl;
            
            if (material->estaPrestado()) prestados++;
            else disponibles++;
        }
        
        cout << "\nEstadisticas:" << endl;
        cout << "Materiales disponibles: " << disponibles << endl;
        cout << "Materiales prestados: " << prestados << endl;
        cout << "Total: " << catalogo.size() << endl;
    }

    string getNombre() const { return nombre; }
};

int main() {
    cout << "SISTEMA DE GESTION DE BIBLIOTECA" << endl;
    cout << "Con COMPOSICION de objetos" << endl;

    Biblioteca miBiblioteca("Biblioteca Central");

    // Agregar materiales de diferentes tipos
    cout << "\nAGREGANDO MATERIALES" << endl;
    miBiblioteca.agregarLibro("Cien Anios de Soledad", "Gabriel Garcia Marquez", 
                               "978-0307474728", 417, "Realismo Magico");
    miBiblioteca.agregarLibro("1984", "George Orwell", 
                               "978-0451524935", 328, "Distopia");
    miBiblioteca.agregarRevista("National Geographic", "Varios Autores", 
                                 120, "Ciencia");
    miBiblioteca.agregarDVD("El Laberinto del Fauno", "Guillermo del Toro", 
                             118, "Fantasia");

    miBiblioteca.mostrarCatalogo();

    cout << "\nOPERACIONES DE PRESTAMO" << endl;
    miBiblioteca.prestarMaterial(1);
    miBiblioteca.prestarMaterial(3);
    miBiblioteca.prestarMaterial(1); // Intento de prestar material ya prestado

    miBiblioteca.mostrarResumen();

    cout << "\nOPERACIONES DE DEVOLUCION" << endl;
    miBiblioteca.devolverMaterial(1);

    miBiblioteca.mostrarResumen();

    cout << "\nFIN DEL PROGRAMA" << endl;

    return 0;
}