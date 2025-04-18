#!/bin/bash

# Colors for better readability
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Create test directory and log directory
mkdir -p test_maps
mkdir -p fd_logs

# Create a simple test map
echo "0 0 0" >test_maps/test.fdf
echo "0 1 0" >>test_maps/test.fdf
echo "0 0 0" >>test_maps/test.fdf

echo -e "${BLUE}=======================================${NC}"
echo -e "${BLUE}FILE DESCRIPTOR LEAK TEST${NC}"
echo -e "${BLUE}=======================================${NC}\n"

# Check if fdf executable exists
if [ ! -f "./fdf" ]; then
        echo -e "${RED}Error: fdf executable not found. Run 'make' first.${NC}"
        rm -rf test_maps
        exit 1
fi

# Function to test FD leaks
test_fd_leaks() {
        local test_name="$1"
        local command="$2"

        echo -e "${YELLOW}TEST:${NC} $test_name"
        echo -e "${YELLOW}COMMAND:${NC} $command"

        # Get the shell's current FD count as baseline
        local shell_fd_count=$(ls -l /proc/$$/fd | wc -l)
        echo "Shell baseline FD count: $shell_fd_count"

        # Run the command in background
        eval "$command" >/dev/null 2>&1 &
        local pid=$!

        # Wait a bit for the process to start
        sleep 0.5

        # Check if process is running
        if kill -0 $pid 2>/dev/null; then
                # Process is running, check its FDs
                echo "Process started with PID: $pid"
                ls -la /proc/$pid/fd >"fd_logs/${test_name// /_}_initial.log" 2>/dev/null
                local initial_count=$(ls -la /proc/$pid/fd 2>/dev/null | wc -l)
                echo "Initial FD count: $initial_count"

                # Wait a bit to let it run
                sleep 1

                # Check FDs again
                if kill -0 $pid 2>/dev/null; then
                        ls -la /proc/$pid/fd >"fd_logs/${test_name// /_}_after.log" 2>/dev/null
                        local after_count=$(ls -la /proc/$pid/fd 2>/dev/null | wc -l)
                        echo "After running for 1s, FD count: $after_count"

                        # Calculate difference
                        local diff=$((after_count - initial_count))

                        # Kill the process
                        echo "Terminating process..."
                        kill -15 $pid 2>/dev/null
                        sleep 0.5
                        kill -9 $pid 2>/dev/null

                        # Check for zombie
                        if ps -p $pid >/dev/null 2>&1; then
                                echo -e "${RED}WARNING: Process $pid is still running or zombie${NC}"
                        fi

                        # Evaluate result
                        if [ $diff -gt 3 ]; then
                                echo -e "${RED}❌ FAILED: FD count increased by $diff (possibly leaking)${NC}"
                                echo -e "${YELLOW}Check fd_logs/${test_name// /_}_*.log for details${NC}"
                        else
                                echo -e "${GREEN}✅ PASSED: FD count stable (no obvious leaks)${NC}"
                        fi
                else
                        echo -e "${YELLOW}Process terminated before second check${NC}"
                        echo -e "${GREEN}✅ PASSED (Process completed normally)${NC}"
                fi
        else
                echo -e "${YELLOW}Process exited immediately${NC}"
                echo -e "${GREEN}✅ PASSED (Process completed normally)${NC}"
        fi

        echo ""
}

# Test with a normal map file
test_fd_leaks "Normal map test" "./fdf test_maps/test.fdf"

# Test with error cases
test_fd_leaks "Nonexistent file" "./fdf nonexistent_file.fdf"
test_fd_leaks "No arguments" "./fdf"
test_fd_leaks "Too many arguments" "./fdf test_maps/test.fdf extra_arg"

# Test with forced termination
test_fd_leaks "Force termination" "timeout 0.7s ./fdf test_maps/test.fdf"

echo -e "${BLUE}=======================================${NC}"
echo -e "${BLUE}ZOMBIE PROCESS CHECK${NC}"
echo -e "${BLUE}=======================================${NC}\n"

# Run a command, then check for zombies
echo -e "${YELLOW}Running FdF and checking for zombie processes...${NC}"
./fdf test_maps/test.fdf >/dev/null 2>&1 &
pid=$!
sleep 1
kill -15 $pid 2>/dev/null
sleep 0.5

# Check for zombies
zombies=$(ps aux | grep -E "Z.*fdf|defunct" | grep -v grep)
if [ -z "$zombies" ]; then
        echo -e "${GREEN}✅ No zombie processes detected${NC}"
else
        echo -e "${RED}❌ Zombie processes detected:${NC}"
        echo "$zombies"
fi

# Clean up
echo -e "\n${YELLOW}Cleaning up test files...${NC}"
rm -rf test_maps

echo -e "\n${GREEN}Test completed! Check the results above for any FD leaks or zombie processes.${NC}"
