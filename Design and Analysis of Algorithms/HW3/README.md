# HW 3

## Project Overview
This program solves the following algorithmic problems:

1. **Find the Heavier Coin Among Nine Coins** with only two weighings using a balance scale.
2. **Find the Heavier Coin in a Set of n Coins** where `n` is a power of 3, using at most `log₃(n)` weighings.
3. **Search for a Value in a 2D Sorted Matrix** using a divide-and-conquer approach.

---

## Problems and Solutions

### Problem 1: Identify the Heavier Coin Among Nine Coins
#### Problem Description
- Nine coins are identical in appearance, but one coin is heavier.
- You are allowed **two weighings** on a balance scale to determine the heavier coin.

#### Approach:
- Divide the coins into three groups of three coins each.
- Compare the weights of the first two groups:
  - If one group is heavier, the heavier coin is in that group.
  - If the groups are equal, the heavier coin is in the third group.
- Within the heavier group, compare individual coins to identify the heavier one.

#### Example Usage:
```
int[] coins = new int[]{ 0, 0, 0, 0, 0, 0, 0, 1, 0 };
System.out.println("The fake coin is the one numbered: " + sort1(coins));
```

---

### Problem 2: Find the Heavier Coin Among n Coins
#### Problem Description
- A set of `n` coins (where `n` is a power of 3) contains one heavier coin.
- You are allowed at most `log₃(n)` weighings to determine the heavier coin.

#### Approach:
- Divide the coins into three equal groups.
- Compare the weights of the first two groups:
  - If one group is heavier, the heavier coin is in that group.
  - If the groups are equal, the heavier coin is in the third group.
- Recursively apply the same logic to the group with the heavier coin until the group size is 1.

#### Example Usage:
```
int[] coins1 = new int[]{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 };
System.out.println("The fake coin is the one numbered: " + sort2(coins1, 0, 11));
```

---

### Problem 3: Search for a Value in a 2D Sorted Matrix
#### Problem Description
- You are given a 2D matrix where each row and column is sorted in ascending order.
- Write an algorithm to determine if a target value exists in the matrix.

#### Approach:
- Use a divide-and-conquer technique:
  - Start with the middle of the matrix.
  - If the middle value equals the target, return `true`.
  - If the middle value is less than the target:
    - Search the bottom-left, bottom-right, and top-right sections of the matrix.
  - If the middle value is greater than the target:
    - Search the top-left, bottom-left, and top-right sections of the matrix.
- Repeat until the value is found or no search space remains.

#### Example Usage:
```
int[][] testArray = new int[10][10];
for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
        testArray[i][j] = (i * 10) + j;
    }
}
if (searchValue(testArray, 870, 0, 0, 9, 9)) {
    System.out.println("Found");
} else {
    System.out.println("Not Found");
}
```
