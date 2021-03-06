/*
 * fttrans.h
 *
 *  Created on: Oct 17, 2017
 *      Author: clasrun
 */

#ifndef FTTRANS_H_
#define FTTRANS_H_

#include "ftlib.h"

/*Complete index map.
 * See ft_pkg.vhd
 * Crate - slot - channel - id - x - y - hodo_sector - hodo_component - hodo_l1_slot - hodo_l1_channel - hodo_l2_slot - hodo_l2_channel
 */
static int ftFullMap[FT_CRYSTAL_NUM][12] = { { 70, 3, 0, 143, 11, 6, 6, 17, 7, 1, 7, 13 }, { 70, 3, 1, 121, 11, 5, 6, 11, 7, 0, 7, 15 }, { 70,
		3, 2, 99, 11, 4, 6, 11, 7, 0, 7, 15 }, { 70, 3, 3, 77, 11, 3, 6, 7, 9, 2, 9, 10 }, { 70, 3, 4, 55, 11, 2, 6, 7, 9, 2, 9, 10 }, { 70,
		3, 5, 11, 11, 0, 6, 3, 9, 7, 9, 15 }, { 70, 3, 6, 33, 11, 1, 6, 3, 9, 7, 9, 15 }, { 70, 3, 7, 144, 12, 6, 6, 18, 7, 2, 7, 14 }, {
		70, 3, 8, 122, 12, 5, 6, 11, 7, 0, 7, 15 }, { 70, 3, 9, 100, 12, 4, 6, 11, 7, 0, 7, 15 },
		{ 70, 3, 10, 78, 12, 3, 6, 7, 9, 2, 9, 10 }, { 70, 3, 11, 56, 12, 2, 6, 7, 9, 2, 9, 10 },
		{ 70, 3, 12, 12, 12, 0, 6, 3, 9, 7, 9, 15 }, { 70, 3, 13, 34, 12, 1, 6, 3, 9, 7, 9, 15 },
		{ 70, 3, 14, 167, 13, 7, 0, 0, 0, 0, 0, 0 }, { 70, 3, 15, 145, 13, 6, 6, 19, 9, 4, 9, 13 }, { 70, 4, 0, 101, 13, 4, 6, 12, 19, 6,
				19, 14 }, { 70, 4, 1, 79, 13, 3, 6, 8, 4, 1, 4, 8 }, { 70, 4, 2, 13, 13, 0, 6, 4, 18, 1, 18, 8 }, { 70, 4, 3, 35, 13, 1, 6,
				4, 18, 1, 18, 8 }, { 70, 4, 4, 57, 13, 2, 6, 8, 4, 1, 4, 8 }, { 70, 4, 5, 190, 14, 8, 0, 0, 0, 0, 0, 0 }, { 70, 4, 6, 168,
				14, 7, 7, 9, 8, 1, 8, 13 }, { 70, 4, 7, 146, 14, 6, 6, 20, 9, 3, 9, 14 }, { 70, 4, 8, 124, 14, 5, 6, 12, 19, 6, 19, 14 }, {
				70, 4, 9, 102, 14, 4, 6, 12, 19, 6, 19, 14 }, { 70, 4, 10, 36, 14, 1, 6, 4, 18, 1, 18, 8 }, { 70, 4, 11, 58, 14, 2, 6, 8, 4,
				1, 4, 8 }, { 70, 4, 12, 80, 14, 3, 6, 8, 4, 1, 4, 8 }, { 70, 4, 13, 235, 15, 10, 8, 16, 9, 0, 9, 9 }, { 70, 4, 14, 213, 15,
				9, 8, 15, 9, 6, 9, 11 }, { 70, 4, 15, 191, 15, 8, 8, 14, 9, 5, 9, 12 }, { 70, 5, 0, 169, 15, 7, 8, 13, 8, 0, 8, 14 }, { 70,
				5, 1, 147, 15, 6, 7, 8, 7, 3, 7, 12 }, { 70, 5, 2, 125, 15, 5, 7, 8, 7, 3, 7, 12 },
		{ 70, 5, 3, 103, 15, 4, 7, 7, 5, 1, 5, 8 }, { 70, 5, 4, 81, 15, 3, 7, 7, 5, 1, 5, 8 }, { 70, 5, 5, 59, 15, 2, 7, 6, 18, 3, 18, 9 },
		{ 70, 5, 6, 37, 15, 1, 7, 6, 18, 3, 18, 9 }, { 70, 5, 7, 236, 16, 10, 8, 10, 4, 4, 4, 13 }, { 70, 5, 8, 214, 16, 9, 8, 10, 4, 4, 4,
				13 }, { 70, 5, 9, 192, 16, 8, 8, 9, 6, 5, 6, 12 }, { 70, 5, 10, 170, 16, 7, 8, 9, 6, 5, 6, 12 }, { 70, 5, 11, 148, 16, 6, 7,
				8, 7, 3, 7, 12 }, { 70, 5, 12, 126, 16, 5, 7, 8, 7, 3, 7, 12 }, { 70, 5, 13, 104, 16, 4, 7, 7, 5, 1, 5, 8 }, { 70, 5, 14,
				82, 16, 3, 7, 7, 5, 1, 5, 8 }, { 70, 5, 15, 60, 16, 2, 7, 6, 18, 3, 18, 9 }, { 70, 6, 0, 237, 17, 10, 8, 10, 4, 4, 4, 13 },
		{ 70, 6, 1, 215, 17, 9, 8, 10, 4, 4, 4, 13 }, { 70, 6, 2, 193, 17, 8, 8, 9, 6, 5, 6, 12 },
		{ 70, 6, 3, 171, 17, 7, 8, 9, 6, 5, 6, 12 }, { 70, 6, 4, 149, 17, 6, 7, 5, 6, 0, 6, 13 },
		{ 70, 6, 5, 61, 17, 2, 7, 3, 6, 1, 6, 14 }, { 70, 6, 6, 83, 17, 3, 7, 4, 5, 0, 5, 9 }, { 70, 6, 7, 105, 17, 4, 7, 4, 5, 0, 5, 9 }, {
				70, 6, 8, 127, 17, 5, 7, 5, 6, 0, 6, 13 }, { 70, 6, 9, 238, 18, 10, 8, 6, 4, 3, 4, 10 }, { 70, 6, 10, 216, 18, 9, 8, 6, 4,
				3, 4, 10 }, { 70, 6, 11, 194, 18, 8, 8, 5, 6, 3, 6, 10 }, { 70, 6, 12, 172, 18, 7, 8, 5, 6, 3, 6, 10 }, { 70, 6, 13, 150,
				18, 6, 7, 5, 6, 0, 6, 13 }, { 70, 6, 14, 84, 18, 3, 7, 4, 5, 0, 5, 9 }, { 70, 6, 15, 106, 18, 4, 7, 4, 5, 0, 5, 9 }, { 70,
				7, 0, 128, 18, 5, 7, 5, 6, 0, 6, 13 }, { 70, 7, 1, 239, 19, 10, 8, 6, 4, 3, 4, 10 }, { 70, 7, 2, 217, 19, 9, 8, 6, 4, 3, 4,
				10 }, { 70, 7, 3, 195, 19, 8, 8, 5, 6, 3, 6, 10 }, { 70, 7, 4, 173, 19, 7, 8, 5, 6, 3, 6, 10 }, { 70, 7, 5, 151, 19, 6, 7,
				2, 5, 2, 5, 11 }, { 70, 7, 6, 107, 19, 4, 7, 1, 6, 2, 6, 15 }, { 70, 7, 7, 129, 19, 5, 7, 2, 5, 2, 5, 11 }, { 70, 7, 8, 240,
				20, 10, 8, 2, 3, 4, 3, 10 }, { 70, 7, 9, 218, 20, 9, 8, 2, 3, 4, 3, 10 }, { 70, 7, 10, 196, 20, 8, 8, 1, 5, 3, 5, 10 }, {
				70, 7, 11, 174, 20, 7, 8, 1, 5, 3, 5, 10 }, { 70, 7, 12, 152, 20, 6, 7, 2, 5, 2, 5, 11 }, { 70, 7, 13, 130, 20, 5, 7, 2, 5,
				2, 5, 11 }, { 70, 7, 14, 197, 21, 8, 8, 1, 5, 3, 5, 10 }, { 70, 7, 15, 219, 21, 9, 8, 2, 3, 4, 3, 10 }, { 70, 8, 0, 263, 21,
				11, 8, 3, 3, 5, 3, 11 }, { 70, 8, 1, 285, 21, 12, 8, 3, 3, 5, 3, 11 }, { 70, 8, 2, 307, 21, 13, 8, 4, 3, 3, 3, 13 }, { 70,
				8, 3, 372, 20, 16, 1, 6, 4, 5, 4, 12 }, { 70, 8, 4, 350, 20, 15, 1, 6, 4, 5, 4, 12 }, { 70, 8, 5, 328, 20, 14, 8, 4, 3, 3,
				3, 13 }, { 70, 8, 6, 306, 20, 13, 8, 4, 3, 3, 3, 13 }, { 70, 8, 7, 284, 20, 12, 8, 3, 3, 5, 3, 11 }, { 70, 8, 8, 262, 20,
				11, 8, 3, 3, 5, 3, 11 }, { 70, 8, 9, 371, 19, 16, 1, 6, 4, 5, 4, 12 }, { 70, 8, 10, 393, 19, 17, 1, 3, 19, 0, 5, 14 }, { 70,
				8, 11, 349, 19, 15, 1, 6, 4, 5, 4, 12 }, { 70, 8, 12, 327, 19, 14, 8, 8, 3, 2, 3, 12 }, { 70, 8, 13, 305, 19, 13, 8, 8, 3,
				2, 3, 12 }, { 70, 8, 14, 283, 19, 12, 8, 7, 4, 2, 4, 11 }, { 70, 8, 15, 261, 19, 11, 8, 7, 4, 2, 4, 11 }, { 70, 9, 0, 370,
				18, 16, 1, 7, 6, 6, 6, 11 }, { 70, 9, 1, 392, 18, 17, 1, 4, 6, 4, 6, 9 }, { 70, 9, 2, 414, 18, 18, 1, 4, 6, 4, 6, 9 }, { 70,
				9, 3, 348, 18, 15, 1, 7, 6, 6, 6, 11 }, { 70, 9, 4, 326, 18, 14, 8, 8, 3, 2, 3, 12 }, { 70, 9, 5, 304, 18, 13, 8, 8, 3, 2,
				3, 12 }, { 70, 9, 6, 282, 18, 12, 8, 7, 4, 2, 4, 11 }, { 70, 9, 7, 260, 18, 11, 8, 7, 4, 2, 4, 11 }, { 70, 9, 8, 369, 17,
				16, 1, 7, 6, 6, 6, 11 }, { 70, 9, 9, 391, 17, 17, 1, 4, 6, 4, 6, 9 }, { 70, 9, 10, 413, 17, 18, 1, 4, 6, 4, 6, 9 }, { 70, 9,
				11, 435, 17, 19, 1, 1, 5, 7, 5, 13 }, { 70, 9, 12, 347, 17, 15, 1, 7, 6, 6, 6, 11 }, { 70, 9, 13, 325, 17, 14, 8, 12, 7, 4,
				7, 11 }, { 70, 9, 14, 303, 17, 13, 8, 12, 7, 4, 7, 11 }, { 70, 9, 15, 281, 17, 12, 8, 11, 8, 5, 8, 15 }, { 70, 10, 0, 456,
				16, 20, 1, 2, 5, 4, 5, 12 }, { 70, 10, 1, 434, 16, 19, 1, 2, 5, 4, 5, 12 }, { 70, 10, 2, 412, 16, 18, 1, 5, 3, 1, 3, 15 }, {
				70, 10, 3, 390, 16, 17, 1, 5, 3, 1, 3, 15 }, { 70, 10, 4, 368, 16, 16, 1, 8, 8, 2, 8, 10 }, { 70, 10, 5, 346, 16, 15, 1, 8,
				8, 2, 8, 10 }, { 70, 10, 6, 324, 16, 14, 8, 12, 7, 4, 7, 11 }, { 70, 10, 7, 302, 16, 13, 8, 12, 7, 4, 7, 11 }, { 70, 10, 8,
				280, 16, 12, 8, 11, 8, 5, 8, 15 }, { 70, 10, 9, 258, 16, 11, 8, 11, 8, 5, 8, 15 }, { 70, 10, 10, 455, 15, 20, 1, 2, 5, 4, 5,
				12 }, { 70, 10, 11, 433, 15, 19, 1, 2, 5, 4, 5, 12 }, { 70, 10, 12, 411, 15, 18, 1, 5, 3, 1, 3, 15 }, { 70, 10, 13, 389, 15,
				17, 1, 5, 3, 1, 3, 15 }, { 70, 10, 14, 367, 15, 16, 1, 8, 8, 2, 8, 10 }, { 70, 10, 15, 345, 15, 15, 1, 8, 8, 2, 8, 10 }, {
				70, 13, 0, 323, 15, 14, 8, 20, 8, 3, 8, 9 }, { 70, 13, 1, 301, 15, 13, 8, 19, 10, 0, 10, 9 }, { 70, 13, 2, 279, 15, 12, 8,
				18, 10, 1, 10, 8 }, { 70, 13, 3, 257, 15, 11, 8, 17, 9, 1, 9, 8 }, { 70, 13, 4, 410, 14, 18, 2, 5, 4, 7, 4, 14 }, { 70, 13,
				5, 432, 14, 19, 2, 5, 4, 7, 4, 14 }, { 70, 13, 6, 454, 14, 20, 2, 1, 3, 0, 3, 14 }, { 70, 13, 7, 388, 14, 17, 2, 9, 5, 5, 5,
				15 }, { 70, 13, 8, 366, 14, 16, 2, 9, 5, 5, 5, 15 }, { 70, 13, 9, 344, 14, 15, 2, 13, 8, 7, 8, 11 }, { 70, 13, 10, 322, 14,
				14, 1, 9, 8, 4, 8, 8 }, { 70, 13, 11, 300, 14, 13, 0, 0, 0, 0, 0, 0 }, { 70, 13, 12, 431, 13, 19, 2, 5, 4, 7, 4, 14 }, { 70,
				13, 13, 453, 13, 20, 2, 1, 3, 0, 3, 14 }, { 70, 13, 14, 475, 13, 21, 2, 1, 3, 0, 3, 14 }, { 70, 13, 15, 409, 13, 18, 2, 5,
				4, 7, 4, 14 }, { 70, 14, 0, 365, 13, 16, 2, 9, 5, 5, 5, 15 }, { 70, 14, 1, 343, 13, 15, 2, 14, 8, 6, 8, 12 }, { 70, 14, 2,
				321, 13, 14, 0, 0, 0, 0, 0, 0 }, { 70, 14, 3, 452, 12, 20, 2, 2, 4, 6, 4, 15 },
		{ 70, 14, 4, 474, 12, 21, 2, 2, 4, 6, 4, 15 }, { 70, 14, 5, 430, 12, 19, 2, 6, 6, 7, 6, 8 }, { 70, 14, 6, 408, 12, 18, 2, 6, 6, 7,
				6, 8 }, { 70, 14, 7, 386, 12, 17, 2, 10, 7, 7, 7, 10 }, { 70, 14, 8, 364, 12, 16, 2, 10, 7, 7, 7, 10 }, { 70, 14, 9, 342,
				12, 15, 2, 15, 7, 5, 7, 8 }, { 70, 14, 10, 451, 11, 20, 2, 2, 4, 6, 4, 15 }, { 70, 14, 11, 473, 11, 21, 2, 2, 4, 6, 4, 15 },
		{ 70, 14, 12, 429, 11, 19, 2, 6, 6, 7, 6, 8 }, { 70, 14, 13, 407, 11, 18, 2, 6, 6, 7, 6, 8 }, { 70, 14, 14, 385, 11, 17, 2, 10, 7,
				7, 7, 10 }, { 70, 14, 15, 363, 11, 16, 2, 10, 7, 7, 7, 10 }, { 70, 15, 0, 123, 13, 5, 6, 12, 19, 6, 19, 14 }, { 70, 15, 1,
				38, 16, 1, 7, 6, 18, 3, 18, 9 }, { 70, 15, 2, 241, 21, 10, 8, 2, 3, 4, 3, 10 },
		{ 70, 15, 3, 259, 17, 11, 8, 11, 8, 5, 8, 15 }, { 70, 15, 4, 387, 13, 17, 2, 9, 5, 5, 5, 15 }, { 70, 15, 5, 341, 11, 15, 2, 16, 7,
				6, 7, 9 }, { 70, 15, 6, 360, 8, 16, 2, 12, 16, 1, 16, 8 }, { 70, 15, 7, 445, 5, 20, 3, 6, 16, 2, 16, 11 }, { 70, 15, 8, 242,
				0, 11, 4, 2, 18, 2, 18, 11 }, { 70, 15, 9, 224, 4, 10, 4, 11, 18, 7, 18, 13 }, { 70, 15, 10, 96, 8, 4, 6, 9, 3, 7, 3, 9 }, {
				70, 15, 11, 142, 10, 6, 6, 16, 15, 3, 15, 12 }, { 71, 3, 0, 340, 10, 15, 2, 17, 14, 3, 14, 9 }, { 71, 3, 1, 362, 10, 16, 2,
				11, 15, 0, 15, 8 }, { 71, 3, 2, 384, 10, 17, 2, 11, 15, 0, 15, 8 }, { 71, 3, 3, 406, 10, 18, 2, 7, 16, 0, 16, 9 }, { 71, 3,
				4, 428, 10, 19, 2, 7, 16, 0, 16, 9 }, { 71, 3, 5, 472, 10, 21, 2, 3, 17, 0, 17, 8 }, { 71, 3, 6, 450, 10, 20, 2, 3, 17, 0,
				17, 8 }, { 71, 3, 7, 339, 9, 15, 2, 18, 14, 4, 14, 8 }, { 71, 3, 8, 361, 9, 16, 2, 11, 15, 0, 15, 8 }, { 71, 3, 9, 383, 9,
				17, 2, 11, 15, 0, 15, 8 }, { 71, 3, 10, 405, 9, 18, 2, 7, 16, 0, 16, 9 }, { 71, 3, 11, 427, 9, 19, 2, 7, 16, 0, 16, 9 }, {
				71, 3, 12, 471, 9, 21, 2, 3, 17, 0, 17, 8 }, { 71, 3, 13, 449, 9, 20, 2, 3, 17, 0, 17, 8 }, { 71, 3, 14, 316, 8, 14, 0, 0,
				0, 0, 0, 0 }, { 71, 3, 15, 338, 8, 15, 2, 19, 14, 7, 14, 12 }, { 71, 4, 0, 382, 8, 17, 2, 12, 16, 1, 16, 8 }, { 71, 4, 1,
				404, 8, 18, 2, 8, 17, 1, 18, 14 }, { 71, 4, 2, 470, 8, 21, 2, 4, 19, 1, 19, 9 },
		{ 71, 4, 3, 448, 8, 20, 2, 4, 19, 1, 19, 9 }, { 71, 4, 4, 426, 8, 19, 2, 8, 17, 1, 18, 14 }, { 71, 4, 5, 293, 7, 13, 0, 0, 0, 0, 0,
				0 }, { 71, 4, 6, 315, 7, 14, 3, 9, 13, 7, 13, 10 }, { 71, 4, 7, 337, 7, 15, 2, 20, 14, 6, 14, 11 }, { 71, 4, 8, 359, 7, 16,
				2, 12, 16, 1, 16, 8 }, { 71, 4, 9, 381, 7, 17, 2, 12, 16, 1, 16, 8 }, { 71, 4, 10, 447, 7, 20, 2, 4, 19, 1, 19, 9 }, { 71,
				4, 11, 425, 7, 19, 2, 8, 17, 1, 18, 14 }, { 71, 4, 12, 403, 7, 18, 2, 8, 17, 1, 18, 14 }, { 71, 4, 13, 248, 6, 11, 4, 16,
				10, 4, 10, 13 }, { 71, 4, 14, 270, 6, 12, 4, 15, 10, 2, 10, 10 }, { 71, 4, 15, 292, 6, 13, 4, 14, 10, 3, 10, 11 }, { 71, 5,
				0, 314, 6, 14, 4, 13, 13, 6, 13, 9 }, { 71, 5, 1, 336, 6, 15, 3, 8, 13, 5, 13, 8 }, { 71, 5, 2, 358, 6, 16, 3, 8, 13, 5, 13,
				8 }, { 71, 5, 3, 380, 6, 17, 3, 7, 18, 6, 18, 15 }, { 71, 5, 4, 402, 6, 18, 3, 7, 18, 6, 18, 15 }, { 71, 5, 5, 424, 6, 19,
				3, 6, 16, 2, 16, 11 }, { 71, 5, 6, 446, 6, 20, 3, 6, 16, 2, 16, 11 }, { 71, 5, 7, 247, 5, 11, 4, 10, 14, 5, 14, 13 }, { 71,
				5, 8, 269, 5, 12, 4, 10, 14, 5, 14, 13 }, { 71, 5, 9, 291, 5, 13, 4, 9, 14, 2, 14, 10 }, { 71, 5, 10, 313, 5, 14, 4, 9, 14,
				2, 14, 10 }, { 71, 5, 11, 335, 5, 15, 3, 8, 13, 5, 13, 8 }, { 71, 5, 12, 357, 5, 16, 3, 8, 13, 5, 13, 8 }, { 71, 5, 13, 379,
				5, 17, 3, 7, 18, 6, 18, 15 }, { 71, 5, 14, 401, 5, 18, 3, 7, 18, 6, 18, 15 },
		{ 71, 5, 15, 423, 5, 19, 3, 6, 16, 2, 16, 11 }, { 71, 6, 0, 246, 4, 11, 4, 10, 14, 5, 14, 13 }, { 71, 6, 1, 268, 4, 12, 4, 10, 14,
				5, 14, 13 }, { 71, 6, 2, 290, 4, 13, 4, 9, 14, 2, 14, 10 }, { 71, 6, 3, 312, 4, 14, 4, 9, 14, 2, 14, 10 }, { 71, 6, 4, 334,
				4, 15, 3, 5, 15, 1, 15, 9 }, { 71, 6, 5, 422, 4, 19, 3, 3, 17, 3, 17, 9 }, { 71, 6, 6, 400, 4, 18, 3, 4, 16, 3, 16, 10 }, {
				71, 6, 7, 378, 4, 17, 3, 4, 16, 3, 16, 10 }, { 71, 6, 8, 356, 4, 16, 3, 5, 15, 1, 15, 9 }, { 71, 6, 9, 245, 3, 11, 4, 6, 17,
				6, 17, 12 }, { 71, 6, 10, 267, 3, 12, 4, 6, 17, 6, 17, 12 }, { 71, 6, 11, 289, 3, 13, 4, 5, 18, 5, 18, 12 }, { 71, 6, 12,
				311, 3, 14, 4, 5, 18, 5, 18, 12 }, { 71, 6, 13, 333, 3, 15, 3, 5, 15, 1, 15, 9 }, { 71, 6, 14, 399, 3, 18, 3, 4, 16, 3, 16,
				10 }, { 71, 6, 15, 377, 3, 17, 3, 4, 16, 3, 16, 10 }, { 71, 7, 0, 355, 3, 16, 3, 5, 15, 1, 15, 9 }, { 71, 7, 1, 244, 2, 11,
				4, 6, 17, 6, 17, 12 }, { 71, 7, 2, 266, 2, 12, 4, 6, 17, 6, 17, 12 }, { 71, 7, 3, 288, 2, 13, 4, 5, 18, 5, 18, 12 }, { 71,
				7, 4, 310, 2, 14, 4, 5, 18, 5, 18, 12 }, { 71, 7, 5, 332, 2, 15, 3, 2, 17, 2, 17, 11 }, { 71, 7, 6, 376, 2, 17, 3, 1, 17, 4,
				17, 10 }, { 71, 7, 7, 354, 2, 16, 3, 2, 17, 2, 17, 11 }, { 71, 7, 8, 243, 1, 11, 4, 2, 18, 2, 18, 11 }, { 71, 7, 9, 265, 1,
				12, 4, 2, 18, 2, 18, 11 }, { 71, 7, 10, 287, 1, 13, 4, 1, 19, 3, 19, 11 }, { 71, 7, 11, 309, 1, 14, 4, 1, 19, 3, 19, 11 }, {
				71, 7, 12, 331, 1, 15, 3, 2, 17, 2, 17, 11 }, { 71, 7, 13, 353, 1, 16, 3, 2, 17, 2, 17, 11 }, { 71, 7, 14, 286, 0, 13, 4, 1,
				19, 3, 19, 11 }, { 71, 7, 15, 264, 0, 12, 4, 2, 18, 2, 18, 11 }, { 71, 8, 0, 220, 0, 10, 4, 3, 19, 4, 19, 12 }, { 71, 8, 1,
				198, 0, 9, 4, 3, 19, 4, 19, 12 }, { 71, 8, 2, 176, 0, 8, 4, 4, 17, 5, 17, 13 },
		{ 71, 8, 3, 111, 1, 5, 5, 6, 16, 5, 16, 12 }, { 71, 8, 4, 133, 1, 6, 5, 6, 16, 5, 16, 12 }, { 71, 8, 5, 155, 1, 7, 4, 4, 17, 5, 17,
				13 }, { 71, 8, 6, 177, 1, 8, 4, 4, 17, 5, 17, 13 }, { 71, 8, 7, 199, 1, 9, 4, 3, 19, 4, 19, 12 }, { 71, 8, 8, 221, 1, 10, 4,
				3, 19, 4, 19, 12 }, { 71, 8, 9, 112, 2, 5, 5, 6, 16, 5, 16, 12 }, { 71, 8, 10, 90, 2, 4, 5, 3, 15, 7, 15, 15 }, { 71, 8, 11,
				134, 2, 6, 5, 6, 16, 5, 16, 12 }, { 71, 8, 12, 156, 2, 7, 4, 8, 16, 4, 16, 13 },
		{ 71, 8, 13, 178, 2, 8, 4, 8, 16, 4, 16, 13 }, { 71, 8, 14, 200, 2, 9, 4, 7, 18, 4, 18, 10 }, { 71, 8, 15, 222, 2, 10, 4, 7, 18, 4,
				18, 10 }, { 71, 9, 0, 113, 3, 5, 5, 7, 16, 7, 16, 14 }, { 71, 9, 1, 91, 3, 4, 5, 4, 17, 7, 17, 14 }, { 71, 9, 2, 69, 3, 3,
				5, 4, 17, 7, 17, 14 }, { 71, 9, 3, 135, 3, 6, 5, 7, 16, 7, 16, 14 }, { 71, 9, 4, 157, 3, 7, 4, 8, 16, 4, 16, 13 }, { 71, 9,
				5, 179, 3, 8, 4, 8, 16, 4, 16, 13 }, { 71, 9, 6, 201, 3, 9, 4, 7, 18, 4, 18, 10 }, { 71, 9, 7, 223, 3, 10, 4, 7, 18, 4, 18,
				10 }, { 71, 9, 8, 114, 4, 5, 5, 7, 16, 7, 16, 14 }, { 71, 9, 9, 92, 4, 4, 5, 4, 17, 7, 17, 14 }, { 71, 9, 10, 70, 4, 3, 5,
				4, 17, 7, 17, 14 }, { 71, 9, 11, 48, 4, 2, 5, 1, 15, 6, 15, 14 }, { 71, 9, 12, 136, 4, 6, 5, 7, 16, 7, 16, 14 }, { 71, 9,
				13, 158, 4, 7, 4, 12, 15, 2, 15, 10 }, { 71, 9, 14, 180, 4, 8, 4, 12, 15, 2, 15, 10 }, { 71, 9, 15, 202, 4, 9, 4, 11, 18, 7,
				18, 13 }, { 71, 10, 0, 27, 5, 1, 5, 2, 15, 6, 15, 14 }, { 71, 10, 1, 49, 5, 2, 5, 2, 15, 6, 15, 14 }, { 71, 10, 2, 71, 5, 3,
				5, 5, 16, 6, 16, 15 }, { 71, 10, 3, 93, 5, 4, 5, 5, 16, 6, 16, 15 }, { 71, 10, 4, 115, 5, 5, 5, 8, 15, 5, 15, 13 }, { 71,
				10, 5, 137, 5, 6, 5, 8, 15, 5, 15, 13 }, { 71, 10, 6, 159, 5, 7, 4, 12, 15, 2, 15, 10 }, { 71, 10, 7, 181, 5, 8, 4, 12, 15,
				2, 15, 10 }, { 71, 10, 8, 203, 5, 9, 4, 11, 18, 7, 18, 13 }, { 71, 10, 9, 225, 5, 10, 4, 11, 18, 7, 18, 13 }, { 71, 10, 10,
				28, 6, 1, 5, 2, 15, 6, 15, 14 }, { 71, 10, 11, 50, 6, 2, 5, 2, 4, 0, 4, 9 }, { 71, 10, 12, 72, 6, 3, 5, 5, 16, 6, 16, 15 },
		{ 71, 10, 13, 94, 6, 4, 5, 5, 16, 6, 16, 15 }, { 71, 10, 14, 116, 6, 5, 5, 8, 15, 5, 15, 13 }, { 71, 10, 15, 138, 6, 6, 5, 8, 15, 5,
				15, 13 }, { 71, 13, 0, 160, 6, 7, 4, 20, 14, 1, 14, 14 }, { 71, 13, 1, 182, 6, 8, 4, 19, 10, 6, 10, 14 }, { 71, 13, 2, 204,
				6, 9, 4, 18, 10, 7, 10, 15 }, { 71, 13, 3, 226, 6, 10, 4, 17, 10, 5, 10, 12 }, { 71, 13, 4, 73, 7, 3, 6, 5, 18, 0, 17, 15 },
		{ 71, 13, 5, 51, 7, 2, 6, 5, 18, 0, 17, 15 }, { 71, 13, 6, 29, 7, 1, 6, 1, 3, 6, 3, 8 }, { 71, 13, 7, 95, 7, 4, 6, 9, 3, 7, 3, 9 },
		{ 71, 13, 8, 117, 7, 5, 6, 9, 3, 7, 3, 9 }, { 71, 13, 9, 139, 7, 6, 6, 13, 13, 0, 13, 14 }, { 71, 13, 10, 161, 7, 7, 5, 9, 14, 0,
				14, 15 }, { 71, 13, 11, 183, 7, 8, 0, 0, 0, 0, 0, 0 }, { 71, 13, 12, 52, 8, 2, 6, 5, 18, 0, 17, 15 }, { 71, 13, 13, 30, 8,
				1, 6, 1, 3, 6, 3, 8 }, { 71, 13, 14, 8, 8, 0, 6, 1, 3, 6, 3, 8 }, { 71, 13, 15, 74, 8, 3, 6, 5, 18, 0, 17, 15 }, { 71, 14,
				0, 118, 8, 5, 6, 9, 3, 7, 3, 9 }, { 71, 14, 1, 140, 8, 6, 6, 14, 13, 1, 13, 13 },
		{ 71, 14, 2, 162, 8, 7, 0, 0, 0, 0, 0, 0 }, { 71, 14, 3, 31, 9, 1, 6, 2, 13, 3, 13, 15 },
		{ 71, 14, 4, 9, 9, 0, 6, 2, 13, 3, 13, 15 }, { 71, 14, 5, 53, 9, 2, 6, 6, 13, 4, 13, 12 }, { 71, 14, 6, 75, 9, 3, 6, 6, 13, 4, 13,
				12 }, { 71, 14, 7, 97, 9, 4, 6, 10, 13, 2, 13, 11 }, { 71, 14, 8, 119, 9, 5, 6, 10, 13, 2, 13, 11 }, { 71, 14, 9, 141, 9, 6,
				6, 15, 15, 4, 15, 11 }, { 71, 14, 10, 32, 10, 1, 6, 2, 13, 3, 13, 15 }, { 71, 14, 11, 10, 10, 0, 6, 2, 13, 3, 13, 15 }, {
				71, 14, 12, 54, 10, 2, 6, 6, 13, 4, 13, 12 }, { 71, 14, 13, 76, 10, 3, 6, 6, 13, 4, 13, 12 }, { 71, 14, 14, 98, 10, 4, 6,
				10, 13, 2, 13, 11 }, { 71, 14, 15, 120, 10, 5, 6, 10, 13, 2, 13, 11 } };

int getMatchingHodoChannel(int xx, int yy, int layer);
int getMatchingHodoSlot(int xx, int yy, int layer);
int getCaloIdxFromXY(int xx, int yy);
int getCaloIdxFromCrateSlotChannel(int crate, int slot, int channel);
int getROCFromXY(int xx, int yy);
void getCaloXYfromIdx(int idx,int &xx,int &yy);
/*Just for debugging*/
int getXRecfromXVTP(int xvtp);
int getYRecfromYVTP(int yvtp);


#endif /* FTTRANS_H_ */
