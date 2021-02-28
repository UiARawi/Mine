library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity final_project_tb is
--  Port ( );
end final_project_tb;

architecture Behavioral of final_project_tb is
component Final_prosjekt_top_file 
    Port(Clk_Final: in std_logic;
        SW_Final: in std_logic_vector(5 downto 0);
        Decoder_Final: out std_logic_vector(7 downto 0);
        Mux_Final: out std_logic_vector(7 downto 0);
        MISO_Final: in std_logic ;
        MOSI_Final: out std_logic;
        SS_Final: inout std_logic ;
        SCLK_Final: inout std_logic 
    );
end component;

signal Clk_Final_tb: std_logic:='0';
signal SW_Final_tb: std_logic_vector(5 downto 0):="000000";
signal Decoder_Final_tb: std_logic_vector(7 downto 0):= "00000000";
signal Mux_Final_tb: std_logic_vector(7 downto 0):= "11111111";
signal MISO_Final_tb: std_logic:= '0';
signal MOSI_Final_tb: std_logic:= '0';
signal SS_Final_tb: std_logic:= '0';
signal SCLK_Final_tb: std_logic:= '0';

begin
    uut: Final_prosjekt_top_file port map(
        Clk_Final => Clk_Final_tb,
        SW_Final => SW_Final_tb,
        Decoder_Final => Decoder_Final_tb,
        Mux_Final => Mux_Final_tb,
        MISO_Final => MOSI_Final_tb,
        MOSI_Final => MoSi_Final_tb,
        SS_Final => SS_Final_tb,
        SCLK_Final => SCLK_Final_tb
    );
process
    begin
        wait for 5 ns;
        Clk_final_tb  <= '1';
        wait for 5 ns;
        Clk_final_tb <= '0';
end process; 

process
    begin
       SW_Final_tb <= "000010"; 
       wait;
end process;

end Behavioral;
