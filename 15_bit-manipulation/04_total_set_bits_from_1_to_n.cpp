/*

link: https://practice.geeksforgeeks.org/problems/count-total-set-bits-1587115620/1
sol: https://www.geeksforgeeks.org/count-total-set-bits-in-all-numbers-from-1-to-n/
video: https://www.youtube.com/watch?v=g6OxU-hRGtY

to find set bits: __builtin_popcount(N);

*/

// ----------------------------------------------------------------------------------------------------------------------- //

int total_popcount(int n) {
    int count = 0;
    while (n) {
        if (n & 1) count++;
        n >>= 1;
    }
    return count;
}

// ----------------------------------------------------------------------------------------------------------------------- //

// method 1
// TC: O(N)
int countSetBits(int n)
{
    int count = 0;
    for (int i = 1;i <= n;i++) {
        count += total_popcount(i);
    }
    return count;
}

// ----------------------------------------------------------------------------------------------------------------------- //

// method 2
// TC: O(N log N);
int countSetBits(int n) {
    int i = 0;  // for bit position from least to most significant

    int ans = 0;

    while ((1 << i) <= n) {
        bool k = 0; // temp bit status, will change after certain pos
        int change = 1 << i;
        /* for eg. if bit pos is 0 then it will change alternative and if bit pos is 1 then will change after every 2 occurences. */

        for (int j = 0;j <= n;j++) {
            ans += k;   // save temp bit to ans
            if (change == 1) {
                k = !k;
                change = 1 << i;
            }
            else {
                change--;
            }
        }
        i++;
    }
    return ans;
}

// ----------------------------------------------------------------------------------------------------------------------- //

// method 3 most optimal
// TC: O(log(N))
// refer: onenote for 
int findPower(int n) {
    int count = 0;
    while ((1 << count) <= n) {
        count++;
    }
    return count - 1;
}
int countSetBits(int n)
{
    if (n == 0) {
        return 0;
    }

    int max_pow_of_2 = findPower(n); // or can use log2(n) instead of self made function.
    int till_pow_of_2 = max_pow_of_2 * (1 << (max_pow_of_2 - 1));

    int extra_line_of_bit = n - (1 << max_pow_of_2) + 1;

    return till_pow_of_2 + extra_line_of_bit + countSetBits(n - (1 << max_pow_of_2));
}


int countSetBits(int n)
{

    // Ignore 0 as all the bits are unset
    n++;

    // To store the powers of 2
    int powerOf2 = 2;

    // To store the result, it is initialized
    // with n/2 because the count of set
    // least significant bits in the integers
    // from 1 to n is n/2
    int cnt = n / 2;

    // Loop for every bit required to represent n
    while (powerOf2 <= n) {

        // Total count of pairs of 0s and 1s
        int totalPairs = n / powerOf2;

        // totalPairs/2 gives the complete
        // count of the pairs of 1s
        // Multiplying it with the current power
        // of 2 will give the count of
        // 1s in the current bit
        cnt += (totalPairs / 2) * powerOf2;

        // If the count of pairs was odd then
        // add the remaining 1s which could
        // not be groupped together
        cnt += (totalPairs & 1) ? (n % powerOf2) : 0;

        // Next power of 2
        powerOf2 <<= 1;
    }

    // Return the result
    return cnt;
}

// ----------------------------------------------------------------------------------------------------------------------- //
