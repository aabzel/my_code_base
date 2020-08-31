rem components/lib/shared_data/shared_data.mk
rem spc58_lanctrl.mk
rem lan.mk

rem components/lib/lan_config_V1/lan_config.mk

echo digraph build_Dependence {> files_tree.dot
echo rankdir=LR;>> files_tree.dot
parse_mk.exe "C:\Job\IO_V4\1_FW\controllers_abarunin_io_040\components\boards\TSTP_V2\board.mk" files_tree.dot red TSTP_V2_board_mk  
parse_mk.exe "C:\Job\IO_V4\1_FW\controllers_abarunin_io_040\components\boards\TSTS_V1\board.mk" files_tree.dot cyan TSTS_V1_board_mk
echo }>> files_tree.dot

dot files_tree.dot -Tsvg -o files_tree.svg
"C:\Program Files\Internet Explorer\iexplore.exe" "C:\1_lessons\C_programming_language\trainings\training\build_component_tree\files_tree.svg"
Sleep 1






