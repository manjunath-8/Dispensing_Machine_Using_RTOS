# Dispensing Machine Using RTOS
This project involves the implementation of an automated product dispensing system at a shopping mart using an RTOS (Real-Time Operating System). The system is designed to streamline the process of dispensing products into bags after billing. It utilizes an LCD for displaying products and prices, a UART interface for user input, and DC motors to dispense products. The system calculates and displays the total amount to be paid on the UART terminal.

## Features

- **LCD Display**: Shows the list of products and their prices.
- **UART Interface**: Allows the user to enter the product code and quantity. For example, entering `A8` indicates product A with a quantity of 8.
- **DC Motors**: Each product is associated with a DC motor that rotates to dispense the specified quantity of the product.
- **Billing**: The total amount to be paid is calculated and displayed on the UART terminal.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
