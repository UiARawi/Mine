----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.03.2019 09:33:22
-- Design Name: 
-- Module Name: toers_komp_inv - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity FSM_1 is
        Port (Clock:                    in std_logic;
              sw0, sw1, sw2, sw3 :      in std_logic;
              z :                       out std_logic_VECTOR (2 DOWNTO 0));
end FSM_1;

architecture Behavioral of FSM_1 is
type state_type is (s_idle,s0, s1, s2, s3,s4);
signal y : state_type;

begin

FSM_transition: PROCESS (Clock)
begin
    if (clock'event and clock = '1') then
    case y is
        when s_idle=>
        if sw0='0' and sw1='0' and sw2='0' and sw3='0' then
        y<=s_idle;
        end if;
        when s0 =>
            if sw0 = '1' then y <= s1; 
            elsif sw1 = '1' then y <= s2;
            elsif sw2 = '1' then y <= s3; 
            elsif sw3 = '1' then y <= s4; 
            else y <= s0; end if;
        when s1 =>
            if sw1 = '1' then y <= s2; 
            elsif sw2 = '1' then y <= s3; 
            elsif sw3 = '1' then y <= s4; 
            elsif sw0 = '1' then y <= s1; 
            else y <= s0; end if;
        when s2 =>
            if sw2 = '1' then y <= s3; 
            elsif sw3 = '1' then y <= s4; 
            elsif sw0 = '1' then y <= s1; 
            elsif sw1 = '1' then y <= s2; 
            else y <= s0; end if;
        when s3 =>
            if sw3 = '1' then y <= s4; 
            elsif sw0 = '1' then y <= s1; 
            elsif sw1 = '1' then y <= s2; 
            elsif sw2 = '1' then y <= s3; 
            else y <= s0; end if;
        when s4 =>
            if sw0 = '1' then y <= s1; 
            elsif sw1 = '1' then y <= s2; 
            elsif sw2 = '1' then y <= s3; 
            elsif sw3 = '1' then y <= s4; 
            else y <= s0; end if;
        when others =>
            y <= s0;
    end case;
  end if;
end process;    
    
FSM_outputs: PROCESS (y, clock)
begin
    z <= "111";
    case y is
        when s_idle =>
            z<="111";
        when s0 =>
        when s1 =>
            z <= "000";
        when s2 =>
            z <= "001";
        when s3 =>
            z <= "010";
        when s4 =>
            z <= "011";
    end case;
end PROCESS;
         
        
end Behavioral;
