version = "1.0.1"
class Ticket: # creating a ticket class to be used in an array of tickets
	num = 0
	name = ""
	staff_id = -1
	email = ""
	description = ""
	response = "Not Yet Provided"
	status = "Open"
	resolved = False

	def __init__(self, num, name, staff_id, email, description): # constructor that is run when the object is created
		self.num = num
		self.name = name
		self.staff_id = staff_id
		self.email = email
		self.description = description
		if(description == "Password change"):
			self.password_change()
			print("Password changed")

	def submit_ticket(self, name, staff_id, email, description): # class method to submit ticket
		self.num = num
		self.name = name
		self.staff_id = staff_id
		self.email = email
		self.description = description

	def resolve_ticket(self, response):
		self.response = response
		self.status = "Closed"
		self.resolved = True

	def is_resolved(self):
		return self.resolved 

	def password_change(self):
		# self.resolve_ticket(self.staff_id[:2] + self.name[:3])
		name = self.name.split()
		password = "".join([self.staff_id[:2], name[0][:3]])
		self.resolve_ticket(password)
		print(password)
		return 

	def display(self):
		print("Ticket number: {}\nTicket Creator: {}\nStaff ID: {}\nEmail Address: {}\nDescription: {}\nResponse: {}\nTicket Status: {}".format(self.num, self.name, self.staff_id, self.email, self.description, self.response, self.status))

def main(): # Main function
	print("Ticketing system version:", version)
	ticket_list = []
	ticket_num = 2000
	while(1):
		command = input("What would you like to do (m for help): ")
		if(command == 'm'):
			print("\nn  create new ticket\nd  display statistics\np  print tickets\nr  respond to ticket\nq  quit\n")
			continue
		if(command == 'n'):
			staff_id = input("\nStaff ID: "	)
			name = input("Name: ")
			email = input("Email: ")
			description = input("Description: ")
			if(len(staff_id) < 2):
				print("Staff ID too short\n")
				continue
			if(len(name) < 3):
				print("Name too short\n")
				continue
			ticket_list.append(Ticket(ticket_num, name, staff_id, email, description))
			print("\n")
			ticket_num += 1
		if(command == 'd'):
			print("\n")
			resolved = 0
			for i in ticket_list:
				if(i.is_resolved()):
					resolved += 1
			print("Tickets Created: {}\nTickets Resolved: {}\nTickets To Solve: {}\n".format(len(ticket_list), resolved, len(ticket_list) - resolved))	
		if(command == 'p'):
			print("\n")
			for i in ticket_list:
				i.display()
				print("\n")
		if(command == 'r'):
			print("\n")
			for i in ticket_list:
				i.display()
				print("\n")
			choice = input("\nWhich ticket would you like to respond to: ")
			for i in ticket_list:
				if(str(i.num) == choice and bool(i.resolved) == False):
					i.display()
					print("\n")
					response = input("\nWhat is your response to this ticket: ")
					if(len(response) < 1):
						break
					i.resolve_ticket(response)
			print("\n")
		if(command == 'q'):
			print("Exiting...")
			quit()



if __name__ == "__main__": # Essentially if the code is being run by itself run main. This is useful for when you want to make a code that can be run by itself or be used in part of another script
	main()
