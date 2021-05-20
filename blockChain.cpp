#include "blockChain.h"
#include "mineAlgo.h"
#include <memory>
#include <botan/hash.h>
#include <botan/base58.h>
#include <botan/secmem.h>
#include <iostream>

blockChain::blockChain()
{
    genesisBlock = std::shared_ptr<block>(new block(0,"933ec8bc34e21924fa75f560edc22df1d1c",0,std::vector<std::string>(),0));
    mining = mineAlgo(genesisBlock);
    std::cout<<"Test1"<<std::endl;
    mining.setBlockData(mining.hashGen(genNonce));
    std::cout<<"Test2"<<std::endl;
    this->chain.push_back(genesisBlock);
}

bool blockChain::validateBlock(std::shared_ptr<block> prevBlock, std::shared_ptr<block> curBlock)
{
    if(curBlock->getIndex() == 0)
    {
        return true;
        std::cout<<"Its the initial block!"<<std::endl;
    }

    std::string r1 = mineAlgo::round_01[mineAlgo::numbList[curBlock->getIndex()]];
    std::string r2 = mineAlgo::round_02[mineAlgo::numbList[mineAlgo::findBase58Val(curBlock->getPrevHash().back())]];
    std::string r3 = mineAlgo::round_03;

    std::unique_ptr<Botan::HashFunction> hash_01(Botan::HashFunction::create(r1));
    std::unique_ptr<Botan::HashFunction> hash_02(Botan::HashFunction::create(r2));
    std::unique_ptr<Botan::HashFunction> hash_03(Botan::HashFunction::create(r3));

    mineAlgo prevBlockAlgo(prevBlock);
    mineAlgo curBlockAlgo(curBlock);
    if(curBlock->getPrevHash() !=  prevBlock->getCurHash())
    {
        return false;
    }

    std::string combData = curBlock->digest(curBlock->nonce);

    Botan::secure_vector<uint8_t> hashData;
    hash_01->update(combData);
    hash_01->final(hashData);
    hash_02->update(hashData);
    hash_02->final(hashData);
    hash_03->update(hashData);
    hash_03->final(hashData);
    std::string checkDat = Botan::base58_encode(hashData);

    if(checkDat == curBlock->getCurHash())
    {
        return true;
    }
    return false;
}

int8_t blockChain::diffAdjust()
{
    if(chain.size() % 10 != 0){return 0;}
    std::shared_ptr<block> lastBlock = chain.back();
    std::shared_ptr<block> oldBlock = chain.at(chain.size() - 11);
    if((lastBlock->getTimestamp() - oldBlock->getTimestamp()) > block_gen_interval * block_adj_interval)
    {
        return 1;
    }
    else if((lastBlock->getTimestamp() - oldBlock->getTimestamp()) < block_gen_interval * block_adj_interval)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int blockChain::addBlock(std::shared_ptr<block> newBlock)
{
    std::shared_ptr<block> lastBlock = chain.at(newBlock->getIndex()-1);
    std::cout<<"\n\nCurrent block data: " << *newBlock;
    std::cout<<"\n\nValidating...\nPrevious block data: \n" << *lastBlock;
    if(validateBlock(lastBlock,newBlock))
    {
        chain.push_back(newBlock);
        return 0;
    }
    else
    {
        return -1;
    }
}
