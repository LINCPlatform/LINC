// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin Core developers
// Copyright (c) 2014-2017 The Dash Core developers
// Copyright (c) 2018 The LINC Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"
#include "consensus/merkle.h"

#include <stdio.h>
#include "tinyformat.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

#include "chainparamsseeds.h"

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(txNew);
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

/**
 * Build the genesis block. Note that the output of its generation
 * transaction cannot be spent since it did not originally exist in the
 * database.
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "LINC is not a coin // 2018-04-24";
    const CScript genesisOutputScript = CScript() << ParseHex("048fb16fbd075e50edecec80589e3dddb74fe6433001a3ffbc894403b61279a5270edfa49aa7c12320a9da173331412f226f32bcd01802d5e9b40b15d0e3c894f3") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */


class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 64800; // every ~90 days
        consensus.nMasternodePaymentsStartBlock = 3600; //
        consensus.nMasternodePaymentsIncreaseBlock = 3600; // not used
        consensus.nMasternodePaymentsIncreasePeriod = 64800; // increase masternode reward every 64800 block
        consensus.nDevFundPaymentsStartBlock = 21600;
        consensus.devFundPaymentsAddress = "LZxvv1WkcsFoRVu6pEZUKumkhV2XGqSmjP";
        consensus.nPoolRegistrationStartBlock = 21600;
        consensus.nSameForgerPenaltyStartBlock = 25000;
        consensus.nInstantSendKeepLock = 24;
        consensus.nBudgetPaymentsStartBlock = 0x7fffffff; // no budget temporarily
        consensus.nBudgetPaymentsCycleBlocks = 16616; // ~(60*24*30)/2.6, actual number of blocks per month is 200700 / 12 = 16725
        consensus.nBudgetPaymentsWindowBlocks = 100;
        consensus.nBudgetProposalEstablishingTime = 60*60*24;
        consensus.nSuperblockStartBlock = 0x7fffffff; // no superblocks temporarily
        consensus.nSuperblockCycle = 16616; // ~(60*24*30)/2.6, actual number of blocks per month is 200700 / 12 = 16725
        consensus.nGovernanceMinQuorum = 10;
        consensus.nGovernanceFilterElements = 20000;
        consensus.nMasternodeMinimumConfirmations = 15;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = 0; // from launch
        consensus.BIP34Hash = uint256S("0x0000083b904abb91545ffdc8bb61f9fabb4e728629b8975baaadb10eb0f54d99"); // genesis hash
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // LINC: 1 day
        consensus.nPowTargetSpacing = 2 * 60; // LINC: 2 minutes
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 10;
        consensus.nPowDGWHeight = 50;
        consensus.nRuleChangeActivationThreshold = 1916; // 95% of 2016
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1519862400; // March 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1551398400; // March 1st, 2018

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 32-bit integer with any alignment.
         */
        pchMessageStart[0] = 0xca;
        pchMessageStart[1] = 0xd3;
        pchMessageStart[2] = 0xb0;
        pchMessageStart[3] = 0xb7;
        vAlertPubKey = ParseHex("04409e02e9b6f772af40fc897683076eec4152a5e425834a735f3e850a6493267f9864bc6c61df584e29e218d12d99ecb8982c3c1747afc0c81cc7a39a31a1f646");
        nDefaultPort = 17222;
        nMaxTipAge = 2 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1524571200, 1428749, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000083b904abb91545ffdc8bb61f9fabb4e728629b8975baaadb10eb0f54d99"));
        assert(genesis.hashMerkleRoot == uint256S("0x984e1a31140f65ba4dbef8b5d22a5d1a2363bc43898107a9fa88cfd2dde44c9f"));


        vSeeds.push_back(CDNSSeedData("seed1.linc", "dnsseed1.linc.site"));
        vSeeds.push_back(CDNSSeedData("seed2.linc", "dnsseed2.linc.site"));
        vSeeds.push_back(CDNSSeedData("seed3.linc", "dnsseed3.linc.site"));
        vSeeds.push_back(CDNSSeedData("seed4.linc", "dnsseed4.linc.site"));


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,48); // L
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18); // 8
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,212);
        // LINC BIP32 pubkeys start with 'xpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        // LINC BIP32 prvkeys start with 'xprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();
        // LINC BIP44 coin type is '5'
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x05).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 60*60; // fulfilled requests expire in 1 hour
        strSporkPubKey = "04a460e5df140a13bbc49c904c2ab92ca615f776070e9847044ea95b5c374385a29fdbef318a4b495d77bec63bee11a3805862cae5e5fb7b3add309a0075afb387";
        strMasternodePaymentsPubKey = "04a460e5df140a13bbc49c904c2ab92ca615f776070e9847044ea95b5c374385a29fdbef318a4b495d77bec63bee11a3805862cae5e5fb7b3add309a0075afb387";

        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (  0, uint256S("0x0000083b904abb91545ffdc8bb61f9fabb4e728629b8975baaadb10eb0f54d99"))
            (  5900, uint256S("0x000000000c36c7a21a77b9b0610b6abfeba1f397de80333bdf608de3be77a245"))
            (  6200, uint256S("0x000000d1c2d7e422860d402afb2d59fdfda9fed098a0048d200f67b89fc60228")),
            1525469428, // * UNIX timestamp of last checkpoint block
            10448,    // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            1500        // * estimated number of transactions per day after checkpoint
        };

        registeredPools = boost::assign::map_list_of
        (0,     std::set<std::string>() )
        (21600, boost::assign::list_of<std::string> 
                    ("LNg5rEQFKTDPzcFMJjZPyygPis1q8s6AYT")  // LINC
                    ("LPvR4Hjs2KT5NCBD5fATCxuY2n9Pd7yRMu")  // Saltpool
                    ("LKaYw79j6j7ZKRp2HmgLAUdpafsjJ9hFUh")  // Hash4life
                    ("LcByXiuQnAn55zAFTSUzmjysZXzUH3uX1P")  // FairMine
                    ("LPeebZHVdKpVJcLZEJqYzTAf3hV6PDqJ3f")  // BSOD
                    ("LiHjnMV83HpFfD3DzjCU9bdkV3SboR3cyt")  // WeekendPool
                .convert_to_container<std::set<std::string> >()  );
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CChainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 64800; // every ~90 days
        consensus.nMasternodePaymentsStartBlock = 3600; //
        consensus.nMasternodePaymentsIncreaseBlock = 3600; // not used
        consensus.nMasternodePaymentsIncreasePeriod = 64800; // increase masternode reward every 64800 block
        consensus.nDevFundPaymentsStartBlock = 21600;
        consensus.devFundPaymentsAddress = "LZxvv1WkcsFoRVu6pEZUKumkhV2XGqSmjP";
        consensus.nPoolRegistrationStartBlock = 0x7fffffff;
        consensus.nSameForgerPenaltyStartBlock = 0x7fffffff;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 0x7fffffff; // no budget temporarily
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 0x7fffffff; // NOTE: Should satisfy nSuperblockStartBlock > nBudgetPeymentsStartBlock
        consensus.nSuperblockCycle = 24; // Superblocks can be issued hourly on testnet
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 500;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 51;
        consensus.nMajorityRejectBlockOutdated = 75;
        consensus.nMajorityWindow = 100;
        consensus.BIP34Height = 0; // from launch
                consensus.BIP34Hash = uint256S("0x00000bf3093df9f798156889d2578eeb3b357f35af64c2ebf5efb80444693e0a"); // genesis hash
        consensus.powLimit = uint256S("00000fffff000000000000000000000000000000000000000000000000000000");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // LINC: 1 day
        consensus.nPowTargetSpacing = 2 * 60; // LINC: 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.nPowKGWHeight = 10;
        consensus.nPowDGWHeight = 50;
        consensus.nRuleChangeActivationThreshold = 1512; // 75% for testchains
        consensus.nMinerConfirmationWindow = 2016; // nPowTargetTimespan / nPowTargetSpacing
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601; // January 1, 2008
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999; // December 31, 2008

        // Deployment of BIP68, BIP112, and BIP113.
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1519862400; // March 1st, 2017
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1551398400; // March 1st, 2018

        pchMessageStart[0] = 0xc2;
        pchMessageStart[1] = 0x3d;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0xbf;
        vAlertPubKey = ParseHex("047ce3f4270b51da389992fc2509710da96f4103f61513188bafd56d4493510cbc4c3c578ff08dd5da82050fe85bc2a7f66f7462268c58892e235ba0a9a8addfe3");
        nDefaultPort = 17333;
        nMaxTipAge = 0x7fffffff; // allow mining on top of old blocks for testnet
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1524571220, 180513, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x00000bf3093df9f798156889d2578eeb3b357f35af64c2ebf5efb80444693e0a"));
        assert(genesis.hashMerkleRoot == uint256S("0x984e1a31140f65ba4dbef8b5d22a5d1a2363bc43898107a9fa88cfd2dde44c9f"));

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("testnet-seed.linc",  "testnet-seed.linc.site"));

        // Testnet LINC addresses start with 't'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,127);
        // Testnet LINC script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Testnet LINC BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Testnet LINC BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Testnet LINC BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fMiningRequiresPeers = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 3;
        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes
        strSporkPubKey = "04547e657d1c35813d2461eb7cad490be6222b90e192d6e184ff93907173bac6b29fe4bec036b9f1baa36904d8f30d773e5af730050c88120db1aa54217c36b8b5";
        strMasternodePaymentsPubKey = "04547e657d1c35813d2461eb7cad490be6222b90e192d6e184ff93907173bac6b29fe4bec036b9f1baa36904d8f30d773e5af730050c88120db1aa54217c36b8b5";


        checkpointData = (CCheckpointData) {
            boost::assign::map_list_of
            (    0, uint256S("0x00000bf3093df9f798156889d2578eeb3b357f35af64c2ebf5efb80444693e0a")),

            1524571220, // * UNIX timestamp of last checkpoint block
            0,     // * total number of transactions between genesis and last checkpoint
                        //   (the tx=... number in the SetBestChain debug.log lines)
            0         // * estimated number of transactions per day after checkpoint
        };

        registeredPools = boost::assign::map_list_of
        (0,     std::set<std::string>());
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CChainParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.nMasternodePaymentsStartBlock = 240;
        consensus.nMasternodePaymentsIncreaseBlock = 350;
        consensus.nMasternodePaymentsIncreasePeriod = 10;
        consensus.nDevFundPaymentsStartBlock = 21600;
        consensus.devFundPaymentsAddress = "LZxvv1WkcsFoRVu6pEZUKumkhV2XGqSmjP";
        consensus.nPoolRegistrationStartBlock = 0x7fffffff;
        consensus.nSameForgerPenaltyStartBlock = 0x7fffffff;
        consensus.nInstantSendKeepLock = 6;
        consensus.nBudgetPaymentsStartBlock = 0x7fffffff;
        consensus.nBudgetPaymentsCycleBlocks = 50;
        consensus.nBudgetPaymentsWindowBlocks = 10;
        consensus.nBudgetProposalEstablishingTime = 60*20;
        consensus.nSuperblockStartBlock = 0x7fffffff;
        consensus.nSuperblockCycle = 10;
        consensus.nGovernanceMinQuorum = 1;
        consensus.nGovernanceFilterElements = 100;
        consensus.nMasternodeMinimumConfirmations = 1;
        consensus.nMajorityEnforceBlockUpgrade = 750;
        consensus.nMajorityRejectBlockOutdated = 950;
        consensus.nMajorityWindow = 1000;
        consensus.BIP34Height = -1; // BIP34 has not necessarily activated on regtest
        consensus.BIP34Hash = uint256();
        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 24 * 60 * 60; // LINC: 1 day
        consensus.nPowTargetSpacing = 2 * 60; // LINC: 2.5 minutes
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nPowKGWHeight = 50;
        consensus.nPowDGWHeight = 50;
        consensus.nRuleChangeActivationThreshold = 108; // 75% for testchains
        consensus.nMinerConfirmationWindow = 144; // Faster than normal for regtest (144 instead of 2016)
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 999999999999ULL;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 999999999999ULL;

        pchMessageStart[0] = 0xc9;
        pchMessageStart[1] = 0xf7;
        pchMessageStart[2] = 0xba;
        pchMessageStart[3] = 0xa1;
        nMaxTipAge = 6 * 60 * 60; // ~144 blocks behind -> 2 x fork detection time, was 24 * 60 * 60 in bitcoin
        nDefaultPort = 17444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1524571240, 248688, 0x1e0ffff0, 1, 50 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000001cb43c3505462b0d56f357ad7cacb87db76a97ee8b119666ad051f60918"));
        assert(genesis.hashMerkleRoot == uint256S("0x984e1a31140f65ba4dbef8b5d22a5d1a2363bc43898107a9fa88cfd2dde44c9f"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;

        nFulfilledRequestExpireTime = 5*60; // fulfilled requests expire in 5 minutes

        checkpointData = (CCheckpointData){
            boost::assign::map_list_of
            ( 0, uint256S("0x000001cb43c3505462b0d56f357ad7cacb87db76a97ee8b119666ad051f60918")),
            0,
            0,
            0
        };
        
        registeredPools = boost::assign::map_list_of
        (0,     std::set<std::string>());

        // Regtest LINC addresses start with 'r'
        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,122);
        // Regtest LINC script addresses start with '8' or '9'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,19);
        // Regtest private keys start with '9' or 'c' (Bitcoin defaults)
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,239);
        // Regtest LINC BIP32 pubkeys start with 'tpub' (Bitcoin defaults)
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        // Regtest LINC BIP32 prvkeys start with 'tprv' (Bitcoin defaults)
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();
        // Regtest LINC BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE]  = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();
   }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = 0;

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
            return mainParams;
    else if (chain == CBaseChainParams::TESTNET)
            return testNetParams;
    else if (chain == CBaseChainParams::REGTEST)
            return regTestParams;
    else
        throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}
