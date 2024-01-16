#pragma once
#include <map>
#include <string>
#include <vector>
#include <queue>

// May to add rarity of diseases and other earnigs for other diseases

std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string numbers = "0123456789";

void run_simulation() {
    bool life = true;
    int days = 0;

    std::vector<Patient*> patients;
    std::vector<MedicineEmployee*> doctors;
    std::vector<DepartmentDirector*> directors;
    while (life) {
        days++;
    }
}

std::string generate_start_disease_naming() {
    int range = 3;
    std::string result = "";
    srand(time(NULL));
    for (int i = 0; i < range; i++) {
        result += alphabet[rand() % 51];
    }
    return result + "-";
}
std::string generate_midle_disease_naming() {
    int range = 6;
    std::string origin = alphabet + numbers;
    std::string result = "";
    srand(time(NULL));
    for (int i = 0; i < range; i++) {
        result += origin[rand() % 61];
    }
    return result + "-";
}
std::string generate_end_disease_naming() {
    int range = 4;
    std::string result = "";
    srand(time(NULL));
    for (int i = 0; i < range; i++) {
        result += numbers[rand() % 9];
    }
    return result;
}


enum DeiseasesTypes {
    NoDeiseas = 1,
    Surginious,
    Surigilious,
    Surgalius,
    ENTilious,
    ENTaoulious,
    ENTononius
};


std::vector<std::string> departments = { "SurgeonDep", "ENTDep" };

std::map<std::string, std::vector<enum DeiseasesTypes>> DeiseasesForDeps = {
    {"SurgeonDep", {Surginious, Surigilious, Surgalius} },
    {"ENTDep", { ENTilious, ENTaoulious, ENTononius} }
};


class Destiny;
class Hospital;
class DepartmentDirector;
class MedicineEmployee;
class Surgeon;
class ENTSpecialist;
class Disease;
class Patient;

class Destiny {
private:
    int count_of_patients;
    int count_of_doctors;
    int percentage_of_get_illing;
    static const int min_days_to_heal = 2;
    static const int max_days_to_heal = 5;
public:
    Destiny() {
        srand(time(NULL));
        count_of_doctors = 1 + rand() % 5;
        count_of_patients = 1 + rand() % 8;
        percentage_of_get_illing = 10 + rand() % 40;
    }

    Patient* make_patient() { ; }
    MedicineEmployee* make_doctor() { ; }

    static std::string make_disease_name() {
        return generate_start_disease_naming() + generate_midle_disease_naming() + generate_end_disease_naming();
    }
    static int make_disease_time_to_heal() {
        srand(time(NULL));
        return Destiny::min_days_to_heal + rand() % max_days_to_heal;
    }
    static DeiseasesTypes make_disease_type() {
        srand(time(NULL));
        int random_type = 2 + rand() % 6;
        return DeiseasesTypes(random_type);
    }
};

class Hospital {
private:
    std::vector<std::string> departments;
    std::vector<MedicineEmployee*> employees;
    std::vector<Patient*> patients;
    std::queue<Patient*> unserviced_patients;
public:
    Hospital() {
        departments = { "SurgeonDep", "ENTDep" };
        employees = {};
        patients = {};
        unserviced_patients = {};
    }

    void add_patient(Patient* patient) {
        patients.push_back(patient);
    }

    void add_doctor(MedicineEmployee* employee) {
        employees.push_back(employee);
    }

    // Heal all the pacients
    void heal_patients() {
        for (int i = 0; i < employees.size(); i++) {
            MedicineEmployee* employee = employees[i];
            std::vector<Patient*> employee_own_patients = employee->own_patients;
            for (int i = 0; i < employee_own_patients.size(); i++) {
                Patient* patient = employee_own_patients[i];
                employee
            }
        }
    }

    // Add patients to healing by the free doctor
    void service_new_patients () {
        if (!unserviced_patients.empty()) {
            Patient* patient = unserviced_patients.front();
            unserviced_patients.pop();
            Disease current_disease = patient->disease;
            bool get_mergency = false;
            for (int i = 0; i < employees.size(); i++) {
                MedicineEmployee* employee = employees[i];
                if (employee->heal_current_disease(current_disease.type)) {
                    if (employee->own_patients.size() < employee->get_max_count_patients()) {
                        employee->own_patients.push_back(patient);
                        patients.push_back(patient);
                        get_mergency = true;
                        break;
                    }
                }
            }
            if (!get_mergency) {
                unserviced_patients.push(patient);
            }
        }
    }

    // Add patient to queue, later it will go to doctor, when someone of doctors became free
    void add_pacient_to_queue (Patient* patient) {
        unserviced_patients.push(patient);
    }
};

class MedicineEmployee {
    friend class Hospital;
protected:
    std::string department;
    std::string name;
    std::string surname;
    int age;
    std::string position;
    std::string sex;
    std::vector<Patient*> own_patients;
    int money;
    bool hired;
public:
    MedicineEmployee(std::string uname = "Undefined", std::string usurname = "Undefined",
        int uage = 0, std::string uposition = "Undefined", std::string usex = "Undefined",
        std::string udepartment = "Undefined") {
        hired = true;
        name = uname;
        surname = usurname;
        age = uage;
        position = uposition;
        sex = usex;
        department = udepartment;
    }

    virtual ~MedicineEmployee () {}

    virtual void heal_patient (Patient* patient);

    bool heal_current_disease(DeiseasesTypes type) {
        auto iter = DeiseasesForDeps.find(department);
        if (iter != DeiseasesForDeps.end()) {
            std::vector<DeiseasesTypes> types = iter->second;
            for (int i = 0; i < types.size(); i++) {
                if (types[i] == type) {
                    return true;
                }
            }
        }
        else {
            std::cout << "[-] Doctor has incorrect department!" << std::endl;
        }
        return false;
    }

    int get_max_count_patients() {
        if (typeid(this) == typeid(Surgeon)) {
            return dynamic_cast<Surgeon*>(this)->max_patient_count;
        }
        else if (typeid(this) == typeid(ENTSpecialist)) {
            return dynamic_cast<ENTSpecialist*>(this)->max_patient_count;
        }
        else {
            std::cout << "Incorrect class of employee" << std::endl;
            return 0;
        }
    }
};

class DepartmentDirector : private MedicineEmployee, private Hospital {
public:
    DepartmentDirector() {}
    void lay_off_employee() {}
    void hire_employee() {}
};

class Surgeon : private MedicineEmployee { // Хирург
    friend class MedicineEmployee;
private:
    const int max_patient_count = 2;
    int patients_now = 0;
public:
    Surgeon(std::string uname = "Undefined", std::string usurname = "Undefined",
        int uage = 0, std::string uposition = "Undefined", std::string usex = "Undefined",
        std::string udepartment = "Undefined")
        : MedicineEmployee(uname, usurname, uage, uposition, usex, udepartment) {

    }

    virtual void heal_patient(Patient* patient) {
        this->money += 100;
        patient;
    }

    virtual ~Surgeon () {}
};

class ENTSpecialist : private MedicineEmployee { // Лор
    friend class MedicineEmployee;
private:
    const int max_patient_count = 5;
    int patients_now = 0;
public:
    ENTSpecialist(std::string uname = "Undefined", std::string usurname = "Undefined",
        int uage = 0, std::string uposition = "Undefined", std::string usex = "Undefined",
        std::string udepartment = "Undefined")
        : MedicineEmployee(uname, usurname, uage, uposition, usex, udepartment) {

    }

    virtual ~ENTSpecialist() {}
};

class Disease {
    friend class Patient;
    friend class Hospital;
private:
    std::string disease_name;
    bool active;
    int days_to_heal;
    DeiseasesTypes type;
public:
    Disease() {
        active = false;
        disease_name = "None";
        days_to_heal = 0;
        type = NoDeiseas;
    }
    Disease(bool activation) {
        active = true;
        disease_name = Destiny::make_disease_name();
        days_to_heal = Destiny::make_disease_time_to_heal();
        type = Destiny::make_disease_type();
    }
};

class Patient {
    friend class Hospital;
    friend class MedicineEmployee;
private:
    std::string name;
    std::string surname;
    int age;
    std::string sex;
    Disease disease;
    int healing_days;
public:
    Patient(Disease udisease, std::string uname = "Undefined", std::string usurname = "Undefined",
        int uage = 0, std::string usex = "Undefined") {
        name = uname;
        surname = usurname;
        age = uage;
        sex = usex;
        disease = udisease;
        healing_days = 0;
    }

    void get_disease() {
        disease = Disease(true);
    }

    void became_healthy() {
        disease = Disease();
    }

    void go_to_hospital(Hospital* hospital) {
        hospital->add_pacient_to_queue(this);
    }
private:
    void heal();
};
