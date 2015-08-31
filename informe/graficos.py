
import matplotlib.pyplot as plt
import numpy as np

#xpuntos=
y=np.arange(0,8.1,.1)
#plt.plot(y,[0]+[np.prod(y[1:i]) for i in range(2,10)],'b-')
plt.plot(y,np.exp(y))

plt.show()
