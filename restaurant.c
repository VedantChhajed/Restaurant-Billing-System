#include <stdio.h>  // For input/output functions
#include <stdlib.h>  // For memory allocation and system functions
#include <string.h>  // For string operations

// Maximum length for item names
#define MAX_NAME_LENGTH 50
// File name to store daily sales data
#define SALES_FILE "sales.txt"

// Structure to store menu item details
struct MenuItem {
    int itemID;          // Unique ID for each menu item
    char itemName[MAX_NAME_LENGTH];  // Name of the item
    float price;         // Price of the item
};

// Structure to store order details
struct Order {
    int orderID;         // Unique ID for each order
    int itemID;          // ID of the ordered item
    char itemName[MAX_NAME_LENGTH];  // Name of the ordered item
    int quantity;        // Quantity ordered
    float totalPrice;    // Total price (price * quantity)
};

// Function prototypes
void displayMenu(struct MenuItem *menu, int size);
struct Order* takeOrder(struct MenuItem *menu, int menuSize, int *orderCount);
void generateBill(struct Order *orders, int orderCount);
void displayDailySales();
void saveOrderToFile(struct Order order);

// Function to show the restaurant menu
void displayMenu(struct MenuItem *menu, int size) {
    // Print menu header
    printf("\n+--------------------------------+\n");
    printf("|         RESTAURANT MENU         |\n");
    printf("+------+--------------------+-------------+\n");
    printf("|  ID  |        Item        |    Price    |\n");
    printf("+------+--------------------+-------------+\n");

    // Print each menu item
    for (int i = 0; i < size; i++) {
        printf("|  %-3d | %-18s | ₹%-10.2f |\n",
            menu[i].itemID,
            menu[i].itemName,
            menu[i].price);
    }

    printf("+------+--------------------+-------------+\n");
}

// Function to take a new order
struct Order* takeOrder(struct MenuItem *menu, int menuSize, int *orderCount) {
    static int nextOrderID = 1;  // To generate unique order IDs
    struct Order *orders = NULL;  // Array to store orders
    char continue_order;          // To check if user wants to add more items
    *orderCount = 0;             // Initialize order count to 0

    do {
        // Allocate memory for new order
        orders = realloc(orders, (*orderCount + 1) * sizeof(struct Order));
        if (orders == NULL) {
            printf("Memory allocation failed!\n");
            return NULL;
        }

        // Get item ID from user
        printf("\nEnter item ID: ");
        int itemID;
        // Keep asking until valid item ID is entered
        while (scanf("%d", &itemID) != 1 || itemID < 1 || itemID > menuSize) {
            printf("Invalid item ID! Please enter a number between 1 and %d: ", menuSize);
            while (getchar() != '\n');  // Clear input buffer
        }

        // Get quantity from user
        printf("Enter quantity: ");
        int quantity;
        // Keep asking until valid quantity is entered
        while (scanf("%d", &quantity) != 1 || quantity < 1) {
            printf("Invalid quantity! Please enter a positive number: ");
            while (getchar() != '\n');  // Clear input buffer
        }

        // Find the menu item and create the order
        for (int i = 0; i < menuSize; i++) {
            if (menu[i].itemID == itemID) {
                // Fill order details
                orders[*orderCount].orderID = nextOrderID++;
                orders[*orderCount].itemID = itemID;
                strcpy(orders[*orderCount].itemName, menu[i].itemName);
                orders[*orderCount].quantity = quantity;
                orders[*orderCount].totalPrice = menu[i].price * quantity;
                (*orderCount)++;  // Increment order count
                break;
            }
        }

        // Ask if user wants to order more items
        printf("Add another item? (y/n): ");
        while (getchar() != '\n');  // Clear input buffer
        scanf("%c", &continue_order);
    } while (continue_order == 'y' || continue_order == 'Y');

    return orders;
}

// Function to generate and display bill
void generateBill(struct Order *orders, int orderCount) {
    float grandTotal = 0;  // To store total bill amount
    
    // Print bill header
    printf("\n+----------------------------------------------+\n");
    printf("|                    BILL                    |\n");
    printf("+-------+----------------------+------+--------+\n");
    printf("|  ID   |         Item         |  Qty  | Total  |\n");
    printf("+-------+----------------------+------+--------+\n");

    // Print each ordered item
    for (int i = 0; i < orderCount; i++) {
        printf("|  %-3d  | %-20s |  %-3d  | ₹%-5.2f |\n",
            orders[i].orderID,
            orders[i].itemName,
            orders[i].quantity,
            orders[i].totalPrice);
        grandTotal += orders[i].totalPrice;  // Add to total
        saveOrderToFile(orders[i]);          // Save order to file
    }

    // Print grand total
    printf("+-------+----------------------+------+--------+\n");
    printf("|                Grand Total          | ₹%-5.2f |\n", grandTotal);
    printf("+----------------------------------------------+\n");
}

// Function to display daily sales report
void displayDailySales() {
    // Try to open sales file
    FILE *fp = fopen(SALES_FILE, "r");
    if (fp == NULL) {
        printf("No sales data available!\n");
        return;
    }

    float totalSales = 0;  // To store total sales amount
    char line[100];        // To store each line from file
    
    // Print report header
    printf("\n+----------------------------------------+\n");
    printf("|            DAILY SALES REPORT            |\n");
    printf("+-------+--------------------+--------+----------+\n");
    printf("|  ID   |        Item        |  Qty   |  Total   |\n");
    printf("+-------+--------------------+--------+----------+\n");

    // Read and print each order from file
    while (fgets(line, sizeof(line), fp)) {
        struct Order order;
        // Parse line into order structure
        sscanf(line, "%d,%[^,],%d,%f", 
            &order.orderID, 
            order.itemName, 
            &order.quantity, 
            &order.totalPrice);
        // Print order details
        printf("|  %3d  | %-18s |   %3d  | ₹%7.2f |\n",
            order.orderID,
            order.itemName,
            order.quantity,
            order.totalPrice);
        totalSales += order.totalPrice;  // Add to total sales
    }

    // Print total sales
    printf("+-------+--------------------+--------+----------+\n");
    printf("|              Total Sales             | ₹%7.2f |\n", totalSales);
    printf("+----------------------------------------+\n");
    fclose(fp);  // Close the file
}

// Function to save order to file
void saveOrderToFile(struct Order order) {
    // Open file in append mode
    FILE *fp = fopen(SALES_FILE, "a");
    if (fp == NULL) {
        printf("Error: Unable to create sales file!\n");
        return;
    }
    // Write order details to file
    fprintf(fp, "%d,%s,%d,%.2f\n", 
        order.orderID, 
        order.itemName, 
        order.quantity, 
        order.totalPrice);
    fclose(fp);  // Close the file
}

// Main function - program entry point
int main() {
    system("clear");  // Clear the screen
    printf("Welcome to Restaurant Management System\n");
    
    // Define menu items
    struct MenuItem menu[] = {
        {1, "Burger", 59.00},
        {2, "Pizza", 99.00},
        {3, "Pasta", 89.00},
        {4, "Salad", 49.00}
    };
    
    int userChoice;          // To store user's menu choice
    struct Order *orders = NULL;  // To store current order
    int orderCount = 0;      // Number of items in current order

    // Main program loop
    do {
        // Display main menu
        printf("\n=== MAIN MENU ===\n");
        printf("1. Display Food Menu\n");
        printf("2. Take New Order\n");
        printf("3. Generate Bill\n");
        printf("4. Display Daily Sales\n");
        printf("5. Exit Program\n");
        printf("Enter your choice (1-5): ");
        
        // Get valid choice from user
        while (scanf("%d", &userChoice) != 1) {
            printf("Please enter a valid number between 1 and 5: ");
            while (getchar() != '\n');  // Clear input buffer
        }

        // Process user choice
        switch (userChoice) {
            case 1:  // Display menu
                displayMenu(menu, 4);
                break;
            case 2:  // Take new order
                if (orders != NULL) {
                    free(orders);  // Free previous order memory
                }
                orders = takeOrder(menu, 4, &orderCount);
                break;
            case 3:  // Generate bill
                if (orders != NULL && orderCount > 0) {
                    generateBill(orders, orderCount);
                } else {
                    printf("Error: No orders to generate bill!\n");
                }
                break;
            case 4:  // Display sales report
                displayDailySales();
                break;
            case 5:  // Exit program
                printf("Thank you for using our system! Goodbye!\n");
                if (orders != NULL) {
                    free(orders);  // Free memory before exit
                }
                break;
            default:  // Invalid choice
                printf("Error: Invalid choice! Please enter a number between 1 and 5.\n");
        }
    } while (userChoice != 5);  // Continue until user chooses to exit

    return 0;
}
