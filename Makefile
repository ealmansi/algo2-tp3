all: compile

LIBAED2 = 								\
	lib/aed2/ConjAcotado.o				\

OBJS = 									\
	src/Acuerdo.o						\
	src/Driver.o 						\
	src/Gremio.o						\
	src/Paritaria.o						\
	src/SistemaLaboral.o				\
	src/Temporada.o						\

TARGET =					 			\
	src/tp3.o 							\

clean:
	@$(RM) -rf $(LIBAED2) $(OBJS) $(TARGET)

%.o: %.cpp
	@g++ -c -o $@ $<

compile: $(LIBAED2) $(OBJS) $(TARGET)
	@g++ -o tp3 $(LIBAED2) $(OBJS) $(TARGET) $(LIBS) -O0 -g -Wall -fmessage-length=0
