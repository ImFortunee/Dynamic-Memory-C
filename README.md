
# COVID Contact Tracing App

A simple contact tracing application written in C that manages user locations and tracks potential COVID-19 exposure through location history.

## Features

- **User Management**: Add and remove users from the system
- **Location Tracking**: Track up to 2 locations per user
- **Contact Tracing**: Check which users have visited specific locations
- **Data Persistence**: Save and load user data to/from files
- **Sorted Storage**: Users are stored alphabetically in a linked list

## How to Use

1. **Compile the program:**
   ```bash
   make
   ```

2. **Run the application:**
   ```bash
   ./main
   ```

3. **Menu Options:**
   - `1` - Add a new user to the system
   - `2` - Add a location visit for an existing user
   - `3` - Remove a user from the system
   - `4` - Check which users have been to a specific location
   - `5` - Display all users and their locations
   - `6` - Save current data to file
   - `7` - Load data from file
   - `8` - Exit the application

## Data Structure

The application uses a **linked list** to store user information, with each user containing:
- Name (up to 100 characters)
- Up to 2 location entries
- Counter for number of places visited

## File Storage

User data is saved to `UserDataFile.txt` in binary format for persistence between sessions.

## Code Structure

- **Linked List Implementation**: Users are stored in alphabetical order
- **Memory Management**: Proper allocation and deallocation of memory
- **File I/O**: Binary file operations for data persistence
- **Error Handling**: Input validation and error messages

## Requirements

- GCC compiler
- Standard C libraries (stdio.h, stdlib.h, string.h)

## Author

COVID Contact Tracing App - A simple C implementation for educational purposes.
