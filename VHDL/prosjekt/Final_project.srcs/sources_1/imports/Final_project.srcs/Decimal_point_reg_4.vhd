


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use IEEE.std_logic_arith.all;
use IEEE.numeric_std.all;



entity Decimal_point_reg_4 is
    Port (w : in std_logic_vector(7 downto 0);
          reg_shown : in std_logic_vector(2 downto 0);
          q : out std_logic_vector(7 downto 0) );
end Decimal_point_reg_4;

architecture Behavioral of Decimal_point_reg_4 is

begin
process(reg_shown)
    begin
        IF reg_shown = "011" then
            q <= w;
        else
            q <= w - 1;
        end if;
end process;

end Behavioral;
