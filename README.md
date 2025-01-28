# Railway Reservation System

A simple and efficient railway reservation management system. This project aims to manage reservations with basic features such as user login, train management, and reservations. It is designed to be easy to use and understand, with fixed dummy mistakes and sample inputs.

## Features

- **User Management**: Login system for users with secure authentication.
- **Train Management**: Manage trains, including details about schedules, availability, and more.
- **Reservation Management**: Simple and intuitive interface to manage reservations.
- **Error Handling**: Fixed dummy errors and added input validation to enhance system robustness.
- **GUI Support**: Supports a basic interface using the Awicons Vista Artistic 2 Hot Train icon.

## Project Structure

The project is structured into several C++ files and includes the following components:

- `main.cpp`: The entry point for the program where the main function resides. It initializes the system and interacts with the user.
- `User.cpp`: Contains the implementation of the User class for handling user login and authentication.
- `ReservationManager.cpp`: Manages reservations, including creating, modifying, and canceling them.
- `TrainManager.cpp`: Handles train-related operations such as adding, viewing, and updating train schedules.
- `Awicons-Vista-Artistic-2-Hot-Train.ico`: The icon used for the graphical interface of the program.
- `MYprogram.exe`: The executable file for the system.
- `Railway-Reservation-System.code-workspace`: The workspace configuration for your code editor.
- `desktop.ini`: Configuration file for desktop icon settings.

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/railway-reservation-system.git

2. ***Run the program 
   ```bash
   g++ main.cpp TrainManager.cpp ReservationManager.cpp train.cpp User.cpp -o Myprogram
   ./Myprogram.exe

