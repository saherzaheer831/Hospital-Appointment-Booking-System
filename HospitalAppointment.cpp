#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>
using namespace std;

const int MAX = 100;

struct Doctor {
    int id;
    string name;
    string specialization;
    string availableTime;
    vector<string> availableDays;
};

struct Appointment {
    int patientID;
    string patientName;
    int doctorID;
    string date;
    string day;
};

Doctor doctors[MAX];
Appointment appointments[MAX];
int doctorCount = 0;
int appointmentCount = 0;

// Patient credentials
string patientUsernames[MAX] = {
    "ahmedali", "saranoor", "aliraza", "fatimakhan", "zainabbas", "mariashah",
    "usmantariq", "ayeshabibi", "hassanjamil", "zoyamalik", "bilalahmad", "sanaharoon",
    "fahadqureshi", "iqramehmood", "nomankhalid", "rabiayounus", "adeelrana", "mehakfarooq",
    "hamzayasin", "hinazafar", "omarshahid", "laibanadeem", "shayanali", "mariamtariq",
    "saadrauf", "taniajaved", "daniyalhaider", "nimrairfan", "rehansaeed", "fizamalik",
    "mubeenaslam", "alinasheikh", "imrannaveed"
};

string patientPasswords[MAX] = {
    "aa@421", "sn@837", "ar@193", "fk@582", "za@364", "ms@105",
    "ut@479", "ab@238", "hj@663", "zm@750", "ba@986", "sh@114",
    "fq@672", "im@549", "nk@375", "ry@842", "ar@291", "mf@700",
    "hy@328", "hz@159", "os@934", "ln@286", "sa@913", "mt@570",
    "sr@643", "tj@821", "dh@734", "ni@207", "rs@688", "fm@192",
    "ma@357", "as@903", "in@416"
};

string patientNames[MAX] = {
    "Ahmed Ali     ", "Sara Noor     ", "Ali Raza      ", "Fatima Khan   ", "Zain Abbas    ", "Maria Shah    ",
    "Usman Tariq   ", "Ayesha Bibi   ", "Hassan Jamil  ", "Zoya Malik    ", "Bilal Ahmad   ", "Sana Haroon   ",
    "Fahad Qureshi ", "Iqra Mehmood  ", "Noman Khalid  ", "Rabia Younus  ", "Adeel Rana    ", "Mehak Farooq  ",
    "Hamza Yasin   ", "Hina Zafar    ", "Omar Shahid   ", "Laiba Nadeem  ", "Shayan Ali    ", "Mariam Tariq  ",
    "Saad Rauf     ", "Tania Javed   ", "Daniyal Haider", "Nimra Irfan   ", "Rehan Saeed   ", "Fiza Malik    ",
    "Mubeen Aslam  ", "Alina Sheikh  ", "Imran Naveed  "
};

int patientLoginCount = 33;

// Doctor credentials
string doctorUsernames[11] = {"usman", "mazhar", "huma", "hina", "sadat", "faiq", "najam", "mujadad", "rubina", "adeel", "mishi"};
string doctorPasswords[11] = {"us@2576", "mz@2311", "huma#9787", "hina$9272", "sadi*3275", "fai@2975", "naji#19.95", "muji3931!", "rubi2218?", "adi8890}", "N9BZ5GScpzfkTeh"};
int doctorIDs[11] = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111};

// Function Prototypes
bool login(string role, string& outUsername);
void createPatientLogin();
void adminMenu();
void doctorMenu(string username);
void patientMenu(string username);
void addDoctor();
void viewDoctors();
void bookAppointment(string username);
void viewAppointments();
void viewAppointmentsForDoctor(int docID);
void viewAppointmentsForPatient(int patientID);
void cancelAppointment(string username);
void cancelDoctorAppointment(int docID);
bool isDoctorAvailableOnDay(int docID, const string& day);
int getValidInput(int min, int max);

// Helper function to get valid integer input
int getValidInput(int min, int max) {
    string input;
    int choice;
    
    while (true) {
        cin >> input;
        
        // Check if input is a single digit
        if (input.length() == 1 && isdigit(input[0])) {
            choice = input[0] - '0';
            if (choice >= min && choice <= max) {
                return choice;
            }
        }
        
        cout << "Invalid choice! Please enter a number between " << min << " and " << max << ": ";
        cin.clear();
    }
}

int main() {
    string input, username;
    int choice;

    // Sample Doctors
    doctors[0] = {101, "Dr. Usman Ahmed   ", "Medicine Specialist", "10AM-2PM", {"Monday", "Wednesday"}};
    doctors[1] = {102, "Dr. Mazhar Abbas  ", "General Surgeon    ", "1PM-5PM ", {"Tuesday", "Thursday"}};
    doctors[2] = {103, "Dr. Huma Bashir   ", "Gynaecologist      ", "10AM-2PM", {"Monday", "Friday"}};
    doctors[3] = {104, "Dr. Hina Ayesha   ", "Paediatritian      ", "10AM-2PM", {"Wednesday"}};
    doctors[4] = {105, "Dr. Sadat Nawaz   ", "Orthopaedic Surgeon", "10AM-2PM", {"Friday"}};
    doctors[5] = {106, "Dr. Faiq Abdullah ", "Cardiologist       ", "10AM-2PM", {"Tuesday"}};
    doctors[6] = {107, "Dr. Najam Jamshaid", "Dermatologist      ", "10AM-2PM", {"Monday", "Thursday"}};
    doctors[7] = {108, "Dr. Mujadad Ahmed ", "Ophthalmologist    ", "10AM-2PM", {"Monday"}};
    doctors[8] = {109, "Dr. Rubina Mubeen ", "Radiologist        ", "10AM-2PM", {"Wednesday"}};
    doctors[9] = {110, "Dr. Adeel Arif    ", "ENT Specialist     ", "10AM-2PM", {"Tuesday", "Friday"}};
    doctors[10] = {111, "Dr. Mishaal Ch    ", "Psychiatrist       ", "9AM-1PM ", {"Thursday"}};
    doctorCount = 11;

    // Predefined Appointments for patients
    int pid = 501;
    for (int d = 0; d < doctorCount && appointmentCount < MAX - 10; d++) {
        for (int i = 0; i < 3 && appointmentCount < MAX - 10; i++) {
            if (pid - 501 < patientLoginCount) {
                appointments[appointmentCount++] = {
                    pid,
                    patientNames[pid - 501],
                    doctors[d].id,
                    "2024-06-" + to_string(10 + i + d),
                    doctors[d].availableDays[i % doctors[d].availableDays.size()]
                };
                pid++;
            }
        }
    }

    // Main Menu
    while (true) {
        cout << "\n===== HOSPITAL APPOINTMENT BOOKING SYSTEM =====\n";
        cout << "1. Administrator\n2. Doctor\n3. Patient\n4. Exit\n";
        cout << "Choose your role (1-4): ";
        
        choice = getValidInput(1, 4);

        switch (choice) {
            case 1: if (login("admin", username)) adminMenu(); break;
            case 2: if (login("doctor", username)) doctorMenu(username); break;
            case 3:
                cout << "\nNote: If you are a new patient, ask Admin to register you.\nAdmin Email: contactinfo890@gmail.com \n";
                if (login("patient", username)) patientMenu(username);
                break;
            case 4: cout << "Exiting program. Goodbye!\n"; return 0;
        }
    }
}

bool login(string role, string& outUsername) {
    string username, password;
    cout << "\nEnter Username: "; cin >> username;
    cout << "Enter Password: "; cin >> password;

    if (role == "admin" && username == "Cybrixx5" && password == "19.95") {
        outUsername = username;
        cout << "\nLogin Successful as Furqan!\nHello Furqan.\n"; return true;
    }
    else if (role == "admin" && username == "saher" && password == "zaheer") {
        outUsername = username;
        cout << "\nLogin Successful as Saher!\nHello Saher.\n"; return true;
    }
    else if (role == "admin" && username == "isbah" && password == "rizwan") {
        outUsername = username;
        cout << "\nLogin Successful as Isbah!\nHello Isbah.\n"; return true;
    }
    else if (role == "doctor") {
        for (int i = 0; i < 11; i++) {
            if (doctorUsernames[i] == username && doctorPasswords[i] == password) {
                outUsername = username;
                cout << "\nLogin Successful as Doctor!\n"; return true;
            }
        }
    }
    else if (role == "patient") {
        for (int i = 0; i < patientLoginCount; i++) {
            if (patientUsernames[i] == username && patientPasswords[i] == password) {
                outUsername = username;
                cout << "\nLogin Successful as Patient!\nYour Patient ID: " << (501 + i) << "\n"; return true;
            }
        }
    }

    cout << "Login Failed! Try again.\n"; return false;
}

void adminMenu() {
    int option;
    do {
        cout << "\n--- ADMIN MENU ---\n";
        cout << "1. Add Doctor\n2. View All Doctors\n3. View Appointments\n4. Add New Patient Login\n5. Exit\nChoose option (1-5): ";
        option = getValidInput(1, 5);

        switch (option) {
            case 1: addDoctor(); break;
            case 2: viewDoctors(); break;
            case 3: viewAppointments(); break;
            case 4: createPatientLogin(); break;
            case 5: cout << "Exiting Admin Menu...\n"; break;
        }
    } while (option != 5);
}

void doctorMenu(string username) {
    int doctorID = -1;
    for (int i = 0; i < 11; i++) {
        if (doctorUsernames[i] == username) {
            doctorID = doctorIDs[i];
            break;
        }
    }
    if (doctorID == -1) return;

    int option;
    do {
        cout << "\n--- DOCTOR MENU ---\n";
        cout << "1. View My Appointments\n2. Cancel Appointment\n3. Exit\nChoose option (1-3): ";
        option = getValidInput(1, 3);

        switch (option) {
            case 1: viewAppointmentsForDoctor(doctorID); break;
            case 2: cancelDoctorAppointment(doctorID); break;
            case 3: cout << "Exiting Doctor Menu...\n"; break;
        }
    } while (option != 3);
}

void patientMenu(string username) {
    int patientID = -1;
    for (int i = 0; i < patientLoginCount; i++) {
        if (patientUsernames[i] == username) {
            patientID = 501 + i;
            break;
        }
    }
    if (patientID == -1) return;

    int option;
    do {
        cout << "\n--- PATIENT MENU ---\n";
        cout << "1. View Doctors\n2. Book Appointment\n3. View My Appointments\n4. Cancel My Appointment\n5. Exit\nChoose option (1-5): ";
        option = getValidInput(1, 5);

        switch (option) {
            case 1: viewDoctors(); break;
            case 2: bookAppointment(username); break;
            case 3: viewAppointmentsForPatient(patientID); break;
            case 4: cancelAppointment(username); break;
            case 5: cout << "Exiting Patient Menu...\n"; break;
        }
    } while (option != 5);
}

void createPatientLogin() {
    if (patientLoginCount >= MAX) {
        cout << "Cannot add more patient logins.\n"; return;
    }

    string newUser, newPass, newName;
    cout << "Enter new patient's username: "; cin >> newUser;
    cout << "Enter new patient's password: "; cin >> newPass;
    cin.ignore();
    cout << "Enter full name of patient: "; getline(cin, newName);

    patientUsernames[patientLoginCount] = newUser;
    patientPasswords[patientLoginCount] = newPass;
    patientNames[patientLoginCount] = newName;
    patientLoginCount++;
    cout << "New patient login created successfully!\n";
}

void viewDoctors() {
    cout << "\n--- Doctor List ---\n";
    for (int i = 0; i < doctorCount; i++) {
        cout << "ID: " << doctors[i].id << " | Name: " << doctors[i].name
             << " | Specialization: " << doctors[i].specialization
             << " | Time: " << doctors[i].availableTime
             << " | Days: ";
        for (size_t j = 0; j < doctors[i].availableDays.size(); j++) {
            cout << doctors[i].availableDays[j];
            if (j < doctors[i].availableDays.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
}

bool isDoctorAvailableOnDay(int docID, const string& day) {
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == docID) {
            for (const string& d : doctors[i].availableDays)
                if (d == day) return true;
        }
    }
    return false;
}

void bookAppointment(string username) {
    int patientID = -1;
    string expectedName;
    for (int i = 0; i < patientLoginCount; i++) {
        if (patientUsernames[i] == username) {
            patientID = 501 + i;
            expectedName = patientNames[i];
            break;
        }
    }
    if (patientID == -1) return;

    if (appointmentCount >= MAX) {
        cout << "Cannot book more appointments. System full.\n";
        return;
    }

    Appointment a;
    a.patientID = patientID;
    a.patientName = expectedName;

    viewDoctors();
    cout << "Enter Doctor ID to Book Appointment: ";
    cin >> a.doctorID;

    // Validate doctor ID
    bool validDoctor = false;
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == a.doctorID) {
            validDoctor = true;
            break;
        }
    }
    if (!validDoctor) {
        cout << "Invalid Doctor ID!\n";
        return;
    }

    cout << "Enter Appointment Date (YYYY-MM-DD): ";
    cin >> a.date;
    cout << "Enter Appointment Day (e.g., Monday) with first letter Capital: ";
    cin >> a.day;

    if (!isDoctorAvailableOnDay(a.doctorID, a.day)) {
        cout << "Error: Doctor is not available on " << a.day << ".\n";
        return;
    }

    appointments[appointmentCount++] = a;
    cout << "Appointment Booked Successfully for " << a.date << " (" << a.day << ").\n";
}

void viewAppointments() {
    cout << "\n--- All Appointments ---\n";
    if (appointmentCount == 0) {
        cout << "No appointments found.\n";
        return;
    }
    for (int i = 0; i < appointmentCount; i++) {
        cout << "Patient ID: " << appointments[i].patientID
             << " | Name: " << appointments[i].patientName
             << " | Doctor ID: " << appointments[i].doctorID
             << " | Date: " << appointments[i].date
             << " | Day: " << appointments[i].day << "\n";
    }
}

void viewAppointmentsForDoctor(int docID) {
    cout << "\n--- Your Appointments ---\n";
    bool found = false;
    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].doctorID == docID) {
            cout << "Patient ID: " << appointments[i].patientID
                 << " | Name: " << appointments[i].patientName
                 << " | Date: " << appointments[i].date
                 << " | Day: " << appointments[i].day << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No appointments found.\n";
    }
}

void viewAppointmentsForPatient(int patientID) {
    cout << "\n--- Your Appointments ---\n";
    bool found = false;
    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].patientID == patientID) {
            cout << "Doctor ID: " << appointments[i].doctorID
                 << " | Date: " << appointments[i].date
                 << " | Day: " << appointments[i].day << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "No appointments found.\n";
    }
}

void cancelDoctorAppointment(int docID) {
    viewAppointmentsForDoctor(docID);
    if (appointmentCount == 0) return;
    
    int pid;
    cout << "Enter Patient ID to cancel their appointment: ";
    cin >> pid;
    
    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].doctorID == docID && appointments[i].patientID == pid) {
            for (int j = i; j < appointmentCount - 1; j++)
                appointments[j] = appointments[j + 1];
            appointmentCount--;
            cout << "Appointment cancelled successfully.\n";
            return;
        }
    }
    cout << "No matching appointment found.\n";
}

void cancelAppointment(string username) {
    int patientID = -1;
    for (int i = 0; i < patientLoginCount; i++) {
        if (patientUsernames[i] == username) {
            patientID = 501 + i;
            break;
        }
    }
    if (patientID == -1) return;

    for (int i = 0; i < appointmentCount; i++) {
        if (appointments[i].patientID == patientID) {
            for (int j = i; j < appointmentCount - 1; j++)
                appointments[j] = appointments[j + 1];
            appointmentCount--;
            cout << "Appointment cancelled successfully.\n";
            return;
        }
    }
    cout << "No appointment found under your ID.\n";
}

void addDoctor() {
    if (doctorCount >= MAX) {
        cout << "Cannot add more doctors.\n";
        return;
    }

    Doctor d;
    cout << "Enter Doctor ID: ";
    cin >> d.id;
    
    // Check for duplicate ID
    for (int i = 0; i < doctorCount; i++) {
        if (doctors[i].id == d.id) {
            cout << "Doctor with this ID already exists!\n";
            return;
        }
    }
    
    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, d.name);

    cout << "Enter Specialization: ";
    getline(cin, d.specialization);

    cout << "Enter Available Time (e.g., 10AM-2PM): ";
    getline(cin, d.availableTime);

    int dayCount;
    cout << "Enter number of available days: ";
    cin >> dayCount;
    cin.ignore();

    for (int i = 0; i < dayCount; i++) {
        string day;
        cout << "Enter day " << (i + 1) << ": ";
        getline(cin, day);
        d.availableDays.push_back(day);
    }

    doctors[doctorCount++] = d;
    cout << "Doctor added successfully!\n";
}

