#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>

struct Alumno {
    char codigo[6];
    char nombre[12];
    char apellidos[21];
    char carrera[16];
};

class FixedRecord {
    std::fstream file;
public:
    std::vector<Alumno> load();

    void add(Alumno record);

    Alumno readRecord(int pos);

    FixedRecord(char *filename);

    ~FixedRecord();
};

void pregunta1();

Alumno createAlumno(std::string codigo_, std::string nombre_, std::string apellidos_, std::string carrera_);