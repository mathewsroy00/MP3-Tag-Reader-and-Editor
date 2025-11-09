# 🎧 MP3 Tag Reader & Editor

A **C-based command-line application** that reads and edits ID3v2 metadata tags in MP3 files.

---

## 🚀 Project Overview
Many MP3 files store hidden metadata — such as **title, artist, album, year, and genre** — in ID3 tags.  
Manually editing this data across multiple files can be tedious and error-prone.  

This project provides a **simple and efficient way** to **view and modify MP3 metadata directly** from the terminal, using fundamental C programming concepts like file handling and endianness management.

---

## ⚙️ Features
- **View Metadata:** Displays information such as *Title, Artist, Album, Year, Genre,* and *Comment*.  
- **Edit Tags:** Modify individual metadata fields directly from the **command line** using tag options (`-t`, `-a`, `-A`, `-y`, `-g`, `-c`).  
- **File Validation:** Verifies whether the given file contains a valid **ID3v2 tag** before performing operations.  
- **Endianness Handling:** Handles byte-order conversions for accurate cross-platform data processing.  
- **Error Handling:** Detects invalid arguments, missing files, or unsupported tags with clear error messages.  
- **Modular Design:** Organized into multiple source files (`main.c`, `view.c`, `edit.c`, `header.h`) for clean and maintainable code.  

---

## 🧠 Key Concepts & Challenges
- **Advanced File I/O in C:** Used `fseek()`, `fread()`, and `fwrite()` for low-level file operations.  
- **Binary Data Manipulation:** Extracted and modified ID3v2 metadata frames stored in binary format.  
- **Endianness Control:** Implemented byte-order handling to ensure consistent tag size interpretation across systems.  
- **Metadata Integrity:** Ensured that only tag data is modified — the audio stream remains untouched.  
- **Robust Input Validation:** Built safe argument parsing to handle invalid or missing parameters gracefully.

---

## 📂 File Structure
- `main.c` – Handles command-line arguments and overall program flow  
- `view.c` – Contains functions to read and display MP3 metadata  
- `edit.c` – Contains functions to modify and update metadata fields  
- `header.h` – Header file with function declarations, macros, and structures  
- `sample.mp3` – Example MP3 file for testing (optional)  

---

## 📈 Future Enhancements
- Support for additional tag versions (ID3v1, ID3v2.4)  
- Add functionality for **batch editing** multiple MP3 files  
- Create a **GUI-based version** for easier interaction  
- Include a **metadata backup/restore** feature  

---
