library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity TrafficController is
    generic 
    (
        NUM_LANES : INTEGER := 4;
        BUF_SIZE : INTEGER := 16
    );

    port
    (  
        CLK_IN : IN STD_LOGIC;
        -- 16 bits of info for each lane
        -- 63 - 48 (W) | 47 - 32 (S) | 31 - 16 (E) | 15 - 0 (N)
        SENSORS_IN : IN STD_LOGIC_VECTOR(NUM_LANES * BUF_SIZE - 1 downto 0);
        BLOCKLED_OUT : OUT STD_LOGIC_VECTOR(NUM_LANES-1 downto 0)
    );

end TrafficController;

architecture RTL of TrafficController is
    -- Data structure
    -- b0 < car Detected, b1-2 < road, b3-4 direction, b5-15 counter
    begin
end RTL;