@echo off
set INCDIR=
rem set INCDIR=%INCDIR%  -IC:\1_lessons\C_programming_language\trainings\training\STM32Cube_FW_F1_V1.8.3\Drivers\STM32F1xx_HAL_Driver\Inc
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\STM32Cube_FW_F1_V1.8.3\Drivers\CMSIS\Device\ST\STM32F1xx\Include
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\stm32_vl_discovery\bsp

rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\stm32_vl_discovery
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\utils_stm32
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\utils
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\components\lib\diag_page
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\components\lib\sd_card
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\components\lib\stm32_gpio\src
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\components\lib\stm32_spi
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\components\lib\stm32_tim\src
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\components\lib\unit_test\src
rem set INCDIR=%INCDIR% -IC:\1_lessons\C_programming_language\trainings\training\com_utils

set C_SRC=*.c
rem set C_SRC=%C_SRC% C:/1_lessons/C_programming_language/trainings/training/components/lib/sd_card/sd_card_commands.c
rem set OPT=-weak 
set OPT=%OPT% -strict
rem set OPT=%OPT%    -weak 
set OPT=%OPT% +never-include 
set OPT=%OPT% +gnuextensions
set OPT=%OPT% +posixlib
set OPT=%OPT% -unrecog
set OPT=%OPT% +trytorecover
rem set OPT=%OPT% +export-header  
set OPT=%OPT% -preproc
rem set OPT=%OPT% +skip-iso-headers  
rem set OPT=%OPT% +skip-ansi-headers



rem set INCDIR=-IC:\1_lessons\C_programming_language\trainings\training\STM32Cube_FW_F1_V1.8.3\Drivers\STM32F1xx_HAL_Driver\Inc
rem INCDIR +=-IC:\1_lessons\C_programming_language\trainings\training\stm32_vl_discovery\bsp
splint %OPT% %INCDIR%   %C_SRC%
Sleep 60
