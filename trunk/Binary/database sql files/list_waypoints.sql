-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 09:57 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `list_waypoints`
-- 

DROP TABLE IF EXISTS `list_waypoints`;
CREATE TABLE IF NOT EXISTS `list_waypoints` (
  `mapid` int(11) NOT NULL,
  `wpnum` int(11) NOT NULL,
  `mapx` float NOT NULL,
  `mapy` float NOT NULL,
  `wptype` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_general_ci;

-- 
-- Dumping data for table `list_waypoints`
-- 

