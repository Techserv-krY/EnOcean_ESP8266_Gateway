-- phpMyAdmin SQL Dump
-- version 4.8.5
-- https://www.phpmyadmin.net/
--
-- Host: mysql
-- Generation Time: Dec 18, 2019 at 12:03 PM
-- Server version: 8.0.15
-- PHP Version: 7.2.14

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `node_techserv`
--
CREATE DATABASE IF NOT EXISTS `node_techserv` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
USE `node_techserv`;

-- --------------------------------------------------------

--
-- Table structure for table `node_eno_devices`
--

DROP TABLE IF EXISTS `node_eno_devices`;
CREATE TABLE `node_eno_devices` (
  `created` datetime NOT NULL,
  `modified` datetime NOT NULL,
  `shield` varchar(8) NOT NULL,
  `baseid` decimal(3,0) NOT NULL,
  `deviceid` varchar(8) NOT NULL,
  `eep` varchar(8) NOT NULL,
  `name` varchar(30) DEFAULT NULL,
  `wert1` varchar(8) DEFAULT NULL,
  `wert2` varchar(8) DEFAULT NULL,
  `wert3` varchar(8) DEFAULT NULL,
  `wert4` varchar(8) DEFAULT NULL,
  `gruppe1` varchar(30) DEFAULT NULL,
  `gruppe2` varchar(30) DEFAULT NULL,
  `gruppe3` varchar(30) DEFAULT NULL,
  `gruppe4` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- RELATIONSHIPS FOR TABLE `node_eno_devices`:
--   `shield`
--       `node_eno_shields` -> `shield`
--   `eep`
--       `node_eno_eep` -> `eep`
--

-- --------------------------------------------------------

--
-- Table structure for table `node_eno_eep`
--

DROP TABLE IF EXISTS `node_eno_eep`;
CREATE TABLE `node_eno_eep` (
  `func` varchar(30) NOT NULL,
  `manu` varchar(30) NOT NULL,
  `bez` varchar(30) NOT NULL,
  `eep` varchar(8) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- RELATIONSHIPS FOR TABLE `node_eno_eep`:
--

-- --------------------------------------------------------

--
-- Table structure for table `node_eno_room`
--

DROP TABLE IF EXISTS `node_eno_room`;
CREATE TABLE `node_eno_room` (
  `id` int(11) NOT NULL,
  `build` varchar(2) NOT NULL,
  `floor` varchar(3) NOT NULL,
  `room` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- RELATIONSHIPS FOR TABLE `node_eno_room`:
--

-- --------------------------------------------------------

--
-- Table structure for table `node_eno_shields`
--

DROP TABLE IF EXISTS `node_eno_shields`;
CREATE TABLE `node_eno_shields` (
  `created` datetime NOT NULL,
  `modified` datetime NOT NULL,
  `shield` varchar(8) NOT NULL,
  `build` varchar(2) NOT NULL,
  `floor` varchar(3) NOT NULL,
  `room` varchar(20) NOT NULL,
  `ip` varchar(15) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

--
-- RELATIONSHIPS FOR TABLE `node_eno_shields`:
--

--
-- Indexes for dumped tables
--

--
-- Indexes for table `node_eno_devices`
--
ALTER TABLE `node_eno_devices`
  ADD PRIMARY KEY (`deviceid`),
  ADD UNIQUE KEY `name` (`name`),
  ADD KEY `gruppe1` (`gruppe1`),
  ADD KEY `gruppe2` (`gruppe2`),
  ADD KEY `gruppe3` (`gruppe3`),
  ADD KEY `gruppe4` (`gruppe4`),
  ADD KEY `shield` (`shield`),
  ADD KEY `eep` (`eep`);

--
-- Indexes for table `node_eno_eep`
--
ALTER TABLE `node_eno_eep`
  ADD PRIMARY KEY (`eep`) USING BTREE,
  ADD UNIQUE KEY `bez` (`bez`);

--
-- Indexes for table `node_eno_room`
--
ALTER TABLE `node_eno_room`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `node_eno_shields`
--
ALTER TABLE `node_eno_shields`
  ADD UNIQUE KEY `shield` (`shield`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `node_eno_room`
--
ALTER TABLE `node_eno_room`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `node_eno_devices`
--
ALTER TABLE `node_eno_devices`
  ADD CONSTRAINT `node_eno_devices_ibfk_1` FOREIGN KEY (`shield`) REFERENCES `node_eno_shields` (`shield`),
  ADD CONSTRAINT `node_eno_devices_ibfk_2` FOREIGN KEY (`eep`) REFERENCES `node_eno_eep` (`eep`);
COMMIT;
