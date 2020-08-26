iklib.so: IKWrapperPy.cpp ikfast_solver.cpp
	g++ -fpic -c -lstdc++ -llapack -I/usr/include/python2.7 -I/usr/lib/python2.7/config-arm-linux-gnueabihf IKWrapperPy.cpp ikfast_solver.cpp
	g++ -shared  IKWrapperPy.o ikfast_solver.o -o ikfast.so

clean:
	@rm IKWrapperPy.o ikfast_solver.o ikfast.so
