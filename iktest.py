import numpy as np
import ikfast
 
a = np.zeros(6)
b = np.zeros(6)
fk = np.array([0,0,0,0,0,0],float)
ik = np.array([0.4,0.4,0.3,30,30,30],float)

# fk: j1~j6 (degree)
print 'fk'
a = ikfast.fk(fk[0],fk[1],fk[2],fk[3],fk[4],fk[5])
print a

# ik: x,y,z,rx,ry,rz,n (meter,degree)
print 'ik'
i = 0
while b[0] >= 0:
	b = ikfast.ik(ik[0],ik[1],ik[2],ik[3],ik[4],ik[5],i)
	if b[0]>=0 :
		print b
	i=i+1

