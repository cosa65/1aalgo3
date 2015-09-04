import sys
import os
# python casos.py 10 hola.txt

def printear(ms, name):

	f = open(name, 'a+')
	string = ''
	n=0
	for m in range(1,ms+1):
		#M = m+1
		string += str(ms-m) + ' '
	f.write(string)
	f.write(os.linesep)
	f.close()



if __name__ == '__main__':
	printear(int(sys.argv[1]), sys.argv[2])
