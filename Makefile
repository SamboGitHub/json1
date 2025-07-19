SRCS=$(notdir $(wildcard src/*))
OBJS=$(addprefix obj/,$(addsuffix .o,$(basename $(SRCS))))

# add -I includerfolder1 -I includefolder2...
CFLAGS+=-I include -I /usr/include/nlohmann

vpath %.cc src

obj/%.o:%.cc
	$(CXX) -c -o $@ $(CXXFLAGS) $(CFLAGS) $^

# change the program name before the colon
# add a -l libraryname -l libraryname2 below
jsontest:$(OBJS)
	g++ -o $@ $(OBJS)

tcp-client : tcp-client.o
	g++ -o $@ tcp-client.o

#change the prgram name below
clean:
	rm -f jsontest obj/*
