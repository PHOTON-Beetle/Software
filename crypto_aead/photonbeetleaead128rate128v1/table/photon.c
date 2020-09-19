/**********************************************
 * PHOTON-Beetle                              *
 * Authenticated Encryption and Hash Family   *
 *                                            *
 * Table-based Implementation for PC          *
 * Version 1.0 2020 by PHOTON-Beetle Team     *
 **********************************************/
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

const uint32_t SCShRMCS_Table[D][1<<S] = {
{0xbf5c86f8, 0xa9756b96, 0xceb643e4, 0x5dab3cd3, 0x1629ed6e, 0x00000000, 0x71eac51c, 0x931d7f37, 0x67c32872, 0xf4de5745, 0xd89fae8a, 0x3a6814a1, 0x85349259, 0xe2f7ba2b, 0x2c41f9cf, 0x4b82d1bd}, 
{0x565ef4bc, 0x7b7d93a5, 0xb3b7e2c6, 0xacafd85b, 0x2d236719, 0x00000000, 0xe5e9167a, 0x1f183a9d, 0xc8ca7163, 0xd7d24bfe, 0x9e9485df, 0x6465a938, 0x323b5d84, 0xfaf12ce7, 0x4946ce21, 0x818cbf42}, 
{0xba3969b3, 0xaec2b2ac, 0xc58d3dc8, 0x5761c156, 0x14fbdb1f, 0x00000000, 0x7fb4547b, 0x92ecfc9e, 0x6b4f8f64, 0xf9a373fa, 0xd176e6d7, 0x3c2e4e32, 0x86172781, 0xed58a8e5, 0x28d5952d, 0x439a1a49}, 
{0xd33c3811, 0x1cc5c644, 0xf8868499, 0x966b6322, 0xcff9fe55, 0x00000000, 0x2bbabc88, 0x6eede7bb, 0xe44342dd, 0x8aaea566, 0x377f7acc, 0x722821ff, 0xa11419ee, 0x45575b33, 0xbdd1dfaa, 0x59929d77}, 
{0xb26f4579, 0xa8b937f2, 0xc13e2bad, 0x54cd8ae1, 0x1ad6728b, 0x00000000, 0x73516ed4, 0x95f3a14c, 0x69871c5f, 0xfc74bd13, 0xdbe85926, 0x3d4a96be, 0x8f25d3c7, 0xe6a2cf98, 0x279ce435, 0x4e1bf86a}, 
{0xa2539fc1, 0xe87c2954, 0x51b8de69, 0x74a61db2, 0x4a2fb695, 0x00000000, 0xf3eb41a8, 0x251ec3db, 0xb9c4f73d, 0x9cda34e6, 0x1b9768fc, 0xcd62ea8f, 0x6f31754e, 0xd6f58273, 0x874d5c1a, 0x3e89ab27}, 
{0x993846cb, 0x22c63b5a, 0xdd84236c, 0x11638cb5, 0xbbfe7d91, 0x00000000, 0x44bc65a7, 0xcce7afd9, 0xff421836, 0x33a5b7ef, 0x667a5efd, 0xee219483, 0x7719d248, 0x885bca7e, 0x55dfe912, 0xaa9df124}, 
{0xeb643e47, 0xdab3cd3f, 0x7c32872a, 0xf5c86f8e, 0x31d7f378, 0x00000000, 0x9756b96d, 0x89fae8a4, 0xa6814a15, 0x2f7ba2b1, 0x4de57452, 0x5349259b, 0xb82d1bdc, 0x1eac51c9, 0x629ed6e3, 0xc41f9cf6}
};


inline static void AddKey(uint8_t state[D][D], int round)
{
	state[0][0] ^= RC[round][0];
	state[1][0] ^= RC[round][1];
	state[2][0] ^= RC[round][2];
	state[3][0] ^= RC[round][3];
	state[4][0] ^= RC[round][4];
	state[5][0] ^= RC[round][5];
	state[6][0] ^= RC[round][6];
	state[7][0] ^= RC[round][7];
}

inline static void SCShRMCS(uint8_t state[D][D])
{
	int c;
	uint32_t v;
	uint8_t os[D][D];
	memcpy(os, state, D*D);

	for(c = 0; c < D; c++) // for all columns
	{
		v = 0;
		v ^= SCShRMCS_Table[0][os[0][(0+c)&0x7]];
		v ^= SCShRMCS_Table[1][os[1][(1+c)&0x7]];
		v ^= SCShRMCS_Table[2][os[2][(2+c)&0x7]];
		v ^= SCShRMCS_Table[3][os[3][(3+c)&0x7]];
		v ^= SCShRMCS_Table[4][os[4][(4+c)&0x7]];
		v ^= SCShRMCS_Table[5][os[5][(5+c)&0x7]];
		v ^= SCShRMCS_Table[6][os[6][(6+c)&0x7]];
		v ^= SCShRMCS_Table[7][os[7][(7+c)&0x7]];

		state[7][c] = (v >> (0*8)) & 0xF;
		state[6][c] = (v >> (0*8 + 4)) & 0xF;
		state[5][c] = (v >> (1*8)) & 0xF;
		state[4][c] = (v >> (1*8 + 4)) & 0xF;
		state[3][c] = (v >> (2*8)) & 0xF;
		state[2][c] = (v >> (2*8 + 4)) & 0xF;
		state[1][c] = (v >> (3*8)) & 0xF;
		state[0][c] = (v >> (3*8 + 4)) & 0xF;
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
	uint64_t *state_pt;
	uint32_t a_dword;
	uint64_t x;
	uint64_t xl;
	uint64_t xh;
	uint64_t t;

#define STATESIZE_INuint8_tS          ((D * D * S + 7) / 8) // (8 * 8 * 4 + 7) / 8 = 32 uint8_ts
#define STATESIZE_INDWORDS ((STATESIZE_INuint8_tS + 3) / 4) // (32 + 3) / 4 = 8 dwords
	State_inout_pt = (uint32_t *)State_inout;
	state_pt = (uint64_t *)&(state[0][0]);
	for (i = 0; i < STATESIZE_INDWORDS; i++)
	{
		a_dword = State_inout_pt[i];
		xl = (uint64_t)a_dword & 0x0F0F0F0FULL;
		xh = (uint64_t)a_dword & 0xF0F0F0F0ULL;
		x = (xh << 28ULL) | xl;
		t = (x ^ (x >> 16ULL)) & 0x00000000FFFF0000ULL; x = x ^ t ^ (t << 16ULL);
		t = (x ^ (x >>  8ULL)) & 0x0000FF000000FF00ULL; x = x ^ t ^ (t <<  8ULL);
		state_pt[i] = x;
	}
 
    Permutation(state, ROUND);

	State_inout_pt = (uint32_t *)State_inout;
	state_pt = (uint64_t *)&(state[0][0]);
	for (i = 0; i < STATESIZE_INDWORDS; i++)
	{
		x = state_pt[i];
		t = (x ^ (x >>  8ULL)) & 0x0000FF000000FF00ULL; x = x ^ t ^ (t <<  8ULL);
		t = (x ^ (x >> 16ULL)) & 0x00000000FFFF0000ULL; x = x ^ t ^ (t << 16ULL);
		xl = x & 0x0F0F0F0FULL;
		xh = (x >> 28ULL) & 0xF0F0F0F0ULL;
		a_dword = (xh | xl);
		State_inout_pt[i] = a_dword;
	}
}