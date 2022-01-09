/*
On an infinite plane, a robot initially stands at (0, 0) and faces north. The robot can receive one of three instructions:

"G": go straight 1 unit;
"L": turn 90 degrees to the left;
"R": turn 90 degrees to the right.
The robot performs the instructions given in order, and repeats them forever.

Return true if and only if there exists a circle in the plane such that the robot never leaves the circle.

Example 1:

Input: instructions = "GGLLGG"
Output: true
Explanation: The robot moves from (0,0) to (0,2), turns 180 degrees, and then returns to (0,0).
When repeating these instructions, the robot remains in the circle of radius 2 centered at the origin.
Example 2:

Input: instructions = "GG"
Output: false
Explanation: The robot moves north indefinitely.
Example 3:

Input: instructions = "GL"
Output: true
Explanation: The robot moves from (0, 0) -> (0, 1) -> (-1, 1) -> (-1, 0) -> (0, 0) -> ...

Constraints:

1 <= instructions.length <= 100
instructions[i] is 'G', 'L' or, 'R'.

Hint - 1 : Calculate the final vector of how the robot travels after executing all instructions once - it consists of a change in position plus a change in direction.
Hint - 2 : The robot stays in the circle if and only if (looking at the final vector) it changes direction (ie. doesn't stay pointing north), or it moves 0.

Solution : Just like the hint says : Check if final position of the robot after following the instruction is 0,0 or if it has changed it's direction i.e. final
direction it is facing is not North.
*/

class Solution {
public:
    bool isRobotBounded(string instructions) {
        char dir = 'N';
        int x = 0, y = 0;
        
        for (auto c : instructions) {
            switch (c) {
                case 'G':
                    if (dir == 'N') {
                        y++;
                    } else if (dir == 'S') {
                        y--;
                    } else if (dir == 'E') {
                        x++;
                    } else {
                        x--;
                    }
                    break;
                case 'L':
                    if (dir == 'N') {
                        dir = 'W';
                        //cout<<"Moving "<<dir<<endl;
                    } else if (dir == 'E') {
                        dir = 'N';
                        //cout<<"Moving "<<dir<<endl;
                    } else if (dir == 'S') {
                        dir = 'E';
                        //cout<<"Moving "<<dir<<endl;
                    } else {
                        dir = 'S';
                        //cout<<"Moving "<<dir<<endl;
                    }
                    break;
                case 'R':
                    if (dir == 'N') {
                        dir = 'E';
                        //cout<<"Moving "<<dir<<endl;
                    } else if (dir == 'E') {
                        dir = 'S';
                        //cout<<"Moving "<<dir<<endl;
                    } else if (dir == 'S') {
                        dir = 'W';
                        //cout<<"Moving "<<dir<<endl;
                    } else {
                        dir = 'N';
                        //cout<<"Moving "<<dir<<endl;
                    }
                    break;
            }
        }
        cout<<"Final vector : "<<x<<" "<<y<<" "<<dir<<endl;
        if (dir != 'N' || (x == 0 && y == 0))
            return true;
        return false;
    }
};
