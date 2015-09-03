# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np

#f=open('clocks208Asm2.txt','r')
#a=[]
#for l in f:
#  a.append(int(l[:-2]))
#f.close()    
#plt.hist(a, bins=25)
#i = 0
#for i in range(len(a)):
#  print a[i]

fig, ax = plt.subplots()
loc = [1,2,3,4,5,6]
loc=np.arange(6)
width=0.35
#C, ASM1, ASM2, ASM1_MejoraenScalar, ASM2_MejoraenScalar, ASM2_mejoraconrgb
medias=[0.000003 , 0.000023 ,0.000943  ,0.001308,  0.001477  , 0.001655 ]
#, ,
std=[0,0,0,0,0,0]
barras=ax.bar(loc,medias,width,yerr=std,error_kw=dict(ecolor='k', lw=2, capsize=5, capthick=2))

dicolor={0:'b',1:'g',2:'r',3:'wheat',4:'darkred',5:'darkgray',6:'chartreuse',7:'olive',8:'teal',9:'aquamarine',10:'orangered',11:'yellow',12:'deeppink'}
for i in loc:
  barras[i].set_color(dicolor[i])
    
#ax.errorbar(loc,medias,yerr=std,linewidth=8)    
    
ax.set_ylabel('Tiempo de ejecucion')
ax.set_xlabel('Tests para ronda de 5 exploradoras')
ax.set_xticks(loc+width*1.2/2)
ax.set_title('Tiempo esperado de ejecucion en casos mejor, promedio y peor')
ax.set_xticklabels(('Mejor caso', 'Mejor caso', 'Random', 'Random', 'Random', 'Peor caso')) 

plt.show()
