#include "GamePCH.h"
#include <assert.h>
#include <float.h>
#include <math.h>

#include "Tilemap/Tilemap.h"
#include "Pathfinder.h"

Pathfinder::Pathfinder(Tilemap* pTilemap, int width, int height)
{
    m_pTilemap = pTilemap;

    m_NumNodes = width * height;

    m_Nodes = new PathNode[m_NumNodes];
    m_OpenNodes = new int[m_NumNodes];

    m_MapWidth = width;
    m_MapHeight = height;

    Reset();
}

Pathfinder::~Pathfinder()
{
    delete[] m_Nodes;
    delete[] m_OpenNodes;
}

void Pathfinder::Reset()
{
    m_NumOpen = 0;

    for (int i = 0; i < m_NumNodes; i++)
    {
        m_Nodes[i].parentNodeIndex = -1;
        m_Nodes[i].status = PathNode::Unchecked;

        m_Nodes[i].f = 0;
        m_Nodes[i].g = FLT_MAX; // Set G to be highest cost possible, so any comparison will be better.
        m_Nodes[i].h = -1; // -1 indicates the heuristic hasn't been calculated yet.
    }
}

bool Pathfinder::FindPath(int sx, int sy, int ex, int ey)
{
    // Reset the pathfinder.
    Reset();

    // Get the starting tile index and the destination tile index.
    int startIndex = CalculateNodeIndex(sx, sy);
    int endIndex = CalculateNodeIndex(ex, ey);

    // Set starting node cost to zero, then add it to the open list to start the process.
    m_Nodes[startIndex].g = 0;
    AddToOpen(startIndex);
    while (true)
    {
        // Find the lowest F and remove it from the open list.
        int lowestFNode = FindNodeIndexWithLowestFInOpen();
        RemoveFromOpen(lowestFNode);
        // If we found the end node, we're done.
        if (lowestFNode == endIndex)
        {
            return true;
        }
        // Mark the node as closed.
        m_Nodes[lowestFNode].status = PathNode::Closed;
        // Add neighbours to open list.
        AddNeighboursToOpenList(lowestFNode, endIndex);
        // If we're out of nodes to check, then we're done without finding the end node.
        if (m_NumOpen == 0)
            return false;
    }

    // This shouldn't happen, we should either find the destination or run out of nodes in the open list.
    assert(false);
    return false;
}

int Pathfinder::GetPath(int* path, int maxdistance, int ex, int ey)
{
    int nodeIndex = CalculateNodeIndex(ex, ey);

    int length = 0;
    while (true)
    {
        if (path != nullptr && length >= maxdistance)
            return -1; // Path didn't fit in size.

        if (path != nullptr) // If no path array is passed in, just get the length.
            path[length] = nodeIndex;
        length++;

        nodeIndex = m_Nodes[nodeIndex].parentNodeIndex;

        if (nodeIndex == -1)
            return length;
    }

    // There should be no way to get here.
    assert(false);
    return -1;
}

void Pathfinder::AddToOpen(int nodeindex)
{
    assert(m_Nodes[nodeindex].status != PathNode::Closed);

    // If the node isn't already open, then add it to the list.
    if (m_Nodes[nodeindex].status != PathNode::Open)
    {
        m_OpenNodes[m_NumOpen] = nodeindex;
        m_NumOpen++;
        m_Nodes[nodeindex].status = PathNode::Open;
    }
}

void Pathfinder::RemoveFromOpen(int nodeindex)
{
    // Remove the node from the open list, since we don't care about order, replace the node we're removing with the last node in list.
    for (int i = 0; i < m_NumOpen; i++)
    {
        if (m_OpenNodes[i] == nodeindex)
        {
            m_NumOpen--;
            m_OpenNodes[i] = m_OpenNodes[m_NumOpen];
            return;
        }
    }
}

int Pathfinder::FindNodeIndexWithLowestFInOpen()
{
    // Loop through the nodes in the open list, then find and return the node with the lowest F score.
    int lowestNode = -1;
    int lowestF = 99999999;
    for (int i = 0; i < m_NumOpen; i++)
    {

        if (m_Nodes[m_OpenNodes[i]].f < lowestF)
        {
            lowestF = (int)m_Nodes[m_OpenNodes[i]].f;
            lowestNode = m_OpenNodes[i];
        }


    }
    return lowestNode;
}

int Pathfinder::CalculateNodeIndex(int tx, int ty)
{
    /*   assert(tx >= 0 && tx < m_MapWidth &&
           ty >= 0 && ty < m_MapHeight);*/
    int nodeIndex = ty * m_MapWidth + tx;
    // Calculate the node index based on the tiles x/y.
    return nodeIndex; // PLACEHOLDER: to allow code to compile until method is implemented
}

int Pathfinder::CheckIfNodeIsClearAndReturnNodeIndex(int tx, int ty)
{
    //int clearNode = CalculateNodeIndex(tx, ty);
    // If the node is out of bounds, return -1 (an invalid tile index).
    if (tx < 0 || tx > m_MapWidth || ty > m_MapHeight || ty < 0)
    {
        return -1;
    }
    // If the node is already closed, return -1 (an invalid tile index).
    if (m_Nodes[CalculateNodeIndex(tx, ty)].status == PathNode::Closed)
    {
        return -1;
    }
    // If the node can't be walked on, return -1 (an invalid tile index).
    bool isTileWalkable = m_pTilemap->IsTileWalkableAtTilePos(tx, ty);
    if (isTileWalkable == false)
    {
        return -1;
    }
    // Return a valid tile index.
    return CalculateNodeIndex(tx, ty); // PLACEHOLDER: to allow code to compile until method is implemented
}

void Pathfinder::AddNeighboursToOpenList(int nodeIndex, int endNodeIndex)
{
    // Calculate the tile x/y based on the nodeIndex.
    int nodeX = nodeIndex % m_MapWidth;
    int nodeY = nodeIndex / m_MapWidth;
    // Fill an array with the four neighbour tile indices. (use CheckIfNodeIsClearAndReturnNodeIndex() for each to see if it's valid).
    int nodestoadd[4] = { nodeIndex + m_MapWidth, nodeIndex + 1, nodeIndex - m_MapWidth, nodeIndex - 1 };


    // Loop through the array.
    for (int i = 0; i < 4; i++)
    {
        // Check if the node to add has a valid node index.
        int validNode;
        if (i == 0) // north neighbor
        {
            validNode = CheckIfNodeIsClearAndReturnNodeIndex(nodeX, nodeY + 1);
        }
        else if (i == 1) // east neighbor
        {
            validNode = CheckIfNodeIsClearAndReturnNodeIndex(nodeX + 1, nodeY);
        }
        else if (i == 2) // south neighbor
        {
            validNode = CheckIfNodeIsClearAndReturnNodeIndex(nodeX, nodeY - 1);
        }

        else if (i == 3) // west neighbor
        {
            validNode = CheckIfNodeIsClearAndReturnNodeIndex(nodeX - 1, nodeY);
        }

        if (validNode != -1)
        {
            int cost = 1; // Assume a travel cost of 1 for each tile.

            // Add the node to the open list.
            AddToOpen(nodestoadd[i]);
            // If the cost to get there from here (new G) is less than the previous cost (old G) to get there, then overwrite the values.
            float newG = m_Nodes[nodeIndex].g + cost;
            float oldG = m_Nodes[nodestoadd[i]].g;
            if (newG < oldG)
            {
                // Set the parent node.
                m_Nodes[nodestoadd[i]].parentNodeIndex = nodeIndex;
                // Set the new cost to travel to that node.
                m_Nodes[nodestoadd[i]].g = newG;
                // If we haven't already calculated the heuristic, calculate it.
                float newH = CalculateH(nodestoadd[i], endNodeIndex);
                m_Nodes[nodestoadd[i]].h = newH;
                // Calculate the final value.
                int newF = int(newG + newH);
                m_Nodes[nodestoadd[i]].f = (float)newF;
            }
        }
    }
}

float Pathfinder::CalculateH(int nodeIndex1, int nodeIndex2)
{
    // Calculate the h score using the Manhatten distance (absolute diff in x + absolute diff in y).
    int nodeX1 = nodeIndex1 & m_MapWidth;
    int nodeY1 = nodeIndex1 / m_MapWidth;
    int nodeX2 = nodeIndex2 & m_MapWidth;
    int nodeY2 = nodeIndex2 / m_MapWidth;
    int valueH = abs(nodeX1 - nodeX2) + abs(nodeY1 - nodeY2);
    return (float)valueH; // PLACEHOLDER: to allow code to compile until method is implemented
}
