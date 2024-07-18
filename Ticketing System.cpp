#include <iostream>
#include <queue>
#include <string>
using namespace std;

const int g_kArraySize = 8;

// CustomerQueue Class Definition
class CustomerQueue {
private:
    queue<int> q;

public:
    // Add a customer order (number of items) to the queue
    void enqueue(int value) {
        q.push(value);
    }

    // Remove and serve the customer order at the front of the queue
    void dequeue() {
        if (!q.empty()) {
            q.pop();
        } else {
            cout << "Queue is empty!" << endl;
        }
    }

    // Check if the queue is empty
    bool isEmpty() const {
        return q.empty();
    }

    // Display the customer order currently being served
    int peek() const {
        if (!q.empty()) {
            return q.front();
        } else {
            cout << "Queue is empty!" << endl;
            return -1;  // Indicates empty queue
        }
    }

    // Display all customer orders in the queue
    void display() const {
        if (q.empty()) {
            cout << "Queue is empty!" << endl;
            return;
        }
        queue<int> temp = q;
        while (!temp.empty()) {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

// FoodItem Class Definition
class FoodItem {
private:
    string item_name;
    int items_available;
    double item_price;

public:
    FoodItem();
    FoodItem(string my_item_name, int my_items_available, double my_item_price);
    ~FoodItem();

    string get_item_name();
    int get_items_available();
    double get_item_price();

    void set_item_name(string new_item_name);
    void set_items_available(int new_items_available);
    void set_item_price(double new_item_price);

    double PurchaseItem(int purchase_items_available);
    void Display();
};

// Default constructor
FoodItem::FoodItem() {
    item_name = "";
    items_available = 0;
    item_price = 0.0;
}

// Parameterized constructor
FoodItem::FoodItem(string my_item_name, int my_items_available, double my_item_price) {
    item_name = my_item_name;
    items_available = my_items_available;
    item_price = my_item_price;
}

// Destructor
FoodItem::~FoodItem() {
    cout << item_name << " is no longer available.." << endl;
}

// Getter for item name
string FoodItem::get_item_name() {
    return item_name;
}

// Getter for items available
int FoodItem::get_items_available() {
    return items_available;
}

// Getter for item price
double FoodItem::get_item_price() {
    return item_price;
}

// Setter for item name
void FoodItem::set_item_name(string new_item_name) {
    item_name = new_item_name;
}

// Setter for items available
void FoodItem::set_items_available(int new_items_available) {
    items_available = new_items_available;
}

// Setter for item price
void FoodItem::set_item_price(double new_item_price) {
    item_price = new_item_price;
}

// Purchase a given number of items
double FoodItem::PurchaseItem(int purchase_items_available) {
    double total_price;

    // Check if enough items are available
    if (purchase_items_available <= items_available) {
        total_price = purchase_items_available * item_price;
        items_available = items_available - purchase_items_available;
        return total_price;
    } else {
        return -1;
    }
}

// Display item details
void FoodItem::Display() {
    cout.setf(ios::fixed, ios::floatfield);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "*********************************" << endl;
    cout << "Item Name:       " << item_name << endl;
    cout << "Items Available: " << items_available << endl;
    cout << "Price per Item:  $" << item_price << endl;
    cout << "*********************************" << endl;
}

// FoodTicketMaster Class Definition
class FoodTicketMaster {
private:
    FoodItem* p_ItemList;
    CustomerQueue customerQueue;  // Add customer queue

public:
    FoodTicketMaster();
    ~FoodTicketMaster();

    void Init(FoodItem* p_my_ItemList, int array_size);
    void Run();
    void DisplayMenu();
    void ViewItems();
    FoodItem* SearchItem();
    FoodItem* FindItem(string find_item_name);
    void PurchaseItem();
    void ProcessQueue();  // Add method to process queue
};

// Default constructor
FoodTicketMaster::FoodTicketMaster() {
    p_ItemList = NULL;
}

// Destructor
FoodTicketMaster::~FoodTicketMaster() {
    cout << "Food stall has been closed.." << endl;
}

// Initialize the item list
void FoodTicketMaster::Init(FoodItem* p_my_ItemList, int array_size) {
    string item_titles[g_kArraySize] = { "Burger", "Pizza", "Hotdog", "Sandwich", "Salad", "Tacos", "Sushi", "Pasta" };

    int stall_items[g_kArraySize] = { 85,75,90,90,75,100,65,50 };

    double item_price[g_kArraySize] = { 5.5,7.5,3.5,4.5,6.5,5.0,8.5,7.0 };

    FoodItem* p = p_my_ItemList;

    for (int i = 0; i <= g_kArraySize - 1; i++) {
        p->set_item_name(item_titles[i]);
        p->set_items_available(stall_items[i]);
        p->set_item_price(item_price[i]);
        p++;
    }

    p_ItemList = p_my_ItemList;
}

// Run the main loop
void FoodTicketMaster::Run() {
    int option;

    do {
        DisplayMenu();

        cout << "\nPlease select an option: ";
        cin >> option;

        switch (option) {
        case 1:
            ViewItems();
            system("PAUSE");
            system("CLS");
            break;

        case 2:
            SearchItem();
            system("PAUSE");
            system("CLS");
            break;

        case 3:
            PurchaseItem();
            break;

        case 4:
            cout << "\nThank You!\n" << endl;
            break;

        default:
            cout << "Please choose a valid option:" << endl
                 << "=============================" << endl;
            cin.ignore();
        }
    } while (option != 4);
}

// Display the main menu
void FoodTicketMaster::DisplayMenu() {
    cout << "******************************" << endl;
    cout << "*    Food Ticketing System   *" << endl;
    cout << "******************************" << endl;
    cout << "*           MENU             *" << endl;
    cout << "******************************" << endl;
    cout << "* 1. View all items          *" << endl;
    cout << "* 2. Search an item          *" << endl;
    cout << "* 3. Purchase items          *" << endl;
    cout << "* 4. Exit Application        *" << endl;
    cout << "******************************" << endl;
}

// View all items
void FoodTicketMaster::ViewItems() {
    FoodItem* p_view_items = p_ItemList;
    system("CLS");
    cout << "******************************" << endl;
    cout << "*    Available Food Items    *" << endl;
    cout << "******************************" << endl;

    for (int i = 0; i < g_kArraySize; i++) {
        cout << "Item " << i + 1 << ": " << endl;
        p_view_items->Display();
        ++p_view_items;
    }
}

// Search for a food item by name
FoodItem* FoodTicketMaster::SearchItem() {
    string search_item_name;

    cout << "\nPlease enter a food item name: ";
    cin.sync();
    std::getline(std::cin, search_item_name);

    FoodItem* p = FindItem(search_item_name);

    if (p != NULL) {
        p->Display();
    } else {
        cout << "\nError: Item not found." << endl << endl;
        return NULL;
    }
    return p;
}

// Find a food item by name
FoodItem* FoodTicketMaster::FindItem(string find_item_name) {
    FoodItem* p_find_item = p_ItemList;
    for (int i = 0; i < g_kArraySize; i++) {
        if (p_find_item->get_item_name() == find_item_name) {
            cout << "\nItem found" << endl;
            return p_find_item;
        } else {
            p_find_item++;
        }
    }
    return NULL;
}

// Purchase items for a food item
void FoodTicketMaster::PurchaseItem() {
    string purchase_item_name;
    int total_items;
    system("CLS");
    cout << "\nPlease enter a food item name: ";
    cin.sync();
    std::getline(std::cin, purchase_item_name);

    cout << "\nPlease enter the total number of items you wish to purchase: ";
    cin >> total_items;

    FoodItem* p = FindItem(purchase_item_name);

    if (p != NULL) {
        double total_cost = p->PurchaseItem(total_items);
        if (total_cost == -1) {
            cout << "\nThis item has been sold out or there are not enough items available per your request." << endl << endl;
        } else {
            cout << "\nYour total bill is: $" << total_cost << endl;
        }
        customerQueue.enqueue(total_items);  // Enqueue the customer order
        ProcessQueue();  // Process the queue
        cout << "\n\n";
        system("PAUSE");
        system("CLS");
    } else {
        cout << "No item has been found" << endl;
    }
}

// Process the customer queue
void FoodTicketMaster::ProcessQueue() {
    cout << "\nProcessing Queue:" << endl;
    customerQueue.display();  // Display the queue
    while (!customerQueue.isEmpty()) {
        cout << "\nServing customer order: " << customerQueue.peek() << endl;
        customerQueue.dequeue();
    }
}

// Main Function
int main() {
    FoodItem item_objects[g_kArraySize];

    FoodTicketMaster* p_FoodTicketMaster = new FoodTicketMaster();
    p_FoodTicketMaster->Init(item_objects, g_kArraySize);
    p_FoodTicketMaster->Run();

    delete p_FoodTicketMaster;
    return 0;
}

/*
Description:
- The CustomerQueue class simulates a queue of customer orders, where each order is an integer representing the number of items a customer wants to purchase.
- The FoodItem class represents a food item with a name, available items, and item price. It includes methods to purchase items and display item information.
- The FoodTicketMaster class manages the food ticketing system, including initializing item data, displaying menus, viewing items, searching for an item, purchasing items, and processing the customer queue.
- In the PurchaseItem function, customer orders (number of items) are enqueued into the CustomerQueue, and then the queue is processed to simulate serving the customers.
- The main function initializes the item data and runs the FoodTicketMaster system.
*/

