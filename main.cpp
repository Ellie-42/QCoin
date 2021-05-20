#include <iostream>
#include <memory>
#include "blockChain.h"
#include <json/json.h>
#include <chrono>

int main()
{
    std::cout<<"Compiled!"<<std::endl;

    blockChain testNet;

    std::shared_ptr<block> genBlockTest = testNet.getBlockAtIndex(0);

    std::cout<<"Genesis Block\n"<<"-------------------"<<std::endl;
    std::cout<<*genBlockTest;
    std::cout<<"Combined data:   " << genBlockTest->combineTxData()<<std::endl;
    std::cout<<"\n-------------------\n"<<std::endl;

    std::cout<<"JSON Testing on: " << "Genesis Block" <<std::endl;

    Json::Value testData = genBlockTest->toJson();
    std::shared_ptr<block> testBlockClone(new block(testData));

    std::cout<<"\nLoad from JSON test:"<<std::endl;

    std::cout<<*testBlockClone;
    std::cout<<"Combined data:   " << testBlockClone->combineTxData()<<std::endl;

    std::cout<<"\n-------------------\n"<<std::endl;

    std::vector<std::string> transData;

    transData.push_back("This should be jsonified transaction data");
    std::cout<<"Made some data."<<std::endl;

    std::shared_ptr<block> blockTest=std::shared_ptr<block>(new block(1, genBlockTest->getCurHash(), std::time(nullptr), transData, 0));
    mineAlgo miner(blockTest);

    std::cout<<"Mining algo made."<<std::endl;

    std::cout<<"Data!"<<std::endl;

    miner.setBlockData(miner.mine());

    std::cout<<"Block? Mined."<<std::endl;

    if(testNet.addBlock(blockTest)==0)
    {
        std::cout<<"The addition of a new block has been successful.\nRaising the difficulty."<<std::endl;
    }
    else
    {
        std::cout<<"The new block did not validate. Exiting..."<<std::endl;
        return -404;
    }
    char emp;
    std::cin>>emp;
    transData.push_back("But is it? No.");
    std::shared_ptr<block> blockTest2 = std::shared_ptr<block>(new block(2,blockTest->getCurHash(), std::time(nullptr),transData,5));
    miner.setCurBlock(blockTest2);
    miner.setBlockData(miner.mine());
    if(testNet.addBlock(blockTest2)==0)
    {
        std::cout<<"The addition of the second new block has been successful.\nRaising the difficulty."<<std::endl;
    }
    else
    {
        std::cout<<"The second new block did not validate. Exiting..."<<std::endl;
        return -405;
    }

    std::shared_ptr<block> blockTest3 = std::shared_ptr<block>(new block(3,blockTest2->getCurHash(), std::time(nullptr),transData,7));
    miner.setCurBlock(blockTest3);
    miner.setBlockData(miner.mine());
    if(testNet.addBlock(blockTest3)==0)
    {
        std::cout<<"The addition of the thirds new block has been successful.\nRaising the difficulty."<<std::endl;
    }
    else
    {
        std::cout<<"The thirds new block did not validate. Exiting..."<<std::endl;
        return -405;
    }

    std::cout<<"The block chain test has been successful. Good job.\nNow finish the transaction flow, compression, and the network."<<std::endl;

    return 0;
}
