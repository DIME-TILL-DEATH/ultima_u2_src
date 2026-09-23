CXX=arm-kgp-eabi-g++
TARGETFLAGS=
CXXFLAGS=-fno-exceptions

FPV5_D_FLAGS=$(CXXFLAGS) -mfloat-abi=hard  -mcpu=cortex-m7     -mtune=cortex-m7    -mfpu=fpv5-d16    -Ofast
FPV5_S_FLAGS=$(CXXFLAGS) -mfloat-abi=hard  -mcpu=cortex-m7     -mtune=cortex-m7    -mfpu=fpv5-sp-d16 -Ofast
FPV4_S_FLAGS=$(CXXFLAGS) -mfloat-abi=hard  -mcpu=cortex-m4     -mtune=cortex-m4    -mfpu=fpv4-sp-d16 -Ofast
M3_FLAGS=    $(CXXFLAGS) -mfloat-abi=soft  -mcpu=cortex-m3     -mtune=cortex-m3                      -Ofast
M0PLUS_FLAGS=$(CXXFLAGS) -mfloat-abi=soft  -mcpu=cortex-m0plus -mtune=cortex-m0plus                  -Ofast

all:
	$(CXX) $(M0PLUS_FLAGS) -c a.cc -S -o m0plus.s
	$(CXX) $(M0PLUS_FLAGS) -c a.cc -o m0plus.o
	$(CXX) -nostartfiles $(M0PLUS_FLAGS) m0plus.o -o m0plus.out
	$(CXX) $(M3_FLAGS) -c a.cc -S -o m3.s
	$(CXX) $(M3_FLAGS) -c a.cc -o m3.o
	$(CXX) -nostartfiles $(M3_FLAGS) m3.o -o m3.out
	$(CXX) $(FPV4_S_FLAGS) -c a.cc -S -o fpv4-sp-d16.s
	$(CXX) $(FPV4_S_FLAGS) -c a.cc -o fpv4-sp-d16.o
	$(CXX) -nostartfiles $(FPV4_S_FLAGS) fpv4-sp-d16.o -o fpv4-sp-d16.out
	$(CXX) $(FPV5_D_FLAGS) -c a.cc -S -o fpv5-d16.s
	$(CXX) $(FPV5_D_FLAGS) -c a.cc -o fpv5-d16.o
	$(CXX) -nostartfiles $(FPV5_D_FLAGS) fpv5-d16.o -o fpv5-d16.out
	$(CXX) $(FPV5_S_FLAGS) -c a.cc -S -o fpv5-sp-d16.s
	$(CXX) $(FPV5_S_FLAGS) -c a.cc -o fpv5-sp-d16.o
	$(CXX) -nostartfiles $(FPV5_S_FLAGS) fpv5-sp-d16.o -o fpv5-sp-d16.out

clean:
	rm *.s *.o *.out
	

