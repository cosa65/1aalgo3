import numpy as np
import matplotlib.pyplot as plt


# y[0..1] = mejoresCasos e=3
# y[2..4] = CasosPromedios e=3
# y[4..5] = CasoPeor e=3

#x = [3, 3, 3, 3, 3, 3]
x = [3, 3, 3, 3, 3, 3]
#y = [0.000002, 0.000007, 0.000028, 0.000029, 0.000029, 0.000049]
y = [0.00106, 0.000780, 0.032470, 0.03200, 0.031870, 0.046200 ]
#[0.66029 ,0.71213,0.75875,1.370972 ]  


colors = [1,2,3,4,5,6]

area = 34

plt.scatter(x , y , s=area , c=colors , alpha=0.5)
plt.show()
