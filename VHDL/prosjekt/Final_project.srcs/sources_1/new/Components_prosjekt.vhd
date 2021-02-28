


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

package components_prosjekt is
component pluss_minus is
    Port ( w   : in std_logic;
           y   : out std_logic_vector(7 downto 0));
end component;

component register_shown is
    Port ( w   : in std_logic_vector(1 downto 0);
           y   : out std_logic_vector(7 downto 0));
end component;

component fourbittil7segment is
    Port(   w   : in std_logic_vector(3 downto 0);
            y   : out std_logic_vector(7 downto 0));
end component;

component register_8bit is
    generic( N : Integer := 8);
        port ( R : in std_logic_vector (N-1 downto 0);
               Rin: in std_logic;
               Clock : in std_logic;
               Q : out std_logic_vector (N-1 downto 0));  
end component;

component register_12bit is
    generic( N : Integer := 12);
        port ( R : in std_logic_vector (N-1 downto 0);
               Rin: in std_logic;
               Clock : in std_logic;
               Q : out std_logic_vector (N-1 downto 0));  
end component;

component toers_komp_inv is
    generic( N : integer := 12);
        Port (y : in std_logic_vector(N-1 downto 0);
              m : out std_logic;
              z : out std_logic_vector(N-1 downto 0));
end component;

component ele112_UpDownCounter is
    GENERIC( N:INTEGER := 3);
    Port ( Count : in STD_LOGIC;
           UP_DOWN : in STD_LOGIC;
           clear: in STD_LOGIC;
           Q : inout STD_LOGIC_VECTOR (N-1 downto 0));
end component;

component FSM_2 is
    Port (C   : out std_logic_vector(2 downto 0);
          CLK : in std_logic);
end component;

component clock_div_pow2 is
port(
  clk         : in  std_logic;
  rst         : in  std_logic;
  clk_div2    : out std_logic;
  clk_div4    : out std_logic;
  clk_div8    : out std_logic);
end component;

end components_prosjekt;
