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
        string claseAUsar = clases.at(i);
        string atributos_por_linea = "";
        stringstream tokensAtributos(claseAUsar);
        while (getline(tokensAtributos, atributos_por_linea, ' '))
        {
            atributos.push_back(atributos_por_linea);
        }
        for (int j = 0; j < atributos.size(); j++)
        {
            string atributoAUsar = atributos.at(j);
            string atributos_individuales = "";
            stringstream separarAtributoEnEspecifico(atributoAUsar);
            while (getline(separarAtributoEnEspecifico, atributos_individuales, ':'))
            {
                _claseIndividual.push_back(atributos_individuales);
            }
        }
        for (int k = 0; k < _claseIndividual.size(); k++)
        {
            cout << _claseIndividual.at(k) << "--";
        }
    }

    read.close();
}