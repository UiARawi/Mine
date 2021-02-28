library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity scale_clock is
  port (
    clk_100Mhz : in std_logic;
    rst       : in  std_logic;
    clk_1Hz   : out std_logic);
end scale_clock;

architecture Behavioral of scale_clock is

  signal prescaler : unsigned(26 downto 0);
  signal clk_1Hz_i : std_logic;
begin

  gen_clk : process (clk_100Mhz, rst)
  begin  -- process gen_clk
    if rst = '1' then
      clk_1Hz_i   <= '0';
      prescaler   <= (others => '0');
    elsif rising_edge(clk_100Mhz) then   -- rising clock edge
      if prescaler = X"2FAF080" then     -- 100 000 000 in hex
        prescaler   <= (others => '0');
        clk_1Hz_i   <= not clk_1Hz_i;
      else
        prescaler <= prescaler + "1";
      end if;
    end if;
  end process gen_clk;

clk_1Hz <= clk_1Hz_i;

end Behavioral;