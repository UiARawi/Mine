


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;


entity ele112_PreScaler is
    Port ( clk : in STD_LOGIC;
           reset : in STD_LOGIC;
           preScalerNumber : in STD_LOGIC_VECTOR (2 downto 0);
           clkOut : out STD_LOGIC);
end ele112_PreScaler;

architecture Behavioral of ele112_PreScaler is
signal counter : STD_LOGIC_VECTOR (9 DOWNTO 0):= (others => '0');
begin
  PROCESS(clk)
    BEGIN
      IF (clk'EVENT AND clk = '1') THEN
       IF ( reset = '1') THEN
         counter <= (others => '0');
       ELSE  
        counter <= counter + 1 ;
       END IF; 
      END IF; 
   END PROCESS; 
   
   WITH  preScalerNumber SELECT
    clkOut <= counter(2) WHEN  "000",--25 MHZ
              counter(3) WHEN  "001",--12.5 MHz
              counter(4) WHEN  "010",--6.25 MHz
              counter(5) WHEN  "011",--3.75 MHz
              counter(6) WHEN  "100",--1.825 MHz
              counter(7) WHEN  "101",--0.9125 MHz 
              counter(8) WHEN OTHERS; 

end Behavioral;
