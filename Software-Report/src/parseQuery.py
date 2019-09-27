import sys
import os

#Input file must be a csv with 4 columns
#Columms: device name, user name, software name, days since last use

class Computer():

	def __init__(self, name, user, model):
		self.name = name
		self.user = user
		self.model = model
		self.software = []

	def __str__(self):
		return(str(self.name))


def openFile(file_name):

	with open(file_name, 'r', encoding="utf-8") as file:
		first_line = file.readline()
		first_line = first_line[1:-1]# trim leading space and trailing new-line
		
		if first_line != '"Device Name","Full Name","Name","Model"':
			return

		rows = []
		
		for row in file:
			rows.append("".join(row))

	file.close()
	return rows


def processRow(row):

	new_row = ""

	for char in row:
		if char not in ['"', '\n']:
				new_row += char

	new_row = new_row.split(',')

	# merge first name and last name into single element
	# and error correct for software names with commas in them
	if len(new_row) != 4:
		try:
			new_row = [new_row[0], new_row[2]+" "+new_row[1], "".join(new_row[3:-1]), new_row[-1]]
		except:
			print(new_row)

	return new_row


def filterSoftware(software, computer):

	if software.startswith("Windows"):
		return False
		
	if "Office" in software and "(French)" in software:
		return False
		
	with open('contains.csv', 'r') as file:
		for row in file:
			# the row without the newline character
			if row[:-1] in software:
				return False
				
		file.close()

	with open('single.csv', 'r') as file:
		for row in file:
			# the row without the newline character
			if row[:-1] == software:
				return False
				
		file.close()
		
	return software not in computer.software


def processFile(file):

	computers = []
	current_computer = Computer(file[0][0], file[0][1], file[0][-1])
	computers.append(current_computer)

	for i in range(1, len(file)):

		if file[i][0] != current_computer.name:
			current_computer = Computer(file[i][0], file[i][1], file[i][-1])
			computers.append(current_computer)
		elif filterSoftware(file[i][2], current_computer):
			current_computer.software.append(file[i][2])
		

	return computers


def createReport(path):
	file = openFile(path)
	processed_file = []

	for row in file:
		processed_file.append(processRow(row))

	return processFile(processed_file)


def createCSV(report, path):
	outFile = open(path+"/report.csv", 'w')

	# commas tells the writer to start writing in the next cell
	for computer in report:
		outFile.write(computer.name+","+computer.user.replace(',','')+","+computer.model)# write computer name, user name and model in first 3 columns
		outFile.write('\n')
		for software in computer.software:
			outFile.write(",,,"+software)# write software in column 4
			outFile.write('\n')
			
			
if __name__ == "__main__":
	csv = createReport(str(sys.argv[1]))
	createCSV(csv, str(sys.argv[2]))