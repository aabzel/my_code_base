@echo off
rem components\lib\shared_data\shared_data.mk
rem spc58_lanctrl.mk
rem lan.mk
rem https://graphviz.org/doc/info/colors.html
rem components\lib\lan_config_V1\lan_config.mk

echo digraph build_Dependence {> files_tree.dot
echo rankdir=LR;>> files_tree.dot

rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils/generate_parameters.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/IO_V4/IO_V4_A_bootloader/Makefile" files_tree.dot 
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils/generate_can_manager.mk" files_tree.dot 
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/EthConverter/EthConverter_Cube/board.mk" files_tree.dot 
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/EthConverter/EthConverter_Generic/rules.mk" files_tree.dot 
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/EthConverter/EthConverter_Generic/utils_stm32l4xx/utils.mk" files_tree.dot 

echo }>> files_tree.dot

pause
Sleep 1






