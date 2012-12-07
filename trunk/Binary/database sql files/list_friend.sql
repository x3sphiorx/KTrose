-- phpMyAdmin SQL Dump
-- version 2.10.3
-- http://www.phpmyadmin.net
-- 
-- Host: localhost
-- Generation Time: Dec 07, 2012 at 09:49 AM
-- Server version: 5.0.45
-- PHP Version: 5.2.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

-- 
-- Database: `irose`
-- 

-- --------------------------------------------------------

-- 
-- Table structure for table `list_friend`
-- 

DROP TABLE IF EXISTS `list_friend`;
CREATE TABLE IF NOT EXISTS `list_friend` (
  `id` int(11) NOT NULL,
  `idfriend` int(11) NOT NULL,
  `namefriend` varchar(50) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- 
-- Dumping data for table `list_friend`
-- 

