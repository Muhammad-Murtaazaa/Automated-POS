#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;

const int MAX_BILL_ITEMS = 100;

// Forward declare Inventory and BillingSystem classes
class Inventory;
class BillingSystem;

void showInventoryMenu(Inventory& inventory);
void showBillingMenu(BillingSystem& billingSystem);

template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    void push(T value)
    {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop()
    {
        if (isEmpty())
        {
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    T top() const
    {
        if (!isEmpty())
        {
            return topNode->data;
        }
        throw runtime_error("Stack is empty");
    }

    bool isEmpty() const
    {
        return topNode == nullptr;
    }
};

class UndoRedo
{
private:
    Stack<string> undoStack;
    Stack<string> redoStack;

public:
    void performAction(const string& action)
    {
        undoStack.push(action);
        while (!redoStack.isEmpty())
        {
            redoStack.pop(); // Clear redo stack when a new action is performed
        }
        cout << "Performed action: " << action << endl;
    }

    void undo()
    {
        if (undoStack.isEmpty())
        {
            cout << "Nothing to undo!" << endl;
            return;
        }
        string lastAction = undoStack.top();
        undoStack.pop();
        redoStack.push(lastAction);
        cout << "Undone action: " << lastAction << endl;
    }

    void redo()
    {
        if (redoStack.isEmpty())
        {
            cout << "Nothing to redo!" << endl;
            return;
        }
        string lastUndone = redoStack.top();
        redoStack.pop();
        undoStack.push(lastUndone);
        cout << "Redone action: " << lastUndone << endl;
    }

    void printState() const
    {
        cout << "\nCurrent State:\n";
        cout << "Undo Stack: ";
        Stack<string> tempUndo = undoStack; // Copy to display contents
        while (!tempUndo.isEmpty())
        {
            cout << tempUndo.top() << " ";
            tempUndo.pop();
        }
        cout << "\nRedo Stack: ";
        Stack<string> tempRedo = redoStack; // Copy to display contents
        while (!tempRedo.isEmpty())
        {
            cout << tempRedo.top() << " ";
            tempRedo.pop();
        }
        cout << "\n";
    }
};

class FeedbackSystem
{
public:
    void collectFeedback();
    void saveFeedback(const string& name, const string& email, const string& feedback);

private:
    string getCurrentTime() const;
};

void FeedbackSystem::collectFeedback()
{
    string name, email, feedback;

    cout << "=============== USER FEEDBACK INTERFACE ===============" << endl;
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Enter your email: ";
    getline(cin, email);
    cout << "Enter your feedback: ";
    getline(cin, feedback);

    saveFeedback(name, email, feedback);

    cout << "Thank you for your feedback!" << endl;
}

void FeedbackSystem::saveFeedback(const string& name, const string& email, const string& feedback)
{
    ofstream file("feedback.txt", ios::app);
    if (!file)
    {
        cerr << "Error opening feedback file for writing!" << endl;
        return;
    }

    file << "=============== FEEDBACK ENTRY ===============" << endl;
    file << "Name: " << name << endl;
    file << "Email: " << email << endl;
    file << "Date: " << getCurrentTime() << endl;
    file << "Feedback: " << feedback << endl;
    file << "==============================================" << endl;
    file.close();
}

string FeedbackSystem::getCurrentTime() const
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[50];
    strftime(buffer, 50, "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

struct product
{
    int id;
    string name;
    double price;
    int stock;
    product* prev;
    product* next;

    product(int id, string name, double price, int stock)
    {
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
        prev = next = nullptr;
    }
};

class Inventory
{
private:
    product* head;
    product* tail;
    int size;
    UndoRedo undoRedoSystem;

public:
    Inventory() : head(nullptr), tail(nullptr), size(0) {}

    ~Inventory()
    {
        while (head)
        {
            product* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addProduct(int id, string name, double price, int stock)
    {
        if (productExists(id))
        {
            cout << "Product with ID " << id << " already exists." << endl;
            return;
        }

        product* newNode = new product(id, name, price, stock);
        if (!tail)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
        cout << "Product added: " << name << " (ID: " << id << ")" << endl;
        undoRedoSystem.performAction("Add product: " + name);
    }

    bool productExists(int id)
    {
        product* current = head;
        while (current)
        {
            if (current->id == id)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    product* findProduct(int id)
    {
        product* current = head;
        while (current)
        {
            if (current->id == id)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void removeProduct(int id)
    {
        product* current = findProduct(id);
        if (!current)
        {
            cout << "Product with ID " << id << " not found." << endl;
            return;
        }

        if (current->prev)
            current->prev->next = current->next;
        else
            head = current->next;

        if (current->next)
            current->next->prev = current->prev;
        else
            tail = current->prev;

        cout << "Removed product: " << current->name << " (ID: " << id << ")" << endl;
        delete current;
        size--;
        undoRedoSystem.performAction("Remove product: " + to_string(id));
    }

    void updateProduct(int id, string name, double price, int stock)
    {
        product* current = findProduct(id);
        if (!current)
        {
            cout << "Product with ID " << id << " not found." << endl;
            return;
        }

        if (!name.empty()) current->name = name;
        if (price >= 0) current->price = price;
        if (stock >= 0) current->stock = stock;

        cout << "Updated product: " << current->name << " (ID: " << id << ")" << endl;
        undoRedoSystem.performAction("Update product: " + current->name);
    }

    void applyDiscountToProduct(int id, double discountPercent)
    {
        product* current = findProduct(id);
        if (!current)
        {
            cout << "Product with ID " << id << " not found." << endl;
            return;
        }
        double discountAmount = current->price * (discountPercent / 100);
        current->price -= discountAmount;
        cout << "Applied " << discountPercent << "% discount. New price: " << current->price << endl;
        undoRedoSystem.performAction("Apply discount to product: " + to_string(id));
    }

    void displayStock() const
    {
        if (!head)
        {
            cout << "No products in inventory!" << endl;
            return;
        }

        product* current = head;
        while (current)
        {
            cout << "Product: " << current->name << " | Price: " << current->price << " | Stock: " << current->stock << endl;
            current = current->next;
        }
    }

    void undoAction()
    {
        undoRedoSystem.undo();
    }

    void redoAction()
    {
        undoRedoSystem.redo();
    }

    void printState()
    {
        undoRedoSystem.printState();
    }
};

class BillingSystem
{
private:
    double total;
    double taxRate;
    double totalSales;
    UndoRedo undoRedoSystem;

public:
    BillingSystem(double TAX_RATE = 0.1) : total(0), taxRate(TAX_RATE), totalSales(0) {}

    void addProduct(string name, double price, int quantity)
    {
        total += price * quantity;
        cout << "Added to bill: " << name << " | Quantity: " << quantity << " | Subtotal: " << price * quantity << endl;
        undoRedoSystem.performAction("Add product to bill: " + name);
    }

    void finalizeBill(double payment)
    {
        double tax = total * taxRate;
        double grandTotal = total + tax;
        cout << "Total: " << total << endl;
        cout << "Tax: " << tax << endl;
        cout << "Grand Total: " << grandTotal << endl;

        if (payment < grandTotal)
        {
            cout << "Insufficient payment! Bill not completed." << endl;
            return;
        }

        double change = payment - grandTotal;
        cout << "Payment received: " << payment << endl;
        cout << "Change: " << change << endl;

        totalSales += grandTotal;
        undoRedoSystem.performAction("Finalize bill. Total: " + to_string(grandTotal));

        FeedbackSystem feedbackSystem;
        feedbackSystem.collectFeedback();
    }

    void undoAction()
    {
        undoRedoSystem.undo();
    }

    void redoAction()
    {
        undoRedoSystem.redo();
    }

    void printState()
    {
        undoRedoSystem.printState();
    }
};

// Menu system for interacting with the user
void showMainMenu(Inventory& inventory, BillingSystem& billingSystem)
{
    int choice;
    do
    {
        cout << "\n============== Main Menu ==============" << endl;
        cout << "1. Manage Inventory" << endl;
        cout << "2. Billing System" << endl;
        cout << "3. View Inventory" << endl;
        cout << "4. Undo Last Action" << endl;
        cout << "5. Redo Last Action" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To clear the input buffer
        
        switch (choice)
        {
        case 1:
            showInventoryMenu(inventory);
            break;
        case 2:
            showBillingMenu(billingSystem);
            break;
        case 3:
            inventory.displayStock();
            break;
        case 4:
            inventory.undoAction();
            break;
        case 5:
            inventory.redoAction();
            break;
        case 0:
            cout << "Exiting the system..." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (choice != 0);
}

void showInventoryMenu(Inventory& inventory)
{
    int choice;
    do
    {
        cout << "\n============== Inventory Menu ==============" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Remove Product" << endl;
        cout << "3. Update Product" << endl;
        cout << "4. Apply Discount to Product" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To clear the input buffer
        
        int id;
        string name;
        double price;
        int stock;
        double discountPercent;
        
        switch (choice)
        {
        case 1:
            cout << "Enter product ID, name, price, and stock: ";
            cin >> id >> name >> price >> stock;
            inventory.addProduct(id, name, price, stock);
            break;
        case 2:
            cout << "Enter product ID to remove: ";
            cin >> id;
            inventory.removeProduct(id);
            break;
        case 3:
            cout << "Enter product ID, new name, price, and stock: ";
            cin >> id >> name >> price >> stock;
            inventory.updateProduct(id, name, price, stock);
            break;
        case 4:
            cout << "Enter product ID and discount percentage: ";
            cin >> id >> discountPercent;
            inventory.applyDiscountToProduct(id, discountPercent);
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (choice != 0);
}

void showBillingMenu(BillingSystem& billingSystem)
{
    int choice;
    do
    {
        cout << "\n============== Billing System ==============" << endl;
        cout << "1. Add Product to Bill" << endl;
        cout << "2. Finalize Bill" << endl;
        cout << "3. Undo Last Action" << endl;
        cout << "4. Redo Last Action" << endl;
        cout << "0. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // To clear the input buffer
        
        string name;
        double price;
        int quantity;
        double payment;

        switch (choice)
        {
        case 1:
            cout << "Enter product name, price, and quantity: ";
            cin >> name >> price >> quantity;
            billingSystem.addProduct(name, price, quantity);
            break;
        case 2:
            cout << "Enter payment amount: ";
            cin >> payment;
            billingSystem.finalizeBill(payment);
            break;
        case 3:
            billingSystem.undoAction();
            break;
        case 4:
            billingSystem.redoAction();
            break;
        case 0:
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
            break;
        }
    } while (choice != 0);
}

int main()
{
    Inventory inventory;
    BillingSystem billingSystem;
    showMainMenu(inventory, billingSystem);
    return 0;
}
