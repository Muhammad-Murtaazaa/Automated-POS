# 🚀 Point of Sale (POS) System - Version 1.0

![CLI Based](https://img.shields.io/badge/CLI-Based-blue)
![Open Source](https://img.shields.io/badge/Open-Source-green)
![C++](https://img.shields.io/badge/Language-C%2B%2B-red)
![License](https://img.shields.io/badge/License-MIT-brightgreen)

A command-line interface (CLI) Point of Sale system designed for efficient inventory management and billing operations. Developed using C++ and core data structures.

---

## 📌 Project Overview

### 🔹 Core Features:
- **🛒 Inventory Management** using singly linked lists
- **🧾 Billing System** using queues
- **⏪ Undo/Redo Operations** with stacks
- **🤖 Auto-Pilot Mode** for automated customer processing
- **📂 File Handling** for persistent data storage
- **📝 Feedback System** for customer input

---

## 🚀 Key Features

### 📦 Inventory Management
- ➕ Add/Remove products
- ✏️ Update product details (name, price, stock)
- 💰 Apply product-specific discounts
- 📊 Real-time stock display
- 💾 Auto-save to `inventory.txt`

### 💵 Billing System
- ➕ Add/Remove items from bill
- 🏷️ Tax calculation (10%)
- 👀 Bill preview & finalization
- 💳 Multiple payment methods
- 💾 Auto-save bills to `bill.txt`

### ⏪ Undo/Redo Functionality
- 🔄 Reverse/add recent actions:
  - ➕ Product additions
  - ❌ Product removals

### 🤖 Auto-Pilot Mode
- 🏬 Sequential customer processing
- 🔄 Automatic stock updates
- 📝 Feedback collection
- 🔑 Admin password protected exit
- 💾 Data auto-saving

### 📝 Feedback System
- 🗣️ Collect customer feedback
- 📄 Store in `feedback.txt`
- 🖥️ Simple interface

---

## 🛠 Technologies Used

- **C++17** (OOP Paradigm)
- **Data Structures**:
  - 📌 Singly Linked List (Inventory)
  - 📌 Queue (Billing)
  - 📌 Stack (Undo/Redo)
- **File Handling** for data persistence
- 📚 Standard Template Library (STL)

---

## 🚨 Important Notes

- **🔑 Admin Password**: `1234` (for Auto-Pilot Mode)
- **📂 Data Files**:
  - `inventory.txt`
  - `bill.txt`
  - `feedback.txt`

---

## 🛠 Setup Instructions

### 1️⃣ Requirements:
- 🖥️ C++ Compiler (g++ recommended)
- 💻 Terminal/Command Prompt

### 2️⃣ Compilation:
```bash
g++ PointOfSaleSystem.cpp -o posystem
```

## 📖 Usage Guide

### 📌 Main Menu Navigation

- 🛍️ **Product Management**
- 🧾 **Billing System**
- 🤖 **Auto-Pilot Mode**
- ℹ️ **System Info**

## 📦 Product Management

- ➕ **Add/Remove products**
- ✏️ **Update stock/prices**
- 💰 **Apply discounts**
- 📊 **View inventory**

## 💵 Billing Process

- 🛒 **Scan products**
- 🔢 **Modify quantities**
- 💳 **Multiple payment options**
- 📄 **Digital receipt generation**

## 🤖 Auto-Pilot Mode

- 🔄 **Automated customer handling**
- 📝 **Feedback collection**
- 🔐 **Admin password protected exit**

## 🔮 Future Enhancements

### 🚀 Planned Features

- 🖥️ **GUI implementation**
- 🗄️ **Database integration**
- 📊 **Sales analytics/reporting**
- 👥 **Multi-user support**
- 📡 **Barcode scanning**
- 🎟️ **Customer loyalty programs**

### 💡 Potential Improvements

- 🔍 **Enhanced input validation**
- 🔐 **Cryptographic password storage**
- 📂 **JSON data storage**
- 🌍 **Multi-language support**
- ☁️ **Cloud backup integration**

## 🤝 Contributing

We welcome contributions! Follow these steps:

1. Fork the repository
2. Create a feature branch:
   ```sh
   git checkout -b feature/your-feature
   ```
3. Commit changes
4. Push to branch
5. Create a Pull Request

### ⚡ Guidelines:

- ✅ Maintain clean code structure
- 📌 Add comments for complex logic
- 📝 Update documentation accordingly
- 🛠️ Test changes thoroughly

## 📜 License

This project is open-source under the MIT License. See [LICENSE](LICENSE) for details.

📢 **Note:** This is Version 1.0. Report issues and suggest improvements through GitHub issues.
