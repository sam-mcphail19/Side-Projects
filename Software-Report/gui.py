from tkinter import *
from tkinter import filedialog
import writeEmail
import parseQuery
import os


WIDTH = 1200
HEIGHT = 900

class ToggledFrame(Frame):

	def __init__(self, parent, text="", *args, **options):
		Frame.__init__(self, parent, *args, **options)

		self.show = True

		self.title_frame = Frame(self)
		self.title_frame.pack(fill=X, expand=1)

		self.label = Label(self.title_frame, text=text)
		self.label.grid(row=0, column=0, sticky=W)
		
		self.toggle_button = Button(self.title_frame, width=2, text='-', command=self.toggle, padx=3, pady=3)
		self.toggle_button.grid(row=0, column=2, sticky=E)
		self.title_frame.grid_columnconfigure(2, weight=1)

		self.sub_frame = Frame(self)
		self.sub_frame.pack(fill=X)

	def toggle(self):
		if self.show:
			self.sub_frame.forget()
			self.toggle_button.configure(text='+')
		else:
			self.sub_frame.pack(fill=X, expand=1)
			self.toggle_button.configure(text='-')
		
		self.show = not self.show
		
		list.frame.event_generate("<Configure>")
		list.canvas.event_generate("<Configure>")

		
class ScrollableFrame(Frame):

	def __init__(self, parentObject, background):
		Frame.__init__(self, parentObject, background = background, bg="#ffffff")
		self.canvas = Canvas(self, borderwidth=0, background = background, highlightthickness=0)
		self.frame = Frame(self.canvas, background = background, bg="#ffffff")

		self.vert_bar = Scrollbar(self, orient="vertical", command=self.canvas.yview, background=background)
		self.canvas.configure(yscrollcommand=self.vert_bar.set)
		self.vert_bar.grid(row=0, column=1, sticky=N+S)

		self.hori_bar = Scrollbar(self, orient="horizontal", command=self.canvas.xview, background=background)
		self.canvas.configure(xscrollcommand=self.hori_bar.set)
		self.hori_bar.grid(row=1, column=0, sticky=E+W)
		
		self.canvas.grid(row=0, column=0, sticky=N+S+E+W)
		self.window = self.canvas.create_window(0,0, window=self.frame, anchor=NW, tags="self.frame")

		self.grid_columnconfigure(0, weight=1)
		self.grid_rowconfigure(0, weight=1)

		self.frame.bind("<Configure>", self.onFrameConfigure)
		self.canvas.bind("<Configure>", self.onCanvasConfigure)
		
		self.canvas.event_generate("<Configure>")
		self.frame.event_generate("<Configure>")

	def onFrameConfigure(self, event):
		x1, y1, x2, y2 = self.canvas.bbox("all")
		height = self.canvas.winfo_height()
		width = self.canvas.winfo_width()
		self.canvas.config(scrollregion = (0,0, max(x2, width), max(y2, height)))


	def onCanvasConfigure(self, event):
		minWidth = self.frame.winfo_reqwidth()
		
		if self.winfo_width() >= minWidth:
			newWidth = self.winfo_width()
		else:
			newWidth = minWidth
			self.hori_bar.grid()
		
		self.canvas.itemconfig(self.window, width=newWidth-18)

		
class CopyAllButton(Frame):

	def __init__(self, parent, text="", *args, **options):
		Frame.__init__(self, parent, *args, **options)
		
		self.button = Button(self, text=text, command=self.copy)
		self.button.pack()
		
	def copy(self):
		window.clipboard_clear()
		
		for child in self.master.master.sub_frame.winfo_children():
			for sub_child in child.winfo_children():
				if type(sub_child) == Text:
					window.clipboard_append(sub_child.get("1.0",END))
					
					
class ToggleAllButton(Frame):

	def __init__(self, parent, *args, **options):
		Frame.__init__(self, parent, *args, **options)
		
		self.button = Button(self, text="Collapse All", command=self.toggle)
		self.button.pack()
		
		self.collapse = True
		
	def toggle(self):
		
		try:
			frames = list.winfo_children()[0].winfo_children()[0].winfo_children()
		except:
			return
		
		for frame in frames:
			if type(frame) == ToggledFrame:
				if (self.collapse and frame.show) or (not self.collapse and not frame.show):
					frame.toggle()
					
		if self.collapse:
			self.button.config(text="Expand All")
		else:
			self.button.config(text="Collapse All")
			
		self.collapse = not self.collapse
		
		list.canvas.event_generate("<Configure>")
		list.frame.event_generate("<Configure>")


def center(window):
	screen_width = window.winfo_screenwidth()
	screen_height = window.winfo_screenheight()
	
	x = screen_width/2 - WIDTH/2
	y = screen_height/2 - HEIGHT/2
	
	window.geometry('%dx%d+%d+%d' % (WIDTH, HEIGHT, x, y))


def getFile():
	selected = filedialog.askopenfilename(filetypes = (("CSV files", "*.csv"), ("All files", "*")))
	if selected:
		filepathval.set(selected)
		

def getExportPath():
	selected = filedialog.askdirectory()
	if selected:
		export_path.set(selected)
		
		
def exportCSV():
	report = parseQuery.createReport(str(filepathval.get()))
	parseQuery.createCSV(report, str(export_path.get()))
	#OPEN THE CSV
	

def filepath_Callback(event):
	filepath.selection_range(0, END)
	
	
def onMousewheel(event):
	list.canvas.yview_scroll(int(-1*(event.delta/120)), "units")
	
	
def emptyList():
	if list.frame.winfo_children() != []:
		for child in list.frame.winfo_children():
			child.destroy()
			
def removeLabels():
	if invalid:
		invalid.grid_forget()
		
	if created:
		created.grid_forget()


def writeMail():
	invalid = None
	
	path = str(filepathval.get())
	
	if not os.path.exists(path):
		removeLabels()
		invalid = Label(fileselect, text="Invalid File Path", fg="#ff0000", bg="#ffffff")
		invalid.grid(column=0, row=5)
		emptyList()
		return
		
	report = parseQuery.createReport(path)
	dates = [start_date_val.get(), end_date_val.get(), response_date_val.get()]
	
	writeEmail.writeEmails(report, dates)
	
	removeLabels()

def createReport():
	global invalid
	global created

	path = str(filepathval.get())
	
	if not os.path.exists(path) or path[-4:] != ".csv":
		removeLabels()
		invalid = Label(fileselect, text="Invalid File Path", fg="#ff0000", bg="#ffffff")
		invalid.grid(column=0, row=5)
		emptyList()
		return
		
	if parseQuery.openFile(path) is None:
		removeLabels()
		invalid = Label(fileselect, text="Invalid CSV Format", fg="#ff0000", bg="#ffffff")
		invalid.grid(column=0, row=5)
		emptyList()
		return
		
	report = parseQuery.createReport(path)
	
	removeLabels()
		
	created = Label(fileselect, text="Report Created Successfully", bg="#ffffff")
	created.grid(column=0, row=5)
	
	emptyList()

	i = 1
	
	for computer in report:
	
		current_computer = ToggledFrame(list.frame, text=computer.name + " - " + computer.user, relief="flat")
		current_computer.grid(row=i, column=0, sticky=W+E)
		
		CopyAllButton(current_computer.title_frame, text="Copy All").grid(row=0, column=1, sticky=E, padx=5, pady=3)
		
		if i%2 == 1:
			current_computer.title_frame.configure(bg="#bbbbff")
			current_computer.label.configure(bg="#bbbbff")
		else:
			current_computer.title_frame.configure(bg="#ddddff")
			current_computer.label.configure(bg="#ddddff")
		
		list.frame.grid_columnconfigure(0, weight=1)
		
		j = 0
		
		for software in computer.software:
			
			newsoftware = Frame(current_computer.sub_frame)
			newsoftware.grid(row=j, column=0, sticky=W+E)
			current_computer.sub_frame.grid_columnconfigure(0, weight=1)
			
			text = Text(newsoftware, height=1, font=("helvetica", 10), relief="flat")
			text.insert(1.0, software)
			text.grid(row=j, column=0, sticky=W, padx=(50,10))
			text.configure(state="disabled")
			#Label(newsoftware, text="").grid(row=j, column=1, sticky=E)
			
			newsoftware.grid_columnconfigure(1, weight=1)
				
			color = ("#BABABA", "#EFEFEF")[j%2 == 0]
				
			newsoftware.configure(bg=color)
			for child in newsoftware.winfo_children():
				child.configure(bg=color)
			
			j+=1
	
		i += 1
		
	list.frame.event_generate("<Configure>")
	list.canvas.event_generate("<Configure>")
	
	num_devices = "Total devices: " + str(len(report))
	Label(fileselect,text=num_devices, bg="#FFFFFF").grid(row=0, column=0, sticky=N)
	fileselect.grid_rowconfigure(0, weight=1)
	
	
def main():
	global window
	window = Tk()
	window.title("Software Report Tool")
	window.configure(bg="#FFFFFF")
	center(window)
	
	global invalid
	invalid = None
	global created
	created = None

	global top
	top = Frame(window, background="#FFFFFF")
	top.grid(column=0, row=0, sticky=N+E+W)

	global fileselect
	fileselect = Frame(top, background="#FFFFFF")
	fileselect.grid(row=0, column=0, sticky=N+E+S)

	global fileenter
	fileenter = Frame(fileselect, background="#FFFFFF")
	fileenter.grid(column=0, row=1, padx=10, pady=(10,75))

	global filepathval
	filepathval = StringVar()
	filepathval.set("Enter File Path to CSV")

	global filepath
	filepath = Entry(fileenter, textvariable=filepathval)
	filepath.grid(column=0, row=1, pady=5)
	filepath.bind("<FocusIn>", filepath_Callback)

	global browse
	browse = Button(fileenter, text="Browse Files", command=getFile)
	browse.grid(column=0, row=2)

	global enter
	enter = Button(fileselect, text="Generate Report", command=createReport)
	enter.grid(column=0, row=2)

	global num_devices
	num_devices = StringVar()
	num_devices.set("")

	global emails
	emails = Frame(top, background="#FFFFFF")
	emails.grid(row=0, column=1, pady=(50,0), sticky=E+W+N)

	top.grid_columnconfigure(1, weight=1)
	
	global dates
	dates = Frame(emails, bg="#FFFFFF")
	dates.grid(column=0, row=0, padx=(50,0), sticky=W)
	
	global start_date
	global end_date
	global response_date
	
	global start_date_val
	global end_date_val
	global response_date_val
	
	start_date_val = StringVar()
	start_date_val.set("ENTER START DATE")
	start_date = Entry(dates, text=start_date_val, bg="#FFFFFF")
	start_date.grid(column=1, row=0, padx=5, pady=5)
	
	end_date_val = StringVar()
	end_date_val.set("ENTER END DATE")
	end_date = Entry(dates, text=end_date_val, bg="#FFFFFF")
	end_date.grid(column=1, row=1, padx=5, pady=5)
	
	response_date_val = StringVar()
	response_date_val.set("ENTER REPONSE DATE")
	response_date = Entry(dates, text=response_date_val, bg="#FFFFFF")
	response_date.grid(column=1, row=2, padx=5, pady=5)

	global write_emails
	write_emails = Button(emails, text="Write Emails", command=writeMail)
	write_emails.grid(column=1, row=0, pady=10, sticky=W)

	#to center everything in the emails section
	emails.grid_columnconfigure(1, weight=1)
	
	toggle_all = ToggleAllButton(top)
	toggle_all.grid(row=1, column=2, sticky=S+E, padx=19, pady=5)
	
	export = Frame(top, bg="#FFFFFF")
	export.grid(row=1, column=1, sticky=S+E, pady=5)
	
	global export_path
	export_path = StringVar()
	
	export_csv_button = Button(export, text="Export Report to CSV", command=exportCSV)
	export_csv_button.grid(row=0, column=0, padx=15)
	export_csv = Entry(export, textvariable=export_path)
	export_csv.grid(row=0, column=1)
	export_csv_browse = Button(export, text="Browse Files", command=getExportPath)
	export_csv_browse.grid(row=0, column=2)

	global list
	list = ScrollableFrame(window, background="#FFFFFF")
	list.grid(column=0, row=1, sticky=N+S+E+W)

	window.grid_columnconfigure(0, weight=1)
	window.grid_rowconfigure(1, weight=1)
	
	list.canvas.bind_all("<MouseWheel>", onMousewheel)

	window.mainloop()
	
if __name__ == "__main__":
	main()