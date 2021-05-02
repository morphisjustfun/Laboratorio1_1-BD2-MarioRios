//
// Created by lordmarcusvane on 2021-05-01.
//


#include "pregunta2.h"
#include <cstring>
#include <sstream>

void pregunta2() {
    std::cout.precision(MAX_MENSUALIDAD_SIZE - 2);
    char *filename = strdup("datos1_b.txt");
    auto prueba2 = new FixedRecord_b(filename);

    // Pruebas

    // Load
    std::cout << "Por comodidad el indexamiento empieza en 0 y los registros no borrados se representan por -2"
              << std::endl;
    std::cout << "Se implementó la estructura LIFO para el FreeList en los métodos add y remove"
              << std::endl;
    std::cout << "\n";
    std::cout << "Prueba load" << std::endl;
    std::cout
            << "Los registros ciclo y mensualidad no se encuentran alineados ya que no son texto y no tienen tamaño predefinido, sino que son valores numéricos"
            << std::endl;
    std::cout << "\n";
    std::vector<Alumno_b> load_test = prueba2->load();
    std::cout << Alumno_b::header_nextdel << std::endl;
    for (auto alumno: load_test) {
        std::cout << alumno.codigo << alumno.nombre << alumno.apellidos << alumno.carrera << alumno.ciclo << "  "
                  << alumno.mensualidad << "  " << alumno.nextdel << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Prueba read record -" << " cod 2" << std::endl;
    auto record_test = prueba2->readRecord(2);
    std::cout<< "\n";
    std::cout << record_test.codigo << record_test.nombre << record_test.apellidos << record_test.carrera
              << record_test.ciclo << "  " << record_test.mensualidad << "  " << record_test.nextdel << std::endl;

    std::cout << "\n";
    std::cout << "Prueba delete record -" << " cod 1" << std::endl;
    std::cout << "\n";
    prueba2->delete_record(1);
    load_test = prueba2->load();
    std::cout << Alumno_b::header_nextdel << std::endl;
    for (auto alumno: load_test) {
        std::cout << alumno.codigo << alumno.nombre << alumno.apellidos << alumno.carrera << alumno.ciclo << "  "
                  << alumno.mensualidad << "  " << alumno.nextdel << std::endl;
    }
    std::cout << "\n";
    std::cout << "Prueba add record" << std::endl;
    std::cout << "\n";
    auto add_test = createAlumno("2019","TestAdd","Rios Gamboa","CS",4,123.12,-2);
    prueba2->add(add_test);
    prueba2->update(filename);
    std::cout << "\n";
    load_test = prueba2->load();
    std::cout << Alumno_b::header_nextdel << std::endl;
    for (auto alumno: load_test) {
        std::cout << alumno.codigo << alumno.nombre << alumno.apellidos << alumno.carrera << alumno.ciclo << "  "
                  << alumno.mensualidad << "  " << alumno.nextdel << std::endl;
    }
//    auto lj = prueba2->readRecord(0);
//    std::cout << lj.nextdel << std::endl;
//    auto alumno_b = createAlumno("0109", "Nel", "Rios", "CS", 5, 210.14, 0);
//    prueba2->add(alumno_b);
//    auto l = prueba2->load();
//    std::cout << l[0].nextdel << std::endl;
// 2 y 5
//    prueba2->delete_record(8);
    delete prueba2;
}

Alumno_b
createAlumno(std::string codigo_, std::string nombre_, std::string apellidos_, std::string carrera_, int ciclo_,
             float mensualidad_, int nextdel_) {
    std::string codigo_t(sizeof(Alumno_b::codigo) - 1, ' ');
    std::string nombre_t(sizeof(Alumno_b::nombre) - 1, ' ');
    std::string apellidos_t(sizeof(Alumno_b::apellidos) - 1, ' ');
    std::string carrera_t(sizeof(Alumno_b::carrera) - 1, ' ');
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
    Alumno_b result{};
    strcpy(result.codigo, codigo_t.c_str());
    strcpy(result.nombre, nombre_t.c_str());
    strcpy(result.apellidos, apellidos_t.c_str());
    strcpy(result.carrera, carrera_t.c_str());
    result.nextdel = nextdel_;
    result.mensualidad = mensualidad_;
    result.ciclo = ciclo_;
    return result;
}

FixedRecord_b::FixedRecord_b(char *name) {
    file.open(name, std::ios::binary | std::ios::out | std::ios::in);
    if (!file) {
        std::cout << "Archivo no encontrado";
        exit(1);
    }
}

FixedRecord_b::~FixedRecord_b() {
    file.close();
}

std::vector<Alumno_b> FixedRecord_b::load() {
    file.clear();
    file.seekg(0, std::ios::beg);
    std::vector<Alumno_b> result;
    int len;
    file.read((char *) &len, sizeof(len));
    char *buffer = new char[len + 1];
    file.seekg(0, std::ios::beg);
    file.read(buffer, len);
    buffer[len] = '\0';
    std::string bufferString = buffer;
    delete[] buffer;
    std::string delimiter = "\n";
    size_t pos;
    std::string token;
    Alumno_b record{};
    std::string format =
            "%5c%11c%20c%15c%" + std::to_string(MAX_CICLO_SIZE - 1) + "c%" + std::to_string(MAX_MENSUALIDAD_SIZE - 1) +
            "c%" + std::to_string(MAX_FREELIST_SIZE - 1) + "c";
    int index = 0;
    while ((pos = bufferString.find(delimiter)) != std::string::npos) {
        if (index == 0) {
            char nextdel[MAX_FREELIST_SIZE];
            token = bufferString.substr(0, pos);
            sscanf(token.c_str(), ("%" + std::to_string(MAX_FREELIST_SIZE - 1) + "c").c_str(), nextdel);
            bufferString.erase(0, pos + delimiter.length());
            Alumno_b::header_nextdel = std::stoi(nextdel);
        } else {
            char ciclo[MAX_CICLO_SIZE];
            char mensualidad[MAX_MENSUALIDAD_SIZE];
            char nextdel[MAX_FREELIST_SIZE];
            token = bufferString.substr(0, pos);
            sscanf(token.c_str(), format.c_str(), record.codigo, record.nombre, record.apellidos, record.carrera, ciclo,
                   mensualidad, nextdel);
            bufferString.erase(0, pos + delimiter.length());
            record.ciclo = std::stoi(ciclo);
            record.mensualidad = std::stof(mensualidad);
            record.nextdel = std::stoi(nextdel);
            result.push_back(record);
        }
        index++;
    }
    return result;
}

Alumno_b FixedRecord_b::readRecord(int pos) {
    file.clear();
    file.seekg((long) ((Alumno_b::size_word) * pos + (MAX_FREELIST_SIZE) * sizeof(char)), std::ios::beg);
    Alumno_b record = Alumno_b();
    std::string line;
    char *buffer = new char[Alumno_b::size_word + 1];
    file.read(buffer, Alumno_b::size_word);
    buffer[Alumno_b::size_word] = '\0';
    std::string bufferString = buffer;
    delete[] buffer;
    char ciclo[MAX_CICLO_SIZE];
    char mensualidad[MAX_MENSUALIDAD_SIZE];
    char nextdel[MAX_FREELIST_SIZE];
    std::string format =
            "%5c%11c%20c%15c%" + std::to_string(MAX_CICLO_SIZE - 1) + "c%" + std::to_string(MAX_MENSUALIDAD_SIZE - 1) +
            "c%" + std::to_string(MAX_FREELIST_SIZE - 1) + "c";
    sscanf(bufferString.c_str(), format.c_str(), record.codigo, record.nombre, record.apellidos, record.carrera, ciclo,
           mensualidad, nextdel);
    record.ciclo = std::stoi(ciclo);
    record.mensualidad = std::stof(mensualidad);
    record.nextdel = std::stoi(nextdel);
    return record;
}

void FixedRecord_b::add(Alumno_b record) {
    load();
    file.clear();
    std::string ciclo_t(MAX_CICLO_SIZE - 1, ' ');
    std::string mensualidad_t(MAX_MENSUALIDAD_SIZE - 1, ' ');
    std::string nextdel_t(MAX_FREELIST_SIZE - 1, ' ');
    std::string ciclo_n = std::to_string(record.ciclo);
    std::string mensualidad_n = std::to_string(record.mensualidad);
    std::string nextdel_n = std::to_string(record.nextdel);
    int index = 0;
    for (const char &element: ciclo_n) {
        ciclo_t[index] = element;
        index++;
    }
    index = 0;
    for (const char &element: mensualidad_n) {
        mensualidad_t[index] = element;
        index++;
    }
    index = 0;
    for (const char &element: nextdel_n) {
        nextdel_t[index] = element;
        index++;
    }
    if (Alumno_b::header_nextdel == -1) {
        std::stringstream target;
        target << record.codigo << record.nombre << record.apellidos << record.carrera << ciclo_t << mensualidad_t
               << nextdel_t << "\n";
        std::string target_string = target.str();
        int len = (int) target_string.size();
        file.seekg(0, std::ios::end);
        file.write(target_string.c_str(), len);
        file.flush();
    } else {
        std::stringstream target;
        target << "\n" << record.codigo << record.nombre << record.apellidos << record.carrera << ciclo_t
               << mensualidad_t
               << nextdel_t;
        std::string target_string = target.str();
        int len = (int) target_string.size();
        int temp = Alumno_b::header_nextdel;
        file.seekg((long) ((Alumno_b::size_word) * temp + (MAX_FREELIST_SIZE) * sizeof(char)), std::ios::beg);
        char *bufferold = new char[Alumno_b::size_word + 1];
        file.read(bufferold, Alumno_b::size_word);
        bufferold[Alumno_b::size_word] = '\0';
        std::string bufferString = bufferold;
        file.seekg(0, std::ios::beg);
        std::fstream tempfile;
        tempfile.open("datos1_b_temp.txt", std::ios::out);
        tempfile.close();
        std::fstream tempfile_m;
        tempfile_m.open("datos1_b_temp.txt", std::ios::out | std::ios::in);
        std::string templine;
        std::string target_next = bufferString.substr(bufferString.size() - MAX_FREELIST_SIZE, bufferString.size());
        int new_header_next = std::stoi(target_next);
        int index_a = 0;
        while (std::getline(file, templine)) {
            if (index_a != 0) {
                tempfile_m << templine << std::endl;
            }
            index_a++;
        }
        tempfile_m.seekg(Alumno_b::size_word * temp - 1, std::ios::beg);
        tempfile_m.write(target_string.c_str(), len);
        tempfile_m.flush();
        std::string nextdel_r(MAX_FREELIST_SIZE - 1, ' ');
        std::string nextdel_re = std::to_string(new_header_next);
        int index_ = 0;
        for (const char &element: nextdel_re) {
            nextdel_r[index_] = element;
            index_++;
        }
        std::fstream tempfile_f;
        tempfile_f.open("datos1_b_temp_f.txt", std::ios::out);
        tempfile_f << nextdel_r << std::endl;
        tempfile_m.seekg(0, std::ios::beg);
        while (std::getline(tempfile_m, templine)) {
            tempfile_f << templine << std::endl;
        }
        tempfile_f.close();
        tempfile_m.close();
        remove("datos1_b_temp.txt");
        remove("datos1_b.txt");
        rename("datos1_b_temp_f.txt", "datos1_b.txt");
    }
}


void FixedRecord_b::delete_record(int pos) {
    load();
    file.clear();
    file.seekg((long) ((Alumno_b::size_word) * pos + (MAX_FREELIST_SIZE) * sizeof(char)), std::ios::beg);
    char *buffer = new char[Alumno_b::size_word + 1];
    file.read(buffer, Alumno_b::size_word);
    buffer[Alumno_b::size_word] = '\0';
    std::string replace_nextdel = std::to_string(Alumno_b::header_nextdel);
    int index = 0;
    buffer[Alumno_b::size_word - 2] = ' ';
    buffer[Alumno_b::size_word - 3] = ' ';
    buffer[Alumno_b::size_word - 4] = ' ';
    for (const char &element: replace_nextdel) {
        buffer[Alumno_b::size_word - MAX_FREELIST_SIZE + index] = element;
        index++;
    }
    file.seekg((long) ((Alumno_b::size_word) * pos + (MAX_FREELIST_SIZE) * sizeof(char)), std::ios::beg);
    file.write(buffer, Alumno_b::size_word);
    file.flush();
    file.clear();
    file.seekg(0, std::ios::beg);
    char *n_buffer = new char[MAX_FREELIST_SIZE * sizeof(char) + 1];
    file.read(n_buffer, MAX_FREELIST_SIZE * sizeof(char));
    n_buffer[MAX_FREELIST_SIZE * sizeof(char)] = '\0';
    std::string replace_nextdel_m = std::to_string(pos);
    index = 0;
    n_buffer[0] = ' ';
    n_buffer[1] = ' ';
    n_buffer[2] = ' ';
    for (const char &element: replace_nextdel_m) {
        n_buffer[index] = element;
        index++;
    }
    file.seekg(0, std::ios::beg);
    file.write(n_buffer, MAX_FREELIST_SIZE * sizeof(char));
    file.flush();
    delete[] buffer;
    delete[] n_buffer;
}

void FixedRecord_b::update(char *name) {
    file.close();
    file.open(name, std::ios::binary | std::ios::out | std::ios::in);
}

int Alumno_b::header_nextdel = -1;

int Alumno_b::size_word = 67;
