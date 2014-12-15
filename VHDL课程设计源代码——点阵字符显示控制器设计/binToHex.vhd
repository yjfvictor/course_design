-- ------------------------------------------
--   binary input to hexadecimal output
--  
--          Author: Victor Jianfei Ye
-- ------------------------------------------

LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY binToHex IS
	PORT ( input: IN STD_LOGIC_VECTOR(3 DOWNTO 0 );
			dot_matrix_screen: OUT STD_LOGIC_VECTOR(255 DOWNTO 0 )
		);
END ENTITY binToHex;

ARCHITECTURE IO OF binToHex IS
BEGIN
	PROCESS ( input(0), input(1), input(2), input(3))
	BEGIN
		CASE input IS
			-- 0
			WHEN "0000" => dot_matrix_screen <= "0011111111111100001000000000010000100000000001000010000000000100001000000000010000100000000001000010000000000100001000000000010000100000000001000010000000000100001000000000010000100000000001000010000000000100001000000000010000100000000001000011111111111100";  -- 0
			-- 1
			WHEN "0001" => dot_matrix_screen <= "0000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000100000";  -- 1
			-- 2
			WHEN "0010" => dot_matrix_screen <= "0000000000000000000001111111000000001000000010000001000000000100000000000000100000000000000100000000000000100000000000000100000000000000100000000000000100000000000000100000000000000100000000000000100000000000000100000000000000111111111111000000000000000000";  -- 2
			-- 3
			WHEN "0011" => dot_matrix_screen <= "0000011111100000000010000001000000010000000010000000000000000100000000000000100000000000000100000000000000100000000011111100000000000000001000000000000000010000000000000000100000000000000001000000000000001000000100000001000000001000001000000000011111000000";  -- 3
			-- 4
			WHEN "0100" => dot_matrix_screen <= "0000000000110000000000001111000000000001101100000000001100110000000001100011000000001100001100000001100000110000001100000011000011111111111111111111111111111111000000000011000000000000001100000000000000110000000000000011000000000000001100000000000000110000";  -- 4
			-- 5
			WHEN "0101" => dot_matrix_screen <= "0001111111111100000100000000000000010000000000000001000000000000000100000000000000010000000000000001000000000000000111111100000000000000011100000000000000111000000000000001110000000000000001110000000000000111000000000001110000000000001110000001111111100000";  -- 5
			-- 6
			WHEN "0110" => dot_matrix_screen <= "0000000011111110000000111000000000000111000000000000111000000000000111000000000000111000000000000111000000000000011100000000000001111111111000000111000000111000011100000000111001110000000001110011100000001110000111100011100000000111111100000000000000000000";  -- 6
			-- 7
			WHEN "0111" => dot_matrix_screen <= "0011111111111110000000000000011000000000000001100000000000000110000000000000110000000000000011000000000000001100000000000000110000000000000110000000000000011000000000000001100000000000000110000000000000011000000000000001100000000000000110000000000000011000";  -- 7
			-- 8
			WHEN "1000" => dot_matrix_screen <= "0000111111110000001110000001110001110000000011101110000000000111011100000000111000111000000111000000111001110000000001111110000000001111111100000011100000011100011100000000111011100000000001110111000000001110001110000001110000001110011100000000011111100000";  -- 8
			-- 9
			WHEN "1001" => dot_matrix_screen <= "0000111111110000000110000001100000110000000011000011000000000110000110000000001100001100000000110000011000000011000000111111111100000000000001100000000000001100000000000001100000000000001100000000000001100000000000001100000000000001100000000000011000000000";  -- 9
			-- A
			WHEN "1010" => dot_matrix_screen <= "0000000110000000000001100110000000001100001100000000110000110000000110000001100000011000000110000001100000011000001100000000110000111111111111000011000000001100011000000000011001100000000001100110000000000110110000000000001111000000000000111100000000000011";  -- A
			-- B
			WHEN "1011" => dot_matrix_screen <= "0111111111000000011100000111000001110000000111000111000000000111011100000000011101110000000111000111000001110000011111111100000001111111110000000111000001110000011100000001110001110000000001110111000000000111011100000001110001110000011100000111111111000000";  -- B
			-- C
			WHEN "1100" => dot_matrix_screen <= "0000001111111000000001100000110000011000000001100011000000000011001100000000000001100000000000000110000000000000110000000000000011000000000000000110000000000000011000000000000000110000000000000011000000000011000011000000011000000110000011000000001111111000";  -- C
			-- D
			WHEN "1101" => dot_matrix_screen <= "1111111110000000110000000110000011000000000110001100000000001100110000000000110011000000000001101100000000000011110000000000001111000000000000111100000000000011110000000000011011000000000011001100000000001100110000000001100011000000011000001111111110000000";  -- D
			-- E
			WHEN "1110" => dot_matrix_screen <= "1111111111111111111111111111111111000000000000001100000000000000110000000000000011000000000000001100000000000000111111111111111111111111111111111100000000000000110000000000000011000000000000001100000000000000110000000000000011111111111111111111111111111111";  -- E
			-- F
			WHEN "1111" => dot_matrix_screen <= "1111111111111111111111111111111111000000000000001100000000000000110000000000000011000000000000001100000000000000111111111111111111111111111111111100000000000000110000000000000011000000000000001100000000000000110000000000000011000000000000001100000000000000";  -- F
			-- others
			WHEN OTHERS => dot_matrix_screen <= "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
		END CASE;
	END PROCESS;
END ARCHITECTURE IO;