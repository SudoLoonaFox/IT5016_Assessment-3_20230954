#include<iostream>
#include<string>
using namespace std;

class Ticket{
	private:
		int num;
		string name;
		string staff_id = "Unset";
		string email;
		string description;
		string response = "Not Yet Provided";
		string status = "Open";
		bool resolved = false;

		void password_change(){
			resolve_ticket(staff_id.substr(2) + name.substr(3));
		}

	public:
		void create(int num_i, string name_i, string staff_id_i, string email_i, string description_i){
			num = num_i;
			name = name_i;
			staff_id = staff_id_i;
			email = email_i;
			description = description_i;
		}

		bool is_resolved(){
			return resolved;
		}

		void resolve_ticket(string resolution){
			response = resolution;
			status = "Closed";
			resolved = true;
		}

		void display_ticket(){
			cout << "Ticket number: " << num << "\nTicket Creator: " << name << "\nStaff ID: " << staff_id << "\nEmail Address: " << email << "\nDescription: " << description << "\nResponse: " << response << "\nTicket Status: " << status << endl;
		}
};

int main(){
	Ticket ticket_list[200];
	int ticket_num = 0;
	int ticket_num_start = 2000;
	string command;
	while(1){
		cout << "What would you like to do (m for help): ";
		cin >> command;
		if(command == "m"){
			cout << "n  create new ticket\nd  display statistics\np  print tickets\nr  respond to ticket\nq  quit" << endl;
			continue;
		}
		if(command == "n"){
			if(ticket_num == sizeof(ticket_list)/sizeof(*ticket_list)){
				cout << "No space to create new ticket";
				continue;
			}
			string staff_id_t;
			string name_t;
			string email_t;
			string description_t;
			cout << "Staff ID: ";
			cin >> staff_id_t;
			cout << "Name: ";
			cin >> name_t;
			cout << "Email: ";
			cin >> email_t;
			cout << "Description: ";
			cin >> description_t;
			if(staff_id_t.length() < 2){
				cout << "Staff ID too short" << endl;
				continue;
			}
			if(name_t.length() < 2){
				cout << "Name too short" << endl;
				continue;
			}
			ticket_list[ticket_num].create(ticket_num+ticket_num_start, name_t, staff_id_t, email_t, description_t);
			ticket_num++;
			continue;
		}
		if(command == "d"){
			int resolved = 0;
			for(int i = 0; i < ticket_num; i++){
				ticket_list[i].display_ticket();
				if(ticket_list[i].is_resolved()){
					resolved++;
				}
			cout << "Tickets Created: " << ticket_num << "\nTickets Resolved: " << resolved << "\nTickets To Solve: " << ticket_num - resolved << endl;
			}
			continue;
		}
		if(command == "p"){
			for(int i = 0; i < ticket_num; i++){
				ticket_list[i].display_ticket();
			}
		}
		if(command == "r"){
			for(int i = 0; i < ticket_num; i++){
				ticket_list[i].display_ticket();
			}
			unsigned int num = 0;
			cout << "Select Ticket by number: ";
			cin >> num;	
			num -= ticket_num_start;
			if(num > ticket_num){
				continue;
			}
			ticket_list[num].display_ticket();
			string resolution;
			cin >> resolution;
			if(resolution.length() < 1){
				continue;
			}
			ticket_list[num].resolve_ticket(resolution);
			continue;
		}
		if(command == "q"){
			cout << "Exiting..." << endl;
			return 0;
		}
	}
	return 0;
}
