-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 09:59 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `player_quests`
-- 

DROP TABLE IF EXISTS `player_quests`;
CREATE TABLE IF NOT EXISTS `player_quests` (
  `owner` int(11) NOT NULL,
  `questid` int(11) NOT NULL,
  `starttime` int(11) NOT NULL,
  `vbl` varchar(100) collate latin1_general_ci NOT NULL default '0|0|0|0|0|0|0|0|0|0',
  `switches` varchar(100) collate latin1_general_ci NOT NULL default '0|0|0|0',
  `items` varchar(100) collate latin1_general_ci NOT NULL default '0|0|0|0|0',
  `count` varchar(100) collate latin1_general_ci NOT NULL default '0|0|0|0|0',
  `episodevar` varchar(50) collate latin1_general_ci NOT NULL default '0|0|0|0|0',
  `jobvar` varchar(30) collate latin1_general_ci NOT NULL default '0|0|0',
  `planetvar` varchar(70) collate latin1_general_ci NOT NULL default '0|0|0|0|0|0|0',
  `unionvar` varchar(100) collate latin1_general_ci NOT NULL default '0|0|0|0|0|0|0|0|0|0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- 
-- Dumping data for table `player_quests`
-- 

