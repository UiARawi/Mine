


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

PACKAGE components_Lab_5 IS   


COMPONENT ELE112_shiftlne is
GENERIC ( N : INTEGER := 4);
    Port ( R : in STD_LOGIC_VECTOR (N -1 downto 0);
           L : in STD_LOGIC;
           E : in STD_LOGIC;
           W : in STD_LOGIC;
           Clock : in STD_LOGIC;
           Q : inout STD_LOGIC_VECTOR (N -1 downto 0));
END COMPONENT;

COMPONENT ele112_PreScaler is
    Port ( clk : in STD_LOGIC;
           reset : in STD_LOGIC;
           preScalerNumber : in STD_LOGIC_VECTOR (2 downto 0);
           clkOut : out STD_LOGIC);
END COMPONENT;

  COMPONENT ele112_regn  --register
    GENERIC ( N : INTEGER := 12);
    PORT (  R           :IN STD_LOGIC_VECTOR ( N-1 DOWNTO 0);
            RIN         : in  STD_LOGIC;
            clear       : in std_logic;
            Clock       : IN  STD_LOGIC;
            Q           : OUT STD_LOGIC_VECTOR(N-1 DOWNTO 0));
  END COMPONENT; 
  
  COMPONENT ele112_UpDownCounter  --register
    GENERIC ( N : INTEGER := 8);
    Port ( count: in STD_LOGIC;
           UP_DOWN : in STD_LOGIC;
           clear: in STD_LOGIC;
           Q : inout STD_LOGIC_VECTOR (N-1 downto 0));
    END COMPONENT;       

       
       END components_Lab_5;