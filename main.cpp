#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
    string directorioArchivo = "./";
    directorioArchivo += argv[1];
    ifstream read;
    read.open(directorioArchivo, ios::in);
    vector<string> clases;
    vector<string> atributos;
    vector<string> _claseIndividual;
    vector<string> _atributoIndividual;
    vector<string> separacionTipoDeAtributo;
    while (!read.eof())
    {
        string clase;
        getline(read, clase);
        stringstream tokens(clase);
        string separacion;
        while (getline(tokens, separacion, ']'))
        {
            clases.push_back(separacion);
        }
    }
    for (int i = 0; i < clases.size(); i++)
    {
        string claseAusar = clases.at(i);
        string lista_de_atributos;
        stringstream _atributos(claseAusar);
        while (getline(_atributos, lista_de_atributos, ' '))
        {
            lista_de_atributos = lista_de_atributos.substr(1);
            _claseIndividual.push_back(lista_de_atributos);
        }
    }
    for (int i = 0; i < clases.size(); i++)
    {
        string claseAUsar = clases.at(i);
        stringstream streamsClases(claseAUsar);
        string lineasDeclase;
        while (getline(streamsClases, lineasDeclase, ' '))
        {
            atributos.push_back(lineasDeclase);
        }
    }
    for (size_t i = 0; i < atributos.size(); i++)
    {
        int contador = 0;
        string atributosAusar = atributos.at(i);
        stringstream streamAtributoIndividual(atributosAusar);
        string _atributoPorLinea;
        while (getline(streamAtributoIndividual, _atributoPorLinea, ':'))
        {
            if (contador % 2 == 1)
            {
                _atributoIndividual.push_back(_atributoPorLinea);
            }
            contador++;
        }
    }
    string nombreDeClase = _atributoIndividual.at(0);
    _atributoIndividual.erase(_atributoIndividual.begin());
    for (int i = 0; i < _atributoIndividual.size(); i++)
    {
        string separadorDeAtributoYtipo = _atributoIndividual.at(i);
        stringstream streamDeSeparador(separadorDeAtributoYtipo);
        string auxiliar;
        while (getline(streamDeSeparador, auxiliar, '|'))
        {
            separacionTipoDeAtributo.push_back(auxiliar);
        }
    }
    ofstream archivoH;
    archivoH.open(nombreDeClase + ".h");
    string encabezado;
    char aux;
    for (int i = 0; i < nombreDeClase.length(); i++)
    {
        encabezado += toupper(nombreDeClase[i]);
    }
    archivoH << "#ifndef " << encabezado << "_H" << endl;
    archivoH << "#define " << encabezado << "_H" << endl;
    archivoH << "#include <iostream>" << endl;
    archivoH << "using namespace std;" << endl;
    archivoH << "class " << nombreDeClase << "{" << endl;
    archivoH << "private: \n";
    for (int i = 0; i < separacionTipoDeAtributo.size(); i++)
    {
        if (i != 0)
        {
            if (i % 2 == 0)
            {
                archivoH << ";\n";
            }
        }
        archivoH << separacionTipoDeAtributo.at(i) << " ";
        if (i + 1 == separacionTipoDeAtributo.size())
        {
            archivoH << ";\n";
        }
    }
    archivoH << "public: \n";
    archivoH << "   " << nombreDeClase << "(){};\n";
    archivoH << "   " << nombreDeClase << '(';
    for (int i = 0; i < separacionTipoDeAtributo.size(); i++)
    {
        if (i != 0)
        {
            if (i + 1 == separacionTipoDeAtributo.size())
            {
                archivoH << "_" << separacionTipoDeAtributo.at(i) << ")\n{";
            }
            else if (i % 2 != 0)
            {
                archivoH << "_" << separacionTipoDeAtributo.at(i) << ",";
            }
            else if (i % 2 == 0)
            {
                archivoH << separacionTipoDeAtributo.at(i) << " ";
            }
        }
        else
        {
            archivoH << separacionTipoDeAtributo.at(i) << " ";
        }
    }

    for (int i = 0; i < separacionTipoDeAtributo.size(); i++)
    {
        if (i != 0)
        {
            if (i % 2 != 0)
            {
                archivoH << "       this->" << separacionTipoDeAtributo.at(i) << "=_" << separacionTipoDeAtributo.at(i) << ";\n";
            }
        }
    }
    archivoH << "}\n";
    for (int i = 0; i < separacionTipoDeAtributo.size(); i++)
    {
        if (i % 2 == 0)
        {
            archivoH << "   void set_" << separacionTipoDeAtributo.at(i + 1) << "(" << separacionTipoDeAtributo.at(i) << ");\n";
        }
    }
    for (int i = 0; i < separacionTipoDeAtributo.size(); i++)
    {
        if (i % 2 == 0)
        {
            archivoH << "   " << separacionTipoDeAtributo.at(i) << " get_" << separacionTipoDeAtributo.at(i + 1) << "();\n";
        }
    }
    archivoH << "};\n#endif";
    read.close();
}