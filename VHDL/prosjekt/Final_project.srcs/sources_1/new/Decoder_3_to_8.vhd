library IEEE;	
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity decoder is
Port ( s : in STD_LOGIC_VECTOR (2 downto 0);

y : out STD_LOGIC_VECTOR (7 downto 0));
end decoder;

architecture Behavioral of decoder is
begin
with s select
y<="11111110" when "000",
   "11111101" when "001",
   "11111011" when "010",
   "11110111" when "011",
   "11101111" when "100",
   "11011111" when "101",
   "11111111" when "110",
   "11111111" when "111",
   "11111111" when others;
end Behavioral;
