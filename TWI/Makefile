# ATmega32 at work
MCU = atmega32
# oder MCU = atmega16 
# oder MCU = at90s8535



#Main application file name
MAIN_APP = main
#Main hex file path in windows format
MAIN_HEX_PATH = \$(MAIN_APP).hex

# Compiler and other Section
CC = avr-gcc
OBJCOPY = avr-objcopy.exe
DEBUG=dwarf-2
OPT = s

#Options for avr-gcc
CFLAGS = -g -Os -o

CFLAGS += -mmcu=$(MCU)

#Linking options for avr-gcc
LFLAGS = -Os -mmcu=atmega32 -o

#Options for HEX file generation
HFLAGS = -j .text -j .data -O ihex



# Sources files needed for building the application 
SRC = $(MAIN_APP).c
SRC += 

LDFLAGS += -L. -li2c
DEPS = i2c.h
# The headers files needed for building the application
INCLUDE = -I. 
INCLUDE +=  

# Libraries Flags
	# /Einbinden von Funktionen aus einer Library efsl (Dateiname libefsl.a)


##########------------------------------------------------------##########
##########                 Programmer Defaults                  ##########
##########          Set up once, then forget about it           ##########
##########        (Can override.  See bottom of file.)          ##########
##########------------------------------------------------------##########

#PROGRAMMER_TYPE = usbtiny
# extra arguments to avrdude: baud rate, chip type, -F flag, etc.
#PROGRAMMER_ARGS = 	

##########------------------------------------------------------##########
##########                  Program Locations                   ##########
##########     Won't need to change if they're in your PATH     ##########
##########------------------------------------------------------##########

#CC = avr-gcc
#OBJCOPY = avr-objcopy
# OBJDUMP = avr-objdump
# AVRSIZE = avr-size
# AVRDUDE = avrdude

all : Build clean

Build : $(MAIN_APP).elf
	$(OBJCOPY) $(HFLAGS) $< $(MAIN_APP).hex
	
$(MAIN_APP).elf: $(MAIN_APP).o
	$(CC) $(SRC) $(INCLUDE) $(LFLAGS) $@
	
# $(MAIN_APP).o:$(SRC)
# 	$(CC) $^ $(INCLUDE) $(CFLAGS) $@


clean:
	rm -f *.o *.elf  