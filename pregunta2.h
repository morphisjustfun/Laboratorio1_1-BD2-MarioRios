//
// Created by lordmarcusvane on 2021-05-01.
//

#ifndef LABORATORIO1_1_PREGUNTA2_H
#define LABORATORIO1_1_PREGUNTA2_H

#include <iostream>
#include <fstream>
#include <vector>

#define MAX_CICLO_SIZE 5
#define MAX_MENSUALIDAD_SIZE 9
#define MAX_FREELIST_SIZE 4


struct Alumno_b {
    static int size_word;
    static int header_nextdel;
    char codigo[6];
    char nombre[12];
    char apellidos[21];
    char carrera[16];
    int ciclo;
    float mensualidad;
    int nextdel;
};

class FixedRecord_b {
    std::fstream file;
public:
    FixedRecord_b(char *name);

    ~FixedRecord_b();

    std::vector<Alumno_b> load();

    Alumno_b readRecord(int pos);

    void add(Alumno_b record);

    void delete_record(int pos);

    void update(char *name);
};

void pregunta2();

Alumno_b
createAlumno(std::string codigo_, std::string nombre_, std::string apellidos_, std::string carrera_, int ciclo_,
             float mensualidad_, int nextdel_);

#endif //LABORATORIO1_1_PREGUNTA2_H
