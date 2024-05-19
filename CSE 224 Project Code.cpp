#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Bus;

class Student {
public:
    string studentID;
    string gender;
    string name;
public:
    Student(const string& id, const string& studentGender, const string& studentName)
    : studentID(id), gender(studentGender), name(studentName) {}

    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "Student ID: " << studentID << endl;
        cout << "Gender (Male/Female): " << gender << endl;
    }

    // Method 1: to book multiple seats on a bus. Will define it outside the class later.
    void bookSeats(Bus& bus);
};

class Bus {
public:
    string name;
    vector<bool> seats;

public:

    // "seats" attribute hocce ekta vector
    // Vector er index hocce seat no and element hocce bool type: true or false
    // seat available hole value false, occupied hole true. 
    // initially sob seat khali tai sob false, like seats={0,0,0,.....}
    // setas[0] ei seat ta driver er
    Bus(const string& busName) : name(busName), seats(51, false) {} // 0-based index

    // Method 1: to book only one seat per call
    void bookSeat(int seatNumber) {
        seats[seatNumber] = true;
    }

    // Method 2: to check if a seat is occupied or not
    bool isSeatOccupied(int seatNumber) const {
        return seats[seatNumber];
    }

    // Method 3: to display seat availability or whole bus scanning, jemon  ta kori amra seat dorte uthar pore lmao
    void displaySeatAvailability() const {
        cout << "Seat availability for bus " << name << ":" << endl;
        for (int i = 1; i <= 50; ++i) {
            cout << "Seat " << i << ": ";
            if (seats[i]) {
                cout << "Occupied" << endl;
            } else {
                cout << "Available" << endl;
            }
        }
    }
};

//Creating a txt file to save reservation data
ofstream my_file("reservation_file_data.txt");

// Defining Method 1 of Student  class to book seats on a bus object
void Student::bookSeats(Bus& bus) {
    int numSeats;
    // Bus ekta object hishebe pass korar por age dekhi eektu seat teat kemon khali 
    bus.displaySeatAvailability();
    cout << "How many seats do you want to book? "<<endl;
    cin >> numSeats;
    while (numSeats > 30){
    cout << "You can't book more that 30 seats, type again!"<<endl;
    cin >> numSeats;
    }
    // New vector, for personal use, mane student/user er dhora seat data save rakhar jonno
    vector<int> bookedSeats;
    cout << "Enter specific seat numbers to book (1 to 50): "<<endl;
    for (int i = 0; i < numSeats; ++i) {
        int seatNumber;
        cin >> seatNumber;
        if (seatNumber >= 1 && seatNumber <= 50) {
            if (!bus.isSeatOccupied(seatNumber)) {
                if ((gender=="Male" || gender=="male") && ((seatNumber >= 1 && seatNumber <= 9) || (seatNumber >= 31 && seatNumber <= 36))) {
                cout << "Seat from 1 to 9 and 31 to 36, these seats are for females only. You should be ashamed. "<<endl;
                cout << "DSW must be informed!!!"<<endl;
                numSeats++;
                cout << "Choose another seat no. please, which is valid for male students!"<<endl;}
                else{
                bus.bookSeat(seatNumber);
                // Student er dhora seat er number new vector tai push/entry kortesi
                bookedSeats.push_back(seatNumber);
                }
                }
            else {
                numSeats++;
                cout << "Seat number " << seatNumber << " is already occupied!" << endl;
                cout << "Choose another unoccupied seat please"<<endl;
            }
        } else {
            numSeats++;
            cout << "Choose another valid seat no. please"<<endl;
            cout << "Invalid seat number: " << seatNumber << endl;
        }
    }

    //Saving outputs in the txt file we have written previously
    my_file<<"Booked seats by Id "<<studentID<<" in "<<bus.name<<":"<<endl;
    for (int seat : bookedSeats) {
        my_file << seat << " ";
    }
    my_file<<endl;
    // Printing outputs
    cout << "Booked seats by Id "<<studentID<<" in "<<bus.name<<":"<<endl;
    for (int seat : bookedSeats) {
        cout << seat << " ";
    }
    cout << endl;
    cout << "Bus seat reservation data updated"<<endl;
    bus.displaySeatAvailability();
}


int main() {
    cout << "Welcome to the CUET Student Bus Seat Reservation System!" << endl;
    
    // Cerating 7 bus objects of CUET

    Bus bus_1("Meghna");
    Bus bus_2("Bhuriganga");
    Bus bus_3("Rupsha");
    Bus bus_4("Surma");
    Bus bus_5("Matamuhuri");
    Bus bus_6("Shangu");
    Bus bus_7("Turag");

    // Sob bus object ekta vector a rakkhlam
    vector<Bus> buses={bus_1,bus_2,bus_3,bus_4,bus_5,bus_6,bus_7};
    
    int numStudents;
    cout<<"How many users/students are here to book seat?"<<endl;
    cin>> numStudents;
    int i=1;

    // Loop for multiple useer, jotojon seat dorte asche totobar cholbe
    while (i<=numStudents)
    {
    cout<<"Colecting info for user/student no "<<i<<endl;
    cout<<"Choose a bus from Meghna(1), Bhuriganga(2), Rupsha(3), Surma(4), Matamuhuri(5), Shangu(6), Turag(7)"<<endl;
    // Bus koto no choose korse etar index nicchi
    int bus_no;
    cin>> bus_no;

    while (bus_no < 1 || bus_no > 7) {
            cout << "Invalid bus choice. Please enter a number between 1 and 7." << endl;
            cin >> bus_no;   
    }

    // Getting student information to create one Student object every time for each student/user
    string studentID, studentName, studentGender;
    cout << "Enter your name: ";
    cin>> studentName;
    cout << "Enter your student ID: ";
    cin >> studentID;
    cout << "Enter your gender (Male/Female): ";
    cin >> studentGender;

    // Create a student object
    Student student(studentID, studentGender, studentName);
    student.displayInfo();
    // Calling that magical method of Student class, that will do the rest.
    student.bookSeats(buses[bus_no-1]);
    i++;
}
my_file<<"All the other seats are available"<<endl;
my_file.close();
return 0;
}

