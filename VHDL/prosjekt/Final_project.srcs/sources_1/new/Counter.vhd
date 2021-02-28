

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use ieee.std_logic_unsigned.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ele112_UpDownCounter is
    
    Port ( Count : in STD_LOGIC;
           clear: in STD_LOGIC;
           EC: in std_logic;
           Q : out STD_LOGIC_VECTOR (2 downto 0));
end ele112_UpDownCounter;

architecture Behavioral of ele112_UpDownCounter is
signal Q_signal: std_logic_vector(2 downto 0):="000";


begin
  PROCESS (Count, clear)
   BEGIN
   IF clear = '1' THEN
      Q_signal <= (others => '0'); 
   ELSIF (Count'EVENT AND Count = '1') then  
--    ELSIF Q ="111" then 
--      Q <="000";
      
       Q_signal <= Q_signal + 1;
     END IF;
   
   END PROCESS;
   
 Q<=Q_signal;

end Behavioral;