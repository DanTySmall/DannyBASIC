# DannyBASIC 
A modern implementation of TinyBASIC

## Table of Contents

1.  [Supported Keywords](#orgf62fcd8)
2.  [Installation Instructions For End Users](#org6cf7fc0)
3.  [Installation Instructions For Contributors](#orge58055f)


This project takes a basic file that contains the supported keywords, generate intermediate code then, run the commands


<a id="orgf62fcd8"></a>

## Supported Keywords

GOTO<br/>
GOSUB<br/>
IF<br/>
INPUT<br/>
LET<br/>
LIST<br/>
PRINT<br/>
RETURN<br/>
RUN<br/>
THEN<br/>


<a id="org6cf7fc0"></a>

## Installation Instructions For End Users

1.  Clone the Repo<br/>
    git clone <https://github.com/DanTySmall/DannyBASIC.git>
2.  Use make commands to compile source code<br/>
    make all
3.  Run Executable with program file<br/>
    ./dannybasic \<Program File>


<a id="orge58055f"></a>

## Installation Instructions For Contributors

Main Files:<br/>
        Parse.cpp + .hpp - Generates Tokens<br/>
        Syntax.cpp + .hpp - Generates Intermediate Code<br/>
        Execute.cpp + .hpp - Runs Intermediate Code<br/>

These Files can be edited and compiled with make command
make all

