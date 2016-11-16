#include "GetColor.hpp"

std::unordered_map<GC, Color> GetColor = {
	{ GC::PINK, Color(212, 0, 83) },
	{ GC::CYAN, Color(0, 246, 235) },
	{ GC::ORANGE, Color(255, 138, 47) },
	{ GC::PURPLE, Color(59, 7, 86) },
	{ GC::YELLOW, Color(221, 210, 12) },
	{ GC::NAVY, Color(0, 49, 74) },
	{ GC::GREEN, Color(57, 255, 82) },
	{ GC::BLUE, Color(74, 98, 255) },
	{ GC::SUNLIGHT, Color(196, 248, 169) },
	{ GC::TOMATOSAUCE, Color(199, 26, 29) },
	{ GC::MUSTARD, Color(255, 189, 33) },
	{ GC::BUBBLEGUM, Color(255, 121, 216) },
	{ GC::CHEWEDBUBBLEGUM, Color(196, 0, 129) },
	{ GC::INDIGOPRIDE, Color(72, 0, 193) },
	{ GC::LEMONGRASS, Color(131, 235, 0) },
	{ GC::TURQUOISE, Color(0, 234, 174) },
	{ GC::FOREST, Color(51, 83, 0) },
	{ GC::SPIDERMANRED, Color(255, 42, 30) },
	{ GC::SPIDERMANBLUE, Color(35, 40, 255) },
	{ GC::CLOUD, Color(117, 255, 230) },
	{ GC::PEACH, Color(255, 162, 162) },
	{ GC::MAROON, Color(122, 0, 91) },
	{ GC::VOMIT, Color(181, 158, 0) },
	{ GC::ICE, Color(122, 149, 253) },
	{ GC::BURGANDY, Color(93, 0, 4) },
	{ GC::LAVENDER, Color(154, 86, 255) },
	{ GC::NEONGREEN, Color(142, 240, 0) }, 
	{ GC::SHALLOWSEA, Color(90, 83, 255) },
	{ GC::ELECTRICITY, Color(255, 255, 68) },
	{ GC::COTTONCANDY, Color(255, 75, 101) },
	{ GC::SEAFOAM, Color(136, 255, 184) },
	{ GC::GOLD, Color(255, 167, 31) },
	{ GC::IRONGRIT, Color(138, 179, 243) },
	{ GC::CHERRY, Color(255, 29, 48) },
	{ GC::LEATHER, Color(225, 109, 0) },
	{ GC::MOSS, Color(0, 211, 25) },
	{ GC::DIAMONDSHINE, Color(157, 255, 241) },
	{ GC::OPENSIGN, Color(192, 0, 212) },
	{ GC::FAKEINDIGO, Color(80, 10, 255) },
	{ GC::RUST, Color(255, 103, 68) },
	{ GC::FLUFFPINK, Color(255, 114, 160) },
	{ GC::ANGRYBLUE, Color(4, 26, 255) },
	{ GC::WARNING, Color(228, 57, 15) },
	{ GC::BABYGREEN, Color(79, 255, 105) },
	{ GC::STEELBLUE, Color(46, 150, 225) },
	{ GC::COUPLEMONTHSWORNBASKETBALLORANGE, Color(190, 72, 0) },
	{ GC::ALIENWARE, Color(36, 255, 18) },
	{ GC::MOSSYAQUARIUM, Color(0, 227, 142) },
	{ GC::GOLDENGATERED, Color(255, 48, 31) },
	{ GC::SANDPAPER, Color(255, 191, 98) },
	{ GC::SUICIDEAD, Color(159, 0, 2) },
	{ GC::BRUISE, Color(59, 31, 103) },
	{ GC::HAPPYNESS, Color(255, 244, 69) },
	{ GC::SADNESS, Color(66, 0, 216) },

	{ GC::TRAFFICONE, Color(255, 139, 3) },
	{ GC::AQUAMARINE, Color(10, 206, 255) },
	{ GC::PARADELIGHTS, Color(255, 17, 40) },
	{ GC::PARADENIGHT, Color(168, 20, 126) },
	{ GC::EMERALD, Color(0, 254, 153) },
	{ GC::COALMINE, Color(173, 67, 0) },
	{ GC::STOICROCK, Color(255, 142, 113) },
	{ GC::TENSIONSENVELOPMENT, Color(214, 1, 255) },
	{ GC::CROW, Color(56, 0, 139) },
	{ GC::SKYFALL, Color(117, 194, 255) },
	{ GC::FLAMINGROCKET, Color(255, 87, 73) },
	{ GC::THELIGHTOFSPACE, Color(253, 255, 109) },
	{ GC::SATURN, Color(240, 217, 0) },
	{ GC::URANUSDEATH, Color(0, 225, 64) }, 
	{ GC::MARBLEGUMBALL, Color(19, 77, 255) },
	{ GC::LIPSTICK, Color(211, 0, 59) },
	{ GC::THEFORESTFIRE, Color(255, 63, 31) },
	{ GC::THEFORESTTHATBURNED, Color(92, 255, 84) },

	// Branch text
	//"LET YOU",
	{ GC::IFPLUTOWASAPLANET, Color(28, 229, 247) },

	//"DIVE AWAY",
	{ GC::PUMPKINPIE, Color(255, 132, 5) },
	{ GC::GREENPASTURE, Color(55, 122, 64) },
	//"FROM OUR",
	{ GC::WATERCOMBUSTION, Color(0, 59, 248) },
	{ GC::BADMAGMA, Color(133, 0, 44) },
	//"PAINFUL DAYS", 
	{ GC::DABOMB, Color(226, 255, 104) },
	{ GC::NUCLEARGLOW, Color(109, 161, 66) },
	//"USO DARAKE",
	{ GC::ILOVEYOU, Color(230, 0, 26) },
	{ GC::INANYEVENT, Color(222, 101, 115) },
	//"NO SABITA",
	{ GC::NEONFOLLOWER, Color(0, 250, 65) },
	{ GC::DARKNESSBEFALLS, Color(0, 161, 148) },
	//"HIBI WO",
	{ GC::MERCURYINMYDRINK, Color(13, 189, 255) },
	{ GC::NAKEDJUICE, Color(237, 81, 20) },
	//"UGATTE",
	{ GC::NORMALTORCH, Color(215, 217, 0) },
	{ GC::SOHOTITSBLUE, Color(110, 176, 235) },
	//"GET YOUR",
	{ GC::IMAGUY, Color(0, 23, 207) },
	{ GC::IMAGIRL, Color(195, 0, 193) },
	//"HIDDEN WAY",
	{ GC::SHITTYCHRISTMASRED, Color(220, 41, 0) },
	{ GC::SHITTYCHRISTMASGREEN, Color(23, 255, 148) },
	//"FROM OUR",
	{ GC::CACTUS, Color(102, 210, 0) },
	{ GC::DESERTSAND, Color(233, 114, 40) },
	//"FLAWLESS MAZE",
	{ GC::OYSTERFISH, Color(255, 122, 206) },
	{ GC::DEEPSEATOO, Color(0, 60, 140) },
	//"SAGASU",
	{ GC::MORNINGSTAR, Color(255, 115, 33) },
	{ GC::SKYRISE, Color(16, 141, 201) },
	//"WO",
	{ GC::ICKYJUICE, Color(0, 228, 120) },
	{ GC::BATTERYACID, Color(168, 210, 0) },
	//"O",
	{ GC::BORINGBROWNCHOCOLATE, Color(128, 98, 0) },
	{ GC::EXOTICPINKWRAPPER, Color(255, 48, 230) },
	//"O",
	{ GC::STRIVINGREACHINGBUTNOTSUCCEEDING, Color(231, 255, 159) },
	{ GC::MELLOWCONTENTION, Color(3, 211, 255) },
	//"O",
	{ GC::STUDYFORTHEFUTURE, Color(168, 118, 255) },
	{ GC::TRAPPEDROOM, Color(255, 149, 131) },
	//"O",
	{ GC::THEACTOFCARING, Color(250, 112, 152) },
	{ GC::ROOMMATESPEE, Color(255, 232, 93) },
	//"O",
	{ GC::GAYNESS, Color(235, 61, 255) },
	{ GC::SOPHISTICATION, Color(103, 0, 192) },
	//"WE'RE",
	{ GC::WHOAMI, Color(0, 167, 108) },
	{ GC::BUTTHEDECORATION, Color(255, 112, 67) },
	//"BREATHING",
	{ GC::BREATH, Color(0, 83, 197) },
	{ GC::BREATHING, Color(90, 222, 255) },
	//"IN",
	{ GC::ITHOUGHTITWOULDBEALRIGHT, Color(184, 250, 0) },
	{ GC::BUTTHEN, Color(220, 62, 48) },
	//"DUALIVE"
	{ GC::EVERYTHING, Color(0, 0, 0) },
	{ GC::FELLAPART, Color(255, 255, 255) }
};