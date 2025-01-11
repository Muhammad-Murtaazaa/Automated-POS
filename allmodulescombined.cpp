// #include <iostream>
// #include <fstream>
// #include <string>
// #include <ctime>
// #include <iomanip>
// using namespace std;
// const int MAX_BILL_ITEMS = 100;
// class Inventory;
// class BillingSystem;
// void showInventoryMenu(Inventory& inventory);
// void showBillingMenu(BillingSystem& billingSystem);
// template <typename T>
// class Stack
// {
// private:
//     struct Node
//     {
//         T data;
//         Node* next;
//         Node(T value) : data(value), next(nullptr) {}
//     };

//     Node* topNode;

// public:
//     Stack() : topNode(nullptr) {}

//     ~Stack()
//     {
//         while (!isEmpty())
//         {
//             pop();
//         }
//     }

//     void push(T value)
//     {
//         Node* newNode = new Node(value);
//         newNode->next = topNode;
//         topNode = newNode;
//     }

//     void pop()
//     {
//         if (isEmpty())
//         {
//             return;
//         }
//         Node* temp = topNode;
//         topNode = topNode->next;
//         delete temp;
//     }

//     T top() const
//     {
//         if (!isEmpty())
//         {
//             return topNode->data;
//         }
//         throw runtime_error("Stack is empty");
//     }

//     bool isEmpty() const
//     {
//         return topNode == nullptr;
//     }
// };

// class UndoRedo
// {
// private:
//     Stack<string> undoStack;
//     Stack<string> redoStack;

// public:
//     void performAction(const string& action)
//     {
//         undoStack.push(action);
//         while (!redoStack.isEmpty())
//         {
//             redoStack.pop(); // Clear redo stack when a new action is performed
//         }
//         cout << "Performed action: " << action << endl;
//     }

//     void undo()
//     {
//         if (undoStack.isEmpty())
//         {
//             cout << "Nothing to undo!" << endl;
//             return;
//         }
//         string lastAction = undoStack.top();
//         undoStack.pop();
//         redoStack.push(lastAction);
//         cout << "Undone action: " << lastAction << endl;
//     }

//     void redo()
//     {
//         if (redoStack.isEmpty())
//         {
//             cout << "Nothing to redo!" << endl;
//             return;
//         }
//         string lastUndone = redoStack.top();
//         redoStack.pop();
//         undoStack.push(lastUndone);
//         cout << "Redone action: " << lastUndone << endl;
//     }

//     void printState() const
//     {
//         cout << "\nCurrent State:\n";
//         cout << "Undo Stack: ";
//         Stack<string> tempUndo = undoStack; // Copy to display contents
//         while (!tempUndo.isEmpty())
//         {
//             cout << tempUndo.top() << " ";
//             tempUndo.pop();
//         }
//         cout << "\nRedo Stack: ";
//         Stack<string> tempRedo = redoStack; // Copy to display contents
//         while (!tempRedo.isEmpty())
//         {
//             cout << tempRedo.top() << " ";
//             tempRedo.pop();
//         }
//         cout << "\n";
//     }
// };

// class FeedbackSystem
// {
// public:
//     void collectFeedback();
//     void saveFeedback(const string& name, const string& email, const string& feedback);

// private:
//     string getCurrentTime() const;
// };

// void FeedbackSystem::collectFeedback()
// {
//     string name, email, feedback;

//     cout << "=============== USER FEEDBACK INTERFACE ===============" << endl;
//     cout << "Enter your name: ";
//     getline(cin, name);
//     cout << "Enter your email: ";
//     getline(cin, email);
//     cout << "Enter your feedback: ";
//     getline(cin, feedback);

//     saveFeedback(name, email, feedback);

//     cout << "Thank you for your feedback!" << endl;
// }

// void FeedbackSystem::saveFeedback(const string& name, const string& email, const string& feedback)
// {
//     ofstream file("feedback.txt", ios::app);
//     if (!file)
//     {
//         cerr << "Error opening feedback file for writing!" << endl;
//         return;
//     }

//     file << "=============== FEEDBACK ENTRY ===============" << endl;
//     file << "Name: " << name << endl;
//     file << "Email: " << email << endl;
//     file << "Date: " << getCurrentTime() << endl;
//     file << "Feedback: " << feedback << endl;
//     file << "==============================================" << endl;
//     file.close();
// }

// string FeedbackSystem::getCurrentTime() const
// {
//     time_t now = time(0);
//     tm* ltm = localtime(&now);
//     char buffer[50];
//     strftime(buffer, 50, "%Y-%m-%d %H:%M:%S", ltm);
//     return string(buffer);
// }

// struct product
// {
//     int id;
//     string name;
//     double price;
//     int stock;
//     product* prev;
//     product* next;

//     product(int id, string name, double price, int stock)
//     {
//         this->id = id;
//         this->name = name;
//         this->price = price;
//         this->stock = stock;
//         prev = next = nullptr;
//     }
// };

// class Inventory
// {
// private:
//     product* head;
//     product* tail;
//     int size;
//     UndoRedo undoRedoSystem;

// public:
//     Inventory() : head(nullptr), tail(nullptr), size(0) {}

//     ~Inventory()
//     {
//         while (head)
//         {
//             product* temp = head;
//             head = head->next;
//             delete temp;
//         }
//     }

//     void addProduct(int id, string name, double price, int stock)
//     {
//         if (productExists(id))
//         {
//             cout << "Product with ID " << id << " already exists." << endl;
//             return;
//         }

//         product* newNode = new product(id, name, price, stock);
//         if (!tail)
//         {
//             head = tail = newNode;
//         }
//         else
//         {
//             tail->next = newNode;
//             newNode->prev = tail;
//             tail = newNode;
//         }
//         size++;
//         cout << "Product added: " << name << " (ID: " << id << ")" << endl;
//         undoRedoSystem.performAction("Add product: " + name);
//     }

//     bool productExists(int id)
//     {
//         product* current = head;
//         while (current)
//         {
//             if (current->id == id)
//             {
//                 return true;
//             }
//             current = current->next;
//         }
//         return false;
//     }

//     product* findProduct(int id)
//     {
//         product* current = head;
//         while (current)
//         {
//             if (current->id == id)
//             {
//                 return current;
//             }
//             current = current->next;
//         }
//         return nullptr;
//     }

//     void removeProduct(int id)
//     {
//         product* current = findProduct(id);
//         if (!current)
//         {
//             cout << "Product with ID " << id << " not found." << endl;
//             return;
//         }

//         if (current->prev)
//             current->prev->next = current->next;
//         else
//             head = current->next;

//         if (current->next)
//             current->next->prev = current->prev;
//         else
//             tail = current->prev;

//         cout << "Removed product: " << current->name << " (ID: " << id << ")" << endl;
//         delete current;
//         size--;
//         undoRedoSystem.performAction("Remove product: " + to_string(id));
//     }

//     void updateProduct(int id, string name, double price, int stock)
//     {
//         product* current = findProduct(id);
//         if (!current)
//         {
//             cout << "Product with ID " << id << " not found." << endl;
//             return;
//         }

//         if (!name.empty()) current->name = name;
//         if (price >= 0) current->price = price;
//         if (stock >= 0) current->stock = stock;

//         cout << "Updated product: " << current->name << " (ID: " << id << ")" << endl;
//         undoRedoSystem.performAction("Update product: " + current->name);
//     }

//     void applyDiscountToProduct(int id, double discountPercent)
//     {
//         product* current = findProduct(id);
//         if (!current)
//         {
//             cout << "Product with ID " << id << " not found." << endl;
//             return;
//         }
//         double discountAmount = current->price * (discountPercent / 100);
//         current->price -= discountAmount;
//         cout << "Applied " << discountPercent << "% discount. New price: " << current->price << endl;
//         undoRedoSystem.performAction("Apply discount to product: " + to_string(id));
//     }

//     void displayStock() const
//     {
//         if (!head)
//         {
//             cout << "No products in inventory!" << endl;
//             return;
//         }

//         product* current = head;
//         while (current)
//         {
//             cout << "Product: " << current->name << " | Price: " << current->price << " | Stock: " << current->stock << endl;
//             current = current->next;
//         }
//     }

//     void undoAction()
//     {
//         undoRedoSystem.undo();
//     }

//     void redoAction()
//     {
//         undoRedoSystem.redo();
//     }

//     void printState()
//     {
//         undoRedoSystem.printState();
//     }
// };

// class BillingSystem
// {
// private:
//     double total;
//     double taxRate;
//     double totalSales;
//     UndoRedo undoRedoSystem;

// public:
//     BillingSystem(double TAX_RATE = 0.1) : total(0), taxRate(TAX_RATE), totalSales(0) {}

//     void addProduct(string name, double price, int quantity)
//     {
//         double amount = price * quantity;
//         total += amount;
//         cout << "Added product: " << name << " | Quantity: " << quantity << " | Price: " << price << endl;
//         undoRedoSystem.performAction("Add product to bill: " + name + " | Quantity: " + to_string(quantity));
//     }

//     void applyDiscount(double discountPercent)
//     {
//         double discountAmount = total * (discountPercent / 100);
//         total -= discountAmount;
//         cout << "Applied discount: " << discountPercent << "% | Discount: " << discountAmount << endl;
//         undoRedoSystem.performAction("Apply discount to bill: " + to_string(discountPercent) + "%");
//     }

//     void printBill()
//     {
//         cout << "\n==================== BILL =====================" << endl;
//         cout << "Total before tax: " << total << endl;
//         double taxAmount = total * taxRate;
//         cout << "Tax (" << taxRate * 100 << "%): " << taxAmount << endl;
//         total += taxAmount;
//         cout << "Total after tax: " << total << endl;
//         totalSales += total;
//         cout << "===============================================" << endl;
//     }

//     void undoAction()
//     {
//         undoRedoSystem.undo();
//     }

//     void redoAction()
//     {
//         undoRedoSystem.redo();
//     }

//     void printState()
//     {
//         undoRedoSystem.printState();
//     }
// };

// void showInventoryMenu(Inventory& inventory)
// {
//     int choice;
//     do
//     {
//         cout << "\n============== Inventory Menu ==============" << endl;
//         cout << "1. Add Product" << endl;
//         cout << "2. Remove Product" << endl;
//         cout << "3. Update Product" << endl;
//         cout << "4. Apply Discount" << endl;
//         cout << "5. View Inventory" << endl;
//         cout << "6. Undo Last Action" << endl;
//         cout << "7. Redo Last Action" << endl;
//         cout << "0. Return to Main Menu" << endl;
//         cout << "Enter your choice: ";
//         cin >> choice;
//         cin.ignore();  // To clear the input buffer
        
//         switch (choice)
//         {
//         case 1:
//             {
//                 int id, stock;
//                 string name;
//                 double price;
//                 cout << "Enter product ID: ";
//                 cin >> id;
//                 cin.ignore();
//                 cout << "Enter product name: ";
//                 getline(cin, name);
//                 cout << "Enter product price: ";
//                 cin >> price;
//                 cout << "Enter product stock: ";
//                 cin >> stock;
//                 inventory.addProduct(id, name, price, stock);
//             }
//             break;
//         case 2:
//             {
//                 int id;
//                 cout << "Enter product ID to remove: ";
//                 cin >> id;
//                 inventory.removeProduct(id);
//             }
//             break;
//         case 3:
//             {
//                 int id, stock;
//                 string name;
//                 double price;
//                 cout << "Enter product ID to update: ";
//                 cin >> id;
//                 cin.ignore();
//                 cout << "Enter new product name (or leave empty to skip): ";
//                 getline(cin, name);
//                 cout << "Enter new product price (-1 to skip): ";
//                 cin >> price;
//                 cout << "Enter new product stock (-1 to skip): ";
//                 cin >> stock;
//                 inventory.updateProduct(id, name, price, stock);
//             }
//             break;
//         case 4:
//             {
//                 int id;
//                 double discount;
//                 cout << "Enter product ID to apply discount: ";
//                 cin >> id;
//                 cout << "Enter discount percentage: ";
//                 cin >> discount;
//                 inventory.applyDiscountToProduct(id, discount);
//             }
//             break;
//         case 5:
//             inventory.displayStock();
//             break;
//         case 6:
//             inventory.undoAction();
//             break;
//         case 7:
//             inventory.redoAction();
//             break;
//         case 0:
//             cout << "Returning to main menu..." << endl;
//             break;
//         default:
//             cout << "Invalid choice, try again!" << endl;
//             break;
//         }
//     } while (choice != 0);
// }

// void showBillingMenu(BillingSystem& billingSystem)
// {
//     int choice;
//     do
//     {
//         cout << "\n============== Billing Menu ==============" << endl;
//         cout << "1. Add Product to Bill" << endl;
//         cout << "2. Apply Discount" << endl;
//         cout << "3. Print Bill" << endl;
//         cout << "4. Undo Last Action" << endl;
//         cout << "5. Redo Last Action" << endl;
//         cout << "0. Return to Main Menu" << endl;
//         cout << "Enter your choice: ";
//         cin >> choice;
//         cin.ignore();  // To clear the input buffer
        
//         switch (choice)
//         {
//         case 1:
//             {
//                 string name;
//                 double price;
//                 int quantity;
//                 cout << "Enter product name: ";
//                 getline(cin, name);
//                 cout << "Enter product price: ";
//                 cin >> price;
//                 cout << "Enter product quantity: ";
//                 cin >> quantity;
//                 billingSystem.addProduct(name, price, quantity);
//             }
//             break;
//         case 2:
//             {
//                 double discount;
//                 cout << "Enter discount percentage: ";
//                 cin >> discount;
//                 billingSystem.applyDiscount(discount);
//             }
//             break;
//         case 3:
//             billingSystem.printBill();
//             break;
//         case 4:
//             billingSystem.undoAction();
//             break;
//         case 5:
//             billingSystem.redoAction();
//             break;
//         case 0:
//             cout << "Returning to main menu..." << endl;
//             break;
//         default:
//             cout << "Invalid choice, try again!" << endl;
//             break;
//         }
//     } while (choice != 0);
// }

// void showNewMainMenu(Inventory& inventory, BillingSystem& billingSystem)
// {
//     int choice;
//     do
//     {
//         cout << "\n============== Welcome to the System ==============" << endl;
//         cout << "1. Enter Point of Sale System" << endl;
//         cout << "2. About the System" << endl;
//         cout << "3. Exit" << endl;
//         cout << "Enter your choice: ";
//         cin >> choice;
//         cin.ignore();  // To clear the input buffer
        
//         switch (choice)
//         {
//         case 1:
//             int subChoice;
//             cout << "\n1. Manage Inventory\n2. Manage Billing\nEnter your choice: ";
//             cin >> subChoice;
//             cin.ignore();
//             if (subChoice == 1)
//             {
//                 showInventoryMenu(inventory); // Show the inventory management menu
//             }
//             else if (subChoice == 2)
//             {
//                 showBillingMenu(billingSystem); // Show the billing system menu
//             }
//             else
//             {
//                 cout << "Invalid choice! Returning to main menu." << endl;
//             }
//             break;
//         case 2:
//             cout << "\nSystem Information:\n";
//             cout << "System Developed by: Your Name\n";
//             cout << "Student ID: Your ID\n";
//             cout << "About: This is a Point of Sale (POS) system with inventory management and billing functionalities.\n";
//             break;
//         case 3:
//             cout << "Exiting the system..." << endl;
//             break;
//         default:
//             cout << "Invalid choice, please try again." << endl;
//             break;
//         }
//     } while (choice != 3); // Exit the loop if the user selects 3
// }

// int main()
// {
//     Inventory inventory;
//     BillingSystem billingSystem;

//     // Call the main menu to run the system
//     showNewMainMenu(inventory, billingSystem);

//     return 0;
// }