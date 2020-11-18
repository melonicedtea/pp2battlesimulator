#include "Grid.h"
#include "precomp.h"

namespace Tmpl8
{
mutex m;

Grid::Grid()
{
    // Fill grid with empty vectors.
    for (int y = 0; y < NUM_CELLS; y++)
    {
        vector<vector<Tank*>> vector_tank_ptrs;
       
        for (int x = 0; x < NUM_CELLS; x++)
        {
            vector<Tank*> tankptrs;
            vector_tank_ptrs.emplace_back(tankptrs);
        }
        cells.emplace_back(vector_tank_ptrs);
    }
};
//Grid::~Grid(){};

void Grid::add(Tank* tank)
{
    // Determine which grid cell it's in.
    int cellX = (int)(tank->position.x / (float)Grid::CELL_SIZE);
    int cellY = (int)(tank->position.y / (float)Grid::CELL_SIZE);

    //// Add to the list for the cell it's in.
    cells[cellX][cellY].emplace_back(tank);
}

void Grid::handleCollisions()
{
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            handleCell(x, y);
        }
    }
}

void Grid::handleCell(int x, int y)
{
    //Handle current unit
    //vector<Tank*> current = cells[x][y];
    handleUnit(cells[x][y], cells[x][y]);

    // Also try the neighboring cells.
    if (x > 0 && y > 0) handleUnit(cells[x][y], cells[x - 1][y - 1]);
    if (x > 0) handleUnit(cells[x][y], cells[x - 1][y]);
    if (y > 0) handleUnit(cells[x][y], cells[x][y - 1]);
    if (x > 0 && y < NUM_CELLS - 1)
    {
        handleUnit(cells[x][y], cells[x - 1][y + 1]);
    }
}

void Grid::handleUnit(vector<Tank*> &tank_ptrs, vector<Tank*> &oTank_ptrs)
{
    for (Tank* tank : tank_ptrs)
    {
        if (tank->active)
        {
            for (Tank* oTank : oTank_ptrs)
            {
                if (tank == oTank) continue;

                vec2 dir = tank->Get_Position() - oTank->Get_Position();
                float dirSquaredLen = dir.sqrLength();

                float colSquaredLen = (tank->Get_collision_radius() * tank->Get_collision_radius()) + (oTank->Get_collision_radius() * oTank->Get_collision_radius());

                if (dirSquaredLen < colSquaredLen)
                {
                    tank->Push(dir.normalized(), 1.f);
                }
            }
        }
    }
}

void Grid::move(Tank* tank)
{
    // after every tick check position
    // See which cell it was in.
    int oldCellX = (int)(tank->old_position.x / (float)Grid::CELL_SIZE);
    int oldCellY = (int)(tank->old_position.y / (float)Grid::CELL_SIZE);

    // See which cell it's moving to.
    int cellX = (int)(tank->position.x / (float)Grid::CELL_SIZE);
    int cellY = (int)(tank->position.y / (float)Grid::CELL_SIZE);

    // If it didn't change cells, we're done.
    if (oldCellX == cellX && oldCellY == cellY) return;

    // erase from old cell
    cells[oldCellX][oldCellY].erase(std::remove/*_if*/(cells[oldCellX][oldCellY].begin(), cells[oldCellX][oldCellY].end(), tank/*[tank](const Tank* otank) { return tank == otank; }*/), cells[oldCellX][oldCellY].end());
    // Add it back to the grid at its new cell.
    add(tank);
}

} // namespace Tmpl8