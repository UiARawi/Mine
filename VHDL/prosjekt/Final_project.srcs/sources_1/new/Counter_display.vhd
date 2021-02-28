

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;


entity ele112_UpCounter is
    
    Port ( Count : in STD_LOGIC;
           clear: in STD_LOGIC;
           EC: in STD_LOGIC;
           Q : out STD_LOGIC_VECTOR (2 downto 0));
end ele112_UpCounter;

architecture Behavioral of ele112_UpCounter is

signal Q_signal :  STD_LOGIC_VECTOR (2 downto 0);


begin
  PROCESS (Count, clear)
   BEGIN
   IF clear = '1' THEN
      Q_signal <= (others => '0');    
      ELSIF (Count'EVENT AND Count = '1') THEN
        IF EC = '1' THEN
             Q_signal <= Q_signal + 1;
         end if;
     END IF;
    END PROCESS;
    
 Q<= Q_signal;

end Behavioral;
