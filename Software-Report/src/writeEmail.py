from bs4 import BeautifulSoup
import win32com.client as win32 
import re
import os
import sys


class Soup():

	def __init__(self, filename, report):
		
		with open(filename, "r") as html:
			soup = BeautifulSoup(html, "html.parser")

		html.close()
		self.html = soup
		self.report = report

	def fixUnrecognizedTags(self, tag):
		for tag in self.html.find_all(re.compile(tag)):
			tag = self.html.new_tag(tag)
		
	# user's name and dates
	def fillFields(self, computer, dates):
		self.html.find(id="name").find('span').string = computer.user.split()[0]
		
		html_dates = self.html.find(id="dates").find('span').find_all('span')
		html_dates[0].string = dates[0]
		html_dates[1].string = dates[1]
		html_dates[2].string = dates[2]
		
	def fillContactInfo(self, computer):
		table = self.html.find(id="ContactInfo").find_all("tr")
		row2 = table[1].find_all("td")
		row3 = table[2].find_all("td")
		row4 = table[3].find_all("td")
		row2[1].string = computer.user
		row3[1].string = ""
		row4[1].string = ""
	
	def fillDeviceInfo(self, computer):
		table = self.html.find(id="DeviceInfo").find_all("tr")
		row2 = table[1].find_all("td")
		row3 = table[2].find_all("td")
		row4 = table[3].find_all("td")
		row2[1].string = computer.name
		row3[1].string = computer.model
		row4[1].string = ""
		
	def fillSoftwareRecords(self, computer):
		table = self.html.find(id="SoftwareTable")
		
		for software in computer.software:
			new_row = "<tr style='mso-yfti-irow:1'><td width=407 valign=top style='width:305.6pt;border:solid windowtext 1.0pt;border-top:none;padding:0cm 5.4pt 0cm 5.4pt'><span style='mso-bookmark:_Hlk10446490'></span><p class=MsoNormal style='line-height:105%'><span style='mso-bookmark:_Hlk10446490'><o:p>&nbsp;</o:p></span></p></td><span style='mso-bookmark:_Hlk10446490'></span><td width=228 valign=top style='width:171.0pt;border-top:none;border-left:none;border-bottom:solid windowtext 1.0pt;border-right:solid windowtext 1.0pt;background:#E2EFD9;padding:0cm 5.4pt 0cm 5.4pt'><span style='mso-bookmark:_Hlk10446490'></span><p class=MsoNormal style='line-height:105%'><span style='mso-bookmark:_Hlk10446490'><o:p>&nbsp;</o:p></span></p></td><span style='mso-bookmark:_Hlk10446490'></span></tr>"
			new_row = BeautifulSoup(new_row, "html.parser")
			new_row.find("td").find("p").string = software
			table.append(new_row)

	def __str__(self):
		return str(self.html)


def writeEmail(soup, computer, dates):
	soup.fixUnrecognizedTags("o:p")
	soup.fillFields(computer, dates)
	soup.fillContactInfo(computer)
	soup.fillDeviceInfo(computer)
	soup.fillSoftwareRecords(computer)

	outlook = win32.Dispatch('outlook.application')

	
	user = computer.user.split()
	mail = outlook.CreateItem(0)
	if len(user) == 2:
		mail.To = user[0] + "." + user[1] + "@sobeys.com"
	else:
		print(user)
		return
	mail.Subject = "C20016 - " + computer.name
	mail.HtmlBody = str(soup.html)
	mail.display()


def writeEmails(report, dates):
	for computer in report:
		soup = Soup("EmailTemplate.html", report)
		writeEmail(soup, computer, dates)
