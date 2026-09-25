#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Patient
{
    int patientId;
    string name;
    int age;
    string gender;
    string contact;
    double balance;
};
struct Doctor
{
    int doc_id;
    string name;
    string specialty;
    int experience;
};
struct Appointment
{
    int patientId;
    int doctorId;
    char date[11];
    char time[10];
};
struct Treatment
{
    int patientId;
    string description;
    double cost;
    bool paid;
};
bool corrphone(string contact)
{
    if (contact.length() != 11)
        return false;
    for (int i = 0; i < contact.length(); i++)
    {
        if (contact[i] < '0' || contact[i] > '9')
            return false;
    }
    return true;
}

string fixGender(string g)
{
    if (g == "M")
        return "Male";
    if (g == "F")
        return "Female";
    return g;
}

string fixDate(string d)
{
    if (d.length() >= 10 && d[4] == '-')
    {
        string year = d.substr(0, 4);
        string month = d.substr(5, 2);
        string day = d.substr(8, 2);

        return month + "-" + day + "-" + year;
    }
    return d;
}

string fixtime(string t)
{

    if (t.find("AM") != -1 || t.find("PM") != -1)
        return t;

    string hourStr = t.substr(0, 2);
    string minutes = t.substr(2);

    int hour = (hourStr[0] - '0') * 10 + (hourStr[1] - '0');

    string period = "AM";

    if (hour >= 12)
    {
        period = "PM";
        if (hour > 12)
            hour -= 12;
    }

    if (hour == 0)
        hour = 12;

    string result = "";

    if (hour >= 10)
    {
        result += char((hour / 10) + '0');
        result += char((hour % 10) + '0');
    }
    else
    {
        result += char(hour + '0');
    }

    result += minutes;
    result += " ";
    result += period;

    return result;
}

bool isValidRecord(string id, string name, string contact)
{
    if (id == "" || name == "" || contact == "")
        return false;
    if (!corrphone(contact))
        return false;

    return true;
}

void cleanpatients()
{

    ifstream file("patients.txt");
    ofstream temp("temp.txt");

    if (!file)
    {
        cout << "patients file not found \n";
        return;
    }

    string line;
    string ids[500]; 
    int idcount = 0; 
    while (getline(file, line))
    {

        string part[6], word = "";
        int index = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;

        if (index < 5)
            continue;

        string id = part[0];
        string name = part[1];
        string age = part[2];
        string gender = fixGender(part[3]);
        string contact = part[4];
        string balance = part[5];
        if (!isValidRecord(id, name, contact))
            continue;

    
        bool duplicate = false; // to chk duplicate id
        for (int i = 0; i < idcount; i++)
        {
            if (ids[i] == id)
            {
                duplicate = true;
                break;
            }
        }
        if (duplicate)
            continue;

        ids[idcount++] = id;

        temp << id << "#" << name << "#" << age << "#" << gender << "#" << contact << "#" << balance << endl;
    }
    file.close();
    temp.close();
    remove("patients.txt");
    rename("temp.txt", "patients.txt");
    cout << "patients files is cleaned\n";
}

void cleandoctors()
{

    ifstream file("doctors.txt");
    ofstream temp("temp.txt");

    if (!file)
    {
        cout << "doctors file not found\n";
        return;
    }

    string line;
    while (getline(file, line))
    {
        string part[4], word = "";
        int index = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;
        if (index < 3)
            continue;
        if (part[1] == "" || part[2] == "")
            continue;
        temp << part[0] << "#" << part[1] << "#" << part[2] << "#" << part[3] << endl;
    }
    file.close();
    temp.close();
    remove("doctors.txt");
    rename("temp.txt", "doctors.txt");
    cout << "doctors file is cleaned\n";
}
void cleanAppointments()
{
    ifstream file("appointments.txt");
    ofstream temp("temp.txt");
    if (!file)
    {
        cout << "appointments file not found\n";
        return;
    }
    string line;
    while (getline(file, line))
    {
        string part[4], word = "";
        int index = 0;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;
        if (index < 3)
            continue;
        string date = fixDate(part[2]);
        string time = fixtime(part[3]);
        temp << part[0] << "#" << part[1] << "#" << date << "#" << time << endl;
    }
    file.close();
    temp.close();
    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");
    cout << "Appointments cleaned\n";
}
void cleanTreatments()
{
    ifstream file("treatments.txt");
    ofstream temp("temp.txt");
    if (!file)
    {
        cout << "treatments file not found\n";
        return;
    }
    string line;
    while (getline(file, line))
    {
        if (line != "")
            temp << line << endl;
    }
    file.close();
    temp.close();
    remove("treatments.txt");
    rename("temp.txt", "treatments.txt");

    cout << "Treatments cleaned\n";
}
void cleanBills()
{
    ifstream file("bills.txt");
    ofstream temp("temp.txt");

    if (!file)
    {
        cout << "bills file not found\n";
        return;
    }

    string line;

    while (getline(file, line))
    {
        if (line != "")
            temp << line << endl;
    }

    file.close();
    temp.close();
    remove("bills.txt");
    rename("temp.txt", "bills.txt");

    cout << "Bills cleaned\n";
}
int countpatients()
{
    ifstream file("patients.txt");

    string line;
    int count = 0;

    while (getline(file, line))
    {
        if (line != "")
            count++;
    }

    file.close();
    return count;
}
int countdoctors()
{
    ifstream file("doctors.txt");

    string line;
    int count = 0;

    while (getline(file, line))
    {
        if (line != "")
            count++;
    }

    file.close();
    return count;
}
void loadpatients(Patient *p, int n)
{

    ifstream file("patients.txt");
    string line;

    int i = 0;

    while (getline(file, line))
    {

        string part[6], word = "";
        int index = 0;

        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[j];
        }
        part[index] = word;

    
        int num = 0;
        for (int k = 0; k < part[0].length(); k++)
        {
            num = num * 10 + (part[0][k] - '0');
        }
        p[i].patientId = num;

        
        num = 0;
        for (int k = 0; k < part[2].length(); k++)
        {
            num = num * 10 + (part[2][k] - '0');
        }
        p[i].age = num; 
        p[i].name = part[1];
        p[i].gender = part[3];
        p[i].contact = part[4];
        double bal = 0;
        for (int k = 0; k < part[5].length(); k++)
        {
            bal = bal * 10 + (part[5][k] - '0');
        }
        p[i].balance = bal;

        i++;
    }

    file.close();
}
void loaddoctors(Doctor *d, int n)
{

    ifstream file("doctors.txt");
    string line;

    int i = 0;

    while (getline(file, line))
    {

        string part[4], word = "";
        int index = 0;

        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[j];
        }
        part[index] = word;

        int num = 0;
        for (int k = 0; k < part[0].length(); k++)
        {
            num = num * 10 + (part[0][k] - '0');
        }
        d[i].doc_id = num;

        
        num = 0;
        for (int k = 0; k < part[3].length(); k++)
        {
            num = num * 10 + (part[3][k] - '0');
        }
        d[i].experience = num;
        d[i].name = part[1];
        d[i].specialty = part[2];

        i++;
    }

    file.close();
}
void showpatients(Patient *p, int n)
{

    cout << "\nPatients:\n";

    for (int i = 0; i < n; i++)
    {
        cout << p[i].patientId << " "
             << p[i].name << " "
             << p[i].age << " "
             << p[i].gender << " "
             << p[i].contact << endl;
    }
}
void showdoctors(Doctor *d, int n)
{

    cout << "\nDoctors:\n";

    for (int i = 0; i < n; i++)
    {
        cout << d[i].doc_id << " "
             << d[i].name << " "
             << d[i].specialty << " "
             << d[i].experience << endl;
    }
}
void searchpatient(Patient *p, int n)
{

    int id;
    cout << "\nEnter patient ID: ";
    cin >> id;

    bool found = false;

    for (int i = 0; i < n; i++)
    {

        if (p[i].patientId == id)
        {

            cout << "\nPatient Found:\n";
            cout << p[i].patientId << " "
                 << p[i].name << " "
                 << p[i].age << " "
                 << p[i].gender << " "
                 << p[i].contact << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Patient not found\n";
    }
}

bool login()
{

    string id, pass;

    cout << "\nLogin Required\n";
    cout << "Enter ID: ";
    cin >> id;

    cout << "Enter Password: ";
    cin >> pass;

    if (id == "admin" && pass == "1234")
    {
        cout << "Login successful\n";
        return true;
    }
    else
    {
        cout << "Invalid ID or Password\n";
        return false;
    }
}
void addpatient()
{

    ofstream file("patients.txt", ios::app);

    string id, name, age, gender, contact, balance;

    cout << "\nEnter ID: ";
    cin >> id;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;

    cout << "Enter Gender (M/F): ";
    cin >> gender;

    cout << "Enter Contact: ";
    cin >> contact;

    cout << "Enter Balance: ";
    cin >> balance;

    if (name == "" || id == "" || contact == "")
    {
        cout << "Invalid data\n";
        return;
    }

    file << id << "#" << name << "#" << age << "#"
         << gender << "#" << contact << "#" << balance << endl;

    file.close();

    cout << "Patient added\n";
}
void deletepatient()
{

    ifstream file("patients.txt");
    ofstream temp("temp.txt");

    string line, id;

    cout << "\nEnter ID to delete: ";
    cin >> id;

    bool found = false;

    while (getline(file, line))
    {

        string part[6], word = "";
        int index = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;

        if (part[0] == id)
        {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found)
        cout << "Patient deleted\n";
    else
        cout << "Patient not found\n";
}
void updatepatient()
{

    ifstream file("patients.txt");
    ofstream temp("temp.txt");

    string line, id;

    cout << "\nEnter ID to update: ";
    cin >> id;

    bool found = false;

    while (getline(file, line))
    {

        string part[6], word = "";
        int index = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;

        if (part[0] == id)
        {

            found = true;

            string name, age, gender, contact, balance;

            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter New Age: ";
            cin >> age;

            cout << "Enter New Gender: ";
            cin >> gender;

            cout << "Enter New Contact: ";
            cin >> contact;

            cout << "Enter New Balance: ";
            cin >> balance;

            temp << id << "#" << name << "#" << age << "#"
                 << gender << "#" << contact << "#" << balance << endl;
        }
        else
        {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found)
        cout << "Patient updated\n";
    else
        cout << "Patient not found\n";
}
void adddoctor()
{

    ofstream file("doctors.txt", ios::app);

    string id, name, specialty, exp;

    cout << "\nEnter Doctor ID: ";
    cin >> id;

    cout << "Enter Name: ";
    cin >> name;

    cout << "Enter Specialty: ";
    cin >> specialty;

    cout << "Enter Experience: ";
    cin >> exp;

    if (id == "" || name == "")
    {
        cout << "Invalid data\n";
        return;
    }

    file << id << "#" << name << "#" << specialty << "#" << exp << endl;

    file.close();

    cout << "Doctor added\n";
}
void deletedoctor()
{

    ifstream file("doctors.txt");
    ofstream temp("temp.txt");

    string line, id;

    cout << "\nEnter Doctor ID to delete: ";
    cin >> id;

    bool found = false;

    while (getline(file, line))
    {

        string part[4], word = "";
        int index = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;

        if (part[0] == id)
        {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("doctors.txt");
    rename("temp.txt", "doctors.txt");

    if (found)
        cout << "Doctor deleted\n";
    else
        cout << "Doctor not found\n";
}
void updatedoctor()
{

    ifstream file("doctors.txt");
    ofstream temp("temp.txt");

    string line, id;

    cout << "\nEnter Doctor ID to update: ";
    cin >> id;

    bool found = false;

    while (getline(file, line))
    {

        string part[4], word = "";
        int index = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;

        if (part[0] == id)
        {

            found = true;

            string name, specialty, exp;

            cout << "Enter New Name: ";
            cin >> name;

            cout << "Enter New Specialty: ";
            cin >> specialty;

            cout << "Enter New Experience: ";
            cin >> exp;

            temp << id << "#" << name << "#" << specialty << "#" << exp << endl;
        }
        else
        {
            temp << line << endl;
        }
    }

    file.close();
    temp.close();

    remove("doctors.txt");
    rename("temp.txt", "doctors.txt");

    if (found)
        cout << "Doctor updated\n";
    else
        cout << "Doctor not found\n";
}
void addappointment()
{

    ofstream file("appointments.txt", ios::app);

    string pid, did, date, time;

    cout << "\nEnter Patient ID: ";
    cin >> pid;

    cout << "Enter Doctor ID: ";
    cin >> did;

    cout << "Enter Date (YYYY-MM-DD): ";
    cin >> date;

    cout << "Enter Time (HHMM): ";
    cin >> time;

    file << pid << "#" << did << "#" << date << "#" << time << endl;

    file.close();

    cout << "Appointment scheduled\n";
}
void viewappointments()
{

    ifstream file("appointments.txt");

    string line;

    cout << "\nAppointments:\n";

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}
void cancelappointment()
{

    ifstream file("appointments.txt");
    ofstream temp("temp.txt");

    string line, pid;

    cout << "\nEnter Patient ID to cancel appointment: ";
    cin >> pid;

    bool found = false;

    while (getline(file, line))
    {

        string part[4], word = "";
        int index = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;

        if (part[0] == pid)
        {
            found = true;
            continue;
        }

        temp << line << endl;
    }

    file.close();
    temp.close();

    remove("appointments.txt");
    rename("temp.txt", "appointments.txt");

    if (found)
        cout << "Appointment cancelled\n";
    else
        cout << "Not found\n";
}
void shedulewithbalance()
{

    ifstream file("patients.txt");
    ofstream temp("temp.txt");

    string line, pid;
    double cost;

    cout << "Enter Patient ID: ";
    cin >> pid;

    cout << "Enter Treatment Cost: ";
    cin >> cost;

    bool found = false;
    bool allowed = false;

    while (getline(file, line))
    {

        string part[6], word = "";
        int index = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;

        if (part[0] == pid)
        {

            found = true;

            double balance = 0;
            for (int i = 0; i < part[5].length(); i++)
            {
                balance = balance * 10 + (part[5][i] - '0');
            }

            if (balance >= cost)
            {
                balance = balance - cost;
                allowed = true;

                temp << part[0] << "#" << part[1] << "#" << part[2] << "#"
                     << part[3] << "#" << part[4] << "#" << balance << endl;
            }
            else
            {
                cout << "Insufficient balance\n";
                temp << line << endl;
            }
        }
        else
            temp << line << endl;
    }

    file.close();
    temp.close();

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (allowed)
    {
        cout << "Appointment allowed\n";
    }
}
void addtreatment()
{

    ofstream file("treatments.txt", ios::app);

    string pid, desc, cost;

    cout << "Enter Patient ID: ";
    cin >> pid;

    cout << "Enter Description: ";
    cin >> desc;

    cout << "Enter Cost: ";
    cin >> cost;

    file << pid << "#" << desc << "#" << cost << "#0" << endl;

    file.close();

    cout << "Treatment added\n";
}
void viewtreatments()
{

    ifstream file("treatments.txt");
    string line;

    cout << "\nTreatments:\n";

    while (getline(file, line))
    {
        cout << line << endl;
    }

    file.close();
}
void paytreatment()
{

    ifstream file("treatments.txt");
    ofstream temp("temp.txt");

    string line, pid;

    cout << "Enter Patient ID: ";
    cin >> pid;

    while (getline(file, line))
    {

        string part[4], word = "";
        int index = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;

        if (part[0] == pid)
        {
            temp << part[0] << "#" << part[1] << "#" << part[2] << "#1" << endl;
        }
        else
            temp << line << endl;
    }

    file.close();
    temp.close();

    remove("treatments.txt");
    rename("temp.txt", "treatments.txt");

    cout << "Payment updated\n";
}
void generatebill()
{

    ifstream file("treatments.txt");

    string line, pid;
    double total = 0;

    cout << "Enter Patient ID: ";
    cin >> pid;

    cout << "\nBill:\n";

    while (getline(file, line))
    {

        string part[4], word = "";
        int index = 0;

        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
            {
                part[index++] = word;
                word = "";
            }
            else
                word += line[i];
        }
        part[index] = word;

        if (part[0] == pid)
        {

            cout << part[1] << "  " << part[2] << endl;

            double cost = 0;
            for (int i = 0; i < part[2].length(); i++)
            {
                cost = cost * 10 + (part[2][i] - '0');
            }

            total += cost;
        }
    }

    cout << "Total = " << total << endl;

    file.close();
}
void searchname()
{

    ifstream file("patients.txt");

    string line, name;

    cout << "Enter Name: ";
    cin >> name;

    while (getline(file, line))
    {

        if (line.find(name) != -1)
        {
            cout << line << endl;
        }
    }

    file.close();
}
void searchspecial()
{

    ifstream file("doctors.txt");

    string line, sp;

    cout << "Enter Specialty: ";
    cin >> sp;

    while (getline(file, line))
    {

        if (line.find(sp) != -1)
        {
            cout << line << endl;
        }
    }

    file.close();
}
void sortdoctorsbyexp()
{

    int n = countdoctors();

    Doctor *d = new Doctor[n];

    loaddoctors(d, n);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {

            if (d[j].experience < d[j + 1].experience)
            {

                Doctor temp = d[j];
                d[j] = d[j + 1];
                d[j + 1] = temp;
            }
        }
    }

    cout << "\nSorted Doctors:\n";

    for (int i = 0; i < n; i++)
    {
        cout << d[i].doc_id << " " << d[i].name << " "
             << d[i].specialty << " " << d[i].experience << endl;
    }

    delete[] d;
}
void menu(Patient *p, int p_count, Doctor *d, int d_count)
{
    int choice;

    while (true)
    {
        cout << "\n==========================================\n";
        cout << "        HOSPITAL MANAGEMENT SYSTEM        \n";
        cout << "==========================================\n";
        cout << "1. Patient Management\n";
        cout << "2. Doctor Management\n";
        cout << "3. Appointments\n";
        cout << "4. Treatments & Billing\n";
        cout << "5. Search / Reports\n";
        cout << "6. Exit\n";
        cout << "==========================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int sub;
            while (true)
            {
                cout << "\n===== Patient Management =====\n";
                cout << "1. View All Patients\n";
                cout << "2. Add Patient\n";
                cout << "3. Update Patient\n";
                cout << "4. Delete Patient\n";
                cout << "5. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> sub;

                if (sub == 1)
                    showpatients(p, p_count);
                else if (sub == 2)
                    addpatient();
                else if (sub == 3)
                    updatepatient();
                else if (sub == 4)
                    deletepatient();
                else if (sub == 5)
                    break;
                else
                    cout << "Invalid choice\n";
            }
        }
        else if (choice == 2)
        {
            int sub;
            while (true)
            {
                cout << "\n===== Doctor Management =====\n";
                cout << "1. View All Doctors\n";
                cout << "2. Add Doctor\n";
                cout << "3. Update Doctor\n";
                cout << "4. Delete Doctor\n";
                cout << "5. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> sub;

                if (sub == 1)
                    showdoctors(d, d_count);
                else if (sub == 2)
                    adddoctor();
                else if (sub == 3)
                    updatedoctor();
                else if (sub == 4)
                    deletedoctor();
                else if (sub == 5)
                    break;
                else
                    cout << "Invalid choice\n";
            }
        }
        else if (choice == 3)
        {
            int sub;
            while (true)
            {
                cout << "\n===== Appointments =====\n";
                cout << "1. Schedule Appointment\n";
                cout << "2. View Appointments\n";
                cout << "3. Cancel Appointment\n";
                cout << "4. Check Balance & Schedule\n";
                cout << "5. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> sub;

                if (sub == 1)
                    addappointment();
                else if (sub == 2)
                    viewappointments();
                else if (sub == 3)
                    cancelappointment();
                else if (sub == 4)
                    shedulewithbalance();
                else if (sub == 5)
                    break;
                else
                    cout << "Invalid choice\n";
            }
        }
        else if (choice == 4)
        {
            int sub;
            while (true)
            {
                cout << "\n===== Treatments & Billing =====\n";
                cout << "1. Add Treatment\n";
                cout << "2. View Treatments\n";
                cout << "3. Update Payment Status\n";
                cout << "4. Generate Bill\n";
                cout << "5. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> sub;

                if (sub == 1)
                    addtreatment();
                else if (sub == 2)
                    viewtreatments();
                else if (sub == 3)
                    paytreatment();
                else if (sub == 4)
                    generatebill();
                else if (sub == 5)
                    break;
                else
                    cout << "Invalid choice\n";
            }
        }
        else if (choice == 5)
        {
            int sub;
            while (true)
            {
                cout << "\n===== Search / Reports =====\n";
                cout << "1. Search Patient by ID\n";
                cout << "2. Search Patient by Name\n";
                cout << "3. Search Doctor by Specialty\n";
                cout << "4. Sort Doctors by Experience\n";
                cout << "5. Back to Main Menu\n";
                cout << "Enter your choice: ";
                cin >> sub;

                if (sub == 1)
                    searchpatient(p, p_count);
                else if (sub == 2)
                    searchname();
                else if (sub == 3)
                    searchspecial();
                else if (sub == 4)
                    sortdoctorsbyexp();
                else if (sub == 5)
                    break;
                else
                    cout << "Invalid choice\n";
            }
        }
        else if (choice == 6)
        {
            cout << "Exiting system\n";
            break;
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }
}
int main()
{

    cleanpatients();
    cleandoctors();
    cleanAppointments();
    cleanTreatments();
    cleanBills();


    int p_count = countpatients();
    int d_count = countdoctors();


    Patient *p = new Patient[p_count];
    Doctor *d = new Doctor[d_count];

    loadpatients(p, p_count);
    loaddoctors(d, d_count);

    if (login())
    {
        menu(p, p_count, d, d_count);
    }

    delete[] p;
    delete[] d;

    return 0;
}