/*
2225. Find Players With Zero or One Losses

You are given an integer array matches where matches[i] = [winneri, loseri] indicates that the player winneri defeated player loseri in a match.

Return a list answer of size 2 where:
answer[0] is a list of all players that have not lost any matches.
answer[1] is a list of all players that have lost exactly one match.
The values in the two lists should be returned in increasing order.

Note:

You should only consider the players that have played at least one match.
The testcases will be generated such that no two matches will have the same outcome.
 

Example 1:

Input: matches = [[1,3],[2,3],[3,6],[5,6],[5,7],[4,5],[4,8],[4,9],[10,4],[10,9]]
Output: [[1,2,10],[4,5,7,8]]
Explanation:
Players 1, 2, and 10 have not lost any matches.
Players 4, 5, 7, and 8 each have lost one match.
Players 3, 6, and 9 each have lost two matches.
Thus, answer[0] = [1,2,10] and answer[1] = [4,5,7,8].
Example 2:

Input: matches = [[2,3],[1,3],[5,4],[6,4]]
Output: [[1,2,5,6],[]]
Explanation:
Players 1, 2, 5, and 6 have not lost any matches.
Players 3 and 4 each have lost two matches.
Thus, answer[0] = [1,2,5,6] and answer[1] = [].

Constraints:

1 <= matches.length <= 10^5
matches[i].length == 2
1 <= winneri, loseri <= 10^5
winneri != loseri
All matches[i] are unique.

Solution : Just store player id to player stats - wins and loses in a map and iterate over the map to find the players with 0 and 1 losses. Note storing only the
losses doesn't work because if we store only the losses, then those players who have never participated in any match, will get accounted as well.

Time & Space Complexity : O(n). HashMap lookup is O(1)
*/

class Solution {
    class stats {
        int id;
        int wins;
        int loss;
    }
    public List<List<Integer>> findWinners(int[][] matches) {
        Map<Integer, stats> playerStats = new HashMap<>();
        
        for (int[] match : matches) {
            stats winnerStats = playerStats.getOrDefault(match[0], new stats());
            winnerStats.id = match[0];
            winnerStats.wins++;
            playerStats.put(match[0], winnerStats);
            stats loserStats = playerStats.getOrDefault(match[1], new stats());
            loserStats.loss++;
            loserStats.id = match[1];
            playerStats.put(match[1], loserStats);
        }
        List<Integer> oneLoss   = new ArrayList<>();
        List<Integer> zeroLoss  = new ArrayList<>();
        List<List<Integer>> res = new ArrayList<>();
        for (stats each : playerStats.values()) {
            if (each.loss == 1) {
                oneLoss.add(each.id);
            } else if (each.loss == 0) {
                zeroLoss.add(each.id);
            }
        }
        Collections.sort(oneLoss);
        Collections.sort(zeroLoss);
        res.add(zeroLoss);
        res.add(oneLoss);
        return res;
    }
}
