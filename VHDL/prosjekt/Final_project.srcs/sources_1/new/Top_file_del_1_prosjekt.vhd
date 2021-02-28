


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.components_all.all;



entity Top_file_del_1_prosjekt is
Port ( 
sw: in std_logic_vector(5 downto 0);
decodr_out: out std_logic_vector(7 downto 0);
mux_out:out std_logic_vector(7 downto 0);
x_reg_fra_spare: in std_logic_vector(11 downto 0);
y_reg_fra_spare: in std_logic_vector(11 downto 0);
z_reg_fra_spare: in std_logic_vector(11 downto 0);
t_reg_fra_spare: in std_logic_vector(11 downto 0);
Clk : in std_logic  );
end Top_file_del_1_prosjekt;

architecture Behavioral of Top_file_del_1_prosjekt is

signal ein: std_logic_vector(3 downto 0);
signal ti: std_logic_vector(3 downto 0);
signal hundre: std_logic_vector(3 downto 0);
signal tusen: std_logic_vector(3 downto 0);
signal to_komp_out: std_logic_vector(11 downto 0);
signal toers_komp: std_logic;
signal ram_1_1: std_logic_vector(7 downto 0);
signal ram_2_1: std_logic_vector(7 downto 0);
signal ram_3_1: std_logic_vector(7 downto 0);
signal ram_4_1: std_logic_vector(7 downto 0);
signal ram_5_1: std_logic_vector(7 downto 0);
signal ram_6_1: std_logic_vector(7 downto 0);
signal reg_lest: std_logic_vector(2 downto 0);
signal mux_4_1: std_logic_vector(11 downto 0);
signal idle_reg_data: std_logic_vector (11 downto 0):=(others=>'0');
signal idle_reg_dout: std_logic_vector (11 downto 0);
signal x_reg_1: std_logic_vector (11 downto 0);
signal y_reg_1: std_logic_vector (11 downto 0);
signal z_reg_1: std_logic_vector (11 downto 0);
signal t_reg_1: std_logic_vector (11 downto 0);
signal cdiv2: std_logic;
signal cdiv4: std_logic;
signal cdiv8: std_logic;
signal ram1_fsm: std_logic_vector(7 downto 0); 
signal ram2_fsm: std_logic_vector(7 downto 0); 
signal ram3_fsm: std_logic_vector(7 downto 0); 
signal ram4_fsm: std_logic_vector(7 downto 0); 
signal ram5_fsm: std_logic_vector(7 downto 0); 
signal ram6_fsm: std_logic_vector(7 downto 0); 
signal fra_decimal_point_4: std_logic_vector(7 downto 0); 
signal fra_decimal_point_2: std_logic_vector(7 downto 0); 


signal clk_fsm_1: std_logic;
signal fsm_1_out: std_logic_vector(2 downto 0);
signal Clk_div: std_logic;

begin

fsm_display:  FSM_Ram 
        Port map(
        Reset => '0', 
        CLK => Clk, 
        ram_1 => ram1_fsm,
        ram_2 => ram2_fsm,
        ram_3  => ram3_fsm,
        ram_4 => ram4_fsm,
        ram_5  => ram5_fsm,
        ram_6 => ram6_fsm,
        ram_out => mux_out,
        y_decoder => decodr_out
        );
        
              
CLK_divider: clock_div_pow2 
port map(
  clk => Clk_div,         
  rst => '0',         
  clk_div2 => cdiv2,   
  clk_div4 => cdiv4,   
  clk_div8 => cdiv8   );
  
Prescaler: scale_clock
  port map(
    clk_100Mhz => Clk,
    rst => '0',
    clk_1Hz => Clk_div);

  
Mux_clock_div: MUX_4 
    PORT  map  ( w0 => Clk_div, w1 => cdiv2, w2 => cdiv4, w3 => cdiv8, 
            s => sw(5 downto 4),
            f => clk_fsm_1) ;

 idle_reg:register_12bit 
        port map ( R =>idle_reg_data,
               Rin =>'1',
               Clock => Clk, 
               Q => idle_reg_dout);

               
 X_reg:register_12bit 
        port map ( R =>x_reg_fra_spare,
               Rin =>'1',
               Clock => Clk, 
               Q => x_reg_1);
               
Y_reg:register_12bit 
        port map ( R =>y_reg_fra_spare,
               Rin =>'1',
               Clock => Clk, 
               Q => y_reg_1);

Z_reg:register_12bit 
        port map ( R =>z_reg_fra_spare,
               Rin =>'1',
               Clock => Clk, 
               Q => z_reg_1);

T_reg:register_12bit 
        port map ( R =>t_reg_fra_spare,
               Rin =>'1',
               Clock => Clk, 
               Q => t_reg_1);
Fsm_1_sw: FSM_1 
        Port map (Clock => clk_fsm_1,
              sw0 => sw(0), sw1 => sw(1), sw2 => sw(2), sw3 => sw(3), 
              z => fsm_1_out);
               
Mux_xyzt: MUX_xyzt_reg 
    PORT map  ( w0 => x_reg_1, w1 => y_reg_1, w2 => z_reg_1, w3 => t_reg_1,w4=>idle_reg_dout, 
            s => fsm_1_out,
            f => mux_4_1 ) ;
               
Twos_com: toers_komp_inv 
        Port map(y => mux_4_1,
              m => toers_komp,
              z => to_komp_out);
              
BCD_display:  bin2bcd_12bit 
    Port map ( binIN => to_komp_out,
           ones => ein,
           tens => ti,
           hundreds => hundre,
           thousands => tusen
          );

            

              
fortegn_display: pluss_minus
    Port map ( w => toers_komp,   
           y => ram_5_1 );  
           
X_Y_Z_shown: register_shown 
    Port map ( w => fsm_1_out,  
           y => ram_6_1  );

first_rigisters:  fourbittil7segment 
    Port map(   w => ein,
            y => ram_1_1);

second_rigisters:  fourbittil7segment 
    Port map(   w => ti,  
            y => ram_2_1 );
            

third_rigisters:  fourbittil7segment 
    Port map(   w => hundre,  
            y => ram_3_1  );
                       

fourth_rigisters:  fourbittil7segment 
    Port map(   w => tusen,  
            y => ram_4_1  );            
            

Reg_0_ram: register_8bit 
        port map ( R =>ram_1_1 ,
               Rin => '1',
               Clock => Clk, 
               Q => ram1_fsm) ;     

Reg_1_ram: register_8bit 
        port map ( R => fra_decimal_point_2,
               Rin => '1',
               Clock => Clk, 
               Q => ram2_fsm) ;   

Reg_2_ram: register_8bit 
        port map ( R =>ram_3_1,
               Rin => '1',
               Clock => Clk, 
               Q => ram3_fsm) ;   

Reg_3_ram: register_8bit 
        port map ( R => fra_decimal_point_4,
               Rin => '1',
               Clock => Clk, 
               Q => ram4_fsm) ;   

Reg_4_ram: register_8bit 
        port map ( R => ram_5_1,
               Rin => '1',
               Clock => Clk, 
               Q => ram5_fsm) ;   

Reg_5_ram: register_8bit 
        port map ( R => ram_6_1,
               Rin => '1',
               Clock => Clk, 
               Q => ram6_fsm) ; 
               
Decimal_point_4: Decimal_point_reg_4 
    Port map (w=>ram_4_1,
          reg_shown=>fsm_1_out,
          q=>fra_decimal_point_4 );
          
Decimal_point_2: Decimal_point_reg_2 
    Port map (w=>ram_2_1,
          reg_shown=>fsm_1_out,
          q=>fra_decimal_point_2 );

           
end Behavioral;
