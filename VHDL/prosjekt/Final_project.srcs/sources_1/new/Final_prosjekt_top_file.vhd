
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.Final_components.all;
use IEEE.STD_LOGIC_ARITH.ALL;
use ieee.numeric_std.all;
use IEEE.std_logic_unsigned.all;

entity Final_prosjekt_top_file is
  Port (
  
  Reset_final:in std_logic;
  Clk_Final: in std_logic;
  SW_Final: in std_logic_vector(5 downto 0);
  Decoder_Final: out std_logic_vector(7 downto 0);
  Mux_Final: out std_logic_vector(7 downto 0);
  MISO_Final: in std_logic;
  MOSI_Final: out std_logic;
  SS_Final: inout std_logic;
  SCLK_Final: inout std_logic
  );
end Final_prosjekt_top_file;

architecture Behavioral of Final_prosjekt_top_file is


constant  SYSCLK_FREQUENCY_HZ_fn    : integer := 108000000;
constant  SCLK_FREQUENCY_HZ_fn      : integer := 1000000;
constant  NUM_READS_AVG_fn          : integer := 16;
constant  UPDATE_FREQUENCY_HZ_fn    : integer := 1000;
signal    Data_Ready_fn             : std_logic;


signal x_reg_fra_spare_final: std_logic_vector(11 downto 0);
signal y_reg_fra_spare_final: std_logic_vector(11 downto 0);
signal z_reg_fra_spare_final: std_logic_vector(11 downto 0);
signal t_reg_fra_spare_final: std_logic_vector(11 downto 0);



begin

Del_1: Top_file_del_1_prosjekt 
Port map ( 
sw=>SW_Final,
decodr_out=> Decoder_Final,
mux_out=> mux_Final,
x_reg_fra_spare=>x_reg_fra_spare_final,
y_reg_fra_spare=>y_reg_fra_spare_final,
z_reg_fra_spare=>z_reg_fra_spare_final,
t_reg_fra_spare=>t_reg_fra_spare_final,
Clk=>Clk_Final );


ADXL_362_ctrl: ADXL362Ctrl 
generic map
(
   SYSCLK_FREQUENCY_HZ=>SYSCLK_FREQUENCY_HZ_fn,
   SCLK_FREQUENCY_HZ=>SCLK_FREQUENCY_HZ_fn,
   NUM_READS_AVG=>NUM_READS_AVG_fn,
   UPDATE_FREQUENCY_HZ=>UPDATE_FREQUENCY_HZ_fn
)
port map
(
   SYSCLK=>CLk_final,-- System Clock
   RESET=>reset_final,

   -- Accelerometer data signals
   ACCEL_X=>x_reg_fra_spare_final,
   ACCEL_Y=>y_reg_fra_spare_final,
   ACCEL_Z=>z_reg_fra_spare_final,
   ACCEL_TMP=>t_reg_fra_spare_final,
   Data_Ready=>Data_Ready_fn,

   --SPI Interface Signals
   SCLK=>SCLK_final,
   MOSI=>MOSI_final,
   MISO=>MISO_final,
   SS=>SS_final
);



           

end Behavioral;
