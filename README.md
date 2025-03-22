# Grand Hotel Paradox Simulation in C++

## Introduction

This C++ program, `Grand-Hotel.cpp`, is an interactive simulation of the famous Grand Hotel paradox, a thought experiment that beautifully illustrates the counterintuitive properties of infinite sets. The paradox demonstrates how a hotel with an infinite number of fully occupied rooms can accommodate additional guests, even an infinite number of them, by cleverly rearranging the existing occupants.



## Theoretical Basis

The Grand Hotel paradox was conceived by the renowned German mathematician **David Hilbert** in **1924**. It was later popularized by the physicist and writer **George Gamow** in his 1947 book, "One, Two, Three... Infinity."

The paradox centers around a hypothetical hotel with an infinite number of rooms, all of which are currently occupied by guests. Intuitively, one might think that there is no room for any new arrivals. However, the nature of infinite sets allows for seemingly impossible scenarios. The core idea is that a countably infinite set can be put into a one-to-one correspondence (a bijection) with a proper subset of itself.

**The Paradox Explained:**

Imagine a hotel with rooms numbered 1, 2, 3, and so on, extending to infinity. Every room has one guest.

* **Scenario 1: One New Guest Arrives**
    * The hotel manager can simply ask the guest in room 1 to move to room 2, the guest in room 2 to move to room 3, and in general, the guest in room *n* to move to room *n* + 1. This process shifts every existing guest one room down, leaving room 1 vacant for the new arrival.

* **Scenario 2: An Infinite Number of New Guests Arrive**
    * Now, suppose an infinite number of new guests arrive, say, on an infinitely long bus. The manager can accommodate them by asking the guest in room *n* to move to room 2*n*.
    * The guest in room 1 moves to room 2.
    * The guest in room 2 moves to room 4.
    * The guest in room 3 moves to room 6.
    * And so on.
    * This action moves all the original guests into the even-numbered rooms. All the odd-numbered rooms (1, 3, 5, 7, ...) become vacant. Since there are infinitely many odd numbers, the infinitely many new guests can each be assigned to one of these newly freed rooms.

This paradox highlights the difference between finite and infinite sets. For finite sets, if you have a set that is full, you cannot add more elements without removing existing ones. However, with infinite sets, this is not necessarily the case.

## Key Ideas (Implemented in Potential Future Extensions)

While the current version of `Grand-Hotel.cpp` focuses on the first two scenarios, the following methods represent other fascinating ways to accommodate infinite guests in an infinitely full hotel:

1.  **New Visitor:** Shift each guest from room *n* to room *n* + 1, freeing up room 1 for the new guest.
2.  **Infinite Number of New Visitors:** Shift each guest from room *n* to room 2\*n, freeing up all odd-numbered rooms.
3.  **Prime Power Method:** Relocate guests to rooms whose numbers are powers of prime numbers.
4.  **Integer Factorization Method:** Assign rooms based on the unique prime factorization of integers.
5.  **Interleaving Method:** Interleave the digits of bus numbers and seat numbers to create unique room numbers.
6.  **Triangular Number Method:** Use triangular numbers to relocate guests.
7.  **Higher Levels of Infinity:** Assign rooms based on three-dimensional addresses (ferry-bus-seat).
8.  **Binary Encoding Method:** Encode guest addresses in binary format.

## Main Functions and Algorithms

This program is structured with the following key functions and algorithms:

### Helper Functions

* `delay(int milliseconds)`: Pauses the program execution for a specified number of milliseconds, used for animation effects.
* `clearScreen()`: Clears the console screen.
* `printWelcomeScreen()`: Displays the initial welcome screen with ASCII art representing the hotel receptionist.
* `printHotel(const vector<int>& hotel, int visibleRooms = 15)`: Prints the current state of the hotel, showing room numbers and whether they are occupied by a guest. It displays a limited number of rooms for better readability and indicates the infinite nature of the hotel.

### Simulation Modes

The current version implements the following simulation modes:

1.  **Single Guest Check-in (Option 1):**
    * `moveOneGuest(vector<int>& hotel)`: Simulates the process of shifting each existing guest from room *n* to room *n* + 1 with a simple console animation.
    * After the shift, a new guest is checked into room 1.

2.  **Infinite Visitors Check-in (Option 2):**
    * `moveGroupGuests(vector<int>& hotel)`: Simulates the process of shifting each existing guest from room *n* to room 2\*n with a console animation.
    * After the shift, new guests are conceptually checked into the now-vacant odd-numbered rooms.

### Main Menu

* `main()`: The entry point of the program. It initializes the hotel with a finite number of occupied rooms (for demonstration purposes), displays the welcome screen and menu, takes user input to select a simulation mode, and then executes the chosen simulation. Finally, it prints the theoretical explanation of the Grand Hotel paradox before exiting.

## Conclusion

The `Grand-Hotel.cpp` program offers an engaging and interactive way to understand the Grand Hotel paradox. By simulating the process of accommodating new guests in an infinitely full hotel using different mathematical strategies, it demonstrates the fascinating and sometimes counter-intuitive nature of infinite sets. This program serves as a valuable tool for exploring fundamental concepts in set theory and the nature of infinity.
