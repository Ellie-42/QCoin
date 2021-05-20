#include "mineAlgo.h"
#include "block.h"
#include <memory>
#include <iostream>
#include <string>
#include <botan/hash.h>
#include <botan/base58.h>
#include <botan/hex.h>
#include <botan/rng.h>
#include <botan/auto_rng.h>
#include <chrono>
#include <bitset>

mineAlgo::mineAlgo(std::shared_ptr<block> blockData)
{
    this->blockData = blockData;
    this->blockTxData = blockData->combineTxData();
}

mineAlgo::mineAlgo(const mineAlgo &cpy)
{
    blockData = cpy.blockData;
    blockTxData = cpy.blockTxData;
}

mineAlgo::mineAlgo()
{

}

void mineAlgo::setBlockData(miningData data)
{
    std::cout<<"Setting values."<<std::endl;
    blockData->setCurHash(data.hashData);
    blockData->nonce = data.nonce;
    std::cout<<"Vals set."<<std::endl;
}

miningData mineAlgo::mine()
{
    std::cout<<"Digging the mine."<<std::endl;


    //std::cout<<"Mine initiated."<<std::endl;
    std::unique_ptr<Botan::RandomNumberGenerator> rng;
    rng.reset(new Botan::AutoSeeded_RNG);
    uint8_t bytes[4];

    miningData mDat;
    bool found = false;
    while(!found)
    {
        rng->randomize(bytes,4);
        int nonce;
        nonce = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24);
        mDat = hashGen(nonce);
        uint8_t curDiff = blockData->getDiff();
        std::string diffComp = "";
        for(uint8_t ui = 0; ui < curDiff; ui++){diffComp+="0";}
        if(mDat.hashBits.substr(0,curDiff) == diffComp)
        {
            found = true;
        }
        std::cout<<"Compared."<<std::endl;
    }
    std::cout<<"Return data. Hash: "<<mDat.hashData << "\nNonce: "<<mDat.nonce<<std::endl;

    return mDat;
}

miningData mineAlgo::hashGen(int nonce01)
{
    std::string r1 = round_01[numbList[std::to_string(blockData->getIndex()).back()]];
    std::string r2 = round_02[numbList[findBase58Val(blockData->getPrevHash().back())]];
    std::string r3 = round_03;

    std::cout<<"Hash 1 name: " << r1 << std::endl;
    std::cout<<"Hash 2 name: " << r2 << std::endl;

    std::unique_ptr<Botan::HashFunction> hash_01(Botan::HashFunction::create(r1));
    std::unique_ptr<Botan::HashFunction> hash_02(Botan::HashFunction::create(r2));//
    std::unique_ptr<Botan::HashFunction> hash_03(Botan::HashFunction::create(r3));

    std::string completeBlockData = blockData->digest(nonce01);
    Botan::secure_vector<uint8_t> hashData01;

    hash_01->update(completeBlockData);
    hash_01->final(hashData01);
    hash_02->update(hashData01);
    hash_02->final(hashData01);
    hash_03->update(hashData01);
    hash_03->final(hashData01);
    miningData retVal;
    std::vector<uint8_t> hashDigest = Botan::unlock(hashData01);
    for(int i = 0; i < 16; i++)
    {
        std::bitset<8> bTemp(hashDigest.at(i));
        retVal.hashBits += bTemp.to_string();
    }
    retVal.hashData = Botan::base58_encode(hashDigest.data(), hashDigest.size());
    std::cout<<"Hash data: " << retVal.hashData << std::endl;
    std::cout<<"Nonce: " << nonce01 <<std::endl;
    retVal.nonce = nonce01;
    return retVal;
}

uint8_t mineAlgo::findBase58Val(char val)
{
    for(int i = 0; i<58; i++)
    {
        if(mineAlgo::base58List[i] == val)
        {
            return i;
        }
    }
    return -1;
}

mineAlgo::~mineAlgo()
{
    //in case i need to
}


const std::string mineAlgo::round_01 [4]= {"Skein-512","Blake2b","SHA-3","SHA-256"};
const std::string mineAlgo::round_02 [4]= {"Blake2b(256)","SHA-256","Whirlpool","SHAKE-256"};
const std::string mineAlgo::round_03 = "SHAKE-128";
const char mineAlgo::base58List [58] = {'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','J','K','L','M','N','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
const int8_t mineAlgo::numbList [58] = {0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3,0,1};

