@echo off
rem components\lib\shared_data\shared_data.mk
rem spc58_lanctrl.mk
rem lan.mk
rem https://graphviz.org/doc/info/colors.html
rem components\lib\lan_config_V1\lan_config.mk

echo digraph build_Dependence {> files_tree.dot
echo rankdir=LR;>> files_tree.dot

rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils/generate_parameters.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/AEC_V2/AEC_V2_Bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/AEC_V2/AEC_V2_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/DCU_V4/DCU_V4_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/DCU_V4/DCU_V4_bootloader_updater/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/DCU_V4/DCU_V4_WSS_Test/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/DCU_V5/DCU_V5_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/DCU_V5/DCU_V5_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/DCU_V5/DCU_V5_utest_hw/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/EthConverter/EthConverter_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/IoBangN_V1/IoBangN_V1_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/IoBangN_V1/IoBangN_V1_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/IO_V4/IO_V4_A_assembly_test/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/IO_V4/IO_V4_A_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/IO_V4/IO_V4_A_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/IO_V4/IO_V4_A_utest_general/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/IO_V4/IO_V4_A_utest_hw/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/spc58_disp/spc58_disp_utest_general/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTE_V1/TSTE_V1_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTF_V1/TSTF_V1_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTF_V1/TSTF_V1_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTF_V2/TSTF_V2_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTF_V2/TSTF_V2_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTF_V2/TSTF_V2_IO_bang/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTI_V1/TSTI_V1_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTI_V1/TSTI_V1_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTI_V1/TSTI_V1_Generic_lin15/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTI_V1/TSTI_V1_IO_Bang/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTI_V1/TSTI_V1_IO_Bang_Bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTP_V1/TSTP_V1_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTP_V1/TSTP_V1_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTP_V2/TSTP_V2_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTP_V2/TSTP_V2_Generic/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTP_V2/TSTP_V2_IO_Bang/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTS_V1/TSTS_V1_bootloader/Makefile"  files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/TSTS_V1/TSTS_V1_Generic/Makefile"  files_tree.dot 

parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils/generate_can_manager.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils/join_list.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_spc58/rules.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_spc58/spc58ec/platform.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_spc58/spc58xn/platform.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_spc58/utils.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_stm32/rules.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/common/utils_stm32/utils.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/AEC_V2/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/AEC_V2/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/DCU_V4/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/DCU_V4/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/DCU_V5/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/DCU_V5/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/IoBangN_V1/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/IoBangN_V1/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/IoBang_TSTF_V2/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/IoBang_TSTF_V2/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/IoBang_TSTP_V2/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/IoBang_TSTP_V2/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/IO_V4/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/IO_V4/io_v4.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/IO_V4_A/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/spc58ec_disp/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/spc58ec_disp/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTE_V1/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTE_V1/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTF_V1/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTF_V1/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTF_V2/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTF_V2/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTI_V1/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTI_V1/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTP_V1/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTP_V1/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTP_V2/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTP_V2/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTS_V1/board.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/boards/TSTS_V1/cfg/board_cfg.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/ad5641/ad5641.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/ksz8081/ksz8081.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/ksz9031/ksz9031.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/sja1105/sja1105.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/tic12400/tic12400.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/tja1021/tja1021.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/tja110x/tja110x.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/tja1145ex/tja1145ex.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/drivers/tle9255w/tle9255w.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/adc_tests/adc_tests/adc_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/adc_tests/adc_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/backup_app/backup_app.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/bootloader/bootloader.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/bootloader_updater/bootloader_updater.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/bootloader_updater_fw/bootloader_updater_fw.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/bootloader_updater_fw/bootloader_updater_fw_lite.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/canif/canif.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/canif_tests/canif_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/can_gateway/can_gateway.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/can_utils/can_utils.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/can_utils_tests/can_utils_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/components_info/components_info.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/cse_driver/cse_driver.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/cse_driver/cse_ext_driver.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/cse_driver/cse_personalization_support/cse_perso_support.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/dcu_storage/dcu_storage.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/dcu_storage_tests/dcu_storage_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/dev_error_handler/dev_error_handler.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/diagnostics/diagnostics.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/diagnostics_tests/diagnostics_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/diag_page/diag_page.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/flash25/flash25.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/flash25_tests/flash25_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/gtm/gtm.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/gtm_tests/gtm_tests_DCU_V5.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/gtm_tests/gtm_tests_IO_V4.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/health_indicators/adcex/adcex_health_indicators.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/health_indicators/mcan/mcan_health_indicators.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/health_indicators/memu/memu_health_indicators.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/health_monitor/health_monitor.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/lan/lan.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/lan_config_V1/lan_config.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/lin/lin.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/lin_tests/lin_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/module_info/module_info.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/module_power/module_power.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/quencoder/quencoder.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/quencoder_tests/quencoder_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data/shared_data.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_can/shared_data_can.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_can_tests/shared_data_can_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_di/shared_data_di_hw.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_diagnostics/shared_data_diagnostics.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_diagnostics_tests/shared_data_diagnostics_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_di_tests/shared_data_di_hw_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_pm/shared_data_pm_hw.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_pm_tests/shared_data_pm_hw_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_tests/shared_data_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_uio/shared_data_uio_hw.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_uio_tests/shared_data_uio_hw_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_wss/shared_data_wss_hw.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/shared_data_wss_tests/shared_data_wss_hw_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_adcex/spc58_adcex.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_adcex/spc58_adcex_simple.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_crc/spc58_crc.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_crc_tests/spc58_crc_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_dcf/spc58_dcf.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_eth/composite/spc58_lan_composite.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_eth/spc58_lanctrl.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_gpio/spc58_gpio.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_gpio_tests/spc58_gpio_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_hal/spc58_hal.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_lin_lld/spc58_lin_lld.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_mcan/spc58_mcan.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_mcan_tests/spc58_mcan_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_memu/spc58_memu.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_reset_info/spc58_reset_info.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_tests/spc58_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/spc58_xcp_tests/spc58_xcp_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/system_software_base/flash_info/flash_info.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/system_software_base/system_settings/system_settings.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/system_software_base/system_software.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/temp_sensor/temp_sensor.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/tic12400_tests/tic12400_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/tja1145_tests/tja1145_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/tle9255w_tests/tle9255w_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/uio/uio.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/uio_tests/uio_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/unit_test/unit_test.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/unit_test_utils/unit_test_utils.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/wheel_speed_sensor/wheel_speed_sensor.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/wheel_speed_sensor_tests/wss_tests.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/xcp/xcp_master.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/lib/xcp/xcp_slave.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/toolboxes/base_toolbox/base_toolbox.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/toolboxes/diagnostics_toolbox/toolbox/diagnostics_toolbox.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/toolboxes/digital_input_toolbox/digital_input_toolbox.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/toolboxes/io_toolbox/io_toolbox.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/toolboxes/power_management_toolbox/pm_toolbox.mk" files_tree.dot 
parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/components/toolboxes/wheel_speed_sensor_toolbox/wheel_speed_sensor_toolbox.mk" files_tree.dot 
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/EthConverter/EthConverter_Cube/board.mk" files_tree.dot 
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/EthConverter/EthConverter_Generic/rules.mk" files_tree.dot 
rem parse_mk.exe "C:/Job/IO_V4/1_FW/controllers_abarunin_io_040/projects/EthConverter/EthConverter_Generic/utils_stm32l4xx/utils.mk" files_tree.dot 

echo }>> files_tree.dot

dot files_tree.dot -Tsvg -o files_tree.svg
"C:\Program Files\Internet Explorer\iexplore.exe" "C:\1_lessons\C_programming_language\trainings\training\build_component_tree\files_tree.svg"
pause
Sleep 1






