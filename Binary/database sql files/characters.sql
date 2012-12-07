-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 09:40 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `characters`
-- 

DROP TABLE IF EXISTS `characters`;
CREATE TABLE IF NOT EXISTS `characters` (
  `account_name` varchar(64) NOT NULL,
  `id` int(11) NOT NULL auto_increment,
  `char_name` varchar(64) NOT NULL,
  `zuly` decimal(11,0) NOT NULL default '500',
  `level` decimal(11,0) NOT NULL default '1',
  `curHp` decimal(18,0) NOT NULL default '50',
  `curMp` decimal(18,0) NOT NULL default '18',
  `str` decimal(11,0) NOT NULL default '15',
  `con` decimal(11,0) NOT NULL default '15',
  `dex` decimal(11,0) NOT NULL default '15',
  `_int` decimal(11,0) NOT NULL default '15',
  `cha` decimal(11,0) NOT NULL default '10',
  `sen` decimal(11,0) NOT NULL default '10',
  `face` decimal(11,0) NOT NULL default '1',
  `hairStyle` decimal(11,0) NOT NULL default '1',
  `sex` decimal(11,0) NOT NULL default '0',
  `exp` decimal(11,0) NOT NULL default '0',
  `skillp` decimal(11,0) NOT NULL default '0',
  `statp` decimal(11,0) NOT NULL default '0',
  `clanid` decimal(11,0) NOT NULL default '0',
  `unionid` decimal(2,0) unsigned NOT NULL default '0',
  `union1points` int(11) unsigned NOT NULL default '0',
  `union2points` int(11) unsigned NOT NULL default '0',
  `union3points` int(11) unsigned NOT NULL default '0',
  `union4points` int(11) unsigned NOT NULL default '0',
  `union5points` int(11) unsigned NOT NULL default '0',
  `union6points` int(11) unsigned NOT NULL default '0',
  `union7points` int(11) unsigned NOT NULL default '0',
  `union8points` int(11) unsigned NOT NULL default '0',
  `union9points` int(11) unsigned NOT NULL default '0',
  `union10points` int(11) unsigned NOT NULL default '0',
  `classid` decimal(11,0) NOT NULL default '0',
  `deletetime` decimal(20,0) NOT NULL default '0',
  `clan_rank` int(11) NOT NULL default '0',
  `stamina` int(11) NOT NULL default '5000',
  `quests` blob,
  `questflags` blob,
  `quickbar` varchar(255) NOT NULL default '0',
  `basic_skills` varchar(255) NOT NULL default '11,12,16,20,41,42,43,181,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,',
  `askill` varchar(255) NOT NULL default '0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0',
  `askilllvl` varchar(255) NOT NULL default '0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0',
  `pskill` varchar(255) NOT NULL default '0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0',
  `pskilllvl` varchar(255) NOT NULL default '0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0',
  `respawnid` int(11) NOT NULL default '89',
  `townid` int(11) NOT NULL default '20',
  `class_skills` varchar(255) NOT NULL default '0',
  `class_skills_level` varchar(255) NOT NULL default '1',
  `isgm` tinyint(1) NOT NULL default '0',
  `isdev` tinyint(1) NOT NULL default '0',
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=24 ;



