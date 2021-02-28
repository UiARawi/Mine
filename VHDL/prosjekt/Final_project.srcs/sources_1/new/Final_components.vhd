library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


package Final_components is

component Top_file_del_1_prosjekt is
Port ( 
sw: in std_logic_vector(5 downto 0);
decodr_out: out std_logic_vector(7 downto 0);
mux_out:out std_logic_vector(7 downto 0);
x_reg_fra_spare: in std_logic_vector(11 downto 0);
y_reg_fra_spare: in std_logic_vector(11 downto 0);
z_reg_fra_spare: in std_logic_vector(11 downto 0);
t_reg_fra_spare: in std_logic_vector(11 downto 0);
Clk : in std_logic  );
end component;

--component ELE112_LAB_5 is
--GENERIC( N : INTEGER :=12; TS : INTEGER :=64);
--    Port (    
--          x_spare_register : out std_logic_vector (11 downto 0):=(others=>'0');
--           y_spare_register : out std_logic_vector (11 downto 0):=(others=>'0');
--           z_spare_register : out std_logic_vector (11 downto 0):=(others=>'0');
--           t_spare_register : out std_logic_vector (11 downto 0):=(others=>'0');
--          LD_x_spare :in  STD_LOGIC;
--           LD_y_spare : in STD_LOGIC;
--           LD_z_spare : in STD_LOGIC;
--           LD_t_spare : in STD_LOGIC;
--           clear_12_bit: in std_logic;
--           START : inout STD_LOGIC;
--           STARTED : inout STD_LOGIC;
--           DONE : inout STD_LOGIC;
--           MOSI : out STD_LOGIC;
--           MISO : in STD_LOGIC;
--           SS : inout STD_LOGIC;
--           SCLK : inout STD_LOGIC;
--           Reset:in STD_LOGIC;
--           Starter_fsm: in std_logic;
--           beforedone_fsm: inout std_logic;
--           CLK : in STD_LOGIC);
--end component;

component ADXL362Ctrl is
generic 
(
   SYSCLK_FREQUENCY_HZ : integer := 108000000;
   SCLK_FREQUENCY_HZ   : integer := 1000000;
   NUM_READS_AVG       : integer := 16;
   UPDATE_FREQUENCY_HZ : integer := 1000
);
port
(
   SYSCLK     : in STD_LOGIC; -- System Clock
   RESET      : in STD_LOGIC;

   -- Accelerometer data signals
   ACCEL_X    : out STD_LOGIC_VECTOR (11 downto 0);
   ACCEL_Y    : out STD_LOGIC_VECTOR (11 downto 0);
   ACCEL_Z    : out STD_LOGIC_VECTOR (11 downto 0);
   ACCEL_TMP  : out STD_LOGIC_VECTOR (11 downto 0);
   Data_Ready : out STD_LOGIC;

   --SPI Interface Signals
   SCLK       : out STD_LOGIC;
   MOSI       : out STD_LOGIC;
   MISO       : in STD_LOGIC;
   SS         : out STD_LOGIC
);
end component;


end Final_components;


