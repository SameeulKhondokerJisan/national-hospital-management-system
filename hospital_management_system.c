#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

/* =========================================================
   NATIONAL HOSPITAL & MEDICAL OPERATIONS MANAGEMENT SYSTEM
   ========================================================= */

/* ===================== STRUCTURES ===================== */

typedef struct {
    int id;
    char username[30];
    unsigned long password_hash;
} User;

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[100];
} Patient;

typedef struct {
    int id;
    char name[50];
    char specialization[50];
    float consultation_fee;
} Doctor;

typedef struct {
    int id;
    int patient_id;
    int doctor_id;
    char date[20];
} Appointment;

typedef struct {
    int id;
    char medicine_name[50];
    int quantity;
    float price;
    int reorder_level;
} Medicine;

typedef struct {
    int id;
    int patient_id;
    float treatment_cost;
    float medicine_cost;
    float total_bill;
    char timestamp[30];
} Bill;

/* ===================== UTILITIES ===================== */

unsigned long hashPassword(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

void logActivity(const char *msg) {
    FILE *fp = fopen("hospital_logs.txt", "a");
    if (!fp) return;
    time_t now = time(NULL);
    fprintf(fp, "%s - %s\n", ctime(&now), msg);
    fprintf(fp, "----------------------------------\n");
    fclose(fp);
}

/* ===================== AUTH ===================== */

void initializeAdmin() {
    FILE *fp = fopen("hospital_users.dat", "rb");
    if (fp) { fclose(fp); return; }

    fp = fopen("hospital_users.dat", "wb");
    User admin = {1, "admin", hashPassword("admin123")};
    fwrite(&admin, sizeof(User), 1, fp);
    fclose(fp);
}

int login() {
    char username[30], password[30];
    unsigned long hash;
    User u;

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    hash = hashPassword(password);

    FILE *fp = fopen("hospital_users.dat", "rb");
    if (!fp) return 0;

    while (fread(&u, sizeof(User), 1, fp)) {
        if (strcmp(u.username, username) == 0 && u.password_hash == hash) {
            fclose(fp);
            logActivity("Admin login successful.");
            return 1;
        }
    }

    fclose(fp);
    printf("Invalid credentials.\n");
    return 0;
}

/* ===================== PATIENT ===================== */

void addPatient() {
    FILE *fp = fopen("patients.dat", "ab");
    if (!fp) return;

    Patient p;
    printf("Patient ID: "); scanf("%d", &p.id);
    printf("Name: "); scanf(" %[^\n]", p.name);
    printf("Age: "); scanf("%d", &p.age);
    printf("Gender: "); scanf("%s", p.gender);
    printf("Disease: "); scanf(" %[^\n]", p.disease);

    fwrite(&p, sizeof(Patient), 1, fp);
    fclose(fp);
    logActivity("Patient added.");
}

void viewPatients() {
    FILE *fp = fopen("patients.dat", "rb");
    if (!fp) return;

    Patient p;
    printf("\n--- Patient Records ---\n");
    while (fread(&p, sizeof(Patient), 1, fp)) {
        printf("ID:%d | %s | Age:%d | %s | Disease:%s\n",
               p.id, p.name, p.age, p.gender, p.disease);
    }
    fclose(fp);
}

/* ===================== DOCTOR ===================== */

void addDoctor() {
    FILE *fp = fopen("doctors.dat", "ab");
    if (!fp) return;

    Doctor d;
    printf("Doctor ID: "); scanf("%d", &d.id);
    printf("Name: "); scanf(" %[^\n]", d.name);
    printf("Specialization: "); scanf(" %[^\n]", d.specialization);
    printf("Consultation Fee: "); scanf("%f", &d.consultation_fee);

    fwrite(&d, sizeof(Doctor), 1, fp);
    fclose(fp);
    logActivity("Doctor added.");
}

void viewDoctors() {
    FILE *fp = fopen("doctors.dat", "rb");
    if (!fp) return;

    Doctor d;
    printf("\n--- Doctor Records ---\n");
    while (fread(&d, sizeof(Doctor), 1, fp)) {
        printf("ID:%d | %s | %s | Fee:%.2f\n",
               d.id, d.name, d.specialization, d.consultation_fee);
    }
    fclose(fp);
}

/* ===================== APPOINTMENT ===================== */

void createAppointment() {
    FILE *fp = fopen("appointments.dat", "ab");
    if (!fp) return;

    Appointment a;
    printf("Appointment ID: "); scanf("%d", &a.id);
    printf("Patient ID: "); scanf("%d", &a.patient_id);
    printf("Doctor ID: "); scanf("%d", &a.doctor_id);
    printf("Date (DD/MM/YYYY): "); scanf("%s", a.date);

    fwrite(&a, sizeof(Appointment), 1, fp);
    fclose(fp);
    logActivity("Appointment created.");
}

/* ===================== PHARMACY ===================== */

void addMedicine() {
    FILE *fp = fopen("medicines.dat", "ab");
    if (!fp) return;

    Medicine m;
    printf("Medicine ID: "); scanf("%d", &m.id);
    printf("Medicine Name: "); scanf(" %[^\n]", m.medicine_name);
    printf("Quantity: "); scanf("%d", &m.quantity);
    printf("Price: "); scanf("%f", &m.price);
    printf("Reorder Level: "); scanf("%d", &m.reorder_level);

    fwrite(&m, sizeof(Medicine), 1, fp);
    fclose(fp);
    logActivity("Medicine added.");
}

void viewMedicines() {
    FILE *fp = fopen("medicines.dat", "rb");
    if (!fp) return;

    Medicine m;
    printf("\n--- Medicine Inventory ---\n");
    while (fread(&m, sizeof(Medicine), 1, fp)) {
        printf("ID:%d | %s | Qty:%d | Price:%.2f",
               m.id, m.medicine_name, m.quantity, m.price);
        if (m.quantity <= m.reorder_level)
            printf("  **LOW STOCK**");
        printf("\n");
    }
    fclose(fp);
}

/* ===================== BILLING ===================== */

void generateBill() {
    FILE *fp = fopen("bills.dat", "ab");
    if (!fp) return;

    Bill b;
    printf("Bill ID: "); scanf("%d", &b.id);
    printf("Patient ID: "); scanf("%d", &b.patient_id);
    printf("Treatment Cost: "); scanf("%f", &b.treatment_cost);
    printf("Medicine Cost: "); scanf("%f", &b.medicine_cost);

    b.total_bill = b.treatment_cost + b.medicine_cost;

    time_t now = time(NULL);
    strcpy(b.timestamp, ctime(&now));

    fwrite(&b, sizeof(Bill), 1, fp);
    fclose(fp);

    printf("Total Bill: %.2f\n", b.total_bill);
    logActivity("Bill generated.");
}

/* ===================== ANALYTICS ===================== */

void revenueAnalytics() {
    FILE *fp = fopen("bills.dat", "rb");
    if (!fp) return;

    Bill b;
    float arr[500];
    int n = 0;

    while (fread(&b, sizeof(Bill), 1, fp) && n < 500) {
        arr[n++] = b.total_bill;
    }
    fclose(fp);

    if (n == 0) {
        printf("No billing data.\n");
        return;
    }

    float sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    float mean = sum / n;

    float variance = 0;
    for (int i = 0; i < n; i++)
        variance += pow(arr[i] - mean, 2);
    variance /= n;

    float std = sqrt(variance);

    printf("\n--- Revenue Analytics ---\n");
    printf("Total Bills: %d\n", n);
    printf("Average Bill: %.2f\n", mean);
    printf("Variance: %.2f\n", variance);
    printf("Standard Deviation: %.2f\n", std);

    logActivity("Revenue analytics generated.");
}

/* ===================== MAIN ===================== */

int main() {
    initializeAdmin();

    printf("=== NATIONAL HOSPITAL MANAGEMENT SYSTEM ===\n");

    if (!login()) return 0;

    int choice;

    while (1) {
        printf("\n1.Add Patient\n");
        printf("2.View Patients\n");
        printf("3.Add Doctor\n");
        printf("4.View Doctors\n");
        printf("5.Create Appointment\n");
        printf("6.Add Medicine\n");
        printf("7.View Medicines\n");
        printf("8.Generate Bill\n");
        printf("9.Revenue Analytics\n");
        printf("10.Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: addDoctor(); break;
            case 4: viewDoctors(); break;
            case 5: createAppointment(); break;
            case 6: addMedicine(); break;
            case 7: viewMedicines(); break;
            case 8: generateBill(); break;
            case 9: revenueAnalytics(); break;
            case 10:
                logActivity("System exited.");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}