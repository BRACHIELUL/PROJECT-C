 CC = gcc
 CFLAGS = -ansi -Wall -pedantic -g
 EXE_DEPS = open_macro.o first_pass.o macro_list.o label_list.o print_files.o externs_to_print_list.o second_pass.o labels_in_code.o  data_list.o errors.o entry_list.o extern_list.o word_list.o  main.o general_funcs.o instruction_code.o
 VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
 PROG = assembler
 ARG1 = first_argument
 ARG2 = second_argument
 ARG3 = third_argument
 ARG4 = forth_argument
 ARG5 = fifh_argument
 ARG6 = sixth_argument

 ## Executable
assembler: $(EXE_DEPS)
	$(CC) -g $(EXE_DEPS) $(CFLAGS) -o $@

main.o:
	$(CC) -c main.c $(CFLAGS) -o $@

open_macro.o:
	$(CC) -c open_macro.c $(CFLAGS) -o $@

first_pass.o:
	$(CC) -c first_pass.c $(CFLAGS) -o $@

macro_list.o:
	$(CC) -c macro_list.c $(CFLAGS) -o $@

label_list.o:
	$(CC) -c label_list.c $(CFLAGS) -o $@

word_list.o:
	$(CC) -c word_list.c $(CFLAGS) -o $@

data_list.o:
	$(CC) -c data_list.c $(CFLAGS) -o $@

entry_list.o:
	$(CC) -c entry_list.c $(CFLAGS) -o $@

extern_list.o:
	$(CC) -c extern_list.c $(CFLAGS) -o $@

instruction_code.o:
	$(CC) -c instruction_code.c $(CFLAGS) -o $@

general_funcs.o:
	$(CC) -c general_funcs.c $(CFLAGS) -o $@

errors.o:
	$(CC) -c errors.c $(CFLAGS) -o $@

labels_in_code.o:
	$(CC) -c labels_in_code.c $(CFLAGS) -o $@

second_pass.o:
	$(CC) -c second_pass.c $(CFLAGS) -o $@

print_files.o:
	$(CC) -c print_files.c $(CFLAGS) -o $@

externs_to_print_list.o:
	$(CC) -c externs_to_print_list.c $(CFLAGS) -o $@


clean:
	rm -rf *.o *.am *.ob *.ent *.ext

val:
	valgrind $(VALGRIND_FLAGS) ./$(PROG) $(ARG1) $(ARG2) &(ARG3) &(ARG4) &(ARG5) &(ARG6)