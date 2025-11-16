#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Clase para los libros (eventualmente mas material)
class MaterialBiblioteca {
protected:
    string titulo;
    int id;
    bool prestado;
    static int contadorID;

public:

    MaterialBiblioteca(string t) : titulo(t), prestado(false) {
        id = ++contadorID;
    }


    virtual ~MaterialBiblioteca() {}

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

int MaterialBiblioteca::contadorID = 0;

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

    string getTipo() const override {
        return "Libro";
    }

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
        cout << "\nRevista" << endl;
        cout << "ID: " << id << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "Paginas: " << numPaginas << endl;
        cout << "Genero: " << genero << endl;
        cout << "Estado: " << (prestado ? "PRESTADO" : "DISPONIBLE") << endl;
    }

    string getTipo() const override {
        return "Revista";
    }

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
    DVD(string t, string a, int p, string g)
        : MaterialBiblioteca(t), director(a), duracion(p), genero(g) {}

    void mostrarInfo() const override {
        cout << "\nDVD" << endl;
        cout << "ID: " << id << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Director: " << director << endl;
        cout << "Duracion: " << duracion << endl;
        cout << "Genero: " << genero << endl;
        cout << "Estado: " << (prestado ? "PRESTADO" : "DISPONIBLE") << endl;
    }

    string getTipo() const override {
        return "DVD";
    }

    string getDirector() const { return director; }
    int getDuracion() const { return duracion; }
    string getGenero() const { return genero; }
};

int main() {
    cout << "BIBLIOTECA DIGITAL" << endl;

    Libro libro1("Cien Anios de Soledad", "Gabriel Garcia Marquez", 
                 "978-0307474728", 417, "Realismo Magico");

    Revista revista1("Algun nombre", "Yo mero", 15, "PlayBoy"); 

    DVD DVD1("Algun nombre", "Yo mero", 120, "Terror"); 

    vector<MaterialBiblioteca*> catalogo;
    catalogo.push_back(&libro1);
    catalogo.push_back(&revista1);
    catalogo.push_back(&DVD1);

    cout << "CATALOGO\n";
    for (auto material : catalogo) {
        material->mostrarInfo();
    }

    cout << "\nPRESTAMO\n";
    
    cout << "\nIntentando prestar el primer libro:" << endl;
    libro1.prestar();
    
    cout << "\nVerificando estado del libro:" << endl;
    libro1.mostrarInfo();
    
    cout << "\nIntentando prestar el libro nuevamente:" << endl;
    libro1.prestar();
    
    cout << "\nDevolviendo el libro:" << endl;
    libro1.devolver();

    cout << "\nINFORMACION\n";
    cout << "\nMateriales en el catalogo:" << endl;
    for (auto material : catalogo) {
        cout << "- " << material->getTipo() << ": '" 
             << material->getTitulo() << "' (ID: " 
             << material->getID() << ") - " 
             << (material->estaPrestado() ? "PRESTADO" : "DISPONIBLE") 
             << endl;
    }

    cout << "\nEstado actualizado del catalogo:" << endl;
    for (auto material : catalogo) {
        cout << "- " << material->getTitulo() 
             << ": " << (material->estaPrestado() ? "PRESTADO" : "DISPONIBLE") 
             << endl;
    }

    return 0;
}