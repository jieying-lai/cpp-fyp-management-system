<div align="center">

  # 🎓 Student Final Year Project (FYP) Management & Grading System

  **A terminal-based academic workflow platform engineered in Pure C++, featuring project registry tracking, dual-evaluator score arbitration, and file-based data persistence.**

  [![C++](https://img.shields.io/badge/C%2B%2B-11%20%7C%2014%20%7C%2017-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)](#)
  [![Paradigm](https://img.shields.io/badge/Paradigm-Structured%20%26%20Procedural-lightgrey?style=flat-square)](#)
  [![Persistence](https://img.shields.io/badge/Storage-File%20I%2FO%20(.txt)-blue?style=flat-square)](#)

</div>

---

## 📌 Project Overview

Coordinating undergraduate Final Year Projects (FYP) requires close synchronization between faculty supervisors, independent moderators, and students. Manual administration across topic allocation and independent double-blind evaluation often leads to score discrepancies, allocation collisions, and administrative delays.

Engineered for the **UECS1104 Programming and Problem Solving** curriculum at **Universiti Tunku Abdul Rahman (UTAR)**, this system automates end-to-end project registration, student shortlisting, and assessment moderation for the Department of Computing (DC) within the Lee Kong Chian Faculty of Engineering and Science (LKCFES).

Constructed in **Pure C++** without external library dependencies, the project highlights structured programming fundamentals, composite records using arrays of structures, defensive stream input parsing, and reliable text-file persistence.

---

## ✨ Core System Modules

### 1. 📋 FYP Title & Registration Module
* **Faculty Project Administration**: Lecturers can create, query, and update research project offerings with supervisor assignments.
* **Historical Topic Seed Database**: Pre-populated with at least 30 historical project titles proposed by faculty from the Department of Computing.
* **Student Discovery & Shortlisting**: Undergraduates can browse available project titles, filter by domain/supervisor, and shortlist candidate projects of interest.
* **Registration & Conflict Prevention**: Lecturers review student selections, assign candidates to confirmed project titles, and lock allocations to prevent double-booking.

### 2. ⚖️ Dual-Examiner Grading & Score Arbitration Engine
* **Independent Dual-Evaluation Entry**: Captures separate marks across FYP 1 and FYP 2 milestones from both the **Project Supervisor** and the **Faculty Moderator**.
* **Automated Score Arbitration ($\Delta > 5$)**:
  * Automatically calculates total score aggregates and arithmetic means between both evaluators.
  * Dynamically computes variance:
    $$\Delta = \vert{}\text{Score}_{\text{Supervisor}} - \text{Score}_{\text{Moderator}}\vert{}$$
  * When $\Delta > 5$, the system triggers an explicit **Moderation Discrepancy Flag**, highlighting records that require academic committee arbitration.
* **Academic Analytics & Performance Distribution**: Generates cohort-wide grade summaries, computing distinctions, pass distributions, failures, and class performance metrics.

---

### Key Data Structures

* **`struct FYPTitle`**: Holds project identifiers, topic title, faculty supervisor, field/domain, and availability state.
* **`struct Student`**: Records student matriculation ID, candidate name, shortlisted project identifiers, and confirmed allocation.
* **`struct GradeRecord`**: Manages project-to-student bindings, individual supervisor marks, moderator marks, final averaged grade, and discrepancy alerts.

---

## ⚙️ System Requirements

* **Compiler**: Any standard C++ compiler with C++11 support or newer (`g++`, `clang++`, or MSVC).
* **Environment**: Windows Command Prompt / PowerShell, macOS Terminal, or Linux Bash.
* **Dependencies**: Native C++ standard libraries only (`<iostream>`, `<fstream>`, `<iomanip>`, `<string>`, `<cmath>`).

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone [https://github.com/jieying-lai/cpp-fyp-management-system.git](https://github.com/jieying-lai/cpp-fyp-management-system.git)
cd cpp-fyp-management-system

```

### 2. Compilation

Compile all source files into a single binary using `g++`:

```bash
g++ -std=c++11 src/*.cpp -o fyp_system

```

*(Alternatively, if running as a single consolidated source file: `g++ -std=c++11 main.cpp -o fyp_system`)*

### 3. Execution

* **Windows**:
```cmd
fyp_system.exe

```


* **Linux / macOS**:
```bash
./fyp_system

```



---

## 👥 Collaborative Engineering

Developed as a coursework group assignment for **UECS1104 Programming and Problem Solving**.

* **System Design & Flow Control**: Flowchart planning, menu hierarchies, and defensive user-input loops.
* **Title & Registration Engine**: Implementation of project search filtering, candidate shortlisting, and structural file synchronization.
* **Grading & Arbitration Engine**: Design of mark input matrices, score discrepancy detection algorithms ($\Delta > 5$), and performance summary statistics.

---
