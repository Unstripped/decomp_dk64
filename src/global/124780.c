#include "common.h"
#include "render.h"

// Data-only TU linked inside the global code: its .data (0x8071FA80-0x80721558 + 8-byte TU pad) sits
// between 11BC10's and 126260's .text (dk64.global.us.yaml `linker_section_order: .text`).
// Effect sprite sheets, each with its frameCount * width * height frame texture ids inline; gEffectGridAssets
// (119370) lists all 176 in this order.

EFFECT_GRID_ASSET(11) D_8071FA80 = {
    1, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 64, 64, 11,
    { 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 939 },
};
EFFECT_GRID_ASSET(11) D_8071FAAC = {
    2, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 64, 32, 11,
    { 940, 941, 942, 943, 944, 945, 946, 947, 948, 949, 950 },
};
EFFECT_GRID_ASSET(2) D_8071FAD8 = {
    3, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 32, 32, 2,
    { 951, 952 },
};
EFFECT_GRID_ASSET(2) D_8071FAF0 = {
    3, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 32, 32, 2,
    { 953, 954 },
};
EFFECT_GRID_ASSET(11) gEffectSpriteSparklesBlue = {
    4, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 11,
    { 5005, 5006, 5007, 5008, 5009, 5010, 5011, 5012, 5013, 5014, 5015 },
};
EFFECT_GRID_ASSET(6) gEffectSpriteImpactFlash = {
    5, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 44, 44, 6,
    { 5016, 5017, 5018, 5019, 5020, 5021 },
};
EFFECT_GRID_ASSET(16) gEffectSpriteBurstOrange = {
    6, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 48, 42, 16,
    { 5022, 5023, 5024, 5025, 5026, 5027, 5028, 5029, 5030, 5031, 5032, 5033, 5034, 5035, 5036, 5037 },
};
EFFECT_GRID_ASSET(1) D_8071FB88 = {
    7, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 16, 32, 1,
    { 5038 },
};
EFFECT_GRID_ASSET(10) gEffectSpriteDustPuffBrown = {
    8, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 10,
    { 5039, 5040, 5041, 5042, 5043, 5044, 5045, 5046, 5047, 5048 },
};
EFFECT_GRID_ASSET(11) gEffectSpriteBlast = {
    9, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 11,
    { 5049, 5050, 5051, 5052, 5053, 5054, 5055, 5056, 5057, 5058, 5059 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteRing = {
    10, 1, 1, G_IM_FMT_IA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5060 },
};
EFFECT_GRID_ASSET(16) gEffectSpriteWaterSplash = {
    11, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 64, 48, 16,
    { 5061, 5062, 5063, 5064, 5065, 5066, 5067, 5068, 5069, 5070, 5071, 5072, 5073, 5074, 5075, 5076 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteBubble = {
    13, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5077 },
};
EFFECT_GRID_ASSET(15) gEffectSpriteSparklePurple = {
    14, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 15,
    { 5078, 5079, 5080, 5081, 5082, 5083, 5084, 5085, 5084, 5083, 5082, 5081, 5080, 5079, 5078 },
};
EFFECT_GRID_ASSET(15) gEffectSpriteSparkleYellow = {
    15, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 15,
    { 5086, 5087, 5088, 5089, 5090, 5091, 5092, 5093, 5092, 5091, 5090, 5089, 5088, 5087, 5086 },
};
EFFECT_GRID_ASSET(15) gEffectSpriteSparkleGreen = {
    16, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 15,
    { 5094, 5095, 5096, 5097, 5098, 5099, 5100, 5101, 5100, 5099, 5098, 5097, 5096, 5095, 5094 },
};
EFFECT_GRID_ASSET(35) D_8071FCF4 = {
    17, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 35,
    {
        5078, 5079, 5080, 5081, 5082, 5083, 5084, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085,
        5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085, 5085,
        5085, 5085, 5085,
    },
};
EFFECT_GRID_ASSET(35) D_8071FD50 = {
    18, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 35,
    {
        5086, 5087, 5088, 5089, 5090, 5091, 5092, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093,
        5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093, 5093,
        5093, 5093, 5093,
    },
};
EFFECT_GRID_ASSET(35) D_8071FDAC = {
    19, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 35,
    {
        5094, 5095, 5096, 5097, 5098, 5099, 5100, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101,
        5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101, 5101,
        5101, 5101, 5101,
    },
};
EFFECT_GRID_ASSET(16) gEffectSpriteStarBurst = {
    20, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 64, 64, 16,
    { 5102, 5103, 5104, 5105, 5106, 5107, 5108, 5109, 5110, 5111, 5112, 5113, 5114, 5115, 5116, 5117 },
};
EFFECT_GRID_ASSET(9) D_8071FE3C = {
    21, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 9,
    { 5118, 5119, 5120, 5121, 5122, 5123, 5124, 5125, 5126 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBarrelDebrisDark = {
    22, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 16, 64, 8,
    { 5127, 5128, 5129, 5130, 5131, 5132, 5133, 5134 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBarrelDebrisLight = {
    23, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 16, 64, 8,
    { 5135, 5136, 5137, 5138, 5139, 5140, 5141, 5142 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBarrelDebrisPlank = {
    24, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 16, 64, 8,
    { 5143, 5144, 5145, 5146, 5147, 5148, 5149, 5150 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteWaterRipple = {
    25, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 48, 48, 8,
    { 5151, 5152, 5153, 5154, 5155, 5156, 5157, 5158 },
};
EFFECT_GRID_ASSET(8) sEffectImpactPuffConfig = {
    26, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5159, 5160, 5161, 5162, 5163, 5164, 5165, 5166 },
};
EFFECT_GRID_ASSET(10) gEffectSpriteDustPuff = {
    28, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 10,
    { 5167, 5168, 5169, 5170, 5171, 5172, 5173, 5174, 5175, 5176 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteStar = {
    29, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 1,
    { 5177 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteSleepZ = {
    30, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 1,
    { 5178 },
};
EFFECT_GRID_ASSET(1) D_8071FF70 = {
    32, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 64, 64, 1,
    { 1324 },
};
EFFECT_GRID_ASSET(1) D_8071FF88 = {
    33, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xCD, 0xCD, 0xFF, 0xFF, 1, 1, 16, 32, 1,
    { 5179 },
};
EFFECT_GRID_ASSET(15) sEffectSparkConfig = {
    38, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 15,
    { 5180, 5181, 5182, 5183, 5184, 5185, 5186, 5187, 5188, 5189, 5190, 5191, 5192, 5193, 5194 },
};
EFFECT_GRID_ASSET(28) gEffectSpriteMelonWobble = {
    39, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 28,
    {
        5195, 5196, 5197, 5198, 5199, 5200, 5201, 5202, 5201, 5200, 5199, 5198, 5197, 5196, 5195, 5196,
        5197, 5198, 5199, 5200, 5201, 5202, 5201, 5200, 5199, 5198, 5197, 5196,
    },
};
EFFECT_GRID_ASSET(16) gEffectSpriteMelonSpin = {
    40, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 16,
    { 5203, 5204, 5205, 5206, 5207, 5208, 5209, 5210, 5211, 5212, 5213, 5214, 5215, 5216, 5217, 5218 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteGlowRed = {
    41, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 1,
    { 5219 },
};
EFFECT_GRID_ASSET(16) gSparkEffectSprite = {
    42, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 16,
    { 5220, 5221, 5222, 5223, 5224, 5225, 5226, 5227, 5228, 5229, 5230, 5231, 5232, 5233, 5234, 5235 },
};
EFFECT_GRID_ASSET(16) gEffectSpritePeanut = {
    43, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 16,
    { 5236, 5237, 5238, 5239, 5240, 5241, 5242, 5243, 5244, 5245, 5246, 5247, 5248, 5249, 5250, 5251 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteMuzzleFlash = {
    44, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 1,
    { 5252 },
};
EFFECT_GRID_ASSET(16) gEffectSpritePeanutShard = {
    45, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 16, 16, 16,
    { 5253, 5254, 5255, 5256, 5257, 5258, 5259, 5260, 5261, 5262, 5263, 5264, 5265, 5266, 5267, 5268 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteFireBurst = {
    46, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 12,
    { 5269, 5270, 5271, 5272, 5273, 5274, 5275, 5276, 5277, 5278, 5279, 5280 },
};
EFFECT_GRID_ASSET(15) gEffectSpriteSmokePuff = {
    47, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 15,
    { 5194, 5193, 5192, 5191, 5190, 5189, 5188, 5187, 5186, 5185, 5184, 5183, 5182, 5181, 5180 },
};
EFFECT_GRID_ASSET(6) D_80720180 = {
    48, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 6,
    { 5281, 5282, 5283, 5284, 5285, 5286 },
};
EFFECT_GRID_ASSET(16) gEffectSpritePineapple = {
    49, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 48, 16,
    { 4837, 5287, 5288, 5289, 5290, 5291, 5292, 5293, 5294, 5295, 5296, 5297, 5298, 5299, 5300, 5301 },
};
EFFECT_GRID_ASSET(64) gEffectSpriteFlame = {
    50, 2, 2, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 16,
    {
        5302, 5303, 5304, 5305,
        5306, 5307, 5308, 5309,
        5310, 5311, 5312, 5313,
        5314, 5315, 5316, 5317,
        5318, 5319, 5320, 5321,
        5322, 5323, 5324, 5325,
        5326, 5327, 5328, 5329,
        5330, 5331, 5332, 5333,
        5334, 5335, 5336, 5337,
        5338, 5339, 5340, 5341,
        5342, 5343, 5344, 5345,
        5346, 5347, 5348, 5349,
        5350, 5351, 5352, 5353,
        5354, 5355, 5356, 5357,
        5358, 5359, 5360, 5361,
        5362, 5363, 5364, 5365,
    },
};
EFFECT_GRID_ASSET(16) gEffectSpriteOrangeGrenade = {
    51, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 16,
    { 5366, 5367, 5368, 5369, 5370, 5371, 5372, 5373, 5374, 5375, 5376, 5377, 5378, 5379, 5380, 5381 },
};
EFFECT_GRID_ASSET(16) gEffectSpriteGrape = {
    52, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 16,
    { 5382, 5383, 5384, 5385, 5386, 5387, 5388, 5389, 5390, 5391, 5392, 5393, 5394, 5395, 4833, 5396 },
};
EFFECT_GRID_ASSET(20) gEffectSpriteMelonSplat = {
    53, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 20,
    {
        5397, 5398, 5399, 5400, 5401, 5402, 5403, 5404, 5405, 5406, 5407, 5408, 5409, 5410, 5411, 5412,
        5413, 5414, 5415, 5416,
    },
};
EFFECT_GRID_ASSET(16) gEffectSpriteFuseSpark = {
    54, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 16,
    { 5417, 5418, 5419, 5420, 5421, 5422, 5423, 5424, 5425, 5426, 5427, 5428, 5429, 5430, 5431, 5432 },
};
EFFECT_GRID_ASSET(27) gEffectSpriteExplosion = {
    55, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 27,
    {
        5433, 5434, 5435, 5436, 5437, 5438, 5439, 5440, 5441, 5442, 5443, 5444, 5445, 5446, 5447, 5448,
        5449, 5450, 5451, 5452, 5453, 5454, 5455, 5456, 5457, 5458, 5459,
    },
};
EFFECT_GRID_ASSET(8) gEffectSpriteEmber = {
    56, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 8,
    { 5460, 5461, 5462, 5463, 5464, 5465, 5466, 5467 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteCoinRed = {
    57, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 48, 42, 8,
    { 256, 257, 258, 259, 260, 261, 262, 263 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteCoinGreen = {
    58, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 48, 42, 8,
    { 264, 265, 266, 267, 268, 269, 270, 271 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteCoinBlue = {
    59, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 48, 42, 8,
    { 248, 249, 250, 251, 252, 253, 254, 255 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteCoinYellow = {
    60, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 48, 42, 8,
    { 224, 225, 226, 227, 228, 229, 230, 231 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteCoinPurple = {
    61, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 48, 42, 8,
    { 216, 217, 218, 219, 220, 221, 222, 223 },
};
EFFECT_GRID_ASSET(8) D_80720464 = {
    62, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 44, 44, 8,
    { 955, 956, 957, 958, 959, 960, 961, 962 },
};
EFFECT_GRID_ASSET(16) gEffectSpriteFilm = {
    63, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 48, 42, 16,
    { 431, 432, 433, 434, 435, 436, 437, 438, 439, 440, 441, 442, 443, 444, 445, 446 },
};
EFFECT_GRID_ASSET(28) gEffectSpriteOrange = {
    64, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 32, 32, 28,
    {
        308, 309, 310, 311, 312, 313, 314, 315, 314, 313, 312, 311, 310, 309, 308, 309,
        310, 311, 312, 313, 314, 315, 314, 313, 312, 311, 310, 309,
    },
};
EFFECT_GRID_ASSET(8) gEffectSpriteCrystal = {
    65, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 40, 51, 8,
    { 375, 376, 377, 378, 379, 380, 381, 382 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteGoldenBanana = {
    66, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 44, 44, 12,
    { 5468, 5469, 5470, 5471, 5472, 5473, 5474, 5475, 5476, 5477, 5478, 5479 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaMedal = {
    68, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 44, 44, 8,
    { 5480, 5481, 5482, 5483, 5484, 5485, 5486, 5487 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaRed = {
    69, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 8,
    { 152, 153, 154, 155, 156, 157, 158, 159 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaGreen = {
    70, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 8,
    { 240, 241, 242, 243, 244, 245, 246, 247 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaBlue = {
    71, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 8,
    { 232, 233, 234, 235, 236, 237, 238, 239 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaYellow = {
    72, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 8,
    { 168, 169, 170, 171, 172, 173, 174, 175 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaPurple = {
    73, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 8,
    { 208, 209, 210, 211, 212, 213, 214, 215 },
};
EFFECT_GRID_ASSET(38) D_80720630 = {
    74, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 64, 32, 38,
    {
        5488, 5489, 5490, 5489, 5488, 5488, 5488, 5488, 5488, 5488, 5488, 5488, 5488, 5488, 5489, 5490,
        5489, 5488, 5489, 5490, 5489, 5488, 5488, 5488, 5488, 5488, 5488, 5488, 5488, 5488, 5488, 5488,
        5488, 5488, 5488, 5488, 5488, 5488,
    },
};
EFFECT_GRID_ASSET(1) D_80720690 = {
    75, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 64, 64, 1,
    { 963 },
};
EFFECT_GRID_ASSET(16) gEffectSpriteCoconut = {
    76, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 40, 51, 16,
    { 675, 676, 677, 678, 679, 680, 681, 682, 683, 684, 685, 686, 687, 688, 689, 690 },
};
EFFECT_GRID_ASSET(16) gEffectSpriteCoconutShard = {
    77, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 16, 16, 16,
    { 5491, 5492, 5493, 5494, 5495, 5496, 5497, 5498, 5499, 5500, 5501, 5502, 5503, 5504, 5505, 5506 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteMelonSlice = {
    78, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 48, 42, 12,
    { 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteShardGold = {
    79, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 12,
    { 5507, 5508, 5509, 5510, 5511, 5512, 5513, 5514, 5515, 5516, 5517, 5518 },
};
EFFECT_GRID_ASSET(32) gEffectSpriteCrate = {
    80, 2, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 32, 64, 16,
    {
        383, 384,
        385, 400,
        386, 401,
        387, 402,
        388, 403,
        389, 404,
        390, 405,
        391, 406,
        392, 407,
        393, 408,
        394, 409,
        395, 410,
        396, 411,
        397, 412,
        398, 413,
        399, 414,
    },
};
EFFECT_GRID_ASSET(8) gEffectSpriteDkCoin = {
    81, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 48, 42, 8,
    { 496, 497, 498, 499, 500, 501, 502, 503 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBlueprintBlue = {
    82, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 48, 42, 8,
    { 5519, 5520, 5521, 5522, 5523, 5524, 5525, 5526 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteCannonball = {
    83, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 48, 42, 12,
    { 5527, 5528, 5529, 5530, 5531, 5532, 5533, 5534, 5535, 5536, 5537, 5538 },
};
EFFECT_GRID_ASSET(8) D_80720830 = {
    89, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 40, 51, 8,
    { 375, 376, 377, 378, 379, 380, 381, 382 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteFeather = {
    90, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5539, 5540, 5541, 5542, 5543, 5544, 5545, 5546 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteGuitar = {
    91, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 40, 40, 1,
    { 5547 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteBongos = {
    92, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 40, 40, 1,
    { 5548 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteSaxophone = {
    93, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 40, 40, 1,
    { 5549 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteTriangle = {
    94, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 40, 40, 1,
    { 5550 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteTrombone = {
    95, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 40, 40, 1,
    { 5551 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteNotePairYellow = {
    96, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5552, 5553, 5554, 5555, 5556, 5557, 5558, 5559 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteNoteYellow = {
    97, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5560, 5561, 5562, 5563, 5564, 5565, 5566, 5567 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteNoteGreen = {
    98, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5568, 5569, 5570, 5571, 5572, 5573, 5574, 5575 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteNotePairPink = {
    99, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5576, 5577, 5578, 5579, 5580, 5581, 5582, 5583 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteNotePairRed = {
    100, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5584, 5585, 5586, 5587, 5588, 5589, 5590, 5591 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteNoteRed = {
    101, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5592, 5593, 5594, 5595, 5596, 5597, 5598, 5599 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteNotePairPaleBlue = {
    102, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5600, 5601, 5602, 5603, 5604, 5605, 5606, 5607 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBlueprintRed = {
    103, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 48, 42, 8,
    { 5608, 5609, 5610, 5611, 5612, 5613, 5614, 5615 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBlueprintGreen = {
    104, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 48, 42, 8,
    { 5616, 5617, 5618, 5619, 5620, 5621, 5622, 5623 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBlueprintYellow = {
    105, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 48, 42, 8,
    { 5624, 5625, 5626, 5627, 5628, 5629, 5630, 5631 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBlueprintPurple = {
    106, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 48, 42, 8,
    { 5632, 5633, 5634, 5635, 5636, 5637, 5638, 5639 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteGlintYellow = {
    107, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 8,
    { 5640, 5641, 5642, 5643, 5644, 5645, 5646, 5647 },
};
EFFECT_GRID_ASSET(1) D_80720AA0 = {
    108, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xCD, 0xCD, 0xFF, 0xFF, 0, 0, 16, 32, 1,
    { 964 },
};
EFFECT_GRID_ASSET(1) D_80720AB8 = {
    109, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 32, 32, 1,
    { 965 },
};
EFFECT_GRID_ASSET(1) D_80720AD0 = {
    110, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 8, 8, 1,
    { 966 },
};
EFFECT_GRID_ASSET(1) D_80720AE8 = {
    111, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 64, 64, 1,
    { 967 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteCloud = {
    112, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 48, 32, 8,
    { 5648, 5649, 5650, 5651, 5652, 5653, 5654, 5655 },
};
EFFECT_GRID_ASSET(16) gEffectSpriteLightningArc = {
    113, 2, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 8,
    { 5656, 5657, 5658, 5659, 5660, 5661, 5662, 5663, 5664, 5665, 5666, 5667, 5668, 5669, 5670, 5671 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteWaterDroplet = {
    114, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 16, 16, 1,
    { 5672 },
};
EFFECT_GRID_ASSET(1) D_80720B70 = {
    115, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 64, 64, 1,
    { 968 },
};
EFFECT_GRID_ASSET(1) D_80720B88 = {
    116, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 64, 64, 1,
    { 969 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteGrapeShard = {
    117, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 16, 16, 8,
    { 5673, 5674, 5675, 5676, 5677, 5678, 5679, 5680 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteGlintBlue = {
    118, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 32, 32, 8,
    { 970, 971, 972, 973, 974, 975, 976, 977 },
};
EFFECT_GRID_ASSET(27) gEffectSpriteSmokeCloud = {
    119, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 27,
    {
        5681, 5682, 5683, 5684, 5685, 5686, 5687, 5688, 5689, 5690, 5691, 5692, 5693, 5694, 5695, 5696,
        5697, 5698, 5699, 5700, 5701, 5702, 5703, 5704, 5705, 5706, 5707,
    },
};
EFFECT_GRID_ASSET(14) gControlStickSprite = {
    122, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 14,
    { 5708, 5709, 5710, 5711, 5712, 5713, 5714, 5715, 5714, 5713, 5712, 5711, 5710, 5709 },
};
EFFECT_GRID_ASSET(48) D_80720C64 = {
    123, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 48,
    {
        5716, 5717, 5718, 5719, 5720, 5721, 5722, 5723, 5724, 5725, 5726, 5727, 5728, 5729, 5730, 5731,
        5732, 5733, 5734, 5735, 5736, 5737, 5738, 5739, 5740, 5741, 5742, 5743, 5744, 5745, 5746, 5747,
        5748, 5749, 5750, 5751, 5752, 5753, 5754, 5755, 5756, 5757, 5758, 5759, 5760, 5761, 5762, 5763,
    },
};
EFFECT_GRID_ASSET(1) gEffectSpriteWaterDrip = {
    123, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 16, 32, 1,
    { 5764 },
};
EFFECT_GRID_ASSET(8) gAButtonSprite = {
    124, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5765, 5766, 5767, 5768, 5769, 5768, 5767, 5766 },
};
EFFECT_GRID_ASSET(8) gBButtonSprite = {
    125, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5770, 5771, 5772, 5773, 5774, 5773, 5772, 5771 },
};
EFFECT_GRID_ASSET(8) gZButtonSprite = {
    126, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5775, 5776, 5777, 5778, 5779, 5778, 5777, 5776 },
};
EFFECT_GRID_ASSET(8) gCDownButtonSprite = {
    127, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5780, 5781, 5782, 5783, 5784, 5783, 5782, 5781 },
};
EFFECT_GRID_ASSET(8) gCUpButtonSprite = {
    128, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5785, 5786, 5787, 5788, 5789, 5788, 5787, 5786 },
};
EFFECT_GRID_ASSET(8) D_80720DA4 = {
    129, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5790, 5791, 5792, 5793, 5794, 5793, 5792, 5791 },
};
EFFECT_GRID_ASSET(1) D_80720DC8 = {
    130, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 32, 32, 1,
    { 978 },
};
EFFECT_GRID_ASSET(16) gEffectSpriteBurstGreen = {
    131, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 48, 42, 16,
    { 5795, 5796, 5797, 5798, 5799, 5800, 5801, 5802, 5803, 5804, 5805, 5806, 5807, 5808, 5809, 5810 },
};
EFFECT_GRID_ASSET(2) gEffectSpriteTargetRing = {
    132, 2, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 64, 1,
    { 5811, 5812 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteGooGreen = {
    133, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 48, 42, 1,
    { 5813 },
};
EFFECT_GRID_ASSET(1) D_80720E44 = {
    134, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5814 },
};
EFFECT_GRID_ASSET(1) D_80720E5C = {
    135, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5815 },
};
EFFECT_GRID_ASSET(1) D_80720E74 = {
    136, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5816 },
};
EFFECT_GRID_ASSET(1) D_80720E8C = {
    137, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5817 },
};
EFFECT_GRID_ASSET(1) D_80720EA4 = {
    138, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 8, 1,
    { 5818 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteBananaBunchGreen = {
    139, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 12,
    { 830, 831, 832, 833, 834, 835, 836, 837, 838, 839, 840, 841 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteBananaBunchRed = {
    140, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 12,
    { 854, 855, 856, 857, 858, 859, 860, 861, 862, 863, 864, 865 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteBananaBunchBlue = {
    141, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 12,
    { 818, 819, 820, 821, 822, 823, 824, 825, 826, 827, 828, 829 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteBananaBunchYellow = {
    142, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 12,
    { 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteBananaBunchPurple = {
    143, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 44, 44, 12,
    { 842, 843, 844, 845, 846, 847, 848, 849, 850, 851, 852, 853 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaBalloonGreen = {
    144, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 8,
    { 5819, 5820, 5821, 5822, 5823, 5824, 5825, 5826 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaBalloonRed = {
    145, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 8,
    { 5827, 5828, 5829, 5830, 5831, 5832, 5833, 5834 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaBalloonYellow = {
    146, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 8,
    { 5835, 5836, 5837, 5838, 5839, 5840, 5841, 5842 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaBalloonBlue = {
    147, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 8,
    { 5843, 5844, 5845, 5846, 5847, 5848, 5849, 5850 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteBananaBalloonPurple = {
    148, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 8,
    { 5851, 5852, 5853, 5854, 5855, 5856, 5857, 5858 },
};
EFFECT_GRID_ASSET(8) gRButtonSprite = {
    149, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5859, 5860, 5861, 5862, 5863, 5862, 5861, 5860 },
};
EFFECT_GRID_ASSET(8) D_80721070 = {
    150, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5864, 5865, 5866, 5867, 5868, 5867, 5866, 5865 },
};
EFFECT_GRID_ASSET(8) gFairySprite = {
    151, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5869, 5870, 5871, 5872, 5873, 5874, 5875, 5876 },
};
EFFECT_GRID_ASSET(16) gEffectSpriteKey = {
    152, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 44, 44, 16,
    { 5877, 5878, 5879, 5880, 5881, 5882, 5883, 5884, 5885, 5886, 5887, 5888, 5889, 5890, 5891, 5892 },
};
EFFECT_GRID_ASSET(8) gCrownSprite = {
    153, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 44, 44, 8,
    { 5893, 5894, 5895, 5896, 5897, 5898, 5899, 5900 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteRareCoin = {
    154, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 44, 44, 8,
    { 5901, 5902, 5903, 5904, 3400, 5905, 5906, 5907 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteNintendoCoin = {
    155, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 44, 44, 8,
    { 5908, 5909, 5910, 5911, 3401, 5912, 5913, 5914 },
};
EFFECT_GRID_ASSET(2) gEffectSpriteNoSign = {
    156, 2, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 64, 1,
    { 5915, 5916 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteHeadphones = {
    157, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 40, 40, 8,
    { 979, 980, 981, 982, 983, 984, 985, 986 },
};
EFFECT_GRID_ASSET(1) D_80721194 = {
    158, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 32, 32, 1,
    { 987 },
};
EFFECT_GRID_ASSET(8) gStartButtonSprite = {
    128, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 8,
    { 5917, 5918, 5919, 5920, 5921, 5920, 5919, 5918 },
};
EFFECT_GRID_ASSET(14) gEffectSpriteQuestionMark = {
    160, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 32, 14,
    { 5922, 5923, 5924, 5925, 5926, 5927, 5928, 5929, 5928, 5927, 5926, 5925, 5924, 5923 },
};
EFFECT_GRID_ASSET(4) gEffectSpriteCandyHead = {
    161, 2, 2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5930, 5931, 5932, 5933 },
};
EFFECT_GRID_ASSET(4) gEffectSpriteCrankyHead = {
    162, 2, 2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 4999, 5000, 5001, 5002 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteSnideHead = {
    163, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 64, 32, 1,
    { 5934 },
};
EFFECT_GRID_ASSET(4) gEffectSpriteFunkyHead = {
    164, 2, 2, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5935, 5936, 5937, 5938 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteArrow = {
    165, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 16, 12,
    { 4910, 4911, 4912, 4913, 4914, 4915, 4916, 4917, 4918, 4919, 4920, 4921 },
};
EFFECT_GRID_ASSET(2) gEffectSpriteTwinkle = {
    199, 1, 2, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 1,
    { 3556, 3555 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteDebrisGrey = {
    172, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5939 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteDebrisGreen = {
    173, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5940 },
};
EFFECT_GRID_ASSET(6) gEffectSpriteLeaf = {
    175, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 16, 6,
    { 5941, 5942, 5943, 5944, 5945, 5946 },
};
EFFECT_GRID_ASSET(1) D_80721300 = {
    174, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 64, 64, 1,
    { 5947 },
};
EFFECT_GRID_ASSET(1) D_80721318 = {
    174, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 64, 64, 1,
    { 5948 },
};
EFFECT_GRID_ASSET(10) D_80721330 = {
    176, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xBE, 1, 1, 32, 32, 10,
    { 5949, 5950, 5951, 5952, 5953, 5954, 5955, 5956, 5957, 5958 },
};
EFFECT_GRID_ASSET(5) D_80721358 = {
    178, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 0, 64, 64, 5,
    { 988, 989, 990, 991, 992 },
};
EFFECT_GRID_ASSET(8) gEffectSpriteRainbowCoin = {
    179, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 48, 42, 8,
    { 5959, 5960, 5961, 5962, 5963, 5964, 5965, 5966 },
};
EFFECT_GRID_ASSET(15) gEffectSpriteGlowOrange = {
    180, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 15,
    { 5967, 5968, 5969, 5970, 5971, 5972, 5973, 5974, 5973, 5972, 5971, 5970, 5969, 5968, 5967 },
};
EFFECT_GRID_ASSET(8) D_807213D0 = {
    181, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 16, 16, 8,
    { 5975, 5976, 5977, 5978, 5979, 5980, 5981, 5982 },
};
EFFECT_GRID_ASSET(1) D_807213F4 = {
    87, 1, 1, G_IM_FMT_I, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 64, 64, 1,
    { 5003 },
};
EFFECT_GRID_ASSET(6) effectAssetPathTrail = {
    183, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 6,
    { 5983, 5984, 5985, 5986, 5987, 5988 },
};
EFFECT_GRID_ASSET(1) D_8072142C = {
    184, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 1, 1, 32, 32, 1,
    { 5989 },
};
EFFECT_GRID_ASSET(1) gEffectSpriteBarrelEnd = {
    185, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_32b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 32, 1,
    { 5990 },
};
EFFECT_GRID_ASSET(1) D_8072145C = {
    186, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 48, 42, 1,
    { 3229 },
};
EFFECT_GRID_ASSET(12) gEffectSpriteBananaBunchRainbow = {
    187, 1, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 44, 44, 12,
    { 5991, 5992, 5993, 5994, 5995, 5996, 5997, 5998, 5999, 6000, 3206, 6001 },
};
EFFECT_GRID_ASSET(2) gEffectSpriteDkHead = {
    189, 2, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 1,
    { 636, 635 },
};
EFFECT_GRID_ASSET(2) gEffectSpriteDiddyHead = {
    190, 2, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 1,
    { 633, 634 },
};
EFFECT_GRID_ASSET(2) gEffectSpriteLankyHead = {
    191, 2, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 1,
    { 631, 632 },
};
EFFECT_GRID_ASSET(2) gEffectSpriteTinyHead = {
    192, 2, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 1,
    { 630, 629 },
};
EFFECT_GRID_ASSET(2) gEffectSpriteChunkyHead = {
    193, 2, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 32, 64, 1,
    { 627, 628 },
};
EFFECT_GRID_ASSET(1) gCheckMarkSprite = {
    194, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 64, 64, 1,
    { 6002 },
};
EFFECT_GRID_ASSET(10) gEffectSpriteWrinkly = {
    195, 1, 1, G_IM_FMT_IA, G_IM_SIZ_8b, 0xFF, 0xFF, 0xFF, 0xFF, 0, 1, 64, 64, 10,
    { 6003, 6004, 6005, 6006, 6007, 6008, 6009, 6010, 6011, 6012 },
};
