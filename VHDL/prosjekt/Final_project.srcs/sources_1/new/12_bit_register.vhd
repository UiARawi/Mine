----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.03.2019 09:22:31
-- Design Name: 
-- Module Name: 12_bit_register - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity register_12bit is
    
        port ( R : in std_logic_vector (11 downto 0);
               Rin: in std_logic;
               Clock : in std_logic;
               Q : out std_logic_vector (11 downto 0));  
end register_12bit;

architecture Behavioral of register_12bit is

begin
process(Clock)
    begin
        if (Clock'event AND Clock = '0') then
            if (Rin = '1') then
                Q <= R;
            end if;
        end if;
    end process;
end Behavioral;
