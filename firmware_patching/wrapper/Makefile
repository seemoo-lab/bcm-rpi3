CC=../../buildtools/arm-eabi-4.7/bin/arm-eabi-

all: wrapper.o

wrapper.ld: ../include/wrapper.h Makefile
	# read the wrapper.h file and remove the weak attribute, extract all lines starting with "extern", split them at "(" and "/" and then remove the "*" of a return type, then the function name is the second but last word and the address is the last word
	sed -e "s/__attribute__((weak))//" ../include/wrapper.h | gawk -F'[/(]' '/^extern/ {gsub(/*/,"",$$1);print $$1 $$4}' | gawk -F' ' '{print ".text." $$(NF-1) " " $$NF " : { $(NEXMON_FIRMWARE_PATCHING)/wrapper/wrapper.o (.text." $$(NF-1) ") }"}' > wrapper.ld

wrapper.c: ../include/wrapper.h
	# read the wrapper.h file and remove comments but no #include, remove the weak attribute, remove all extern words at the beginning of a line. if the return value is not void, then insert dummy code that returns 0 otherwise do nothing in the function
	sed -e "/#include/! {/#/d}" -e "s/__attribute__((weak))//" -e "/^extern void \*/ s/;/ { return 0; }/ ; /^extern void /! s/;/ { return 0; }/ ; s/);/) { ; }/" -e "s/^extern //" ../include/wrapper.h > wrapper.c

wrapper.o: wrapper.c wrapper.ld
	$(CC)gcc -Wall -Werror -O2 -nostdlib -nostartfiles -ffreestanding -mthumb -ffunction-sections -fdata-sections -c wrapper.c -o wrapper.o
	# Change byte alignment to 2 byte:
	python2 ../../buildtools/elffile/adjalign.py wrapper.o wrapper.o

clean: 
	rm -f wrapper.o wrapper.c wrapper.ld
