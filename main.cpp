#include <iostream>
using namespace std;
class menus
{
    public:
        void mainmenu();
        void inventory();
};
void menus::mainmenu()
{
    cout << "Main Menu" << endl;
    cout << "1) Inventory" << endl;
    cout << "2) Generate Bill" << endl;
    cout << "4) Show Stock" << endl;
    cout<<"5) Show sales"<<endl;
    cout << "3) Exit" << endl;
}
void menus::inventory()
{
    cout << "Inventory" << endl;
    cout << "1) Add Item" << endl;
    cout << "2) Delete Item" << endl;
    cout << "3) Update Item" << endl;
    cout << "4) Show Inventory" << endl;
    cout << "5) Exit" << endl;
}
int main() {

}