


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

package components is


component scale_clock is
  port (
    clk_100Mhz : in std_logic;
    rst       : in  std_logic;
    clk_1Hz   : out std_logic);
end component;

component MUX_4 IS
    PORT    ( w0, w1, w2, w3 : IN STD_LOGIC ;
            s : IN STD_LOGIC_VECTOR(1 DOWNTO 0) ;
            f : OUT STD_LOGIC ) ;
END component ;

component FSM_1 is
        Port (Clock:                    in std_logic;
              sw0, sw1, sw2, sw3 :      in std_logic;
              z :                       out std_logic_VECTOR (1 DOWNTO 0));
end component;


component FSM_Ram is
        Port (
        Reset: in std_logic;
        CLK: in std_logic;

        ram_1: in std_logic_vector(7 downto 0);
        ram_2: in std_logic_vector(7 downto 0);
        ram_3:in  std_logic_vector(7 downto 0);
        ram_4:in  std_logic_vector(7 downto 0);
        ram_5:in  std_logic_vector(7 downto 0);
        ram_6:in  std_logic_vector(7 downto 0);
        ram_out:out std_logic_vector(7 downto 0);
        y_decoder:out std_logic_vector(7 downto 0)
        );
end component;


component bin2bcd_12bit is
    Port ( binIN : in  STD_LOGIC_VECTOR (11 downto 0);
           ones : out  STD_LOGIC_VECTOR (3 downto 0);
           tens : out  STD_LOGIC_VECTOR (3 downto 0);
           hundreds : out  STD_LOGIC_VECTOR (3 downto 0);
           thousands : out  STD_LOGIC_VECTOR (3 downto 0)
          );
end component;
 component decoder 
 port(  s : in STD_LOGIC_VECTOR (2 downto 0);
        y : out STD_LOGIC_VECTOR (7 downto 0)
 );
 end component;
 
 component ele112_UpCounter
 
    Port ( Count : in STD_LOGIC;
           clear: in STD_LOGIC;
           EC: in std_logic;
           Q : out STD_LOGIC_VECTOR (2 downto 0));
 
 end component;
 
 component MUX_display_RAM
  Port ( a1      : in  std_logic_vector(7 downto 0);
  a2      : in  std_logic_vector(7 downto 0);
  a3      : in  std_logic_vector(7 downto 0);
  a4      : in  std_logic_vector(7 downto 0);
  a5      : in  std_logic_vector(7 downto 0);
  a6      : in  std_logic_vector(7 downto 0);
  sel     : in  std_logic_vector(2 downto 0);
  b       : out std_logic_vector(7 downto 0));
end component;

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
            y   : out std_logic_vector(7 to 0));
end component;

component register_8bit is
    
        port ( R : in std_logic_vector (7 downto 0);
               Rin: in std_logic;
               Clock : in std_logic;
               Q : out std_logic_vector (7 downto 0));  
end component;

component register_12bit is
    
        port ( R : in std_logic_vector (11 downto 0);
               Rin: in std_logic;
               Clock : in std_logic;
               Q : out std_logic_vector (11 downto 0));  
end component;

component toers_komp_inv is
    generic( N : integer := 12);
        Port (y : in std_logic_vector(N-1 downto 0);
              m : out std_logic;
              z : out std_logic_vector(N-1 downto 0));
end component;



component clock_div_pow2 is
port(
  clk         : in  std_logic;
  rst         : in  std_logic;
  clk_div2    : out std_logic;
  clk_div4    : out std_logic;
  clk_div8    : out std_logic);
end component;

component MUX_xyzt_reg IS
    PORT    ( w0, w1, w2, w3 : IN STD_LOGIC_vector (11 downto 0);
            s : IN STD_LOGIC_VECTOR(1 DOWNTO 0) ;
            f : OUT STD_LOGIC_vector(11 downto 0) );
  end component;
end components;
