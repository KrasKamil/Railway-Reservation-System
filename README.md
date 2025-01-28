# Railway Reservation System

A simple and efficient railway reservation management system. This project aims to manage reservations with basic features such as user login, train management, and reservations. It is designed to be easy to use and understand, with fixed dummy mistakes and sample inputs.

## Features

- **User Management**: Login system for users with secure authentication.
- **Train Management**: Manage trains, including details about schedules, availability, and more.
- **Reservation Management**: Simple and intuitive interface to manage reservations.
- **Ticket Management**: Save and search for tickets.
- **Error Handling**: Fixed dummy errors and added input validation to enhance system robustness.
- **Polish Characters Support**: Proper handling and display of Polish characters.

## Project Structure

The project is structured into several C++ files and includes the following components:

- `main.cpp`: The entry point for the program where the main function resides. It initializes the system and interacts with the user.
- `User.cpp`: Contains the implementation of the User class for handling user login and authentication.
- `ReservationManager.cpp`: Manages reservations, including creating, modifying, and canceling them.
- `TrainManager.cpp`: Handles train-related operations such as adding, viewing, and updating train schedules.
- `train.cpp`: Contains the implementation of the Train class for handling train details.
- `ticket.cpp`: Manages ticket-related operations such as saving and searching for tickets.
- `Lib/User.h`: Header file for the User class.
- `Lib/ReservationManager.h`: Header file for the ReservationManager class.
- `Lib/TrainManager.h`: Header file for the TrainManager class.
- `Lib/Train.h`: Header file for the Train class.
- `Lib/ticket.h`: Header file for ticket-related functions.
- `Data/users.json`: JSON file containing user data.
- `Data/trains.json`: JSON file containing train data.
- `Data/tickets.json`: JSON file containing ticket data.

## Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/railway-reservation-system.git
   ```

2. **Run the program:**
   ```bash
   g++ main.cpp TrainManager.cpp ReservationManager.cpp ticket.cpp train.cpp User.cpp -o Myprogram
   ./Myprogram.exe
   ```
