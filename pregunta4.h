//
// Created by lordmarcusvane on 2021-05-02.
//

#ifndef LABORATORIO1_1_PREGUNTA4_H
#define LABORATORIO1_1_PREGUNTA4_H
#define MAX_COD_SIZE 5
#define MAX_CICLO_SIZE 5
#define MAX_MENSUALIDAD_SIZE 5
#define MAX_OBSERVACIONES_SIZE 5

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

struct Cabecera {
    int cod;
    int ciclo;
    int mens;
    int obs;

};

struct Matricula_m {
    std::string codigo;
    int ciclo;
    float mensualidad;
    std::string observaciones;
};

class CabeceraWithFile {
    std::fstream file;
    std::fstream cabecera_file;
public:
    CabeceraWithFile(char *filename, char* cabecera);
    ~CabeceraWithFile();
    std::vector<Matricula_m> load();
    Matricula_m readRecord(int pos);
    void add(Matricula_m record);
};

void pregunta4();

Matricula_m createMatricula(std::string codigo_, int ciclo_ , float mensualidad_ , std::string obs_);

#endif //LABORATORIO1_1_PREGUNTA4_H
