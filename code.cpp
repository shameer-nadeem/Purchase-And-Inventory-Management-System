#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <limits.h>
#include <unistd.h>



using namespace std;


struct Item {
    string name;
    int quantity;
    double sellingPrice;
    double costPrice;
};

// Constants for the maximum number of items
const int MAX_ITEMS = 10;

// Function to clear the console
void clearConsole() {
    system("clear");
}

// Function to display inventory
void displayInventory(const Item inventory[], int itemCount) {
    cout << "Item Name        Quantity    Selling Price    Cost Price" << endl;
    cout << "--------------------------------------------------------" << endl;
    for (int i = 0; i < itemCount; i++) {
        cout << inventory[i].name << "        " << inventory[i].quantity << "          "
             << inventory[i].sellingPrice << "              " << inventory[i].costPrice << endl;
    }
}

// Function to update stock levels
void updateStock(Item inventory[], int itemCount) {
    string itemName;
    int newQuantity;
    cin.ignore();
    cout << "Enter item name to update: ";
    getline(cin, itemName);
    cout << "Enter new quantity: ";
    cin >> newQuantity;

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].name == itemName) {
            inventory[i].quantity = newQuantity;
            cout << "Stock updated successfully!" << endl;
            return;
        }
    }
    cout << "Item not found in inventory!" << endl;
}

// Function to record a purchase
void recordPurchase(const string &productName, int quantity, double totalCost, double profit) {
    ofstream file("sales_record.txt", ios::app);
    if (file.is_open()) {
        file << "Product: " << productName
             << ", Quantity: " << quantity
             << ", Total Cost: $" << fixed << setprecision(2) << totalCost
             << ", Profit: $" << fixed << setprecision(2) << profit << endl;
        file.close();
    } else {
        cout << "Error: Unable to open sales record file!" << endl;
    }
}

// Function for profit analysis
void profitAnalysis(double totalProfit) {
    clearConsole();
    cout << "Profit Analysis Report" << endl;
    cout << "-----------------------" << endl;
    cout << "Total Profit Earned: $" << totalProfit << endl;

    // Read sales record and display details
    ifstream file("sales_record.txt");
    if (file.is_open()) {
        string line;
        cout << "Detailed Sales Records:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "No sales record found." << endl;
    }
}

// Function for the admin menu
void adminMenu(Item inventory[], int itemCount, double totalProfit) {
    int choice;
    do {
        clearConsole();
        cout << "Admin Menu:" << endl;
        cout << "1. View Inventory" << endl;
        cout << "2. Update Stock Levels" << endl;
        cout << "3. View Sales Record" << endl;
        cout << "4. Profit Analysis" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                clearConsole();
                displayInventory(inventory, itemCount);
                break;
            case 2:
                clearConsole();
                updateStock(inventory, itemCount);
                break;
            case 3: {
                clearConsole();
                ifstream file("sales_record.txt");
                if (file.is_open()) {
                    string line;
                    cout << "Sales Record:" << endl;
                    while (getline(file, line)) {
                        cout << line << endl;
                    }
                    file.close();
                } else {
                    cout << "No sales record found." << endl;
                }
                break;
            }
            case 4:
                profitAnalysis(totalProfit);
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    } while (true);
}

// Function for the user menu
void userMenu(Item inventory[], int itemCount, double &totalProfit) {
    string userName;
    cout << "Enter your Name: ";
    cin >> userName;

    int choice, quantity;
    double totalBill = 0;

    do {
        clearConsole();
        cout << "Product List:" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << i + 1 << ". " << inventory[i].name << " ($" << inventory[i].sellingPrice << ")" << endl;
        }
        cout << "Enter the product number to purchase (0 to Exit): ";
        cin >> choice;

        if (choice == 0)
            break;

        if (choice > 0 && choice <= itemCount) {
            cout << "Enter quantity: ";
            cin >> quantity;

            if (quantity <= inventory[choice - 1].quantity) {
                double cost = quantity * inventory[choice - 1].sellingPrice;
                double profit = (inventory[choice - 1].sellingPrice - inventory[choice - 1].costPrice) * quantity;
                inventory[choice - 1].quantity -= quantity;
                totalProfit += profit;

                recordPurchase(inventory[choice - 1].name, quantity, cost, profit);

                totalBill += cost;
                cout << "Purchase successful! Total: $" << cost << endl;
            } else {
                cout << "Insufficient stock!" << endl;
            }
        } else {
            cout << "Invalid choice!" << endl;
        }
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();
    } while (true);

    cout << "Thank you, " << userName << "! Your Total Bill is: $" << totalBill << endl;
    cout << "Visit Again!" << endl;
}

// Main function
int main() {
    Item inventory[MAX_ITEMS] = {
        {"Apple Malt", 50, 2.5, 1.5},
        {"Lemon Malt", 40, 2.0, 1.0},
        {"Peach Malt", 30, 3.0, 2.0}};
    int itemCount = 3;
    double totalProfit = 0.0;

    string username, password;

    clearConsole();
    cout << "Login:" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "Osama" && password == "Osama123") {
        adminMenu(inventory, itemCount, totalProfit);
    } else if (username == "Shameer"  || username == "Sameer" && password == "user123") {
        userMenu(inventory, itemCount, totalProfit);
    } else {
        cout << "Invalid credentials! Exiting..." << endl;
    }
    

//    char cwd[PATH_MAX];
//      if (getcwd(cwd, sizeof(cwd)) != nullptr) {
//          std::cout << "Current Working Directory: " << cwd << std::endl;
//      } else {
//          perror("getcwd() error");
//      }



    return 0;
}
