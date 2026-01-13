# Christmas Wishlist Manager

A clean, menu-driven console application built in C to manage a Christmas wishlist. It allows you to store, search, and view wishes for friends and family.

## Features
*   **Add Records**: Store a person's name and their wish.
*   **Search Function**: Find a person's wish with case-insensitive matching.
*   **View All**: Display the entire wishlist in a formatted list.
*   **Input Validation**: Handles empty inputs and other edge cases.

## Technical Details
This project demonstrates my understanding of:
*   **Structures (`struct`)** for data organization
*   **Arrays** for in-memory storage
*   **String manipulation** (`strcmp`, `fgets`)

## How to Compile and Run
1.  **Clone the repository:**
    ```bash
    git clone https://github.com/danilojonic/christmas-wishlist-manager.git
    cd christmas-wishlist-manager
    ```
2.  **Compile the program:**
    ```bash
    gcc cwm.c -o cwm -Wall -Wextra
    ```
3.  **Run the executable:**
    ```bash
    ./cwm        # On Linux/macOS
    ```
