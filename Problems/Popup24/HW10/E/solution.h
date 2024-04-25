/*
----------------------------------------------------- PROBLEM -----------------------------------------------------

There is a new cryptocurrency called SG coin. Alice purchases an item from Bob and pays in SG coin. The transaction is
recorded in a blockchain. A blockchain is a chain of blocks where each block contains the hash value of the previous
block, a transaction string, a token, and the hash value of the block (a positive integer with 7 trailing zeros).

Example: Suppose the hash value of the last block in the blockchain is 140 000 000 and the next transaction string to be
recorded is “alice-pays-bob-3-sg-coins”. The new block containing the transaction is appended (chained) to the last
block in the blockchain like this: \includegraphics[width=0.9\textwidth ]{example.png}

The token in the new block must be set to a number between 0 to 10^9 - 1 such that the hashValue of the new block is
positive and has 7 trailing zeros. If the token is 606 969 470 then the hashValue of the new block is computed as
follow:

H(140000000,"alice-pays-bob-3-sg-coins",606969470)=990000000

The function H is given below (in C++ and Java format only). There can be many other valid values for the token that
produces a valid hashValue (with 7 trailing zeros), e.g.,

H(140000000,"alice-pays-bob-3-sg-coins",306969470)=690000000

In a distributed system, a new block can be added to the blockchain by anyone and then broadcast to everyone. Everyone
will receive the new block and verify that it is valid (i.e., the last block’s hashValue, transaction string, and token
of the new block produces a hashValue with 7 trailing zeros). Everyone keeps track of the longest chain and only appends
a new block to the longest chain that they have.

Charlie has a lot of computing power and he sees an opportunity to attack the distributed blockchain system by
generating new blocks rapidly, thus producing the longest chain quickly. This allows him to monopolize new transactions
to be appended to the blockchain.

Let’s see an attack scenario. Alice pays Bob 3 SG coins for purchasing an item, she puts the transaction in the
blockchain and broadcasts. Bob sees the transaction in the blockchain and then gives the purchased item to Alice.
Charlie then comes in to disrupt this transaction by creating two consecutive new blocks and broadcasting. Everyone sees
the two new blocks from Charlie and keeps them, discarding the new block from Alice (which is shorter).

You are Charlie and you want to make life harder for Alice and Bob.

The hash function in C++:

long long H(long long previousHash, string &transaction,
            long long token) {
  long long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction[i]) % 1000000007;
  }
  return (v * 7 + token) % 1000000007;
}

The hash function in Java:

static long H(long previousHash, String transaction,
              long token) {
  long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction.charAt(i)) % 1000000007;
  }
  return (v * 7 + token) % 1000000007;
}

----------------------------------------------------- INPUT -----------------------------------------------------

The first line is the hashValue of the last block in the blockchain. The hashValue is between 0 to 1 000 000 006
inclusive and guaranteed to have 7 trailing zeros.

----------------------------------------------------- OUTPUT -----------------------------------------------------

Produce two new blocks A and B as fast as possible. A should be chained to the last block (from the given input) and B
should be chained to A. Print the transaction strings and the tokens of the two new blocks.

The first line contains the transaction string and the token for A separated by a space and the second line is for B.
The transaction string is non-empty and can be anything you want containing only lowercase English characters, digits
(0-9), or hyphen with at most 100 characters. The token must be an integer between 0 to 10^9 - 1.

----------------------------------------------------- EXAMPLE -----------------------------------------------------

Sample Input:
140000000

Sample Output:
charlie-pays-to-eve-9-sg-coins 218216710
icpc-sg-2018-at-nus 620658977

Explanation:
The last three blocks have hashValues of: 140 000 000 => 930 000 000 => 730 000 000.

----------------------------------------------------- SOLUTION -----------------------------------------------------

Notice that the hash function is not very secure in terms of preimage-resistance. The token is simply added in the end.
As such, we can produce an arbitrary string as message, get its hash value and choose the next highest number with 7
trailing zeroes as our target hash. We can get to that target hash by setting the token as target - old_hash.

The only thing that must be considered is that the token must be positive and the hash is modulo 1 000 000 007. As such
if we get the hash 1 000 000 006 for example as the hash with our arbitrary string, then the next highest one would be 1
010 000 000, but this is higher than the modulus. We can solve this by generating multiple arbitrary strings, one of
them should be fine.

*/

#include <stdexcept>
#include <string>

long long H(const long long &previousHash, const std::string &transaction, const long long &token)
{
    long long v = previousHash;
    for (int i = 0; i < transaction.length(); i++)
    {
        v = (v * 31 + transaction[i]) % 1000000007;
    }
    return (v * 7 + token) % 1000000007;
}

std::pair<long long, std::string> find_matching_transaction(const long long &previous_hash)
{
    std::string candidate_message = "";

    for (int i = 0; i < 100; i++)
    {
        candidate_message.push_back('a');
        long long h_value = H(previous_hash, candidate_message, 0);
        // this is the target hash value that we want to get
        long long next_highest = (h_value + 10000000 - (h_value % 10000000)) % 1000000007;

        // need positive token to get to the target hash value (as such it is feasible)
        if (h_value <= next_highest)
        {
            long long token = next_highest - h_value;
            return {next_highest, candidate_message + ' ' + std::to_string(token)};
        }
    }

    throw std::runtime_error("no valid transaction found!");
}

std::pair<std::string, std::string> solve_problem(const long long &previous_hash)
{
    std::pair<long long, std::string> first_block = find_matching_transaction(previous_hash);
    std::pair<long long, std::string> second_block = find_matching_transaction(first_block.first);

    return {first_block.second, second_block.second};
}