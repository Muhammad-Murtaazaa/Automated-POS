// #include <iostream>
// #include <string>
// #include <fstream>
// #include <iomanip> 
// using namespace std;
// class Discount
// {
// public:
//     static void apply(double &price, double discountPercent)
//     {
//         if (discountPercent < 0 || discountPercent > 100)
//         {
//             cout << "Invalid discount percentage! Must be between 0 and 100." << endl;
//             return;
//         }
//         double discountAmount = price * (discountPercent / 100);
//         price -= discountAmount;
//         cout << "Applied " << discountPercent << "% discount. New price: " << price << endl;
//     }
// };
// struct product
// {
//     int id;
//     string name;
//     double price;
//     int stock;
//     product *prev;
//     product *next;

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
//     product *head;
//     product *tail;
//     int size;
// public:
//     Inventory()
//     {
//         head = tail = nullptr;
//         size = 0;
//     }
//     ~Inventory()
//     {
//         while (head)
//         {
//             product *temp = head;
//             head = head->next;
//             delete temp;
//         }
//     }

//     void addProduct(int id, string name, double price, int stock)
//     {
//         product *newNode = new product(id, name, price, stock);
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
//     }

//     void removeProduct(int id)
//     {
//         product *current = head;
//         while (current)
//         {
//             if (current->id == id)
//             {
//                 if (current->prev)
//                     current->prev->next = current->next;
//                 else
//                     head = current->next;

//                 if (current->next)
//                     current->next->prev = current->prev;
//                 else
//                     tail = current->prev;

//                 cout << "Removed product: " << current->name << " (ID: " << id << ")" << endl;
//                 delete current;
//                 size--;
//                 return;
//             }
//             current = current->next;
//         }
//         cout << "Product with ID " << id << " not found." << endl;
//     }

//     void updateProduct(int id, string name, double price, int stock)
//     {
//         product *current = head;
//         while (current)
//         {
//             if (current->id == id)
//             {
//                 if (!name.empty())
//                     current->name = name;
//                 if (price >= 0)
//                     current->price = price;
//                 if (stock >= 0)
//                     current->stock = stock;
//                 cout << "Updated product: " << name << " (ID: " << id << ")" << endl;
//                 return;
//             }
//             current = current->next;
//         }
//         cout << "Product with ID " << id << " not found." << endl;
//     }

//     void applyDiscountToProduct(int id, double discountPercent)
//     {
//         product *current = head;
//         while (current)
//         {
//             if (current->id == id)
//             {
//                 Discount::apply(current->price, discountPercent);
//                 return;
//             }
//             current = current->next;
//         }
//         cout << "Product with ID " << id << " not found." << endl;
//     }

//     void displayStock() const
//     {
//         if (!head)
//         {
//             cout << "No products in inventory!" << endl;
//             return;
//         }

//         cout << left << setw(10) << "ID"
//              << setw(20) << "Name"
//              << setw(10) << "Price"
//              << setw(10) << "Stock"
//              << endl;
//         cout << string(50, '-') << endl; // Separator line

//         product *current = head;
//         while (current)
//         {
//             cout << left << setw(10) << current->id
//                  << setw(20) << current->name
//                  << right << setw(10) << fixed << setprecision(2) << current->price
//                  << setw(10) << current->stock
//                  << endl;
//             current = current->next;
//         }
//     }

//     void saveStock() const
//     {
//         ofstream file("stock.txt");
//         if (!file)
//         {
//             cout << "Failed to open stock.txt for writing." << endl;
//             return;
//         }

//         file << left << setw(10) << "ID"
//              << setw(20) << "Name"
//              << setw(10) << "Price"
//              << setw(10) << "Stock"
//              << endl;
//         file << string(50, '-') << endl;

//         product *current = head;
//         while (current)
//         {
//             file << left << setw(10) << current->id
//                  << setw(20) << current->name
//                  << right << setw(10) << fixed << setprecision(2) << current->price
//                  << setw(10) << current->stock
//                  << endl;
//             current = current->next;
//         }

//         file.close();
//         cout << "Stock saved to stock.txt" << endl;
//     }
// };
