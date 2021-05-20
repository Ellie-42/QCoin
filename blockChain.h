#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "block.h"
#include "mineAlgo.h"
#include <vector>

const int block_gen_interval = 60;
const int block_adj_interval = 5;
const int genNonce = 1231;

class blockChain
{
    public:

        blockChain();
        int addBlock(std::shared_ptr<block> newBlock); //made this an int to permit addition of error codes later

        std::vector<std::shared_ptr<block>> getChain(){return chain;}
        unsigned int getChainLength(){return chain.size();};

        bool validateBlock(std::shared_ptr<block> prevBlock, std::shared_ptr<block> curBlock);

        std::shared_ptr<block> getBlockAtIndex(unsigned int i){return chain.at(i);}

        int8_t diffAdjust();




    protected:
        std::vector<std::shared_ptr<block>> chain;

    private:
        std::shared_ptr<block> genesisBlock;
        mineAlgo mining;
};

#endif // BLOCKCHAIN_H
