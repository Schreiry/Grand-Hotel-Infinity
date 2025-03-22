#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;
using namespace std::chrono;

// ============================
// Вспомогательные функции для анимации и оформления
// ============================

// Функция для задержки (анимации)
static void delay(int milliseconds) {
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}

// Функция для очистки консоли
void clearScreen() {
    system(CLEAR);
}

// Функция для установки цвета (ANSI-коды)
void setColor(const string& color) {
    cout << color;
}

const string RESET_COLOR = "\033[0m";
const string GREEN_COLOR = "\033[32m";
const string CYAN_COLOR = "\033[36m";
const string YELLOW_COLOR = "\033[33m";
const string MAGENTA_COLOR = "\033[35m";

// Функция для ожидания нажатия клавиши Enter
void waitForEnter() {
    cout << "\nPress Enter to return to the main menu...";
    cin.ignore();
    cin.get();
}

// ============================
// Базовые экраны и ASCII‑арт
// ============================

void printWelcomeScreen() {
    clearScreen();
    setColor(CYAN_COLOR);
    cout << R"(
      ___________________________
     |                           |
     |  Grand Hotel: Infinity    |
     |___________________________|
             ||
       __     ||     __
      |  |____||____|  |
      |__|    ||    |__|
      ||      ||      ||
      ||      ||      ||
     [==]    [==]    [==]
     
   The hotel receptionist greets you warmly!
   
   (The receptionist stands at the bar, bathed in the glow of seductive lamps)
    )" << "\n" << RESET_COLOR;
}

// Вывод состояния отеля – для симуляций с фиксированным числом комнат
void printHotel(const vector<int>& hotel) {
    cout << "\n" << YELLOW_COLOR << "Hotel status (room number : guest):" << RESET_COLOR << "\n";
    for (size_t i = 0; i < hotel.size(); i++) {
        cout << "Room " << setw(3) << i + 1 << " : ";
        if (hotel[i] == 0)
            cout << "[Empty]";
        else {
            // Если номер гостя ≥ 10000 – новый гость (отметим зелёным)
            if (hotel[i] >= 10000) {
                setColor(GREEN_COLOR);
                cout << "New Guest " << (hotel[i] - 10000);
                setColor(RESET_COLOR);
            }
            else {
                cout << "Guest " << hotel[i];
            }
        }
        cout << "\n";
    }
    cout << "\n" << MAGENTA_COLOR << "Count: ∞ (Infinity)" << RESET_COLOR << "\n";
}

// ============================
// Режимы симуляции заселения
// ============================

// 1. Новый посетитель: сдвиг гостей вправо (room n → room n+1)
void simulationNewVisitor(vector<int>& hotel) {
    int n = hotel.size();
    for (int i = n - 1; i >= 0; i--) {
        if (hotel[i] != 0) {
            if (i + 1 < n)
                hotel[i + 1] = hotel[i];
            hotel[i] = 0;
        }
        clearScreen();
        cout << "Resettlement (New Visitor): shifting guests (room n → room n+1)...\n\n";
        printHotel(hotel);
        delay(100);
    }
    // Заселяем нового гостя в комнату 1 (номер 1000)
    hotel[0] = 1000;
    clearScreen();
    cout << GREEN_COLOR << "A brand new guest has checked into room 1!" << RESET_COLOR << "\n\n";
    printHotel(hotel);

    // Теоретическое объяснение метода
    cout << "\n" << CYAN_COLOR << "Theoretical Explanation:" << RESET_COLOR << "\n";
    cout << "In an infinite hotel, even if every room is occupied, shifting each guest\n";
    cout << "from room n to room n+1 frees up room 1 for a new guest.\n";
    waitForEnter();
}

// 2. Бесконечное количество новых посетителей: сдвиг гостей в комнаты 2n (освобождаются нечётные номера)
void simulationInfiniteVisitors(vector<int>& hotel) {
    int n = hotel.size();
    vector<int> oldHotel = hotel;
    for (int i = 0; i < n; i++) hotel[i] = 0;
    for (int i = 0; i < n; i++) {
        int newIndex = 2 * (i + 1) - 1;
        if (newIndex < n)
            hotel[newIndex] = oldHotel[i];
        clearScreen();
        cout << "Resettlement (Infinite Visitors): shifting guests (room n → room 2*n)...\n\n";
        printHotel(hotel);
        delay(100);
    }
    // Заселяем новых гостей в освобождённые (нечётные) комнаты
    for (int i = 0; i < n; i++) {
        if (hotel[i] == 0) {
            int randNum = rand() % 9000 + 1000; // число от 1000 до 9999
            hotel[i] = 10000 + randNum; // метка новых гостей
            clearScreen();
            cout << "Checking in new guests...\n\n";
            printHotel(hotel);
            delay(50);
        }
    }
    clearScreen();
    cout << GREEN_COLOR << "Infinite new guests have been checked in to the vacant (odd) rooms!" << RESET_COLOR << "\n\n";
    printHotel(hotel);

    // Теоретическое объяснение метода
    cout << "\n" << CYAN_COLOR << "Theoretical Explanation:" << RESET_COLOR << "\n";
    cout << "By moving each guest from room n to room 2*n, all odd-numbered rooms become free.\n";
    cout << "Since the set of odd numbers is infinite and countable, these freed rooms\n";
    cout << "can be matched one-to-one with an infinite number of new guests.\n";
    waitForEnter();
}

// 3. Метод степени простого числа: гость из комнаты i → комната 2^i; для пассажиров автобуса – комнаты 3^n и далее.
void simulationPrimePowerMethod() {
    clearScreen();
    cout << YELLOW_COLOR << "Prime Power Method:" << RESET_COLOR << "\n\n";
    int count;
    cout << "Enter number of original guests to reassign (e.g., 8): ";
    cin >> count;
    for (int i = 1; i <= count; i++) {
        unsigned long long room = 1ULL << i; // 2^i
        cout << "Guest from room " << i << " → New room: " << room << "\n";
        delay(300);
    }
    cout << "\nNow, for additional passengers:\n";
    int busNum;
    cout << "Enter bus number (1 for first bus, 2 for second, etc.): ";
    cin >> busNum;
    cout << "Enter seat number: ";
    int seat;
    cin >> seat;
    int primes[] = { 3, 5, 7, 11, 13, 17, 19 };
    int prime = (busNum - 1 < 7) ? primes[busNum - 1] : primes[6];
    unsigned long long room = 1;
    for (int i = 0; i < seat; i++) {
        room *= prime;
    }
    cout << "\nPassenger from bus " << busNum << " seat " << seat
        << " → Room: " << room << "\n";

    cout << "\n" << CYAN_COLOR << "Theoretical Explanation:" << RESET_COLOR << "\n";
    cout << "Assigning rooms as powers of primes utilizes the uniqueness of prime factorizations.\n";
    cout << "No two guests will receive the same room number because every integer\n";
    cout << "has a unique prime factorization.\n";
    waitForEnter();
}

// 4. Метод факторизации целых чисел: для гостя из автобуса c на месте n назначается комната = 2^n * 3^c.
void simulationFactorizationMethod() {
    clearScreen();
    cout << YELLOW_COLOR << "Factorization Method:" << RESET_COLOR << "\n\n";
    int bus, seat;
    cout << "Enter bus number (c): ";
    cin >> bus;
    cout << "Enter seat number (n): ";
    cin >> seat;
    unsigned long long room = 1;
    for (int i = 0; i < seat; i++) room *= 2;
    for (int i = 0; i < bus; i++) room *= 3;
    cout << "\nFor passenger (bus " << bus << ", seat " << seat << ") → Room: " << room << "\n";

    cout << "\n" << CYAN_COLOR << "Theoretical Explanation:" << RESET_COLOR << "\n";
    cout << "Using the unique factorization theorem, we assign a distinct room number\n";
    cout << "by mapping the seat and bus numbers to exponents of distinct primes (2 and 3).\n";
    waitForEnter();
}

// 5. Метод чередования (по 3 цифры): дополняем ведущими нулями и чередуем цифры двух чисел.
string padNumber(const string& num, size_t len) {
    string padded = num;
    while (padded.length() < len)
        padded = "0" + padded;
    return padded;
}
void simulationInterleavingMethod() {
    clearScreen();
    cout << YELLOW_COLOR << "Interleaving Method (by 3 digits):" << RESET_COLOR << "\n\n";
    string busStr, seatStr;
    cout << "Enter bus number: ";
    cin >> busStr;
    cout << "Enter seat number: ";
    cin >> seatStr;
    size_t maxLen = max(busStr.length(), seatStr.length());
    while (maxLen % 3 != 0)
        maxLen++;
    busStr = padNumber(busStr, maxLen);
    seatStr = padNumber(seatStr, maxLen);
    string roomStr;
    for (size_t i = 0; i < maxLen; i++)
        roomStr.push_back((i % 2 == 0) ? busStr[i] : seatStr[i]);
    cout << "\nInterleaved room number: " << roomStr << "\n";

    cout << "\n" << CYAN_COLOR << "Theoretical Explanation:" << RESET_COLOR << "\n";
    cout << "By interleaving the digits of the bus and seat numbers (after padding them),\n";
    cout << "a unique room number is generated that fills the hotel completely without gaps.\n";
    waitForEnter();
}

// 6. Метод треугольного числа:
// Сначала переселяем гостя из комнаты n в T(n)=n(n+1)/2; затем для пассажира из автобуса c на месте n: комната = T(c+n-1)+n.
void simulationTriangularMethod() {
    clearScreen();
    cout << YELLOW_COLOR << "Triangular Number Method:" << RESET_COLOR << "\n\n";
    int count;
    cout << "Enter number of original guests (e.g., 8): ";
    cin >> count;
    for (int n = 1; n <= count; n++) {
        unsigned long long Tn = n * (n + 1ULL) / 2;
        cout << "Guest from room " << n << " → New room: T(" << n << ") = " << Tn << "\n";
        delay(250);
    }
    int bus, seat;
    cout << "\nFor additional passenger:\n";
    cout << "Enter bus number: ";
    cin >> bus;
    cout << "Enter seat number: ";
    cin >> seat;
    unsigned long long T_extra = ((bus + seat - 1) * (bus + seat)) / 2 + seat;
    cout << "Passenger from bus " << bus << " seat " << seat << " → Room: " << T_extra << "\n";

    cout << "\n" << CYAN_COLOR << "Theoretical Explanation:" << RESET_COLOR << "\n";
    cout << "Triangular numbers are used here to reassign guests such that every room is filled.\n";
    cout << "Additional passengers are assigned rooms based on a shifted triangular number sequence.\n";
    waitForEnter();
}

// 7. Высшие уровни бесконечности: для гостя с адресом 'место-автобус-паром' – комната = 2^(место) * 3^(автобус) * 5^(паром)
void simulationHigherInfinityMethod() {
    clearScreen();
    cout << YELLOW_COLOR << "Higher Infinity Method:" << RESET_COLOR << "\n\n";
    int ferry, bus, seat;
    cout << "Enter ferry number: ";
    cin >> ferry;
    cout << "Enter bus number: ";
    cin >> bus;
    cout << "Enter seat number: ";
    cin >> seat;
    unsigned long long room = 1;
    for (int i = 0; i < seat; i++) room *= 2;
    for (int i = 0; i < bus; i++) room *= 3;
    for (int i = 0; i < ferry; i++) room *= 5;
    cout << "\nPassenger (ferry " << ferry << ", bus " << bus << ", seat " << seat << ") → Room: " << room << "\n";

    cout << "\n" << CYAN_COLOR << "Theoretical Explanation:" << RESET_COLOR << "\n";
    cout << "By extending the factorization method with an extra level (ferry) and using 5 as a prime,\n";
    cout << "we can assign unique room numbers even for a three-dimensional infinite scenario.\n";
    waitForEnter();
}

// 8. Двоичный метод с разделением групп и удалением одного нуля из каждой группы.
// Адрес задаётся как последовательность чисел через дефис (например, 2-5-4-3-1).
unsigned long long binaryEncoding(const vector<int>& address) {
    string binStr;
    for (size_t i = 0; i < address.size(); i++) {
        int countZeros = max(0, address[i] - 1);
        for (int j = 0; j < countZeros; j++) {
            binStr.push_back('0');
        }
        if (i < address.size() - 1)
            binStr.push_back('1');
    }
    unsigned long long room = 0;
    for (char ch : binStr) {
        room = (room << 1) + (ch - '0');
    }
    return room;
}
void simulationBinaryEncodingMethod() {
    clearScreen();
    cout << YELLOW_COLOR << "Binary Encoding Method:" << RESET_COLOR << "\n\n";
    cout << "Enter guest address as numbers separated by '-' (e.g., 2-5-4-3-1): ";
    string input;
    cin >> input;
    vector<int> address;
    stringstream ss(input);
    string token;
    while (getline(ss, token, '-')) {
        address.push_back(stoi(token));
    }
    unsigned long long room = binaryEncoding(address);
    cout << "\nFor guest with address " << input << " → Room (binary encoded): " << room << "\n";

    cout << "\n" << CYAN_COLOR << "Theoretical Explanation:" << RESET_COLOR << "\n";
    cout << "This method encodes a guest's multi-level address into a binary number by creating\n";
    cout << "groups of zeros (with one zero removed from each group) separated by ones. This ensures\n";
    cout << "that every room gets uniquely assigned without gaps.\n";
    waitForEnter();
}

// ============================
// Вывод теоретической справки (общей)
// ============================

void printTheory() {
    clearScreen();
    setColor(GREEN_COLOR);
    cout << "\n=== Theory of the Grand Hotel Paradox ===\n";
    cout << "Imagine a hotel with an infinite number of rooms – all are occupied.\n\n";
    cout << "1. New Visitor: Shift each guest from room n to room n+1, freeing room 1.\n";
    cout << "2. Infinite New Visitors: Shift each guest from room n to room 2*n, freeing odd-numbered rooms.\n";
    cout << "3. Prime Power Method: Reassign guests into rooms numbered as powers of primes.\n";
    cout << "4. Factorization Method: Use the unique prime factorization (e.g., room = 2^n * 3^c).\n";
    cout << "5. Interleaving Method: Alternate digits (in groups of three) of bus and seat numbers.\n";
    cout << "6. Triangular Number Method: Reassign guests to triangular numbers T(n)=n(n+1)/2;\n";
    cout << "   for extra passengers, use T(c+n-1)+n.\n";
    cout << "7. Higher Infinity Method: For multi-level addresses (ferry-bus-seat), use room = 2^n * 3^c * 5^f.\n";
    cout << "8. Binary Encoding Method: Encode the guest address in binary, deleting one zero per group,\n";
    cout << "   so that every room is uniquely occupied.\n";
    cout << "\nThese methods illustrate that a countably infinite set can be put in one-to-one\n";
    cout << "correspondence with one of its proper subsets, defying our finite intuitions.\n";
    cout << "===========================================\n" << RESET_COLOR;
    waitForEnter();
}

// ============================
// Главное меню программы
// ============================

void showMainMenu() {
    clearScreen();
    printWelcomeScreen();
    cout << "\n" << YELLOW_COLOR << "Choose an occupancy method:" << RESET_COLOR << "\n";
    cout << "1. New Visitor (shift: room n -> n+1)\n";
    cout << "2. Infinite New Visitors (shift: room n -> 2*n)\n";
    cout << "3. Prime Power Method\n";
    cout << "4. Factorization Method\n";
    cout << "5. Interleaving Method (by 3 digits)\n";
    cout << "6. Triangular Number Method\n";
    cout << "7. Higher Infinity Method (ferry-bus-seat)\n";
    cout << "8. Binary Encoding Method\n";
    cout << "9. View Theory\n";
    cout << "0. Exit\n";
    cout << "\nYour choice: ";
}

int main() {
    srand(time(NULL));
    bool running = true;
    while (running) {
        showMainMenu();
        int choice;
        cin >> choice;
        cin.ignore(); // очистка символа новой строки
        if (choice == 0) {
            running = false;
            break;
        }
        else if (choice == 1 || choice == 2) {
            // Для режимов, где моделируется отель с 100 комнатами
            const int totalRooms = 100;
            vector<int> hotel(totalRooms);
            for (int i = 0; i < totalRooms; i++) {
                hotel[i] = i + 1;
            }
            if (choice == 1)
                simulationNewVisitor(hotel);
            else
                simulationInfiniteVisitors(hotel);
        }
        else if (choice == 3)
            simulationPrimePowerMethod();
        else if (choice == 4)
            simulationFactorizationMethod();
        else if (choice == 5)
            simulationInterleavingMethod();
        else if (choice == 6)
            simulationTriangularMethod();
        else if (choice == 7)
            simulationHigherInfinityMethod();
        else if (choice == 8)
            simulationBinaryEncodingMethod();
        else if (choice == 9)
            printTheory();
        else {
            cout << "\nInvalid choice. Please try again.\n";
            delay(1000);
        }
    }
    clearScreen();
    setColor(GREEN_COLOR);
    cout << "\nThank you for exploring the Grand Hotel Paradox!\n" << RESET_COLOR;
    waitForEnter();
    return 0;
}
