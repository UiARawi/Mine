


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.std_logic_unsigned.all;
use work.components.all;
use ieee.numeric_std.all;
use IEEE.STD_LOGIC_ARITH.ALL;


entity FSM_Ram is
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
end FSM_Ram;

architecture Behavioral of FSM_Ram is
TYPE State_type IS (S0, S1); 
SIGNAL y : State_type;
Signal Refresh_CLK_counter: std_logic_vector(19 downto 0):=(others=>'0');
signal Refresh_CLK: std_logic :='0';
signal EC_display: std_logic :='0';
signal Clear: std_logic:='0';


signal sel_ram: std_logic_vector(2 downto 0):="000";
signal s_decoder: std_logic_vector(2 downto 0):="000";
signal Counter_display_Q: std_logic_vector(2 downto 0);

--SIGNAL test_counter : STD_LOGIC_VECTOR(2 downto 0):= "000";

begin
--dividing the CLK frequency to 500HZ (2 ms-each digit):
process(CLK)
  begin
   if(CLK'event and CLK='1') then 
       Refresh_CLK_counter <= Refresh_CLK_counter + 1;
       
       if(Refresh_CLK_counter = x"1A5E0") then--T= 216 000
         Refresh_CLK<= not Refresh_CLK;
         Refresh_CLK_counter<=(others=>'0');
       end if;
         
    end if;
 end process;
FSM_transition: PROCESS(Reset, Refresh_CLK)
  
   
   BEGIN
     IF Reset = '1' THEN
        y <= S0;
     ELSIF (Refresh_CLK'EVENT AND Refresh_CLK = '1') THEN
        CASE y IS
           WHEN S0 =>
           y<=S1;
             
            WHEN S1 =>
              if Counter_display_Q = "101" then y <= S0; else y<= S1;end if;

           WHEN others =>
                y <= S0;   
        END CASE;
     END IF;
   END PROCESS;
   
 FSM_outputs:process(y, Refresh_CLK)
 begin
 
EC_display<='0';
Clear<='0';
  
   CASE y IS
        WHEN S0 =>
        Clear<='1';
        
            
        WHEN S1 =>
           EC_display<='1'; 
           s_decoder<= Counter_display_Q;
           sel_ram <=  Counter_display_Q;

         
    END CASE;
   END PROCESS; 

--port mapping
Counter_n: ele112_UpCounter 
   PORT MAP (Refresh_CLK, Clear, EC_display, Counter_display_Q); 
           
mux_1:MUX_display_RAM
    port map(ram_1,ram_2,ram_3,ram_4, ram_5, ram_6,sel_ram, ram_out);

decoder_1: decoder
    port map(s_decoder, y_decoder);
    

end Behavioral;
