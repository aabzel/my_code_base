@echo off
rem components\lib\shared_data\shared_data.mk
rem spc58_lanctrl.mk
rem lan.mk
rem https://graphviz.org/doc/info/colors.html
rem components\lib\lan_config_V1\lan_config.mk

echo digraph build_Dependence {> files_tree.dot
echo rankdir=LR;>> files_tree.dot

parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/tja1021/tja1021.mk" files_tree.dot 
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/lin/lin.mk" files_tree.dot green lin_mk
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_lin_lld/spc58_lin_lld.mk" files_tree.dot orange spc58_lin_lld_mk

rem parse_mk.exe "C:\Job\IO_V4\1_FW\controllers_abarunin_io_040\components\drivers\ad5641\ad5641.mk" files_tree.dot blue ad5641_mk
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_spc58/rules.mk" files_tree.dot blue rules_mk
rem parse_mk.exe "C:\Job\IO_V4\1_FW\controllers_abarunin_io_040\components\lib\uio\uio.mk" files_tree.dot mediumorchid1 uio_mk
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/bootloader/bootloader.mk" files_tree.dot blue  bootloader_mk
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils/generate_can_manager.mk" files_tree.dot black  generate_can_manager_mk
 rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils/generate_parameters.mk" files_tree.dot black generate_parameters_mk
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils/join_list.mk" files_tree.dot black join_list_mk
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_spc58/utils.mk" files_tree.dot black utils_mk


rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_spc58/spc58ec/platform.mk" files_tree.dot black spc58ec_platform_mk
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_spc58/spc58xn/platform.mk" files_tree.dot black spc58xn_platform_mk

rem parse_mk.exe "C:\Job\IO_V4\1_FW\controllers_abarunin_io_040\components\boards\IO_V4\cfg\board_cfg.mk" files_tree.dot black IO_V4_board_cfg_mk
rem parse_mk.exe "C:\Job\IO_V4\1_FW\controllers_abarunin_io_040\components\boards\IO_V4\io_v4.mk" files_tree.dot black io_v4_mk
rem parse_mk.exe "C:\Job\IO_V4\1_FW\controllers_abarunin_io_040\components\boards\IO_V4_A\board.mk" files_tree.dot black IO_V4_A_board_mk
rem parse_mk.exe "C:\Job\IO_V4\1_FW\controllers_abarunin_io_040\components\boards\TSTP_V2\board.mk" files_tree.dot red TSTP_V2_board_mk  
rem parse_mk.exe "C:\Job\IO_V4\1_FW\controllers_abarunin_io_040\components\boards\TSTS_V1\board.mk" files_tree.dot cyan TSTS_V1_board_mk
echo }>> files_tree.dot

dot files_tree.dot -Tsvg -o files_tree.svg
"C:\Program Files\Internet Explorer\iexplore.exe" "C:\1_lessons\C_programming_language\trainings\training\build_component_tree\files_tree.svg"
pause
Sleep 1






