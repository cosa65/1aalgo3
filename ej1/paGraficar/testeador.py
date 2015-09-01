import sys
import os

def printear(n, ms):
	f = open('myfile.txt', 'a')
	f.write(n)
	f.write(os.linesep)	
	string = ''
	for m in xrange(1,ms+1):
		#M = m+1
		string += str(m) + ' '
	f.write(string)
	f.write(os.linesep)
	f.close()

if __name__ == '__main__':
	printear(sys.argv[1], int(sys.argv[2]))
