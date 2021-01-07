@echo off
set style1="{IndentWidth: 4, SortIncludes: true, SortUsingDeclarations: true , SpaceBeforeParens: Always,UseTab: Never,PointerAlignment: Right, BreakBeforeBraces: Attach, TabWidth: 4,ColumnLimit: 120 }"
set format_tool="C:\Program Files\LLVM\bin\clang-format.exe"


%format_tool%  -verbose -i -style=%style1% C:\1_lessons\C_programming_language\trainings\training\*.h
%format_tool%  -verbose -i -style=%style1% C:\1_lessons\C_programming_language\trainings\training\*.c
%format_tool%  -verbose -i -style=%style1% C:\1_lessons\C_programming_language\trainings\training\*.cpp

