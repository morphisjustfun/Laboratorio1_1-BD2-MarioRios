//
// Created by lordmarcusvane on 2021-05-02.
//

#ifndef LABORATORIO1_1_PREGUNTA3_H
#define LABORATORIO1_1_PREGUNTA3_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

struct Alumno_d {
    std::string Nombre;
    std::string Apellidos;
    std::string Carrera;
    float mensualidad;
};

class VariableRecord {
    std::fstream file;
public:
    VariableRecord(char* name);
    ~VariableRecord();
    std::vector<Alumno_d> load();
    Alumno_d readRecord(int pos);
    void add(Alumno_d record);
};

void pregunta3();

Alumno_d createAlumno(std::string nombre_,std::string apellidos_,std::string carrera_,float mensualidad_);

#endif //LABORATORIO1_1_PREGUNTA3_H
