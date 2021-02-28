


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;



entity register_8bit is
   
        port ( R : in std_logic_vector (7 downto 0);
               Rin: in std_logic;
               Clock : in std_logic;
               Q : out std_logic_vector (7 downto 0));  
end register_8bit;

architecture Behavioral of register_8bit is

begin
process(Clock, Rin)
    begin
    if Rin ='0' then 
    Q <=x"00";
    elsif Clock'event AND Clock = '0' then
    Q <= R;
           
    end if;
    end process;
end Behavioral;
