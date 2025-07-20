SRCS=main.cc inky.cc
OBJS=$(addprefix obj/,$(addsuffix .o,$(basename $(SRCS))))

# add -I includerfolder1 -I includefolder2...
CFLAGS+=-I include -I /usr/include/nlohmann

vpath %.cc src

obj/%.o:%.cc
	$(CXX) -c -o $@ $(CXXFLAGS) $(CFLAGS) $^

.PHONY: all
all: jsontest tcp-client

# change the program name before the colon
# add a -l libraryname -l libraryname2 below
jsontest:$(OBJS)
	g++ -o $@ $(OBJS)

TCP_CLIENT_SRCS=tcp-client.cc ip4_address.cc tcp4_socket.cc
TCP_CLIENT_OBJS=$(addprefix obj/,$(addsuffix .o,$(basename $(TCP_CLIENT_SRCS))))
tcp-client : $(TCP_CLIENT_OBJS)
	g++ -o $@ $(TCP_CLIENT_OBJS)

#change the prgram name below
.PHONY: clean
clean:
	rm -f jsontest tcp_client obj/*
