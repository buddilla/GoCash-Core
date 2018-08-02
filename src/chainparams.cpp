// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2018 The gocash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
    (0, uint256("0xcc7664befd4eebf99f01f5d1e39c975d1b7960f5a38934eb2861f0db1ce7c3b3"))
    (15000, uint256("0x981549b7241d82b1aacfdc0993e29bcaace7bc55e5cd13abe2bedb403c1040ce"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1528115517, // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    2000        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0xcc7664befd4eebf99f01f5d1e39c975d1b7960f5a38934eb2861f0db1ce7c3b3"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1528115517,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0xcc7664befd4eebf99f01f5d1e39c975d1b7960f5a38934eb2861f0db1ce7c3b3"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1528115517,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0x8c;
        pchMessageStart[2] = 0x29;
        pchMessageStart[3] = 0x53;
        vAlertPubKey = ParseHex("0403DFA2DB75FB42643EE026F6B28E0FA74ED031CB3AFE446AD66369BCBF3C08067A8252F7A62E75C851180AACFD44DC1B466AD809DED972952ED0FF5A17EDD1F6");
        nDefaultPort = 9911;
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // gocash: 1 day
        nTargetSpacing = 1 * 60;  // gocash: 60 seconds
        nMaturity = 30;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 5000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 400;
        nModifierUpdateBlock = 999999999;
        nZerocoinStartHeight = 90000;
        nBlockEnforceSerialRange = 90003; //Enforce serial range starting this block
        nZerocoinStartTime = 1530707517;// October 17, 2017 4:30:00 AM

        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         *
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "GOCASH COIN, Go FOR CASH";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1528115517;
        genesis.nBits = 0x207fffff;;
        genesis.nNonce = 12345;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xfc5dba28d7a5da1db11be7031b25470d7a10124ba8aab78da7eb5ccc2a33ff17"));
        assert(genesis.hashMerkleRoot == uint256("0x429f906734b063fd29980b3df39061aabe16e534f1d3818cc08da096b5563ddf"));

        vSeeds.push_back(CDNSSeedData("0", "168.235.83.224:9911"));
        vSeeds.push_back(CDNSSeedData("1", "183.81.155.6:9911"));
        vSeeds.push_back(CDNSSeedData("2", "139.0.67.212:9911"));
        vSeeds.push_back(CDNSSeedData("3", "115.178.223.69:9911"));
        vSeeds.push_back(CDNSSeedData("4", "173.199.122.103:9911"));
        vSeeds.push_back(CDNSSeedData("5", "115.178.208.112:9911"));
        vSeeds.push_back(CDNSSeedData("6", "173.199.122.103:9911"));
        vSeeds.push_back(CDNSSeedData("7", "203.78.118.92:9911"));
        vSeeds.push_back(CDNSSeedData("8", "203.78.118.190:9911"));
        vSeeds.push_back(CDNSSeedData("9", "173.90.87.168:9911"));
        vSeeds.push_back(CDNSSeedData("10", "112.215.241.151:9911"));
        vSeeds.push_back(CDNSSeedData("11", "112.215.154.228:9911"));
        vSeeds.push_back(CDNSSeedData("12", "90.253.228.171:9911"));
        vSeeds.push_back(CDNSSeedData("13", "75.138.100.44:9911"));
        vSeeds.push_back(CDNSSeedData("14", "115.178.205.115:9911"));
        vSeeds.push_back(CDNSSeedData("15", "101.180.5.119:9911"));
        vSeeds.push_back(CDNSSeedData("16", "14.185.23.246:9911"));
        vSeeds.push_back(CDNSSeedData("17", "112.215.244.131:9911"));
        vSeeds.push_back(CDNSSeedData("18", "36.69.130.163:9911"));
        vSeeds.push_back(CDNSSeedData("19", "180.248.5.112:9911"));
        vSeeds.push_back(CDNSSeedData("20", "98.214.20.153:9911"));
        vSeeds.push_back(CDNSSeedData("21", "36.85.25.159:9911"));
        vSeeds.push_back(CDNSSeedData("22", "79.238.68.246:9911"));
        vSeeds.push_back(CDNSSeedData("23", "180.247.209.187:9911"));
        vSeeds.push_back(CDNSSeedData("24", "118.38.99.125:9911"));
        vSeeds.push_back(CDNSSeedData("25", "176.114.6.90:9911"));
        vSeeds.push_back(CDNSSeedData("26", "114.124.205.212:9911"));
        vSeeds.push_back(CDNSSeedData("27", "177.7.105.17:9911"));
        vSeeds.push_back(CDNSSeedData("28", "115.178.205.137:9911"));
        vSeeds.push_back(CDNSSeedData("29", "141.101.28.218:9911"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 38);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 102);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x10)(0x92)(0x21)(0x2c).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04e3ba5bdf2f09dee40b20f47990d704c7a16a513454e5e504a843a4642edad009ddec7b2943e541f988243ccd660d9b0036155992da298185c0deeeaaeabf228d";
        strObfuscationPoolDummyAddress = "PCYiHgGJJ6xGHqivmdZrYjRnhaYf6AJ2Mp";
        nStartMasternodPayments = 1403728576; //Wed, 25 Jun 2014 20:36:16 GMT

        /** Zerocoin */
        zerocoinModulus = "25195908475657893494027183240048398571429282126204032027777137836043662020707595556264018525880784"
            "4069182906412495150821892985591491761845028084891200728449926873928072877767359714183472702618963750149718246911"
            "6507761337985909570009733045974880842840179742910064245869181719511874612151517265463228221686998754918242243363"
            "7259085141865462043576798423387184774447920739934236584823824281198163815010674810451660377306056201619676256133"
            "8441436038339044149526344321901146575444541784240209246165157233507787077498171257724679629263863563732899121548"
            "31438167899885040445364023527381951378636564391212010397122822120720357";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * CENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 2;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xa4;
        pchMessageStart[1] = 0x24;
        pchMessageStart[2] = 0xf4;
        pchMessageStart[3] = 0xf1;
        vAlertPubKey = ParseHex("04e3ba5bdf2f09dee40b20f47990d704c7a16a513454e5e504a843a4642edad009ddec7b2943e541f988243ccd660d9b0036155992da298185c0deeeaaeabf228d");
        nDefaultPort = 28181;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // gocash: 1 day
        nTargetSpacing = 1 * 10;  // gocash: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 201576;

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1528115517;
        genesis.nNonce = 12345;

        hashGenesisBlock = genesis.GetHash();

        assert(hashGenesisBlock == uint256("0xfc5dba28d7a5da1db11be7031b25470d7a10124ba8aab78da7eb5ccc2a33ff17"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet gocash addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet gocash script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet gocash BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet gocash BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet gocash BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x01)(0x00)(0x00)(0x80).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "04e3ba5bdf2f09dee40b20f47990d704c7a16a513454e5e504a843a4642edad009ddec7b2943e541f988243ccd660d9b0036155992da298185c0deeeaaeabf228d";
        strObfuscationPoolDummyAddress = "PCYiHgGJJ6xGHqivmdZrYjRnhaYf6AJ2Mp";
        nStartMasternodGOCashments = 1505224800; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xb2;
        pchMessageStart[1] = 0x89;
        pchMessageStart[2] = 0x12;
        pchMessageStart[3] = 0x92;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // gocash: 1 day
        nTargetSpacing = 1 * 60;        // gocash: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1528115517;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 12345;

        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18182;
        assert(hashGenesisBlock == uint256("0xfc5dba28d7a5da1db11be7031b25470d7a10124ba8aab78da7eb5ccc2a33ff17"));

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 33336;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams* pCurrentParams = 0;

CModifiableParams* ModifiableParams()
{
    assert(pCurrentParams);
    assert(pCurrentParams == &unitTestParams);
    return (CModifiableParams*)&unitTestParams;
}

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    case CBaseChainParams::UNITTEST:
        return unitTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
