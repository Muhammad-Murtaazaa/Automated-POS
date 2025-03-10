#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

template <class T>
class stack
{
private:
    struct node
    {
        T data;
        node* next;
        node(T data)
        {
            this->data = data;
            next = NULL;
        }
    };
    node* topNode;

public:
    stack()
    {
        topNode = NULL;
    }

    void push(T data)
    {
        node* newNode = new node(data);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop()
    {
        if (topNode == NULL)
        {
            cout << "Stack is empty!" << endl;
            return;
        }
        node* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    T peek()
    {
        if (topNode == NULL)
        {
            cout << "Stack is empty!" << endl;
            return T();
        }
        return topNode->data;
    }

    bool isEmpty()
    {
        return topNode == NULL;
    }

    void top()
    {
        if (isEmpty())
        {
            cout << "Stack is empty!" << endl;
            return;
        }
        cout << "Top of the stack: " << topNode->data << endl;
    }

    ~stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }
};

struct Action
{
    string type;
    int id;
    string name;
    double price;
    int stock;
    Action() {}
    Action(string type, int id, string name = "", double price = 0.0, int stock = 0)
    {
        this->type = type;
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
    }
};

class product
{
public:
    int id;
    string name;
    double price;
    int stock;
    product* next;
    product* prev;

    product(int id, string name, double price, int stock)
    {
        this->id = id;
        this->name = name;
        this->price = price;
        this->stock = stock;
        next = prev = NULL;
    }
};

class Inventory
{
private:
    product* head;
    int numberofproducts;
    stack<Action> undoStack;
    stack<Action> redoStack;
public:
    Inventory()
    {
        head = NULL;
        numberofproducts = 0;
    }

    void savestock() const
    {
        ofstream file("inventory.txt");
        if (!file.is_open())
        {
            cout << "Error: Could not open the file to save inventory!" << endl;
            return;
        }

        file << left << setw(10) << "ID"
            << setw(20) << "Name"
            << setw(10) << "Quantity"
            << setw(10) << "Price" << endl;
        file << string(50, '-') << endl;

        product* current = head;
        while (current != NULL)
        {
            file << left << setw(10) << current->id
                << setw(20) << current->name
                << setw(10) << current->stock
                << setw(10) << fixed << setprecision(2) << current->price
                << endl;
            current = current->next;
        }

        file.close();
        cout << "Inventory successfully saved/updated to 'inventory.txt'." << endl;
    }

    bool productexists(int id)
    {
        product* current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void addproduct(int id, string name, double price, int stock)
    {
        if (productexists(id))
        {
            cout << "A product with ID " << id << " already exists!" << endl;
            cout << "Please enter a different ID" << endl;
            return;
        }
        product* newProduct = new product(id, name, price, stock);
        if (head == NULL)
        {
            head = newProduct;
        }
        else
        {
            product* current = head;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = newProduct;
            newProduct->prev = current;
        }
        numberofproducts++;
        cout << "Product added: " << name << " (ID: " << id << ")" << endl;
        savestock();

        // Record the action for undo functionality
        undoStack.push(Action("ADD", id, name, price, stock));
        while (!redoStack.isEmpty())
        {
            redoStack.pop();
        }
    }

    product* findproduct(int id)
    {
        product* current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                return current;
            }
            current = current->next;
        }
        return NULL;
    }

    void displaystock() const
    {
        if (head == NULL)
        {
            cout << "No products in inventory!" << endl;
            return;
        }
        cout << left << setw(10) << "ID"
            << setw(20) << "Name"
            << setw(10) << "Quantity"
            << setw(10) << "Price" << endl;
        cout << string(50, '-') << endl;

        product* current = head;
        while (current != NULL)
        {
            cout << left << setw(10) << current->id
                << setw(20) << current->name
                << setw(10) << current->stock
                << setw(10) << fixed << setprecision(2) << current->price
                << endl;
            current = current->next;
        }
        cout << string(50, '-') << endl;
    }

    void removeproduct(int id)
    {
        product* current = head;
        while (current != NULL)
        {
            if (current->id == id)
            {
                // Record the removed product for undo functionality
                undoStack.push(Action("REMOVE", id, current->name, current->price, current->stock));
                while (!redoStack.isEmpty())
                {
                    redoStack.pop();
                }

                if (current->prev != NULL)
                {
                    current->prev->next = current->next;
                }
                else
                {
                    head = current->next;
                }
                if (current->next != NULL)
                {
                    current->next->prev = current->prev;
                }
                cout << "Removed product: " << current->name << " (ID: " << id << ")" << endl;
                delete current;
                numberofproducts--;
                savestock();
                return;
            }
            current = current->next;
        }
        cout << "Product with ID " << id << " not found." << endl;
    }

    void updateproduct(int id, string name, double price, int stock)
    {
        product* current = findproduct(id);
        if (current != NULL)
        {
            if (!name.empty())
                current->name = name;
            if (price >= 0)
                current->price = price;
            if (stock >= 0)
                current->stock = stock;
            cout << "Updated product: " << current->name << " (ID: " << id << ")" << endl;
            savestock();
        }
        else
        {
            cout << "Product with ID " << id << " not found." << endl;
        }
    }

    void applydiscounttoproduct(int id, double discountPercent)
    {
        product* current = findproduct(id);
        if (current != NULL)
        {
            double discountAmount = current->price * (discountPercent / 100);
            current->price -= discountAmount;
            cout << "Applied " << discountPercent << "% discount. New price: " << current->price << endl;
            savestock();
        }
        else
        {
            cout << "Product with ID " << id << " not found." << endl;
        }
    }

    void undo()
    {
        if (undoStack.isEmpty())
        {
            cout << "Nothing to undo!" << endl;
            return;
        }

        Action lastAction = undoStack.peek();
        undoStack.pop();

        if (lastAction.type == "ADD")
        {
            removeproduct(lastAction.id);
            redoStack.push(lastAction);
        }
        else if (lastAction.type == "REMOVE")
        {
            addproduct(lastAction.id, lastAction.name, lastAction.price, lastAction.stock);
            redoStack.push(lastAction);
        }
    }

    void redo()
    {
        if (redoStack.isEmpty())
        {
            cout << "Nothing to redo!" << endl;
            return;
        }

        Action lastUndone = redoStack.peek();
        redoStack.pop();

        if (lastUndone.type == "ADD")
        {
            addproduct(lastUndone.id, lastUndone.name, lastUndone.price, lastUndone.stock);
            undoStack.push(lastUndone);
        }
        else if (lastUndone.type == "REMOVE")
        {
            removeproduct(lastUndone.id);
            undoStack.push(lastUndone);
        }
    }
};

struct billnode
{
    int productId;
    int quantity;
    billnode* next;

    billnode(int id, int qty)
    {
        productId = id;
        quantity = qty;
        next = NULL;
    }
};

class billqueue
{
private:
    billnode* front;
    billnode* rear;

public:
    billqueue()
    {
        front = rear = NULL;
    }

    bool isEmpty()
    {
        return front == NULL;
    }

    billnode* getfront()
    {
        return front;
    }

    billnode* peek()
    {
        if (isEmpty())
        {
            cout << "The bill queue is empty!" << endl;
            return NULL;
        }
        return front;
    }

    void enqueue(int productId, int quantity)
    {
        billnode* newNode = new billnode(productId, quantity);
        if (rear == NULL)
        {
            front = rear = newNode;
        }
        else
        {
            rear->next = newNode;
            rear = newNode;
        }
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "The bill queue is empty!" << endl;
            return;
        }
        billnode* temp = front;
        front = front->next;
        if (front == NULL)
        {
            rear = NULL;
        }
        delete temp;
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No items in the bill." << endl;
            return;
        }

        billnode* current = front;
        cout << left << setw(10) << "Product ID" << setw(10) << "Quantity" << endl;
        cout << string(20, '-') << endl;
        while (current != NULL)
        {
            cout << left << setw(10) << current->productId << setw(10) << current->quantity << endl;
            current = current->next;
        }
        cout << string(20, '-') << endl;
    }
};

class BillingSystem
{

private:
    double total;
    double taxrate;
    double totalsales;
    Inventory& inventory;
    billqueue billQueue;

public:
    BillingSystem(Inventory& inv) : inventory(inv)
    {
        total = 0;
        taxrate = 0.1;
        totalsales = 0;
    }

    void saveBillToFile()
    {
        ofstream file("bill.txt");
        if (!file.is_open())
        {
            cout << "Error: Could not open the file to save the bill!" << endl;
            return;
        }
        file << "Customer Bill" << endl;
        file << string(30, '-') << endl;
        file << left << setw(10) << "ProductID"
            << setw(15) << "Quantity"
            << setw(10) << "Price"
            << endl;
        file << string(30, '-') << endl;
        billnode* current = billQueue.getfront();
        while (current != NULL)
        {
            product* prod = inventory.findproduct(current->productId);
            if (prod != NULL)
            {
                file << left << setw(10) << current->productId
                    << setw(15) << current->quantity
                    << setw(10) << fixed << setprecision(2) << prod->price * current->quantity
                    << endl;
            }
            current = current->next;
        }
        file << string(30, '-') << endl;
        file << "Total (before tax): $" << fixed << setprecision(2) << total << endl;
        file << "Tax: $" << fixed << setprecision(2) << total * taxrate << endl;
        file << "Total (with tax): $" << fixed << setprecision(2) << total * (1 + taxrate) << endl;
        file.close();
        cout << "Bill saved to 'bill.txt'." << endl;
    }

    void addProductToBill(int productId, int quantity)
    {
        int p = productId;
        product* prod = inventory.findproduct(p);
        if (prod == NULL)
        {
            cout << "Product with ID " << productId << " not found in inventory!" << endl;
            return;
        }

        if (prod->stock < quantity)
        {
            cout << "Insufficient stock for product: " << prod->name << "!" << endl;
            return;
        }

        billQueue.enqueue(productId, quantity);
        total += prod->price * quantity;
        prod->stock -= quantity;

        cout << "Added " << quantity << " of " << prod->name << " to the bill." << endl;
        inventory.savestock();
    }

    void removeProductFromBill()
    {
        if (billQueue.isEmpty())
        {
            cout << "The bill is empty!" << endl;
            return;
        }

        billnode* billItem = billQueue.peek();
        int productId = billItem->productId;
        int quantity = billItem->quantity;

        product* prod = inventory.findproduct(productId);
        if (prod != NULL)
        {
            prod->stock += quantity;
            total -= prod->price * quantity;
            cout << "Removed " << quantity << " of " << prod->name << " from the bill." << endl;
        }

        billQueue.dequeue();
        inventory.savestock();
    }

    void displayBill()
    {
        cout << "Current Bill:" << endl
            << string(20, '-') << endl;
        billQueue.display();
        cout << "Total (before tax): $" << fixed << setprecision(2) << total << endl;
        cout << "Tax: $" << fixed << setprecision(2) << total * taxrate << endl;
        cout << "Total (with tax): $" << fixed << setprecision(2) << total * (1 + taxrate) << endl;
    }

    void finalizeBill()
    {
        displayBill();
        int choice;

        do
        {
            cout << "Enter your payment method:" << endl;
            cout << "1. Cash" << endl;
            cout << "2. Credit Card" << endl;
            cout << "3. Debit Card" << endl;
            cout << "4. Mobile Wallet" << endl;
            cout << "Choice: ";
            cin >> choice;

            if (choice == 1)
            {
                cout << "Enter the amount you are paying: ";
                double amount;
                cin >> amount;
                if (amount < total)
                {
                    cout << "Insufficient amount. Please pay the full amount!" << endl;
                    continue;
                }
            }
            else if (choice >= 2 && choice <= 4)
            {
                string input;
                cout << "Enter required payment details: ";
                cin >> input;
            }
            else
            {
                cout << "Invalid choice, try again!" << endl;
                continue;
            }

            cout << "Payment successful. Thank you for shopping with us!" << endl;
            saveBillToFile();
            checkout();
            break;

        } while (true);
    }

    void checkout()
    {
        totalsales += total * (1 + taxrate);
        total = 0;
        while (!billQueue.isEmpty())
        {
            billQueue.dequeue();
        }
        cout << "Checkout complete. Thank you!" << endl;
    }
};
class feedbacksystem
{
public:
    void collectfeedback()
    {
        string name, email, feedback;
        cout << "=============== USER FEEDBACK INTERFACE ===============" << endl;
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your feedback: ";
        getline(cin, feedback);
        savefeedback(name, email, feedback);
        cout << "Thank you for your feedback!" << endl;
    }
    void savefeedback(const string& name, const string& email, const string& feedback)
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
        file << "Feedback: " << feedback << endl;
        file << "==============================================" << endl;
        file.close();
    }
};

class AutoPilot
{
private:
    BillingSystem& billingSystem;
    Inventory& inventory;
    const string adminPassword = "1234";
    feedbacksystem feedbackSystem;

    void resetSystem()
    {
        billingSystem.checkout();
        inventory.savestock(); // Ensure that the inventory is saved after the transaction
    }

    bool verifyAdmin()
    {
        string inputPassword;
        cout << "Enter Admin Password to Exit Auto Pilot Mode: ";
        cin >> inputPassword;
        return inputPassword == adminPassword;
    }

    void processCustomer(const string& customerName)
    {
        while (true)
        {
            int productId, quantity;
            cout << endl
                << "Hello, " << customerName << "! What would you like to buy?" << endl;
            inventory.displaystock();

            cout << "Enter Product ID (or -1 to finish): ";
            cin >> productId;

            if (productId == -1)
                break;

            cout << "Enter Quantity: ";
            cin >> quantity;

            product* prod = inventory.findproduct(productId);
            if (prod && prod->stock >= quantity)
            {
                billingSystem.addProductToBill(productId, quantity);
                prod->stock -= quantity; // Reduce the stock
                cout << "Product added to your bill. Stock updated!" << endl;
            }
            else
            {
                cout << "Insufficient stock or product not found!" << endl;
            }
        }

        cout << endl
            << "Generating your bill..." << endl;
        billingSystem.displayBill();
        billingSystem.finalizeBill();
        cout << "Thank you, " << customerName << "! Have a great day!" << endl;

        resetSystem();
    }

    void collectCustomerFeedback()
    {
        feedbackSystem.collectfeedback(); // Call the feedback system to collect feedback
    }

public:

    AutoPilot(BillingSystem& billing, Inventory& inv) : billingSystem(billing), inventory(inv) {}

    void start()
    {
        while (true)
        {
            system("cls");
            cout << "============== AUTO PILOT MODE ==============" << endl;
            string customerName;
            cout << "Welcome to the store!" << endl;
            cout << "Please enter your name: ";
            cin.ignore();
            getline(cin, customerName);

            processCustomer(customerName);

            // Ask for feedback after each customer transaction
            collectCustomerFeedback();

            cout << "Waiting for the next customer..." << endl;
            cout << "To exit Auto Pilot Mode, press '1' or press '2' to continue: ";
            int exitChoice;
            cin >> exitChoice;

            if (exitChoice == 1 && handleAdminExit())
            {
                cout << "Exiting Auto Pilot Mode. Returning to main menu." << endl;
                break;
            }
            else if (exitChoice == 2)
            {
                system("cls");
                continue;
            }
        }
    }

    bool handleAdminExit()
    {
        while (true)
        {
            if (verifyAdmin())
                return true;

            cout << "Incorrect password. Press 1 to try again or 0 to return to Auto Pilot Mode: ";
            int retryChoice;
            cin >> retryChoice;
            if (retryChoice == 0)
                return false;
        }
    }
};

class styles
{
protected:

    void setConsoleColor(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void setTextCenter(const string& text)
    {
        cout << setw(40 + text.length() / 2) << text << endl;
    }

    void typewriterEffect(const string& text, int delay = 50)
    {
        for (char c : text)
        {
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(delay));
        }
        cout << endl;
    }

    void hideCursor()
    {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(consoleHandle, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(consoleHandle, &cursorInfo);
    }
};

class menus : public styles
{
private:
    Inventory inventory;
    BillingSystem billingSystem;
    int choice;

    void displayMenuHeader(const string& text)
    {
        int paddingX = 6;  // Horizontal padding (left & right)
        int paddingY = 2;  // Vertical padding (top & bottom)
        int width = text.length() + paddingX * 2; // Total box width

// Print top border
        cout << "+";
        for (int i = 0; i < width; i++) cout << "=";
        cout << "+" << endl;

// Print empty space above the text
        for (int i = 0; i < paddingY; i++) {
        cout << "*";
        for (int j = 0; j < width; j++) cout << " ";
        cout << "*" << endl;
}

// Print the centered text
        cout << "*";
        cout << string(paddingX - 1, ' '); // Left padding
        cout << text;
        cout << string(width - text.length() - (paddingX - 1), ' '); // Corrected Right Padding
        cout << "*" << endl;

// Print empty space below the text
        for (int i = 0; i < paddingY; i++) {
            cout << "*";
            for (int j = 0; j < width; j++) cout << " ";
            cout << "*" << endl;
}

// Print bottom border
        cout << "+";
        for (int i = 0; i < width; i++) cout << "=";
        cout << "+" << endl;
    }

    int getUserChoice(const string& prompt)
    {
        int choice;
        cout << prompt;
        cin >> choice;
        cin.ignore();
        return choice;
    }

public:
    menus() : billingSystem(inventory) {}
    void about()
    {
        displayMenuHeader("ABOUT THE SYSTEM");
        typewriterEffect("A simple offline Point of Sale System featuring efficient inventory management");
        typewriterEffect("and a simple billing system for paper-less management of your business.");
        typewriterEffect("Developed by:");
        typewriterEffect("  - Muhammad Murtaza");
        typewriterEffect("Press Enter to return to the main menu...");
        cin.ignore();
        mainmenu();
    }

    void mainmenu()
    {
        const int menusize = 4;
        string menuitems[menusize] = { "Enter Point of Sale System", "About the System","Auto Pilot Mode", "Exit" };
        int selected = 0;
        int key;
        hideCursor();

        while (true)
        {
            system("cls");
            displayMenuHeader("POINT OF SALE SYSTEM");
            for (int i = 0; i < menusize; i++) 
            {
                if (i == selected) 
                {
                    setConsoleColor(10); // Highlighted option (green)
                }
                else 
                {
                    setConsoleColor(15); // Normal (White)
                }
                cout << (i + 1) << ". " << menuitems[i] << endl;
            }

            key = _getch();

            if (key == 224) 
            {
                key = _getch();
                if (key == 80 && selected < menusize - 1) // Down arrow
                {
                    selected++;  // Move down
                }
                else if (key == 72 && selected > 0) // Up arrow 
                {
                    selected--;  // Move up
                }
            }
            else if (key == 13) // Enter key 
            {
                system("cls");
                setConsoleColor(15);  // Reset color

                if (selected == 0)  
                {
                    nextmenu();
                }
                else if (selected == 1) 
                {
                    about();
                }
                else if (selected == 2) 
                {
                    AutoPilot autopilot(billingSystem, inventory);
                    autopilot.start();
                    break;
                }
                else if (selected == 3) 
                {
                    cout << "Exiting........"<<endl;
                    cout<<"Thank you for using the system!" << endl;
                    break;
                }
            }
        }
    }

    void nextmenu()
    {
        while (true)
        {
            displayMenuHeader("POINT OF SALE SYSTEM");
            cout << "1. Product Management\n"
                << "2. Generate Bill\n"
                << "3. Back to Main Menu\n";
            choice = getUserChoice("Enter your choice: ");

            switch (choice)
            {
            case 1:
                system("cls");
                productmenu();
                break;
            case 2:
                system("cls");
                billmenu();
                break;
            case 3:
                return;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
            }
        }
    }

    void billmenu()
    {
        while (true)
        {
            displayMenuHeader("BILLING SYSTEM");
            cout << "1. Add Product to Bill\n"
                << "2. Remove Product from Bill\n"
                << "3. Display Bill\n"
                << "4. Checkout\n"
                << "5. Back\n";
            choice = getUserChoice("Enter your choice: ");

            switch (choice)
            {
            case 1:
                system("cls");
                addProductToBill();
                break;
            case 2:
                system("cls");
                billingSystem.displayBill();
                billingSystem.removeProductFromBill();
                break;
            case 3:
                system("cls");
                billingSystem.displayBill();
                break;
            case 4:
                system("cls");
                billingSystem.displayBill();
                billingSystem.checkout();
                return;
            case 5:
                system("cls");
                return;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
            }
        }
    }

    void productmenu()
    {
        while (true)
        {
            displayMenuHeader("PRODUCT MANAGEMENT");
            cout << "1. Add Product\n"
                << "2. Remove Product\n"
                << "3. Update Product\n"
                << "4. Display Stock\n"
                << "5. Apply Discount\n"
                << "6. Undo product addition / removal\n"
                << "7. Redo product addition / removal\n"
                << "8. Back\n";
            choice = getUserChoice("Enter your choice: ");

            switch (choice)
            {
            case 1:
                system("cls");
                inventory.displaystock();
                addproduct();
                inventory.displaystock();
                break;
            case 2:
                system("cls");
                inventory.displaystock();
                removeProduct();
                break;
            case 3:
                system("cls");
                inventory.displaystock();
                updateProduct();
                break;
            case 4:
                system("cls");

                inventory.displaystock();
                break;
            case 5:
                system("cls");
                inventory.displaystock();
                applyDiscount();
                break;
            case 6:
                system("cls");
                inventory.undo();
                break;
            case 7:
                system("cls");
                inventory.redo();
                break;
            case 8:
                system("cls");
                return;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
            }
        }
    }

    void addproduct()
    {
        displayMenuHeader("ADD PRODUCT");
        int id, stock;
        string name;
        double price;
        cout << "Enter product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter product name: ";
        getline(cin, name);
        cout << "Enter product price: ";
        cin >> price;
        cout << "Enter product quantity: ";
        cin >> stock;
        inventory.addproduct(id, name, price, stock);
        cout << "Product added successfully!\n";
    }

    void removeProduct()
    {
        displayMenuHeader("REMOVE PRODUCT");
        int id;
        cout << "Enter product ID to remove: ";
        cin >> id;
        inventory.removeproduct(id);
        cout << "Product removed successfully!\n";
    }

    void updateProduct()
    {
        displayMenuHeader("UPDATE PRODUCT");
        int id, stock;
        string name;
        double price;
        cout << "Enter product ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter new product name (leave empty to keep the same): ";
        getline(cin, name);
        cout << "Enter new product price (negative to keep the same): ";
        cin >> price;
        cout << "Enter new product quantity (negative to keep the same): ";
        cin >> stock;

        inventory.updateproduct(id, name, price, stock);
        cout << "Product updated successfully!\n";
    }

    void applyDiscount()
    {
        displayMenuHeader("APPLY DISCOUNT");
        int id;
        double discount;

        cout << "Enter product ID: ";
        cin >> id;
        cout << "Enter discount percentage: ";
        cin >> discount;
        inventory.applydiscounttoproduct(id, discount);
        cout << "Discount applied successfully!\n";
    }

    void addProductToBill()
    {
        int id, quantity;
        cout << "Enter product ID: ";
        cin >> id;
        cout << "Enter quantity: ";
        cin >> quantity;
        billingSystem.addProductToBill(id, quantity);
        cout << "Product added to bill successfully!\n";
    }
};

int main()
{
    menus menu;
    menu.mainmenu();
    return 0;
}