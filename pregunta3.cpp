//
// Created by lordmarcusvane on 2021-05-02.
//

#include "pregunta3.h"

#include <utility>

VariableRecord::VariableRecord(char *name) {
    file.open(name, std::ios::out | std::ios::in);
}

VariableRecord::~VariableRecord() {
    file.close();
}

std::vector<Alumno_d> VariableRecord::load() {
    file.seekg(0, std::ios::beg);
    std::vector<Alumno_d> result;
    std::string templine;

    std::string delimiter = "|";
    std::string token;
    size_t pos;
    int index = 0;
    while (std::getline(file, templine)) {
        Alumno_d record;
        if (index != 0) {
            int sw = 0;
            while ((pos = templine.find(delimiter)) != std::string::npos) {
                token = templine.substr(0, pos);
                templine.erase(0, pos + delimiter.length());
                switch (sw) {
                    case 0: {
                        record.Nombre = token;
                    }
                    case 1: {
                        record.Apellidos = token;
                    }
                    case 2: {
                        record.Carrera = token;
                    }
                }
                sw++;
            }
            record.mensualidad = std::stof(templine);
            result.push_back(record);
        }
        index++;
    }
    return result;
}

Alumno_d VariableRecord::readRecord(int pos) {
    Alumno_d result;
    file.clear();
    file.seekg(0, std::ios::beg);
    std::string templine;
    int index = 0;
    while (std::getline(file, templine)) {
        if (index != 0) {
            if (index - 1 == pos) {
                std::string delimiter = "|";
                std::string token;
                size_t pos_;
                int sw = 0;
                while ((pos_ = templine.find(delimiter)) != std::string::npos) {
                    token = templine.substr(0, pos_);
                    templine.erase(0, pos_ + delimiter.length());
                    switch (sw) {
                        case 0: {
                            result.Nombre = token;
                        }
                        case 1: {
                            result.Apellidos = token;
                        }
                        case 2: {
                            result.Carrera = token;
                        }
                    }
                    sw++;
                }
                result.mensualidad = std::stof(templine);
                return result;
            }
        }
        index++;
    }
    return Alumno_d();
}

void VariableRecord::add(Alumno_d record) {
    file.clear();
    file.seekg(0,std::ios::end);
    file << record.Nombre << "|" << record.Apellidos << "|" << record.Carrera << "|" << record.mensualidad << "\n";
    file.flush();
}

void pregunta3() {
    char *filename = "datos2.txt";
    auto *prueba3 = new VariableRecord(filename);

    // Pruebas

    // Load

    std::cout << "\n" << "Prueba load" << std::endl;
    std::vector<Alumno_d> load_test = prueba3->load();
    std::cout << "\n";
    for (const auto& alumno: load_test){
        std::cout << alumno.Nombre << "  " << alumno.Apellidos << "  " << alumno.Carrera << "  " << alumno.mensualidad << "\n";
    }
    std::cout << "\n" << "Prueba readRecord - cod 1" << "\n" << "\n";
    auto record_test = prueba3->readRecord(1);
    std::cout << record_test.Nombre << "  " << record_test.Apellidos << "  " << record_test.Carrera << "  " << record_test.mensualidad << "\n";
    std::cout << "\n" << "Prueba add" << "\n" << "\n";
    auto d = createAlumno("Mario","Rios","CS",1200.41);
    prueba3->add(d);
    load_test = prueba3->load();
    std::cout << "\n";
    for (const auto& alumno: load_test){
        std::cout << alumno.Nombre << "  " << alumno.Apellidos << "  " << alumno.Carrera << "  " << alumno.mensualidad << "\n";
    }
    delete prueba3;
}

Alumno_d createAlumno(std::string nombre_, std::string apellidos_, std::string carrera_, float mensualidad_) {
    Alumno_d result;
    result.Nombre = std::move(nombre_);
    result.Apellidos = std::move(apellidos_);
    result.mensualidad = mensualidad_;
    result.Carrera = std::move(carrera_);
    return result;
}

