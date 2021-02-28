----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 18.03.2019 10:40:28
-- Design Name: 
-- Module Name: Clock_divider - Behavioral
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

--Kilde:
--https://surf-vhdl.com/how-to-implement-clock-divider-vhdl/ (18.03.2019, 10:43)

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity clock_div_pow2 is
port(
  clk         : in  std_logic;
  rst         : in  std_logic;
  clk_div2    : out std_logic;
  clk_div4    : out std_logic;
  clk_div8    : out std_logic);
end clock_div_pow2;

architecture rtl of clock_div_pow2 is
signal clk_divider        : unsigned(2 downto 0);

begin
p_clk_divider: process(rst, clk)
begin
  if(rst='1') then
    clk_divider   <= (others=>'0');
  elsif(rising_edge(clk)) then
    clk_divider   <= clk_divider + 1;
  end if;
  
end process p_clk_divider;
clk_div2    <= clk_divider(0);
clk_div4    <= clk_divider(1);
clk_div8    <= clk_divider(2);

end rtl;