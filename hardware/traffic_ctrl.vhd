library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity TrafficController is
    generic 
    (
        NUM_LANES : INTEGER := 4;
        BUF_SIZE : INTEGER := 16;
        NORTH : STD_LOGIC_VECTOR(1 downto 0) := "00";
        EAST : STD_LOGIC_VECTOR(1 downto 0) := "01";
        SOUTH : STD_LOGIC_VECTOR(1 downto 0) := "10";
        WEST : STD_LOGIC_VECTOR(1 downto 0) := "11";
        
        RIGHT : STD_LOGIC_VECTOR(1 downto 0) := "00";
        STRAIGHT : STD_LOGIC_VECTOR(1 downto 0) := "01";
        LEFT : STD_LOGIC_VECTOR(1 downto 0) := "10"
    );

    port
    (  
        CLK_IN : IN STD_LOGIC;
        -- 16 bits of info for each lane
        -- 63 - 48 (W) | 47 - 32 (S) | 31 - 16 (E) | 15 - 0 (N)
        SENSORS_IN : IN STD_LOGIC_VECTOR(NUM_LANES * BUF_SIZE - 1 downto 0);

        -- NW (3), NE (2), SE (1), SW(0)
        BLOCKED_LED_OUT : OUT STD_LOGIC_VECTOR(NUM_LANES-1 downto 0) := x"0"
    );

end TrafficController;

architecture RTL of TrafficController is
    -- Data structure
    -- b0 < car Detected, b1-2 < road, b3-4 direction, b5-15 counter
    signal north_road_input : STD_LOGIC_VECTOR(BUF_SIZE-1 downto 0);
    signal east_road_input : STD_LOGIC_VECTOR(BUF_SIZE-1 downto 0);
    signal south_road_input : STD_LOGIC_VECTOR(BUF_SIZE-1 downto 0);
    signal west_road_input : STD_LOGIC_VECTOR(BUF_SIZE-1 downto 0);

    signal blocks_state : STD_LOGIC_VECTOR(NUM_LANES-1 downto 0);
    signal divided_clock : STD_LOGIC;
    signal next_release : STD_LOGIC_VECTOR(BUF_SIZE-1 downto 0) := X"0000";

    begin
        
        
        -- Sample the input during the rising edge of the divided clock
        sample_input : process(CLK_IN) is
            begin
                if rising_edge(CLK_IN) then:
                    north_road_input <= SENSORS_IN(BUF_SIZE-1 downto 0); -- 15 down to 0
                    east_road_input <= SENSORS_IN(BUF_SIZE*2-1 downto BUF_SIZE); -- 31 down to 16
                    south_road_input <= SENSORS_IN(BUF_SIZE*3-1 downto BUF_SIZE*2); -- 47 down to 32
                    west_road_input <= SENSORS_IN(BUF_SIZE*4-1 downto BUF_SIZE*3); -- 63 down to 48
                end if;
        end process;


        -- Check each input and decide which one to release
        to_release : process(CLK_IN) is
            variable to_release : std_logic_vector(BUF_SIZE-1 downto 0) := x"0000";
            variable task : boolean := False;
            
            begin
                if rising_edge(CLK_IN) then:
                    
                    if north_road_input(0) = '0' and
                        east_road_input(0) = '0' and
                        south_road_input(0) = '0' and
                        west_road_input(0) = '0' then
                            task := False;
                    else
                            task := True;
                    end if;
                        

                    if task then
                        
                        -- Set first value for comparison
                        if north_road_input(0) = '1' then
                            to_release := north_road_input;
                        elsif east_road_input(0) = '1' then
                            to_release := east_road_input;
                        elsif south_road_input(0) = '1' then
                            to_release := south_road_input;
                        elsif west_road_input(0) = '1' then
                            to_release := west_road_input;
                        end if;
                        
                        -- Compare with east
                        -- If east is earlier or priority is higher, replace with east
                        if east_road_input(0) = '1' then
                            if unsigned(to_release(BUF_SIZE-1 downto BUF_SIZE-11)) > unsigned(east_road_input(BUF_SIZE-1 downto BUF_SIZE-11)) or 
                            unsigned(to_release(BUF_SIZE-1 downto BUF_SIZE-11)) = unsigned(east_road_input(BUF_SIZE-1 downto BUF_SIZE-11)) and
                            unsigned(unsigned(to_release(4 downto 3)) > unsigned(east_road_input(4 downto 3))) then
                                to_release := east_road_input
                            end if;
                        end if;

                        -- Compare with south
                        -- If south is earlier or priority is higher, replace with south
                        if south_road_input(0) = '1' then
                            if unsigned(to_release(BUF_SIZE-1 downto BUF_SIZE-11)) > unsigned(south_road_input(BUF_SIZE-1 downto BUF_SIZE-11)) or 
                            unsigned(to_release(BUF_SIZE-1 downto BUF_SIZE-11)) = unsigned(south_road_input(BUF_SIZE-1 downto BUF_SIZE-11)) and
                            unsigned(unsigned(to_release(4 downto 3)) > unsigned(south_road_input(4 downto 3))) then
                                to_release := south_road_input
                            end if;
                        end if;

                        -- Compare with west
                        -- If west is earlier or priority is higher, replace with west
                        if west_road_input(0) = '1' then
                            if unsigned(to_release(BUF_SIZE-1 downto BUF_SIZE-11)) > unsigned(west_road_input(BUF_SIZE-1 downto BUF_SIZE-11)) or 
                            unsigned(to_release(BUF_SIZE-1 downto BUF_SIZE-11)) = unsigned(west_road_input(BUF_SIZE-1 downto BUF_SIZE-11)) and
                            unsigned(to_release(4 downto 3)) > unsigned(west_road_input(4 downto 3))# then
                                to_release := west_road_input
                            end if;
                        end if;

                    end if;

                end if;
                

        end process;

        -- Reserve block depending on direction
        reserve_block : process(CLK_IN) is
            variable temp : std_logic_vector(BUF_SIZE-1 downto 0) := x"0000";
            begin
                if rising_edge(CLK_IN) then
                    if not next_release = x"0000" then
                        temp := next_release
                        
                        -- case of different road
                        case temp(2 downto 1) is
                            
                            when NORTH =>
                                if temp(4 downto 3) = RIGHT then
                                    -- block NW
                                    BLOCKED_LED_OUT(3) <= '1';

                                elsif temp(4 downto 3) = STRAIGHT then
                                    -- block NW, SW
                                    BLOCKED_LED_OUT(3) <= '1';
                                    BLOCKED_LED_OUT(0) <= '1';

                                elsif temp(4 downto 3) = LEFT then
                                    -- block NW, SW, SE
                                    BLOCKED_LED_OUT(3) <= '1';
                                    BLOCKED_LED_OUT(1) <= '1';
                                    BLOCKED_LED_OUT(0) <= '1';
                                end if;
                                
                            when SOUTH =>
                                if temp(4 downto 3) = RIGHT then
                                    -- block SE
                                    BLOCKED_LED_OUT(1) <= '1';

                                elsif temp(4 downto 3) = STRAIGHT then
                                    -- block SE, NE
                                    BLOCKED_LED_OUT(2) <= '1';
                                    BLOCKED_LED_OUT(1) <= '1';
                                    
                                elsif temp(4 downto 3) = LEFT then
                                    -- block NW, NE, SE
                                    BLOCKED_LED_OUT(3) <= '1';
                                    BLOCKED_LED_OUT(2) <= '1';
                                    BLOCKED_LED_OUT(1) <= '1';
                                end if;
                            
                            when EAST =>
                                if temp(4 downto 3) = RIGHT then
                                    -- block NE
                                    BLOCKED_LED_OUT(2) <= '1';

                                elsif temp(4 downto 3) = STRAIGHT then
                                    -- block NW, NE
                                    BLOCKED_LED_OUT(3) <= '1';
                                    BLOCKED_LED_OUT(2) <= '1';
                                    
                                elsif temp(4 downto 3) = LEFT then
                                    -- block NW, NE, SW
                                    BLOCKED_LED_OUT(3) <= '1';
                                    BLOCKED_LED_OUT(2) <= '1';
                                    BLOCKED_LED_OUT(0) <= '1';
                                end if;

                            when WEST =>
                                if temp(4 downto 3) = RIGHT then
                                    -- block SW
                                    BLOCKED_LED_OUT(0) <= '1';

                                elsif temp(4 downto 3) = STRAIGHT then
                                    -- block SW, SE
                                    BLOCKED_LED_OUT(1) <= '1';
                                    BLOCKED_LED_OUT(0) <= '1';
                                    
                                elsif temp(4 downto 3) = LEFT then
                                    -- block NE, SW, SE
                                    BLOCKED_LED_OUT(2) <= '1';
                                    BLOCKED_LED_OUT(1) <= '1';
                                    BLOCKED_LED_OUT(0) <= '1';
                                end if;
                        end case;
                    end if;
                end if;
 
        end process;
end RTL;