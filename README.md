# National Hospital & Medical Operations Management System

## Overview
The National Hospital & Medical Operations Management System is a console-based healthcare management application written in C. The system simulates the core operations of a hospital including patient records, doctor management, appointment scheduling, pharmacy inventory, billing, and revenue analytics.

The system also includes authentication, logging, and file-based data storage to maintain hospital records.

## Features

### Authentication System
- Admin login with username and password
- Password hashing for security
- Automatic administrator initialization

### Patient Management
- Add patient records
- View patient information
- Store patient demographics and disease details

### Doctor Management
- Add doctor profiles
- View doctor records
- Track specialization and consultation fees

### Appointment Management
- Schedule appointments between patients and doctors
- Maintain appointment records with dates

### Pharmacy Inventory
- Add medicines to inventory
- Track medicine quantities and pricing
- Automatic low-stock alerts when inventory falls below reorder level

### Billing System
- Generate patient bills
- Combine treatment and medicine costs
- Record billing timestamps

### Revenue Analytics
The system analyzes billing data and provides statistical insights including:

- Total number of bills
- Average bill amount
- Variance
- Standard deviation

### Activity Logging
System operations are logged including:

- Admin login
- Patient registration
- Doctor additions
- Appointment scheduling
- Medicine inventory updates
- Billing generation
- Analytics generation
- System exit

## Technologies Used
- C Programming Language
- Standard C Libraries
- File-based persistent storage

## System Data Files

| File | Purpose |
|-----|-----|
| hospital_users.dat | Authentication records |
| patients.dat | Patient data |
| doctors.dat | Doctor records |
| appointments.dat | Appointment data |
| medicines.dat | Pharmacy inventory |
| bills.dat | Billing records |
| hospital_logs.txt | System activity logs |

## Default Admin Login

Username: admin  
Password: admin123

## Program Menu

1. Add Patient  
2. View Patients  
3. Add Doctor  
4. View Doctors  
5. Create Appointment  
6. Add Medicine  
7. View Medicines  
8. Generate Bill  
9. Revenue Analytics  
10. Exit  

## Learning Objectives

This project demonstrates:

- Hospital management system design
- File handling in C
- Authentication using hashing
- Healthcare workflow simulation
- Inventory management
- Billing systems
- Statistical analytics
- Console-based management applications

## Author
Jisan
