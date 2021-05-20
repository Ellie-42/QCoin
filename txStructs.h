#ifndef TX_STRUCTS_H
#define TX_STRUCTS_H

#include <botan/hash.h>
#include <botan/base64.h>

#incldue "blockChain.h"

struct TxIn
{
    std::string txOutId,txSig;
    int indexOut;
};

struct TxOut
{
    std::string addr;
    float amount;
};

class transactions
{
    public:
        std::string id;
        std::vector<TxIn> txInList;
        std::vector<TxOut> txOutList;

        std::string createTxId()
        {
            std::string txComp;
            for(TxIn ti : txInList){txComp += ti.txOutId + (std::to_string(indexOut));}
            for(TxOut to : txOutList){txComp += to.addr + (std::to_string(to.amount));}
            std::unique_ptr<Botan::HashFunction> hash_01(Botan::HashFunction::create("SHA-256"));
            std::unique_ptr<Botan::HashFunction> hash_02(Botan::HashFunction::create("SKEIN-512(100)"));
            std::vector<uint8_t> digest = hash_02->process(hash_01->process(txComp));
            return(Botan::base64_encode(digest.data(), digest.size()));
        }
};
