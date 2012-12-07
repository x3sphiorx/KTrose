-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 09:47 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `list_clan`
-- 

DROP TABLE IF EXISTS `list_clan`;
CREATE TABLE IF NOT EXISTS `list_clan` (
  `id` int(11) NOT NULL auto_increment,
  `logo` int(11) default NULL,
  `back` int(11) default NULL,
  `name` varchar(50) default NULL,
  `cp` int(11) default NULL,
  `grade` int(11) default NULL,
  `slogan` varchar(100) default NULL,
  `news` varchar(200) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=4 ;




