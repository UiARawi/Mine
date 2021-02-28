


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;


entity ele112_UpDownCounter is
    GENERIC( N:INTEGER := 8);
    Port ( Count : in STD_LOGIC;
           UP_DOWN : in STD_LOGIC;
           clear: in STD_LOGIC;
           Q : inout STD_LOGIC_VECTOR (N-1 downto 0));
end ele112_UpDownCounter;

architecture Behavioral of ele112_UpDownCounter is


begin
  PROCESS (Count, clear)
   BEGIN
   IF clear = '1' THEN
      Q <= (others => '0');    
      ELSIF (Count'EVENT AND Count = '0') THEN
        IF UP_DOWN = '1' THEN
             Q <= Q + 1;
        ELSE
             Q <= Q -1;     
        END IF;
       
       END IF;
      
    
    END PROCESS;

end Behavioral;
