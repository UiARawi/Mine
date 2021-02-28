LIBRARY ieee ;
USE ieee.std_logic_1164.all ;

ENTITY MUX_xyzt_reg IS
    PORT    ( w0, w1, w2, w3,w4 : IN STD_LOGIC_vector (11 downto 0);
            s : IN STD_LOGIC_VECTOR(2 DOWNTO 0) ;
            f : OUT STD_LOGIC_vector(11 downto 0) ) ;
END MUX_xyzt_reg ;

ARCHITECTURE Behavior OF MUX_xyzt_reg IS
BEGIN
    WITH s SELECT
    f <= w0 WHEN "000",
         w1 WHEN "001",
         w2 WHEN "010",
         w3 WHEN "011",
         w4 when others;
END Behavior ;