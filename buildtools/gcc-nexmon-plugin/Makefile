all: nexmon.so

ifneq ($(shell uname -m),armv7l)
nexmon.so: nexmon.o
	g++ -m32 -shared -o $@ $<
nexmon.o: nexmon.c
	g++ -std=c++11 -Wall -fno-rtti -Wno-literal-suffix -m32 -fPIC -I../gcc-arm-none-eabi-5_4-2016q2_x86/lib/gcc/arm-none-eabi/5.4.1/plugin/include -c -o $@ $<

else
nexmon.so: nexmon.o
	g++ -shared -o $@ $<
nexmon.o: nexmon.c
	g++ -std=c++11 -Wall -fno-rtti -Wno-literal-suffix -fPIC -I../gcc-arm-none-eabi-5_4-2016q2_arm/lib/gcc/arm-none-eabi/5.4.1/plugin/include/ -c -o $@ $<

endif

clean:
	rm -f *.o *.so
