#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdexcept>
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
            next = nullptr;
        }
    };
    node* topNode; 

public:
    stack()
    {
        topNode = nullptr;
    }

    void push(T data) 
    {
        node* newNode = new node(data);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop() 
    {
        if (topNode == nullptr) 
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
        if (topNode == nullptr) 
        {
            throw runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    bool isEmpty() 
    {
        return topNode == nullptr;
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
        next = prev = nullptr;
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
        head = nullptr;
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
        while (current != nullptr) 
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
        while (current != nullptr) 
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
        if (head == nullptr) 
        {
            head = newProduct;
        } else 
        {
            product* current = head;
            while (current->next != nullptr) 
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
        while (current != nullptr) 
        {
            if (current->id == id) 
            {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void displaystock() const 
    {
        if (head == nullptr) 
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
        while (current != nullptr) 
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
        while (current != nullptr) 
        {
            if (current->id == id) 
            {
                // Record the removed product for undo functionality
                undoStack.push(Action("REMOVE", id, current->name, current->price, current->stock));
                while (!redoStack.isEmpty()) 
                {
                    redoStack.pop();
                }

                if (current->prev != nullptr) 
                {
                    current->prev->next = current->next;
                } else 
                {
                    head = current->next;
                }
                if (current->next != nullptr) 
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
        if (current != nullptr) 
        {
            if (!name.empty())
                current->name = name;
            if (price >= 0)
                current->price = price;
            if (stock >= 0)
                current->stock = stock;
            cout << "Updated product: " << current->name << " (ID: " << id << ")" << endl;
            savestock();
        } else 
        {
            cout << "Product with ID " << id << " not found." << endl;
        }
    }

    void applydiscounttoproduct(int id, double discountPercent) 
    {
        product* current = findproduct(id);
        if (current != nullptr) 
        {
            double discountAmount = current->price * (discountPercent / 100);
            current->price -= discountAmount;
            cout << "Applied " << discountPercent << "% discount. New price: " << current->price << endl;
            savestock();
        } else 
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
    billnode *next;

    billnode(int id, int qty) 
    {
        productId = id;
        quantity = qty;
        next = nullptr;
    }
};

class billqueue 
{
private:
    billnode *front;
    billnode *rear;

public:
    billqueue() 
    {
        front = rear = nullptr;
    }

    bool isEmpty() 
    {
        return front == nullptr;
    }

    billnode *getfront() 
    {
        return front;
    }

    billnode *peek() 
    {
        if (isEmpty()) 
        {
            cout << "The bill queue is empty!" << endl;
            return nullptr;
        }
        return front;
    }

    void enqueue(int productId, int quantity) 
    {
        billnode *newNode = new billnode(productId, quantity);
        if (rear == nullptr) 
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
        billnode *temp = front;
        front = front->next;
        if (front == nullptr) 
        {
            rear = nullptr;
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

        billnode *current = front;
        cout << left << setw(10) << "Product ID" << setw(10) << "Quantity" << endl;
        cout << string(20, '-') << endl;
        while (current != nullptr) 
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
    Inventory inventory;
    billqueue billQueue;

public:
    BillingSystem() 
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
        billnode *current = billQueue.getfront();
        while (current != nullptr) 
        {
            product *prod = inventory.findproduct(current->productId);
            if (prod != nullptr) 
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
        product *prod = inventory.findproduct(productId);
        if (prod == nullptr)
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

        billnode *billItem = billQueue.peek();
        int productId = billItem->productId;
        int quantity = billItem->quantity;

        product *prod = inventory.findproduct(productId);
        if (prod != nullptr) 
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
            } else if (choice >= 2 && choice <= 4) 
            {
                string input;
                cout << "Enter required payment details: ";
                cin >> input;
            } else 
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
    void savefeedback(const string &name, const string &email, const string &feedback)
    {
        ofstream file("feedback.txt", ios::app);
        if (!file)
        {
            cerr << "Error opening feedback file for writing!" << endl;
            return;
        }
        file << "=============== FEEDBACK ENTRY ===============" << endl;
        file<<"time:"<<getcurrenttime()<<endl;
        file<<"date:"<<getcurrentdate()<<endl;
        file << "Name: " << name << endl;
        file << "Email: " << email << endl;
        file << "Date: " << getcurrenttime() << endl;
        file << "Feedback: " << feedback << endl;
        file << "==============================================" << endl;
        file.close();
    }
    string getcurrenttime() const
    {
        time_t now = time(0);
        char *dt = ctime(&now);
        return dt;
    }
    string getcurrentdate() const
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        char buffer[50];
        strftime(buffer, 50, "%Y-%m-%d %H:%M:%S", ltm);
        return string(buffer);
    }
};
class AutoPilot
{
private:
    BillingSystem  billingSystem;
    Inventory inventory;
    const string adminPassword = "1234";

    void resetSystem()
    {
        billingSystem.checkout();
    }

    bool verifyAdmin()
    {
        string inputPassword;
        cout << "Enter Admin Password to Exit Auto Pilot Mode: ";
        cin >> inputPassword;
        return inputPassword == adminPassword;
    }

public:
    AutoPilot(BillingSystem &billing, Inventory &inv) : billingSystem(billing), inventory(inv) {}

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

        cout << "Waiting for the next customer..." << endl;
        cout << "To exit Auto Pilot Mode, press '1' or any other key to continue: ";
        int exitChoice;
        cin >> exitChoice;

        if (exitChoice == 1 && handleAdminExit())
        {
            cout << "Exiting Auto Pilot Mode. Returning to main menu." << endl;
            return;
            break;
        }
    }
}

void processCustomer(const string &customerName)
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

        billingSystem.addProductToBill(productId, quantity);
    }

    cout << endl
         << "Generating your bill..." << endl;
    billingSystem.displayBill();
    billingSystem.finalizeBill();
    cout << "Thank you, " << customerName << "! Have a great day!" << endl;
    resetSystem();
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

class menus
{
private:
    Inventory inventory;
    BillingSystem billingSystem;
    int choice;

    void displayMenuHeader(const string &header)
    {
        
        cout << "============== " << header << " ==============" << endl;
    }

    int getUserChoice(const string &prompt)
    {
        int choice;
        cout << prompt;
        cin >> choice;
        cin.ignore();
        return choice;
    }

public:
    void about()
    {
        displayMenuHeader("ABOUT THE SYSTEM");
        cout << "A simple offline Point of Sale System featuring efficient inventory management\n"
             << "and a simple billing system for paper-less management of your business.\n"
             << "Developed by:\n"
             << "  - Muhammad Murtaza (F2023266701)\n"
             << "  - Mohsin Khan (F2023266704)\n"
             << "  - Muhammad Zain-Ul-Abideen (F2023266705)\n\n"
             << "Press Enter to return to the main menu...";
        cin.ignore();
        mainmenu();
    }

    void mainmenu()
    {
        do
        {
            displayMenuHeader("POINT OF SALE SYSTEM");
            cout << "1. Enter Point of Sale System\n"
                 << "2. About the System\n"
                 << "3. Auto Pilot Mode\n"
                 << "4. Exit\n";
            choice = getUserChoice("Enter your choice: ");

            switch (choice)
            {
            case 1:
                nextmenu();
                break;
            case 2:
                about();
                break;
            case 3:
            {
                AutoPilot autopilot(billingSystem, inventory);
                autopilot.start();
                break;
            }
            case 4:
                cout << "Exiting... Thank you for using the system!" << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
            }
        } while (choice != 4);
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
                productmenu();
                break;
            case 2:
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
                addProductToBill();
                break;
            case 2:
                billingSystem.removeProductFromBill();
                break;
            case 3:
                billingSystem.displayBill();
                break;
            case 4:
                billingSystem.checkout();
                return; 
            case 5:
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
                 <<"6. Undo product addition / removal\n"
                 <<"7. Redo product addition / removal\n"
                 << "8. Back\n";
            choice = getUserChoice("Enter your choice: ");

            switch (choice)
            {
            case 1:
                addproduct();
                break;
            case 2:
                removeProduct();
                break;
            case 3:
                updateProduct();
                break;
            case 4:
                inventory.displaystock();
                break;
            case 5:
                applyDiscount();
                break;
            case 6:
                inventory.undo();
                break;
            case 7:
                inventory.redo();
                break;
            case 8:
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