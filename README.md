# cellular.c
some experiments before real CA for my new game
clang -fsanitize=address -g -O0 cellular.c -o cellular

./cellular 'size + 2 for edges' 'turn' 'survive value'

nice exemple :
./cellular 42 5 4
