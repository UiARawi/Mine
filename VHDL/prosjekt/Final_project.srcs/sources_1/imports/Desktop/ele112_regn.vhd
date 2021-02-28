


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ele112_regn is
GENERIC( N:INTEGER := 12);
    Port ( R : in STD_LOGIC_VECTOR (N-1 downto 0);
           Rin : in STD_LOGIC;
           clear: in std_logic;
           Clock : in STD_LOGIC;
           Q : out STD_LOGIC_VECTOR (N-1 downto 0));
end ele112_regn;

architecture Behavioral of ele112_regn is

begin
  PROCESS
  BEGIN
  if clear='0' then
  Q<=(others=>'0');
  else
     Wait UNTIL Clock'EVENT AND Clock = '0';
     IF Rin = '1' THEN
          Q <= R;
     END IF;
   end if;
  END PROCESS;
end Behavioral;
