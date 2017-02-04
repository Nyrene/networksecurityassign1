import string
import random
import subprocess
import commands
import io
import os
from base64 import b64encode

#random = ''.join([random.choice(string.ascii_letters + string.digits) for n in xrange(8)])
counter = 0
thisCommand = "./a.out --strong testfile"
hashlist = {}


while (counter < 100):
	#steps: generate string
	#thisRandom = ''.join([random.choice(string.ascii_letters + string.digits) for n in xrange(8)])
	thisRandom1 = os.urandom(8)
	thisRandom = b64encode(thisRandom1).decode('utf-8')

	#overwrite to file - it's easier to do this using bash
	#writeCommand = "echo \"test\" > testfile"
	writeCommand = "echo " + "\"" + thisRandom + "\"" + " > testfile" 

	#feed to file(below)
	#process = subprocess.Popen(writeCommand, stdout=subprocess.PIPE, stderr=None, shell=True)
	testOutput = commands.getstatusoutput(writeCommand)
	#thisOutput = process.communicate()

	'''
	changefile = open(file, 'a')
	changefile.write(stuff)
	'''

	#save string and its output to dictionary
	hashlist[thisRandom] = testOutput

	print ("\n")
	print("file input: " + thisRandom)
	print(testOutput)


	#repeat
	counter += 1
	

#cool



#write the dict to a file

#JUST USE BASH TO FILTER OUT DUPLICATES