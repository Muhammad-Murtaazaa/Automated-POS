// #include <iostream>
// #include <string>
// #include <vector>
// #include <fstream>
// #include <iomanip>
// #include <ctime>

// using namespace std;

// // Stack for undo/redo operations
// template <typename T>
// class Stack {
// private:
//     vector<T> stack;
// public:
//     void push(T data) {
//         stack.push_back(data);
//     }

//     T pop() {
//         if (stack.empty()) {
//             return nullptr;
//         }
//         T data = stack.back();
//         stack.pop_back();
//         return data;
//     }

//     bool isEmpty() {
//         return stack.empty();
//     }

//     T top() {
//         if (!stack.empty()) {
//             return stack.back();
//         }
//         return nullptr;
//     }
// };

// class Inventory 
// {
// public:
//     int id, price, quantity;
//     string name;
//     Inventory* next;
//     Inventory* prev;

//     Inventory()
//     {
//         id = price = quantity = 0;
//         name = "";
//         next = prev = nullptr;
//     }

//     void addItem(Inventory*& head, Stack<Inventory*>& undoStack);
//     void deleteItem(Inventory*& head, int id, Stack<Inventory*>& undoStack);
//     void showInventory(Inventory* head);
//     void updateItem(Inventory* head, int id);
// };

// class BillItem 
// {
// public:
//     int id, quantity, price;
//     string name;
//     double total;
// };
// class Billing {
// private:
//     vector<BillItem> billItems;
//     double totalAmount;

// public:
//     Billing() : totalAmount(0.0) {}

//     void addItem(Inventory*& head, int id, int quantity, Stack<Inventory*>& undoStack);
//     void removeItem(int id);
//     void generateBill(const string& username);
//     void displayBill();
// };

// // Feedback Class
// class Feedback {
// private:
//     string name, phone, email, suggestions;
//     int rating;

// public:
//     void addFeedback();
//     void viewFeedbacks();
// };

// // User Class
// class User {
// public:
//     string name, phone, email;

//     void registerUser();
//     void loginUser(string& username);
// };

// // Sales Tracker Class
// class SalesTracker {
// private:
//     double totalSales;

// public:
//     SalesTracker() : totalSales(0.0) {}

//     void updateSales(double amount);
//     double getTotalSales() { return totalSales; }
// };

// // Methods for Inventory Management
// void Inventory::addItem(Inventory*& head, Stack<Inventory*>& undoStack) {
//     Inventory* newItem = new Inventory();
//     cout << "Enter ID: ";
//     cin >> newItem->id;
//     cout << "Enter Name: ";
//     cin >> newItem->name;
//     cout << "Enter Price: ";
//     cin >> newItem->price;
//     cout << "Enter Quantity: ";
//     cin >> newItem->quantity;

//     // Push the pointer of the newItem to undo stack
//     undoStack.push(newItem);

//     // Add new item to inventory
//     if (head == nullptr) {
//         head = newItem;
//     } else {
//         Inventory* temp = head;
//         while (temp->next != nullptr) {
//             temp = temp->next;
//         }
//         temp->next = newItem;
//         newItem->prev = temp;
//     }

//     cout << "Item added successfully!\n";
// }

// void Inventory::deleteItem(Inventory*& head, int id, Stack<Inventory*>& undoStack) {
//     Inventory* temp = head;
//     while (temp != nullptr && temp->id != id) {
//         temp = temp->next;
//     }

//     if (temp == nullptr) {
//         cout << "Item not found.\n";
//         return;
//     }


//     undoStack.push(temp);
//     if (temp->prev != nullptr) 
//     {
//         temp->prev->next = temp->next;
//     } else 
//     {
//         head = temp->next;
//     }
//     if (temp->next != nullptr) 
//     {
//         temp->next->prev = temp->prev;
//     }

//     delete temp;
//     cout << "Item deleted successfully!\n";
// }

// void Inventory::showInventory(Inventory* head) {
//     if (head == nullptr) {
//         cout << "Inventory is empty.\n";
//         return;
//     }

//     // Print the table header
//     cout << left << setw(10) << "ID"
//          << setw(20) << "Name"
//          << setw(10) << "Price"
//          << setw(10) << "Quantity" << endl;
//     cout << string(50, '-') << endl;

//     // Print each inventory item in a tabular format
//     Inventory* temp = head;
//     while (temp != nullptr) {
//         cout << left << setw(10) << temp->id
//              << setw(20) << temp->name
//              << setw(10) << temp->price
//              << setw(10) << temp->quantity << endl;
//         temp = temp->next;
//     }
// }

// void Inventory::updateItem(Inventory* head, int id) {
//     Inventory* temp = head;
//     while (temp != nullptr && temp->id != id) {
//         temp = temp->next;
//     }

//     if (temp == nullptr) {
//         cout << "Item not found.\n";
//         return;
//     }

//     cout << "Enter new Name: ";
//     cin >> temp->name;
//     cout << "Enter new Price: ";
//     cin >> temp->price;
//     cout << "Enter new Quantity: ";
//     cin >> temp->quantity;
//     cout << "Item updated successfully!\n";
// }

// // Methods for Billing
// void Billing::addItem(Inventory*& head, int id, int quantity, Stack<Inventory*>& undoStack) {
//     Inventory* temp = head;
//     while (temp != nullptr && temp->id != id) {
//         temp = temp->next;
//     }
//     if (temp != nullptr && temp->quantity >= quantity) {
//         BillItem item;
//         item.id = id;
//         item.name = temp->name;
//         item.price = temp->price;
//         item.quantity = quantity;
//         item.total = temp->price * quantity;
//         billItems.push_back(item);

//         // Update total amount
//         totalAmount += item.total;

//         temp->quantity -= quantity;
//         cout << "Item added to bill.\n";
//     } else {
//         cout << "Item not available or insufficient quantity.\n";
//     }
// }

// void Billing::removeItem(int id) {
//     auto it = billItems.begin();
//     while (it != billItems.end()) {
//         if (it->id == id) {
//             totalAmount -= it->total;
//             billItems.erase(it);
//             cout << "Item removed from bill.\n";
//             return;
//         }
//         ++it;
//     }
//     cout << "Item not found in bill.\n";
// }

// void Billing::generateBill(const string& username) {
//     ofstream outFile(username + "_bill.txt");
//     outFile << "Bill for " << username << "\n";
//     outFile << "----------------------------------------\n";
//     outFile << left << setw(10) << "ID"
//             << setw(20) << "Name"
//             << setw(10) << "Price"
//             << setw(10) << "Quantity"
//             << setw(10) << "Total" << endl;
//     outFile << string(60, '-') << endl;

//     for (const auto& item : billItems) {
//         outFile << left << setw(10) << item.id
//                 << setw(20) << item.name
//                 << setw(10) << item.price
//                 << setw(10) << item.quantity
//                 << setw(10) << item.total << endl;
//     }
//     outFile << string(60, '-') << endl;
//     outFile << "Total Amount: $" << totalAmount << endl;
//     cout << "Bill generated and saved to file.\n";
// }

// // Methods for Feedback
// void Feedback::addFeedback() {
//     cout << "Enter your name: ";
//     cin >> name;
//     cout << "Enter your phone: ";
//     cin >> phone;
//     cout << "Enter your email: ";
//     cin >> email;
//     cout << "Enter your feedback: ";
//     cin >> suggestions;
//     cout << "Enter rating (1-5): ";
//     cin >> rating;

//     // Save feedback to file
//     ofstream outFile("feedbacks.txt", ios::app);
//     outFile << "Name: " << name << "\n";
//     outFile << "Phone: " << phone << "\n";
//     outFile << "Email: " << email << "\n";
//     outFile << "Feedback: " << suggestions << "\n";
//     outFile << "Rating: " << rating << "\n";
//     outFile << "----------------------------------------\n";
//     cout << "Thank you for your feedback!\n";
// }

// void Feedback::viewFeedbacks() {
//     ifstream inFile("feedbacks.txt");
//     if (!inFile) {
//         cout << "No feedbacks available.\n";
//         return;
//     }
//     string line;
//     while (getline(inFile, line)) {
//         cout << line << endl;
//     }
// }

// // Methods for User
// void User::registerUser() {
//     cout << "Enter your name: ";
//     cin >> name;
//     cout << "Enter your phone: ";
//     cin >> phone;
//     cout << "Enter your email: ";
//     cin >> email;
// }

// void User::loginUser(string& username) {
//     cout << "Enter your username: ";
//     cin >> username;
// }

// // Methods for Sales Tracker
// void SalesTracker::updateSales(double amount) {
//     totalSales += amount;
// }

// int main() {
//     Inventory* head = nullptr;
//     Stack<Inventory*> undoStack;
//     SalesTracker salesTracker;
//     Billing billing;
//     Feedback feedback;
//     User user;
//     string username;

//     int choice;
//     while (true) {
//         cout << "\n1. Admin Panel\n2. User Panel\n3. Exit\nEnter your choice: ";
//         cin >> choice;
//     Inventory inv; // Declare outside switch
//         switch (choice) {
//         case 1: // Admin Panel
            
//             while (true) {
//                 cout << "\nAdmin Menu:\n1) Add Item\n2) Delete Item\n3) Show Inventory\n4) Exit\n";
//                 cin >> choice;
//                 switch (choice) {
//                 case 1:
//                     inv.addItem(head, undoStack);
//                     break;
//                 case 2:
//                     cout << "Enter item ID to delete: ";
//                     int idToDelete;
//                     cin >> idToDelete;
//                     inv.deleteItem(head, idToDelete, undoStack);
//                     break;
//                 case 3:
//                     inv.showInventory(head);
//                     break;
//                 case 4:
//                     goto adminExit;
//                 }
//             }
//         adminExit:
//             break;

//         case 2: // User Panel
//             cout << "Enter your username: ";
//             cin >> username;
//             while (true) {
//                 cout << "\nUser Menu:\n1) Add to Bill\n2) Remove from Bill\n3) Generate Bill\n4) View Feedback\n5) Provide Feedback\n6) Exit\n";
//                 cin >> choice;
//                 switch (choice) {
//                 case 1: {
//                     int id, quantity;
//                     cout << "Enter item ID to add: ";
//                     cin >> id;
//                     cout << "Enter quantity: ";
//                     cin >> quantity;
//                     billing.addItem(head, id, quantity, undoStack);
//                     break;
//                 }
//                 case 2: {
//                     int id;
//                     cout << "Enter item ID to remove: ";
//                     cin >> id;
//                     billing.removeItem(id);
//                     break;
//                 }
//                 case 3:
//                     billing.generateBill(username);
//                     break;
//                 case 4:
//                     feedback.viewFeedbacks();
//                     break;
//                 case 5:
//                     feedback.addFeedback();
//                     break;
//                 case 6:
//                     goto userExit;
//                 }
//             }
//         userExit:
//             break;

//         case 3: // Exit
//             cout << "Exiting program.\n";
//             return 0;
//         }
//     }

//     return 0;
// }
