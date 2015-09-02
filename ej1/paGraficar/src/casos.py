import sys
import os
import random
#n=cantidad de cable
#ms=cantidad de ciudades
def printear(n, ms, name, length):
	random.seed()
	f = open(name, 'w+')
	f.write(n)
	f.write(os.linesep)	
	string = ''
	a="mejor"
	n=0
	for m in xrange(1,ms+1):
		#M = m+1
		string += str(m) + ' '
	f.write(string)
	f.write(os.linesep)
	f.close()



if __name__ == '__main__':
	printear(sys.argv[1], int(sys.argv[2]), sys.argv[3], sys.argv[4])
