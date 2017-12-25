BOOST_ROOT = D:\\boost_1_55_0\\boost_1_55_0

CXXFLAGS =	-O2 -g -Wall -Wl,--allow-multiple-definition -fmessage-length=0 -I$(BOOST_ROOT)

LDFLAGS = -L$(BOOST_ROOT)\\stage\\lib

OBJS =	ThirdSampleApp.o MainClass.o

LIBS =  -static -lboost_system -lboost_filesystem -lboost_thread -lboost_date_time

TARGET =	ThirdSampleApp.exe

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
