----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 08.03.2019 08:33:35
-- Design Name: 
-- Module Name: pluss_minus - Behavioral
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

entity pluss_minus is
    Port ( w   : in std_logic;
           y   : out std_logic_vector(7 downto 0));
end pluss_minus;

architecture Behavioral of pluss_minus is

signal a : std_logic;

begin
    a <= w;
    with a select
    y <=    "11111101" when '1', --"minus"
            
            "11111111" when others;       

end Behavioral;
