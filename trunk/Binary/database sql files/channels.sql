-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 09:39 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `channels`
-- 

DROP TABLE IF EXISTS `channels`;
CREATE TABLE IF NOT EXISTS `channels` (
  `id` int(11) NOT NULL,
  `name` varchar(255) default NULL,
  `host` varchar(255) default NULL,
  `port` int(11) default NULL,
  `status` int(11) default NULL,
  `owner` int(11) default NULL,
  `lansubmask` varchar(255) default NULL,
  `lanip` varchar(255) default NULL,
  `connected` int(11) default NULL,
  `maxconnections` int(11) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Dumping data for table `channels`
-- 

INSERT INTO `channels` (`id`, `name`, `host`, `port`, `status`, `owner`, `lansubmask`, `lanip`, `connected`, `maxconnections`) VALUES 
(1, 'Server 1', '127.0.0.1', 29100, NULL, 0, NULL, NULL, 0, 0),
(2, 'Channel 1', '127.0.0.1', 29200, NULL, 1, NULL, NULL, 0, 500);
