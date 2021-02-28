


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;



entity MUX_display_RAM is
 Port ( a1      : in  std_logic_vector(7 downto 0);
  a2      : in  std_logic_vector(7 downto 0);
  a3      : in  std_logic_vector(7 downto 0);
  a4      : in  std_logic_vector(7 downto 0);
  a5      : in  std_logic_vector(7 downto 0);
  a6      : in  std_logic_vector(7 downto 0);
  sel     : in  std_logic_vector(2 downto 0);
  b       : out std_logic_vector(7 downto 0));
end MUX_display_RAM;

architecture Behavioral of MUX_display_RAM is
begin

 process(sel)
begin
  case sel is
    when "000" => b <= a1 ;
    when "001" => b <= a2 ;
    when "010" => b <= a3 ;
    when "011" => b <= a4 ;
    when "100" => b <= a5 ;
    when "101" => b <= a6 ;
    when others => b <= x"00";
  end case;
end process;
end Behavioral;

