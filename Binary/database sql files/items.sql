-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 01:04 PM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `items`
-- 

DROP TABLE IF EXISTS `items`;
CREATE TABLE IF NOT EXISTS `items` (
  `owner` int(11) NOT NULL default '0',
  `itemnum` int(11) NOT NULL default '0',
  `itemtype` int(11) NOT NULL default '0',
  `refine` int(11) NOT NULL default '0',
  `durability` int(11) NOT NULL default '40',
  `lifespan` int(11) NOT NULL default '100',
  `slotnum` int(11) NOT NULL default '0',
  `count` int(11) NOT NULL default '1',
  `stats` int(11) NOT NULL default '0',
  `socketed` int(11) NOT NULL default '0',
  `appraised` int(11) NOT NULL default '0',
  `gem` int(11) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Dumping data for table `items`
-- 

INSERT INTO `items` (`owner`, `itemnum`, `itemtype`, `refine`, `durability`, `lifespan`, `slotnum`, `count`, `stats`, `socketed`, `appraised`, `gem`) VALUES 
(1, 30, 3, 0, 40, 100, 3, 1, 0, 0, 0, 0),
(1, 1, 8, 0, 40, 100, 7, 1, 0, 0, 0, 0),
(1, 222, 2, 0, 40, 100, 12, 1, 0, 0, 0, 0),
(10, 171, 12, 0, 65, 24, 81, 5, 0, 0, 0, 0),
(4, 841, 10, 0, 40, 100, 44, 1, 0, 0, 1, 0),
(4, 401, 10, 0, 40, 100, 43, 9, 0, 0, 1, 0),
(7, 301, 12, 0, 35, 100, 132, 470, 0, 0, 1, 0),
(7, 161, 12, 0, 81, 18, 78, 4, 0, 0, 0, 0),
(3, 102, 10, 0, 0, 100, 43, 20, 0, 0, 1, 0),
(3, 101, 10, 0, 0, 100, 42, 5, 0, 0, 1, 0),
(4, 59, 10, 0, 40, 100, 42, 96, 0, 0, 1, 0),
(4, 1, 8, 0, 40, 100, 14, 1, 0, 0, 0, 0),
(4, 30, 3, 0, 40, 100, 13, 1, 0, 0, 0, 0),
(3, 291, 7, 0, 35, 100, 11, 1, 0, 0, 1, 0),
(3, 290, 7, 0, 35, 100, 10, 1, 0, 0, 1, 0),
(3, 292, 7, 0, 35, 100, 9, 1, 0, 0, 1, 0),
(3, 1, 8, 0, 40, 100, 7, 1, 0, 0, 0, 0),
(3, 30, 3, 0, 40, 100, 3, 1, 0, 0, 0, 0),
(2, 331, 14, 0, 40, 100, 138, 1, 0, 0, 1, 0),
(2, 232, 14, 0, 40, 100, 137, 1, 0, 0, 1, 0),
(2, 131, 14, 0, 40, 100, 136, 1, 0, 0, 1, 0),
(2, 31, 14, 0, 40, 100, 135, 1, 0, 0, 1, 0),
(2, 101, 14, 0, 40, 100, 102, 1, 0, 0, 1, 0),
(2, 31, 12, 0, 40, 100, 89, 1, 0, 0, 1, 0),
(2, 121, 12, 0, 62, 22, 88, 1, 0, 0, 0, 0),
(2, 178, 12, 0, 53, 71, 87, 1, 0, 0, 0, 0),
(2, 341, 12, 0, 48, 78, 86, 60, 0, 0, 0, 0),
(2, 2, 12, 0, 40, 100, 85, 3, 0, 0, 0, 0),
(2, 196, 12, 0, 40, 100, 84, 9, 0, 0, 0, 0),
(2, 42, 12, 0, 40, 100, 83, 7, 0, 0, 0, 0),
(2, 180, 12, 0, 40, 100, 82, 3, 0, 0, 0, 0),
(2, 184, 12, 0, 40, 100, 81, 2, 0, 0, 0, 0),
(2, 41, 12, 0, 40, 100, 80, 10, 0, 0, 0, 0),
(2, 102, 12, 0, 40, 100, 79, 4, 0, 0, 0, 0),
(2, 4, 12, 0, 40, 100, 78, 4, 0, 0, 0, 0),
(2, 171, 12, 0, 40, 100, 77, 1, 0, 0, 0, 0),
(2, 3, 12, 0, 40, 100, 76, 3, 0, 0, 0, 0),
(2, 173, 12, 0, 40, 100, 75, 10, 0, 0, 0, 0),
(2, 111, 12, 0, 40, 100, 74, 15, 0, 0, 0, 0),
(2, 116, 12, 0, 40, 100, 73, 1, 0, 0, 0, 0),
(2, 5, 12, 0, 40, 100, 72, 2, 0, 0, 0, 0),
(2, 291, 10, 0, 40, 100, 58, 8, 0, 0, 1, 0),
(2, 284, 10, 0, 40, 100, 57, 9, 0, 0, 1, 0),
(2, 282, 10, 0, 40, 100, 56, 1, 0, 0, 1, 0),
(2, 280, 10, 0, 40, 100, 55, 4, 0, 0, 1, 0),
(2, 351, 10, 0, 40, 100, 54, 3, 0, 0, 1, 0),
(2, 394, 10, 0, 40, 100, 53, 1, 0, 0, 1, 0),
(2, 124, 10, 0, 0, 0, 52, 1, 0, 0, 0, 0),
(2, 101, 10, 0, 59, 74, 51, 5, 0, 0, 0, 0),
(2, 1, 10, 0, 0, 100, 50, 9, 0, 0, 1, 0),
(2, 122, 10, 0, 40, 100, 49, 3, 0, 0, 0, 0),
(2, 57, 10, 0, 40, 100, 48, 1, 0, 0, 0, 0),
(2, 103, 10, 0, 40, 100, 47, 2, 0, 0, 0, 0),
(2, 120, 10, 0, 40, 100, 46, 4, 0, 0, 0, 0),
(2, 104, 10, 0, 40, 100, 45, 1, 0, 0, 0, 0),
(2, 121, 10, 0, 40, 100, 44, 1, 0, 0, 0, 0),
(2, 102, 10, 0, 40, 100, 43, 5, 0, 0, 0, 0),
(2, 56, 10, 0, 40, 100, 42, 24, 0, 0, 0, 0),
(2, 498, 5, 0, 50, 100, 37, 1, 0, 0, 1, 0),
(7, 196, 12, 0, 43, 39, 77, 8, 0, 0, 0, 0),
(7, 95, 12, 0, 43, 79, 76, 4, 0, 0, 0, 0),
(7, 111, 12, 0, 58, 33, 75, 5, 0, 0, 0, 0),
(7, 121, 12, 0, 40, 28, 74, 4, 0, 0, 0, 0),
(7, 92, 12, 0, 60, 58, 73, 5, 0, 0, 0, 0),
(7, 172, 12, 0, 41, 62, 72, 1, 0, 0, 0, 0),
(7, 651, 10, 0, 56, 43, 50, 1, 0, 0, 0, 0),
(6, 660, 10, 0, 51, 72, 47, 1, 0, 0, 0, 0),
(6, 811, 10, 0, 47, 68, 46, 1, 0, 0, 0, 0),
(6, 719, 10, 0, 27, 27, 45, 1, 0, 0, 0, 0),
(6, 393, 10, 0, 47, 34, 44, 2, 0, 0, 0, 0),
(6, 108, 10, 0, 40, 100, 43, 86, 0, 0, 1, 0),
(6, 120, 10, 0, 22, 59, 42, 5, 0, 0, 0, 0),
(6, 165, 8, 0, 62, 46, 20, 1, 0, 0, 0, 0),
(6, 11, 3, 0, 55, 34, 19, 1, 0, 0, 0, 0),
(6, 241, 2, 0, 52, 50, 18, 1, 30, 0, 0, 0),
(6, 11, 5, 0, 43, 59, 17, 1, 0, 0, 0, 0),
(6, 103, 8, 32, 43, 43, 16, 1, 218, 0, 0, 0),
(6, 10, 2, 0, 52, 48, 15, 1, 0, 0, 0, 0),
(6, 1, 8, 0, 40, 100, 14, 1, 0, 0, 0, 0),
(6, 30, 3, 0, 40, 100, 13, 1, 0, 0, 0, 0),
(6, 222, 2, 0, 40, 100, 12, 1, 0, 0, 0, 0),
(6, 105, 8, 144, 35, 100, 7, 1, 0, 0, 1, 0),
(6, 33, 5, 144, 35, 100, 6, 1, 0, 0, 1, 0),
(6, 33, 4, 144, 35, 100, 5, 1, 0, 0, 1, 0),
(6, 33, 3, 144, 35, 100, 3, 1, 0, 0, 1, 0),
(6, 33, 2, 144, 35, 100, 2, 1, 0, 0, 1, 0),
(7, 104, 10, 0, 40, 100, 49, 65, 0, 0, 1, 0),
(7, 812, 10, 0, 20, 18, 48, 1, 0, 0, 0, 0),
(7, 102, 10, 0, 40, 30, 47, 9, 0, 0, 0, 0),
(7, 142, 10, 0, 0, 0, 46, 2, 0, 0, 0, 0),
(7, 1, 10, 0, 0, 100, 45, 5, 0, 0, 1, 0),
(7, 403, 10, 0, 55, 42, 44, 10, 0, 0, 0, 0),
(7, 103, 10, 0, 54, 85, 43, 5, 0, 0, 0, 0),
(7, 120, 10, 0, 65, 33, 42, 11, 0, 0, 0, 0),
(7, 301, 8, 0, 72, 51, 34, 1, 0, 0, 0, 0),
(7, 331, 8, 0, 45, 17, 33, 1, 0, 0, 0, 0),
(7, 301, 8, 0, 65, 16, 32, 1, 157, 0, 0, 0),
(7, 241, 2, 0, 35, 71, 31, 1, 0, 0, 0, 0),
(7, 227, 6, 0, 51, 10, 30, 1, 0, 0, 0, 0),
(3, 221, 2, 0, 40, 100, 2, 1, 0, 0, 0, 0),
(5, 97, 12, 0, 43, 69, 76, 5, 0, 0, 0, 0),
(5, 121, 12, 0, 46, 39, 75, 18, 0, 0, 0, 0),
(5, 321, 12, 0, 33, 73, 74, 70, 0, 0, 0, 0),
(5, 185, 12, 0, 65, 58, 73, 7, 0, 0, 0, 0),
(5, 91, 12, 0, 58, 43, 72, 1, 0, 0, 0, 0),
(5, 121, 10, 0, 39, 11, 51, 1, 0, 0, 0, 0),
(5, 410, 10, 0, 36, 63, 50, 16, 0, 0, 0, 0),
(5, 1, 10, 0, 0, 100, 49, 5, 0, 0, 1, 0),
(5, 406, 10, 0, 47, 46, 48, 5, 0, 0, 0, 0),
(5, 102, 10, 0, 0, 100, 47, 25, 0, 0, 1, 0),
(5, 401, 10, 0, 58, 79, 46, 1, 0, 0, 0, 0),
(5, 403, 10, 0, 33, 60, 45, 10, 0, 0, 0, 0),
(5, 402, 10, 0, 38, 11, 44, 7, 0, 0, 0, 0),
(5, 120, 10, 0, 0, 100, 43, 15, 0, 0, 1, 0),
(5, 101, 10, 0, 0, 100, 42, 20, 0, 0, 1, 0),
(5, 3, 9, 0, 35, 100, 21, 1, 0, 0, 1, 0),
(5, 1, 8, 0, 40, 100, 19, 1, 0, 0, 0, 0),
(5, 30, 5, 0, 44, 100, 16, 1, 0, 0, 1, 0),
(5, 30, 3, 0, 40, 100, 15, 1, 0, 0, 0, 0),
(5, 91, 2, 0, 62, 25, 14, 1, 0, 0, 0, 0),
(5, 222, 2, 0, 40, 100, 13, 1, 0, 0, 0, 0),
(5, 231, 8, 0, 17, 62, 12, 1, 0, 0, 0, 0),
(5, 291, 7, 0, 35, 100, 11, 1, 0, 0, 1, 0),
(5, 290, 7, 0, 35, 100, 10, 1, 0, 0, 1, 0),
(5, 292, 7, 0, 35, 100, 9, 1, 0, 0, 1, 0),
(5, 102, 8, 48, 35, 100, 7, 1, 0, 0, 1, 0),
(5, 31, 5, 0, 35, 100, 6, 1, 0, 0, 1, 0),
(5, 31, 4, 0, 27, 100, 5, 1, 0, 0, 1, 0),
(5, 241, 6, 0, 55, 19, 4, 1, 0, 0, 0, 0),
(5, 303, 3, 48, 40, 63, 3, 1, 90, 0, 1, 0),
(5, 31, 2, 0, 35, 100, 2, 1, 0, 0, 1, 0),
(4, 222, 2, 0, 40, 100, 12, 1, 0, 0, 0, 0),
(9, 668, 10, 0, 35, 100, 54, 1, 0, 0, 1, 0),
(9, 657, 10, 0, 35, 100, 47, 1, 0, 0, 1, 0),
(9, 652, 10, 0, 35, 100, 44, 1, 0, 0, 1, 0),
(9, 995, 10, 0, 40, 100, 43, 1, 0, 0, 1, 0),
(9, 104, 10, 0, 40, 100, 42, 67, 0, 0, 1, 0),
(9, 1, 8, 0, 40, 100, 28, 1, 0, 0, 0, 0),
(9, 242, 6, 144, 35, 100, 27, 1, 0, 0, 1, 0),
(9, 5, 8, 144, 40, 100, 26, 1, 0, 0, 1, 0),
(9, 5, 8, 16, 40, 100, 25, 1, 0, 0, 1, 0),
(9, 297, 7, 0, 40, 100, 24, 1, 0, 0, 1, 0),
(9, 296, 7, 0, 40, 100, 23, 1, 0, 0, 1, 0),
(9, 298, 7, 0, 40, 100, 22, 1, 0, 0, 1, 0),
(9, 241, 6, 0, 35, 100, 21, 1, 0, 0, 1, 0),
(9, 290, 7, 0, 40, 100, 20, 1, 0, 0, 1, 0),
(9, 21, 7, 0, 35, 100, 19, 1, 0, 0, 1, 0),
(9, 108, 8, 0, 35, 100, 18, 1, 0, 0, 1, 0),
(9, 34, 3, 80, 40, 100, 17, 1, 0, 0, 1, 0),
(9, 11, 8, 96, 40, 100, 16, 1, 181, 1, 1, 0),
(9, 9, 8, 96, 40, 100, 15, 1, 281, 1, 1, 0),
(9, 30, 3, 0, 40, 100, 14, 1, 0, 0, 0, 0),
(9, 222, 2, 0, 40, 100, 12, 1, 0, 0, 0, 0),
(9, 4, 9, 144, 35, 100, 8, 1, 0, 0, 1, 0),
(9, 10, 8, 144, 40, 100, 7, 1, 191, 1, 1, 0),
(9, 34, 5, 80, 40, 100, 6, 1, 193, 1, 1, 0),
(9, 34, 4, 64, 40, 100, 5, 1, 0, 0, 1, 0),
(9, 1, 6, 144, 40, 100, 4, 1, 0, 0, 1, 0),
(9, 10, 3, 128, 40, 100, 3, 1, 191, 1, 1, 0),
(9, 34, 2, 96, 40, 100, 2, 1, 0, 0, 1, 0),
(9, 3, 1, 144, 40, 100, 1, 1, 214, 0, 1, 0),
(2, 331, 8, 0, 35, 100, 36, 1, 0, 1, 1, 0),
(2, 499, 3, 0, 50, 100, 34, 1, 0, 0, 1, 0),
(2, 1, 8, 0, 40, 50, 33, 1, 0, 0, 1, 0),
(2, 61, 9, 0, 35, 100, 32, 1, 0, 0, 1, 0),
(2, 598, 2, 0, 50, 100, 31, 1, 0, 0, 1, 0),
(2, 4, 1, 0, 40, 100, 30, 1, 0, 0, 1, 0),
(2, 61, 2, 0, 34, 100, 29, 1, 0, 0, 1, 0),
(2, 498, 4, 0, 50, 100, 28, 1, 0, 0, 1, 0),
(2, 30, 5, 0, 44, 100, 27, 1, 0, 0, 1, 0),
(2, 63, 2, 0, 35, 100, 26, 1, 0, 0, 1, 0),
(2, 498, 3, 0, 50, 100, 25, 1, 0, 0, 1, 0),
(2, 3, 1, 0, 40, 100, 24, 1, 0, 0, 1, 0),
(2, 2, 5, 0, 65, 20, 23, 1, 0, 0, 0, 0),
(2, 2, 1, 0, 40, 100, 22, 1, 0, 0, 1, 0),
(2, 3, 2, 48, 42, 100, 21, 1, 105, 0, 1, 0),
(10, 71, 12, 0, 34, 75, 80, 4, 0, 0, 0, 0),
(10, 184, 12, 0, 30, 88, 79, 3, 0, 0, 0, 0),
(10, 180, 12, 0, 59, 37, 78, 2, 0, 0, 0, 0),
(10, 179, 12, 0, 26, 66, 77, 1, 0, 0, 0, 0),
(10, 102, 12, 0, 36, 69, 76, 5, 0, 0, 0, 0),
(10, 111, 12, 0, 45, 50, 75, 1, 0, 0, 0, 0),
(10, 41, 12, 0, 60, 47, 74, 4, 0, 0, 0, 0),
(10, 31, 12, 0, 33, 56, 73, 3, 0, 0, 0, 0),
(10, 178, 12, 0, 57, 10, 72, 1, 0, 0, 0, 0),
(10, 402, 10, 0, 54, 44, 46, 2, 0, 0, 0, 0),
(10, 403, 10, 0, 50, 47, 45, 9, 0, 0, 0, 0),
(10, 102, 10, 0, 0, 100, 44, 5, 0, 0, 1, 0),
(10, 120, 10, 0, 0, 100, 43, 11, 0, 0, 1, 0),
(10, 101, 10, 0, 0, 100, 42, 22, 0, 0, 1, 0),
(10, 4, 4, 0, 67, 82, 18, 1, 0, 0, 0, 0),
(10, 4, 4, 0, 35, 78, 17, 1, 0, 0, 0, 0),
(10, 201, 8, 0, 63, 17, 16, 1, 0, 0, 0, 0),
(10, 30, 3, 0, 40, 100, 15, 1, 0, 0, 0, 0),
(10, 30, 5, 0, 44, 100, 14, 1, 0, 0, 1, 0),
(10, 221, 2, 0, 40, 100, 13, 1, 0, 0, 0, 0),
(10, 2, 3, 0, 46, 11, 12, 1, 0, 0, 0, 0),
(10, 1, 8, 0, 40, 100, 7, 1, 0, 0, 0, 0),
(10, 3, 5, 0, 40, 61, 6, 1, 261, 0, 1, 0),
(10, 2, 4, 0, 38, 13, 5, 1, 0, 0, 0, 0),
(10, 4, 3, 0, 58, 56, 3, 1, 0, 0, 0, 0),
(10, 4, 2, 0, 43, 55, 2, 1, 0, 0, 0, 0),
(2, 4, 3, 32, 90, 77, 20, 1, 0, 0, 1, 0),
(2, 2, 3, 0, 43, 63, 19, 1, 102, 0, 1, 0),
(2, 2, 4, 32, 72, 100, 18, 1, 0, 0, 1, 0),
(2, 30, 3, 0, 40, 100, 17, 1, 0, 0, 0, 0),
(2, 4, 5, 0, 37, 64, 16, 1, 194, 0, 0, 0),
(2, 2, 3, 0, 60, 14, 15, 1, 47, 0, 1, 0),
(16, 55, 12, 0, 40, 100, 79, 69, 0, 0, 1, 0),
(16, 196, 12, 0, 40, 100, 78, 30, 0, 0, 1, 0),
(16, 197, 12, 0, 40, 100, 77, 30, 0, 0, 1, 0),
(16, 112, 12, 0, 40, 100, 76, 30, 0, 0, 1, 0),
(16, 60, 12, 0, 40, 100, 75, 20, 0, 0, 1, 0),
(16, 126, 12, 0, 40, 100, 74, 9, 0, 0, 1, 0),
(16, 1, 12, 0, 40, 100, 73, 8, 0, 0, 1, 0),
(16, 111, 12, 0, 40, 100, 72, 69, 0, 0, 1, 0),
(16, 221, 6, 0, 22, 100, 18, 1, 0, 0, 0, 0),
(16, 221, 6, 0, 22, 100, 17, 1, 79, 0, 1, 0),
(16, 223, 6, 0, 50, 100, 16, 1, 4, 0, 1, 0),
(7, 241, 2, 0, 47, 77, 29, 1, 0, 0, 0, 0),
(7, 303, 8, 0, 42, 63, 28, 1, 0, 0, 0, 0),
(7, 227, 6, 0, 45, 72, 27, 1, 0, 0, 0, 0),
(7, 241, 2, 0, 38, 25, 26, 1, 0, 0, 0, 0),
(12, 56, 10, 0, 0, 100, 43, 3, 0, 0, 1, 0),
(12, 5, 10, 0, 0, 100, 42, 30, 0, 0, 1, 0),
(7, 402, 8, 0, 49, 21, 25, 1, 0, 0, 0, 0),
(7, 202, 8, 0, 35, 100, 24, 1, 0, 0, 1, 0),
(7, 241, 2, 0, 45, 59, 23, 1, 0, 0, 0, 0),
(15, 125, 12, 0, 34, 19, 78, 1, 0, 0, 0, 0),
(15, 171, 12, 0, 49, 23, 77, 7, 0, 0, 0, 0),
(15, 174, 12, 0, 37, 21, 76, 5, 0, 0, 0, 0),
(15, 196, 12, 0, 56, 55, 75, 10, 0, 0, 0, 0),
(15, 111, 12, 0, 32, 75, 74, 9, 0, 0, 0, 0),
(15, 102, 12, 0, 27, 44, 73, 5, 0, 0, 0, 0),
(15, 31, 12, 0, 54, 63, 72, 5, 0, 0, 0, 0),
(15, 102, 10, 0, 0, 100, 45, 20, 0, 0, 1, 0),
(15, 121, 10, 0, 0, 100, 44, 20, 0, 0, 1, 0),
(15, 120, 10, 0, 53, 58, 43, 5, 0, 0, 0, 0),
(15, 101, 10, 0, 0, 100, 42, 28, 0, 0, 1, 0),
(15, 505, 3, 0, 46, 70, 33, 1, 148, 0, 1, 0),
(15, 7, 3, 0, 46, 66, 32, 1, 0, 0, 0, 0),
(15, 305, 4, 0, 33, 78, 29, 1, 47, 0, 1, 0),
(15, 32, 8, 0, 57, 78, 26, 1, 0, 0, 0, 0),
(15, 201, 8, 0, 46, 59, 20, 1, 133, 0, 0, 0),
(15, 4, 4, 0, 50, 30, 18, 1, 0, 0, 0, 0),
(15, 30, 3, 0, 40, 100, 15, 1, 0, 0, 0, 0),
(15, 1, 8, 0, 40, 100, 14, 1, 0, 0, 0, 0),
(15, 221, 2, 0, 40, 100, 12, 1, 0, 0, 0, 0),
(15, 31, 8, 0, 56, 25, 7, 1, 271, 0, 1, 0),
(15, 5, 5, 0, 47, 75, 6, 1, 0, 0, 0, 0),
(15, 2, 4, 0, 28, 83, 5, 1, 178, 0, 1, 0),
(15, 2, 3, 0, 40, 81, 3, 1, 0, 0, 0, 0),
(14, 331, 11, 0, 42, 37, 89, 1, 0, 0, 0, 0),
(14, 197, 12, 0, 51, 56, 88, 1, 0, 0, 0, 0),
(14, 221, 12, 0, 65, 52, 87, 4, 0, 0, 0, 0),
(14, 332, 11, 0, 51, 27, 86, 1, 0, 0, 0, 0),
(14, 148, 12, 0, 43, 46, 85, 1, 0, 0, 0, 0),
(14, 185, 12, 0, 37, 29, 84, 1, 0, 0, 0, 0),
(14, 36, 12, 0, 44, 59, 83, 5, 0, 0, 0, 0),
(14, 127, 12, 0, 50, 14, 82, 9, 0, 0, 0, 0),
(14, 201, 12, 0, 71, 56, 81, 6, 0, 0, 0, 0),
(14, 211, 12, 0, 45, 72, 80, 13, 0, 0, 0, 0),
(14, 73, 12, 0, 27, 50, 79, 1, 0, 0, 0, 0),
(14, 61, 12, 0, 63, 20, 78, 3, 0, 0, 0, 0),
(14, 117, 12, 0, 64, 53, 77, 2, 0, 0, 0, 0),
(14, 114, 12, 0, 46, 81, 76, 9, 0, 0, 0, 0),
(14, 81, 12, 0, 45, 30, 75, 2, 0, 0, 0, 0),
(14, 91, 12, 0, 41, 78, 74, 1, 0, 0, 0, 0),
(14, 171, 12, 0, 34, 12, 73, 10, 0, 0, 0, 0),
(14, 174, 12, 0, 37, 62, 72, 9, 0, 0, 0, 0),
(14, 212, 10, 0, 38, 43, 71, 4, 0, 0, 0, 0),
(14, 670, 10, 0, 58, 78, 70, 1, 0, 0, 0, 0),
(14, 669, 10, 0, 71, 86, 69, 1, 0, 0, 0, 0),
(14, 764, 10, 0, 60, 11, 68, 1, 0, 0, 0, 0),
(14, 777, 10, 0, 54, 21, 67, 1, 0, 0, 0, 0),
(14, 265, 10, 0, 41, 61, 66, 2, 0, 0, 0, 0),
(14, 396, 10, 0, 55, 85, 64, 1, 0, 0, 0, 0),
(14, 270, 10, 0, 53, 38, 63, 5, 0, 0, 0, 0),
(14, 394, 10, 0, 61, 80, 62, 2, 0, 0, 0, 0),
(14, 769, 10, 0, 51, 28, 60, 1, 0, 0, 0, 0),
(14, 760, 10, 0, 66, 62, 59, 1, 0, 0, 0, 0),
(14, 222, 10, 0, 67, 24, 58, 5, 0, 0, 0, 0),
(14, 203, 10, 0, 50, 80, 57, 4, 0, 0, 0, 0),
(14, 428, 10, 0, 49, 41, 55, 2, 0, 0, 0, 0),
(14, 272, 10, 0, 39, 71, 53, 3, 0, 0, 0, 0),
(14, 9, 10, 0, 40, 100, 50, 87, 0, 0, 1, 0),
(14, 408, 10, 0, 48, 66, 49, 4, 0, 0, 0, 0),
(14, 406, 10, 0, 41, 63, 48, 4, 0, 0, 0, 0),
(14, 110, 10, 0, 40, 100, 47, 94, 0, 0, 1, 0),
(14, 402, 10, 0, 66, 56, 46, 12, 0, 0, 0, 0),
(14, 403, 10, 0, 64, 41, 45, 3, 0, 0, 0, 0),
(14, 102, 10, 0, 0, 100, 44, 21, 0, 0, 1, 0),
(14, 909, 10, 0, 40, 100, 42, 3, 0, 0, 1, 0),
(14, 916, 8, 0, 57, 48, 38, 1, 0, 0, 0, 0),
(14, 403, 8, 0, 61, 50, 37, 1, 0, 0, 0, 0),
(14, 14, 8, 0, 67, 82, 35, 1, 0, 0, 0, 0),
(14, 227, 6, 0, 54, 63, 34, 1, 226, 0, 0, 0),
(14, 406, 8, 0, 52, 62, 33, 1, 0, 0, 0, 0),
(14, 307, 8, 0, 57, 62, 32, 1, 179, 0, 0, 0),
(14, 14, 5, 0, 44, 43, 31, 1, 0, 0, 0, 0),
(14, 241, 2, 0, 53, 12, 30, 1, 0, 0, 0, 0),
(14, 5, 8, 32, 57, 57, 29, 1, 0, 1, 0, 0),
(14, 312, 2, 0, 51, 45, 28, 1, 12, 0, 0, 0),
(14, 8, 3, 0, 51, 54, 27, 1, 0, 0, 0, 0),
(14, 221, 2, 0, 40, 100, 26, 1, 0, 0, 0, 0),
(14, 606, 5, 0, 53, 15, 25, 1, 32, 0, 0, 0),
(14, 169, 8, 0, 51, 71, 24, 1, 0, 0, 0, 0),
(14, 4, 3, 144, 75, 48, 23, 1, 0, 0, 0, 0),
(16, 241, 6, 0, 21, 100, 15, 1, 0, 0, 0, 0),
(16, 1, 8, 0, 40, 100, 14, 1, 0, 0, 0, 0),
(16, 30, 5, 0, 44, 100, 13, 1, 0, 0, 1, 0),
(16, 221, 2, 0, 40, 100, 12, 1, 0, 0, 0, 0),
(16, 122, 5, 0, 50, 100, 6, 1, 0, 0, 1, 0),
(16, 122, 4, 0, 50, 100, 5, 1, 0, 0, 1, 0),
(16, 122, 3, 0, 50, 100, 3, 1, 0, 0, 1, 0),
(16, 122, 2, 0, 50, 100, 2, 1, 0, 0, 1, 0),
(14, 63, 8, 0, 45, 71, 22, 1, 0, 0, 0, 0),
(14, 407, 8, 144, 35, 100, 21, 1, 0, 0, 1, 0),
(14, 15, 5, 0, 36, 79, 20, 1, 0, 0, 0, 0),
(14, 64, 3, 0, 48, 15, 19, 1, 0, 0, 0, 0),
(14, 30, 5, 0, 44, 100, 18, 1, 0, 0, 1, 0),
(14, 265, 8, 0, 69, 20, 17, 1, 0, 0, 0, 0),
(14, 1, 8, 0, 40, 100, 16, 1, 0, 0, 0, 0),
(14, 168, 8, 0, 51, 65, 15, 1, 0, 0, 0, 0),
(14, 408, 8, 144, 57, 77, 14, 1, 0, 0, 0, 0),
(14, 30, 3, 0, 40, 100, 13, 1, 0, 0, 0, 0),
(14, 298, 7, 0, 40, 100, 12, 1, 0, 0, 1, 0),
(15, 4, 2, 0, 60, 33, 2, 1, 102, 0, 0, 0),
(14, 294, 7, 0, 40, 100, 11, 1, 0, 0, 1, 0),
(14, 293, 7, 0, 40, 100, 10, 1, 0, 0, 1, 0),
(14, 295, 7, 0, 40, 100, 9, 1, 0, 0, 1, 0),
(14, 401, 8, 144, 65, 12, 7, 1, 0, 0, 0, 0),
(14, 94, 5, 144, 35, 100, 6, 1, 0, 0, 1, 0),
(14, 94, 4, 144, 35, 100, 5, 1, 0, 0, 1, 0),
(14, 94, 3, 144, 35, 100, 3, 1, 0, 0, 1, 0),
(14, 94, 2, 144, 35, 100, 2, 1, 0, 0, 1, 0),
(7, 4, 3, 0, 50, 56, 22, 1, 179, 0, 0, 0),
(7, 3, 4, 0, 73, 31, 21, 1, 0, 0, 0, 0),
(7, 3, 5, 0, 48, 59, 20, 1, 0, 0, 0, 0),
(7, 1, 8, 0, 40, 100, 19, 1, 0, 0, 0, 0),
(7, 221, 2, 0, 40, 100, 18, 1, 0, 0, 0, 0),
(7, 9, 2, 0, 56, 55, 17, 1, 0, 0, 0, 0),
(7, 30, 5, 0, 44, 100, 16, 1, 0, 0, 1, 0),
(7, 312, 2, 0, 66, 72, 15, 1, 185, 0, 0, 0),
(7, 915, 3, 0, 50, 100, 14, 1, 0, 0, 1, 0),
(7, 503, 3, 0, 43, 18, 13, 1, 219, 0, 0, 0),
(7, 30, 3, 0, 40, 100, 12, 1, 0, 0, 0, 0),
(7, 401, 8, 144, 35, 100, 7, 1, 0, 0, 1, 0),
(6, 838, 10, 0, 46, 54, 48, 1, 0, 0, 0, 0),
(6, 765, 10, 0, 52, 23, 49, 1, 0, 0, 0, 0),
(6, 657, 10, 0, 35, 100, 51, 1, 0, 0, 1, 0),
(6, 669, 10, 0, 35, 100, 58, 1, 0, 0, 1, 0),
(6, 668, 10, 0, 35, 100, 59, 1, 0, 0, 1, 0),
(6, 667, 10, 0, 35, 100, 60, 1, 0, 0, 1, 0),
(6, 293, 10, 0, 35, 100, 61, 1, 0, 0, 1, 0),
(6, 102, 12, 0, 73, 17, 72, 2, 0, 0, 0, 0),
(6, 174, 12, 0, 46, 14, 73, 7, 0, 0, 0, 0),
(6, 4, 14, 0, 35, 100, 135, 1, 0, 0, 1, 0),
(6, 102, 14, 0, 35, 100, 136, 1, 0, 0, 1, 0),
(6, 202, 14, 0, 35, 100, 137, 1, 0, 0, 1, 0),
(6, 601, 14, 0, 35, 100, 138, 1, 0, 0, 1, 0),
(7, 3, 5, 16, 55, 77, 6, 1, 0, 0, 0, 0),
(7, 91, 4, 0, 27, 100, 5, 1, 0, 0, 1, 0),
(7, 915, 3, 144, 50, 100, 3, 1, 0, 0, 1, 0),
(7, 2, 2, 0, 60, 18, 2, 1, 193, 0, 0, 0),
(2, 241, 6, 0, 50, 10, 14, 1, 0, 0, 0, 0),
(2, 1, 8, 0, 40, 100, 13, 1, 0, 1, 1, 0),
(2, 221, 2, 0, 40, 100, 12, 1, 0, 0, 0, 0),
(2, 285, 7, 0, 0, 100, 11, 1, 0, 0, 1, 0),
(2, 290, 7, 0, 35, 100, 10, 1, 0, 0, 1, 0),
(2, 334, 8, 144, 35, 100, 7, 1, 0, 0, 1, 0),
(2, 63, 5, 0, 35, 100, 6, 1, 0, 0, 1, 0),
(2, 63, 4, 0, 35, 100, 5, 1, 0, 0, 1, 0),
(2, 4, 6, 0, 40, 100, 4, 1, 0, 0, 1, 0),
(2, 63, 3, 144, 35, 100, 3, 1, 0, 0, 1, 0),
(2, 63, 2, 0, 53, 68, 2, 1, 0, 0, 0, 0),
(12, 4, 2, 0, 56, 75, 12, 1, 0, 0, 0, 0),
(12, 401, 8, 0, 35, 100, 7, 1, 0, 0, 1, 0),
(12, 5, 5, 0, 68, 31, 6, 1, 0, 0, 0, 0),
(12, 4, 4, 0, 51, 10, 5, 1, 0, 0, 0, 0),
(12, 30, 3, 0, 40, 100, 3, 1, 0, 0, 0, 0),
(12, 221, 2, 0, 40, 100, 2, 1, 0, 0, 0, 0),
(8, 155, 14, 0, 40, 100, 128, 1, 0, 0, 1, 0),
(8, 555, 14, 0, 40, 100, 127, 1, 0, 0, 1, 0),
(8, 404, 14, 0, 40, 100, 126, 1, 0, 0, 1, 0),
(8, 103, 14, 0, 40, 100, 125, 1, 0, 0, 1, 0),
(8, 14, 14, 0, 40, 100, 124, 1, 0, 0, 1, 0),
(8, 203, 14, 0, 40, 100, 123, 1, 0, 0, 1, 0),
(8, 556, 14, 0, 40, 100, 122, 1, 0, 0, 1, 0),
(8, 557, 14, 0, 40, 100, 121, 1, 0, 0, 1, 0),
(8, 480, 14, 0, 40, 100, 120, 1, 0, 0, 1, 0),
(8, 707, 14, 0, 40, 100, 118, 1, 0, 0, 1, 0),
(8, 551, 14, 0, 40, 100, 117, 1, 0, 0, 1, 0),
(8, 554, 14, 0, 40, 100, 116, 1, 0, 0, 1, 0),
(8, 12, 14, 0, 40, 100, 115, 1, 0, 0, 1, 0),
(8, 601, 14, 0, 40, 100, 114, 1, 0, 0, 1, 0),
(8, 5, 14, 0, 40, 100, 113, 1, 0, 0, 1, 0),
(8, 106, 14, 0, 40, 100, 112, 1, 0, 0, 1, 0),
(8, 31, 14, 0, 40, 100, 111, 1, 0, 0, 1, 0),
(8, 157, 14, 0, 40, 100, 109, 1, 0, 0, 1, 0),
(8, 156, 14, 0, 40, 100, 108, 1, 0, 0, 1, 0),
(8, 6, 14, 0, 40, 100, 107, 1, 0, 0, 1, 0),
(8, 331, 14, 0, 40, 100, 106, 1, 0, 0, 1, 0),
(8, 231, 14, 0, 40, 100, 105, 1, 0, 0, 1, 0),
(8, 133, 14, 0, 40, 100, 104, 1, 0, 0, 1, 0),
(8, 13, 14, 0, 40, 100, 103, 1, 0, 0, 1, 0),
(8, 131, 14, 0, 40, 100, 102, 1, 0, 0, 1, 0),
(8, 173, 12, 0, 43, 25, 78, 1, 0, 0, 0, 0),
(8, 92, 12, 0, 30, 33, 77, 2, 0, 0, 0, 0),
(8, 112, 12, 0, 35, 79, 76, 5, 0, 0, 0, 0),
(8, 184, 12, 0, 43, 20, 75, 3, 0, 0, 0, 0),
(8, 81, 12, 0, 49, 48, 74, 1, 0, 0, 0, 0),
(8, 95, 12, 0, 60, 63, 73, 4, 0, 0, 0, 0),
(8, 171, 12, 0, 68, 22, 72, 10, 0, 0, 0, 0),
(8, 120, 10, 0, 59, 29, 49, 3, 0, 0, 0, 0),
(8, 402, 10, 0, 39, 70, 48, 4, 0, 0, 0, 0),
(8, 410, 10, 0, 57, 62, 47, 3, 0, 0, 0, 0),
(8, 451, 10, 0, 35, 100, 46, 1, 0, 0, 1, 0),
(8, 401, 10, 0, 40, 100, 45, 6, 0, 0, 1, 0),
(8, 422, 10, 0, 48, 25, 44, 5, 0, 0, 0, 0),
(8, 104, 10, 0, 40, 100, 43, 94, 0, 0, 1, 0),
(8, 101, 10, 0, 40, 100, 42, 999, 0, 0, 1, 0),
(8, 31, 4, 0, 27, 100, 32, 1, 0, 0, 1, 0),
(8, 22, 8, 0, 50, 100, 21, 1, 0, 0, 1, 0),
(8, 4, 8, 0, 50, 100, 20, 1, 0, 0, 1, 0),
(8, 5, 5, 0, 54, 44, 19, 1, 0, 0, 0, 0),
(8, 1, 8, 0, 40, 100, 16, 1, 0, 0, 1, 0),
(8, 136, 8, 0, 58, 31, 15, 1, 0, 0, 0, 0),
(8, 11, 8, 0, 50, 100, 14, 1, 0, 0, 1, 0),
(8, 5, 8, 0, 57, 62, 13, 1, 179, 0, 0, 0),
(8, 221, 2, 0, 40, 100, 12, 1, 0, 0, 0, 0),
(8, 10, 8, 0, 50, 100, 7, 1, 0, 0, 1, 0),
(8, 32, 5, 0, 35, 100, 6, 1, 0, 0, 1, 0),
(8, 32, 4, 0, 35, 100, 5, 1, 0, 0, 1, 0),
(8, 32, 3, 0, 50, 100, 3, 1, 0, 0, 1, 0),
(8, 32, 2, 0, 35, 100, 2, 1, 0, 0, 1, 0),
(17, 8, 1, 0, 50, 100, 1, 1, 0, 0, 1, 0);
