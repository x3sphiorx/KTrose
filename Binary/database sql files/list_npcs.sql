-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 09:53 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `list_npcs`
-- 

DROP TABLE IF EXISTS `list_npcs`;
CREATE TABLE IF NOT EXISTS `list_npcs` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(255) NOT NULL default '',
  `type` int(11) default NULL,
  `map` int(11) default NULL,
  `dir` float default NULL,
  `x` float default NULL,
  `y` float default NULL,
  `dialogid` int(11) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=159 ;

-- 
-- Dumping data for table `list_npcs`
-- 

INSERT INTO `list_npcs` (`id`, `name`, `type`, `map`, `dir`, `x`, `y`, `dialogid`) VALUES 
(1, '[Livestock Farmer] Lampa', 1016, 1, 173.934, 5109.42, 5363.68, 116),
(2, '[Ferrell Guild Staff] Crow', 1004, 1, 6.067, 5094.38, 5259.9, 104),
(3, '[Ferrell Guild Staff] Ulysses', 1012, 1, 84.016, 5071.26, 5206.92, 112),
(4, '[Co-Founder of the Junon Order] Francis', 1003, 1, 157.957, 5080.3, 5066.28, 103),
(5, '[Righteous Crusader] Leonard', 1005, 1, 16.102, 5261.08, 5166.96, 105),
(6, '[Designer] Keenu', 1010, 1, 343.898, 5273.5, 5256.83, 110),
(7, '[Eccentric Inventor] Spero', 1011, 1, 14.293, 5212.36, 5254.66, 111),
(8, '[Tavern Owner] Sharlin', 1013, 1, 333.435, 5131.56, 5218.14, 113),
(9, '[Resident] Luth', 1015, 1, 270, 5130.61, 5154.58, 115),
(10, '[Guide] Lena', 1014, 1, 169.135, 5240.4, 5124.57, 114),
(11, '[Event Info] Judy', 1201, 1, 162.011, 5261.88, 5212.97, 305),
(12, '[Teleporter] Selladin', 1017, 1, 162.011, 5247.24, 5222.58, 117),
(13, '[Akram Kingdom Minister] Warren', 1002, 1, 178.499, 5208.78, 5112.94, 102),
(14, '[Village Chief] Cornell', 1001, 1, 183.008, 5217.51, 5113.18, 101),
(15, '[Cornell''s Grandson] Cheney', 1018, 1, 34.535, 5438.63, 5492.2, 118),
(16, '[Arumic Merchant] Tryteh', 1006, 1, 258.129, 5313.26, 5153.74, 106),
(17, '[Gypsy Jewel Seller] Mina', 1007, 1, 197.989, 5292.56, 5127.66, 107),
(18, '[Weapon Seller] Raffle', 1008, 1, 322.406, 5302.32, 5232.34, 108),
(19, '[Armor Seller] Carrion', 1009, 1, 275.984, 5313.53, 5198.14, 109),
(20, '[Keenu''s Daughter] Arisa', 1020, 1, 214.535, 5428.75, 5084.2, 120),
(21, '[Lena''s Sister] Shirley', 1019, 1, 333.435, 5510.14, 5293.33, 119),
(22, '[Righteous Crusader] Gawain', 1090, 2, 84.016, 5334.58, 5353.91, 190),
(23, '[Righteous Crusader] Huffe', 1111, 2, 90, 5334.84, 5345.81, 211),
(24, '[Clan Owner] Burtland', 1115, 2, 90, 5289.1, 5264.1, 215),
(25, '[Teleporter] Idiosel', 1119, 2, 270, 5343.67, 5177.36, 219),
(26, '[Founder of Junon Order] Raw', 1088, 2, 181.501, 5319.27, 5095.36, 188),
(27, '[Elder of Junon Order] Gorthein', 1109, 2, 181.501, 5325.54, 5095.31, 209),
(28, '[Guide] Eva', 1082, 2, 153.435, 5505.78, 5346.09, 182),
(29, '[Soldier] Odelo', 1116, 2, 0, 5507.31, 5397.4, 216),
(30, '[Soldier] Winters', 1117, 2, 0, 5522.99, 5397.75, 217),
(31, '[Mayor] Darren', 1081, 2, 178.499, 5514.48, 5238.2, 181),
(32, '[Event Info] Felice Fete', 1202, 2, 206.565, 5562, 5164.83, 306),
(33, '[Guide] Alphonso', 1118, 2, 178.499, 5520.56, 5063.66, 218),
(34, '[Historian] Jones', 1104, 2, 162.011, 5578.19, 4890.44, 204),
(35, '[Manager of Ferrell] Arothel', 1089, 2, 270, 5713.43, 5360.16, 189),
(36, '[Armor Merchant] Saki', 1094, 2, 258.129, 5721.8, 5290.79, 194),
(37, '[Ferrell Guild Staff] Charrs', 1110, 2, 270, 5713.38, 5368.71, 210),
(38, '[Gypsy Jewel Seller] Bellia', 1092, 2, 217.594, 5725.11, 5199.04, 192),
(39, '[Weapon Merchant] Crune', 1093, 2, 335.763, 5728.67, 5224.89, 193),
(40, '[Designer] Lisa', 1095, 2, 220.893, 5729.06, 5136.33, 195),
(41, '[Ferrell Guild Merchant] Mildun', 1096, 2, 165.707, 5673.16, 5193.89, 196),
(42, '[Tavern Owner] Harin', 1097, 2, 90, 5681.79, 5131.11, 197),
(43, '[Arumic Merchant] Chester', 1091, 2, 211.693, 5723.96, 5087.24, 191),
(44, '[Ferrell Guild Staff] Kiroth', 1098, 2, 275.984, 5603.58, 5058.1, 198),
(45, '[Ferrell Guild Staff] Hayen', 1099, 2, 258.129, 5603.77, 5046.12, 199),
(46, '[Ferrell Guild Staff] Itz', 1100, 2, 270, 5603.69, 5034.52, 200),
(47, '[Arumic Researcher] Carasia', 1112, 2, 197.989, 5730.57, 5094.06, 212),
(48, '[Livestock Farmer] Sicru', 1107, 2, 187.631, 5818.02, 5487.59, 207),
(49, '[Ferrell Guild Staff] Rooen', 1513, 3, 0, 5104.48, 5019.71, 303),
(50, '[Akram Minister] Rodath', 1086, 5, 90, 5155.07, 5279.92, 186),
(51, '[Akram Minister] Mel', 1087, 5, 270, 5247.07, 5279.96, 187),
(52, '[Akram Minister] Gamp', 1084, 6, 270, 5248.14, 5279.2, 187),
(53, '[Referee] Leum', 1113, 9, 0, 5199.99, 5390.04, 213),
(54, '[Referee] Pirre', 1114, 9, 180, 5201.59, 4765.69, 214),
(55, '[Akram Minister] Nell', 1085, 11, 84.016, 4953.37, 4992.35, 184),
(56, '[Akram Minister] Nell', 1085, 11, 10.865, 4978.48, 5478.6, 184),
(57, '[Akram Minister] Nell', 1085, 11, 337.957, 5455.57, 5478.99, 184),
(58, '[Akram Minister] Nell', 1085, 11, 335.763, 5521.94, 5020.66, 184),
(59, '[Akram Minister] Nell', 1085, 12, 84.016, 4953.37, 4992.35, 184),
(60, '[Akram Minister] Nell', 1085, 12, 10.865, 4978.48, 5478.6, 184),
(61, '[Akram Minister] Nell', 1085, 12, 337.957, 5455.57, 5478.99, 184),
(62, '[Akram Minister] Nell', 1085, 12, 335.763, 5521.94, 5020.66, 184),
(63, '[Akram Minister] Nell', 1085, 13, 84.016, 4953.37, 4992.35, 184),
(64, '[Akram Minister] Nell', 1085, 13, 10.865, 4978.48, 5478.6, 184),
(65, '[Akram Minister] Nell', 1085, 13, 337.957, 5455.57, 5478.99, 184),
(66, '[Akram Minister] Nell', 1085, 13, 335.763, 5521.94, 5020.66, 184),
(67, '[Clan House Soldier] Jason', 1162, 15, 183.008, 5205.79, 5129.92, 262),
(68, '[Clan House Manager] Kushard', 1161, 15, 0, 5200.16, 5209.81, 261),
(69, '[Clan House Soldier] Jason', 1162, 15, 181.501, 5204.57, 4970.37, 262),
(70, '[Clan House Manager] Kushard', 1161, 15, 0, 5200.13, 5051.79, 261),
(71, '[Clan House Soldier] Jason', 1162, 15, 181.501, 5203.89, 4809.55, 262),
(72, '[Clan House Manager] Kushard', 1161, 15, 0, 5200.16, 4890.67, 261),
(73, '[Clan House Manager] Kushard', 1161, 15, 0, 5360.21, 5210.15, 261),
(74, '[Clan House Soldier] Jason', 1162, 15, 180, 5363.94, 5130.38, 262),
(75, '[Clan House Soldier] Jason', 1162, 15, 180, 5364.04, 4970.33, 262),
(76, '[Clan House Manager] Kushard', 1161, 15, 0, 5360.2, 5051.41, 261),
(77, '[Clan House Soldier] Jason', 1162, 15, 183.008, 5363.85, 4810.42, 262),
(78, '[Clan House Manager] Kushard', 1161, 15, 0, 5360.25, 4890.3, 261),
(79, '[Clan House Soldier] Jason', 1162, 15, 183.008, 5524.3, 5129.46, 262),
(80, '[Clan House Manager] Kushard', 1161, 15, 0, 5520.19, 5211.31, 261),
(81, '[Clan House Soldier] Jason', 1162, 15, 183.008, 5523.83, 4970.15, 262),
(82, '[Clan House Manager] Kushard', 1161, 15, 0, 5520.18, 5051.41, 261),
(83, '[Clan House Soldier] Jason', 1162, 15, 181.501, 5523.67, 4810.61, 262),
(84, '[Clan House Manager] Kushard', 1161, 15, 0, 5520.16, 4891.07, 261),
(85, '[Visitor Guide] Arua''s Fairy', 1030, 20, 29.043, 5030.74, 5136.11, 0),
(86, '[Visitor Guide] Arua''s Fairy', 1030, 20, 160.035, 5141.14, 4730.24, 130),
(87, '[Visitor Guide] Arua''s Fairy', 1030, 20, 52.486, 5341.63, 5382.6, 130),
(88, '[Visitor Guide] Arua''s Fairy', 1030, 20, 360, 5695.39, 5166.66, 130),
(89, '[Visitor Guide] Arua''s Fairy', 1030, 20, 204.237, 5652.45, 4761.48, 130),
(90, '[Arumic Resercher] Lutis', 1051, 21, 160.035, 5118.14, 5374.91, 151),
(91, '[Cleric] Karitte', 1053, 21, 95.984, 5112.44, 5385.08, 153),
(92, '[Mountain Guide] Shannon', 1052, 21, 353.933, 5357.27, 5282.19, 152),
(93, '[Little Street Vendor] Pony', 1035, 22, 165.707, 5751.58, 5189.86, 135),
(94, '[Ferrell Guild Staff] Peron', 1511, 22, 9.228, 5832.2, 5315.54, 301),
(95, '[Akram Minister] Mairard', 1032, 22, 333.435, 5882.36, 5263.18, 132),
(96, '[Old Fisherman] Myad', 1037, 22, 252.423, 5868.2, 5137.12, 137),
(97, '[Smith] Ronk', 1034, 22, 16.102, 5779.71, 5276.76, 134),
(98, '[Ferrell Guild Staff] Seyon', 1036, 22, 342.011, 5796.58, 5278.06, 136),
(99, '[Visitor Guide] Ronway', 1031, 22, 153.435, 5763.28, 5169.43, 131),
(100, '[Village Chief] Gray', 1038, 22, 275.984, 5879.09, 5105.12, 138),
(101, '[Ferrell Guild Staff] Belz', 1061, 23, 270, 5358.63, 5058.99, 161),
(102, '[Smith] Punwell', 1062, 23, 24.237, 5340.65, 5070.26, 162),
(103, '[Little Street Vendor] Mile', 1063, 23, 307.514, 5356.41, 5043.28, 163),
(104, '[Weapon Craftsman] Mairath', 1064, 23, 180, 5349.02, 5033.95, 164),
(105, '[Ferrell Guild Merchant] Lina', 1071, 24, 293.031, 5567.26, 4927.03, 171),
(106, '[Gypsy Merchant] Methio', 1072, 24, 192.55, 5563.13, 4895.45, 172),
(107, '[Ikaness Staff] Orias', 1073, 24, 95.984, 5515.26, 4925.14, 173),
(108, '[Ikaness Staff] Shroon', 1121, 25, 9.228, 5375.78, 5188.33, 221),
(109, '[Guide of Plain] Pein', 1122, 25, 307.514, 5503.22, 5350.93, 222),
(110, '[Gypsy Seller] Edone', 1123, 25, 187.631, 5448.14, 4976.37, 223),
(111, '[Mountain Guide] Kay', 1131, 26, 22.043, 5669.16, 5105.24, 231),
(112, '[Ferrell Guild Merchant ] Bith', 1143, 27, 197.989, 5259.72, 5147.64, 243),
(113, '[Ferrell Guild Staff] Robin', 1512, 27, 264.016, 5239.23, 5040.74, 302),
(114, '[Residents] Hotch', 1144, 27, 189.228, 5384.23, 5180.1, 244),
(115, '[Righteous Crusader] Gallahad', 1141, 27, 178.499, 5345.2, 5047.71, 241),
(116, '[Akram Minister] Luce', 1142, 27, 101.871, 5320.52, 5081.27, 242),
(117, '[Ferrell Guild Merchant] Med', 1151, 28, 127.514, 5587.09, 4732.29, 251),
(118, '[Event Info] Judith', 1204, 37, 358.499, 5115.68, 5324.15, 308),
(119, '[Event Info] Santa Claus', 1205, 38, 3.012, 5069.18, 5362.51, 309),
(120, '[Event Info] Loelsch', 1206, 38, 66.941, 5057.19, 5351.61, 310),
(121, '[Event Info] Lucielle Fete', 1203, 40, 333.435, 5254.64, 5216.39, 307),
(122, '[Station Guide] Illiya', 1188, 51, 148.307, 5107.24, 4996.57, 288),
(123, '[Tavern Owner] Anzhelika', 1186, 51, 139.107, 5263.61, 5079.49, 286),
(124, '[Ferrell Guild Banker] Andre', 1180, 51, 0, 5414.86, 5114.41, 280),
(125, '[Magic Goods Seller] Pabel', 1185, 51, 3.008, 5298.98, 5105.03, 285),
(126, '[Arumic Prophet] Olleck Basilasi', 1173, 51, 178.499, 5359.62, 5085.72, 273),
(127, '[Akram Ambassador] Eliot', 1172, 51, 157.957, 5285.69, 4940.95, 272),
(128, '[Eucar Judge] Ishtal', 1171, 51, 206.565, 5430.09, 4937.96, 271),
(129, '[Smith] Pavrick', 1181, 51, 335.763, 5440.45, 5103.41, 281),
(130, '[Ferrell Trader] Sergei', 1184, 51, 258.129, 5452.58, 5077.11, 284),
(131, '[Shamanist] Est', 1191, 54, 84.016, 5088.26, 4257.84, 291),
(132, '[Station Guide] Chacha', 1219, 61, 12.55, 5226.6, 4452.72, 319),
(133, '[Raknu Warrior] Toanu', 1229, 61, 180, 5433.18, 4671.45, 0),
(134, '[Raknu Warrior] Guanu', 1230, 61, 178.499, 5425, 4671.48, 0),
(135, '[Elder of Junon Order] Oscar Patrick', 1214, 61, 157.957, 5371.18, 4546.51, 314),
(136, '[Righteous Crusader] Harold Evan', 1211, 61, 14.293, 5369.75, 4575.29, 311),
(137, '[Smith] Nel Eldora', 1223, 61, 14.293, 5395.55, 4614.05, 323),
(138, '[Akram Ambassador] Jacklyn Cooper', 1215, 61, 180, 5430, 4483.79, 315),
(139, '[Patrol Dog] Stephen', 1244, 61, 180, 5427.52, 4482.43, 0),
(140, '[Raknu Warrior] Jeffrey Lloyd', 1221, 61, 180, 5434.01, 4595.87, 321),
(141, '[Arumic Researcher] Catherine Clara', 1212, 61, 330.956, 5473.37, 4618.79, 312),
(142, '[Ferrell Guild Staff] Gilbert', 1213, 61, 217.594, 5474.35, 4513.74, 313),
(143, '[Storage Keeper] Dustin Leta', 1222, 61, 197.989, 5489.63, 4553.05, 322),
(144, '[Patrol Dog] Max', 1243, 61, 199.965, 5487.27, 4550.96, 0),
(145, '[Raknu Resident] Netty', 1237, 61, 328.307, 5494.83, 4593.46, 0),
(146, '[Raknu Chief] Darka Khan', 1220, 61, 352.369, 5650.09, 4464.73, 320),
(147, '[Chef] Peppie', 1224, 61, 192.55, 5627.37, 4436.05, 324),
(148, '[Raknu Resident] Jerrita', 1236, 61, 303.017, 5657.17, 4455.98, 0),
(149, '[Sikuku Warrior] Ruduck', 1254, 62, 118.187, 5746.77, 4776.18, 0),
(150, '[Sikuku Warrior] Yak', 1255, 62, 298.187, 5761.61, 4779.42, 0),
(151, '[Sikuku Warrior] Seka', 1256, 62, 189.228, 5773.05, 4732.45, 0),
(152, '[Sikuku Chief] Namiel Char', 1252, 62, 311.684, 5807.89, 4714.39, 0),
(153, '[Sikuku Warrior] Wounded Soldier', 1262, 62, 337.957, 5854.03, 4685.47, 0),
(154, '[Sikuku Warrior] Wounded Soldier', 1262, 62, 180, 5822.89, 4683.3, 0),
(155, '[Cleric] Jude', 1251, 62, 153.435, 5767.72, 4687.55, 351),
(156, '[Sikuku Resident] Parah', 1260, 62, 17.989, 5819.41, 4634.66, 0),
(157, '[Kuro Tejina Staff] Keako ', 1043, 22, 187, 5828, 5096, 143),
(158, '[Kuro-Tejina Staff] Buffy', 1024, 1, 185, 5226, 5218, 0);