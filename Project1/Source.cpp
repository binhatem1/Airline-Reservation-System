#include <iostream>
#include<string>
#include <conio.h>
using namespace std;
#define sep "\t|"
const int schedule_size = 99;
const int passenger_size = 99;
const int ticket_size = 99;

struct schedule {
	int flight_num, available_seats, flight_date[3];
	string departure_city;
	int  taking_off_hour, taking_off_minute;
	string arrival_city;
	int  reaching_hour, reaching_minute;
};
struct passenger {
	string ID, name, address, phone_number, email, password, log;
};
struct ticket {
	string number, passenger_ID;
	int flight_date[3], flight_num;
};

//DECLARATIONS

int menu();
void adminPrompt();
void admin_access();
void add_schedule();
void edit_schedule(int);
void delete_flight(int);

void menuPassenger();
bool login(string email, string pass);
void loginPrompt();
string emailPrompt();
void signUp();

int getFlightIndex(int);
int getTicketIndex(string);

void cancelTicket(string);
void addTicket(schedule);

schedule displayFlights();
schedule displayFlights(string, string);
schedule displayFlights(string , string , int);
schedule displayFlights(string, string, int taking_off_time[2], int arrival_time[2], int date[3], int);
passenger displayPassengers();
ticket displayTickets();

int input_num();
//GLOBAL VARS

int userIndex = 0;
schedule flights[schedule_size]
= {
	{132,200,{2,2,2023},"Tokyo",12,40,"Cairo",16,00},
	{888,10,{3,9,2023},"Berlin",7,00,"Sydney",14,40},
	{103,500,{4,4,2023},"Mekkah",23,10,"Paris",7,00},
	{130,42,{5,4,2023},"Mekkah",23,10,"Paris",7,00},
	{108,19,{8,4,2023},"Mekkah",22,50,"Paris",1,00},
	{},
	{741,130,{9,3,2023},"Kuwait",2,50,"Alex",16,10}
};
passenger passengers[passenger_size]
= {
	{"400","Ahmed","addr1","010101010","ahmed@gmail.com","123"},
	{"401","Ali","addr2","011123465","ali@gmail.com","123"},
	{"402","Ramy","addr3","012456220","ramy@gmail.com","123"},
	{"403","Waleed","addr4","0105601472","waleed@hotmail.com","123"}
};
ticket tickets[ticket_size]
= {
	{"1000","400",{3,9,2023},888},
	{"1001","400",{4,4,2023},103},
	{},
	{"1002","402",{2,2,2023},132},
	{"1003","403",{2,2,2023},132}
};



int main() {

	int choice = menu();
	switch (choice)
	{
	case 1:
	{
		adminPrompt();
		break;
	}
	case 2:
	{
		loginPrompt();
	}
	case 3:
	{
		signUp();
		break;
	}
	}
	return 0;
}


int menu()
{
	int choice;
	cout << "\n\n                    -----------------------" << endl << "                    WELCOME TO FCIS AIRLINE  " << endl << "                    -----------------------";
	cout << "\n\n\n";
	cout << "|press 1 to login as admin|";
	cout << "\n\n|press 2 to login as a passenger|";
	cout << "\n\n|press 3 to register a new account|";
	cout << "\n\nplease enter your choice  ";
	cin >> choice;
	return choice;

}

bool login(string email, string pass)
{
	for (int i = 0; i < passenger_size; i++)
	{
		if (email == passengers[i].email && pass == passengers[i].password)
		{
			userIndex = i;
			return 1;
		}
	}
	return 0;

}
void loginPrompt() {
	string email, password;
	int choice = 1;

	cout << "\nEnter your email: "; cin >> email;
	cout << "Enter your password: ";
	int i = 0;
	char  ch;
	while ((ch = _getch()) != '\r')
	{
		password += ch;
		cout << '*';
		i++;
	}

	cout << endl << password;

	if (!login(email, password))
	{
		cout << "\n*********\nInvalid email or password\n\n[1] Retry\n[2] Back to Main Menu\n";
		do
		{
			cin >> choice;
			switch (choice)
			{
			case 1: { loginPrompt(); break; }
			case 2: { main(); break; }
			default: { cout << "\nInvalid choice! Please try again\n"; break; }
			}

		} while (choice != 1 && choice != 2);

	}
	else menuPassenger();
}
void signUp()
{
	int index;
	for (int i = 0; i < ticket_size; i++)
	{
		if (passengers[i].ID.empty()) index = i;
	}
	cout << "\t\t\tAccount Registration\n";
	cout << "\t\t\t**********************\n\n";

	passengers[index].ID = "405";
	passengers[index].email = emailPrompt();
	cout << "Password: "; cin >> passengers[index].password;
	cout << "Name: "; cin >> passengers[index].name;
	cout << "Address: "; cin >> passengers[index].address;
	cout << "Phone Number: "; cin >> passengers[index].phone_number;

	cout << "Signed Up successfully!\n";
}
bool usedEmail(string email) {
	for (int i = 0; i < passenger_size; i++)
	{
		if (email == passengers[i].email)
		{
			return 1;
		}
	}
	return 0;
}
string emailPrompt() {
	string email;
	cout << "Email: "; cin >> email;
	if (usedEmail(email))
	{
		cout << "\nEmail is used before! Please try again\n";
		emailPrompt();
	}
	return email;
}
void adminPrompt()
{
	string email, password; int choice;

	cout << "\nEnter your email: "; cin >> email;
	cout << "Enter your password: ";
	int i = 0;
	char  ch;
	while ((ch = _getch()) != '\r')
	{
		password += ch;
		cout << '*';
		i++;
	}

	if (email == "admin@gmail.com" && password == "admin123")
		admin_access();
	else
	{
		cout << "\n**************************************\n";
		cout << "\nInvalid email or password\n\n[1] Retry\n[2] Back to Main Menu\n";
	}


	do
	{
		cin >> choice;
		switch (choice)
		{
		case 1: { adminPrompt(); break; }
		case 2: { main(); break; }
		default: { cout << "Invalid choice! Please try again\n"; break; }
		}

	} while (choice != 1 && choice != 2);

}


//************************ADMIN*******************************//

int num = 7, actual_num = 7;
void add_schedule() {
	cout << "\nEnter the flight number\n";
	cin >> flights[num].flight_num;
	cout << "Enter the number of available seats\n";
	cin >> flights[num].available_seats;
	cout << "Enter the day of flight\n";
	cin >> flights[num].flight_date[0];
	cout << "Enter the month\n";
	cin >> flights[num].flight_date[1];
	cout << "Enter the year\n";
	cin >> flights[num].flight_date[2];
	cout << "Enter the departure city\n";
	cin >> flights[num].departure_city;
	cout << "Enter the taking off hour\n";
	cin >> flights[num].taking_off_hour;
	cout << "Enter the taking off minute\n";
	cin >> flights[num].taking_off_minute;
	cout << "Enter the arrival city\n";
	cin >> flights[num].arrival_city;
	cout << "Enter the reaching hour\n";
	cin >> flights[num].reaching_hour;
	cout << "Enter the reaching minute\n";
	cin >> flights[num].reaching_minute;
	num++;
	actual_num++;
}
void edit_schedule(int k) {

	cout << "\n***********************************************************\n";
	cout << "\nEDIT OPTIONS:\n\n1.the number of available seats\n2.the date of flight\n3.the departure city\n4.the time of taking off\n5.arrival city\n6.reaching time\n\nHow many things you want to edit ?";
	int trials, operation;
	cin >> trials;
	while (trials--)
	{
		cout << "Enter the number which you want do its operation\n";
		cin >> operation;
		if (operation == 1)
		{
			cout << "Enter the new number\n";
			cin >> flights[k].available_seats;
		}
		else if (operation == 2)
		{
			cout << "Enter the day\n";
			cin >> flights[k].flight_date[0];
			cout << "Enter the month\n";
			cin >> flights[k].flight_date[1];
			cout << "Enter the year\n";
			cin >> flights[k].flight_date[2];
		}
		else if (operation == 3)
		{
			cout << "Enter the departure city\n";
			cin >> flights[k].departure_city;
		}
		else if (operation == 4)
		{
			cout << "Enter hour\n";
			cin >> flights[k].taking_off_hour;
			cout << "Enter minute\n";
			cin >> flights[k].taking_off_minute;
		}
		else if (operation == 5)
		{
			cout << "Enter the arrival city\n";
			cin >> flights[k].arrival_city;
		}
		else if (operation == 6)
		{
			cout << "Enter hour\n";
			cin >> flights[k].reaching_hour;
			cout << "Enter minute\n";
			cin >> flights[k].reaching_minute;
		}
		else
			cout << "Invalid number !\n";
	}

	cout << "\nEdited successfully!\n\n";
	admin_access();
}
void delete_flight(int q) {

	flights[getFlightIndex(q)] = { 0,0,0,0,0,"",0,0,"",0,0 };
	cout << "\nDeleted successfully!\n";

}
void admin_access() {
	cout << "\n*****************************************************";
	cout << "\nChoose the Operation you want to do !\n\n\t[1] Add new schedule\n\t[2] Edit an existing flight\n\t[3] Delete an existing schedule\n\t[4] Back to Main Menu\n\n";
	int i;
	cin >> i;

	while (i != 1 && i != 2 && i != 3 && i != 4)
	{
		cout << "\nPlease write a correct number!\n";
		cin >> i;
	}
	if (i == 1)
		add_schedule();
	else if (i == 2)
	{
		schedule flight = displayFlights();
		edit_schedule(flight.flight_num);
	}
	else if (i == 3)
	{
		if (actual_num < 1)
		{
			cout << "\nThere isn't any flight to delete!\n";
			admin_access();
		}
		else
		{
			cout << "\n\n*****DELETE FLIGHT*****\n";
			schedule flight = displayFlights();
			delete_flight(flight.flight_num);
		}
	}
	else if (i == 4) main();

	admin_access();

}

int getFlightIndex(int flightNumber) {
	for (int i = 0; i < schedule_size; i++)
	{
		if (flightNumber == flights[i].flight_num)
		{
			return i;
		}
	}
}
bool ticketExists(string ticketNumber) {
	for (int i = 0; i < ticket_size; i++)
	{
		if (ticketNumber == tickets[i].number)
		{
			return 1;
		}
	}
	return 0;
}
int getTicketIndex(string ticketNumber) {
	for (int i = 0; i < ticket_size; i++)
	{
		if (ticketNumber == tickets[i].number)
		{
			return i;
		}
	}
}

//************************PASSENGER*******************************//

void menuPassenger() {
	int choice;
	cout << "\n**********************************\n";
	cout << "\n\nWelcome, " << passengers[userIndex].name << " :)\n";
	do
	{
		cout << "\n\t[1] Add a new reservation\n\t[2] Cancel reservation\n\t[3] Modify Reservation\n\t[4] Show reservation log\n\t";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			int x;
			do
			{
				cout << "\n\t[1] List all available flights\n\t[2] Search";
				cin >> x;
				switch (x)
				{
				case 1:
				{
					schedule f = displayFlights();
					addTicket(f);  break;
				}

				case 2:
				{

					int counter = 0, wanted_filter, flight_Num = -1, date[3] = {}, taking_off_time[2] = { -1 }, arrival_time[2] = { -1 };
					string dep = "0", arr = "0";
					string select_other_filter_too;
					cout << "Enter the filter which you want to use in searching\1.Flight number\n2.Flight date\n3.Flight path\n4.Taking off time\n5.Arrival time\n";
					do
					{
						wanted_filter = input_num();
						switch (wanted_filter)
						{
						case 1: {
							cout << "Enter the flight number\n";
							flight_Num = input_num();
							counter++;
							break;
						}
						case 2: {
							cout << "Enter the day\n";
							do
							{
								date[0] = input_num();
								if (date[0] < 1 || date[0]>31)
									cout << "Please enter possible number.\n";
							} while (date[0] < 1 || date[0]>31);
							cout << "Enter the month\n";
							do
							{
								date[1] = input_num();
								if (date[1] < 1 || date[1]>12)
									cout << "Please enter possible number.\n";
							} while (date[1] < 1 || date[0]>12);
							cout << "Enter the year\n";
							do
							{
								date[2] = input_num();
								if (date[2] < 2023)
									cout << "Please enter possible number.\n";
							} while (date[2] < 2023);
							counter++;
							break;
						}
						case 3: {
							cout << "Enter the depature\n";
							cin >> dep;
							cout << "Enter the arrival\n";
							cin >> arr;
							counter++;
							break;
						}
						case 4: {
							cout << "Enter the hour\n";
							do
							{
								taking_off_time[0] = input_num();
								if (taking_off_time[0] < 0 || taking_off_time[0] > 23)
									cout << "Please enter possible number.\n";
							} while (taking_off_time[0] < 0 || taking_off_time[0] > 23);
							cout << "Enter the minute\n";
							do
							{
								taking_off_time[1] = input_num();
								if (taking_off_time[1] < 0 || taking_off_time[1] > 59)
									cout << "Please enter possible number.\n";
							} while (taking_off_time[1] < 0 || taking_off_time[1] > 59);
							counter++;
							break;
						}
						case 5: {
							cout << "Enter the hour\n";
							do
							{
								arrival_time[0] = input_num();
								if (arrival_time[0] < 0 || arrival_time[0] > 23)
									cout << "Please enter possible number.\n";
							} while (arrival_time[0] < 0 || arrival_time[0] > 23);
							cout << "Enter the minute\n";
							do
							{
								arrival_time[1] = input_num();
								if (arrival_time[1] < 0 || arrival_time[1] > 59)
									cout << "Please enter possible number.\n";
							} while (arrival_time[1] < 0 || arrival_time[1] > 59);
							counter++;
							break;
						}
						default:
							cout << "Please enter a correct number";
						}
						if (counter > 0)
						{
							cout << "If you want to add other filter , enter y or Y\n";
							cin >> select_other_filter_too;
						}
					} while (wanted_filter < 1 || wanted_filter>5 || counter < 1 || select_other_filter_too == "y" || select_other_filter_too == "Y");
					schedule f = displayFlights(dep, arr, taking_off_time, arrival_time, date, flight_Num);
					addTicket(f);
					break;
				}
				
				default:  cout << "\nInvalid choice! Please try again\n"; break;
				}

			} while (choice != 1 && choice != 2);

			break;
		}
		case 2:
		{
			ticket t = displayTickets();
			cancelTicket(t.number);
			break;
		}
		case 3:
		{
			ticket t = displayTickets();
			schedule f = displayFlights(flights[getFlightIndex(t.flight_num)].departure_city, flights[getFlightIndex(t.flight_num)].arrival_city,t.flight_num);
			cancelTicket(t.number);
			addTicket(f);
		}
		case 4:
		{
			cout << "\n***\nLOG:\n***\n";
			cout << passengers[userIndex].log;
		}
		default: { cout << "\nInvalid choice! Please try again\n"; break;}
		}

	} while (true);

	menuPassenger();
}
void cancelTicket(string ticketNumber) {

	int t = getTicketIndex(ticketNumber);
	int f = getFlightIndex(tickets[t].flight_num);
	flights[f].available_seats++;

	tickets[t].number = "";
	tickets[t].passenger_ID = "";
	tickets[t].flight_date[0] = 0;
	tickets[t].flight_date[1] = 0;
	tickets[t].flight_date[2] = 0;
	tickets[t].flight_num = 0;

	string log = "\Cancelled reservation " + to_string(tickets[t].flight_num);
	passengers[userIndex].log.append(log);

}
void addTicket(schedule flight) {

	flights[getFlightIndex(flight.flight_num)].available_seats--;
	int index;
	for (int i = 0; i < ticket_size; i++)
	{
		if (tickets[i].number.empty()) index = i;
	}
	tickets[index].number = to_string(flight.flight_num) + to_string(flight.available_seats) + to_string(rand() % 10);
	tickets[index].flight_num = flight.flight_num;
	tickets[index].flight_date[0] = flight.flight_date[0];
	tickets[index].flight_date[1] = flight.flight_date[1];
	tickets[index].flight_date[2] = flight.flight_date[2];
	tickets[index].passenger_ID = passengers[userIndex].ID;

	string log = "\nReserved flight " + to_string(flight.flight_num);
	passengers[userIndex].log.append(log);

	cout << "\nReserved successfully! :)\n";
}

schedule displayFlights() {
	int counter = 0, choice, flightIndex[schedule_size];

	cout << "\n**************************************************\n";
	cout << "Index" << sep << "No." << sep << "Seats" << sep << "Day" << sep << "Month" << sep << "Year" << sep << "From" << sep << "Hour" << sep << "Minute" << sep << "To" << sep << "Hour" << sep << "Minute" << endl;
	cout << "_________________________________________________________________________________________________" << endl;

	for (int i = 0; i < schedule_size; i++)
	{
		if (flights[i].flight_num == 0) continue;

		cout << "[" << counter + 1 << "]" << sep << flights[i].flight_num << sep << flights[i].available_seats << sep << flights[i].flight_date[0] << sep << flights[i].flight_date[1] << sep << flights[i].flight_date[2] << sep << flights[i].departure_city << sep << flights[i].taking_off_hour << sep << flights[i].taking_off_minute << sep << flights[i].arrival_city << sep << flights[i].reaching_hour << sep << flights[i].reaching_minute << endl;
		flightIndex[counter] = i;
		counter++;
	}

	if (counter == 0)
	{
		cout << "\n*************\nNo Flights Available\n*************\n";
		if (userIndex) menuPassenger(); else admin_access();
	}
	else {

		do
		{
			cout << "\nFlight Index: ";
			cin >> choice;
			if (choice < 1 || choice > counter)
				cout << "\nInvalid choice! Please retry\n";
			else break;
		} while (true);
	}

	return flights[flightIndex[choice - 1]];

}
schedule displayFlights(string departure, string arrival) {
	int counter = 0, choice, flightIndex[schedule_size];

	cout << "\n**************************************************\n";
	cout << "Index" << sep << "No." << sep << "Seats" << sep << "Day" << sep << "Month" << sep << "Year" << sep << "From" << sep << "Hour" << sep << "Minute" << sep << "To" << sep << "Hour" << sep << "Minute" << endl;
	cout << "_________________________________________________________________________________________________" << endl;

	for (int i = 0; i < schedule_size; i++)
	{
		if (flights[i].flight_num == 0 || departure != flights[i].departure_city || arrival != flights[i].arrival_city) continue;

		cout << "[" << counter + 1 << "]" << sep << flights[i].flight_num << sep << flights[i].available_seats << sep << flights[i].flight_date[0] << sep << flights[i].flight_date[1] << sep << flights[i].flight_date[2] << sep << flights[i].departure_city << sep << flights[i].taking_off_hour << sep << flights[i].taking_off_minute << sep << flights[i].arrival_city << sep << flights[i].reaching_hour << sep << flights[i].reaching_minute << endl;
		flightIndex[counter] = i;
		counter++;
	}

	if (counter == 0)
	{
		cout << "\n*************\nNo Flights Available\n*************\n";
		if (userIndex) menuPassenger(); else admin_access();
	}
	else {

		do
		{
			cout << "\nFlight Index: ";
			cin >> choice;
			if (choice < 1 || choice > counter)
				cout << "\nInvalid choice! Please retry\n";
			else break;
		} while (true);
	}

	return flights[flightIndex[choice - 1]];

}
schedule displayFlights(string departure, string arrival, int skipFlightNumber) {
	int counter = 0, choice, flightIndex[schedule_size];

	cout << "\n**************************************************\n";
	cout << "Index" << sep << "No." << sep << "Seats" << sep << "Day" << sep << "Month" << sep << "Year" << sep << "From" << sep << "Hour" << sep << "Minute" << sep << "To" << sep << "Hour" << sep << "Minute" << endl;
	cout << "_________________________________________________________________________________________________" << endl;

	for (int i = 0; i < schedule_size; i++)
	{
		if (flights[i].flight_num == 0 || departure != flights[i].departure_city || arrival != flights[i].arrival_city || skipFlightNumber == flights[i].flight_num) continue;

		cout << "[" << counter + 1 << "]" << sep << flights[i].flight_num << sep << flights[i].available_seats << sep << flights[i].flight_date[0] << sep << flights[i].flight_date[1] << sep << flights[i].flight_date[2] << sep << flights[i].departure_city << sep << flights[i].taking_off_hour << sep << flights[i].taking_off_minute << sep << flights[i].arrival_city << sep << flights[i].reaching_hour << sep << flights[i].reaching_minute << endl;
		flightIndex[counter] = i;
		counter++;
	}

	if (counter == 0)
	{
		cout << "\n*************\nNo Flights Available\n*************\n";
		if (userIndex) menuPassenger(); else admin_access();
	}
	else {

		do
		{
			cout << "\nFlight Index: ";
			cin >> choice;
			if (choice < 1 || choice > counter)
				cout << "\nInvalid choice! Please retry\n";
			else break;
		} while (true);
	}

	return flights[flightIndex[choice - 1]];

}
schedule displayFlights(string departure, string arrival, int taking_off_time[2], int arrival_time[2], int date[3], int flight_num) {
	int counter = 0, choice, flightIndex[schedule_size];

	cout << "\n**************************************************\n";
	cout << "Index" << sep << "No." << sep << "Seats" << sep << "Day" << sep << "Month" << sep << "Year" << sep << "From" << sep << "Hour" << sep << "Minute" << sep << "To" << sep << "Hour" << sep << "Minute" << endl;
	cout << "_________________________________________________________________________________________________" << endl;

	for (int i = 0; i < schedule_size; i++)
	{
		if (flights[i].flight_num == 0 || (departure != flights[i].departure_city) || (arrival != flights[i].arrival_city) || (taking_off_time[0] != -1 && (taking_off_time[0] != flights[i].taking_off_hour || taking_off_time[1] != flights[i].taking_off_minute)) || (arrival_time[0] != -1 && (arrival_time[0] != flights[i].reaching_hour || arrival_time[1] != flights[i].reaching_minute)) || (flight_num != -1 && flight_num != flights[i].flight_num) || (date[0] != 0 && (date != flights[i].flight_date)))
			continue;

		cout << "[" << counter + 1 << "]" << sep << flights[i].flight_num << sep << flights[i].available_seats << sep << flights[i].flight_date[0] << sep << flights[i].flight_date[1] << sep << flights[i].flight_date[2] << sep << flights[i].departure_city << sep << flights[i].taking_off_hour << sep << flights[i].taking_off_minute << sep << flights[i].arrival_city << sep << flights[i].reaching_hour << sep << flights[i].reaching_minute << endl;
		flightIndex[counter] = i;
		counter++;
	}

	if (counter == 0)
	{
		cout << "\n*************\nNo Flights Available\n*************\n";
		if (userIndex)
			menuPassenger();
		else
			admin_access();
	}
	else {

		do
		{
			cout << "\nFlight Index: ";
			cin >> choice;
			if (choice < 1 || choice > counter)
				cout << "\nInvalid choice! Please retry\n";
			else break;
		} while (true);
	}

	return flights[flightIndex[choice - 1]];

}
passenger displayPassengers() {
	int choice;

	cout << "Index" << sep << "ID" << sep << "Name" << sep << "Address" << sep << "Phone No." << sep << "Log" << endl;
	cout << "__________________________________________________________________" << endl;
	for (int i = 0; i < passenger_size; i++)
	{
		if (passengers[i].ID.empty()) continue;
		cout << "[" << i + 1 << "]" << sep << passengers[i].ID << sep << passengers[i].name << sep << passengers[i].address << sep << passengers[i].phone_number << passengers[i].log << endl;
	}
	cout << "\nPassenger Index: ";
	cin >> choice;
	return passengers[choice - 1];

}
ticket displayTickets() {
	int counter = 0, choice, ticketIndex[ticket_size];

	cout << "Index" << sep << "No." << sep << "ID" << sep << "Day" << sep << "Month" << sep << "Year" << sep << "FNo." << endl;
	cout << "___________________________________________________________________________" << endl;
	for (int i = 0; i < ticket_size; i++)
	{
		if (tickets[i].number.empty() || tickets[i].passenger_ID != passengers[userIndex].ID) continue;

		cout << "[" << counter + 1 << "]" << sep << tickets[i].number << sep << tickets[i].passenger_ID << sep << tickets[i].flight_date[0] << sep << tickets[i].flight_date[1] << sep << tickets[i].flight_date[2] << sep << tickets[i].flight_num << endl;
		ticketIndex[counter] = i;counter++;
	}
	cout << "\nTicket Index: ";
	cin >> choice;
	return tickets[ticketIndex[choice - 1]];
}

int input_num()
{
	string temp;
	bool invalid;
	do
	{
		invalid = 0;
		cin >> temp;
		for (int i = 0; i < temp.size(); i++)
		{
			if (temp[i] < '0' || temp[i]>'9')
			{
				cout << "Invalid ! Reenter please.\n";
				invalid = 1;
				break;
			}
			if (invalid)
				break;
		}
	} while (invalid);
	int temp_num = 0;
	for (int i = 0; i < temp.size(); i++)
	{
		temp_num += temp[i] - '0';
		if (i != temp.size() - 1)
			temp_num *= 10;
	}
	return temp_num;
}