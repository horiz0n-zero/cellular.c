C_SRC = $(shell find . -type f | grep "\.c")
PRINT = printf 'compiling %s -> \33[38;2;0;255;0m%s\33[37m\n' $(SRC) $(basename $(SRC))
REMOVE = printf 'removing \33[38;2;255;0;0m%s\33[37m\n' $(basename $(SRC))
all:
	@$(foreach SRC, $(C_SRC), clang $(SRC) -o $(basename $(SRC)); $(PRINT);)

clean:
	@$(foreach SRC, $(C_SRC), rm $(basename $(SRC)); $(REMOVE);)

re: clean all
