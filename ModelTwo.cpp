#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <cstdlib>

void clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

// Function to print the grid with dots
void printGrid(const std::vector<std::vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 0) {
                std::cout << ". ";  // Healthy cell
            } else {
                std::cout << "o ";  // Cancer cell
            }
        }
        std::cout << std::endl;
    }
}

// Function to generate random cancer cells
void generateCancerCells(std::vector<std::vector<int>>& grid, int numCancerCells) {
    int rows = grid.size();
    int cols = grid[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, rows * cols - 1);

    for (int i = 0; i < numCancerCells; i++) {
        int randomIndex = dis(gen);
        int row = randomIndex / cols;
        int col = randomIndex % cols;
        grid[row][col] = 1; // Set the cell as a cancer cell
    }
}

// Function to spread cancer cells to neighboring healthy cells
void spreadCancerCells(std::vector<std::vector<int>>& grid, double spreadProbability) {
    int rows = grid.size();
    int cols = grid[0].size();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);

    std::vector<std::vector<int>> newGrid = grid; // Copy of the grid to apply changes after the iteration

    // Iterate over each cell in the grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Check if the current cell is a cancer cell
            if (grid[i][j] == 1) {
                // Spread cancer cells to neighboring healthy cells
                if (i > 0 && grid[i - 1][j] == 0 && dis(gen) < spreadProbability) {
                    newGrid[i - 1][j] = 1;
                }
                if (i < rows - 1 && grid[i + 1][j] == 0 && dis(gen) < spreadProbability) {
                    newGrid[i + 1][j] = 1;
                }
                if (j > 0 && grid[i][j - 1] == 0 && dis(gen) < spreadProbability) {
                    newGrid[i][j - 1] = 1;
                }
                if (j < cols - 1 && grid[i][j + 1] == 0 && dis(gen) < spreadProbability) {
                    newGrid[i][j + 1] = 1;
                }
            }
        }
    }

    grid = newGrid; // Update the original grid with the spread cancer cells
}

// Main function with animation
int main() {
    const int rows = 10;
    const int cols = 10;
    const int numIterations = 20; // Number of frames in the animation
    const double spreadProbability = 0.5; // Probability that a cancer cell spreads to a neighboring cell

    // Create the grid
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));

    // Generate initial random cancer cells
    generateCancerCells(grid, 10);

    // Animation loop
    for (int t = 0; t < numIterations; t++) {
        clearScreen(); // Clear the screen

        // Print the current state of the grid
        printGrid(grid);

        // Spread cancer cells
        spreadCancerCells(grid, spreadProbability);

        // Pause to create the animation effect
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    }

    return 0;
}
