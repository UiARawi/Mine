LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY MUX_4 IS
    PORT    ( w0, w1, w2, w3 : IN STD_LOGIC ;
            s : IN STD_LOGIC_VECTOR(1 DOWNTO 0) ;
            f : OUT STD_LOGIC ) ;
END MUX_4 ;

ARCHITECTURE Behavior OF MUX_4 IS
BEGIN
    WITH s SELECT
    f <= w0 WHEN "00",
         w1 WHEN "01",
         w2 WHEN "10",
         w3 WHEN OTHERS ;
END Behavior ;