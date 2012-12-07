-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 09:54 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `list_respawnzones`
-- 

DROP TABLE IF EXISTS `list_respawnzones`;
CREATE TABLE IF NOT EXISTS `list_respawnzones` (
  `id` int(11) NOT NULL auto_increment,
  `map` int(11) NOT NULL,
  `x` float NOT NULL,
  `y` float NOT NULL,
  `radius` float NOT NULL default '10',
  `type` int(11) NOT NULL default '2',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=95 ;

-- 
-- Dumping data for table `list_respawnzones`
-- 

INSERT INTO `list_respawnzones` (`id`, `map`, `x`, `y`, `radius`, `type`) VALUES 
(1, 22, 5098, 5322, 10, 2),
(2, 1, 5239, 5192, 10, 2),
(3, 24, 5537, 4966, 10, 2),
(4, 2, 5653, 5214, 10, 2),
(5, 51, 5357, 5013, 10, 2),
(6, 22, 5026, 5522, 10, 2),
(7, 22, 5232, 5246, 10, 2),
(8, 22, 5073, 5019, 10, 2),
(9, 22, 5645, 5394, 10, 2),
(10, 22, 5851, 5422, 10, 2),
(11, 21, 5083, 5157, 10, 2),
(12, 21, 5142, 5506, 10, 2),
(13, 21, 5343, 5281, 10, 2),
(14, 23, 5345, 5056, 10, 2),
(15, 23, 5338, 5386, 10, 2),
(19, 24, 5027, 5090, 10, 2),
(20, 24, 5265, 5521, 10, 2),
(21, 24, 5523, 5378, 10, 2),
(22, 25, 5128, 5413, 10, 2),
(23, 25, 5489, 5357, 10, 2),
(24, 25, 5242, 5092, 10, 2),
(25, 25, 5555, 4970, 10, 2),
(27, 2, 5514, 5453, 10, 2),
(28, 2, 5048, 5451, 10, 2),
(29, 29, 5159, 5165, 10, 2),
(30, 29, 5067, 5357, 10, 2),
(31, 29, 5568, 5160, 10, 2),
(32, 29, 5823, 5098, 10, 2),
(33, 29, 5664, 4893, 10, 2),
(34, 26, 5146, 5248, 10, 2),
(35, 26, 5127, 5477, 10, 2),
(36, 26, 5429, 5272, 10, 2),
(37, 26, 5681, 5104, 10, 2),
(38, 26, 5288, 4890, 10, 2),
(39, 27, 5219, 5328, 10, 2),
(40, 27, 5588, 5462, 10, 2),
(41, 28, 5189, 5036, 10, 2),
(42, 28, 5639, 4761, 10, 2),
(43, 28, 5568, 5121, 10, 2),
(44, 28, 5541, 5364, 10, 2),
(45, 28, 5232, 5344, 10, 2),
(46, 51, 5357, 5013, 10, 2),
(47, 51, 5638, 5032, 10, 2),
(48, 51, 5324, 5343, 10, 2),
(49, 51, 5321, 4707, 10, 2),
(50, 52, 5132, 4603, 10, 2),
(51, 52, 5181, 4891, 10, 2),
(52, 52, 5698, 5295, 10, 2),
(53, 52, 6050, 5020, 10, 2),
(54, 52, 5622, 4866, 10, 2),
(55, 52, 5533, 4555, 10, 2),
(56, 22, 5756, 5195, 10, 2),
(57, 6, 5200, 5200, 10, 2),
(58, 58, 5700, 4330, 10, 2),
(59, 31, 5430, 5508, 10, 2),
(60, 32, 5253, 5415, 10, 2),
(61, 33, 5065, 5000, 10, 2),
(62, 33, 5695, 5269, 10, 2),
(63, 53, 5040, 5200, 10, 2),
(64, 54, 5080, 4420, 10, 2),
(65, 55, 5520, 4480, 10, 2),
(66, 56, 5035, 4275, 10, 2),
(67, 57, 5430, 5355, 10, 2),
(68, 61, 5435, 4595, 10, 2),
(69, 62, 5750, 5100, 10, 2),
(70, 63, 6075, 5185, 10, 2),
(71, 64, 5035, 5325, 10, 2),
(72, 65, 5485, 5285, 10, 2),
(73, 11, 5000, 5047, 10, 2),
(74, 12, 5000, 5047, 10, 2),
(75, 13, 5000, 5047, 10, 2),
(76, 59, 5102, 5132, 10, 2),
(77, 9, 5201, 4861, 10, 2),
(78, 8, 5160, 5078, 10, 2),
(79, 4, 5197, 5042, 10, 2),
(80, 37, 5117, 5303, 10, 2),
(81, 38, 5072, 5345, 10, 2),
(82, 3, 5198, 5010, 10, 2),
(83, 5, 5201, 5277, 10, 2),
(84, 15, 5200, 5200, 10, 2),
(85, 40, 5184, 5211, 10, 2),
(86, 41, 5050, 5250, 10, 2),
(87, 101, 5162, 5105, 10, 2),
(88, 74, 5161, 5302, 10, 2),
(89, 20, 5685, 5210, 10, 1),
(90, 20, 5305, 5395, 10, 2),
(91, 20, 5002, 5162, 10, 2),
(92, 20, 5120, 4697, 10, 2),
(93, 20, 5675, 4737, 10, 2);
