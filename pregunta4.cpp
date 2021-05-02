//
// Created by lordmarcusvane on 2021-05-02.
//

#include "pregunta4.h"

#include <utility>
#include <sstream>

CabeceraWithFile::CabeceraWithFile(char *filename, char *cabecera) {
    file.open(filename, std::ios::out | std::ios::in | std::ios::binary);
    if (!file) {
        std::cout << "No archivo" << std::endl;
        exit(1);
    }
    cabecera_file.open(cabecera, std::ios::out | std::ios::in);
    if (!cabecera) {
        std::cout << "No archivo" << std::endl;
        exit(1);
    }
}

CabeceraWithFile::~CabeceraWithFile() {
    file.close();
    cabecera_file.close();
}

std::vector<Matricula_m> CabeceraWithFile::load() {
    file.clear();
    cabecera_file.clear();
    file.seekg(0, std::ios::beg);
    cabecera_file.seekg(0, std::ios::beg);
    std::string templine;
    std::vector<Cabecera> cabeceras;
    std::string format_cabecera =
            "%" + std::to_string(MAX_COD_SIZE - 1) + "c%" + std::to_string(MAX_CICLO_SIZE - 1) + "c%" +
            std::to_string(MAX_MENSUALIDAD_SIZE - 1) + "c%" + std::to_string(MAX_OBSERVACIONES_SIZE - 1) + "c";
    while (std::getline(cabecera_file, templine)) {
        char cod_char[MAX_COD_SIZE];
        char ciclo_char[MAX_CICLO_SIZE];
        char mens_char[MAX_MENSUALIDAD_SIZE];
        char obs_char[MAX_OBSERVACIONES_SIZE];
        sscanf(templine.c_str(), format_cabecera.c_str(), cod_char, ciclo_char, mens_char, obs_char);
        cod_char[MAX_COD_SIZE - 1] = '\0';
        ciclo_char[MAX_CICLO_SIZE - 1] = '\0';
        mens_char[MAX_MENSUALIDAD_SIZE - 1] = '\0';
        obs_char[MAX_OBSERVACIONES_SIZE - 1] = '\0';
        Cabecera temp{};
        temp.cod = std::stoi(cod_char);
        temp.ciclo = std::stoi(ciclo_char);
        temp.mens = std::stoi(mens_char);
        temp.obs = std::stoi(obs_char);
        cabeceras.push_back(temp);
    }
    std::vector<Matricula_m> matriculas;
    int progress = 0;
    for (Cabecera &cab : cabeceras) {
        Matricula_m te;
        file.seekg(progress, std::ios::beg);
        char *buffer_cod = new char[cab.cod + 1];
        file.read(buffer_cod, cab.cod);
        buffer_cod[cab.cod] = '\0';
        char *buffer_ciclo = new char[cab.ciclo + 1];
        file.read(buffer_ciclo, cab.ciclo);
        buffer_ciclo[cab.ciclo] = '\0';
        char *buffer_mensualidad = new char[cab.mens + 1];
        file.read(buffer_mensualidad, cab.mens);
        buffer_mensualidad[cab.mens] = '\0';
        char *buffer_obs = new char[cab.obs + 1];
        file.read(buffer_obs, cab.obs);
        buffer_obs[cab.obs] = '\0';
        te.ciclo = std::stoi(buffer_ciclo);
        te.mensualidad = std::stof(buffer_mensualidad);
        te.observaciones = buffer_obs;
        te.codigo = buffer_cod;
        matriculas.push_back(te);
        progress = progress + cab.ciclo + cab.cod + cab.mens + cab.obs + 1;
    }
    return matriculas;
}

Matricula_m CabeceraWithFile::readRecord(int pos) {
    auto target = this->load();
    return target[pos];
}

void CabeceraWithFile::add(Matricula_m record) {
    file.clear();
    cabecera_file.clear();
    file.seekg(0, std::ios::end);
    cabecera_file.seekg(0, std::ios::end);
    int codigo_size = (int) record.codigo.length();
    int obs_size = (int) record.observaciones.length();
    int ciclo_size = (int) std::to_string(record.ciclo).length();
    int mens_size = (int) std::to_string(record.mensualidad).length();
    std::string codigo_t(MAX_COD_SIZE - 1, ' ');
    std::string obs_t(MAX_OBSERVACIONES_SIZE - 1, ' ');
    std::string ciclo_t(MAX_CICLO_SIZE - 1, ' ');
    std::string mens_t(MAX_MENSUALIDAD_SIZE - 1, ' ');
    std::string codigo_n = std::to_string(codigo_size);
    std::string obs_n = std::to_string(obs_size);
    std::string ciclo_n = std::to_string(ciclo_size);
    std::string mens_n = std::to_string(mens_size);
    file << record.codigo << std::to_string(record.ciclo) << std::to_string(record.mensualidad) << record.observaciones
         << "\n";
    file.flush();
    int index = 0;
    for (const char &element: codigo_n) {
        codigo_t[index] = element;
        index++;
    }
    index = 0;
    for (const char &element: obs_n) {
        obs_t[index] = element;
        index++;
    }
    index = 0;
    for (const char &element: ciclo_n) {
        ciclo_t[index] = element;
        index++;
    }
    index = 0;
    for (const char &element: mens_n) {
        mens_t[index] = element;
        index++;
    }
    std::stringstream target;
    target << codigo_t << ciclo_t << mens_t << obs_t << "\n";
    std::string target_string = target.str();
    int len = (int) target_string.size();
    cabecera_file.write(target_string.c_str(), len);
    cabecera_file.flush();
}

void pregunta4() {
    std::cout.precision(10);
    auto *prueba4 = new CabeceraWithFile("datos2_m.txt", "cabecera.dat");


    // Pruebas
    std::cout << "Se guardó y sincronizo la información del fichero principal en una cabecera con extensión dat"
              << std::endl;
    std::cout << "Los archivos no se encuentran alineados ya que no se conoce su longitud real sin la cabecera"
              << std::endl;
    std::cout << "Algunos elementos float se truncan por el tema del floating point"
              << std::endl << std::endl;
    // Load
    std::cout << "Prueba load" << std::endl << "\n";
    auto load_test = prueba4->load();
    for (auto element : load_test){
        std::cout << element.codigo << "  " << element.ciclo << "  " << element.mensualidad  << "  " << element.observaciones << "\n";
    }
    std::cout << std::endl << std::endl;

    // Read record
    std::cout << "Prueba read record -" << " cod 2" << std::endl;
    auto record_test = prueba4->readRecord(2);
    std::cout<< "\n";
    std::cout << record_test.codigo << record_test.ciclo << record_test.mensualidad << record_test.observaciones;
    std::cout << "\n";

    // Add record
    std::cout << "Prueba add record"  << std::endl;
    std::cout << std::endl;
    auto test_target = createMatricula("234",8,1931.1251,"Recien aniadido 2");
    prueba4->add(test_target);
    load_test = prueba4->load();
    for (auto element : load_test){
        std::cout << element.codigo << "  " << element.ciclo << "  " << element.mensualidad  << "  " << element.observaciones << "\n";
    }
    std::cout << std::endl;
    delete prueba4;
//    auto ma = prueba4->readRecord(3);
//    std::cout << ma.mensualidad << std::endl;
}

Matricula_m createMatricula(std::string codigo_, int ciclo_, float mensualidad_, std::string obs_) {
    Matricula_m result;
    result.codigo = std::move(codigo_);
    result.ciclo = ciclo_;
    result.observaciones = std::move(obs_);
    result.mensualidad = mensualidad_;
    return result;
}
