CODE_BASE =		C:/Users/dinkem1/Codebase/TicRingProject/
SRC_CODE_PATH = $(CODE_BASE)TicRingEmbedded/
TEST_CODE_PATH = $(CODE_BASE)TicRingTests/

CXXPATH =
INCLUDE_PATH =	-I$(TEST_CODE_PATH)incl \
                -I$(TEST_CODE_PATH)incl/CppUTest \
                -I$(TEST_CODE_PATH)incl/CppUTestExt \
                -I$(TEST_CODE_PATH)mockIncludes \
                -I$(SRC_CODE_PATH)incl \
				 

CC_COMPILER	= -O2 -Wall -fmessage-length=0
CC_INCLUDE	= $(INCLUDE_PATH) 

CXXFLAGS = 	$(CC_COMPILER) $(CC_INCLUDE)

OBJS =		src/runAllTests.o \
			src/rotatorTest.o \
			src/controlProcessTest.o \
			src/mocks/mockWiringFunctions.o \
			$(SRC_CODE_PATH)src/controlProcess.o \
			$(SRC_CODE_PATH)src/rotator.o \
             

LIBS = $(TEST_CODE_PATH)lib/CppUTest/libCppUTest.a \
       $(TEST_CODE_PATH)lib/CppUTest/libCppUTestExt.a


AUTO_IMPORT = -Xlinker --enable-auto-import

TARGET =		./bin/runAllTests.exe


$(TARGET):	$(OBJS)
	$(CXX)  $(AUTO_IMPORT) -o $(TARGET) $(OBJS)  $(LIBS) $(INCLUDE_PATH)

all:	$(TARGET)	

debug:	CXX += -DDEBUG -g
debug:	$(TARGET)	

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(OBJS) $(DEBUGTARGET)

