-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 09:48 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `list_config`
-- 

DROP TABLE IF EXISTS `list_config`;
CREATE TABLE IF NOT EXISTS `list_config` (
  `exp_rate` int(11) NOT NULL,
  `kill_on_fail` tinyint(1) NOT NULL default '0',
  `drop_rate` int(11) NOT NULL,
  `zuly_rate` int(11) NOT NULL,
  `blue_chance` int(11) NOT NULL,
  `slot_chance` int(11) NOT NULL,
  `stat_chance` int(11) NOT NULL,
  `refine_chance` int(11) NOT NULL,
  `rare_refine` int(11) NOT NULL default '0',
  `conf` varchar(50) NOT NULL,
  `player_damage` int(11) NOT NULL,
  `monster_damage` int(11) NOT NULL,
  `player_acc` int(11) NOT NULL,
  `monster_acc` int(11) NOT NULL,
  `pvp_acc` int(11) NOT NULL,
  `skill_damage` int(11) NOT NULL,
  `maxlevel` int(11) NOT NULL default '255',
  `spawntype` tinyint(4) NOT NULL,
  `dropmultiple` int(11) NOT NULL,
  `massexport` int(11) NOT NULL default '0',
  `attkmult` int(11) NOT NULL,
  `skillmult` int(11) NOT NULL,
  `dropdelay` int(11) NOT NULL,
  `basedroprate` int(11) NOT NULL,
  `ktpointrate` int(11) NOT NULL,
  `movespeedmod` int(11) NOT NULL,
  `greydrop` tinyint(4) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Dumping data for table `list_config`
-- 

INSERT INTO `list_config` (`exp_rate`, `kill_on_fail`, `drop_rate`, `zuly_rate`, `blue_chance`, `slot_chance`, `stat_chance`, `refine_chance`, `rare_refine`, `conf`, `player_damage`, `monster_damage`, `player_acc`, `monster_acc`, `pvp_acc`, `skill_damage`, `maxlevel`, `spawntype`, `dropmultiple`, `massexport`, `attkmult`, `skillmult`, `dropdelay`, `basedroprate`, `ktpointrate`, `movespeedmod`, `greydrop`) VALUES 
(1, 0, 2, 3, 15, 5, 15, 5, 0, 'default', 100, 100, 100, 100, 100, 100, 255, 1, 5, 1, 160, 100, 1, 20, 2, 72, 0);
