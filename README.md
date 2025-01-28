# Restaurant Billing System

A simple restaurant management system implemented in C language that helps manage orders, generate bills, and track daily sales.

## Features

- **Menu Display**: View the restaurant menu with item IDs, names, and prices
- **Order Management**: Take new orders with multiple items and quantities
- **Bill Generation**: Generate formatted bills with order details and total amount
- **Daily Sales Report**: Track and view daily sales data with detailed reports

## How It Works

The system provides a simple command-line interface with the following options:

1. Display Food Menu - Shows available food items with prices
2. Take New Order - Record new customer orders
3. Generate Bill - Create a formatted bill for the current order
4. Display Daily Sales - View a summary of all sales
5. Exit Program - Close the application

## Data Storage

The system stores daily sales data in a 'sales.txt' file, which maintains a record of all orders for generating sales reports.

## Implementation

The project is implemented using:
- C programming language
- File handling for data persistence
- Dynamic memory allocation for order management
- Structured programming with modular functions

## How to Run

### Prerequisites
- GCC compiler
- Terminal or Command Prompt

### Compilation
To compile the program, open your terminal and run:
```bash
gcc restaurant.c -o restaurant
```

### Execution
After compilation, run the program using:
```bash
./restaurant
```

### Usage Example
1. When the program starts, you'll see the main menu
2. Choose option 1 to view the food menu
3. Select option 2 to place a new order
4. Enter the item ID and quantity when prompted
5. Generate the bill using option 3
6. View daily sales report using option 4
7. Exit the program using option 5

Note: The program will create a 'sales.txt' file to store the sales data. This file is automatically managed by the system.