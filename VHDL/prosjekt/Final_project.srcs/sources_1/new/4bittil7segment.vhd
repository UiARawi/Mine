


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;



entity fourbittil7segment is
    Port(   w   : in std_logic_vector(3 downto 0);
            y   : out std_logic_vector(7 downto 0));
end fourbittil7segment;

architecture Behavioral of fourbittil7segment is



begin
  process(w)
  begin
  case w is       --a b c d e f g p
      when "0000"=>y<="00000011"; --"0"
      when "0001"=>y<="10011111"; --"1"
      when "0010"=>y<="00100101";-- 2
      when "0011"=>y<="00001101";-- 3
      when "0100"=>y<="10011001";-- 4
      when "0101"=>y<="01001001";-- 5
      when "0110"=>y<="01000001";-- 6
      when "0111"=>y<="00011111";-- 7
      when "1000"=>y<="00000001";-- 8
      when "1001"=>y<="00001001";-- 9
      when others=>y<="11111111";
  end case;
  end process;

end Behavioral;
