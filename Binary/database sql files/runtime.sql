-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 10:01 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `runtime`
-- 

DROP TABLE IF EXISTS `runtime`;
CREATE TABLE IF NOT EXISTS `runtime` (
  `id` int(11) NOT NULL auto_increment,
  `starttime` varchar(20) collate latin1_general_ci NOT NULL,
  `hours` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci AUTO_INCREMENT=150 ;

-- 
-- Dumping data for table `runtime`
-- 

