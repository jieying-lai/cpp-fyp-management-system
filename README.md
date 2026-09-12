<div align="center">

  # 🎓 Student Final Year Project (FYP) Management & Grading System

  **A terminal-based academic workflow platform engineered in Pure C++, featuring project registry tracking, dual-evaluator score arbitration, and file-based data persistence.**

  [![C++](https://img.shields.io/badge/C%2B%2B-11%20%7C%20Standard-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)](#)
  [![IDE](https://img.shields.io/badge/IDE-Dev--C%2B%2B%205.11%20%7C%206.3-4B8BBE?style=flat-square)](#)
  [![Compiler](https://img.shields.io/badge/Compiler-TDM--GCC%20%2F%20MinGW-blue?style=flat-square)](#)
  [![Persistence](https://img.shields.io/badge/Storage-File%20I%2FO%20(.txt)-lightgrey?style=flat-square)](#)

</div>

---

## 📌 Project Overview

Coordinating undergraduate Final Year Projects (FYP) requires close synchronization between faculty supervisors, independent moderators, and students. Manual administration across topic allocation and independent double-blind evaluation often leads to score discrepancies, allocation collisions, and administrative delays.

Engineered for the **UECS1104 Programming and Problem Solving** curriculum at **Universiti Tunku Abdul Rahman (UTAR)**, this system automates end-to-end project registration, student shortlisting, and assessment moderation for the Department of Computing (DC) within the Lee Kong Chian Faculty of Engineering and Science (LKCFES).

Constructed in **Pure C++** using the **Bloodsheed / Embarcadero Dev-C++** environment, the project highlights structured programming fundamentals, composite records using arrays of structures, defensive stream input parsing, and reliable text-file persistence.

---

## ✨ Core System Modules

### 1. 📋 FYP Title & Registration Module
* **Faculty Project Administration**: Lecturers can create, query, and update research project offerings with supervisor assignments.
* **Historical Topic Seed Database**: Pre-populated with at least 30 historical project titles proposed by faculty from the Department of Computing.
* **Student Discovery & Shortlisting**: Undergraduates can browse available project titles, filter by domain/supervisor, and shortlist candidate projects of interest.
* **Registration & Conflict Prevention**: Lecturers review student selections, assign candidates to confirmed project titles, and lock allocations to prevent duplicate assignments.

### 2. ⚖️ Dual-Examiner Grading & Score Arbitration Engine
* **Independent Dual-Evaluation Entry**: Captures separate marks across FYP 1 and FYP 2 milestones from both the **Project Supervisor** and the **Faculty Moderator**.
* **Automated Score Arbitration ($\Delta > 5$)**:
  * Automatically calculates total score aggregates and arithmetic means between both evaluators.
  * Dynamically computes score variance:
    $$\Delta = |\text{Score}_{\text{Supervisor}} - \text{Score}_{\text{Moderator}}|$$
  * When $\Delta > 5$, the system triggers an explicit **Moderation Discrepancy Flag**, highlighting records that require academic committee arbitration.
* **Academic Analytics & Performance Distribution**: Generates cohort-wide grade summaries, computing distinctions, pass distributions, failures, and class performance metrics.

---

### Key Data Structures

* **`struct FYPTitle`**: Holds project identifiers, topic title, faculty supervisor, field/domain, and allocation state.
* **`struct Student`**: Records student matriculation ID, candidate name, shortlisted project identifiers, and confirmed allocation.
* **`struct GradeRecord`**: Manages project-to-student bindings, individual supervisor marks, moderator marks, final averaged grade, and discrepancy alerts.

---

## ⚙️ Development Environment & Requirements

* **IDE**: Embarcadero Dev-C++ 6.3 or Bloodshed Dev-C++ 5.11
* **Bundled Compiler**: TDM-GCC / MinGW 64-bit (GCC 4.9.2 or higher)
* **Language Standard**: ISO C++11 or C++14
* **Standard Libraries**: `<iostream>`, `<fstream>`, `<iomanip>`, `<string>`, `<cmath>`

---

## 🚀 How to Run in Dev-C++

### Option A: Using Dev-C++ (Recommended GUI Workflow)

1. **Clone or Download the Repository:**
```bash
git clone [https://github.com/jieying-lai/cpp-fyp-management-system.git](https://github.com/jieying-lai/cpp-fyp-management-system.git)

```


2. **Open the Project / Source File:**
* Launch **Dev-C++**.
* Go to **File** $\rightarrow$ **Open**, navigate to the project directory, and select `main.cpp` (or the `.dev` project file if available).


3. **Verify Compiler Settings (C++11 Support):**
* Navigate to **Tools** $\rightarrow$ **Compiler Options**.
* Under the **Settings** tab $\rightarrow$ **Code Generation**, ensure **Language standard (-std)** is set to **ISO C++11** (or add `-std=c++11` to the compiler flags).


4. **Compile & Execute:**
* Press **`F11`** (or click **Execute** $\rightarrow$ **Compile & Run**).
* The console window will launch automatically. Ensure the `.txt` data files remain inside the working directory alongside the executable.



---

### Option B: Terminal Command-Line Build (MinGW / GCC)

If compiling directly via the command prompt:

```cmd
g++ -std=c++11 src/main.cpp -o fyp_system.exe
fyp_system.exe

```

---

## 👥 Collaborative Engineering

Developed as a coursework group assignment for **UECS1104 Programming and Problem Solving** 

* **System Design & Flow Control**: Flowchart planning, menu hierarchies, and defensive user-input parsing.
* **Title & Registration Engine**: Implementation of project search filtering, candidate shortlisting, and structural file synchronization.
* **Grading & Arbitration Engine**: Design of mark input matrices, score discrepancy detection algorithms ($\Delta > 5$), and performance summary statistics.

---
