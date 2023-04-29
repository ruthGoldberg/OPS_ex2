# Operating Systems EX 2
## submitting : beni tibi 208434290 ruth goldberg 322631235
### This EX contains 3 parts , we will explain each one of them.
#### -- Our program written in Clion and we using the compiler GCC --

Part A - in this part we wrote two c programs , the first one calls cmp.c and the second calls copy.c
cmp.c :: takes 2 files and return 0 if the equals or 1 if distinct. one can add the flag -v for printed output according to the int outcome , or the flag -i for ignoring upper and lower cases. you can use both of them too.
to run this source file you need to write in the terminal of the project :
make
./cmp <file1> <file2> (flages) -> flages not an obligation
copy.c :: takes 2 files and copies the first file to the second , returns 0 if succeed , 1 if destination file exists and 2 for other problems. here we have also the flag -v for printed output and -f flag for copy the source to the file either way.
to run this source file you need to write in the terminal of the project :
make
./copy <file1> <file2> (flages) -> flages not an obligation

Part B - in this part we wrote 4 c programs , encode.c , deecode.c , codeA.c and codeB.c.
encode.c :: contains read for the correct codec ( A or B ) which we want to use its encode method.
decode.c :: contains read for the correct codec ( A or B ) which we want to use its decode method.
codeA.c :: contains the implementation for encode and decode for codecA.
codeB.c :: contains the implementation for encode and decode for codecB.
to run this source file you need to write in the terminal of the project :
make
./ <encode/decode> <codecA/codecB> <string>
if you want to insert a string with spaces use " " , for example :"I love ice cream".

Part C - in this part we have only one c program called stshell.c.
It contains the shell options > >> | (2 pipes max) , it ignores ctrl-c , and 'exit' shuts down the shell.
to run this source file you need to write in the terminal of the project :

make

./stshell

now you can run for example:
ls -l | grep txt | wc

./cmp text1.txt text2.txt -v > result.txt

./copy text1.txt text2.txt -v -f >> result.txt

cat makefile

in the zip you can find all the c files we mentioned , h file for partB , makefile and 2 txt files for you to run.
have a nice checking :)

