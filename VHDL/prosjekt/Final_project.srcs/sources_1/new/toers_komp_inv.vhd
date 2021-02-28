


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.numeric_std.all;
use ieee.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;


entity toers_komp_inv is
    generic( N : integer := 12);
        Port (y : in std_logic_vector(N-1 downto 0);
              m : out std_logic;
              z : out std_logic_vector(N-1 downto 0));
end toers_komp_inv;

architecture Behavioral of toers_komp_inv is
signal a : std_logic_vector(N-1 downto 0);

begin
    
    process(y(N-1))
    begin
        IF y(N-1) = '1' then
            m <= y(N-1);
            a <= NOT y;
            z <= a + 1;   
        else
            m <= y(N-1);z <= y;      
        end if;
    end process;
        
        
        



end Behavioral;
