----------------------------------------------------------------------------------

----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.components_lab_5.all;


entity ELE112_LAB_5 is
GENERIC( N : INTEGER :=12; TS : INTEGER :=64);
    Port ( 
           x_spare_register : out std_logic_vector (11 downto 0):=(others=>'0');
           y_spare_register : out std_logic_vector (11 downto 0):=(others=>'0');
           z_spare_register : out std_logic_vector (11 downto 0):=(others=>'0');
           t_spare_register : out std_logic_vector (11 downto 0):=(others=>'0');
           LD_x_spare :in  STD_LOGIC;
           LD_y_spare : in STD_LOGIC;
           LD_z_spare : in STD_LOGIC;
           LD_t_spare : in STD_LOGIC;
           clear_12_bit: in std_logic;
           START : inout STD_LOGIC;
           STARTED : inout STD_LOGIC;
           DONE : inout STD_LOGIC;
           MOSI : out STD_LOGIC;
           MISO : in STD_LOGIC;
           SS : inout STD_LOGIC;
           SCLK : inout STD_LOGIC;
           Reset:in STD_LOGIC;
           Starter_fsm: in std_logic;
           beforedone_fsm: inout std_logic;
           CLK : in STD_LOGIC);
end ELE112_LAB_5;

architecture Behavioral of ELE112_LAB_5 is
  TYPE State_type IS (S0, S1, S2, S3,S4,s5,s6); 
  SIGNAL y : State_type;
  signal preScalerNr : STD_LOGIC_VECTOR (2 downto 0):="100";
  SIGNAL TX_register : std_logic_vector (63 downto 0);
  SIGNAL S_register : std_logic_vector (63 downto 0);
  SIGNAL Count : std_logic_vector (7 downto 0);
  SIGNAL clear_counter : STD_LOGIC ;
  SIGNAL LS : STD_LOGIC;
  SIGNAL ES : STD_LOGIC ;
  SIGNAL EC : STD_LOGIC ; 
  SIGNAL Clk_Div : STD_LOGIC;
  SIGNAL  MISO_int : STD_LOGIC ;
  SIGNAL  start_signal : STD_LOGIC ;
  


begin




-- You may need more states to this FSM    
FSM_transition: PROCESS(Reset, CLK_Div)
   BEGIN
 
     if Reset = '1' then  y <= S0;
     ELSIF (CLK_Div'EVENT AND CLK_Div = '1') THEN
        CASE y IS
          
           WHEN S0 =>
           if Starter_fsm ='1' then y<=S1; else y<=s0;end if;
           WHEN S1 =>
            if start='1' then y<=S2; else y<=s1;end if;
            WHEN S2 =>
              IF count = x"50" THEN  y <= S3; ELSE y <= S2; END IF;          
           WHEN S3 =>
              IF ss= '1' THEN y <= S4 ; ELSE y <= S3; END IF;
          WHEN S4 =>
              IF SCLK = '0' THEN y <= S5 ; ELSE y <= S4; END IF;
          when S5 => 
             if beforedone_fsm = '1' then y<= S6 ; else y <= S5;end if;
          when S6 =>
             if Done = '1' then y<= S0 ; else y <= S6;end if;
           WHEN others =>
               y <= S0 ;   
        END CASE;
     END IF;
     
    
   
     
    
   END PROCESS;
   
   
FSM_outPuts: PROCESS(y, Clk_Div)
   BEGIN
    EC<='0';
    Done <='0';
    STARTED <='0';
    clear_counter<='0';
    ES<='0';
    SS<='1';
    start<='0';
    
    CASE y IS
       when s0=>
       WHEN S1 =>
            TX_register  <= x"0B" & x"0E000000000000";
            clear_counter <= '1';start<='1';
            LS <='1';
       WHEN S2 =>
           STARTED<='1';LS<='0';ES<='1';SCLK<=Clk_Div;
           EC<='1';  SS <= '0';
        WHEN S3 =>
           clear_counter <= '1';SS<='1';
        WHEN S4 =>
            SCLK<='0';
          
        when S5 =>
        
        when S6 =>
            Done<='1';
        
        
        END CASE;
   END PROCESS;   
   
MISO_sample: PROCESS(SCLK)
   BEGIN
   IF SCLK'EVENT AND SCLK = '1' THEN
     MISO_int <= MISO;
    end if; 
  END PROCESS;  
   

   
   -- datapath circuit  
   
Counter_n: ele112_UpDownCounter  
           PORT MAP (SCLK,'1',clear_counter, Count);  
Prescal_clk: ele112_PreScaler
           port map(CLK, Reset,preScalerNr,CLK_Div); 
           
SPI_SHIFT_REG:ELE112_shiftlne GENERIC MAP(N => TS)
           PORT MAP (TX_register,LS, ES,MISO_int,SCLK,S_register);
                           
x_Spare_DATA_REG:ele112_regn GENERIC MAP(N => N)
           PORT MAP(S_register(59 downto 48),LD_x_spare,clear_12_bit, CLK,x_spare_register); 
y_Spare_DATA_REG:ele112_regn GENERIC MAP(N => N)
           PORT MAP(S_register(43 downto 32),LD_y_spare,clear_12_bit, CLK,y_spare_register); 
 z_Spare_DATA_REG:ele112_regn GENERIC MAP(N => N)
           PORT MAP(S_register(27 downto 16),LD_z_spare,clear_12_bit, CLK,z_spare_register); 
t_Spare_DATA_REG:ele112_regn GENERIC MAP(N => N)
           PORT MAP(S_register(11 downto 0),LD_t_spare,clear_12_bit, CLK,t_spare_register); 
-- MISO_int<= S_register(0);
 MOSI<=S_register(63);
 
 

                               

                              
end Behavioral;
