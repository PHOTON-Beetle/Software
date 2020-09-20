#include "photon.h"


const uint8_t RC[12][D] = {
{0x1, 0x0, 0x2, 0x6, 0xe, 0xf, 0xd, 0x9}, 
{0x3, 0x2, 0x0, 0x4, 0xc, 0xd, 0xf, 0xb}, 
{0x7, 0x6, 0x4, 0x0, 0x8, 0x9, 0xb, 0xf}, 
{0xe, 0xf, 0xd, 0x9, 0x1, 0x0, 0x2, 0x6}, 
{0xd, 0xc, 0xe, 0xa, 0x2, 0x3, 0x1, 0x5}, 
{0xb, 0xa, 0x8, 0xc, 0x4, 0x5, 0x7, 0x3}, 
{0x6, 0x7, 0x5, 0x1, 0x9, 0x8, 0xa, 0xe}, 
{0xc, 0xd, 0xf, 0xb, 0x3, 0x2, 0x0, 0x4}, 
{0x9, 0x8, 0xa, 0xe, 0x6, 0x7, 0x5, 0x1}, 
{0x2, 0x3, 0x1, 0x5, 0xd, 0xc, 0xe, 0xa}, 
{0x5, 0x4, 0x6, 0x2, 0xa, 0xb, 0x9, 0xd}, 
{0xa, 0xb, 0x9, 0xd, 0x5, 0x4, 0x6, 0x2}
};

const uint64_t SCShRMCS_Table[D][1<<S] = {
{
0x080f06080c050f0bULL, 0x06090b060507090aULL, 0x040e0304060b0e0cULL, 0x030d0c030b0a0d05ULL, 0x0e060d0e09020601ULL, 0x0000000000000000ULL, 0x0c01050c0a0e0107ULL, 0x07030f070d010309ULL, 0x02070802030c0706ULL, 0x050407050e0d040fULL, 0x0a080e0a0f09080dULL, 0x010a040108060a03ULL, 0x0905020904030508ULL, 0x0b020a0b070f020eULL, 0x0f0c090f01040c02ULL, 0x0d0b010d02080b04ULL, 
},
{
0x0c0b040f0e050605ULL, 0x050a03090d070b07ULL, 0x060c020e070b030bULL, 0x0b05080d0f0a0c0aULL, 0x0901070603020d02ULL, 0x0000000000000000ULL, 0x0a070601090e050eULL, 0x0d090a0308010f01ULL, 0x030601070a0c080cULL, 0x0e0f0b04020d070dULL, 0x0f0d050804090e09ULL, 0x0803090a05060406ULL, 0x04080d050b030203ULL, 0x070e0c02010f0a0fULL, 0x01020e0c06040904ULL, 0x02040f0b0c080108ULL, 
},
{
0x030b090609030a0bULL, 0x0c0a020b020c0e0aULL, 0x080c0d030d08050cULL, 0x0605010c01060705ULL, 0x0f010b0d0b0f0401ULL, 0x0000000000000000ULL, 0x0b070405040b0f07ULL, 0x0e090c0f0c0e0209ULL, 0x04060f080f040b06ULL, 0x0a0f0307030a090fULL, 0x070d060e0607010dULL, 0x02030e040e020c03ULL, 0x0108070207010608ULL, 0x050e080a08050d0eULL, 0x0d020509050d0802ULL, 0x09040a010a090304ULL, 
},
{
0x010108030c03030dULL, 0x0404060c050c0c01ULL, 0x090904080608080fULL, 0x020203060b060609ULL, 0x05050e0f090f0f0cULL, 0x0000000000000000ULL, 0x08080c0b0a0b0b02ULL, 0x0b0b070e0d0e0e06ULL, 0x0d0d02040304040eULL, 0x0606050a0e0a0a08ULL, 0x0c0c0a070f070703ULL, 0x0f0f010208020207ULL, 0x0e0e09010401010aULL, 0x03030b0507050504ULL, 0x0a0a0f0d010d0d0bULL, 0x07070d0902090905ULL, 
},
{
0x090705040f06020bULL, 0x020f0703090b080aULL, 0x0d0a0b020e03010cULL, 0x010e0a080d0c0405ULL, 0x0b080207060d0a01ULL, 0x0000000000000000ULL, 0x040d0e0601050307ULL, 0x0c04010a030f0509ULL, 0x0f050c0107080906ULL, 0x03010d0b04070c0fULL, 0x06020905080e0b0dULL, 0x0e0b06090a040d03ULL, 0x070c030d05020f08ULL, 0x08090f0c020a060eULL, 0x0503040e0c090702ULL, 0x0a06080f0b010e04ULL, 
},
{
0x010c0f090305020aULL, 0x040509020c07080eULL, 0x09060e0d080b0105ULL, 0x020b0d01060a0407ULL, 0x0509060b0f020a04ULL, 0x0000000000000000ULL, 0x080a01040b0e030fULL, 0x0b0d030c0e010502ULL, 0x0d03070f040c090bULL, 0x060e04030a0d0c09ULL, 0x0c0f080607090b01ULL, 0x0f080a0e02060d0cULL, 0x0e04050701030f06ULL, 0x03070208050f060dULL, 0x0a010c050d040708ULL, 0x07020b0a09080e03ULL, 
},
{
0x0b0c060408030909ULL, 0x0a050b03060c0202ULL, 0x0c06030204080d0dULL, 0x050b0c0803060101ULL, 0x01090d070e0f0b0bULL, 0x0000000000000000ULL, 0x070a05060c0b0404ULL, 0x090d0f0a070e0c0cULL, 0x0603080102040f0fULL, 0x0f0e070b050a0303ULL, 0x0d0f0e050a070606ULL, 0x0308040901020e0eULL, 0x0804020d09010707ULL, 0x0e070a0c0b050808ULL, 0x0201090e0f0d0505ULL, 0x0402010f0d090a0aULL, 
},
{
0x07040e0304060b0eULL, 0x0f030d0c030b0a0dULL, 0x0a02070802030c07ULL, 0x0e080f06080c050fULL, 0x0807030f070d0103ULL, 0x0000000000000000ULL, 0x0d06090b06050709ULL, 0x040a080e0a0f0908ULL, 0x05010a040108060aULL, 0x010b020a0b070f02ULL, 0x02050407050e0d04ULL, 0x0b09050209040305ULL, 0x0c0d0b010d02080bULL, 0x090c01050c0a0e01ULL, 0x030e060d0e090206ULL, 0x060f0c090f01040cULL, 
},
};


inline static void AddKey(uint8_t state[D][D], int round)
{
	*((uint64_t *)state[0]) ^= *((uint64_t *)RC[round]);
}

inline static void SCShRMCS(uint8_t state[D][D])
{
	int c;
	uint64_t s2o0;
	uint64_t s2o1;
	uint64_t s2o2;
	uint64_t s2o3;
	uint64_t s2o4;
	uint64_t s2o5;
	uint64_t s2o6;
	uint64_t s2o7;
	uint8_t os[D][D];
	memcpy(os, state, D*D);

	for(c = 0; c < D; c++) // for all columns
	{
		s2o0 = SCShRMCS_Table[0][os[(0+c)&0x7][0]];
		s2o1 = SCShRMCS_Table[1][os[(1+c)&0x7][1]];
		s2o2 = SCShRMCS_Table[2][os[(2+c)&0x7][2]];
		s2o3 = SCShRMCS_Table[3][os[(3+c)&0x7][3]];
		s2o4 = SCShRMCS_Table[4][os[(4+c)&0x7][4]];
		s2o5 = SCShRMCS_Table[5][os[(5+c)&0x7][5]];
		s2o6 = SCShRMCS_Table[6][os[(6+c)&0x7][6]];
		s2o7 = SCShRMCS_Table[7][os[(7+c)&0x7][7]];
		s2o0 ^= s2o1;
		s2o2 ^= s2o3;
		s2o4 ^= s2o5;
		s2o6 ^= s2o7;
		s2o0 ^= s2o2;
		s2o4 ^= s2o6;
		s2o0 ^= s2o4;
		*((uint64_t *)state[c]) = s2o0;;
	}
}

inline static void Permutation(uint8_t state[D][D], int R)
{
	int i;
	for(i = 0; i < R; i++) {
		AddKey(state, i);
		SCShRMCS(state);
	}
}

void PHOTON_Permutation(unsigned char *State_inout)
{
    uint8_t state[D][D];
    int i;

	uint32_t *State_inout_pt;
	uint32_t a_dword;
	uint64_t x;
	uint64_t xl;
	uint64_t xh;
	uint64_t t;

#define STATESIZE_INuint8_tS          ((D * D * S + 7) / 8) // (8 * 8 * 4 + 7) / 8 = 32 uint8_ts
#define STATESIZE_INDWORDS ((STATESIZE_INuint8_tS + 3) / 4) // (32 + 3) / 4 = 8 dwords
	State_inout_pt = (uint32_t *)State_inout;
	for (i = 0; i < STATESIZE_INDWORDS; i++)
	{
		a_dword = State_inout_pt[i];
		xl = (uint64_t)a_dword & 0x0F0F0F0FULL;
		xh = (uint64_t)a_dword & 0xF0F0F0F0ULL;
		x = (xh << 28ULL) | xl;
		t = (x ^ (x >> 16ULL)) & 0x00000000FFFF0000ULL; x = x ^ t ^ (t << 16ULL);
		t = (x ^ (x >>  8ULL)) & 0x0000FF000000FF00ULL; x = x ^ t ^ (t <<  8ULL);
		state[0][i] = (uint8_t)(x) & 0x0F;
		state[1][i] = (uint8_t)(x >> (1 * 8ULL)) & 0x0F;
		state[2][i] = (uint8_t)(x >> (2 * 8ULL)) & 0x0F;
		state[3][i] = (uint8_t)(x >> (3 * 8ULL)) & 0x0F;
		state[4][i] = (uint8_t)(x >> (4 * 8ULL)) & 0x0F;
		state[5][i] = (uint8_t)(x >> (5 * 8ULL)) & 0x0F;
		state[6][i] = (uint8_t)(x >> (6 * 8ULL)) & 0x0F;
		state[7][i] = (uint8_t)(x >> (7 * 8ULL)) & 0x0F;
	}
 
    Permutation(state, ROUND);

	State_inout_pt = (uint32_t *)State_inout;
	for (i = 0; i < STATESIZE_INDWORDS; i++)
	{
		x = ((uint64_t)state[0][i]) |
		    (((uint64_t)state[1][i]) << (1 * 8ULL)) |
		    (((uint64_t)state[2][i]) << (2 * 8ULL)) |
		    (((uint64_t)state[3][i]) << (3 * 8ULL)) |
		    (((uint64_t)state[4][i]) << (4 * 8ULL)) |
		    (((uint64_t)state[5][i]) << (5 * 8ULL)) |
		    (((uint64_t)state[6][i]) << (6 * 8ULL)) |
		    (((uint64_t)state[7][i]) << (7 * 8ULL));
		t = (x ^ (x >>  8ULL)) & 0x0000FF000000FF00ULL; x = x ^ t ^ (t <<  8ULL);
		t = (x ^ (x >> 16ULL)) & 0x00000000FFFF0000ULL; x = x ^ t ^ (t << 16ULL);
		xl = x & 0x0F0F0F0FULL;
		xh = (x >> 28ULL) & 0xF0F0F0F0ULL;
		a_dword = (xh | xl);
		State_inout_pt[i] = a_dword;
	}
}