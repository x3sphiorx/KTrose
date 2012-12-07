-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 10:02 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `storage`
-- 

DROP TABLE IF EXISTS `storage`;
CREATE TABLE IF NOT EXISTS `storage` (
  `owner` int(11) NOT NULL,
  `itemnum` int(11) NOT NULL,
  `itemtype` int(11) NOT NULL,
  `refine` int(11) NOT NULL,
  `durability` int(11) NOT NULL default '40',
  `lifespan` int(11) NOT NULL default '100',
  `slotnum` int(11) NOT NULL,
  `count` int(11) NOT NULL default '1',
  `stats` int(11) NOT NULL default '0',
  `socketed` int(11) NOT NULL default '0',
  `appraised` int(11) NOT NULL default '0',
  `gem` int(11) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Dumping data for table `storage`
-- 

