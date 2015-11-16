// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

#include <iostream>
#include <fstream>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x01;
        pchMessageStart[1] = 0x34;
        pchMessageStart[2] = 0xa9;
        pchMessageStart[3] = 0x7c;
        vAlertPubKey = ParseHex("0451f802a464ee85fc1adb785e6dcb2226839554c060191bb0adf39c8625cd616fde772526e4808fc8bae4c67055b200f9e7ae3a3375508bdcffeda5a5407a5b98");
        nDefaultPort = 18791;
        nRPCPort = 18792;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 12);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.				
        const char* pszTimestamp = "MasterMint, all about nodes and minting";
        CTransaction txNew;
		txNew.nTime = 1447416000;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("040484740fa684ad5023690c80f3a49c3f13f8d45b8c852fbcbc8bc4a8e4d3eb4a10f4d4604fa082ce601aaf0f4702165e1b51850b4a9f21b179c45070ac7b03a9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1447416000;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 186595;	

        hashGenesisBlock = genesis.GetPoWHash();	
			
        assert(hashGenesisBlock == uint256("0x00000eccd32786dbeee375c28ed71d9322bce484749d8488be2dbca92e7321db"));
        assert(genesis.hashMerkleRoot == uint256("0xae59c5a826122ef6953e91734c80379f99b58b96d97fe659687a40c6e6f0bce2"));
      
        base58Prefixes[PUBKEY_ADDRESS] = list_of(50);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(30);
        base58Prefixes[SECRET_KEY] =     list_of(153);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

		vSeeds.push_back(CDNSSeedData("37.97.132.5", "37.97.132.5"));
		
        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 20000000000;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x04;
        pchMessageStart[1] = 0x37;
        pchMessageStart[2] = 0x1f;
        pchMessageStart[3] = 0x21;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("041610cd93ead7072dd920bc204553c6933326ef42ad677a072946c442065ad636a3fd657aad13eac89416e226a765290b83e512f1ebac6a7f63fbcf7916a3ee45");
        nDefaultPort = 19494;
        nRPCPort = 18495;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 0x1e0ffff0; 
        genesis.nNonce = 4935555;
		
        hashGenesisBlock = genesis.GetPoWHash();  
        //assert(hashGenesisBlock == uint256("0x000000110fae8a551368b2e231d690eaf349f12487681794198c85fc95bee8ca"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(85);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(90);
        base58Prefixes[SECRET_KEY]     = list_of(213);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
