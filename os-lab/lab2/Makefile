LIBDIR := libs
OBJDIR := builds
EXEDIR := bin

EXE := $(EXEDIR)/q1
LIBS := $(addprefix $(LIBDIR)/, libscalar.a  libmatrix.so)
SRCS :=$(wildcard src/*.cpp)
OBJS :=$(addprefix $(OBJDIR)/, $(patsubst src/*.cpp, %.o , $(SRCS)))

IN := tests/
OUT := tests/
TEMP_OUT := tests/

MAKE_TEMP_INPUT_FILE   := nice
MAKE_TEMP_INPUT_ARGS   := nice
MAKE_TEMP_OUTPUT_FILE  := nice
 
vpath %.cpp src
vpath %.h include

G := @export LD_LIBRARY_PATH=$(PWD)/$(LIBDIR);
GP := export LD_LIBRARY_PATH=$(PWD)/$(LIBDIR);

all: $(EXE) 
	@echo "Finished successfully"

build : $(EXE) 

lib : $(LIBS)

$(EXE): $(OBJDIR)/q1.o $(LIBS) | $(EXEDIR)
	g++ -o bin/q1 -I include $(OBJDIR)/q1.o -L $(LIBDIR) -lscalar -lmatrix

$(OBJDIR)/matrix.o: matrix.cpp log.h matrix.h scalar.h | $(OBJDIR)
	g++ -fPIC -c -I include $< -o $@

$(OBJDIR)/%.o: %.cpp log.h matrix.h scalar.h | $(OBJDIR)
	g++ -o $@ -c -I include $<

$(LIBDIR)/libscalar.a: $(OBJDIR)/scalar.o | $(LIBDIR)
	ar rcs $@ $^

$(LIBDIR)/libmatrix.so: $(OBJDIR)/matrix.o | $(LIBDIR)
	g++ -shared -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(EXEDIR):
	mkdir -p $(EXEDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(TEMP_OUT):
	mkdir -p $(TEMP_OUT)


test1 : $(EXE) |  $(TEMP_OUT)
	@ $(G) $(EXE) -m < $(IN)sample1.in > $(TEMP_OUT)auto_sample1.out
	@diff $(TEMP_OUT)auto_sample1.out $(OUT)sample1.out && echo "TEST CASE 1:  PASSED!" || echo "TEST CASE 1:  FAILED!"
	

test2 : $(EXE) |  $(TEMP_OUT)
	@ $(G) $(EXE) -m -m< $(IN)sample2.in > $(TEMP_OUT)auto_sample2.out
	@diff $(TEMP_OUT)auto_sample2.out $(OUT)sample2.out && echo "TEST CASE 2:  PASSED!" || echo "TEST CASE 2:  FAILED!"

test3 : $(EXE) |  $(TEMP_OUT)
	@ $(G) $(EXE) -a -a -a -m < $(IN)sample3.in > $(TEMP_OUT)auto_sample3.out
	@diff $(TEMP_OUT)auto_sample3.out $(OUT)sample3.out && echo "TEST CASE 3:  PASSED!" || echo "TEST CASE 3:  FAILED!"

test4 : $(EXE) |  $(TEMP_OUT)
	@ $(G) $(EXE) -t -a -a -a -m -t < $(IN)sample4.in > $(TEMP_OUT)auto_sample4.out
	@diff $(TEMP_OUT)auto_sample4.out $(OUT)sample4.out && echo "TEST CASE 4:  PASSED!" || echo "TEST CASE 4:  FAILED!"

tests: test1 test2 test3 test4 
	@echo "test over"

clean : 
	rm -rf  $(EXEDIR) $(LIBDIR) $(OBJDIR) *.log *.txt


prep : $(OBJDIR)
	$(eval ARGS := $(shell read -p "Enter input file path :| " args; echo $$args ))
	@echo $(ARGS) > $(OBJDIR)/run.in

	$(eval ARGS := $(shell read -p "Enter input options :| " args; echo $$args ))
	@echo $(ARGS) > $(OBJDIR)/run_options.in

	$(eval ARGS := $(shell read -p "Enter output file path :| " args; echo $$args ))
	@echo $(ARGS) > $(OBJDIR)/run.out


run: $(EXE) $(OBJDIR)/run.in $(OBJDIR)/run.out $(OBJDIR)/run_options.in
	$(eval INP1 := $(shell cat $(OBJDIR)/run.in))
	$(eval INP2 := $(shell cat $(OBJDIR)/run_options.in))
	$(eval INP3 := $(shell cat $(OBJDIR)/run.out))

	$(GP) $(EXE) $(INP2)< $(INP1) > $(INP3)
	@echo "run over"

$(OBJDIR)/run.in :
	@echo run.in > $(OBJDIR)/run.in
	
$(OBJDIR)/run.out :
	@echo run.out > $(OBJDIR)/run.out

$(OBJDIR)/run_options.in : 
	@echo '-t' > $(OBJDIR)/run_options.in