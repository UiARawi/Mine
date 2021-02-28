# 
# Synthesis run script generated by Vivado
# 

set TIME_start [clock seconds] 
proc create_report { reportName command } {
  set status "."
  append status $reportName ".fail"
  if { [file exists $status] } {
    eval file delete [glob $status]
  }
  send_msg_id runtcl-4 info "Executing : $command"
  set retval [eval catch { $command } msg]
  if { $retval != 0 } {
    set fp [open $status w]
    close $fp
    send_msg_id runtcl-5 warning "$msg"
  }
}
set_param xicom.use_bs_reader 1
create_project -in_memory -part xc7a100tcsg324-1

set_param project.singleFileAddWarning.threshold 0
set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_property webtalk.parent_dir C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.cache/wt [current_project]
set_property parent.project_path C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language VHDL [current_project]
set_property ip_output_repo c:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.cache/ip [current_project]
set_property ip_cache_permissions {read write} [current_project]
read_vhdl -library xil_defaultlib {
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/12_bit_register.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/4bittil7segment.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/8_bit_register.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/BCD_binary_to_decimal.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/Clk_divider_100_MHz.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/Clock_divider.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/Components_display.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/Counter_display.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/imports/Final_project.srcs/Decimal_point_reg_2.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/imports/Final_project.srcs/Decimal_point_reg_4.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/Decoder_3_to_8.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/FSM_1.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/FSM_Ram.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/Final_components.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/MUX_4.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/MUX_display_RAM.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/MUX_xyzt_reg.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/Main_file_adxl.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/SPI_if.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/components.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/Top_file_del_1_prosjekt.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/pluss_minus.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/register_shown.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/toers_komp_inv.vhd
  C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/sources_1/new/Final_prosjekt_top_file.vhd
}
# Mark all dcp files as not used in implementation to prevent them from being
# stitched into the results of this synthesis run. Any black boxes in the
# design are intentionally left as such for best results. Dcp files will be
# stitched into the design at a later time, either when this synthesis run is
# opened, or when it is stitched into a dependent implementation run.
foreach dcp [get_files -quiet -all -filter file_type=="Design\ Checkpoint"] {
  set_property used_in_implementation false $dcp
}
read_xdc C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/constrs_1/imports/Final_project/Nexys4DDR_Master.xdc
set_property used_in_implementation false [get_files C:/Users/Rawi/Documents/UiA/Vr_19/ELE_112/Lab/prosjekt/Final_project.srcs/constrs_1/imports/Final_project/Nexys4DDR_Master.xdc]

set_param ips.enableIPCacheLiteLoad 1
close [open __synthesis_is_running__ w]

synth_design -top Final_prosjekt_top_file -part xc7a100tcsg324-1


# disable binary constraint mode for synth run checkpoints
set_param constraints.enableBinaryConstraints false
write_checkpoint -force -noxdef Final_prosjekt_top_file.dcp
create_report "synth_1_synth_report_utilization_0" "report_utilization -file Final_prosjekt_top_file_utilization_synth.rpt -pb Final_prosjekt_top_file_utilization_synth.pb"
file delete __synthesis_is_running__
close [open __synthesis_is_complete__ w]
