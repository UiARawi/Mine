


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;



entity register_shown is
    Port ( w   : in std_logic_vector(2 downto 0);
           y   : out std_logic_vector(7 downto 0));
end register_shown;

architecture Behavioral of register_shown is


begin
   process(w)
   begin
   case w is      -- a b c d e f g p
    when "000"   =>y <="10010001"; --"x"
    when "001"   =>y <="10001001";  --"y"
    when "010"   =>y <="00100101"; --"z"
    when "011"   =>y <="11100001";--"t"
    when others =>y <="11111111";
    end case;
    end process;
    
end Behavioral;
