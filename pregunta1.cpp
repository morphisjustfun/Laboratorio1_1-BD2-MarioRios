#include "pregunta1.h"

void pregunta1() {
    char *filename = strdup("datos1.txt");
    auto* prueba1 = new FixedRecord(filename);

    // Pruebas

    // Load
    std::cout << "Prueba load" << std::endl;
    std::vector<Alumno> load_test = prueba1->load();
    for (auto alumno: load_test){
        std::cout << alumno.codigo << alumno.nombre << alumno.apellidos << alumno.carrera << std::endl;
    }
    // Read record
    std::cout << std::endl;
    std::cout << "Prueba read record -" << " cod 2" << std::endl;
    auto record_test = prueba1->readRecord(2);
    std::cout << record_test.codigo << record_test.nombre << record_test.apellidos << record_test.carrera << std::endl;
    std::cout << std::endl;
    std::cout << "Prueba add record -" << std::endl;
    Alumno add_test = createAlumno("2021", "Mario","Rios Gamboa", "CS");
    prueba1->add(add_test);
    std::cout << "Verificando" << std::endl;
    load_test = prueba1->load();
    for (auto alumno: load_test){
        std::cout << alumno.codigo << alumno.nombre << alumno.apellidos << alumno.carrera << std::endl;
    }
    delete prueba1;
}

Alumno createAlumno(std::string codigo_, std::string nombre_, std::string apellidos_, std::string carrera_) {
    std::string codigo_t(sizeof(Alumno::codigo) - 1, ' ');
    std::string nombre_t(sizeof(Alumno::nombre) - 1, ' ');
    std::string apellidos_t(sizeof(Alumno::apellidos) - 1, ' ');
    std::string carrera_t(sizeof(Alumno::carrera) - 1, ' ');
    int index = 0;
    for (const char &element: codigo_) {
        codigo_t[index] = element;
        index++;
    }
    index = 0;
    for (const char &element: nombre_) {
        nombre_t[index] = element;
        index++;
    }
    index = 0;
    for (const char &element: apellidos_) {
        apellidos_t[index] = element;
        index++;
    }
    index = 0;
    for (const char &element: carrera_) {
        carrera_t[index] = element;
        index++;
    }
    Alumno result{};
    strcpy(result.codigo, codigo_t.c_str());
    strcpy(result.nombre, nombre_t.c_str());
    strcpy(result.apellidos, apellidos_t.c_str());
    strcpy(result.carrera, carrera_t.c_str());
    return result;
}

FixedRecord::~FixedRecord() {
    file.close();
}

FixedRecord::FixedRecord(char *name) {
    file.open(name, std::ios::in | std::ios::out);
    if (!file) {
        std::cout << "Archivo no encontrado";
        exit(1);
    }
}

std::vector<Alumno> FixedRecord::load() {
    file.clear();
    file.seekg(0, std::ios::beg);
    std::vector<Alumno> result = {};
    Alumno record = Alumno();
    std::string line;
    while (std::getline(file, line)) {
        sscanf(line.c_str(), "%5c%11c%20c%15c", record.codigo, record.nombre, record.apellidos, record.carrera);
        result.push_back(record);
    }
    return result;
}

void FixedRecord::add(Alumno record) {
    file.clear();
    file.seekg(0, std::ios::end);
    file << record.codigo << record.nombre << record.apellidos << record.carrera << "\n";
    file.flush();
}

Alumno FixedRecord::readRecord(int pos) {
    file.clear();
    file.seekg(0,std::ios::beg);
    Alumno result = Alumno();
    std::string line;
    file.seekg((long) (sizeof(Alumno) - 2) * pos);
    std::getline(file, line);
    sscanf(line.c_str(), "%5c%11c%20c%15c", result.codigo, result.nombre, result.apellidos, result.carrera);
    file.clear();
    file.seekg(0, std::ios::beg);
    return result;
}

