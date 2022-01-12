Welcome to Operator Fill

This is a console based MATH program/game made in C++ which in current stage has 700+ lines of code.(I have plans to make it object oriented for easy maintenance and making it shorter)

In this program/game you will be given a linear arithmetic equation out of which the the arithmetic operators will be left to you to fill to satisfy the given equation.  


ABOUT THE PROGRAM

The questions are semi-randomly generated.

Calculation is done based on BODMAS rule but '+' and '-' are give equal priority as the Calculator will convert any subtraction into a negative number and add those numbers.
FOR EXAMPLE: 34 - 21 will be calculated as 34 + (-21) = 13.

For now most numbers will be < 20. Some numbers will be > 20 but always < 100.

There are 4 numerals in an equation with 3 blanks to fill between them and a Fourth optional blank which only accepts ')'.

You will be able to choose Difficulty and and also custom length of equation in Later updates.


INSTRUCTIONS

Write what will go in the place of a blank and to switch to the next blank use a space. An example is given below for better understanding of the answer format.


Example 1 : 1_2_5_6.. = 5

Here the ans will be: + * -

The above ans will turn this eqn into 1+2*5-6 which is equal to 5. (BODMAS RULE)


HOW TO ADD BRACKETS IN YOUR ANSWER

Example 2: 3_6_5_3.. = 6

Here the ans will be: *( - )+

This will turn this eqn into 3*(6-5)+3 which is equal to 6. (Again BODMAS Rule)

Example 3: 20_10_8_4.. = 6

Answer: / +( - )

This will turn this eqn into 20/10+(8-4) which is equal to 6.



As you saw in Example 3 we filled 4 blanks instead of 3 in other examples. This will become clear in the TYPES OF BLANKS category.


TYPES OF BLANKS

1. '_' 

This is the compulsory blank. All of the compulsory blanks must be filled.

This blank accepts either an operator like '+' '-' '*' or '/' OR a bracket with an operator combo like '+(' or ')*' etc.

2. '..'

This is an optional blank present at the end of every question.

You can Fill it or leave it as it is.

If you wish to Fill it, it only accepts ')'.

We filled this blank in Example 3 but we left it alone in all other examples.



COMMANDS

1."SKIP"

If you dont know the answer to a question or wish to skip that question you can write "skip" or "SKIP" or "Skip" (without quotes of course) to skip the current question.

The program will display one of the correct answers for the question.

2."END"

This command will End the game and view your results.

Just type "end" or "End" or "END" (without quotes) to END the game and display how many questions you correctly answered.



NOTE

All Character displayed above with quotes like '+' or '*(' are to be typed without quotes like + or *(.

DOnt omit multiplying operator if trying to multiply thinking that 2 numbers side by side will multiply both numbers.

For Example: 

(4)(4) will not multiply 4 and 4 to give 16. (4)*(4) will though.

3(-5) will not give -15. Valid format is 3*(-5).

PS: For anyone looking at the source codes and scratching their heads wondering what alien language this guy has written I WILL ADD COMMENTS FOR EACH AND EVERY STEP EVENTUALLY.

BTW this is my First code that I'm uploading to github and I started C (my 1st programming language) about 2 months prior to releasing this Program to the public and this is technically my 3rd C++ program (basically me telling I am new to these stuff) and I think you guys would like it.

Also I am aware that this code is not even close to as efficient as it can be so I am open to suggestions. I did this for fun and also severly underestimated the sheer time and complexity of this program.



 


.












