


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity ELE112_shiftlne is
GENERIC ( N : INTEGER := 4);
    Port ( R : in STD_LOGIC_VECTOR (N -1 downto 0);
           L : in STD_LOGIC;
           E : in STD_LOGIC;
           W : in STD_LOGIC;
           Clock : in STD_LOGIC;
           Q : inout STD_LOGIC_VECTOR (N -1 downto 0));
end ELE112_shiftlne;

architecture Behavioral of ELE112_shiftlne is

begin
     PROCESS(Clock, L,R)
     BEGIN
       IF L = '1' THEN
        Q <= R;
       ELSIF Clock'EVENT AND Clock = '0' THEN
        IF E = '1' THEN
          Q(0) <= W;
          Genbits: FOR i IN 1 TO N-1 LOOP
              Q(i) <= Q(i-1);
          END LOOP;
        END IF;
       END IF;
     END PROCESS;
end Behavioral;
