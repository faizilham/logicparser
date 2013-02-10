Truth Table Generator v1.0
==========================
by Faiz Ilham M

This program is a simple logical expression parser; it generates a truth table from a logical expression.

======Package Content======
ltable.exe (the program, console)
ltable.cpp (source code)
parsefile.bat (command code for file I/O)
in.txt (input file for parsefile.bat)
out.txt (output file for parsefile.bat)
readme.txt (yeah, this file)

===========Usage===========
Please open this program from windows command prompt or linux terminal *if* you have recompile it in linux.
Windows user may Shift+Right Click in the programs directory and select "Open command window here" to open the command prompt.
Write "ltable" then enter. Write the logical expression, for example:

p -> q

The program will output:

p  q  p -> q
1  1  1
1  0  0
0  1  1
0  0  1

You can also run the program with the expression as its parameter directly from command prompt, for example:

C:\> ltable "p->q"

The program will yield the same output as above.

You can also set the program to get input / give output to a file, by using windows/linux I/O redirection command,

C:\> ltable < "input_file.txt" > "output_file.txt"

or by running parsefile.bat provided in the program folder.
If you choose to use parsefile.bat, write your input in "in.txt" in the program folder *before* running it. The output will be shown in "out.txt".


==========Syntax==========
Generally the same as logical / mathematical expression syntax.

Operators
These are the valid operators in ltable, sorted from lowest to highest precedence:
- "<->" (biimplication) -- lowest precedence
- "<-" (reduction)
- "->" (implication)
- "|" (or)
- "&" (and)
- "~" (not)
- "(" and ")" (parentheses) -- highest precedence

Variables
ltable currently supports up to 16 variables per expression. You don't need to declare all variables in the expression; ltable will automatically recognize them.
You can name the variable with any name as long as it doesn't contain any operator. so:
"p->q" is a valid expression,
"hello & world -> _nyan" is a valid expression,
"my123 -> var$ -> @TEST" is a valid expression.

Please also note that variables are case-sensitive.

Whitespace
ltable is whitespace free; "p&q", " p &q ", "p & q" will yield the same output.

==========Contact==========
if you find a bug or want to suggest ideas, feel free to contact me at:

(mail) mail@faizilham.com
(facebook) facebook.com/faiz.ilham
(twitter) @fizilicious