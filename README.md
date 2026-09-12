<div align="center">

  # 🎓 Student Final Year Project (FYP) Management System

  **A terminal-based academic project lifecycle and grading automation system built in Pure C++, featuring dual-examiner arbitration algorithms and custom struct-based file persistence.**

  [![C++](https://img.shields.io/badge/C%2B%2B-11%20%7C%2014%20%7C%2017-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)](#)
  [![Paradigm](https://img.shields.io/badge/Paradigm-Structured%20%26%20Procedural-lightgrey?style=flat-square)](#)
  [![Storage](https://img.shields.io/badge/Persistence-File%20I%2FO%20(.txt)-blue?style=flat-square)](#)
  [![Coursework](https://img.shields.io/badge/UTAR-UECS1004%20%2F%20UECS1104-blueviolet?style=flat-square)](#)

</div>

---

## 📌 Project Overview

At tertiary institutions, coordinating undergraduate Final Year Projects (FYP) requires alignment between academic supervisors, independent moderators, and students. Manual evaluation often leads to score discrepancies and administrative bottlenecks.

Engineered for the **UECS1104 Programming and Problem Solving** coursework at **Universiti Tunku Abdul Rahman (UTAR)**, this system automates project allocation, student shortlisting, and assessment moderation for the Department of Computing (DC), Faculty of Engineering and Science (LKCFES).

The entire application is written in **Pure C++** without third-party frameworks, highlighting structured procedural design, custom record data structures, defensive input validation, and plain-text persistence.

---

## ✨ Core System Modules

### 1. 📋 FYP Title & Registration Module
* **Faculty Project Administration**: Lecturers can propose new FYP research titles, modify project descriptions, and search the repository by title or domain.
* **Student Discovery & Shortlisting**: Undergraduates can browse pre-seeded historical research titles, query matching topics, and shortlist preferences.
* **Student Allocation**: Lecturers confirm student registrations and lock titles against duplicate selections.

### 2. ⚖️ Dual-Examiner FYP Grading & Arbitration Engine
* **Independent Grading Entry**: Captures separate assessment scores (across FYP 1 and FYP 2 phases) from both the **Project Supervisor** and the **External Moderator**.
* **Automated Score Arbitration ($\Delta > 5$)**: 
  * Computes arithmetic mean benchmarks across both evaluators.
  * Dynamically evaluates variance: if $\vert{} \text{Score}_{\text{Supervisor}} - \text{Score}_{\text{Moderator}} \vert{} > 5$, the system triggers an automated **Moderation Variance Warning** to prompt academic arbitration.
* **Academic Analytics & Result Summaries**: Generates cohort-wide performance distributions, calculating distinctions, passing cohorts, failures, and overall grade statistics.

---
